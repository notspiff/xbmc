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
#include "internal/libKODI_guilib_ControlFadeLabelHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  ///
  /// \defgroup CAddonGUIControlFadeLabel
  /// \ingroup GUILIB
  /// @{
  /// @brief <b>Window control used to show multiple pieces of text in the same
  /// position, by fading from one to the other</b>
  ///
  /// The fade label control is used for displaying multiple pieces of text in
  /// the same space in Kodi. You can choose the font, size, colour, location
  /// and contents of the text to be displayed. The first piece of information
  /// to display fades in over 50 frames, then scrolls off to the left. Once it
  /// is finished scrolling off screen, the second piece of information fades
  /// in and the process repeats. A fade label control is not supported in a
  /// list container.
  ///
  /// It has the header \ref GUIControlFadeLabel.h "#include <kodi/gui.api2/GUIControlFadeLabel.h>" be included
  /// to enjoy it.
  ///
  /// @note The call of the control is only possible from the corresponding
  /// window as its class and identification number is required.
  ///
  class CAddonGUIControlFadeLabel
  {
  public:
    ///
    /// \ingroup CAddonGUIControlFadeLabel
    /// @brief
    ///
    ///
    ///
    CAddonGUIControlFadeLabel(CAddonGUIWindow* window, int controlId);

    ///
    /// \ingroup CAddonGUIControlFadeLabel
    /// @brief
    ///
    ///
    ///
    virtual ~CAddonGUIControlFadeLabel();

    ///
    /// \ingroup CAddonGUIControlFadeLabel
    /// @brief
    ///
    ///
    ///
    void SetVisible(bool visible);

    ///
    /// \ingroup CAddonGUIControlFadeLabel
    /// @brief
    ///
    ///
    ///
    void AddLabel(const std::string& label);

    ///
    /// \ingroup CAddonGUIControlFadeLabel
    /// @brief
    ///
    ///
    ///
    std::string GetLabel() const;

    ///
    /// \ingroup CAddonGUIControlFadeLabel
    /// @brief
    ///
    ///
    ///
    void SetScrolling(bool scroll);

    ///
    /// \ingroup CAddonGUIControlFadeLabel
    /// @brief
    ///
    ///
    ///
    void Reset();

    IMPL_GUI_FADELABEL_CONTROL;
  };
  /** @}*/

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_ControlFadeLabelTail.h"
