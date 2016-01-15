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
#include "internal/libKODI_guilib_DialogOKHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  ///
  /// \ingroup GUILIB
  /// \defgroup CAddonGUIDialogOK
  /// @{
  /// @brief <b>OK dialog</b>
  ///
  /// The functions listed below permit the call of a dialogue of information, a
  /// confirmation of the user by press from OK required.
  ///
  /// These are pure static functions them no other initialization need.
  ///
  /// It has the header \ref GUIDialogOK.h "#include <kodi/gui.api2/GUIDialogOK.h>"
  /// be included to enjoy it.
  ///
  /// \image html help.GUIDialogOK.png
  ///
  class CAddonGUIDialogOK
  {
  public:
    ///
    /// \ingroup CAddonGUIDialogOK
    /// @brief Use dialog to inform user with text and confirmation with OK with continued string.
    /// 
    /// @param heading Dialog heading.
    /// @param text Multi-line text.
    ///
    /// <b>Code example:</b>
    /// \code
    /// #include <kodi/gui.api2/GUIDialogOK.h>
    /// ...
    /// CAddonGUIDialogOK::ShowAndGetInput("Test dialog", "Hello World!\nI'm a call from add-on\n :) :D");
    /// \endcode
    ///
    static void ShowAndGetInput(
      const std::string&      heading,
      const std::string&      text);

    ///
    /// \ingroup CAddonGUIDialogOK
    /// @brief Use dialog to inform user with text and confirmation with OK with strings separated to the lines.
    ///
    /// @param heading Dialog heading.
    /// @param line0 Line #1 text.
    /// @param line1 Line #2 text.
    /// @param line2 Line #3 text.
    ///
    /// <b>Code example:</b>
    /// \code
    /// #include <kodi/gui.api2/GUIDialogOK.h>
    /// ...
    /// CAddonGUIDialogOK::ShowAndGetInput("Test dialog", "Hello World!", "I'm a call from add-on", " :) :D");
    /// \endcode
    ///
    static void ShowAndGetInput(
      const std::string&      heading,
      const std::string&      line0,
      const std::string&      line1,
      const std::string&      line2);
  };
  /** @}*/

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_DialogOKTail.h"
