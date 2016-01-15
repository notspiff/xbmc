#pragma once
/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://xbmc.org
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
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

/*!

\defgroup GUILIB Library - GUILIB
\ingroup cpp
\brief <b><em>Graphical functions for Windows and Dialogs to show</em></b>

*/

  ///
  /// \defgroup CGUILib
  /// \ingroup GUILIB
  /// @{
  /// @brief <b>Allow use of binary classes and function to use on add-on's</b>
  ///
  /// Permits the use of the required functions of the add-on to Kodi. This class
  /// also contains some functions to the control.
  ///
  /// These are pure static functions them no other initialization need.
  ///
  /// It has the header \ref GUILib.h "#include <kodi/gui.api2/GUILib.h>" be included
  /// to enjoy it.
  ///
  class CGUILib : protected CGUILib_Internal
  {
  public:

    ///
    /// @defgroup CGUILib_main Register functions
    /// \ingroup CGUILib
    /// @brief <b>Functions to handle library registration to Kodi</b>
    ///
    /// @link CAddonGUIWindow Go back to normal functions from CAddonGUIWindow@endlink
    ///

    ///
    /// \ingroup CGUILib_main
    /// @brief Resolve all callback methods
    /// @param handle Pointer to the add-on
    /// @return True when all methods were resolved, false otherwise.
    ///
    static bool RegisterMe(void *handle);

    ///
    /// \ingroup CGUILib_main
    /// @brief Release all callback methods and close handling with them
    ///
    static void UnRegisterMe();

    /*\_________________________________________________________________________
    \*/

    ///
    /// @defgroup CGUILib_help Help functions
    /// \ingroup CGUILib
    /// @brief <b>Functions for GUI</b>
    ///

    ///
    /// \ingroup CGUILib_help
    /// @brief Performs a graphical lock of rendering engine
    ///
    static void Lock();

    ///
    /// \ingroup CGUILib_help
    /// @brief Performs a graphical unlock of previous locked rendering engine
    ///
    static void Unlock();

    /*\_________________________________________________________________________
    \*/

    ///
    /// \ingroup CGUILib_help
    /// @brief Return the the current screen height with pixel
    ///
    static int GetScreenHeight();

    ///
    /// \ingroup CGUILib_help
    /// @brief Return the the current screen width with pixel
    ///
    static int GetScreenWidth();

    ///
    /// \ingroup CGUILib_help
    /// @brief Return the the current screen rendering resolution
    ///
    static int GetVideoResolution();


    /*\_________________________________________________________________________
    \*/

    ///
    /// \ingroup CGUILib_help
    /// @brief
    ///
    static int GetCurrentWindowDialogId();

    ///
    /// \ingroup CGUILib_help
    /// @brief
    ///
    static int GetCurrentWindowId();

    KODI_GUI_LIBRARY;
  };
  /** @}*/

}; /* namespace V2 */
}; /* namespace GUILIB */
#include "internal/libKODI_guilib_LibTail.h"
