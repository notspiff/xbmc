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

#include "definations.h"
#include "internal/libKODI_guilib_ControlImageHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  ///
  /// \defgroup CAddonGUIControlImage
  /// \ingroup GUILIB
  /// @{
  /// @brief <b>Window control used to show an image.</b>
  ///
  /// The image control is used for displaying images in Kodi. You can choose
  /// the position, size, transparency and contents of the image to be displayed.
  ///
  /// It has the header \ref GUIControlImage.h "#include <kodi/gui.api2/GUIControlImage.h>" be included
  /// to enjoy it.
  ///
  /// @note The call of the control is only possible from the corresponding
  /// window as its class and identification number is required.
  ///
  class CAddonGUIControlImage
  {
  public:

    ///
    /// \ingroup CAddonGUIControlImage
    /// @brief
    ///
    ///
    ///
    CAddonGUIControlImage(CAddonGUIWindow* window, int controlId);

    ///
    /// \ingroup CAddonGUIControlImage
    /// @brief
    ///
    ///
    ///
    virtual ~CAddonGUIControlImage();

    ///
    /// \ingroup CAddonGUIControlImage
    /// @brief
    ///
    ///
    ///
    void SetVisible(bool visible);

    ///
    /// \ingroup CAddonGUIControlImage
    /// @brief
    ///
    ///
    ///
    void SetFileName(const std::string& strFileName, const bool useCache = true);

    ///
    /// \ingroup CAddonGUIControlImage
    /// @brief
    ///
    ///
    ///
    void SetColorDiffuse(uint32_t colorDiffuse);

    IMPL_GUI_IMAGE_CONTROL;
  };
  /** @}*/

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_ControlImageTail.h"
