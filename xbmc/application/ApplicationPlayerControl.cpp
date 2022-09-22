/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "ApplicationPlayerControl.h"

#include "FileItem.h"
#include "GUIUserMessages.h"
#include "PartyModeManager.h"
#include "PlayListPlayer.h"
#include "ServiceBroker.h"
#include "URL.h"
#include "Util.h"
#include "addons/AddonManager.h"
#include "application/ApplicationComponents.h"
#include "application/ApplicationPlayer.h"
#include "application/ApplicationPlayerInfo.h"
#include "application/ApplicationStackHelper.h"
#include "application/ApplicationVolumeHandling.h"
#include "cores/AudioEngine/Interfaces/AE.h"
#include "dialogs/GUIDialogBusy.h"
#include "dialogs/GUIDialogCache.h"
#include "dialogs/GUIDialogSimpleMenu.h"
#include "filesystem/PluginDirectory.h"
#include "filesystem/UPnPDirectory.h"
#include "guilib/GUIComponent.h"
#include "guilib/GUIWindowManager.h"
#include "guilib/LocalizeStrings.h"
#include "messaging/ApplicationMessenger.h"
#include "playlists/PlayList.h"
#include "playlists/PlayListFactory.h"
#include "playlists/SmartPlayList.h"
#include "pvr/PVRManager.h"
#include "pvr/guilib/PVRGUIActions.h"
#include "settings/AdvancedSettings.h"
#include "settings/MediaSettings.h"
#include "settings/Settings.h"
#include "settings/SettingsComponent.h"
#include "storage/MediaManager.h"
#include "threads/IRunnable.h"
#include "utils/log.h"
#include "utils/URIUtils.h"
#include "video/VideoDatabase.h"
#include "video/VideoInfoTag.h"

#include <chrono>

using namespace std::chrono_literals;

namespace
{
class CCreateAndLoadPlayList : public IRunnable
{
public:
  CCreateAndLoadPlayList(CFileItem& item, std::unique_ptr<PLAYLIST::CPlayList>& playlist)
    : m_item(item), m_playlist(playlist)
  {
  }

  void Run() override
  {
    const std::unique_ptr<PLAYLIST::CPlayList> playlist(PLAYLIST::CPlayListFactory::Create(m_item));
    if (playlist)
    {
      if (playlist->Load(m_item.GetPath()))
        *m_playlist = *playlist;
    }
  }

private:
  CFileItem& m_item;
  std::unique_ptr<PLAYLIST::CPlayList>& m_playlist;
};
} // namespace

CApplicationPlayerControl::CApplicationPlayerControl(bool &bStop,
                                                     IPlayerCallback& cb)
  : m_bStop(bStop),
    m_cb(cb)
{
}

bool CApplicationPlayerControl::PlayFile(CFileItem item,
                                         const std::string& player, bool bRestart)
{
  // Ensure the MIME type has been retrieved for http:// and shout:// streams
  if (item.GetMimeType().empty())
    item.FillInMimeType();

  auto& components = CServiceBroker::GetAppComponents();
  const auto appPlayer = components.GetComponent<CApplicationPlayer>();
  const auto stackHelper = components.GetComponent<CApplicationStackHelper>();
  if (!appPlayer || !stackHelper)
    return false;

  if (!bRestart)
  {
    // bRestart will be true when called from PlayStack(), skipping this block
    appPlayer->SetPlaySpeed(1);

    m_nextPlaylistItem = -1;
    stackHelper->Clear();

    if (item.IsVideo())
      CUtil::ClearSubtitles();
  }

  if (item.IsDiscStub())
  {
    return CServiceBroker::GetMediaManager().playStubFile(item);
  }

  if (item.IsPlayList())
    return false;

  // if the item is a plugin we need to resolve the plugin paths
  if (URIUtils::HasPluginPath(item) &&
      !XFILE::CPluginDirectory::GetResolvedPluginResult(item))
    return false;

#ifdef HAS_UPNP
  if (URIUtils::IsUPnP(item.GetPath()))
  {
    if (!XFILE::CUPnPDirectory::GetResource(item.GetURL(), item))
      return false;
  }
#endif

  // if we have a stacked set of files, we need to setup our stack routines for
  // "seamless" seeking and total time of the movie etc.
  // will recall with restart set to true
  if (item.IsStack())
    return PlayStack(item, bRestart);

  CPlayerOptions options;

  if (item.HasProperty("StartPercent"))
  {
    options.startpercent = item.GetProperty("StartPercent").asDouble();
    item.SetStartOffset(0);
  }

  options.starttime = CUtil::ConvertMilliSecsToSecs(item.GetStartOffset());

  if (bRestart)
  {
    // have to be set here due to playstack using this for starting the file
    if (item.HasVideoInfoTag())
      options.state = item.GetVideoInfoTag()->GetResumePoint().playerState;
  }
  if (!bRestart || stackHelper->IsPlayingISOStack())
  {
    // the following code block is only applicable when bRestart is false OR to ISO stacks

    if (item.IsVideo())
    {
      // open the d/b and retrieve the bookmarks for the current movie
      CVideoDatabase dbs;
      dbs.Open();

      std::string path = item.GetPath();
      std::string videoInfoTagPath(item.GetVideoInfoTag()->m_strFileNameAndPath);
      if (videoInfoTagPath.find("removable://") == 0 || item.IsVideoDb())
        path = videoInfoTagPath;
      dbs.LoadVideoInfo(path, *item.GetVideoInfoTag());

      if (item.HasProperty("savedplayerstate"))
      {
        options.starttime = CUtil::ConvertMilliSecsToSecs(item.GetStartOffset());
        options.state = item.GetProperty("savedplayerstate").asString();
        item.ClearProperty("savedplayerstate");
      }
      else if (item.GetStartOffset() == STARTOFFSET_RESUME)
      {
        options.starttime = 0.0;
        if (item.IsResumePointSet())
        {
          options.starttime = item.GetCurrentResumeTime();
          if (item.HasVideoInfoTag())
            options.state = item.GetVideoInfoTag()->GetResumePoint().playerState;
        }
        else
        {
          CBookmark bookmark;
          std::string path = item.GetPath();
          if (item.HasVideoInfoTag() && StringUtils::StartsWith(item.GetVideoInfoTag()->m_strFileNameAndPath, "removable://"))
            path = item.GetVideoInfoTag()->m_strFileNameAndPath;
          else if (item.HasProperty("original_listitem_url") && URIUtils::IsPlugin(item.GetProperty("original_listitem_url").asString()))
            path = item.GetProperty("original_listitem_url").asString();
          if (dbs.GetResumeBookMark(path, bookmark))
          {
            options.starttime = bookmark.timeInSeconds;
            options.state = bookmark.playerState;
          }
        }

        if (options.starttime == 0.0 && item.HasVideoInfoTag())
        {
          // No resume point is set, but check if this item is part of a multi-episode file
          const CVideoInfoTag *tag = item.GetVideoInfoTag();

          if (tag->m_iBookmarkId > 0)
          {
            CBookmark bookmark;
            dbs.GetBookMarkForEpisode(*tag, bookmark);
            options.starttime = bookmark.timeInSeconds;
            options.state = bookmark.playerState;
          }
        }
      }
      else if (item.HasVideoInfoTag())
      {
        const CVideoInfoTag *tag = item.GetVideoInfoTag();

        if (tag->m_iBookmarkId > 0)
        {
          CBookmark bookmark;
          dbs.GetBookMarkForEpisode(*tag, bookmark);
          options.starttime = bookmark.timeInSeconds;
          options.state = bookmark.playerState;
        }
      }

      dbs.Close();
    }
  }

  // a disc image might be Blu-Ray disc
  if (!(options.startpercent > 0.0 || options.starttime > 0.0) &&
      (item.IsBDFile() || item.IsDiscImage()))
  {
    //check if we must show the simplified bd menu
    if (!CGUIDialogSimpleMenu::ShowPlaySelection(item))
      return true;
  }

  // this really aught to be inside !bRestart, but since PlayStack
  // uses that to init playback, we have to keep it outside
  const PLAYLIST::Id playlistId = CServiceBroker::GetPlaylistPlayer().GetCurrentPlaylist();
  if (item.IsAudio() && playlistId == PLAYLIST::TYPE_MUSIC)
  { // playing from a playlist by the looks
    // don't switch to fullscreen if we are not playing the first item...
    options.fullscreen = !CServiceBroker::GetPlaylistPlayer().HasPlayedFirstFile() &&
        CServiceBroker::GetSettingsComponent()->GetSettings()->GetBool(
        CSettings::SETTING_MUSICFILES_SELECTACTION) &&
        !CMediaSettings::GetInstance().DoesMediaStartWindowed();
  }
  else if (item.IsVideo() && playlistId == PLAYLIST::TYPE_VIDEO &&
           CServiceBroker::GetPlaylistPlayer().GetPlaylist(playlistId).size() > 1)
  { // playing from a playlist by the looks
    // don't switch to fullscreen if we are not playing the first item...
    options.fullscreen = !CServiceBroker::GetPlaylistPlayer().HasPlayedFirstFile() &&
        CServiceBroker::GetSettingsComponent()->GetAdvancedSettings()->m_fullScreenOnMovieStart &&
        !CMediaSettings::GetInstance().DoesMediaStartWindowed();
  }
  else if (stackHelper->IsPlayingRegularStack())
  {
    //! @todo - this will fail if user seeks back to first file in stack
    if (stackHelper->GetCurrentPartNumber() == 0 ||
        stackHelper->GetRegisteredStack(item)->GetStartOffset() != 0)
      options.fullscreen = CServiceBroker::GetSettingsComponent()->GetAdvancedSettings()->
          m_fullScreenOnMovieStart && !CMediaSettings::GetInstance().DoesMediaStartWindowed();
    else
      options.fullscreen = false;
  }
  else
    options.fullscreen = CServiceBroker::GetSettingsComponent()->GetAdvancedSettings()->
        m_fullScreenOnMovieStart && !CMediaSettings::GetInstance().DoesMediaStartWindowed();

  // stereo streams may have lower quality, i.e. 32bit vs 16 bit
  options.preferStereo = CServiceBroker::GetSettingsComponent()->GetAdvancedSettings()->m_videoPreferStereoStream &&
                         CServiceBroker::GetActiveAE()->HasStereoAudioChannelCount();

  // reset VideoStartWindowed as it's a temp setting
  CMediaSettings::GetInstance().SetMediaStartWindowed(false);

  {
    // for playing a new item, previous playing item's callback may already
    // pushed some delay message into the threadmessage list, they are not
    // expected be processed after or during the new item playback starting.
    // so we clean up previous playing item's playback callback delay messages here.
    int previousMsgsIgnoredByNewPlaying[] = {
      GUI_MSG_PLAYBACK_STARTED,
      GUI_MSG_PLAYBACK_ENDED,
      GUI_MSG_PLAYBACK_STOPPED,
      GUI_MSG_PLAYLIST_CHANGED,
      GUI_MSG_PLAYLISTPLAYER_STOPPED,
      GUI_MSG_PLAYLISTPLAYER_STARTED,
      GUI_MSG_PLAYLISTPLAYER_CHANGED,
      GUI_MSG_QUEUE_NEXT_ITEM,
      0
    };
    int dMsgCount = CServiceBroker::GetGUI()->GetWindowManager().RemoveThreadMessageByMessageIds(&previousMsgsIgnoredByNewPlaying[0]);
    if (dMsgCount > 0)
      CLog::LogF(LOGDEBUG, "Ignored {} playback thread messages", dMsgCount);
  }

  const auto appVolume = components.GetComponent<CApplicationVolumeHandling>();
  appPlayer->OpenFile(item, options,
                      CServiceBroker::GetPlayerCoreFactory(), player, m_cb);
  appPlayer->SetVolume(appVolume->GetVolumeRatio());
  appPlayer->SetMute(appVolume->IsMuted());

#if !defined(TARGET_POSIX)
  CGUIComponent *gui = CServiceBroker::GetGUI();
  if (gui)
    gui->GetAudioManager().Enable(false);
#endif

  if (item.HasPVRChannelInfoTag())
    CServiceBroker::GetPlaylistPlayer().SetCurrentPlaylist(PLAYLIST::TYPE_NONE);

  return true;
}

bool CApplicationPlayerControl::PlayMedia(CFileItem& item,
                                          const std::string& player,
                                          PLAYLIST::Id playlistId)
{
  // if the item is a plugin we need to resolve the plugin paths
  if (URIUtils::HasPluginPath(item) && !XFILE::CPluginDirectory::GetResolvedPluginResult(item))
    return false;

  if (item.IsSmartPlayList())
  {
    CFileItemList items;
    CUtil::GetRecursiveListing(item.GetPath(), items, "", XFILE::DIR_FLAG_NO_FILE_DIRS);
    if (items.Size())
    {
      CSmartPlaylist smartpl;
      //get name and type of smartplaylist, this will always succeed as GetDirectory also did this.
      smartpl.OpenAndReadName(item.GetURL());
      PLAYLIST::CPlayList playlist;
      playlist.Add(items);
      PLAYLIST::Id smartplPlaylistId = PLAYLIST::TYPE_VIDEO;

      if (smartpl.GetType() == "songs" || smartpl.GetType() == "albums" ||
          smartpl.GetType() == "artists")
        smartplPlaylistId = PLAYLIST::TYPE_MUSIC;

      return ProcessAndStartPlaylist(smartpl.GetName(), playlist, smartplPlaylistId);
    }
  }
  else if (item.IsPlayList() || item.IsInternetStream())
  {
    // Not owner. Dialog auto-deletes itself.
    CGUIDialogCache* dlgCache =
        new CGUIDialogCache(5s, g_localizeStrings.Get(10214), item.GetLabel());

    //is or could be a playlist
    std::unique_ptr<PLAYLIST::CPlayList> playlist;
    CCreateAndLoadPlayList getPlaylist(item, playlist);
    bool cancelled = !CGUIDialogBusy::Wait(&getPlaylist, 100, true);

    if (dlgCache)
    {
      dlgCache->Close();
      if (dlgCache->IsCanceled())
        cancelled = true;
    }

    if (cancelled)
      return true;

    if (playlist)
    {

      if (playlistId != PLAYLIST::TYPE_NONE)
      {
        int track=0;
        if (item.HasProperty("playlist_starting_track"))
          track = (int)item.GetProperty("playlist_starting_track").asInteger();
        return ProcessAndStartPlaylist(item.GetPath(), *playlist, playlistId, track);
      }
      else
      {
        CLog::Log(LOGWARNING,
                  "CApplication::PlayMedia called to play a playlist {} but no idea which playlist "
                  "to use, playing first item",
                  item.GetPath());
        if (playlist->size())
          return PlayFile(*(*playlist)[0], "", false);
      }
    }
  }
  else if (item.IsPVR())
  {
    return CServiceBroker::GetPVRManager().GUIActions()->PlayMedia(CFileItemPtr(new CFileItem(item)));
  }

  CURL path(item.GetPath());
  if (path.GetProtocol() == "game")
  {
    ADDON::AddonPtr addon;
    if (CServiceBroker::GetAddonMgr().GetAddon(path.GetHostName(), addon,
                                               ADDON::ADDON_GAMEDLL,
                                               ADDON::OnlyEnabled::CHOICE_YES))
    {
      CFileItem addonItem(addon);
      return PlayFile(addonItem, player, false);
    }
  }

  //nothing special just play
  return PlayFile(item, player, false);
}

bool CApplicationPlayerControl::
ProcessAndStartPlaylist(const std::string& strPlayList,
                        PLAYLIST::CPlayList& playlist,
                        PLAYLIST::Id playlistId,
                        int track)
{
  CLog::Log(LOGDEBUG, "CApplicationPlayerControl::ProcessAndStartPlaylist({}, {})", strPlayList, playlistId);

  // initial exit conditions
  // no songs in playlist just return
  if (playlist.size() == 0)
    return false;

  // illegal playlist
  if (playlistId == PLAYLIST::TYPE_NONE || playlistId == PLAYLIST::TYPE_PICTURE)
    return false;

  // setup correct playlist
  CServiceBroker::GetPlaylistPlayer().ClearPlaylist(playlistId);

  // if the playlist contains an internet stream, this file will be used
  // to generate a thumbnail for musicplayer.cover
  m_strPlayListFile = strPlayList;

  // add the items to the playlist player
  CServiceBroker::GetPlaylistPlayer().Add(playlistId, playlist);

  // if we have a playlist
  if (CServiceBroker::GetPlaylistPlayer().GetPlaylist(playlistId).size())
  {
    // start playing it
    CServiceBroker::GetPlaylistPlayer().SetCurrentPlaylist(playlistId);
    CServiceBroker::GetPlaylistPlayer().Reset();
    CServiceBroker::GetPlaylistPlayer().Play(track, "");
    return true;
  }
  return false;
}

void CApplicationPlayerControl::SeekTime(double dTime)
{
  auto& components = CServiceBroker::GetAppComponents();
  const auto appPlayer = components.GetComponent<CApplicationPlayer>();
  const auto stackHelper = components.GetComponent<CApplicationStackHelper>();

  if (appPlayer && appPlayer->IsPlaying() && (dTime >= 0.0))
  {
    if (!appPlayer->CanSeek())
      return;

    if (stackHelper && stackHelper->IsPlayingRegularStack())
    {
      // find the item in the stack we are seeking to, and load the new
      // file if necessary, and calculate the correct seek within the new
      // file.  Otherwise, just fall through to the usual routine if the
      // time is higher than our total time.
      int partNumberToPlay = stackHelper->GetStackPartNumberAtTimeMs(static_cast<uint64_t>(dTime * 1000.0));
      uint64_t startOfNewFile = stackHelper->GetStackPartStartTimeMs(partNumberToPlay);
      if (partNumberToPlay == stackHelper->GetCurrentPartNumber())
        appPlayer->SeekTime(static_cast<uint64_t>(dTime * 1000.0) - startOfNewFile);
      else
      { // seeking to a new file
        stackHelper->SetStackPartCurrentFileItem(partNumberToPlay);
        CFileItem *item = new CFileItem(stackHelper->GetCurrentStackPartFileItem());
        item->SetStartOffset(static_cast<uint64_t>(dTime * 1000.0) - startOfNewFile);
        // don't just call "PlayFile" here, as we are quite likely called from the
        // player thread, so we won't be able to delete ourselves.
        CServiceBroker::GetAppMessenger()->PostMsg(TMSG_MEDIA_PLAY, 1, 0, static_cast<void*>(item));
      }
      return;
    }
    // convert to milliseconds and perform seek
    appPlayer->SeekTime( static_cast<int64_t>( dTime * 1000.0 ) );
  }
}

void CApplicationPlayerControl::SeekPercentage(float percent)
{
  auto& components = CServiceBroker::GetAppComponents();
  const auto appPlayer = components.GetComponent<CApplicationPlayer>();
  const auto appPlayerInfo = components.GetComponent<CApplicationPlayerInfo>();
  const auto stackHelper = components.GetComponent<CApplicationStackHelper>();

  if (appPlayer && appPlayer->IsPlaying() && (percent >= 0.0f))
  {
    if (!appPlayer->CanSeek())
      return;
    if (stackHelper && stackHelper->IsPlayingRegularStack())
      SeekTime(static_cast<double>(percent) * 0.01 * appPlayerInfo->GetTotalTime());
    else
      appPlayer->SeekPercentage(percent);
  }
}

void CApplicationPlayerControl::StopPlaying()
{
  CGUIComponent *gui = CServiceBroker::GetGUI();

  if (gui)
  {
    int iWin = gui->GetWindowManager().GetActiveWindow();
    auto& components = CServiceBroker::GetAppComponents();
    const auto appPlayer = components.GetComponent<CApplicationPlayer>();
    if (appPlayer && appPlayer->IsPlaying())
    {
      appPlayer->ClosePlayer();

      // turn off visualisation window when stopping
      if ((iWin == WINDOW_VISUALISATION ||
           iWin == WINDOW_FULLSCREEN_VIDEO ||
           iWin == WINDOW_FULLSCREEN_GAME) &&
           !m_bStop)
        gui->GetWindowManager().PreviousWindow();

      g_partyModeManager.Disable();
    }
  }
}

bool CApplicationPlayerControl::PlayStack(CFileItem& item, bool bRestart)
{
  auto& components = CServiceBroker::GetAppComponents();
  const auto stackHelper = components.GetComponent<CApplicationStackHelper>();
  if (!stackHelper || !stackHelper->InitializeStack(item))
    return false;

  int startoffset = stackHelper->InitializeStackStartPartAndOffset(item);

  CFileItem selectedStackPart = stackHelper->GetCurrentStackPartFileItem();
  selectedStackPart.SetStartOffset(startoffset);

  if (item.HasProperty("savedplayerstate"))
  {
    selectedStackPart.SetProperty("savedplayerstate", item.GetProperty("savedplayerstate")); // pass on to part
    item.ClearProperty("savedplayerstate");
  }

  return PlayFile(selectedStackPart, "", true);
}
