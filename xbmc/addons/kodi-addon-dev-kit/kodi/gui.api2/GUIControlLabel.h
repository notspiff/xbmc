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
#include "internal/libKODI_guilib_ControlLabelHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  ///
  /// \defgroup CAddonGUIControlLabel
  /// \ingroup GUILIB
  /// @{
  /// @brief <b>Window control used to show some lines of text.</b>
  ///
  /// The label control is used for displaying text in Kodi. You can choose
  /// the font, size, colour, location and contents of the text to be displayed.
  ///
  /// It has the header \ref GUIControlLabel.h "#include <kodi/gui.api2/GUIControlLabel.h>" be included
  /// to enjoy it.
  ///
  /// @note The call of the control is only possible from the corresponding
  /// window as its class and identification number is required.
  ///
  class CAddonGUIControlLabel
  {
  public:

    ///
    /// \ingroup CAddonGUIControlLabel
    /// @brief
    ///
    ///
    ///
    CAddonGUIControlLabel(CAddonGUIWindow* window, int controlId);

    ///
    /// \ingroup CAddonGUIControlLabel
    /// @brief
    ///
    ///
    ///
    virtual ~CAddonGUIControlLabel();

    ///
    /// \ingroup CAddonGUIControlLabel
    /// @brief
    ///
    ///
    ///
    void SetVisible(bool visible);

    ///
    /// \ingroup CAddonGUIControlLabel
    /// @brief
    ///
    ///
    ///
    void SetLabel(const std::string& text);

    ///
    /// \ingroup CAddonGUIControlLabel
    /// @brief
    ///
    ///
    ///
    std::string GetLabel() const;

    IMPL_GUI_LABEL_CONTROL;
  };
  /** @}*/

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_ControlLabelTail.h"
