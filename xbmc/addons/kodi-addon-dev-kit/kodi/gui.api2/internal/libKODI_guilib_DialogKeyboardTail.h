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

/*
 * GUILib.h EOF header, passed there (out of normal code style) to reduce
 * not needed parts, to have only add-on programming related stuff there.
 */

namespace GUILIB
{
namespace V2
{

  inline bool CAddonGUIDialogKeyboard::ShowAndGetInput(
        std::string&            strText,
        const std::string&      strHeading,
        bool                    allowEmptyResult,
        bool                    hiddenInput,
        unsigned int            autoCloseMs)
  {
    strText.resize(1024);
    unsigned int size = (unsigned int)strText.capacity();
    bool ret = CGUILib::CGUILib::g_libKODI_Internal->m_Callbacks->Dialogs.Keyboard.ShowAndGetInputWithHead(strText[0], size, strHeading.c_str(), allowEmptyResult, hiddenInput, autoCloseMs);
    strText.resize(size);
    strText.shrink_to_fit();
    return ret;
  }

  inline bool CAddonGUIDialogKeyboard::ShowAndGetInput(
        std::string&            strText,
        bool                    allowEmptyResult,
        unsigned int            autoCloseMs)
  {
    strText.resize(1024);
    unsigned int size = (unsigned int)strText.capacity();
    bool ret = CGUILib::CGUILib::g_libKODI_Internal->m_Callbacks->Dialogs.Keyboard.ShowAndGetInput(strText[0], size, allowEmptyResult, autoCloseMs);
    strText.resize(size);
    strText.shrink_to_fit();
    return ret;
  }

  inline bool CAddonGUIDialogKeyboard::ShowAndGetNewPassword(
        std::string&            strNewPassword,
        const std::string&      strHeading,
        bool                    allowEmptyResult,
        unsigned int            autoCloseMs)
  {
    strNewPassword.resize(1024);
    unsigned int size = (unsigned int)strNewPassword.capacity();
    bool ret = CGUILib::CGUILib::g_libKODI_Internal->m_Callbacks->Dialogs.Keyboard.ShowAndGetNewPasswordWithHead(strNewPassword[0], size, strHeading.c_str(), allowEmptyResult, autoCloseMs);
    strNewPassword.resize(size);
    strNewPassword.shrink_to_fit();
    return ret;
  }

  inline bool CAddonGUIDialogKeyboard::ShowAndGetNewPassword(
        std::string&            strNewPassword,
        unsigned int            autoCloseMs)
  {
    strNewPassword.resize(1024);
    unsigned int size = (unsigned int)strNewPassword.capacity();
    bool ret = CGUILib::CGUILib::g_libKODI_Internal->m_Callbacks->Dialogs.Keyboard.ShowAndGetNewPassword(strNewPassword[0], size, autoCloseMs);
    strNewPassword.resize(size);
    strNewPassword.shrink_to_fit();
    return ret;
  }

  inline bool CAddonGUIDialogKeyboard::ShowAndVerifyNewPassword(
        std::string&            strNewPassword,
        const std::string&      strHeading,
        bool                    allowEmptyResult,
        unsigned int            autoCloseMs)
  {
    strNewPassword.resize(1024);
    unsigned int size = (unsigned int)strNewPassword.capacity();
    bool ret = CGUILib::CGUILib::g_libKODI_Internal->m_Callbacks->Dialogs.Keyboard.ShowAndVerifyNewPasswordWithHead(strNewPassword[0], size, strHeading.c_str(), allowEmptyResult, autoCloseMs);
    strNewPassword.resize(size);
    strNewPassword.shrink_to_fit();
    return ret;
  }

  inline bool CAddonGUIDialogKeyboard::ShowAndVerifyNewPassword(
        std::string&            strNewPassword,
        unsigned int            autoCloseMs)
  {
    strNewPassword.resize(1024);
    unsigned int size = (unsigned int)strNewPassword.capacity();
    bool ret = CGUILib::CGUILib::g_libKODI_Internal->m_Callbacks->Dialogs.Keyboard.ShowAndVerifyNewPassword(strNewPassword[0], size, autoCloseMs);
    strNewPassword.resize(size);
    strNewPassword.shrink_to_fit();
    return ret;
  }

  inline int CAddonGUIDialogKeyboard::ShowAndVerifyPassword(
        std::string&            strPassword,
        const std::string&      strHeading,
        int                     iRetries,
        unsigned int            autoCloseMs)
  {
    strPassword.resize(1024);
    unsigned int size = (unsigned int)strPassword.capacity();
    int ret = CGUILib::CGUILib::g_libKODI_Internal->m_Callbacks->Dialogs.Keyboard.ShowAndVerifyPassword(strPassword[0], size, strHeading.c_str(), iRetries, autoCloseMs);
    strPassword.resize(size);
    strPassword.shrink_to_fit();
    return ret;
  }

  inline bool CAddonGUIDialogKeyboard::ShowAndGetFilter(
        std::string&            strText,
        bool                    searching,
        unsigned int            autoCloseMs)
  {
    strText.resize(1024);
    unsigned int size = (unsigned int)strText.capacity();
    bool ret = CGUILib::CGUILib::g_libKODI_Internal->m_Callbacks->Dialogs.Keyboard.ShowAndGetFilter(strText[0], size, searching, autoCloseMs);
    strText.resize(size);
    strText.shrink_to_fit();
    return ret;
  }

  inline bool CAddonGUIDialogKeyboard::SendTextToActiveKeyboard(
        const std::string&      aTextString,
        bool                    closeKeyboard)
  {
    return CGUILib::CGUILib::g_libKODI_Internal->m_Callbacks->Dialogs.Keyboard.SendTextToActiveKeyboard(aTextString.c_str(), closeKeyboard);
  }

  inline bool CAddonGUIDialogKeyboard::IsKeyboardActivated()
  {
    return CGUILib::CGUILib::g_libKODI_Internal->m_Callbacks->Dialogs.Keyboard.isKeyboardActivated();
  }

}; /* namespace V2 */
}; /* namespace GUILIB */
