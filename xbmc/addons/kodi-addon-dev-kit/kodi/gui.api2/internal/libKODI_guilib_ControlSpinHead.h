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
  class CAddonGUIControlSpin;

  typedef void GUIControl_Spin_SetVisible(
       void*         addonData,
       GUIHANDLE     spinhandle,
       bool          visible);

  typedef void GUIControl_Spin_SetEnabled(
       void*         addonData,
       GUIHANDLE     spinhandle,
       bool          enabled);

  typedef void GUIControl_Spin_SetText(
       void*         addonData,
       GUIHANDLE     spinhandle,
       const char*   text);

  typedef void GUIControl_Spin_Reset(
       void*         addonData,
       GUIHANDLE     spinhandle);

  typedef void GUIControl_Spin_SetType(
       void*         addonData,
       GUIHANDLE     handle,
       int           type);

  typedef void GUIControl_Spin_AddStringLabel(
       void*         addonData,
       GUIHANDLE     handle,
       const char*   label,
       const char*   value);

  typedef void GUIControl_Spin_SetStringValue(
       void*         addonData,
       GUIHANDLE     handle,
       const char*   value);

  typedef void GUIControl_Spin_GetStringValue(
       void*         addonData,
       GUIHANDLE     handle,
       char&         value,
       unsigned int& maxStringSize);

  typedef void GUIControl_Spin_AddIntLabel(
       void*         addonData,
       GUIHANDLE     handle,
       const char*   label,
       int           value);

  typedef void GUIControl_Spin_SetIntRange(
       void*         addonData,
       GUIHANDLE     handle,
       int           start,
       int           end);

  typedef void GUIControl_Spin_SetIntValue(
       void*         addonData,
       GUIHANDLE     handle,
       int           value);

  typedef int  GUIControl_Spin_GetIntValue(
       void*         addonData,
       GUIHANDLE     handle);

  typedef void GUIControl_Spin_SetFloatRange(
       void*         addonData,
       GUIHANDLE     handle,
       float         start,
       float         end);

  typedef void GUIControl_Spin_SetFloatValue(
       void*         addonData,
       GUIHANDLE     handle,
       float         value);

  typedef float GUIControl_Spin_GetFloatValue(
       void*         addonData,
       GUIHANDLE     handle);

  typedef void GUIControl_Spin_SetFloatInterval(
       void*         addonData,
       GUIHANDLE     handle,
       float         interval);

  typedef struct CB_GUILib_Control_Spin
  {
    GUIControl_Spin_SetVisible*          SetVisible;
    GUIControl_Spin_SetEnabled*          SetEnabled;

    GUIControl_Spin_SetText*             SetText;
    GUIControl_Spin_Reset*               Reset;
    GUIControl_Spin_SetType*             SetType;

    GUIControl_Spin_AddStringLabel*      AddStringLabel;
    GUIControl_Spin_SetStringValue*      SetStringValue;
    GUIControl_Spin_GetStringValue*      GetStringValue;

    GUIControl_Spin_AddIntLabel*         AddIntLabel;
    GUIControl_Spin_SetIntRange*         SetIntRange;
    GUIControl_Spin_SetIntValue*         SetIntValue;
    GUIControl_Spin_GetIntValue*         GetIntValue;

    GUIControl_Spin_SetFloatRange*       SetFloatRange;
    GUIControl_Spin_SetFloatValue*       SetFloatValue;
    GUIControl_Spin_GetFloatValue*       GetFloatValue;
    GUIControl_Spin_SetFloatInterval*    SetFloatInterval;
  } CB_GUILib_Control_Spin;

  #define IMPL_GUI_SPIN_CONTROL                 \
    private:                                    \
      CAddonGUIWindow*  m_Window;               \
      int               m_ControlId;            \
      GUIHANDLE         m_ControlHandle;        \
      ADDON::AddonCB*   m_Handle;               \
      CB_GUILib*        m_cb;

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
