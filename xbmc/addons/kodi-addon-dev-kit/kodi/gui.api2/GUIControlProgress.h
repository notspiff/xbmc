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
#include "internal/libKODI_guilib_ControlProgressHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  ///
  /// \defgroup CAddonGUIControlProgress
  /// \ingroup GUILIB
  /// @{
  /// @brief <b>Window control to show the progress of a particular operation</b>
  ///
  /// The progress control is used to show the progress of an item that may take
  /// a long time, or to show how far through a movie you are. You can choose the
  /// position, size, and look of the progress control.
  ///
  /// It has the header \ref GUIControlProgress.h "#include <kodi/gui.api2/GUIControlProgress.h>" be included
  /// to enjoy it.
  ///
  /// @note The call of the control is only possible from the corresponding
  /// window as its class and identification number is required.
  ///
  class CAddonGUIControlProgress
  {
  public:

    ///
    /// \ingroup CAddonGUIControlProgress
    /// @brief
    ///
    ///
    ///
    CAddonGUIControlProgress(CAddonGUIWindow* window, int controlId);

    ///
    /// \ingroup CAddonGUIControlProgress
    /// @brief
    ///
    ///
    ///
    virtual ~CAddonGUIControlProgress();

    ///
    /// \ingroup CAddonGUIControlProgress
    /// @brief
    ///
    ///
    ///
    void SetVisible(bool visible);

    ///
    /// \ingroup CAddonGUIControlProgress
    /// @brief
    ///
    ///
    ///
    void SetPercentage(float percent);

    ///
    /// \ingroup CAddonGUIControlProgress
    /// @brief
    ///
    ///
    ///
    float GetPercentage() const;

    IMPL_GUI_PROGRESS_CONTROL;
  };
  /** @}*/

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_ControlProgressTail.h"
