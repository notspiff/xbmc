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

#include "addons/Addon.h"
#include "addons/binary/ExceptionHandling.h"
#include "addons/binary/callbacks/AddonCallbacks.h"
#include "guilib/GUISettingsSliderControl.h"
#include "guilib/GUIWindowManager.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIControlSettingsSlider.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{
extern "C"
{

void CAddonGUI_Control_SettingsSlider::Init(CB_GUILib *callbacks)
{
  callbacks->Control.SettingsSlider.SetVisible            = CAddonGUI_Control_SettingsSlider::SetVisible;
  callbacks->Control.SettingsSlider.SetEnabled            = CAddonGUI_Control_SettingsSlider::SetEnabled;

  callbacks->Control.SettingsSlider.SetText               = CAddonGUI_Control_SettingsSlider::SetText;
  callbacks->Control.SettingsSlider.Reset                 = CAddonGUI_Control_SettingsSlider::Reset;

  callbacks->Control.SettingsSlider.SetIntRange           = CAddonGUI_Control_SettingsSlider::SetIntRange;
  callbacks->Control.SettingsSlider.SetIntValue           = CAddonGUI_Control_SettingsSlider::SetIntValue;
  callbacks->Control.SettingsSlider.GetIntValue           = CAddonGUI_Control_SettingsSlider::GetIntValue;
  callbacks->Control.SettingsSlider.SetIntInterval        = CAddonGUI_Control_SettingsSlider::SetIntInterval;

  callbacks->Control.SettingsSlider.SetPercentage         = CAddonGUI_Control_SettingsSlider::SetPercentage;
  callbacks->Control.SettingsSlider.GetPercentage         = CAddonGUI_Control_SettingsSlider::GetPercentage;

  callbacks->Control.SettingsSlider.SetFloatRange         = CAddonGUI_Control_SettingsSlider::SetFloatRange;
  callbacks->Control.SettingsSlider.SetFloatValue         = CAddonGUI_Control_SettingsSlider::SetFloatValue;
  callbacks->Control.SettingsSlider.GetFloatValue         = CAddonGUI_Control_SettingsSlider::GetFloatValue;
  callbacks->Control.SettingsSlider.SetFloatInterval      = CAddonGUI_Control_SettingsSlider::SetFloatInterval;
}

void CAddonGUI_Control_SettingsSlider::SetVisible(void *addonData, GUIHANDLE handle, bool visible)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_SettingsSlider - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUISettingsSliderControl*>(handle)->SetVisible(visible);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_SettingsSlider::SetEnabled(void *addonData, GUIHANDLE handle, bool enabled)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_SettingsSlider - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUISettingsSliderControl*>(handle)->SetEnabled(enabled);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_SettingsSlider::SetText(void *addonData, GUIHANDLE handle, const char *text)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_SettingsSlider - %s - invalid handler data", __FUNCTION__);

    CGUISettingsSliderControl* pControl = static_cast<CGUISettingsSliderControl*>(handle);

    // create message
    CGUIMessage msg(GUI_MSG_LABEL_SET, pControl->GetParentID(), pControl->GetID());
    msg.SetLabel(text);

    // send message
    g_windowManager.SendThreadMessage(msg, pControl->GetParentID());
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_SettingsSlider::Reset(void *addonData, GUIHANDLE handle)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_SettingsSlider - %s - invalid handler data", __FUNCTION__);

    CGUISettingsSliderControl* pControl = static_cast<CGUISettingsSliderControl*>(handle);

    CGUIMessage msg(GUI_MSG_LABEL_RESET, pControl->GetParentID(), pControl->GetID());
    g_windowManager.SendThreadMessage(msg, pControl->GetParentID());
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_SettingsSlider::SetIntRange(void *addonData, GUIHANDLE handle, int iStart, int iEnd)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_SettingsSlider - %s - invalid handler data", __FUNCTION__);

    CGUISettingsSliderControl* pControl = static_cast<CGUISettingsSliderControl *>(handle);
    pControl->SetType(SLIDER_CONTROL_TYPE_INT);
    pControl->SetRange(iStart, iEnd);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_SettingsSlider::SetIntValue(void *addonData, GUIHANDLE handle, int iValue)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_SettingsSlider - %s - invalid handler data", __FUNCTION__);

    CGUISettingsSliderControl* pControl = static_cast<CGUISettingsSliderControl *>(handle);
    pControl->SetType(SLIDER_CONTROL_TYPE_INT);
    pControl->SetIntValue(iValue);
  }
  HANDLE_ADDON_EXCEPTION
}

int CAddonGUI_Control_SettingsSlider::GetIntValue(void *addonData, GUIHANDLE handle)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_SettingsSlider - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUISettingsSliderControl*>(handle)->GetIntValue();
  }
  HANDLE_ADDON_EXCEPTION

  return -1;
}

void CAddonGUI_Control_SettingsSlider::SetIntInterval(void *addonData, GUIHANDLE handle, int iInterval)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_SettingsSlider - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUISettingsSliderControl*>(handle)->SetIntInterval(iInterval);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_SettingsSlider::SetPercentage(void *addonData, GUIHANDLE handle, float fPercent)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_SettingsSlider - %s - invalid handler data", __FUNCTION__);

    CGUISettingsSliderControl* pControl = static_cast<CGUISettingsSliderControl *>(handle);
    pControl->SetType(SLIDER_CONTROL_TYPE_PERCENTAGE);
    pControl->SetPercentage(fPercent);
  }
  HANDLE_ADDON_EXCEPTION
}

float CAddonGUI_Control_SettingsSlider::GetPercentage(void *addonData, GUIHANDLE handle)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_SettingsSlider - %s - invalid handler data", __FUNCTION__);

    return static_cast<CGUISettingsSliderControl*>(handle)->GetPercentage();
  }
  HANDLE_ADDON_EXCEPTION

  return 0.0f;
}

void CAddonGUI_Control_SettingsSlider::SetFloatRange(void *addonData, GUIHANDLE handle, float fStart, float fEnd)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_SettingsSlider - %s - invalid handler data", __FUNCTION__);

    CGUISettingsSliderControl* pControl = static_cast<CGUISettingsSliderControl *>(handle);
    pControl->SetType(SLIDER_CONTROL_TYPE_FLOAT);
    pControl->SetFloatRange(fStart, fEnd);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_SettingsSlider::SetFloatValue(void *addonData, GUIHANDLE handle, float fValue)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_SettingsSlider - %s - invalid handler data", __FUNCTION__);

    CGUISettingsSliderControl* pControl = static_cast<CGUISettingsSliderControl *>(handle);
    pControl->SetType(SLIDER_CONTROL_TYPE_FLOAT);
    pControl->SetFloatValue(fValue);
  }
  HANDLE_ADDON_EXCEPTION
}

float CAddonGUI_Control_SettingsSlider::GetFloatValue(void *addonData, GUIHANDLE handle)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_SettingsSlider - %s - invalid handler data", __FUNCTION__);

    return static_cast<CGUISettingsSliderControl*>(handle)->GetFloatValue();
  }
  HANDLE_ADDON_EXCEPTION

  return 0.0f;
}

void CAddonGUI_Control_SettingsSlider::SetFloatInterval(void *addonData, GUIHANDLE handle, float fInterval)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_SettingsSlider - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUISettingsSliderControl*>(handle)->SetFloatInterval(fInterval);
  }
  HANDLE_ADDON_EXCEPTION
}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
