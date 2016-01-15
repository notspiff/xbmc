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
#include "guilib/GUITextBox.h"
#include "guilib/GUIWindowManager.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIControlTextBox.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{
extern "C"
{

void CAddonGUI_Control_TextBox::Init(CB_GUILib *callbacks)
{
  callbacks->Control.TextBox.SetVisible       = CAddonGUI_Control_TextBox::SetVisible;
  callbacks->Control.TextBox.Reset            = CAddonGUI_Control_TextBox::Reset;
  callbacks->Control.TextBox.SetText          = CAddonGUI_Control_TextBox::SetText;
  callbacks->Control.TextBox.GetText          = CAddonGUI_Control_TextBox::GetText;
  callbacks->Control.TextBox.Scroll           = CAddonGUI_Control_TextBox::Scroll;
  callbacks->Control.TextBox.SetAutoScrolling = CAddonGUI_Control_TextBox::SetAutoScrolling;
}

void CAddonGUI_Control_TextBox::SetVisible(void *addonData, GUIHANDLE handle, bool visible)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_TextBox - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUITextBox*>(handle)->SetVisible(visible);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_TextBox::Reset(void *addonData, GUIHANDLE handle)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_TextBox - %s - invalid handler data", __FUNCTION__);

    CGUITextBox* textBox = static_cast<CGUITextBox*>(handle);

    CGUIMessage msg(GUI_MSG_LABEL_RESET, textBox->GetParentID(), textBox->GetID());
    g_windowManager.SendThreadMessage(msg, textBox->GetParentID());
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_TextBox::SetText(void *addonData, GUIHANDLE handle, const char *text)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_TextBox - %s - invalid handler data", __FUNCTION__);

    CGUITextBox* textBox = static_cast<CGUITextBox*>(handle);

    // create message
    CGUIMessage msg(GUI_MSG_LABEL_SET, textBox->GetParentID(), textBox->GetID());
    msg.SetLabel(text);

    // send message
    g_windowManager.SendThreadMessage(msg, textBox->GetParentID());
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_TextBox::GetText(void *addonData, GUIHANDLE handle, char &text, unsigned int &iMaxStringSize)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_TextBox - %s - invalid handler data", __FUNCTION__);

    std::string tmpText = static_cast<CGUITextBox*>(handle)->GetDescription();
    strncpy(&text, tmpText.c_str(), iMaxStringSize);
    iMaxStringSize = tmpText.size();
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_TextBox::Scroll(void *addonData, GUIHANDLE handle, unsigned int position)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_TextBox - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUITextBox*>(handle)->Scroll(position);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_TextBox::SetAutoScrolling(void *addonData, GUIHANDLE handle, int delay, int time, int repeat)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_TextBox - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUITextBox*>(handle)->SetAutoScrolling(delay, time, repeat);
  }
  HANDLE_ADDON_EXCEPTION
}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
