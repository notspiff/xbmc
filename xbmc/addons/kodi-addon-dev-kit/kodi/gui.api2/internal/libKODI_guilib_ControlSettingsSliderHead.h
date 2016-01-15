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
  class CAddonGUIControlSettingsSlider;

  typedef void GUIControl_SettingsSlider_SetVisible(
       void         *addonData,
       GUIHANDLE     handle,
       bool          yesNo);

  typedef void GUIControl_SettingsSlider_SetEnabled(
       void         *addonData,
       GUIHANDLE     handle,
       bool          yesNo);

  typedef void GUIControl_SettingsSlider_SetText(
       void         *addonData,
       GUIHANDLE     handle,
       const char   *label);

  typedef void GUIControl_SettingsSlider_Reset(
       void         *addonData,
       GUIHANDLE     handle);

  typedef void GUIControl_SettingsSlider_SetIntRange(
       void         *addonData,
       GUIHANDLE     handle,
       int           iStart,
       int           iEnd);

  typedef void GUIControl_SettingsSlider_SetIntValue(
       void         *addonData,
       GUIHANDLE     handle,
       int           iValue);

  typedef int  GUIControl_SettingsSlider_GetIntValue(
       void         *addonData,
       GUIHANDLE     handle);

  typedef void GUIControl_SettingsSlider_SetIntInterval(
       void         *addonData,
       GUIHANDLE     handle,
       int           iInterval);

  typedef void GUIControl_SettingsSlider_SetPercentage(
       void         *addonData,
       GUIHANDLE     handle,
       float         fPercent);

  typedef float GUIControl_SettingsSlider_GetPercentage(
       void         *addonData,
       GUIHANDLE     handle);

  typedef void GUIControl_SettingsSlider_SetFloatRange(
       void         *addonData,
       GUIHANDLE     handle,
       float         fStart,
       float         fEnd);

  typedef void GUIControl_SettingsSlider_SetFloatValue(
       void         *addonData,
       GUIHANDLE     handle,
       float         fValue);

  typedef float GUIControl_SettingsSlider_GetFloatValue(
       void         *addonData,
       GUIHANDLE     handle);

  typedef void GUIControl_SettingsSlider_SetFloatInterval(
       void         *addonData,
       GUIHANDLE     handle,
       float         fInterval);

  typedef struct CB_GUILib_Control_SettingsSlider
  {
    GUIControl_SettingsSlider_SetVisible*          SetVisible;
    GUIControl_SettingsSlider_SetEnabled*          SetEnabled;

    GUIControl_SettingsSlider_SetText*             SetText;
    GUIControl_SettingsSlider_Reset*               Reset;

    GUIControl_SettingsSlider_SetIntRange*         SetIntRange;
    GUIControl_SettingsSlider_SetIntValue*         SetIntValue;
    GUIControl_SettingsSlider_GetIntValue*         GetIntValue;
    GUIControl_SettingsSlider_SetIntInterval*      SetIntInterval;

    GUIControl_SettingsSlider_SetPercentage*       SetPercentage;
    GUIControl_SettingsSlider_GetPercentage*       GetPercentage;

    GUIControl_SettingsSlider_SetFloatRange*       SetFloatRange;
    GUIControl_SettingsSlider_SetFloatValue*       SetFloatValue;
    GUIControl_SettingsSlider_GetFloatValue*       GetFloatValue;
    GUIControl_SettingsSlider_SetFloatInterval*    SetFloatInterval;
  } CB_GUILib_Control_SettingsSlider;

  #define IMPL_GUI_SETTINGS_SLIDER_CONTROL      \
    private:                                    \
      CAddonGUIWindow*  m_Window;               \
      int               m_ControlId;            \
      GUIHANDLE         m_ControlHandle;        \
      ADDON::AddonCB*   m_Handle;               \
      CB_GUILib*        m_cb;

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
