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

  inline CAddonGUIControlFadeLabel::CAddonGUIControlFadeLabel(CAddonGUIWindow* window, int controlId)
   : m_Window(window),
     m_ControlId(controlId),
     m_Handle((ADDON::AddonCB*)CGUILib::g_libKODI_Internal->m_Handle),
     m_cb(CGUILib::g_libKODI_Internal->m_Callbacks)
  {
    if (m_Handle && m_cb)
    {
      m_ControlHandle = m_cb->Window.GetControl_FadeLabel(m_Handle->addonData, m_Window->m_WindowHandle, controlId);
      if (!m_ControlHandle)
        fprintf(stderr, "libKODI_guilib-ERROR: CAddonGUIControlFadeLabel can't create control class from Kodi !!!\n");
    }
  }

  inline CAddonGUIControlFadeLabel::~CAddonGUIControlFadeLabel()
  {
  }

  inline void CAddonGUIControlFadeLabel::SetVisible(bool visible)
  {
    m_cb->Control.FadeLabel.SetVisible(m_Handle->addonData, m_ControlHandle, visible);
  }

  inline void CAddonGUIControlFadeLabel::AddLabel(const std::string& text)
  {
    m_cb->Control.FadeLabel.AddLabel(m_Handle->addonData, m_ControlHandle, text.c_str());
  }

  inline std::string CAddonGUIControlFadeLabel::GetLabel() const
  {
    std::string text;
    text.resize(1024);
    unsigned int size = (unsigned int)text.capacity();
    m_cb->Control.FadeLabel.GetLabel(m_Handle->addonData, m_ControlHandle, text[0], size);
    text.resize(size);
    text.shrink_to_fit();
    return text;
  }

  inline void CAddonGUIControlFadeLabel::SetScrolling(bool scroll)
  {
    m_cb->Control.FadeLabel.SetScrolling(m_Handle->addonData, m_ControlHandle, scroll);
  }

  inline void CAddonGUIControlFadeLabel::Reset()
  {
    m_cb->Control.FadeLabel.Reset(m_Handle->addonData, m_ControlHandle);
  }

}; /* namespace V2 */
}; /* namespace GUILIB */
