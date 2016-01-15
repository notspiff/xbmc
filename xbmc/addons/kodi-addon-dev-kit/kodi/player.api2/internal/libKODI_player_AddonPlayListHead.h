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

#include "kodi/gui.api2/definations.h"

namespace PlayerLIB
{
namespace V2
{
extern "C"
{

  typedef PLAYERHANDLE AddonPlayList_New(
        void*             addonData,
        int               playlist);

  typedef void AddonPlayList_Delete(
        void*             addonData,
        PLAYERHANDLE      handle);

  typedef bool AddonPlayList_LoadPlaylist(
        void*             addonData,
        PLAYERHANDLE      handle,
        const char*       filename,
        int               playList);

  typedef void AddonPlayList_AddItemURL(
        void*             addonData,
        PLAYERHANDLE      handle,
        const char*       url,
        int               index);

  typedef void AddonPlayList_AddItemList(
        void*             addonData,
        PLAYERHANDLE      handle,
        const GUILIB::V2::GUIHANDLE listitem,
        int               index);

  typedef void AddonPlayList_RemoveItem(
        void*             addonData,
        PLAYERHANDLE      handle,
        const char*       url);

  typedef void AddonPlayList_ClearList(
        void*             addonData,
        PLAYERHANDLE      handle);

  typedef int AddonPlayList_GetListSize(
        void*             addonData,
        PLAYERHANDLE      handle);

  typedef int AddonPlayList_GetListPosition(
        void*             addonData,
        PLAYERHANDLE      handle);

  typedef void AddonPlayList_Shuffle(
        void*             addonData,
        PLAYERHANDLE      handle,
        bool              shuffle);

  typedef struct CB_PlayerLib_AddonPlayList
  {
    AddonPlayList_New*                      New;
    AddonPlayList_Delete*                   Delete;
    AddonPlayList_LoadPlaylist*             LoadPlaylist;
    AddonPlayList_AddItemURL*               AddItemURL;
    AddonPlayList_AddItemList*              AddItemList;
    AddonPlayList_RemoveItem*               RemoveItem;
    AddonPlayList_ClearList*                ClearList;
    AddonPlayList_GetListSize*              GetListSize;
    AddonPlayList_GetListPosition*          GetListPosition;
    AddonPlayList_Shuffle*                  Shuffle;
  } CB_PlayerLib_AddonPlayList;

  #define IMPL_ADDON_PLAYLIST                                                  \
    public:                                                                    \
      const GUIHANDLE GetListHandle() const                                    \
      {                                                                        \
        return m_ControlHandle;                                                \
      }                                                                        \
      const AddonPlayListType GetListType() const                              \
      {                                                                        \
        return m_playlist;                                                     \
      }                                                                        \
    private:                                                                   \
      PLAYERHANDLE      m_ControlHandle;                                       \
      ADDON::AddonCB*   m_Handle;                                              \
      CB_PlayerLib*     m_cb;                                                  \
      AddonPlayListType m_playlist;

}; /* extern "C" */
}; /* V2 */
}; /* PlayerLIB */
