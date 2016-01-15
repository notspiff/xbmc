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

  inline CAddonGUIDialogProgress::CAddonGUIDialogProgress()
   : m_Handle(CGUILib::g_libKODI_Internal->m_Handle),
     m_cb(CGUILib::g_libKODI_Internal->m_Callbacks)
  {
    if (m_Handle && m_cb)
    {
      m_DialogHandle = m_cb->Dialogs.Progress.New(m_Handle->addonData);
      if (!m_DialogHandle)
        fprintf(stderr, "libKODI_guilib-ERROR: CAddonGUIDialogProgress can't create window class from Kodi !!!\n"); \
    }
  }

  inline CAddonGUIDialogProgress::~CAddonGUIDialogProgress()
  {
    if (m_Handle && m_cb && m_DialogHandle)
    {
      m_cb->Dialogs.Progress.Delete(m_Handle->addonData, m_DialogHandle);
      m_DialogHandle = nullptr;
    }
  }

  inline void CAddonGUIDialogProgress::Open()
  {
    m_cb->Dialogs.Progress.Open(m_Handle->addonData, m_DialogHandle);
  }

  inline void CAddonGUIDialogProgress::SetHeading(const std::string& title)
  {
    m_cb->Dialogs.Progress.SetHeading(m_Handle->addonData, m_DialogHandle, title.c_str());
  }

  inline void CAddonGUIDialogProgress::SetLine(unsigned int iLine, const std::string& line)
  {
    m_cb->Dialogs.Progress.SetLine(m_Handle->addonData, m_DialogHandle, iLine, line.c_str());
  }

  inline void CAddonGUIDialogProgress::SetCanCancel(bool bCanCancel)
  {
    m_cb->Dialogs.Progress.SetCanCancel(m_Handle->addonData, m_DialogHandle, bCanCancel);
  }

  inline bool CAddonGUIDialogProgress::IsCanceled() const
  {
    return m_cb->Dialogs.Progress.IsCanceled(m_Handle->addonData, m_DialogHandle);
  }

  inline void CAddonGUIDialogProgress::SetPercentage(int iPercentage)
  {
    m_cb->Dialogs.Progress.SetPercentage(m_Handle->addonData, m_DialogHandle, iPercentage);
  }

  inline int CAddonGUIDialogProgress::GetPercentage() const
  {
    return m_cb->Dialogs.Progress.GetPercentage(m_Handle->addonData, m_DialogHandle);
  }

  inline void CAddonGUIDialogProgress::ShowProgressBar(bool bOnOff)
  {
    m_cb->Dialogs.Progress.ShowProgressBar(m_Handle->addonData, m_DialogHandle, bOnOff);
  }

  inline void CAddonGUIDialogProgress::SetProgressMax(int iMax)
  {
    m_cb->Dialogs.Progress.SetProgressMax(m_Handle->addonData, m_DialogHandle, iMax);
  }

  inline void CAddonGUIDialogProgress::SetProgressAdvance(int nSteps)
  {
    m_cb->Dialogs.Progress.SetProgressAdvance(m_Handle->addonData, m_DialogHandle, nSteps);
  }

  inline bool CAddonGUIDialogProgress::Abort()
  {
    return m_cb->Dialogs.Progress.Abort(m_Handle->addonData, m_DialogHandle);
  }

}; /* namespace V2 */
}; /* namespace GUILIB */
