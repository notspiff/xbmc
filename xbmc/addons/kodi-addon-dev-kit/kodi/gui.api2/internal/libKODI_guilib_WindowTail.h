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

  inline CAddonGUIWindow::CAddonGUIWindow(
          const std::string&          xmlFilename,
          const std::string&          defaultSkin,
          bool                        forceFallback,
          bool                        asDialog)
   : m_Handle((ADDON::AddonCB*)CGUILib::g_libKODI_Internal->m_Handle)
   , m_cb(CGUILib::g_libKODI_Internal->m_Callbacks)
  {
    if (m_Handle && m_cb)
    {
      m_WindowHandle = m_cb->Window.New(m_Handle->addonData, xmlFilename.c_str(),
                                        defaultSkin.c_str(), forceFallback, asDialog);
      if (!m_WindowHandle)
        fprintf(stderr, "libKODI_gui-ERROR: cGUIWindow can't create window class from Kodi !!!\n");

      m_cb->Window.SetCallbacks(m_Handle->addonData, m_WindowHandle, this,
                                OnInitCB, OnClickCB, OnFocusCB, OnActionCB);
    }
  }

  inline CAddonGUIWindow::~CAddonGUIWindow()
  {
    if (m_Handle && m_cb && m_WindowHandle)
    {
      m_cb->Window.Delete(m_Handle->addonData, m_WindowHandle);
      m_WindowHandle = NULL;
    }
  }

  inline bool CAddonGUIWindow::Show()
  {
    return m_cb->Window.Show(m_Handle->addonData, m_WindowHandle);
  }

  inline void CAddonGUIWindow::Close()
  {
    m_cb->Window.Close(m_Handle->addonData, m_WindowHandle);
  }

  inline void CAddonGUIWindow::DoModal()
  {
    m_cb->Window.DoModal(m_Handle->addonData, m_WindowHandle);
  }

  inline bool CAddonGUIWindow::SetFocusId(int iControlId)
  {
    return m_cb->Window.SetFocusId(m_Handle->addonData, m_WindowHandle, iControlId);
  }

  inline int CAddonGUIWindow::GetFocusId()
  {
    return m_cb->Window.GetFocusId(m_Handle->addonData, m_WindowHandle);
  }

  inline bool CAddonGUIWindow::SetCoordinateResolution(int res)
  {
    return m_cb->Window.SetCoordinateResolution(m_Handle->addonData, m_WindowHandle, res);
  }

  inline void CAddonGUIWindow::SetProperty(const std::string& key, const std::string& value)
  {
    m_cb->Window.SetProperty(m_Handle->addonData, m_WindowHandle, key.c_str(), value.c_str());
  }

  inline void CAddonGUIWindow::SetPropertyInt(const std::string& key, int value)
  {
    m_cb->Window.SetPropertyInt(m_Handle->addonData, m_WindowHandle, key.c_str(), value);
  }

  inline void CAddonGUIWindow::SetPropertyBool(const std::string& key, bool value)
  {
    m_cb->Window.SetPropertyBool(m_Handle->addonData, m_WindowHandle, key.c_str(), value);
  }

  inline void CAddonGUIWindow::SetPropertyDouble(const std::string& key, double value)
  {
    m_cb->Window.SetPropertyDouble(m_Handle->addonData, m_WindowHandle, key.c_str(), value);
  }

  inline std::string CAddonGUIWindow::GetProperty(const std::string& key) const
  {
    std::string label;
    label.resize(1024);
    unsigned int size = (unsigned int)label.capacity();
    m_cb->Window.GetProperty(m_Handle->addonData, m_WindowHandle, key.c_str(), label[0], size);
    label.resize(size);
    label.shrink_to_fit();
    return label.c_str();
  }

  inline int CAddonGUIWindow::GetPropertyInt(const std::string& key) const
  {
    return m_cb->Window.GetPropertyInt(m_Handle->addonData, m_WindowHandle, key.c_str());
  }

  inline bool CAddonGUIWindow::GetPropertyBool(const std::string& key) const
  {
    return m_cb->Window.GetPropertyBool(m_Handle->addonData, m_WindowHandle, key.c_str());
  }

  inline double CAddonGUIWindow::GetPropertyDouble(const std::string& key) const
  {
    return m_cb->Window.GetPropertyDouble(m_Handle->addonData, m_WindowHandle, key.c_str());
  }

  inline void CAddonGUIWindow::ClearProperties()
  {
    m_cb->Window.ClearProperties(m_Handle->addonData, m_WindowHandle);
  }

  inline int CAddonGUIWindow::GetListSize()
  {
    return m_cb->Window.GetListSize(m_Handle->addonData, m_WindowHandle);
  }

  inline void CAddonGUIWindow::ClearList()
  {
    m_cb->Window.ClearList(m_Handle->addonData, m_WindowHandle);
  }

  inline GUIHANDLE CAddonGUIWindow::AddStringItem(const std::string& name, int itemPosition)
  {
    return m_cb->Window.AddStringItem(m_Handle->addonData, m_WindowHandle, name.c_str(), itemPosition);
  }

  inline void CAddonGUIWindow::AddItem(GUIHANDLE item, int itemPosition)
  {
    m_cb->Window.AddItem(m_Handle->addonData, m_WindowHandle, item, itemPosition);
  }

  inline void CAddonGUIWindow::AddItem(CAddonGUIListItem *item, int itemPosition)
  {
    m_cb->Window.AddItem(m_Handle->addonData, m_WindowHandle, item->m_ListItemHandle, itemPosition);
  }

  inline void CAddonGUIWindow::RemoveItem(int itemPosition)
  {
    m_cb->Window.RemoveItem(m_Handle->addonData, m_WindowHandle, itemPosition);
  }

  inline GUIHANDLE CAddonGUIWindow::GetListItem(int listPos)
  {
    return m_cb->Window.GetListItem(m_Handle->addonData, m_WindowHandle, listPos);
  }

  inline void CAddonGUIWindow::SetCurrentListPosition(int listPos)
  {
    m_cb->Window.SetCurrentListPosition(m_Handle->addonData, m_WindowHandle, listPos);
  }

  inline int CAddonGUIWindow::GetCurrentListPosition()
  {
    return m_cb->Window.GetCurrentListPosition(m_Handle->addonData, m_WindowHandle);
  }

  inline void CAddonGUIWindow::SetControlLabel(int controlId, const std::string& label)
  {
    m_cb->Window.SetControlLabel(m_Handle->addonData, m_WindowHandle, controlId, label.c_str());
  }

  inline void CAddonGUIWindow::MarkDirtyRegion()
  {
    m_cb->Window.MarkDirtyRegion(m_Handle->addonData, m_WindowHandle);
  }

  /*!
   * Kodi to add-on override defination function to use if class becomes used
   * independet.
   */
  inline void CAddonGUIWindow::SetIndependentCallbacks(
    GUIHANDLE     cbhdl,
    bool          (*CBOnInit)  (GUIHANDLE cbhdl),
    bool          (*CBOnFocus) (GUIHANDLE cbhdl, int controlId),
    bool          (*CBOnClick) (GUIHANDLE cbhdl, int controlId),
    bool          (*CBOnAction)(GUIHANDLE cbhdl, int actionId))
  {
    if (!m_Handle || !m_cb || !cbhdl ||
        !CBOnInit || !CBOnFocus || !CBOnClick || !CBOnAction)
    {
        fprintf(stderr, "libKODI_gui-ERROR: SetIndependentCallbacks called with nullptr !!!\n");
        return;
    }

    m_cb->Window.SetCallbacks(m_Handle->addonData, m_WindowHandle, cbhdl,
                              CBOnInit, CBOnFocus, CBOnClick, CBOnAction);
  }

  /*!
   * Defined callback functions from Kodi to add-on, for use in parent / child system
   * (is private)!
   */

  inline bool CAddonGUIWindow::OnInitCB(GUIHANDLE cbhdl)
  {
    return static_cast<CAddonGUIWindow*>(cbhdl)->OnInit();
  }

  inline bool CAddonGUIWindow::OnClickCB(GUIHANDLE cbhdl, int controlId)
  {
    return static_cast<CAddonGUIWindow*>(cbhdl)->OnClick(controlId);
  }

  inline bool CAddonGUIWindow::OnFocusCB(GUIHANDLE cbhdl, int controlId)
  {
    return static_cast<CAddonGUIWindow*>(cbhdl)->OnFocus(controlId);
  }

  inline bool CAddonGUIWindow::OnActionCB(GUIHANDLE cbhdl, int actionId)
  {
    return static_cast<CAddonGUIWindow*>(cbhdl)->OnAction(actionId);
  }

}; /* namespace V2 */
}; /* namespace GUILIB */
