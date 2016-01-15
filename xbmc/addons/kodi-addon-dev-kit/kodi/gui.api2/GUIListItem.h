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

#include "internal/libKODI_guilib_internal.h"
#include "internal/libKODI_guilib_ListItemHead.h"

namespace GUILIB
{
namespace V2
{

  ///
  /// \ingroup GUILIB
  /// \defgroup CAddonGUIListItem
  /// @{
  /// @brief <b>Selectable window list item</b>
  ///
  /// The with \ref GUIListItem.h "#include <kodi/addon.api2/GUIListItem.h>" given
  /// class is used to create a item entry for a list on window and to support it's
  /// control.
  ///
  class CAddonGUIListItem
  {
  public:
    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    CAddonGUIListItem(
      const std::string&      label,
      const std::string&      label2,
      const std::string&      iconImage,
      const std::string&      thumbnailImage,
      const std::string&      path);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    ~CAddonGUIListItem();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    std::string GetLabel();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    void SetLabel(const std::string& label);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    std::string GetLabel2();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    void SetLabel2(const std::string& label);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    std::string GetIconImage();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    void SetIconImage(const std::string& image);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    std::string GetOverlayImage();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    void SetOverlayImage(unsigned int image, bool bOnOff = false);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    void SetThumbnailImage(const std::string& image);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    void SetSortLabel(const std::string& label);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    void SetArt(const std::string& type, const std::string& url);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    void SetArtFallback(const std::string& from, const std::string& to);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    bool HasArt(const std::string& type);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    bool HasIcon();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    bool HasOverlay();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    bool IsFileItem();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    bool IsFolder();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    void Select(bool bOnOff);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    bool IsSelected();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    void SetProperty(const std::string& key, const std::string& value);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    std::string GetProperty(const std::string& key);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    void IncrementProperty(const std::string& key, int nVal);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    void ClearProperty(const std::string& key);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    void ClearProperties();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    bool HasProperties();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    bool HasProperty(const std::string& key);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    ///
    ///
    void SetPath(const std::string& path);

    IMPL_ADDON_GUI_LIST;
  };
  /** @}*/

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_ListItemTail.h"
