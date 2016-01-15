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

  class CAddonGUIDialogKeyboard;

  typedef bool GUIDialog_Keyboard_ShowAndGetInputWithHead
      (char         &strTextString,
       unsigned int &iMaxStringSize,
       const char  *heading,
       bool         allowEmptyResult,
       bool         hiddenInput,
       unsigned int autoCloseMs);

  typedef bool GUIDialog_Keyboard_ShowAndGetInput
      (char         &strTextString,
       unsigned int &iMaxStringSize,
       bool         allowEmptyResult,
       unsigned int autoCloseMs);

  typedef bool GUIDialog_Keyboard_ShowAndGetNewPasswordWithHead
      (char         &newPassword,
       unsigned int &iMaxStringSize,
       const char   *strHeading,
       bool          allowEmptyResult,
       unsigned int  autoCloseMs);

  typedef bool GUIDialog_Keyboard_ShowAndGetNewPassword
      (char         &strNewPassword,
       unsigned int &iMaxStringSize,
       unsigned int  autoCloseMs);

  typedef bool GUIDialog_Keyboard_ShowAndVerifyNewPasswordWithHead
      (char         &strNewPassword,
       unsigned int &iMaxStringSize,
       const char   *strHeading,
       bool          allowEmpty,
       unsigned int  autoCloseMs);

  typedef bool GUIDialog_Keyboard_ShowAndVerifyNewPassword
      (char         &strNewPassword,
       unsigned int &iMaxStringSize,
       unsigned int  autoCloseMs);

  typedef int  GUIDialog_Keyboard_ShowAndVerifyPassword
      (char         &strPassword,
       unsigned int &iMaxStringSize,
       const char   *strHeading,
       int           iRetries,
       unsigned int  autoCloseMs);

  typedef bool GUIDialog_Keyboard_ShowAndGetFilter
      (char         &aTextString,
       unsigned int &iMaxStringSize,
       bool          searching,
       unsigned int  autoCloseMs);

  typedef bool GUIDialog_Keyboard_SendTextToActiveKeyboard
      (const char   *aTextString,
       bool          closeKeyboard);

  typedef bool GUIDialog_Keyboard_isKeyboardActivated
      ();

  typedef struct CB_GUILib_Dialog_Keyboard
  {
    GUIDialog_Keyboard_ShowAndGetInputWithHead*          ShowAndGetInputWithHead;
    GUIDialog_Keyboard_ShowAndGetInput*                  ShowAndGetInput;
    GUIDialog_Keyboard_ShowAndGetNewPasswordWithHead*    ShowAndGetNewPasswordWithHead;
    GUIDialog_Keyboard_ShowAndGetNewPassword*            ShowAndGetNewPassword;
    GUIDialog_Keyboard_ShowAndVerifyNewPasswordWithHead* ShowAndVerifyNewPasswordWithHead;
    GUIDialog_Keyboard_ShowAndVerifyNewPassword*         ShowAndVerifyNewPassword;
    GUIDialog_Keyboard_ShowAndVerifyPassword*            ShowAndVerifyPassword;
    GUIDialog_Keyboard_ShowAndGetFilter*                 ShowAndGetFilter;
    GUIDialog_Keyboard_SendTextToActiveKeyboard*         SendTextToActiveKeyboard;
    GUIDialog_Keyboard_isKeyboardActivated*              isKeyboardActivated;
  } CB_GUILib_Dialog_Keyboard;

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
