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
#include "internal/libKODI_guilib_ControlSliderHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  ///
  /// \defgroup CAddonGUIControlSlider
  /// \ingroup GUILIB
  /// @{
  /// @brief <b>Window control for moveable slider</b>
  ///
  /// The slider control is used for things where a sliding bar best represents
  /// the operation at hand (such as a volume control or seek control). You can
  /// choose the position, size, and look of the slider control.
  ///
  /// It has the header \ref GUIControlSlider.h "#include <kodi/gui.api2/GUIControlSlider.h>" be included
  /// to enjoy it.
  ///
  /// @note The call of the control is only possible from the corresponding
  /// window as its class and identification number is required.
  ///
  class CAddonGUIControlSlider
  {
  public:

    ///
    /// \ingroup CAddonGUIControlSlider
    /// @brief
    ///
    ///
    ///
    CAddonGUIControlSlider(CAddonGUIWindow* window, int controlId);

    ///
    /// \ingroup CAddonGUIControlSlider
    /// @brief
    ///
    ///
    ///
    virtual ~CAddonGUIControlSlider();

    ///
    /// \ingroup CAddonGUIControlSlider
    /// @brief
    ///
    ///
    ///
    void SetVisible(bool visible);

    ///
    /// \ingroup CAddonGUIControlSlider
    /// @brief
    ///
    ///
    ///
    void SetEnabled(bool enabled);

    ///
    /// \ingroup CAddonGUIControlSlider
    /// @brief
    ///
    ///
    ///
    void Reset();

    ///
    /// \ingroup CAddonGUIControlSlider
    /// @brief
    ///
    ///
    ///
    std::string GetDescription() const;

    ///
    /// \ingroup CAddonGUIControlSlider
    /// @brief
    ///
    ///
    ///
    void SetIntRange(int start, int end);

    ///
    /// \ingroup CAddonGUIControlSlider
    /// @brief
    ///
    ///
    ///
    void SetIntValue(int value);

    ///
    /// \ingroup CAddonGUIControlSlider
    /// @brief
    ///
    ///
    ///
    int GetIntValue() const;

    ///
    /// \ingroup CAddonGUIControlSlider
    /// @brief
    ///
    ///
    ///
    void SetIntInterval(int interval);

    ///
    /// \ingroup CAddonGUIControlSlider
    /// @brief
    ///
    ///
    ///
    void SetPercentage(float percent);

    ///
    /// \ingroup CAddonGUIControlSlider
    /// @brief
    ///
    ///
    ///
    float GetPercentage() const;

    ///
    /// \ingroup CAddonGUIControlSlider
    /// @brief
    ///
    ///
    ///
    void SetFloatRange(float start, float end);

    ///
    /// \ingroup CAddonGUIControlSlider
    /// @brief
    ///
    ///
    ///
    void SetFloatValue(float value);

    ///
    /// \ingroup CAddonGUIControlSlider
    /// @brief
    ///
    ///
    ///
    float GetFloatValue() const;

    ///
    /// \ingroup CAddonGUIControlSlider
    /// @brief
    ///
    ///
    ///
    void SetFloatInterval(float interval);

    IMPL_GUI_SLIDER_CONTROL;
  };
  /** @}*/

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_ControlSliderTail.h"
