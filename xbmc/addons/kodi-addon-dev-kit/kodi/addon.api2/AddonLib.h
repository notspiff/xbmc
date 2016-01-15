#pragma once
/*
 *      Copyright (C) 2005-2013 Team XBMC
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

#include "internal/libKODI_addon_Internal.h"

namespace AddOnLIB
{
namespace V2
{

/*\_____________________________________________________________________________
| |
| | AddOn development guide for AddOnLIB used for doxygen
| |_____________________________________________________________________________
\*/
/*!

\defgroup AddOnLIB Library - AddOnLIB
\ingroup cpp
\brief <b><em>Primary add-on helper library with general functions</em></b>

------------------------------------------------------------------------

<b>Code example:</b>

Below is a code example do show what must be done on add-on base function to
become support for library:

@code
#include <kodi/addon.api2/AddonLib.h>
#include <kodi/addon.api2/General.h>  // Needed for CAddOnLib_General::Log

// Insert one macro on your add-on for it
IMPLEMENT_KODI_ADDON_LIBRARY;
...

ADDON_STATUS ADDON_Create(void* hdl, void* props)
{
  if (!hdl || !props)
    return ADDON_STATUS_UNKNOWN;

  // Enable access to all add-on to Kodi functions
  if (!CAddonLib::RegisterMe(hdl))
    return ADDON_STATUS_PERMANENT_FAILURE;
  ...

  // Example lib call
  CAddOnLib_General::Log(LOG_INFO, "My add-on creation done");

  return ADDON_STATUS_OK;
}

void ADDON_Destroy()
{
  ...
  CAddonLib::UnRegisterMe();
  ...
}
@endcode

@note To use the add-on on Windows must be the dlfcn-win32.cpp inserted on
them. Is required to have translation functions from Windows to dlfcn,
requested for access to Kodi!

 */
/*\_____________________________________________________________________________
\*/

  ///
  /// \defgroup CAddonLib
  /// \ingroup AddOnLIB
  /// @{
  /// @brief <b>Addon basic library functions</b>
  ///
  /// Permits the use of the required functions of the add-on to Kodi.
  ///
  /// These are pure static functions them no other initialization need.
  ///
  /// It has the header \ref AddonLib.h "#include <kodi/addon.api2/AddonLib.h>" be included
  /// to enjoy it.
  ///
  class CAddonLib : protected CAddonLib_Internal
  {
  public:

    ///
    /// @ingroup CAddonLib
    /// @brief Resolve all callback methods
    ///
    /// This function link the all functions from library to kodi and without
    /// this call are them note usable.
    ///
    /// @note The required handle becomes only be send from ADDON_Create call.
    ///
    /// @param[in] handle Pointer to the add-on
    /// @return True when all methods were resolved, false otherwise.
    ///
    /// <b>Code example:</b>
    /// @code
    /// #include <kodi/addon.api2/AddonLib.h>
    ///
    /// // Insert one macro on your add-on for it
    /// IMPLEMENT_KODI_ADDON_LIBRARY;
    /// ...
    /// ADDON_STATUS ADDON_Create(void* hdl, void* props)
    /// {
    ///   ...
    ///   // Enable access to all add-on to Kodi functions
    ///   if (!CAddonLib::RegisterMe(hdl))
    ///     return ADDON_STATUS_PERMANENT_FAILURE;
    ///   ...
    /// }
    /// @endcode
    ///
    /// @warning To use the library must be one time the macro IMPLEMENT_KODI_ADDON_LIBRARY
    /// somewhere included.
    ///
    static bool RegisterMe(void* handle);

    ///
    /// @ingroup CAddonLib
    /// @brief Release all callback methods and close handling with them
    ///
    /// <b>Code example:</b>
    /// @code
    /// #include <kodi/addon.api2/AddonLib.h>
    /// ...
    /// void ADDON_Destroy()
    /// {
    ///   ...
    ///   CAddonLib::UnRegisterMe();
    ///   ...
    /// }
    /// @endcode
    ///
    static void UnRegisterMe();

    KODI_ADDON_LIBRARY;
  };
  ///@}

}; /* namespace V2 */
}; /* namespace AddOnLIB */
#include "internal/libKODI_addon_AddonLibTail.h"
