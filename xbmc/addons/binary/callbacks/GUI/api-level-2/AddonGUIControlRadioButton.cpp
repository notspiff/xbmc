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
#include "guilib/GUIRadioButtonControl.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIControlRadioButton.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{
extern "C"
{

void CAddonGUI_Control_RadioButton::Init(CB_GUILib *callbacks)
{
  callbacks->Control.RadioButton.SetVisible   = CAddonGUI_Control_RadioButton::SetVisible;
  callbacks->Control.RadioButton.SetEnabled   = CAddonGUI_Control_RadioButton::SetEnabled;

  callbacks->Control.RadioButton.SetLabel     = CAddonGUI_Control_RadioButton::SetLabel;
  callbacks->Control.RadioButton.GetLabel     = CAddonGUI_Control_RadioButton::GetLabel;

  callbacks->Control.RadioButton.SetSelected  = CAddonGUI_Control_RadioButton::SetSelected;
  callbacks->Control.RadioButton.IsSelected   = CAddonGUI_Control_RadioButton::IsSelected;
}

void CAddonGUI_Control_RadioButton::SetVisible(void *addonData, GUIHANDLE handle, bool visible)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_RadioButton - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUIRadioButtonControl*>(handle)->SetVisible(visible);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_RadioButton::SetEnabled(void *addonData, GUIHANDLE handle, bool enabled)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_RadioButton - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUIRadioButtonControl*>(handle)->SetEnabled(enabled);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_RadioButton::SetLabel(void *addonData, GUIHANDLE handle, const char *label)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_RadioButton - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUIRadioButtonControl*>(handle)->SetLabel(label);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_RadioButton::GetLabel(void *addonData, GUIHANDLE handle, char &text, unsigned int &iMaxStringSize)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_RadioButton - %s - invalid handler data", __FUNCTION__);

    CGUIRadioButtonControl* pRadioButton = static_cast<CGUIRadioButtonControl *>(handle);
    strncpy(&text, pRadioButton->GetLabel().c_str(), iMaxStringSize);
    iMaxStringSize = pRadioButton->GetLabel().length();
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_RadioButton::SetSelected(void *addonData, GUIHANDLE handle, bool selected)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_RadioButton - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUIRadioButtonControl*>(handle)->SetSelected(selected);
  }
  HANDLE_ADDON_EXCEPTION
}

bool CAddonGUI_Control_RadioButton::IsSelected(void *addonData, GUIHANDLE handle)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_RadioButton - %s - invalid handler data", __FUNCTION__);

    return static_cast<CGUIRadioButtonControl *>(handle)->IsSelected();
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
