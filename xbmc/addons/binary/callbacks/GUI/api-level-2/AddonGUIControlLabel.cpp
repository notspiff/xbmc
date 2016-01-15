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
#include "guilib/GUILabelControl.h"
#include "guilib/GUIWindowManager.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIControlLabel.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{
extern "C"
{

void CAddonGUI_Control_Label::Init(CB_GUILib *callbacks)
{
  callbacks->Control.Label.SetVisible = CAddonGUI_Control_Label::SetVisible;
  callbacks->Control.Label.SetLabel   = CAddonGUI_Control_Label::SetLabel;
  callbacks->Control.Label.GetLabel   = CAddonGUI_Control_Label::GetLabel;
}

void CAddonGUI_Control_Label::SetVisible(void *addonData, GUIHANDLE handle, bool visible)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Label - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUILabelControl*>(handle)->SetVisible(visible);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Label::SetLabel(void *addonData, GUIHANDLE handle, const char *label)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Label - %s - invalid handler data", __FUNCTION__);

    CGUILabelControl* pControl = static_cast<CGUILabelControl*>(handle);

    // create message
    CGUIMessage msg(GUI_MSG_LABEL_SET, pControl->GetParentID(), pControl->GetID());
    msg.SetLabel(label);

    // send message
    g_windowManager.SendThreadMessage(msg, pControl->GetParentID());
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Label::GetLabel(void *addonData, GUIHANDLE handle, char &label, unsigned int &iMaxStringSize)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Label - %s - invalid handler data", __FUNCTION__);

    std::string text = static_cast<CGUILabelControl*>(handle)->GetDescription(); // GetDescription = label
    strncpy(&label, text.c_str(), iMaxStringSize);
    iMaxStringSize = text.length();
  }
  HANDLE_ADDON_EXCEPTION
}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
