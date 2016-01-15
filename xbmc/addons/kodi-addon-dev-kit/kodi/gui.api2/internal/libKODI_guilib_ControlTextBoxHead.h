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
  class CAddonGUIControlTextBox;

  typedef void GUIControl_TextBox_SetVisible(
       void         *addonData,
       GUIHANDLE     spinhandle,
       bool          visible);

  typedef void GUIControl_TextBox_Reset(
       void         *addonData,
       GUIHANDLE     handle);

  typedef void GUIControl_TextBox_SetText(
       void         *addonData,
       GUIHANDLE     handle,
       const char*   text);

  typedef void GUIControl_TextBox_GetText(
       void         *addonData,
       GUIHANDLE     handle,
       char         &text,
       unsigned int &iMaxStringSize);

  typedef void GUIControl_TextBox_Scroll(
       void         *addonData,
       GUIHANDLE     handle,
       unsigned int  scroll);

  typedef void GUIControl_TextBox_SetAutoScrolling(
       void         *addonData,
       GUIHANDLE     handle,
       int           delay,
       int           time,
       int           repeat);

  typedef struct CB_GUILib_Control_TextBox
  {
    GUIControl_TextBox_SetVisible*          SetVisible;
    GUIControl_TextBox_Reset*               Reset;
    GUIControl_TextBox_SetText*             SetText;
    GUIControl_TextBox_GetText*             GetText;
    GUIControl_TextBox_Scroll*              Scroll;
    GUIControl_TextBox_SetAutoScrolling*    SetAutoScrolling;
  } CB_GUILib_Control_TextBox;

  #define IMPL_GUI_TEXTBOX_CONTROL              \
    private:                                    \
      CAddonGUIWindow*  m_Window;               \
      int               m_ControlId;            \
      GUIHANDLE         m_ControlHandle;        \
      ADDON::AddonCB*   m_Handle;               \
      CB_GUILib*        m_cb;

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
