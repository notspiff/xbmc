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
#include "guilib/GUIEditControl.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIControlEdit.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{
extern "C"
{

void CAddonGUI_Control_Edit::Init(CB_GUILib *callbacks)
{
  callbacks->Control.Edit.SetVisible              = CAddonGUI_Control_Edit::SetVisible;
  callbacks->Control.Edit.SetEnabled              = CAddonGUI_Control_Edit::SetEnabled;
  callbacks->Control.Edit.SetLabel                = CAddonGUI_Control_Edit::SetLabel;
  callbacks->Control.Edit.GetLabel                = CAddonGUI_Control_Edit::GetLabel;
  callbacks->Control.Edit.SetText                 = CAddonGUI_Control_Edit::SetText;
  callbacks->Control.Edit.GetText                 = CAddonGUI_Control_Edit::GetText;
  callbacks->Control.Edit.SetCursorPosition       = CAddonGUI_Control_Edit::SetCursorPosition;
  callbacks->Control.Edit.GetCursorPosition       = CAddonGUI_Control_Edit::GetCursorPosition;
  callbacks->Control.Edit.SetInputType            = CAddonGUI_Control_Edit::SetInputType;
}

void CAddonGUI_Control_Edit::SetVisible(void *addonData, GUIHANDLE handle, bool yesNo)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Edit - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUIEditControl*>(handle)->SetVisible(yesNo);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Edit::SetEnabled(void *addonData, GUIHANDLE handle, bool yesNo)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Edit - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUIEditControl*>(handle)->SetEnabled(yesNo);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Edit::SetLabel(void *addonData, GUIHANDLE handle, const char *label)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Edit - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUIEditControl*>(handle)->SetLabel(label);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Edit::GetLabel(void *addonData, GUIHANDLE handle, char &label, unsigned int &iMaxStringSize)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Edit - %s - invalid handler data", __FUNCTION__);

    std::string text = static_cast<CGUIEditControl*>(handle)->GetLabel();
    strncpy(&label, text.c_str(), iMaxStringSize);
    iMaxStringSize = text.length();
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Edit::SetText(void *addonData, GUIHANDLE handle, const char* text)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Edit - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUIEditControl*>(handle)->SetLabel2(text);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Edit::GetText(void *addonData, GUIHANDLE handle, char& text, unsigned int &iMaxStringSize)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Edit - %s - invalid handler data", __FUNCTION__);

    std::string textTmp = static_cast<CGUIEditControl*>(handle)->GetLabel2();
    strncpy(&text, textTmp.c_str(), iMaxStringSize);
    iMaxStringSize = textTmp.length();
  }
  HANDLE_ADDON_EXCEPTION
}

unsigned int CAddonGUI_Control_Edit::GetCursorPosition(void *addonData, GUIHANDLE handle)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Edit - %s - invalid handler data", __FUNCTION__);

    return static_cast<CGUIEditControl*>(handle)->GetCursorPosition();
  }
  HANDLE_ADDON_EXCEPTION

  return 0;
}

void CAddonGUI_Control_Edit::SetCursorPosition(void *addonData, GUIHANDLE handle, unsigned int iPosition)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Edit - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUIEditControl*>(handle)->SetCursorPosition(iPosition);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Edit::SetInputType(void *addonData, GUIHANDLE handle, AddonGUIInputType type, const char *heading)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Edit - %s - invalid handler data", __FUNCTION__);

    CGUIEditControl::INPUT_TYPE kodiType;
    switch (type)
    {
      case ADDON_INPUT_TYPE_TEXT:
        kodiType = CGUIEditControl::INPUT_TYPE_TEXT;
        break;
      case ADDON_INPUT_TYPE_NUMBER:
        kodiType = CGUIEditControl::INPUT_TYPE_NUMBER;
        break;
      case ADDON_INPUT_TYPE_SECONDS:
        kodiType = CGUIEditControl::INPUT_TYPE_SECONDS;
        break;
      case ADDON_INPUT_TYPE_TIME:
        kodiType = CGUIEditControl::INPUT_TYPE_TIME;
        break;
      case ADDON_INPUT_TYPE_DATE:
        kodiType = CGUIEditControl::INPUT_TYPE_DATE;
        break;
      case ADDON_INPUT_TYPE_IPADDRESS:
        kodiType = CGUIEditControl::INPUT_TYPE_IPADDRESS;
        break;
      case ADDON_INPUT_TYPE_PASSWORD:
        kodiType = CGUIEditControl::INPUT_TYPE_PASSWORD;
        break;
      case ADDON_INPUT_TYPE_PASSWORD_MD5:
        kodiType = CGUIEditControl::INPUT_TYPE_PASSWORD_MD5;
        break;
      case ADDON_INPUT_TYPE_SEARCH:
        kodiType = CGUIEditControl::INPUT_TYPE_SEARCH;
        break;
      case ADDON_INPUT_TYPE_FILTER:
        kodiType = CGUIEditControl::INPUT_TYPE_FILTER;
        break;
      case ADDON_INPUT_TYPE_READONLY:
      default:
        kodiType = CGUIEditControl::INPUT_TYPE_PASSWORD_NUMBER_VERIFY_NEW;
    }

    static_cast<CGUIEditControl*>(handle)->SetInputType(kodiType, heading);
  }
  HANDLE_ADDON_EXCEPTION
}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
