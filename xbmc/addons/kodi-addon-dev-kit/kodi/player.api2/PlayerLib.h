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
#include "internal/libKODI_player_Internal.h"

namespace PlayerLIB
{
namespace V2
{

/*!

\defgroup PlayerLIB  Library - PlayerLIB
\ingroup cpp
\brief <b><em>Auxiliary functions for playback and control of files</em></b>

*/

  ///
  /// \defgroup CPlayerLib
  /// \ingroup PlayerLIB
  /// @{
  /// @brief <b>Allow use of binary classes and function to use on add-on's</b>
  ///
  /// Permits the use of the required functions of the add-on to Kodi. This class
  /// also contains some functions to the control.
  ///
  /// These are pure static functions them no other initialization need.
  ///
  /// It has the header \ref PlayerLib.h "#include <kodi/player.api2/PlayerLib.h>" be included
  /// to enjoy it.
  ///
  class CPlayerLib : protected CPlayerLib_Internal
  {
  public:
    ///
    /// @ingroup CPlayerLib
    /// @brief Resolve all callback methods
    /// @param handle Pointer to the add-on
    /// @return True when all methods were resolved, false otherwise.
    ///
    static bool RegisterMe(void *handle);

    ///
    /// @ingroup CPlayerLib
    /// @brief Release all callback methods and close handling with them
    ///
    static void UnRegisterMe();

    KODI_PLAYER_LIBRARY;
  };
  /** @}*/

}; /* namespace V2 */
}; /* namespace PlayerLIB */
#include "internal/libKODI_player_LibFunc.h"
