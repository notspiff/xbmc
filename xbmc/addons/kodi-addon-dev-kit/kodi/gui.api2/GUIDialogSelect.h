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

#include <vector>

#include "definations.h"
#include "internal/libKODI_guilib_DialogSelectHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  ///
  /// \ingroup GUILIB
  /// \defgroup CAddonGUIDialogSelect
  /// @{
  /// @brief <b>Selection dialog</b>
  ///
  /// The function listed below permits the call of a dialogue to select of an
  /// entry as a key
  ///
  /// These are pure static functions them no other initialization need.
  ///
  /// It has the header \ref GUIDialogSelect.h "#include <kodi/gui.api2/GUIDialogSelect.h>"
  /// be included to enjoy it.
  ///
  /// \image html help.GUIDialogSelect.png
  ///
  class CAddonGUIDialogSelect
  {
  public:
    ///
    /// \ingroup CAddonGUIDialogSelect
    /// @brief Show a selection dialog about given parts.
    ///
    /// @param heading   Dialog heading name
    /// @param entries   String list about entries
    /// @param selected  [opt] Predefined selection (default is <tt>-1</tt> for the first)
    /// @return          The selected entry, if return <tt>-1</tt> was nothing selected or canceled
    ///
    /// <b>Code example:</b>
    /// \code
    /// #include <kodi/gui.api2/GUIDialogSelect.h>
    ///
    /// const std::vector<std::string> entries
    /// {
    ///   "Test 1",
    ///   "Test 2",
    ///   "Test 3",
    ///   "Test 4",
    ///   "Test 5"
    /// };
    ///
    /// int selected = CAddonGUIDialogSelect::Show("Test selection", entries, -1);
    /// if (selected < 0)
    ///   fprintf(stderr, "Item selection canceled\n");
    /// else
    ///   fprintf(stderr, "Selected item is: %i\n", selected);
    /// \endcode
    ///
    static int Show(
      const std::string&              heading,
      const std::vector<std::string>& entries,
      int                             selected = -1);
  };
  /** @}*/

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_DialogSelectTail.h"
