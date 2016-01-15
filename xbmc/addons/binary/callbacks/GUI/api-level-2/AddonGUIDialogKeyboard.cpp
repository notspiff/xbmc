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
#include "guilib/GUIKeyboardFactory.h"
#include "utils/Variant.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIDialogKeyboard.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{
extern "C"
{

void CAddonGUI_Dialog_Keyboard::Init(CB_GUILib *callbacks)
{
  callbacks->Dialogs.Keyboard.ShowAndGetInputWithHead           = CAddonGUI_Dialog_Keyboard::ShowAndGetInputWithHead;
  callbacks->Dialogs.Keyboard.ShowAndGetInput                   = CAddonGUI_Dialog_Keyboard::ShowAndGetInput;
  callbacks->Dialogs.Keyboard.ShowAndGetNewPasswordWithHead     = CAddonGUI_Dialog_Keyboard::ShowAndGetNewPasswordWithHead;
  callbacks->Dialogs.Keyboard.ShowAndGetNewPassword             = CAddonGUI_Dialog_Keyboard::ShowAndGetNewPassword;
  callbacks->Dialogs.Keyboard.ShowAndVerifyNewPasswordWithHead  = CAddonGUI_Dialog_Keyboard::ShowAndVerifyNewPasswordWithHead;
  callbacks->Dialogs.Keyboard.ShowAndVerifyNewPassword          = CAddonGUI_Dialog_Keyboard::ShowAndVerifyNewPassword;
  callbacks->Dialogs.Keyboard.ShowAndVerifyPassword             = CAddonGUI_Dialog_Keyboard::ShowAndVerifyPassword;
  callbacks->Dialogs.Keyboard.ShowAndGetFilter                  = CAddonGUI_Dialog_Keyboard::ShowAndGetFilter;
  callbacks->Dialogs.Keyboard.SendTextToActiveKeyboard          = CAddonGUI_Dialog_Keyboard::SendTextToActiveKeyboard;
  callbacks->Dialogs.Keyboard.isKeyboardActivated               = CAddonGUI_Dialog_Keyboard::isKeyboardActivated;
}

bool CAddonGUI_Dialog_Keyboard::ShowAndGetInputWithHead(char &aTextString, unsigned int &iMaxStringSize, const char *strHeading, bool allowEmptyResult, bool hiddenInput, unsigned int autoCloseMs)
{
  try
  {
    std::string str = &aTextString;
    bool bRet = CGUIKeyboardFactory::ShowAndGetInput(str, CVariant{strHeading}, allowEmptyResult, hiddenInput, autoCloseMs);
    if (bRet)
      strncpy(&aTextString, str.c_str(), iMaxStringSize);
    iMaxStringSize = str.length();
    return bRet;
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

bool CAddonGUI_Dialog_Keyboard::ShowAndGetInput(char &aTextString, unsigned int &iMaxStringSize, bool allowEmptyResult, unsigned int autoCloseMs)
{
  try
  {
    std::string str = &aTextString;
    bool bRet = CGUIKeyboardFactory::ShowAndGetInput(str, allowEmptyResult, autoCloseMs);
    if (bRet)
      strncpy(&aTextString, str.c_str(), iMaxStringSize);
    iMaxStringSize = str.length();
    return bRet;
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

bool CAddonGUI_Dialog_Keyboard::ShowAndGetNewPasswordWithHead(char &strNewPassword, unsigned int &iMaxStringSize, const char *strHeading, bool allowEmptyResult, unsigned int autoCloseMs)
{
  try
  {
    std::string str = &strNewPassword;
    bool bRet = CGUIKeyboardFactory::ShowAndGetNewPassword(str, strHeading, allowEmptyResult, autoCloseMs);
    if (bRet)
      strncpy(&strNewPassword, str.c_str(), iMaxStringSize);
    iMaxStringSize = str.length();
    return bRet;
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

bool CAddonGUI_Dialog_Keyboard::ShowAndGetNewPassword(char &strNewPassword, unsigned int &iMaxStringSize, unsigned int autoCloseMs)
{
  try
  {
    std::string str = &strNewPassword;
    bool bRet = CGUIKeyboardFactory::ShowAndGetNewPassword(str, autoCloseMs);
    if (bRet)
      strncpy(&strNewPassword, str.c_str(), iMaxStringSize);
    iMaxStringSize = str.length();
    return bRet;
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

bool CAddonGUI_Dialog_Keyboard::ShowAndVerifyNewPasswordWithHead(char &strNewPassword, unsigned int &iMaxStringSize, const char *strHeading, bool allowEmptyResult, unsigned int autoCloseMs)
{
  try
  {
    std::string str = &strNewPassword;
    bool bRet = CGUIKeyboardFactory::ShowAndVerifyNewPassword(str, strHeading, allowEmptyResult, autoCloseMs);
    if (bRet)
      strncpy(&strNewPassword, str.c_str(), iMaxStringSize);
    iMaxStringSize = str.length();
    return bRet;
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

bool CAddonGUI_Dialog_Keyboard::ShowAndVerifyNewPassword(char &strNewPassword, unsigned int &iMaxStringSize, unsigned int autoCloseMs)
{
  try
  {
    std::string str = &strNewPassword;
    bool bRet = CGUIKeyboardFactory::ShowAndVerifyNewPassword(str, autoCloseMs);
    if (bRet)
      strncpy(&strNewPassword, str.c_str(), iMaxStringSize);
    iMaxStringSize = str.length();
    return bRet;
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

int CAddonGUI_Dialog_Keyboard::ShowAndVerifyPassword(char &strPassword, unsigned int &iMaxStringSize, const char *strHeading, int iRetries, unsigned int autoCloseMs)
{
  try
  {
    std::string str = &strPassword;
    int iRet = CGUIKeyboardFactory::ShowAndVerifyPassword(str, strHeading, iRetries, autoCloseMs);
    if (iRet)
      strncpy(&strPassword, str.c_str(), iMaxStringSize);
    iMaxStringSize = str.length();
    return iRet;
  }
  HANDLE_ADDON_EXCEPTION

  return -1;
}

bool CAddonGUI_Dialog_Keyboard::ShowAndGetFilter(char &aTextString, unsigned int &iMaxStringSize, bool searching, unsigned int autoCloseMs)
{
  try
  {
    std::string str = &aTextString;
    bool bRet = CGUIKeyboardFactory::ShowAndGetFilter(str, searching, autoCloseMs);
    if (bRet)
      strncpy(&aTextString, str.c_str(), iMaxStringSize);
    iMaxStringSize = str.length();
    return bRet;
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

bool CAddonGUI_Dialog_Keyboard::SendTextToActiveKeyboard(const char *aTextString, bool closeKeyboard)
{
  try
  {
    return CGUIKeyboardFactory::SendTextToActiveKeyboard(aTextString, closeKeyboard);
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

bool CAddonGUI_Dialog_Keyboard::isKeyboardActivated()
{
  try
  {
    return CGUIKeyboardFactory::isKeyboardActivated();
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
