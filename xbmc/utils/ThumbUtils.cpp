/*
 *  Copyright (C) 2024 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "ThumbUtils.h"

#include "FileItem.h"
#include "FileItemList.h"
#include "ServiceBroker.h"
#include "filesystem/Directory.h"
#include "filesystem/File.h"
#include "filesystem/StackDirectory.h"
#include "music/MusicFileItemClassify.h"
#include "network/NetworkFileItemClassify.h"
#include "playlists/PlayListFileItemClassify.h"
#include "pvr/channels/PVRChannel.h"
#include "settings/AdvancedSettings.h"
#include "settings/SettingsComponent.h"
#include "utils/FileExtensionProvider.h"
#include "utils/StringUtils.h"
#include "utils/URIUtils.h"
#include "video/VideoFileItemClassify.h"
#include "video/VideoInfoTag.h"

using namespace XFILE;

namespace KODI::THUMBS
{

void FillInDefaultIcon(CFileItem& item)
{
  if (URIUtils::IsPVRGuideItem(item.GetPath()))
  {
    // epg items never have a default icon. no need to execute this expensive method.
    // when filling epg grid window, easily tens of thousands of epg items are processed.
    return;
  }

  //CLog::Log(LOGINFO, "FillInDefaultIcon({})", pItem->GetLabel());
  // find the default icon for a file or folder item
  // for files this can be the (depending on the file type)
  //   default picture for photo's
  //   default picture for songs
  //   default picture for videos
  //   default picture for shortcuts
  //   default picture for playlists
  //
  // for folders
  //   for .. folders the default picture for parent folder
  //   for other folders the defaultFolder.png

  if (item.GetArt("icon").empty())
  {
    if (!item.m_bIsFolder)
    {
      /* To reduce the average runtime of this code, this list should
       * be ordered with most frequently seen types first.  Also bear
       * in mind the complexity of the code behind the check in the
       * case of IsWhatever() returns false.
       */
      if (item.IsPVRChannel())
      {
        if (item.GetPVRChannelInfoTag()->IsRadio())
          item.SetArt("icon", "DefaultMusicSongs.png");
        else
          item.SetArt("icon", "DefaultTVShows.png");
      }
      else if (item.IsLiveTV())
      {
        // Live TV Channel
        item.SetArt("icon", "DefaultTVShows.png");
      }
      else if (URIUtils::IsArchive(item.GetPath()) )
      { // archive
        item.SetArt("icon", "DefaultFile.png");
      }
      else if (item.IsUsablePVRRecording())
      {
        // PVR recording
        item.SetArt("icon", "DefaultVideo.png");
      }
      else if (item.IsDeletedPVRRecording())
      {
        // PVR deleted recording
        item.SetArt("icon", "DefaultVideoDeleted.png");
      }
      else if (PLAYLIST::IsPlayList(item) || PLAYLIST::IsSmartPlayList(item))
      {
        item.SetArt("icon", "DefaultPlaylist.png");
      }
      else if (MUSIC::IsAudio(item))
      {
        // audio
        item.SetArt("icon", "DefaultAudio.png");
      }
      else if (VIDEO::IsVideo(item))
      {
        // video
        item.SetArt("icon", "DefaultVideo.png");
      }
      else if (item.IsPVRTimer())
      {
        item.SetArt("icon", "DefaultVideo.png");
      }
      else if (item.IsPicture())
      {
        // picture
        item.SetArt("icon", "DefaultPicture.png");
      }
      else if (item.IsPythonScript())
      {
        item.SetArt("icon", "DefaultScript.png");
      }
      else if (item.IsFavourite())
      {
        item.SetArt("icon", "DefaultFavourites.png");
      }
      else
      {
        // default icon for unknown file type
        item.SetArt("icon", "DefaultFile.png");
      }
    }
    else
    {
      if (PLAYLIST::IsPlayList(item) || PLAYLIST::IsSmartPlayList(item))
      {
        item.SetArt("icon", "DefaultPlaylist.png");
      }
      else if (item.IsParentFolder())
      {
        item.SetArt("icon", "DefaultFolderBack.png");
      }
      else
      {
        item.SetArt("icon", "DefaultFolder.png");
      }
    }
  }
  // Set the icon overlays (if applicable)
  if (!item.HasOverlay() && !item.HasProperty("icon_never_overlay"))
  {
    if (URIUtils::IsInRAR(item.GetPath()))
      item.SetOverlayImage(CGUIListItem::ICON_OVERLAY_RAR);
    else if (URIUtils::IsInZIP(item.GetPath()))
      item.SetOverlayImage(CGUIListItem::ICON_OVERLAY_ZIP);
  }
}

std::string GetLocalFanart(const CFileItem& item)
{
  if (VIDEO::IsVideoDb(item))
  {
    if (!item.HasVideoInfoTag())
      return ""; // nothing can be done
    CFileItem dbItem(item.m_bIsFolder ? item.GetVideoInfoTag()->m_strPath : item.GetVideoInfoTag()->m_strFileNameAndPath, item.m_bIsFolder);
    return GetLocalFanart(dbItem);
  }

  std::string strFile2;
  std::string strFile = item.GetPath();
  if (item.IsStack())
  {
    std::string strPath;
    URIUtils::GetParentPath(item.GetPath(), strPath);
    CStackDirectory dir;
    std::string strPath2;
    strPath2 = dir.GetStackedTitlePath(strFile);
    strFile = URIUtils::AddFileToFolder(strPath, URIUtils::GetFileName(strPath2));
    CFileItem fan_item(dir.GetFirstStackedFile(item.GetPath()),false);
    std::string strTBNFile(URIUtils::ReplaceExtension(GetTBNFile(fan_item), "-fanart"));
    strFile2 = URIUtils::AddFileToFolder(strPath, URIUtils::GetFileName(strTBNFile));
  }
  if (URIUtils::IsInRAR(strFile) || URIUtils::IsInZIP(strFile))
  {
    std::string strPath = URIUtils::GetDirectory(strFile);
    std::string strParent;
    URIUtils::GetParentPath(strPath, strParent);
    strFile = URIUtils::AddFileToFolder(strParent, URIUtils::GetFileName(item.GetPath()));
  }

  // no local fanart available for these
  if (NETWORK::IsInternetStream(item) || URIUtils::IsUPnP(strFile) ||
      URIUtils::IsBluray(strFile) || item.IsLiveTV() || item.IsPlugin() || item.IsAddonsPath() || item.IsDVD() ||
      (URIUtils::IsFTP(strFile) &&
       !CServiceBroker::GetSettingsComponent()->GetAdvancedSettings()->m_bFTPThumbs) ||
      item.GetPath().empty())
    return "";

  std::string strDir = URIUtils::GetDirectory(strFile);

  if (strDir.empty())
    return "";

  CFileItemList items;
  CDirectory::GetDirectory(strDir, items, CServiceBroker::GetFileExtensionProvider().GetPictureExtensions(), DIR_FLAG_NO_FILE_DIRS | DIR_FLAG_READ_CACHE | DIR_FLAG_NO_FILE_INFO);
  if (item.IsOpticalMediaFile())
  { // grab from the optical media parent folder as well
    CFileItemList moreItems;
    CDirectory::GetDirectory(item.GetLocalMetadataPath(), moreItems, CServiceBroker::GetFileExtensionProvider().GetPictureExtensions(), DIR_FLAG_NO_FILE_DIRS | DIR_FLAG_READ_CACHE | DIR_FLAG_NO_FILE_INFO);
    items.Append(moreItems);
  }

  std::vector<std::string> fanarts = { "fanart" };

  strFile = URIUtils::ReplaceExtension(strFile, "-fanart");
  fanarts.insert(item.m_bIsFolder ? fanarts.end() : fanarts.begin(), URIUtils::GetFileName(strFile));

  if (!strFile2.empty())
    fanarts.insert(item.m_bIsFolder ? fanarts.end() : fanarts.begin(), URIUtils::GetFileName(strFile2));

  for (const auto& fanart : fanarts)
  {
    for (const auto& item : items)
    {
      std::string strCandidate = URIUtils::GetFileName(item->GetPath());
      URIUtils::RemoveExtension(strCandidate);
      std::string strFanart = fanart;
      URIUtils::RemoveExtension(strFanart);
      if (StringUtils::EqualsNoCase(strCandidate, strFanart))
        return item->GetPath();
    }
  }

  return "";
}

// Gets the .tbn filename from a file or folder name.
// <filename>.ext -> <filename>.tbn
// <foldername>/ -> <foldername>.tbn
std::string GetTBNFile(const CFileItem& item)
{
  std::string thumbFile;
  std::string strFile = item.GetPath();

  if (item.IsStack())
  {
    std::string strPath, strReturn;
    URIUtils::GetParentPath(item.GetPath(), strPath);
    CFileItem item(CStackDirectory::GetFirstStackedFile(strFile),false);
    std::string strTBNFile = GetTBNFile(item);
    strReturn = URIUtils::AddFileToFolder(strPath, URIUtils::GetFileName(strTBNFile));
    if (CFile::Exists(strReturn))
      return strReturn;

    strFile = URIUtils::AddFileToFolder(strPath,URIUtils::GetFileName(CStackDirectory::GetStackedTitlePath(strFile)));
  }

  if (URIUtils::IsInRAR(strFile) || URIUtils::IsInZIP(strFile))
  {
    std::string strPath = URIUtils::GetDirectory(strFile);
    std::string strParent;
    URIUtils::GetParentPath(strPath, strParent);
    strFile = URIUtils::AddFileToFolder(strParent, URIUtils::GetFileName(item.GetPath()));
  }

  CURL url(strFile);
  strFile = url.GetFileName();

  if (item.m_bIsFolder && !item.IsFileFolder())
    URIUtils::RemoveSlashAtEnd(strFile);

  if (!strFile.empty())
  {
    if (item.m_bIsFolder && !item.IsFileFolder())
      thumbFile = strFile + ".tbn"; // folder, so just add ".tbn"
    else
      thumbFile = URIUtils::ReplaceExtension(strFile, ".tbn");
    url.SetFileName(thumbFile);
    thumbFile = url.Get();
  }
  return thumbFile;
}

}
