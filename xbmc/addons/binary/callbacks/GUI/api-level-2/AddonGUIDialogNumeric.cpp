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

#include "XBDateTime.h"
#include "addons/Addon.h"
#include "addons/binary/ExceptionHandling.h"
#include "addons/binary/callbacks/AddonCallbacks.h"
#include "dialogs/GUIDialogNumeric.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIDialogNumeric.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{
extern "C"
{

void CAddonGUI_Dialog_Numeric::Init(CB_GUILib *callbacks)
{
  callbacks->Dialogs.Numeric.ShowAndVerifyNewPassword      = CAddonGUI_Dialog_Numeric::ShowAndVerifyNewPassword;
  callbacks->Dialogs.Numeric.ShowAndVerifyPassword         = CAddonGUI_Dialog_Numeric::ShowAndVerifyPassword;
  callbacks->Dialogs.Numeric.ShowAndVerifyInput            = CAddonGUI_Dialog_Numeric::ShowAndVerifyInput;
  callbacks->Dialogs.Numeric.ShowAndGetTime                = CAddonGUI_Dialog_Numeric::ShowAndGetTime;
  callbacks->Dialogs.Numeric.ShowAndGetDate                = CAddonGUI_Dialog_Numeric::ShowAndGetDate;
  callbacks->Dialogs.Numeric.ShowAndGetIPAddress           = CAddonGUI_Dialog_Numeric::ShowAndGetIPAddress;
  callbacks->Dialogs.Numeric.ShowAndGetNumber              = CAddonGUI_Dialog_Numeric::ShowAndGetNumber;
  callbacks->Dialogs.Numeric.ShowAndGetSeconds             = CAddonGUI_Dialog_Numeric::ShowAndGetSeconds;
}

bool CAddonGUI_Dialog_Numeric::ShowAndVerifyNewPassword(char &strNewPassword, unsigned int &iMaxStringSize)
{
  try
  {
    std::string str = &strNewPassword;
    bool bRet = CGUIDialogNumeric::ShowAndVerifyNewPassword(str);
    if (bRet)
      strncpy(&strNewPassword, str.c_str(), iMaxStringSize);
    iMaxStringSize = str.length();
    return bRet;
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

int CAddonGUI_Dialog_Numeric::ShowAndVerifyPassword(char &strPassword, unsigned int &iMaxStringSize, const char *strHeading, int iRetries)
{
  try
  {
    std::string str = &strPassword;
    int bRet = CGUIDialogNumeric::ShowAndVerifyPassword(str, strHeading, iRetries);
    if (bRet)
      strncpy(&strPassword, str.c_str(), iMaxStringSize);
    iMaxStringSize = str.length();
    return bRet;
  }
  HANDLE_ADDON_EXCEPTION

  return -1;
}

bool CAddonGUI_Dialog_Numeric::ShowAndVerifyInput(char &strToVerify, unsigned int &iMaxStringSize, const char *strHeading, bool bVerifyInput)
{
  try
  {
    std::string str = &strToVerify;
    bool bRet = CGUIDialogNumeric::ShowAndVerifyInput(str, strHeading, bVerifyInput);
    if (bRet)
      strncpy(&strToVerify, str.c_str(), iMaxStringSize);
    iMaxStringSize = str.length();
    return bRet;
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

bool CAddonGUI_Dialog_Numeric::ShowAndGetTime(tm &time, const char *strHeading)
{
  try
  {
    SYSTEMTIME systemTime;
    CDateTime dateTime(time);
    dateTime.GetAsSystemTime(systemTime);
    if (CGUIDialogNumeric::ShowAndGetTime(systemTime, strHeading))
    {
      dateTime = systemTime;
      dateTime.GetAsTm(time);
      return true;
    }
    return false;
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

bool CAddonGUI_Dialog_Numeric::ShowAndGetDate(tm &date, const char *strHeading)
{
  try
  {
    SYSTEMTIME systemTime;
    CDateTime dateTime(date);
    dateTime.GetAsSystemTime(systemTime);
    if (CGUIDialogNumeric::ShowAndGetDate(systemTime, strHeading))
    {
      dateTime = systemTime;
      dateTime.GetAsTm(date);
      return true;
    }
    return false;
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

bool CAddonGUI_Dialog_Numeric::ShowAndGetIPAddress(char &strIPAddress, unsigned int &iMaxStringSize, const char *strHeading)
{
  try
  {
    std::string strIP = &strIPAddress;
    bool bRet = CGUIDialogNumeric::ShowAndGetIPAddress(strIP, strHeading);
    if (bRet)
      strncpy(&strIPAddress, strIP.c_str(), iMaxStringSize);
    iMaxStringSize = strIP.length();
    return bRet;
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

bool CAddonGUI_Dialog_Numeric::ShowAndGetNumber(char &strInput, unsigned int &iMaxStringSize, const char *strHeading, unsigned int iAutoCloseTimeoutMs)
{
  try
  {
    std::string str = &strInput;
    bool bRet = CGUIDialogNumeric::ShowAndGetNumber(str, strHeading, iAutoCloseTimeoutMs);
    if (bRet)
      strncpy(&strInput, str.c_str(), iMaxStringSize);
    iMaxStringSize = str.length();
    return bRet;
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

bool CAddonGUI_Dialog_Numeric::ShowAndGetSeconds(char &timeString, unsigned int &iMaxStringSize, const char *strHeading)
{
  try
  {
    std::string str = &timeString;
    bool bRet = CGUIDialogNumeric::ShowAndGetSeconds(str, strHeading);
    if (bRet)
      strncpy(&timeString, str.c_str(), iMaxStringSize);
    iMaxStringSize = str.length();
    return bRet;
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
