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
#include "internal/libKODI_guilib_internal.h"
#include "internal/libKODI_guilib_ControlTextBoxHead.h"

namespace GUILIB
{
namespace V2
{

  ///
  /// \defgroup CAddonGUIControlTextBox
  /// \ingroup GUILIB
  /// @{
  /// @brief <b>Used to show a multi-page piece of text</b>
  ///
  /// The text box control can be used to display descriptions, help texts or
  /// other larger texts. It corresponds to the representation which is also to
  /// be seen on the CAddonGUIDialogTextViewer.
  ///
  /// It has the header \ref GUIControlTextBox.h "#include <kodi/gui.api2/GUIControlTextBox.h>" be included
  /// to enjoy it.
  ///
  /// @note The call of the control is only possible from the corresponding
  /// window as its class and identification number is required.
  ///
  class CAddonGUIControlTextBox
  {
  public:

    ///
    /// \ingroup CAddonGUIControlTextBox
    /// @brief
    ///
    ///
    ///
    CAddonGUIControlTextBox(CAddonGUIWindow* window, int controlId);

    ///
    /// \ingroup CAddonGUIControlTextBox
    /// @brief
    ///
    ///
    ///
    virtual ~CAddonGUIControlTextBox();

    ///
    /// \ingroup CAddonGUIControlTextBox
    /// @brief
    ///
    ///
    ///
    void SetVisible(bool visible);

    ///
    /// \ingroup CAddonGUIControlTextBox
    /// @brief
    ///
    ///
    ///
    void Reset();

    ///
    /// \ingroup CAddonGUIControlTextBox
    /// @brief
    ///
    ///
    ///
    void SetText(const std::string& text);

    ///
    /// \ingroup CAddonGUIControlTextBox
    /// @brief
    ///
    ///
    ///
    std::string GetText() const;

    ///
    /// \ingroup CAddonGUIControlTextBox
    /// @brief
    ///
    ///
    ///
    void Scroll(unsigned int position);

    ///
    /// \ingroup CAddonGUIControlTextBox
    /// @brief
    ///
    ///
    ///
    void SetAutoScrolling(int delay, int time, int repeat);

    IMPL_GUI_TEXTBOX_CONTROL;
  };
  /** @}*/

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_ControlTextBoxTail.h"
