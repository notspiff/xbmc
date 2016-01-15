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
#include "internal/libKODI_guilib_ControlRadioButtonHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  ///
  /// \defgroup CAddonGUIControlRadioButton
  /// \ingroup GUILIB
  /// @{
  /// @brief <b>Window control for a radio button (as used for on/off settings)</b>
  ///
  /// The radio button control is used for creating push button on/off settings
  /// in Kodi. You can choose the position, size, and look of the button. When the
  /// user clicks on the radio button, the state will change, toggling the extra
  /// textures (textureradioon and textureradiooff). Used for settings controls.
  ///
  /// It has the header \ref GUIControlRadioButton.h "#include <kodi/gui.api2/GUIControlRadioButton.h>" be included
  /// to enjoy it.
  ///
  /// @note The call of the control is only possible from the corresponding
  /// window as its class and identification number is required.
  ///
  class CAddonGUIControlRadioButton
  {
  public:

    ///
    /// \ingroup CAddonGUIControlRadioButton
    /// @brief
    ///
    ///
    ///
    CAddonGUIControlRadioButton(CAddonGUIWindow* window, int controlId);

    ///
    /// \ingroup CAddonGUIControlRadioButton
    /// @brief
    ///
    ///
    ///
    virtual ~CAddonGUIControlRadioButton();

    ///
    /// \ingroup CAddonGUIControlRadioButton
    /// @brief
    ///
    ///
    ///
    void SetVisible(bool visible);

    ///
    /// \ingroup CAddonGUIControlRadioButton
    /// @brief
    ///
    ///
    ///
    void SetEnabled(bool enabled);

    ///
    /// \ingroup CAddonGUIControlRadioButton
    /// @brief
    ///
    ///
    ///
    void SetLabel(const std::string& label);

    ///
    /// \ingroup CAddonGUIControlRadioButton
    /// @brief
    ///
    ///
    ///
    std::string GetLabel() const;

    ///
    /// \ingroup CAddonGUIControlRadioButton
    /// @brief
    ///
    ///
    ///
    void SetSelected(bool selected);

    ///
    /// \ingroup CAddonGUIControlRadioButton
    /// @brief
    ///
    ///
    ///
    bool IsSelected() const;

    IMPL_GUI_RADIO_BUTTON_CONTROL;
  };
  /** @}*/

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_ControlRadioButtonTail.h"
