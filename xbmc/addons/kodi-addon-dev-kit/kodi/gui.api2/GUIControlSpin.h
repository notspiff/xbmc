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
#include "internal/libKODI_guilib_ControlSpinHead.h"

namespace GUILIB
{
namespace V2
{

  ///
  /// \defgroup CAddonGUIControlSpin
  /// \ingroup GUILIB
  /// @{
  /// @brief <b>Window control used for cycling up/down controls</b>
  ///
  /// The settings spin control is used in the settings screens for when a list
  /// of options can be chosen from using up/down arrows. You can choose the
  /// position, size, and look of the spin control. It is basically a cross
  /// between the button control and a spin control. It has a label and focus
  /// and non focus textures, as well as a spin control on the right.
  ///
  /// It has the header \ref GUIControlSpin.h "#include <kodi/gui.api2/GUIControlSpin.h>" be included
  /// to enjoy it.
  ///
  /// @note The call of the control is only possible from the corresponding
  /// window as its class and identification number is required.
  ///


  ///
  /// \ingroup CAddonGUIControlSpin
  /// @brief
  ///
  ///
  ///
  typedef enum AddonGUISpinControlType
  {
    ADDON_SPIN_CONTROL_TYPE_INT    = 1,
    ADDON_SPIN_CONTROL_TYPE_FLOAT  = 2,
    ADDON_SPIN_CONTROL_TYPE_TEXT   = 3,
    ADDON_SPIN_CONTROL_TYPE_PAGE   = 4
  } AddonGUISpinControlType;

  class CAddonGUIControlSpin
  {
  public:

    ///
    /// \ingroup CAddonGUIControlSpin
    /// @brief
    ///
    ///
    ///
    CAddonGUIControlSpin(CAddonGUIWindow* window, int controlId);

    ///
    /// \ingroup CAddonGUIControlSpin
    /// @brief
    ///
    ///
    ///
    virtual ~CAddonGUIControlSpin();

    ///
    /// \ingroup CAddonGUIControlSpin
    /// @brief
    ///
    ///
    ///
    void SetVisible(bool visible);

    ///
    /// \ingroup CAddonGUIControlSpin
    /// @brief
    ///
    ///
    ///
    void SetEnabled(bool enabled);

    ///
    /// \ingroup CAddonGUIControlSpin
    /// @brief
    ///
    ///
    ///
    void SetText(const std::string& text);

    ///
    /// \ingroup CAddonGUIControlSpin
    /// @brief
    ///
    ///
    ///
    void Reset();

    ///
    /// \ingroup CAddonGUIControlSpin
    /// @brief
    ///
    ///
    ///
    void SetType(int type);

    ///
    /// \ingroup CAddonGUIControlSpin
    /// @brief
    ///
    ///
    ///
    void AddLabel(const std::string& label, const std::string& value);

    ///
    /// \ingroup CAddonGUIControlSpin
    /// @brief
    ///
    ///
    ///
    void AddLabel(const std::string& label, int value);

    ///
    /// \ingroup CAddonGUIControlSpin
    /// @brief
    ///
    ///
    ///
    void SetStringValue(const std::string& value);

    ///
    /// \ingroup CAddonGUIControlSpin
    /// @brief
    ///
    ///
    ///
    std::string GetStringValue() const;

    ///
    /// \ingroup CAddonGUIControlSpin
    /// @brief
    ///
    ///
    ///
    void SetIntRange(int start, int end);

    ///
    /// \ingroup CAddonGUIControlSpin
    /// @brief
    ///
    ///
    ///
    void SetIntValue(int value);

    ///
    /// \ingroup CAddonGUIControlSpin
    /// @brief
    ///
    ///
    ///
    int GetIntValue() const;

    ///
    /// \ingroup CAddonGUIControlSpin
    /// @brief
    ///
    ///
    ///
    void SetFloatRange(float start, float end);

    ///
    /// \ingroup CAddonGUIControlSpin
    /// @brief
    ///
    ///
    ///
    void SetFloatValue(float value);

    ///
    /// \ingroup CAddonGUIControlSpin
    /// @brief
    ///
    ///
    ///
    float GetFloatValue() const;

    ///
    /// \ingroup CAddonGUIControlSpin
    /// @brief
    ///
    ///
    ///
    void SetFloatInterval(float interval);

    IMPL_GUI_SPIN_CONTROL;
  };
  /** @}*/

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_ControlSpinTail.h"
