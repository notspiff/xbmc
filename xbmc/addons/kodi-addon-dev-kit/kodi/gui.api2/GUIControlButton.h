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
#include "internal/libKODI_guilib_ControlButtonHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  ///
  /// \defgroup CAddonGUIControlButton
  /// \ingroup GUILIB
  /// @{
  /// @brief <b>Standard push button control for window</b>
  ///
  /// The button control is used for creating push buttons in Kodi. You can
  /// choose the position, size, and look of the button, as well as choosing
  /// what action(s) should be performed when pushed.
  ///
  /// It has the header \ref GUIControlButton.h "#include <kodi/gui.api2/GUIControlButton.h>" be included
  /// to enjoy it.
  ///
  /// @note The call of the control is only possible from the corresponding
  /// window as its class and identification number is required.
  ///
  class CAddonGUIControlButton
  {
  public:
    ///
    /// @ingroup CAddonGUIControlButton
    /// @brief Construct a new control
    ///
    /// @param window      related window control class
    /// @param controlId   Used skin xml control id
    ///
    CAddonGUIControlButton(CAddonGUIWindow* window, int controlId);

    ///
    /// @ingroup CAddonGUIControlButton
    /// @brief Destructor
    ///
    ~CAddonGUIControlButton();

    ///
    /// @ingroup CAddonGUIControlButton
    /// @brief Set the control on window to visible
    ///
    /// @param If true visible, otherwise hidden
    ///
    void SetVisible(bool visible);

    ///
    /// @ingroup CAddonGUIControlButton
    /// @brief Set's the control's enabled/disabled state
    ///
    /// @param If true enabled, otherwise disabled
    ///
    void SetEnabled(bool enabled);

    ///
    /// @ingroup CAddonGUIControlButton
    /// @brief To set the text string on button
    ///
    /// @param Text to show
    ///
    void SetLabel(const std::string& text);

    ///
    /// @ingroup CAddonGUIControlButton
    /// @brief Get the used text from button
    ///
    /// @return Text shown
    ///
    std::string GetLabel() const;

    ///
    /// @ingroup CAddonGUIControlButton
    /// @brief If two labels are used for button becomes it set with them
    ///
    /// @param Text for second label
    ///
    void SetLabel2(const std::string& text);

    ///
    /// @ingroup CAddonGUIControlButton
    /// @brief Get the second label if present
    ///
    /// @return Second label
    ///
    std::string GetLabel2() const;

    IMPL_GUI_BUTTON_CONTROL;
  };
  /** @}*/

}; /* namespace V2 */
}; /* namespace GUILIB */
#include "internal/libKODI_guilib_ControlButtonTail.h"
