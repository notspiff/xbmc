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
#include "guilib/GUISpinControlEx.h"
#include "guilib/GUIWindowManager.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIControlSpin.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{
extern "C"
{

void CAddonGUI_Control_Spin::Init(CB_GUILib *callbacks)
{
  callbacks->Control.Spin.SetVisible        = CAddonGUI_Control_Spin::SetVisible;
  callbacks->Control.Spin.SetEnabled        = CAddonGUI_Control_Spin::SetEnabled;

  callbacks->Control.Spin.SetText           = CAddonGUI_Control_Spin::SetText;
  callbacks->Control.Spin.Reset             = CAddonGUI_Control_Spin::Reset;
  callbacks->Control.Spin.SetType           = CAddonGUI_Control_Spin::SetType;

  callbacks->Control.Spin.AddStringLabel    = CAddonGUI_Control_Spin::AddStringLabel;
  callbacks->Control.Spin.SetStringValue    = CAddonGUI_Control_Spin::SetStringValue;
  callbacks->Control.Spin.GetStringValue    = CAddonGUI_Control_Spin::GetStringValue;

  callbacks->Control.Spin.AddIntLabel       = CAddonGUI_Control_Spin::AddIntLabel;
  callbacks->Control.Spin.SetIntRange       = CAddonGUI_Control_Spin::SetIntRange;
  callbacks->Control.Spin.SetIntValue       = CAddonGUI_Control_Spin::SetIntValue;
  callbacks->Control.Spin.GetIntValue       = CAddonGUI_Control_Spin::GetIntValue;

  callbacks->Control.Spin.SetFloatRange     = CAddonGUI_Control_Spin::SetFloatRange;
  callbacks->Control.Spin.SetFloatValue     = CAddonGUI_Control_Spin::SetFloatValue;
  callbacks->Control.Spin.GetFloatValue     = CAddonGUI_Control_Spin::GetFloatValue;
  callbacks->Control.Spin.SetFloatInterval  = CAddonGUI_Control_Spin::SetFloatInterval;
}

void CAddonGUI_Control_Spin::SetVisible(void *addonData, GUIHANDLE handle, bool visible)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Spin - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUISpinControlEx*>(handle)->SetVisible(visible);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Spin::SetEnabled(void *addonData, GUIHANDLE handle, bool enabled)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Spin - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUISpinControlEx*>(handle)->SetEnabled(enabled);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Spin::SetText(void *addonData, GUIHANDLE handle, const char *text)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Spin - %s - invalid handler data", __FUNCTION__);

    CGUISpinControlEx* pControl = static_cast<CGUISpinControlEx*>(handle);

    // create message
    CGUIMessage msg(GUI_MSG_LABEL_SET, pControl->GetParentID(), pControl->GetID());
    msg.SetLabel(text);

    // send message
    g_windowManager.SendThreadMessage(msg, pControl->GetParentID());
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Spin::Reset(void *addonData, GUIHANDLE handle)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Spin - %s - invalid handler data", __FUNCTION__);

    CGUISpinControlEx* pControl = static_cast<CGUISpinControlEx*>(handle);

    CGUIMessage msg(GUI_MSG_LABEL_RESET, pControl->GetParentID(), pControl->GetID());
    g_windowManager.SendThreadMessage(msg, pControl->GetParentID());
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Spin::SetType(void *addonData, GUIHANDLE handle, int type)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Spin - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUISpinControlEx*>(handle)->SetType(type);
  }
  HANDLE_ADDON_EXCEPTION
}


void CAddonGUI_Control_Spin::AddStringLabel(void *addonData, GUIHANDLE handle, const char* label, const char* value)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Spin - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUISpinControlEx*>(handle)->AddLabel(std::string(label), std::string(value));
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Spin::SetStringValue(void *addonData, GUIHANDLE handle, const char* value)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Spin - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUISpinControlEx*>(handle)->SetStringValue(std::string(value));
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Spin::GetStringValue(void *addonData, GUIHANDLE handle, char &value, unsigned int &maxStringSize)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Spin - %s - invalid handler data", __FUNCTION__);

    std::string text = static_cast<CGUISpinControlEx*>(handle)->GetStringValue();
    strncpy(&value, text.c_str(), maxStringSize);
    maxStringSize = text.length();
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Spin::AddIntLabel(void *addonData, GUIHANDLE handle, const char* label, int value)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Spin - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUISpinControlEx*>(handle)->AddLabel(std::string(label), value);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Spin::SetIntRange(void *addonData, GUIHANDLE handle, int start, int end)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Spin - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUISpinControlEx*>(handle)->SetRange(start, end);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Spin::SetIntValue(void *addonData, GUIHANDLE handle, int value)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Spin - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUISpinControlEx*>(handle)->SetValue(value);
  }
  HANDLE_ADDON_EXCEPTION
}

int CAddonGUI_Control_Spin::GetIntValue(void *addonData, GUIHANDLE handle)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Spin - %s - invalid handler data", __FUNCTION__);

    return static_cast<CGUISpinControlEx*>(handle)->GetValue();
  }
  HANDLE_ADDON_EXCEPTION

  return 0;
}

void CAddonGUI_Control_Spin::SetFloatRange(void *addonData, GUIHANDLE handle, float start, float end)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Spin - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUISpinControlEx*>(handle)->SetFloatRange(start, end);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Spin::SetFloatValue(void *addonData, GUIHANDLE handle, float value)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Spin - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUISpinControlEx*>(handle)->SetFloatValue(value);
  }
  HANDLE_ADDON_EXCEPTION
}

float CAddonGUI_Control_Spin::GetFloatValue(void *addonData, GUIHANDLE handle)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Spin - %s - invalid handler data", __FUNCTION__);

    return static_cast<CGUISpinControlEx*>(handle)->GetFloatValue();
  }
  HANDLE_ADDON_EXCEPTION

  return 0.0f;
}

void CAddonGUI_Control_Spin::SetFloatInterval(void *addonData, GUIHANDLE handle, float interval)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Spin - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUISpinControlEx*>(handle)->SetFloatInterval(interval);
  }
  HANDLE_ADDON_EXCEPTION
}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
