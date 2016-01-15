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

  inline CAddonGUIDialogExtendedProgress::CAddonGUIDialogExtendedProgress(const std::string& title)
   : m_Handle((ADDON::AddonCB*)CGUILib::g_libKODI_Internal->m_Handle),
     m_cb(CGUILib::g_libKODI_Internal->m_Callbacks)
  {
    if (m_Handle && m_cb)
    {
      m_DialogHandle = m_cb->Dialogs.ExtendedProgress.New(m_Handle->addonData, title.c_str());
      if (!m_DialogHandle)
        fprintf(stderr, "libKODI_guilib-ERROR: CAddonGUIDialogExtendedProgress can't create window class from Kodi !!!\n");
    }
  }

  inline CAddonGUIDialogExtendedProgress::~CAddonGUIDialogExtendedProgress()
  {
    if (m_Handle && m_cb && m_DialogHandle)
    {
      m_cb->Dialogs.ExtendedProgress.Delete(m_Handle->addonData, m_DialogHandle);
      m_DialogHandle = nullptr;
    }
  }

  inline std::string CAddonGUIDialogExtendedProgress::Title() const
  {
    std::string text;
    text.resize(1024);
    unsigned int size = (unsigned int)text.capacity();
    m_cb->Dialogs.ExtendedProgress.Title(m_Handle->addonData, m_DialogHandle, text[0], size);
    text.resize(size);
    text.shrink_to_fit();
    return text;
  }

  inline void CAddonGUIDialogExtendedProgress::SetTitle(const std::string& title)
  {
    m_cb->Dialogs.ExtendedProgress.SetTitle(m_Handle->addonData, m_DialogHandle, title.c_str());
  }

  inline std::string CAddonGUIDialogExtendedProgress::Text() const
  {
    std::string text;
    text.resize(1024);
    unsigned int size = (unsigned int)text.capacity();
    m_cb->Dialogs.ExtendedProgress.Text(m_Handle->addonData, m_DialogHandle, text[0], size);
    text.resize(size);
    text.shrink_to_fit();
    return text;
  }

  inline void CAddonGUIDialogExtendedProgress::SetText(const std::string& text)
  {
    m_cb->Dialogs.ExtendedProgress.SetText(m_Handle->addonData, m_DialogHandle, text.c_str());
  }

  inline bool CAddonGUIDialogExtendedProgress::IsFinished() const
  {
    return m_cb->Dialogs.ExtendedProgress.IsFinished(m_Handle->addonData, m_DialogHandle);
  }

  inline void CAddonGUIDialogExtendedProgress::MarkFinished()
  {
    m_cb->Dialogs.ExtendedProgress.MarkFinished(m_Handle->addonData, m_DialogHandle);
  }

  inline float CAddonGUIDialogExtendedProgress::Percentage() const
  {
    return m_cb->Dialogs.ExtendedProgress.Percentage(m_Handle->addonData, m_DialogHandle);
  }

  inline void CAddonGUIDialogExtendedProgress::SetPercentage(float fPercentage)
  {
    m_cb->Dialogs.ExtendedProgress.SetPercentage(m_Handle->addonData, m_DialogHandle, fPercentag
  }

  inline void CAddonGUIDialogExtendedProgress::SetProgress(int currentItem, int itemCount)
  {
    m_cb->Dialogs.ExtendedProgress.SetProgress(m_Handle->addonData, m_DialogHandle, currentItem,
  }

}; /* namespace V2 */
}; /* namespace GUILIB */
