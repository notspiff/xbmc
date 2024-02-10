/*
 *  Copyright (C) 2005-2020 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "games/GameFileItemClassify.h"

#include "FileItem.h"
#include "games/GameUtils.h"

using namespace KODI::GAME;

bool IsGame(const CFileItem& item)
{
  if (item.HasGameInfoTag())
    return true;

  if (item.HasVideoInfoTag())
    return false;

  if (item.HasMusicInfoTag())
    return false;

  if (item.HasPictureInfoTag())
    return false;

  if (item.IsPVR())
    return false;

  if (item.HasAddonInfo())
    return CGameUtils::IsStandaloneGame(std::const_pointer_cast<ADDON::IAddon>(item.GetAddonInfo()));

  return CGameUtils::HasGameExtension(item.GetPath());
}
