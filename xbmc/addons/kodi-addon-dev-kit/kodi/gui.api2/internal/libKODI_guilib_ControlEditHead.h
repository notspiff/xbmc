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

namespace GUILIB
{
namespace V2
{
extern "C"
{

  class CAddonGUIWindow;
  class CAddonGUIControlEdit;

  typedef void GUIControl_Edit_SetVisible
      (void         *addonData,
       GUIHANDLE     handle,
       bool          visible);

  typedef void GUIControl_Edit_SetEnabled
      (void         *addonData,
       GUIHANDLE     handle,
       bool          enabled);

  typedef void GUIControl_Edit_SetLabel
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *label);

  typedef void GUIControl_Edit_GetLabel
      (void         *addonData,
       GUIHANDLE     handle,
       char         &label,
       unsigned int &iMaxStringSize);

  typedef void GUIControl_Edit_SetText
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *text);

  typedef void GUIControl_Edit_GetText
      (void         *addonData,
       GUIHANDLE     handle,
       char         &text,
       unsigned int &iMaxStringSize);

  typedef void GUIControl_Edit_SetCursorPosition
      (void         *addonData,
       GUIHANDLE     handle,
       unsigned int  iPosition);

  typedef unsigned int GUIControl_Edit_GetCursorPosition
      (void         *addonData,
       GUIHANDLE     handle);

  typedef void GUIControl_Edit_SetInputType
      (void         *addonData,
       GUIHANDLE     handle,
       AddonGUIInputType type,
       const char   *heading);

  typedef struct CB_GUILib_Control_Edit
  {
    GUIControl_Edit_SetVisible*        SetVisible;
    GUIControl_Edit_SetEnabled*        SetEnabled;

    GUIControl_Edit_SetLabel*          SetLabel;
    GUIControl_Edit_GetLabel*          GetLabel;
    GUIControl_Edit_SetText*           SetText;
    GUIControl_Edit_GetText*           GetText;
    GUIControl_Edit_SetCursorPosition* SetCursorPosition;
    GUIControl_Edit_GetCursorPosition* GetCursorPosition;
    GUIControl_Edit_SetInputType*      SetInputType;
  } CB_GUILib_Control_Edit;

  #define IMPL_GUI_EDIT_CONTROL                 \
    private:                                    \
      CAddonGUIWindow*  m_Window;               \
      int               m_ControlId;            \
      GUIHANDLE         m_ControlHandle;        \
      ADDON::AddonCB*   m_Handle;               \
      CB_GUILib*        m_cb;

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
