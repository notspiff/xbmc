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
  class CAddonGUIControlFadeLabel;

  typedef void GUIControl_FadeLabel_SetVisible(
       void         *addonData,
       GUIHANDLE     handle,
       bool          visible);

  typedef void GUIControl_FadeLabel_AddLabel(
       void         *addonData,
       GUIHANDLE     handle,
       const char   *text);

  typedef void GUIControl_FadeLabel_GetLabel(
       void         *addonData,
       GUIHANDLE     handle,
       char         &text,
       unsigned int &iMaxStringSize);

  typedef void GUIControl_FadeLabel_SetScrolling(
       void*         addonData,
       GUIHANDLE     handle,
       bool          scroll);

  typedef void GUIControl_FadeLabel_Reset(
       void*         addonData, 
       GUIHANDLE     handle);

  typedef struct CB_GUILib_Control_FadeLabel
  {
    GUIControl_FadeLabel_SetVisible*       SetVisible;
    GUIControl_FadeLabel_AddLabel*         AddLabel;
    GUIControl_FadeLabel_GetLabel*         GetLabel;
    GUIControl_FadeLabel_SetScrolling*     SetScrolling;
    GUIControl_FadeLabel_Reset*            Reset;
  } CB_GUILib_Control_FadeLabel;

  #define IMPL_GUI_FADELABEL_CONTROL            \
    private:                                    \
      CAddonGUIWindow*  m_Window;               \
      int               m_ControlId;            \
      GUIHANDLE         m_ControlHandle;        \
      ADDON::AddonCB*   m_Handle;               \
      CB_GUILib*        m_cb;

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
