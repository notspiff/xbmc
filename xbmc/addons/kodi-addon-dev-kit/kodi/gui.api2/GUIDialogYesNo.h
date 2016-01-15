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
#include "internal/libKODI_guilib_DialogYesNoHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  ///
  /// \ingroup GUILIB
  /// \defgroup CAddonGUIDialogYesNo
  /// @{
  /// @brief <b>Yes / No dialog</b>
  ///
  /// The Yes / No dialog can be used to inform the user about questions and get
  /// the answer.
  ///
  /// In order to achieve a line break is a <b>\\n</b> directly in the text or in the
  /// "./resources/language/resource.language.??_??/strings.po" to call with
  /// <b>std::string CAddonLib_General::GetLocalizedString(...);</b>.
  ///
  /// These are pure static functions them no other initialization need.
  ///
  /// It has the header \ref GUIDialogYesNo.h "#include <kodi/gui.api2/GUIDialogYesNo.h>"
  /// be included to enjoy it.
  ///
  /// \image html help.GUIDialogYesNo.png
  ///
  class CAddonGUIDialogYesNo
  {
  public:
    ///
    /// \ingroup CAddonGUIDialogYesNo
    /// @brief Use dialog to get numeric new password with one text string shown everywhere and cancel return field
    ///
    /// @param heading    Dialog heading
    /// @param text       Multi-line text
    /// @param bCanceled  Return value about cancel button
    /// @param noLabel    [opt] label to put on the no button
    /// @param yesLabel   [opt] label to put on the yes button
    /// @return           Returns True if 'Yes' was pressed, else False
    ///
    /// @note It is preferred to only use this as it is actually a multi-line text.
    ///
    /// <b>Code example:</b>
    /// \code
    /// #include <kodi/gui.api2/GUIDialogYesNo.h>
    ///
    /// bool canceled;
    /// bool ret = CAddonGUIDialogYesNo::ShowAndGetInput(
    ///    "Yes / No test call",   /* The Header */
    ///    "You has opened Yes / No dialog for test\n\nIs this OK for you?",
    ///    canceled,               /* return value about cancel button */
    ///    "Not really",           /* No label, is optional and if empty "No" */
    ///    "Ohhh yes");            /* Yes label, also optional and if empty "Yes" */
    /// fprintf(stderr, "You has called Yes/No, returned '%s' and was %s\n",
    ///          ret ? "yes" : "no",
    ///          canceled ? "canceled" : "not canceled");
    /// \endcode
    ///
    static bool ShowAndGetInput(
      const std::string&      heading,
      const std::string&      text,
      bool&                   bCanceled,
      const std::string&      noLabel = "",
      const std::string&      yesLabel = "");

    ///
    /// \ingroup CAddonGUIDialogYesNo
    /// @brief Use dialog to get numeric new password with separated line strings
    ///
    /// @param heading  Dialog heading
    /// @param line0    Line #0 text
    /// @param line1    Line #1 text
    /// @param line2    Line #2 text
    /// @param noLabel  [opt] label to put on the no button.
    /// @param yesLabel [opt] label to put on the yes button.
    /// @return         Returns True if 'Yes' was pressed, else False.
    ///
    /// <b>Code example:</b>
    /// \code
    /// #include <kodi/gui.api2/GUIDialogYesNo.h>
    ///
    /// bool ret = CAddonGUIDialogYesNo::ShowAndGetInput(
    ///    "Yes / No test call",   // The Header
    ///    "You has opened Yes / No dialog for test",
    ///    "",
    ///    "Is this OK for you?",
    ///    "Not really",           // No label, is optional and if empty "No"
    ///    "Ohhh yes");            // Yes label, also optional and if empty "Yes"
    /// fprintf(stderr, "You has called Yes/No, returned '%s'\n",
    ///          ret ? "yes" : "no");
    /// \endcode
    ///
    static bool ShowAndGetInput(
      const std::string&      heading,
      const std::string&      line0,
      const std::string&      line1,
      const std::string&      line2,
      const std::string&      noLabel = "",
      const std::string&      yesLabel = "");

    ///
    /// \ingroup CAddonGUIDialogYesNo
    /// @brief Use dialog to get numeric new password with separated line strings and cancel return field
    ///
    /// @param heading    Dialog heading
    /// @param line0      Line #0 text
    /// @param line1      Line #1 text
    /// @param line2      Line #2 text
    /// @param bCanceled  Return value about cancel button
    /// @param noLabel    [opt] label to put on the no button
    /// @param yesLabel   [opt] label to put on the yes button
    /// @return           Returns True if 'Yes' was pressed, else False
    ///
    /// <b>Code example:</b>
    /// \code
    /// #include <kodi/gui.api2/GUIDialogYesNo.h>
    ///
    /// bool canceled;
    /// bool ret = CAddonGUIDialogYesNo::ShowAndGetInput(
    ///    "Yes / No test call",   // The Header
    ///    "You has opened Yes / No dialog for test",
    ///    "",
    ///    "Is this OK for you?",
    ///    canceled,               // return value about cancel button
    ///    "Not really",           // No label, is optional and if empty "No"
    ///    "Ohhh yes");            // Yes label, also optional and if empty "Yes"
    /// fprintf(stderr, "You has called Yes/No, returned '%s' and was %s\n",
    ///          ret ? "yes" : "no",
    ///          canceled ? "canceled" : "not canceled");
    /// \endcode
    ///
    static bool ShowAndGetInput(
      const std::string&      heading,
      const std::string&      line0,
      const std::string&      line1,
      const std::string&      line2,
      bool&                   bCanceled,
      const std::string&      noLabel = "",
      const std::string&      yesLabel = "");
  };
  /** @}*/

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_DialogYesNoTail.h"
