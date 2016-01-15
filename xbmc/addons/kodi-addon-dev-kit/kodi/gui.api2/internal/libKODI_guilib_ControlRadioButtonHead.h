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
  class CAddonGUIControlRadioButton;

  typedef void GUIControl_RadioButton_SetVisible
      (void       *addonData,
       GUIHANDLE   handle,
       bool        yesNo);

  typedef void GUIControl_RadioButton_SetEnabled(
       void*         addonData,
       GUIHANDLE     spinhandle,
       bool          enabled);

  typedef void GUIControl_RadioButton_SetLabel
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *text);

  typedef void GUIControl_RadioButton_GetLabel
      (void         *addonData,
       GUIHANDLE     handle,
       char         &text,
       unsigned int &iMaxStringSize);

  typedef void GUIControl_RadioButton_SetSelected
      (void       *addonData,
       GUIHANDLE   handle,
       bool        yesNo);

  typedef bool GUIControl_RadioButton_IsSelected
      (void       *addonData,
       GUIHANDLE   handle);

  typedef struct CB_GUILib_Control_RadioButton
  {
    GUIControl_RadioButton_SetVisible*   SetVisible;
    GUIControl_RadioButton_SetEnabled*   SetEnabled;
    GUIControl_RadioButton_SetLabel*     SetLabel;
    GUIControl_RadioButton_GetLabel*     GetLabel;
    GUIControl_RadioButton_SetSelected*  SetSelected;
    GUIControl_RadioButton_IsSelected*   IsSelected;
  } CB_GUILib_Control_RadioButton;

  #define IMPL_GUI_RADIO_BUTTON_CONTROL         \
    private:                                    \
      CAddonGUIWindow*  m_Window;               \
      int               m_ControlId;            \
      GUIHANDLE         m_ControlHandle;        \
      ADDON::AddonCB*   m_Handle;               \
      CB_GUILib*        m_cb;

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
