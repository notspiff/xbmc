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

/*
 * GUILib.h EOF header, passed there (out of normal code style) to reduce
 * not needed parts, to have only add-on programming related stuff there.
 */
namespace GUILIB
{
namespace V2
{

  inline CAddonGUIControlSettingsSlider::CAddonGUIControlSettingsSlider(CAddonGUIWindow* window, int controlId)
   : m_Window(window),
     m_ControlId(controlId),
     m_Handle((ADDON::AddonCB*)CGUILib::g_libKODI_Internal->m_Handle),
     m_cb(CGUILib::g_libKODI_Internal->m_Callbacks)
  {
    if (m_Handle && m_cb)
    {
      m_ControlHandle = m_cb->Window.GetControl_SettingsSlider(m_Handle->addonData, m_Window->m_WindowHandle, controlId);
      if (!m_ControlHandle)
        fprintf(stderr, "libKODI_guilib-ERROR: CAddonGUIControlSettingsSlider can't create control class from Kodi !!!\n");
    }
  }

  inline CAddonGUIControlSettingsSlider::~CAddonGUIControlSettingsSlider()
  {
  }

  inline void CAddonGUIControlSettingsSlider::SetVisible(bool visible)
  {
    m_cb->Control.SettingsSlider.SetVisible(m_Handle->addonData, m_ControlHandle, visible);
  }

  inline void CAddonGUIControlSettingsSlider::SetEnabled(bool enabled)
  {
    m_cb->Control.SettingsSlider.SetEnabled(m_Handle->addonData, m_ControlHandle, enabled);
  }

  inline void CAddonGUIControlSettingsSlider::SetText(const std::string& label)
  {
    m_cb->Control.SettingsSlider.SetText(m_Handle->addonData, m_ControlHandle, label.c_str());
  }

  inline void CAddonGUIControlSettingsSlider::Reset()
  {
    m_cb->Control.SettingsSlider.Reset(m_Handle->addonData, m_ControlHandle);
  }

  inline void CAddonGUIControlSettingsSlider::SetIntRange(int start, int end)
  {
    m_cb->Control.SettingsSlider.SetIntRange(m_Handle->addonData, m_ControlHandle, start, end);
  }

  inline void CAddonGUIControlSettingsSlider::SetIntValue(int value)
  {
    m_cb->Control.SettingsSlider.SetIntValue(m_Handle->addonData, m_ControlHandle, value);
  }

  inline int CAddonGUIControlSettingsSlider::GetIntValue() const
  {
    return m_cb->Control.SettingsSlider.GetIntValue(m_Handle->addonData, m_ControlHandle);
  }

  inline void CAddonGUIControlSettingsSlider::SetIntInterval(int interval)
  {
    m_cb->Control.SettingsSlider.SetIntInterval(m_Handle->addonData, m_ControlHandle, interval);
  }

  inline void CAddonGUIControlSettingsSlider::SetPercentage(float percent)
  {
    m_cb->Control.SettingsSlider.SetPercentage(m_Handle->addonData, m_ControlHandle, percent);
  }

  inline float CAddonGUIControlSettingsSlider::GetPercentage() const
  {
    return m_cb->Control.SettingsSlider.GetPercentage(m_Handle->addonData, m_ControlHandle);
  }

  inline void CAddonGUIControlSettingsSlider::SetFloatRange(float start, float end)
  {
    m_cb->Control.SettingsSlider.SetFloatRange(m_Handle->addonData, m_ControlHandle, start, end);
  }

  inline void CAddonGUIControlSettingsSlider::SetFloatValue(float value)
  {
    m_cb->Control.SettingsSlider.SetFloatValue(m_Handle->addonData, m_ControlHandle, value);
  }

  inline float CAddonGUIControlSettingsSlider::GetFloatValue() const
  {
    return m_cb->Control.SettingsSlider.GetFloatValue(m_Handle->addonData, m_ControlHandle);
  }

  inline void CAddonGUIControlSettingsSlider::SetFloatInterval(float interval)
  {
    m_cb->Control.SettingsSlider.SetFloatInterval(m_Handle->addonData, m_ControlHandle, interval);
  }

}; /* namespace V2 */
}; /* namespace GUILIB */
