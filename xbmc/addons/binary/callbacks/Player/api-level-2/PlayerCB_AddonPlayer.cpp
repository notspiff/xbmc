/*
 *      Copyright (C) 2015 Team KODI
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with KODI; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "Application.h"
#include "FileItem.h"
#include "addons/Addon.h"
#include "addons/binary/BinaryAddonManager.h"
#include "addons/binary/ExceptionHandling.h"
#include "addons/binary/callbacks/AddonCallbacks.h"
#include "messaging/ApplicationMessenger.h"
#include "playlists/PlayList.h"
#include "settings/AdvancedSettings.h"
#include "settings/MediaSettings.h"

#include "AddonCallbacksPlayer.h"
#include "PlayerCB_AddonPlayer.h"

using namespace ADDON;
using namespace KODI::MESSAGING;

namespace PlayerLIB
{
namespace V2
{
extern "C"
{

void CPlayerCB_AddonPlayer::Init(CB_PlayerLib *callbacks)
{
  callbacks->AddonPlayer.GetSupportedMedia            = CPlayerCB_AddonPlayer::GetSupportedMedia;
  callbacks->AddonPlayer.New                          = CPlayerCB_AddonPlayer::New;
  callbacks->AddonPlayer.Delete                       = CPlayerCB_AddonPlayer::Delete;
  callbacks->AddonPlayer.SetCallbacks                 = CPlayerCB_AddonPlayer::SetCallbacks;
  callbacks->AddonPlayer.PlayFile                     = CPlayerCB_AddonPlayer::PlayFile;
  callbacks->AddonPlayer.PlayFileItem                 = CPlayerCB_AddonPlayer::PlayFileItem;
  callbacks->AddonPlayer.Stop                         = CPlayerCB_AddonPlayer::Stop;
  callbacks->AddonPlayer.Pause                        = CPlayerCB_AddonPlayer::Pause;
  callbacks->AddonPlayer.PlayNext                     = CPlayerCB_AddonPlayer::PlayNext;
  callbacks->AddonPlayer.PlayPrevious                 = CPlayerCB_AddonPlayer::PlayPrevious;
  callbacks->AddonPlayer.PlaySelected                 = CPlayerCB_AddonPlayer::PlaySelected;
  callbacks->AddonPlayer.IsPlaying                    = CPlayerCB_AddonPlayer::IsPlaying;
  callbacks->AddonPlayer.IsPlayingAudio               = CPlayerCB_AddonPlayer::IsPlayingAudio;
  callbacks->AddonPlayer.IsPlayingVideo               = CPlayerCB_AddonPlayer::IsPlayingVideo;
  callbacks->AddonPlayer.IsPlayingRDS                 = CPlayerCB_AddonPlayer::IsPlayingRDS;
  callbacks->AddonPlayer.GetPlayingFile               = CPlayerCB_AddonPlayer::GetPlayingFile;
  callbacks->AddonPlayer.GetTotalTime                 = CPlayerCB_AddonPlayer::GetTotalTime;
  callbacks->AddonPlayer.GetTime                      = CPlayerCB_AddonPlayer::GetTime;
  callbacks->AddonPlayer.SeekTime                     = CPlayerCB_AddonPlayer::SeekTime;
  callbacks->AddonPlayer.GetAvailableAudioStreams     = CPlayerCB_AddonPlayer::GetAvailableAudioStreams;
  callbacks->AddonPlayer.SetAudioStream               = CPlayerCB_AddonPlayer::SetAudioStream;
  callbacks->AddonPlayer.GetAvailableSubtitleStreams  = CPlayerCB_AddonPlayer::GetAvailableSubtitleStreams;
  callbacks->AddonPlayer.SetSubtitleStream            = CPlayerCB_AddonPlayer::SetSubtitleStream;
  callbacks->AddonPlayer.ShowSubtitles                = CPlayerCB_AddonPlayer::ShowSubtitles;
  callbacks->AddonPlayer.GetCurrentSubtitleName       = CPlayerCB_AddonPlayer::GetCurrentSubtitleName;
  callbacks->AddonPlayer.AddSubtitle                  = CPlayerCB_AddonPlayer::AddSubtitle;
  callbacks->AddonPlayer.ClearList                    = CPlayerCB_AddonPlayer::ClearList;
}

char* CPlayerCB_AddonPlayer::GetSupportedMedia(void* addonData, int mediaType)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks*>(addonData);
    if (!helper)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p')",
                                        __FUNCTION__, helper);
    std::string result;
    if (mediaType == PlayList_Music)
      result = g_advancedSettings.m_videoExtensions;
    else if (mediaType == PlayList_Video)
      result = g_advancedSettings.GetMusicExtensions();
    else if (mediaType == PlayList_Picture)
      result = g_advancedSettings.m_pictureExtensions;
    else
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (mediaType='%i')",
                                        __FUNCTION__, mediaType);
    char* ret = strdup(result.c_str());
    return ret;
  }
  HANDLE_ADDON_EXCEPTION

  return nullptr;
}

PLAYERHANDLE CPlayerCB_AddonPlayer::New(void *addonData)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks*>(addonData);
    if (!helper)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p')",
                                        __FUNCTION__, helper);

    CAddonPlayerControl* player = new CAddonPlayerControl(helper->GetAddon());
    return player;
  }
  HANDLE_ADDON_EXCEPTION

  return nullptr;
}

void CPlayerCB_AddonPlayer::Delete(void *addonData, PLAYERHANDLE handle)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);

    delete static_cast<CAddonPlayerControl*>(handle);
  }
  HANDLE_ADDON_EXCEPTION
}

void CPlayerCB_AddonPlayer::SetCallbacks(
        void*             addonData,
        PLAYERHANDLE      handle,
        PLAYERHANDLE      cbhdl,
        void      (*CBOnPlayBackStarted)     (PLAYERHANDLE cbhdl),
        void      (*CBOnPlayBackEnded)       (PLAYERHANDLE cbhdl),
        void      (*CBOnPlayBackStopped)     (PLAYERHANDLE cbhdl),
        void      (*CBOnPlayBackPaused)      (PLAYERHANDLE cbhdl),
        void      (*CBOnPlayBackResumed)     (PLAYERHANDLE cbhdl),
        void      (*CBOnQueueNextItem)       (PLAYERHANDLE cbhdl),
        void      (*CBOnPlayBackSpeedChanged)(PLAYERHANDLE cbhdl, int iSpeed),
        void      (*CBOnPlayBackSeek)        (PLAYERHANDLE cbhdl, int iTime, int seekOffset),
        void      (*CBOnPlayBackSeekChapter) (PLAYERHANDLE cbhdl, int iChapter))
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle || !cbhdl)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', handle='%p', cbhdl='%p')",
                                        __FUNCTION__, helper, handle, cbhdl);

    CAddonPlayerControl* pAddonControl = static_cast<CAddonPlayerControl*>(handle);

    CSingleLock lock(pAddonControl->m_playStateMutex);
    pAddonControl->m_cbhdl                    = cbhdl;
    pAddonControl->CBOnPlayBackStarted        = CBOnPlayBackStarted;
    pAddonControl->CBOnPlayBackEnded          = CBOnPlayBackEnded;
    pAddonControl->CBOnPlayBackStopped        = CBOnPlayBackStopped;
    pAddonControl->CBOnPlayBackPaused         = CBOnPlayBackPaused;
    pAddonControl->CBOnPlayBackResumed        = CBOnPlayBackResumed;
    pAddonControl->CBOnQueueNextItem          = CBOnQueueNextItem;
    pAddonControl->CBOnPlayBackSpeedChanged   = CBOnPlayBackSpeedChanged;
    pAddonControl->CBOnPlayBackSeek           = CBOnPlayBackSeek;
    pAddonControl->CBOnPlayBackSeekChapter    = CBOnPlayBackSeekChapter;
  }
  HANDLE_ADDON_EXCEPTION
}

bool CPlayerCB_AddonPlayer::PlayFile(void *addonData, PLAYERHANDLE handle, const char* item, bool windowed)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle || !item)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', handle='%p', item='%p')",
                                        __FUNCTION__, helper, handle, item);

    return static_cast<CAddonPlayerControl*>(handle)->PlayFile(item, windowed);
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

bool CPlayerCB_AddonPlayer::PlayFileItem(void *addonData, PLAYERHANDLE handle, const GUILIB::V2::GUIHANDLE listitem, bool windowed)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle || !listitem)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', handle='%p', listitem='%p')",
                                        __FUNCTION__, helper, handle, listitem);

    return static_cast<CAddonPlayerControl*>(handle)->PlayFileItem(static_cast<const CFileItem*>(listitem), windowed);
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

bool CPlayerCB_AddonPlayer::PlayList(void *addonData, PLAYERHANDLE handle, const PLAYERHANDLE list, int playListId, bool windowed, int startpos)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle || !list)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', handle='%p', list='%p')",
                                        __FUNCTION__, helper, handle, list);

    return static_cast<CAddonPlayerControl*>(handle)->PlayList(static_cast<const PLAYLIST::CPlayList*>(list), playListId, windowed, startpos);
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

void CPlayerCB_AddonPlayer::Stop(void *addonData, PLAYERHANDLE handle)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);

    static_cast<CAddonPlayerControl*>(handle)->Stop();
  }
  HANDLE_ADDON_EXCEPTION
}

void CPlayerCB_AddonPlayer::Pause(void *addonData, PLAYERHANDLE handle)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);

    static_cast<CAddonPlayerControl*>(handle)->Pause();
  }
  HANDLE_ADDON_EXCEPTION
}

void CPlayerCB_AddonPlayer::PlayNext(void *addonData, PLAYERHANDLE handle)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);

    static_cast<CAddonPlayerControl*>(handle)->PlayNext();
  }
  HANDLE_ADDON_EXCEPTION
}

void CPlayerCB_AddonPlayer::PlayPrevious(void *addonData, PLAYERHANDLE handle)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);

    static_cast<CAddonPlayerControl*>(handle)->PlayPrevious();
  }
  HANDLE_ADDON_EXCEPTION
}

void CPlayerCB_AddonPlayer::PlaySelected(void *addonData, PLAYERHANDLE handle, int selected)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);

    static_cast<CAddonPlayerControl*>(handle)->PlaySelected(selected);
  }
  HANDLE_ADDON_EXCEPTION
}

bool CPlayerCB_AddonPlayer::IsPlaying(void *addonData, PLAYERHANDLE handle)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);

    return static_cast<CAddonPlayerControl*>(handle)->IsPlaying();
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

bool CPlayerCB_AddonPlayer::IsPlayingAudio(void *addonData, PLAYERHANDLE handle)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);

    return static_cast<CAddonPlayerControl*>(handle)->IsPlayingAudio();
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

bool CPlayerCB_AddonPlayer::IsPlayingVideo(void *addonData, PLAYERHANDLE handle)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);

    return static_cast<CAddonPlayerControl*>(handle)->IsPlayingVideo();
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

bool CPlayerCB_AddonPlayer::IsPlayingRDS(void *addonData, PLAYERHANDLE handle)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);

    return static_cast<CAddonPlayerControl*>(handle)->IsPlayingRDS();
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

bool CPlayerCB_AddonPlayer::GetPlayingFile(void *addonData, PLAYERHANDLE handle, char& file, unsigned int& iMaxStringSize)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);

    std::string fileName = static_cast<CAddonPlayerControl*>(handle)->GetPlayingFile();
    strncpy(&file, fileName.c_str(), iMaxStringSize);
    iMaxStringSize = fileName.length();
    return (iMaxStringSize != 0);
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

double CPlayerCB_AddonPlayer::GetTotalTime(void *addonData, PLAYERHANDLE handle)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);

    return static_cast<CAddonPlayerControl*>(handle)->GetTotalTime();
  }
  HANDLE_ADDON_EXCEPTION

  return 0.0;
}

double CPlayerCB_AddonPlayer::GetTime(void *addonData, PLAYERHANDLE handle)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);

    return static_cast<CAddonPlayerControl*>(handle)->GetTime();
  }
  HANDLE_ADDON_EXCEPTION

  return 0.0;
}

void CPlayerCB_AddonPlayer::SeekTime(void *addonData, PLAYERHANDLE handle, double seekTime)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);

    static_cast<CAddonPlayerControl*>(handle)->SeekTime(seekTime);
  }
  HANDLE_ADDON_EXCEPTION
}

bool CPlayerCB_AddonPlayer::GetAvailableAudioStreams(void *addonData, PLAYERHANDLE handle, char**& streams, unsigned int& entries)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);

    std::vector<std::string> streamsInt = static_cast<CAddonPlayerControl*>(handle)->GetAvailableAudioStreams();
    if (!streamsInt.empty())
    {
      entries = streamsInt.size();
      streams = (char**)malloc(entries*sizeof(char*));
      for (unsigned int i = 0; i < entries; ++i)
        streams[i] = strdup(streamsInt[i].c_str());

      return true;
    }
    else
      entries = 0;
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

void CPlayerCB_AddonPlayer::SetAudioStream(void *addonData, PLAYERHANDLE handle, int iStream)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);

    static_cast<CAddonPlayerControl*>(handle)->SetAudioStream(iStream);
  }
  HANDLE_ADDON_EXCEPTION
}

bool CPlayerCB_AddonPlayer::GetAvailableSubtitleStreams(void *addonData, PLAYERHANDLE handle, char**& streams, unsigned int& entries)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);

    std::vector<std::string> streamsInt = static_cast<CAddonPlayerControl*>(handle)->GetAvailableSubtitleStreams();
    if (!streamsInt.empty())
    {
      entries = streamsInt.size();
      streams = (char**)malloc(entries*sizeof(char*));
      for (unsigned int i = 0; i < entries; ++i)
        streams[i] = strdup(streamsInt[i].c_str());

      return true;
    }
    else
      entries = 0;
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

void CPlayerCB_AddonPlayer::SetSubtitleStream(void *addonData, PLAYERHANDLE handle, int iStream)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);

    static_cast<CAddonPlayerControl*>(handle)->SetSubtitleStream(iStream);
  }
  HANDLE_ADDON_EXCEPTION
}

void CPlayerCB_AddonPlayer::ShowSubtitles(void *addonData, PLAYERHANDLE handle, bool bVisible)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);

    static_cast<CAddonPlayerControl*>(handle)->ShowSubtitles(bVisible);
  }
  HANDLE_ADDON_EXCEPTION
}

bool CPlayerCB_AddonPlayer::GetCurrentSubtitleName(void *addonData, PLAYERHANDLE handle, char& name, unsigned int& iMaxStringSize)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);

    std::string strName = static_cast<CAddonPlayerControl*>(handle)->GetCurrentSubtitleName();
    strncpy(&name, strName.c_str(), iMaxStringSize);
    iMaxStringSize = strName.length();

    return (iMaxStringSize != 0);
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

void CPlayerCB_AddonPlayer::AddSubtitle(void *addonData, PLAYERHANDLE handle, const char* strSubPath)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);

    static_cast<CAddonPlayerControl*>(handle)->AddSubtitle(strSubPath);
  }
  HANDLE_ADDON_EXCEPTION
}

void CPlayerCB_AddonPlayer::ClearList(char**& path, unsigned int entries)
{
  try
  {
    if (path)
    {
      for (unsigned int i = 0; i < entries; ++i)
      {
        if (path[i])
          free(path[i]);
      }
      free(path);
    }
    else
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid add-on data for path", __FUNCTION__);
  }
  HANDLE_ADDON_EXCEPTION
}

/*\_____________________________________________________________________________
\*/

CAddonPlayerControl::CAddonPlayerControl(ADDON::CAddon* addon)
  : CBOnPlayBackStarted(nullptr),
    CBOnPlayBackEnded(nullptr),
    CBOnPlayBackStopped(nullptr),
    CBOnPlayBackPaused(nullptr),
    CBOnPlayBackResumed(nullptr),
    CBOnQueueNextItem(nullptr),
    CBOnPlayBackSpeedChanged(nullptr),
    CBOnPlayBackSeek(nullptr),
    CBOnPlayBackSeekChapter(nullptr),
    m_cbhdl(nullptr),
    m_addon(addon),
    m_playList(PLAYLIST_MUSIC)
{
  ADDON::CBinaryAddonManager::GetInstance().RegisterPlayerCallBack(this);
}

CAddonPlayerControl::~CAddonPlayerControl()
{
  ADDON::CBinaryAddonManager::GetInstance().UnregisterPlayerCallBack(this);
}

inline bool CAddonPlayerControl::PlayFile(std::string item, bool windowed)
{
  // set fullscreen or windowed
  CMediaSettings::GetInstance().SetVideoStartWindowed(windowed);
  CApplicationMessenger::GetInstance().PostMsg(TMSG_MEDIA_PLAY, 0, 0, static_cast<void*>(new CFileItem(item, false)));
}

inline bool CAddonPlayerControl::PlayFileItem(const CFileItem* item, bool windowed)
{
  // set fullscreen or windowed
  CMediaSettings::GetInstance().SetVideoStartWindowed(windowed);
  CApplicationMessenger::GetInstance().PostMsg(TMSG_MEDIA_PLAY, 0, 0, static_cast<void*>(new CFileItem(*item)));
}

inline bool CAddonPlayerControl::PlayList(const PLAYLIST::CPlayList* playlist, int playListId, bool windowed, int startpos)
{
  if (playlist != nullptr)
  {
    // set fullscreen or windowed
    CMediaSettings::GetInstance().SetVideoStartWindowed(windowed);

    // play playlist (a playlist from playlistplayer.cpp)
    m_playList = playListId;
    g_playlistPlayer.SetCurrentPlaylist(m_playList);
    if (startpos > -1)
      g_playlistPlayer.SetCurrentSong(startpos);
    CApplicationMessenger::GetInstance().SendMsg(TMSG_PLAYLISTPLAYER_PLAY, startpos);
    return true;
  }
  return false;
}

inline void CAddonPlayerControl::Stop()
{
  CApplicationMessenger::GetInstance().SendMsg(TMSG_MEDIA_STOP);
}

inline void CAddonPlayerControl::Pause()
{
  CApplicationMessenger::GetInstance().SendMsg(TMSG_MEDIA_PAUSE);
}

inline void CAddonPlayerControl::PlayNext()
{
  CApplicationMessenger::GetInstance().SendMsg(TMSG_PLAYLISTPLAYER_NEXT);
}

inline void CAddonPlayerControl::PlayPrevious()
{
  CApplicationMessenger::GetInstance().SendMsg(TMSG_PLAYLISTPLAYER_PREV);
}

inline void CAddonPlayerControl::PlaySelected(int selected)
{
  if (g_playlistPlayer.GetCurrentPlaylist() != m_playList)
  {
    g_playlistPlayer.SetCurrentPlaylist(m_playList);
  }
  g_playlistPlayer.SetCurrentSong(selected);

  CApplicationMessenger::GetInstance().SendMsg(TMSG_PLAYLISTPLAYER_PLAY, selected);
}

void CAddonPlayerControl::OnPlayBackEnded()
{
  try
  {
    CThread::SetCrashProtection(m_addon);
    CSingleLock lock(m_playStateMutex);
    if (CBOnPlayBackEnded)
      CBOnPlayBackEnded(m_cbhdl);
    CThread::SetCrashProtection(nullptr);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonPlayerControl::OnPlayBackStarted()
{
  try
  {
    CThread::SetCrashProtection(m_addon);
    CSingleLock lock(m_playStateMutex);
    if (CBOnPlayBackStarted)
      CBOnPlayBackStarted(m_cbhdl);
    CThread::SetCrashProtection(nullptr);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonPlayerControl::OnPlayBackPaused()
{
  try
  {
    CThread::SetCrashProtection(m_addon);
    CSingleLock lock(m_playStateMutex);
    if (CBOnPlayBackPaused)
      CBOnPlayBackPaused(m_cbhdl);
    CThread::SetCrashProtection(nullptr);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonPlayerControl::OnPlayBackResumed()
{
  try
  {
    CThread::SetCrashProtection(m_addon);
    CSingleLock lock(m_playStateMutex);
    if (CBOnPlayBackResumed)
      CBOnPlayBackResumed(m_cbhdl);
    CThread::SetCrashProtection(nullptr);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonPlayerControl::OnPlayBackStopped()
{
  try
  {
    CThread::SetCrashProtection(m_addon);
    CSingleLock lock(m_playStateMutex);
    if (CBOnPlayBackStopped)
      CBOnPlayBackStopped(m_cbhdl);
    CThread::SetCrashProtection(nullptr);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonPlayerControl::OnQueueNextItem()
{
  try
  {
    CThread::SetCrashProtection(m_addon);
    CSingleLock lock(m_playStateMutex);
    if (CBOnQueueNextItem)
      CBOnQueueNextItem(m_cbhdl);
    CThread::SetCrashProtection(nullptr);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonPlayerControl::OnPlayBackSeek(int iTime, int seekOffset)
{
  try
  {
    CThread::SetCrashProtection(m_addon);
    CSingleLock lock(m_playStateMutex);
    if (CBOnPlayBackSeek)
      CBOnPlayBackSeek(m_cbhdl, iTime, seekOffset);
    CThread::SetCrashProtection(nullptr);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonPlayerControl::OnPlayBackSeekChapter(int iChapter)
{
  try
  {
    CThread::SetCrashProtection(m_addon);
    CSingleLock lock(m_playStateMutex);
    if (CBOnPlayBackSeekChapter)
      CBOnPlayBackSeekChapter(m_cbhdl, iChapter);
    CThread::SetCrashProtection(nullptr);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonPlayerControl::OnPlayBackSpeedChanged(int iSpeed)
{
  try
  {
    CThread::SetCrashProtection(m_addon);
    CSingleLock lock(m_playStateMutex);
    if (CBOnPlayBackSpeedChanged)
      CBOnPlayBackSpeedChanged(m_cbhdl, iSpeed);
    CThread::SetCrashProtection(nullptr);
  }
  HANDLE_ADDON_EXCEPTION
}

inline bool CAddonPlayerControl::IsPlaying()
{
  return g_application.m_pPlayer->IsPlaying();
}

inline bool CAddonPlayerControl::IsPlayingAudio()
{
  return g_application.m_pPlayer->IsPlayingAudio();
}

inline bool CAddonPlayerControl::IsPlayingVideo()
{
  return g_application.m_pPlayer->IsPlayingVideo();
}

inline bool CAddonPlayerControl::IsPlayingRDS()
{
  return g_application.m_pPlayer->IsPlayingRDS();
}

inline std::string CAddonPlayerControl::GetPlayingFile()
{
  if (!g_application.m_pPlayer->IsPlaying())
    throw ADDON::UnimplementedException("CAddonPlayerControl::GetPlayingFile", "Kodi is not playing any media file");

  return g_application.CurrentFile();
}

inline double CAddonPlayerControl::GetTotalTime()
{
  if (!g_application.m_pPlayer->IsPlaying())
    throw ADDON::UnimplementedException("CAddonPlayerControl::GetTotalTime", "Kodi is not playing any media file");

  return g_application.GetTotalTime();
}

inline double CAddonPlayerControl::GetTime()
{
  if (!g_application.m_pPlayer->IsPlaying())
    throw ADDON::UnimplementedException("CAddonPlayerControl::GetTime", "Kodi is not playing any media file");

  return g_application.GetTime();
}

inline void CAddonPlayerControl::SeekTime(double seekTime)
{
  if (!g_application.m_pPlayer->IsPlaying())
    throw ADDON::UnimplementedException("CAddonPlayerControl::SeekTime", "Kodi is not playing any media file");

  g_application.SeekTime(seekTime);
}

inline std::vector<std::string> CAddonPlayerControl::GetAvailableAudioStreams()
{
  if (g_application.m_pPlayer->HasPlayer())
  {
    int streamCount = g_application.m_pPlayer->GetAudioStreamCount();
    std::vector<std::string> ret(streamCount);
    for (int iStream = 0; iStream < streamCount; iStream++)
    {
      SPlayerAudioStreamInfo info;
      g_application.m_pPlayer->GetAudioStreamInfo(iStream, info);

      if (info.language.length() > 0)
        ret[iStream] = info.language;
      else
        ret[iStream] = info.name;
    }
    return ret;
  }

  return std::vector<std::string>();
}

inline void CAddonPlayerControl::SetAudioStream(int iStream)
{
  if (g_application.m_pPlayer->HasPlayer())
  {
    int streamCount = g_application.m_pPlayer->GetAudioStreamCount();
    if (iStream < streamCount)
      g_application.m_pPlayer->SetAudioStream(iStream);
  }
}

inline std::vector<std::string> CAddonPlayerControl::GetAvailableSubtitleStreams()
{
  if (g_application.m_pPlayer->HasPlayer())
  {
    int subtitleCount = g_application.m_pPlayer->GetSubtitleCount();
    std::vector<std::string> ret(subtitleCount);
    for (int iStream = 0; iStream < subtitleCount; iStream++)
    {
      SPlayerSubtitleStreamInfo info;
      g_application.m_pPlayer->GetSubtitleStreamInfo(iStream, info);

      if (!info.language.empty())
        ret[iStream] = info.language;
      else
        ret[iStream] = info.name;
    }
    return ret;
  }

  return std::vector<std::string>();
}

inline void CAddonPlayerControl::SetSubtitleStream(int iStream)
{
  if (g_application.m_pPlayer->HasPlayer())
  {
    int streamCount = g_application.m_pPlayer->GetSubtitleCount();
    if(iStream < streamCount)
    {
      g_application.m_pPlayer->SetSubtitle(iStream);
      g_application.m_pPlayer->SetSubtitleVisible(true);
    }
  }
}

inline void CAddonPlayerControl::ShowSubtitles(bool bVisible)
{
  if (g_application.m_pPlayer->HasPlayer())
  {
    g_application.m_pPlayer->SetSubtitleVisible(bVisible);
  }
}

inline std::string CAddonPlayerControl::GetCurrentSubtitleName()
{
  if (g_application.m_pPlayer->HasPlayer())
  {
    SPlayerSubtitleStreamInfo info;
    g_application.m_pPlayer->GetSubtitleStreamInfo(g_application.m_pPlayer->GetSubtitle(), info);

    if (!info.language.empty())
      return info.language;
    else
      return info.name;
  }

  return "";
}

inline void CAddonPlayerControl::AddSubtitle(const std::string& strSubPath)
{
  if (g_application.m_pPlayer->HasPlayer())
  {
    g_application.m_pPlayer->AddSubtitle(strSubPath);
  }
}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace PlayerLIB */
