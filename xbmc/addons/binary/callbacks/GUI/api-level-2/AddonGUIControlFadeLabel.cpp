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
#include "guilib/GUIFadeLabelControl.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIControlFadeLabel.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{
extern "C"
{

void CAddonGUI_Control_FadeLabel::Init(CB_GUILib *callbacks)
{
  callbacks->Control.FadeLabel.SetVisible              = CAddonGUI_Control_Button::SetVisible;
  callbacks->Control.FadeLabel.AddLabel                = CAddonGUI_Control_FadeLabel::AddLabel;
  callbacks->Control.FadeLabel.GetLabel                = CAddonGUI_Control_FadeLabel::GetLabel;
  callbacks->Control.FadeLabel.SetScrolling            = CAddonGUI_Control_FadeLabel::SetScrolling;
  callbacks->Control.FadeLabel.Reset                   = CAddonGUI_Control_FadeLabel::Reset;
}

void CAddonGUI_Control_FadeLabel::SetVisible(void *addonData, GUIHANDLE handle, bool visible)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_FadeLabel - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUIFadeLabelControl*>(handle)->SetVisible(visible);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_FadeLabel::AddLabel(void *addonData, GUIHANDLE handle, const char *label)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_FadeLabel - %s - invalid handler data", __FUNCTION__);

    CGUIMessage msg(GUI_MSG_LABEL_ADD, static_cast<CGUIFadeLabelControl*>(handle)->GetParentID(), static_cast<CGUIFadeLabelControl*>(handle)->GetID());
    msg.SetLabel(label);
    static_cast<CGUIFadeLabelControl*>(handle)->OnMessage(msg);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_FadeLabel::GetLabel(void *addonData, GUIHANDLE handle, char &label, unsigned int &iMaxStringSize)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_FadeLabel - %s - invalid handler data", __FUNCTION__);

    CGUIMessage msg(GUI_MSG_ITEM_SELECTED, static_cast<CGUIFadeLabelControl*>(handle)->GetParentID(), static_cast<CGUIFadeLabelControl*>(handle)->GetID());
    static_cast<CGUIFadeLabelControl*>(handle)->OnMessage(msg);
    std::string text = msg.GetLabel();
    strncpy(&label, text.c_str(), iMaxStringSize);
    iMaxStringSize = text.length();
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_FadeLabel::SetScrolling(void *addonData, GUIHANDLE handle, bool scroll)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_FadeLabel - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUIFadeLabelControl*>(handle)->SetScrolling(scroll);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_FadeLabel::Reset(void *addonData, GUIHANDLE handle)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_FadeLabel - %s - invalid handler data", __FUNCTION__);

    CGUIMessage msg(GUI_MSG_LABEL_RESET, static_cast<CGUIFadeLabelControl*>(handle)->GetParentID(), static_cast<CGUIFadeLabelControl*>(handle)->GetID());
    static_cast<CGUIFadeLabelControl*>(handle)->OnMessage(msg);
  }
  HANDLE_ADDON_EXCEPTION
}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
