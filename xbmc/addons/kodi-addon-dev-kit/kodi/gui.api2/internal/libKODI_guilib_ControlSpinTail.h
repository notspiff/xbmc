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

  inline CAddonGUIControlSpin::CAddonGUIControlSpin(CAddonGUIWindow* window, int controlId)
   : m_Window(window),
     m_ControlId(controlId),
     m_Handle((ADDON::AddonCB*)CGUILib::g_libKODI_Internal->m_Handle),
     m_cb(CGUILib::g_libKODI_Internal->m_Callbacks)
  {
    if (m_Handle && m_cb)
    {
      m_ControlHandle = m_cb->Window.GetControl_Spin(m_Handle->addonData, m_Window->m_WindowHandle, controlId);
      if (!m_ControlHandle)
        fprintf(stderr, "libKODI_guilib-ERROR: CAddonGUIControlSpin can't create control class from Kodi !!!\n");
    }
  }

  inline CAddonGUIControlSpin::~CAddonGUIControlSpin()
  {
  }

  inline void CAddonGUIControlSpin::SetVisible(bool visible)
  {
    m_cb->Control.Spin.SetVisible(m_Handle->addonData, m_ControlHandle, visible);
  }

  inline void CAddonGUIControlSpin::SetEnabled(bool enabled)
  {
    m_cb->Control.Spin.SetEnabled(m_Handle->addonData, m_ControlHandle, enabled);
  }

  inline void CAddonGUIControlSpin::SetText(const std::string& label)
  {
    m_cb->Control.Spin.SetText(m_Handle->addonData, m_ControlHandle, label.c_str());
  }

  inline void CAddonGUIControlSpin::Reset()
  {
    m_cb->Control.Spin.Reset(m_Handle->addonData, m_ControlHandle);
  }

  inline void CAddonGUIControlSpin::SetType(int type)
  {
    m_cb->Control.Spin.SetType(m_Handle->addonData, m_ControlHandle, type);
  }

  inline void CAddonGUIControlSpin::AddLabel(const std::string& label, const std::string& value)
  {
    m_cb->Control.Spin.AddStringLabel(m_Handle->addonData, m_ControlHandle, label.c_str(), value.c_str());
  }

  inline void CAddonGUIControlSpin::AddLabel(const std::string& label, int value)
  {
    m_cb->Control.Spin.AddIntLabel(m_Handle->addonData, m_ControlHandle, label.c_str(), value);
  }

  inline void CAddonGUIControlSpin::SetStringValue(const std::string& value)
  {
    m_cb->Control.Spin.SetStringValue(m_Handle->addonData, m_ControlHandle, value.c_str());
  }

  inline std::string CAddonGUIControlSpin::GetStringValue() const
  {
    std::string text;
    text.resize(1024);
    unsigned int size = (unsigned int)text.capacity();
    m_cb->Control.Spin.GetStringValue(m_Handle->addonData, m_ControlHandle, text[0], size);
    text.resize(size);
    text.shrink_to_fit();
    return text;
  }

  inline void CAddonGUIControlSpin::SetIntRange(int start, int end)
  {
    m_cb->Control.Spin.SetIntRange(m_Handle->addonData, m_ControlHandle, start, end);
  }

  inline void CAddonGUIControlSpin::SetIntValue(int value)
  {
    m_cb->Control.Spin.SetIntValue(m_Handle->addonData, m_ControlHandle, value);
  }

  inline int CAddonGUIControlSpin::GetIntValue() const
  {
    return m_cb->Control.Spin.GetIntValue(m_Handle->addonData, m_ControlHandle);
  }

  inline void CAddonGUIControlSpin::SetFloatRange(float start, float end)
  {
    m_cb->Control.Spin.SetFloatRange(m_Handle->addonData, m_ControlHandle,start ,end);
  }

  inline void CAddonGUIControlSpin::SetFloatValue(float value)
  {
    m_cb->Control.Spin.SetFloatValue(m_Handle->addonData, m_ControlHandle, value);
  }

  inline float CAddonGUIControlSpin::GetFloatValue() const
  {
    return m_cb->Control.Spin.GetFloatValue(m_Handle->addonData, m_ControlHandle);
  }

  inline void CAddonGUIControlSpin::SetFloatInterval(float interval)
  {
    m_cb->Control.Spin.SetFloatInterval(m_Handle->addonData, m_ControlHandle, interval);
  }

}; /* namespace V2 */
}; /* namespace GUILIB */
