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
#include "internal/libKODI_guilib_ControlSettingsSliderHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  ///
  /// \defgroup CAddonGUIControlSettingsSlider
  /// \ingroup GUILIB
  /// @{
  /// @brief <b>Window control for moveable slider with text name</b>
  ///
  /// The settings slider control is used in the settings screens for when an
  /// option is best specified on a sliding scale. You can choose the position,
  /// size, and look of the slider control. It is basically a cross between the
  /// button control and a slider control. It has a label and focus and non focus
  /// textures, as well as a slider control on the right.
  ///
  /// It has the header \ref GUIControlSettingsSlider.h "#include <kodi/gui.api2/GUIControlSettingsSlider.h>" be included
  /// to enjoy it.
  ///
  /// @note The call of the control is only possible from the corresponding
  /// window as its class and identification number is required.
  ///
  class CAddonGUIControlSettingsSlider
  {
  public:

    ///
    /// \ingroup CAddonGUIControlSettingsSlider
    /// @brief
    ///
    ///
    ///
    CAddonGUIControlSettingsSlider(CAddonGUIWindow* window, int controlId);

    ///
    /// \ingroup CAddonGUIControlSettingsSlider
    /// @brief
    ///
    ///
    ///
    virtual ~CAddonGUIControlSettingsSlider();

    ///
    /// \ingroup CAddonGUIControlSettingsSlider
    /// @brief
    ///
    ///
    ///
    void SetVisible(bool visible);

    ///
    /// \ingroup CAddonGUIControlSettingsSlider
    /// @brief
    ///
    ///
    ///
    void SetEnabled(bool enabled);

    ///
    /// \ingroup CAddonGUIControlSettingsSlider
    /// @brief
    ///
    ///
    ///
    void SetText(const std::string& text);

    ///
    /// \ingroup CAddonGUIControlSettingsSlider
    /// @brief
    ///
    ///
    ///
    void Reset();

    ///
    /// \ingroup CAddonGUIControlSettingsSlider
    /// @brief
    ///
    ///
    ///
    void SetIntRange(int start, int end);

    ///
    /// \ingroup CAddonGUIControlSettingsSlider
    /// @brief
    ///
    ///
    ///
    void SetIntValue(int value);

    ///
    /// \ingroup CAddonGUIControlSettingsSlider
    /// @brief
    ///
    ///
    ///
    int GetIntValue() const;

    ///
    /// \ingroup CAddonGUIControlSettingsSlider
    /// @brief
    ///
    ///
    ///
    void SetIntInterval(int interval);

    ///
    /// \ingroup CAddonGUIControlSettingsSlider
    /// @brief
    ///
    ///
    ///
    void SetPercentage(float percent);

    ///
    /// \ingroup CAddonGUIControlSettingsSlider
    /// @brief
    ///
    ///
    ///
    float GetPercentage() const;

    ///
    /// \ingroup CAddonGUIControlSettingsSlider
    /// @brief
    ///
    ///
    ///
    void SetFloatRange(float start, float end);

    ///
    /// \ingroup CAddonGUIControlSettingsSlider
    /// @brief
    ///
    ///
    ///
    void SetFloatValue(float value);

    ///
    /// \ingroup CAddonGUIControlSettingsSlider
    /// @brief
    ///
    ///
    ///
    float GetFloatValue() const;

    ///
    /// \ingroup CAddonGUIControlSettingsSlider
    /// @brief
    ///
    ///
    ///
    void SetFloatInterval(float interval);

    IMPL_GUI_SETTINGS_SLIDER_CONTROL;
  };
  /** @}*/

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_ControlSettingsSliderTail.h"
