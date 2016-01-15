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
  class CAddonGUIControlSlider;

  typedef void GUIControl_Slider_SetVisible(
       void         *addonData,
       GUIHANDLE     handle,
       bool          yesNo);

  typedef void GUIControl_Slider_SetEnabled(
       void         *addonData,
       GUIHANDLE     handle,
       bool          yesNo);

  typedef void GUIControl_Slider_Reset(
       void         *addonData,
       GUIHANDLE     handle);

  typedef void GUIControl_Slider_GetDescription(
       void         *addonData,
       GUIHANDLE     handle,
       char         &text,
       unsigned int &iMaxStringSize);

  typedef void GUIControl_Slider_SetIntRange(
       void         *addonData,
       GUIHANDLE     handle,
       int           start,
       int           end);

  typedef void GUIControl_Slider_SetIntValue(
       void         *addonData,
       GUIHANDLE     handle,
       int           value);

  typedef int  GUIControl_Slider_GetIntValue(
       void         *addonData,
       GUIHANDLE     handle);

  typedef void GUIControl_Slider_SetIntInterval(
       void         *addonData,
       GUIHANDLE     handle,
       int           interval);

  typedef void GUIControl_Slider_SetPercentage(
       void         *addonData,
       GUIHANDLE     handle,
       float         percent);

  typedef float GUIControl_Slider_GetPercentage(
       void         *addonData,
       GUIHANDLE     handle);

  typedef void GUIControl_Slider_SetFloatRange(
       void         *addonData,
       GUIHANDLE     handle,
       float         start,
       float         end);

  typedef void GUIControl_Slider_SetFloatValue(
       void         *addonData,
       GUIHANDLE     handle,
       float         value);

  typedef float GUIControl_Slider_GetFloatValue(
       void         *addonData,
       GUIHANDLE     handle);

  typedef void GUIControl_Slider_SetFloatInterval(
       void         *addonData,
       GUIHANDLE     handle,
       float         interval);

  typedef struct CB_GUILib_Control_Slider
  {
    GUIControl_Slider_SetVisible*        SetVisible;
    GUIControl_Slider_SetEnabled*        SetEnabled;

    GUIControl_Slider_Reset*             Reset;
    GUIControl_Slider_GetDescription*    GetDescription;

    GUIControl_Slider_SetIntRange*       SetIntRange;
    GUIControl_Slider_SetIntValue*       SetIntValue;
    GUIControl_Slider_GetIntValue*       GetIntValue;
    GUIControl_Slider_SetIntInterval*    SetIntInterval;

    GUIControl_Slider_SetPercentage*     SetPercentage;
    GUIControl_Slider_GetPercentage*     GetPercentage;

    GUIControl_Slider_SetFloatRange*     SetFloatRange;
    GUIControl_Slider_SetFloatValue*     SetFloatValue;
    GUIControl_Slider_GetFloatValue*     GetFloatValue;
    GUIControl_Slider_SetFloatInterval*  SetFloatInterval;
  } CB_GUILib_Control_Slider;

  #define IMPL_GUI_SLIDER_CONTROL               \
    private:                                    \
      CAddonGUIWindow*  m_Window;               \
      int               m_ControlId;            \
      GUIHANDLE         m_ControlHandle;        \
      ADDON::AddonCB*   m_Handle;               \
      CB_GUILib*        m_cb;

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
