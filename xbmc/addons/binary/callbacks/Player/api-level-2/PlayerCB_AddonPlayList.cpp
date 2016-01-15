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
#include "playlists/PlayList.h"
#include "playlists/PlayListFactory.h"
#include "utils/URIUtils.h"

#include "AddonCallbacksPlayer.h"
#include "PlayerCB_AddonPlayList.h"

using namespace ADDON;
using namespace PLAYLIST;

namespace PlayerLIB
{
namespace V2
{
extern "C"
{

void CPlayerCB_AddonPlayList::Init(CB_PlayerLib *callbacks)
{
  callbacks->AddonPlayList.New                          = CPlayerCB_AddonPlayList::New;
  callbacks->AddonPlayList.Delete                       = CPlayerCB_AddonPlayList::Delete;
  callbacks->AddonPlayList.LoadPlaylist                 = CPlayerCB_AddonPlayList::LoadPlaylist;
  callbacks->AddonPlayList.AddItemURL                   = CPlayerCB_AddonPlayList::AddItemURL;
  callbacks->AddonPlayList.AddItemList                  = CPlayerCB_AddonPlayList::AddItemList;
  callbacks->AddonPlayList.RemoveItem                   = CPlayerCB_AddonPlayList::RemoveItem;
  callbacks->AddonPlayList.ClearList                    = CPlayerCB_AddonPlayList::ClearList;
  callbacks->AddonPlayList.GetListSize                  = CPlayerCB_AddonPlayList::GetListSize;
  callbacks->AddonPlayList.GetListPosition              = CPlayerCB_AddonPlayList::GetListPosition;
  callbacks->AddonPlayList.Shuffle                      = CPlayerCB_AddonPlayList::Shuffle;
}

PLAYERHANDLE CPlayerCB_AddonPlayList::New(void *addonData, int playList)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks*>(addonData);
    if (!helper)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayList - %s - invalid data (addonData='%p')",
                                        __FUNCTION__, helper);

      // we do not create our own playlist, just using the ones from playlistplayer
      if (playList != PLAYLIST_MUSIC && playList != PLAYLIST_VIDEO && playList != PLAYLIST_PICTURE)
        throw ADDON::WrongValueException("CPlayerCB_AddonPlayList - %s: %s/%s - PlayList does not exist",
                                           __FUNCTION__,
                                           TranslateType(helper->GetAddon()->Type()).c_str(),
                                           helper->GetAddon()->Name().c_str());

    return &g_playlistPlayer.GetPlaylist(playList);;
  }
  HANDLE_ADDON_EXCEPTION

  return nullptr;
}

void CPlayerCB_AddonPlayList::Delete(void *addonData, PLAYERHANDLE handle)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayList - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);
    // Nothing to do, present if needed in future (to prevent API change)
  }
  HANDLE_ADDON_EXCEPTION
}

bool CPlayerCB_AddonPlayList::LoadPlaylist(void* addonData, PLAYERHANDLE handle, const char* filename, int playList)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle || !filename)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayList - %s - invalid data (addonData='%p', handle='%p', filename='%p')",
                                        __FUNCTION__, helper, handle, filename);

    CFileItem item(filename);
    item.SetPath(filename);

    if (item.IsPlayList())
    {
      // load playlist and copy all items to existing playlist

      // load a playlist like .m3u, .pls
      // first get correct factory to load playlist
      std::unique_ptr<CPlayList> pPlayList(CPlayListFactory::Create(item));
      if (pPlayList.get() != nullptr)
      {
        // load it
        if (!pPlayList->Load(item.GetPath()))
        {
          //hmmm unable to load playlist?
          return false;
        }

        // clear current playlist
        g_playlistPlayer.ClearPlaylist(playList);

        // add each item of the playlist to the playlistplayer
        for (int i = 0; i < (int)pPlayList->size(); ++i)
        {
          CFileItemPtr playListItem =(*pPlayList)[i];
          if (playListItem->GetLabel().empty())
            playListItem->SetLabel(URIUtils::GetFileName(playListItem->GetPath()));

          static_cast<PLAYLIST::CPlayList*>(handle)->Add(playListItem);
        }
      }
      return true;
    }
    else
    {
      // filename is not a valid playlist
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayList - %s: %s/%s - Not a valid playlist",
                                         __FUNCTION__,
                                         TranslateType(helper->GetAddon()->Type()).c_str(),
                                         helper->GetAddon()->Name().c_str());
    }
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

void CPlayerCB_AddonPlayList::AddItemURL(void* addonData, PLAYERHANDLE handle, const char* url, int index)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle || !url)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayList - %s - invalid data (addonData='%p', handle='%p', url='%p')",
                                        __FUNCTION__, helper, handle, url);

    CFileItemPtr item(new CFileItem(url, false));
    item->SetLabel(url);

    CFileItemList items;
    items.Add(item);
    static_cast<PLAYLIST::CPlayList*>(handle)->Insert(items, index);
  }
  HANDLE_ADDON_EXCEPTION
}

void CPlayerCB_AddonPlayList::AddItemList(void* addonData, PLAYERHANDLE handle, const GUILIB::V2::GUIHANDLE listitem, int index)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle || !listitem)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayList - %s - invalid data (addonData='%p', handle='%p', listitem='%p')",
                                        __FUNCTION__, helper, handle, listitem);

    CFileItemList items;
    items.Add(std::make_shared<CFileItem>(*static_cast<const CFileItem*>(listitem)));
    static_cast<PLAYLIST::CPlayList*>(handle)->Insert(items, index);
  }
  HANDLE_ADDON_EXCEPTION
}

void CPlayerCB_AddonPlayList::CPlayerCB_AddonPlayList::RemoveItem(void* addonData, PLAYERHANDLE handle, const char* url)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle || !url)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayList - %s - invalid data (addonData='%p', handle='%p', url='%p')",
                                        __FUNCTION__, helper, handle, url);

    static_cast<PLAYLIST::CPlayList*>(handle)->Remove(url);
  }
  HANDLE_ADDON_EXCEPTION
}

void CPlayerCB_AddonPlayList::ClearList(void* addonData, PLAYERHANDLE handle)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayList - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);

    static_cast<PLAYLIST::CPlayList*>(handle)->Clear();
  }
  HANDLE_ADDON_EXCEPTION
}

int CPlayerCB_AddonPlayList::GetListSize(void* addonData, PLAYERHANDLE handle)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayList - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);

    return static_cast<PLAYLIST::CPlayList*>(handle)->size();
  }
  HANDLE_ADDON_EXCEPTION

  return -1;
}

int CPlayerCB_AddonPlayList::GetListPosition(void* addonData, PLAYERHANDLE handle)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayList - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);

    return g_playlistPlayer.GetCurrentSong();
  }
  HANDLE_ADDON_EXCEPTION

  return -1;
}

void CPlayerCB_AddonPlayList::Shuffle(void* addonData, PLAYERHANDLE handle, bool shuffle)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !handle)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayList - %s - invalid data (addonData='%p', handle='%p')",
                                        __FUNCTION__, helper, handle);

    if (shuffle)
      static_cast<PLAYLIST::CPlayList*>(handle)->Shuffle();
    else
      static_cast<PLAYLIST::CPlayList*>(handle)->UnShuffle();
  }
  HANDLE_ADDON_EXCEPTION
}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace PlayerLIB */
