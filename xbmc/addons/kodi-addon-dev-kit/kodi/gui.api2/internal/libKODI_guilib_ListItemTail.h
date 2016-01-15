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

/*
 * GUILib.h EOF header, passed there (out of normal code style) to reduce
 * not needed parts, to have only add-on programming related stuff there.
 */

namespace GUILIB
{
namespace V2
{

  inline CAddonGUIListItem::CAddonGUIListItem(
    const std::string&      label,
    const std::string&      label2,
    const std::string&      iconImage,
    const std::string&      thumbnailImage,
    const std::string&      path)
   : m_Handle((ADDON::AddonCB*)CGUILib::g_libKODI_Internal->m_Handle),
     m_cb(CGUILib::g_libKODI_Internal->m_Callbacks)
  {
    m_ListItemHandle = m_cb->ListItem.Create(m_Handle->addonData, label.c_str(),
                                             label2.c_str(), iconImage.c_str(),
                                             thumbnailImage.c_str(), path.c_str());
  }

  inline CAddonGUIListItem::~CAddonGUIListItem()
  {
    m_cb->ListItem.Destroy(m_Handle->addonData, m_ListItemHandle);
  }

  inline std::string CAddonGUIListItem::GetLabel()
  {
    std::string label;
    label.resize(1024);
    unsigned int size = (unsigned int)label.capacity();
    m_cb->ListItem.GetLabel(m_Handle->addonData, m_ListItemHandle, label[0], size);
    label.resize(size);
    label.shrink_to_fit();
    return label.c_str();
  }

  inline void CAddonGUIListItem::SetLabel(const std::string &label)
  {
    m_cb->ListItem.SetLabel(m_Handle->addonData, m_ListItemHandle, label.c_str());
  }

  inline std::string CAddonGUIListItem::GetLabel2()
  {
    std::string label;
    label.resize(1024);
    unsigned int size = (unsigned int)label.capacity();
    m_cb->ListItem.GetLabel2(m_Handle->addonData, m_ListItemHandle, label[0], size);
    label.resize(size);
    label.shrink_to_fit();
    return label.c_str();
  }

  inline void CAddonGUIListItem::SetLabel2(const std::string &label)
  {
    m_cb->ListItem.SetLabel2(m_Handle->addonData, m_ListItemHandle, label.c_str());
  }

  inline std::string CAddonGUIListItem::GetIconImage()
  {
    std::string image;
    image.resize(1024);
    unsigned int size = (unsigned int)image.capacity();
    m_cb->ListItem.GetIconImage(m_Handle->addonData, m_ListItemHandle, image[0], size);
    image.resize(size);
    image.shrink_to_fit();
    return image.c_str();
  }

  inline void CAddonGUIListItem::SetIconImage(const std::string &image)
  {
    m_cb->ListItem.SetIconImage(m_Handle->addonData, m_ListItemHandle, image.c_str());
  }

  inline std::string CAddonGUIListItem::GetOverlayImage()
  {
    std::string image;
    image.resize(1024);
    unsigned int size = (unsigned int)image.capacity();
    m_cb->ListItem.GetOverlayImage(m_Handle->addonData, m_ListItemHandle, image[0], size);
    image.resize(size);
    image.shrink_to_fit();
    return image.c_str();
  }

  inline void CAddonGUIListItem::SetOverlayImage(unsigned int image, bool bOnOff /*= false */)
  {
    m_cb->ListItem.SetOverlayImage(m_Handle->addonData, m_ListItemHandle, image, bOnOff);
  }

  inline void CAddonGUIListItem::SetThumbnailImage(const std::string &image)
  {
    m_cb->ListItem.SetThumbnailImage(m_Handle->addonData, m_ListItemHandle, image.c_str());
  }

  inline void CAddonGUIListItem::SetArt(const std::string &type, const std::string &url)
  {
    m_cb->ListItem.SetArt(m_Handle->addonData, m_ListItemHandle, type.c_str(), url.c_str());
  }

  inline void CAddonGUIListItem::SetArtFallback(const std::string &from, const std::string &to)
  {
    m_cb->ListItem.SetArtFallback(m_Handle->addonData, m_ListItemHandle, from.c_str(), to.c_str());
  }

  inline bool CAddonGUIListItem::HasArt(const std::string &type)
  {
    return m_cb->ListItem.HasArt(m_Handle->addonData, m_ListItemHandle, type.c_str());
  }

  inline void CAddonGUIListItem::SetSortLabel(const std::string &label)
  {
    m_cb->ListItem.SetSortLabel(m_Handle->addonData, m_ListItemHandle, label.c_str());
  }

  inline void CAddonGUIListItem::Select(bool bOnOff)
  {
    m_cb->ListItem.Select(m_Handle->addonData, m_ListItemHandle, bOnOff);
  }

  inline bool CAddonGUIListItem::IsSelected()
  {
    return m_cb->ListItem.IsSelected(m_Handle->addonData, m_ListItemHandle);
  }

  inline bool CAddonGUIListItem::HasIcon()
  {
    return m_cb->ListItem.HasIcon(m_Handle->addonData, m_ListItemHandle);
  }

  inline bool CAddonGUIListItem::HasOverlay()
  {
    return m_cb->ListItem.HasOverlay(m_Handle->addonData, m_ListItemHandle);
  }

  inline bool CAddonGUIListItem::IsFileItem()
  {
    return m_cb->ListItem.IsFileItem(m_Handle->addonData, m_ListItemHandle);
  }

  inline bool CAddonGUIListItem::IsFolder()
  {
    return m_cb->ListItem.IsFolder(m_Handle->addonData, m_ListItemHandle);
  }

  inline void CAddonGUIListItem::SetProperty(const std::string &key, const std::string &value)
  {
    m_cb->ListItem.SetProperty(m_Handle->addonData, m_ListItemHandle, key.c_str(), value.c_str());
  }

  inline std::string CAddonGUIListItem::GetProperty(const std::string &key)
  {
    std::string property;
    property.resize(1024);
    unsigned int size = (unsigned int)property.capacity();
    m_cb->ListItem.GetProperty(m_Handle->addonData, m_ListItemHandle, key.c_str(), property[0], size);
    property.resize(size);
    property.shrink_to_fit();
    return property;
  }

  inline void CAddonGUIListItem::IncrementProperty(const std::string &key, int nVal)
  {
    m_cb->ListItem.IncrementProperty(m_Handle->addonData, m_ListItemHandle, key.c_str(), nVal);
  }

  inline void CAddonGUIListItem::ClearProperty(const std::string &key)
  {
    m_cb->ListItem.ClearProperty(m_Handle->addonData, m_ListItemHandle, key.c_str());
  }

  inline void CAddonGUIListItem::ClearProperties()
  {
    m_cb->ListItem.ClearProperties(m_Handle->addonData, m_ListItemHandle);
  }

  inline bool CAddonGUIListItem::HasProperties()
  {
    return m_cb->ListItem.HasProperties(m_Handle->addonData, m_ListItemHandle);
  }

  inline bool CAddonGUIListItem::HasProperty(const std::string &key)
  {
    return m_cb->ListItem.HasProperty(m_Handle->addonData, m_ListItemHandle, key.c_str());
  }

  inline void CAddonGUIListItem::SetPath(const std::string &path)
  {
    m_cb->ListItem.SetPath(m_Handle->addonData, m_ListItemHandle, path.c_str());
  }

}; /* namespace V2 */
}; /* namespace GUILIB */
