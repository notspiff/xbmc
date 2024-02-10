/*
 *  Copyright (C) 2005-2020 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "playlists/PlayListFileItemClassify.h"

#include "FileItem.h"
#include "playlists/PlayListFactory.h"
#include "utils/URIUtils.h"
#include "utils/Variant.h"

bool IsLibraryFolder(const CFileItem& item)
{
  if (item.HasProperty("library.filter") && item.GetProperty("library.filter").asBoolean())
    return true;

  return URIUtils::IsLibraryFolder(item.GetPath());
}

bool IsPlayList(const CFileItem& item)
{
  return PLAYLIST::CPlayListFactory::IsPlaylist(item);
}

bool IsSmartPlayList(const CFileItem& item)
{
  if (item.HasProperty("library.smartplaylist") && item.GetProperty("library.smartplaylist").asBoolean())
    return true;

  return URIUtils::HasExtension(item.GetPath(), ".xsp");
}
