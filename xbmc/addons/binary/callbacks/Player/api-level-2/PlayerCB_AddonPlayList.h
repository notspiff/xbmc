#pragma once
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

#include "cores/IPlayerCallback.h"

#include "addons/kodi-addon-dev-kit/kodi/player.api2/PlayerLib.h"

class CFileItem;

namespace PlayerLIB
{
namespace V2
{
extern "C"
{

  class CPlayerCB_AddonPlayList
  {
  public:
    static void Init(CB_PlayerLib *callbacks);

    static PLAYERHANDLE New(void *addonData, int playList);
    static void Delete(void *addonData, PLAYERHANDLE handle);

    static bool LoadPlaylist(void* addonData, PLAYERHANDLE handle, const char* filename, int playList);
    static void AddItemURL(void* addonData, PLAYERHANDLE handle, const char* url, int index);
    static void AddItemList(void* addonData, PLAYERHANDLE handle, const GUILIB::V2::GUIHANDLE listitem, int index);
    static void RemoveItem(void* addonData, PLAYERHANDLE handle, const char* url);
    static void ClearList(void* addonData, PLAYERHANDLE handle);
    static int GetListSize(void* addonData, PLAYERHANDLE handle);
    static int GetListPosition(void* addonData, PLAYERHANDLE handle);
    static void Shuffle(void* addonData, PLAYERHANDLE handle, bool shuffle);
  };

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace PlayerLIB */
