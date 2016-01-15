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

namespace PlayerLIB
{
namespace V2
{
extern "C"
{

  inline CPlayerLib_PlayList::CPlayerLib_PlayList(AddonPlayListType playlist)
   : m_Handle((ADDON::AddonCB*)CGUILib::g_libKODI_Internal->m_Handle),
     m_cb(CPlayerLib::g_libKODI_Internal->m_Callbacks),
     m_ControlHandle(nullptr),
     m_playlist(playlist)
  {
    if (m_Handle && m_cb)
    {
      m_ControlHandle = m_cb->AddonPlayList.New(m_Handle->addonData, m_playlist);
      if (!m_ControlHandle)
        fprintf(stderr, "ERROR: CPlayerLib_PlayList can't create control class from Kodi !!!\n");
    }
  }

  inline CPlayerLib_PlayList::~CPlayerLib_PlayList()
  {
    m_cb->AddonPlayList.Delete(m_Handle->addonData, m_ControlHandle);
  }

  inline AddonPlayListType CPlayerLib_PlayList::GetPlayListType() const
  {
    return m_playlist;
  }

  inline bool CPlayerLib_PlayList::LoadPlaylist(const std::string& filename)
  {
    return m_cb->AddonPlayList.LoadPlaylist(m_Handle->addonData, m_ControlHandle, filename.c_str(), m_playlist);
  }

  inline void CPlayerLib_PlayList::AddItem(const std::string& url, int index)
  {
    m_cb->AddonPlayList.AddItemURL(m_Handle->addonData, m_ControlHandle, url.c_str(), index);
  }

  inline void CPlayerLib_PlayList::AddItem(const CAddonGUIListItem* listitem, int index)
  {
    m_cb->AddonPlayList.AddItemList(m_Handle->addonData, m_ControlHandle, listitem->GetListItemHandle(), index);
  }

  inline void CPlayerLib_PlayList::RemoveItem(const std::string& url)
  {
    m_cb->AddonPlayList.RemoveItem(m_Handle->addonData, m_ControlHandle, url.c_str());
  }

  inline void CPlayerLib_PlayList::ClearList()
  {
    m_cb->AddonPlayList.ClearList(m_Handle->addonData, m_ControlHandle);
  }

  inline int CPlayerLib_PlayList::GetListSize()
  {
    return m_cb->AddonPlayList.GetListSize(m_Handle->addonData, m_ControlHandle);
  }

  inline int CPlayerLib_PlayList::GetListPosition()
  {
    return m_cb->AddonPlayList.GetListPosition(m_Handle->addonData, m_ControlHandle);
  }

  inline void CPlayerLib_PlayList::Shuffle(bool shuffle)
  {
    m_cb->AddonPlayList.Shuffle(m_Handle->addonData, m_ControlHandle, shuffle);
  }

}; /* extern "C" */
}; /* V2 */
}; /* PlayerLIB */
