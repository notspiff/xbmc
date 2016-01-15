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
#include "guilib/GUISliderControl.h"
#include "guilib/GUIWindowManager.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIControlSlider.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{
extern "C"
{

void CAddonGUI_Control_Slider::Init(CB_GUILib *callbacks)
{
  callbacks->Control.Slider.SetVisible        = CAddonGUI_Control_Slider::SetVisible;
  callbacks->Control.Slider.SetEnabled        = CAddonGUI_Control_Slider::SetEnabled;

  callbacks->Control.Slider.Reset             = CAddonGUI_Control_Slider::Reset;
  callbacks->Control.Slider.GetDescription    = CAddonGUI_Control_Slider::GetDescription;

  callbacks->Control.Slider.SetIntRange       = CAddonGUI_Control_Slider::SetIntRange;
  callbacks->Control.Slider.SetIntValue       = CAddonGUI_Control_Slider::SetIntValue;
  callbacks->Control.Slider.GetIntValue       = CAddonGUI_Control_Slider::GetIntValue;
  callbacks->Control.Slider.SetIntInterval    = CAddonGUI_Control_Slider::SetIntInterval;

  callbacks->Control.Slider.SetPercentage     = CAddonGUI_Control_Slider::SetPercentage;
  callbacks->Control.Slider.GetPercentage     = CAddonGUI_Control_Slider::GetPercentage;

  callbacks->Control.Slider.SetFloatRange     = CAddonGUI_Control_Slider::SetFloatRange;
  callbacks->Control.Slider.SetFloatValue     = CAddonGUI_Control_Slider::SetFloatValue;
  callbacks->Control.Slider.GetFloatValue     = CAddonGUI_Control_Slider::GetFloatValue;
  callbacks->Control.Slider.SetFloatInterval  = CAddonGUI_Control_Slider::SetFloatInterval;
}

void CAddonGUI_Control_Slider::SetVisible(void *addonData, GUIHANDLE handle, bool visible)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Slider - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUISliderControl*>(handle)->SetVisible(visible);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Slider::SetEnabled(void *addonData, GUIHANDLE handle, bool enabled)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Slider - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUISliderControl*>(handle)->SetEnabled(enabled);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Slider::Reset(void *addonData, GUIHANDLE handle)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Slider - %s - invalid handler data", __FUNCTION__);

    CGUISliderControl* pControl = static_cast<CGUISliderControl*>(handle);

    CGUIMessage msg(GUI_MSG_LABEL_RESET, pControl->GetParentID(), pControl->GetID());
    g_windowManager.SendThreadMessage(msg, pControl->GetParentID());
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Slider::GetDescription(void *addonData, GUIHANDLE handle, char &label, unsigned int &iMaxStringSize)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Slider - %s - invalid handler data", __FUNCTION__);

    std::string text = static_cast<CGUISliderControl*>(handle)->GetDescription();
    strncpy(&label, text.c_str(), iMaxStringSize);
    iMaxStringSize = text.length();
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Slider::SetIntRange(void *addonData, GUIHANDLE handle, int iStart, int iEnd)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Slider - %s - invalid handler data", __FUNCTION__);

    CGUISliderControl* pControl = static_cast<CGUISliderControl *>(handle);
    pControl->SetType(SLIDER_CONTROL_TYPE_INT);
    pControl->SetRange(iStart, iEnd);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Slider::SetIntValue(void *addonData, GUIHANDLE handle, int iValue)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Slider - %s - invalid handler data", __FUNCTION__);

    CGUISliderControl* pControl = static_cast<CGUISliderControl *>(handle);
    pControl->SetType(SLIDER_CONTROL_TYPE_INT);
    pControl->SetIntValue(iValue);
  }
  HANDLE_ADDON_EXCEPTION
}

int CAddonGUI_Control_Slider::GetIntValue(void *addonData, GUIHANDLE handle)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Slider - %s - invalid handler data", __FUNCTION__);

    return static_cast<CGUISliderControl*>(handle)->GetIntValue();
  }
  HANDLE_ADDON_EXCEPTION

  return 0;
}

void CAddonGUI_Control_Slider::SetIntInterval(void *addonData, GUIHANDLE handle, int iInterval)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Slider - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUISliderControl*>(handle)->SetIntInterval(iInterval);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Slider::SetPercentage(void *addonData, GUIHANDLE handle, float fPercent)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Slider - %s - invalid handler data", __FUNCTION__);

    CGUISliderControl* pControl = static_cast<CGUISliderControl *>(handle);
    pControl->SetType(SLIDER_CONTROL_TYPE_PERCENTAGE);
    pControl->SetPercentage(fPercent);
  }
  HANDLE_ADDON_EXCEPTION
}

float CAddonGUI_Control_Slider::GetPercentage(void *addonData, GUIHANDLE handle)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Slider - %s - invalid handler data", __FUNCTION__);

    return static_cast<CGUISliderControl*>(handle)->GetPercentage();
  }
  HANDLE_ADDON_EXCEPTION

  return 0.0f;
}

void CAddonGUI_Control_Slider::SetFloatRange(void *addonData, GUIHANDLE handle, float fStart, float fEnd)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Slider - %s - invalid handler data", __FUNCTION__);

    CGUISliderControl* pControl = static_cast<CGUISliderControl *>(handle);
    pControl->SetType(SLIDER_CONTROL_TYPE_FLOAT);
    pControl->SetFloatRange(fStart, fEnd);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Slider::SetFloatValue(void *addonData, GUIHANDLE handle, float iValue)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Slider - %s - invalid handler data", __FUNCTION__);

    CGUISliderControl* pControl = static_cast<CGUISliderControl *>(handle);
    pControl->SetType(SLIDER_CONTROL_TYPE_FLOAT);
    pControl->SetFloatValue(iValue);
  }
  HANDLE_ADDON_EXCEPTION
}

float CAddonGUI_Control_Slider::GetFloatValue(void *addonData, GUIHANDLE handle)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Slider - %s - invalid handler data", __FUNCTION__);

    return static_cast<CGUISliderControl*>(handle)->GetFloatValue();
  }
  HANDLE_ADDON_EXCEPTION

  return 0.0f;
}

void CAddonGUI_Control_Slider::SetFloatInterval(void *addonData, GUIHANDLE handle, float fInterval)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Slider - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUISliderControl*>(handle)->SetFloatInterval(fInterval);
  }
  HANDLE_ADDON_EXCEPTION
}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
