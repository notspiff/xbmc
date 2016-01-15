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

  class CAddonGUIDialogNumeric;

  typedef bool GUIDialog_Numeric_ShowAndVerifyNewPassword
      (char         &strNewPassword,
       unsigned int &iMaxStringSize);

  typedef int  GUIDialog_Numeric_ShowAndVerifyPassword
      (char         &strPassword,
       unsigned int &iMaxStringSize,
       const char   *strHeading,
       int           iRetries);

  typedef bool GUIDialog_Numeric_ShowAndVerifyInput
      (char         &strPassword,
       unsigned int &iMaxStringSize,
       const char   *strHeading,
       bool          bVerifyInput);

  typedef bool GUIDialog_Numeric_ShowAndGetTime
      (tm           &time,
       const char   *strHeading);

  typedef bool GUIDialog_Numeric_ShowAndGetDate
      (tm           &date,
       const char   *strHeading);

  typedef bool GUIDialog_Numeric_ShowAndGetIPAddress
      (char         &strIPAddress,
       unsigned int &iMaxStringSize,
       const char   *strHeading);

  typedef bool GUIDialog_Numeric_ShowAndGetNumber
      (char         &strInput,
       unsigned int &iMaxStringSize,
       const char   *strHeading,
       unsigned int  iAutoCloseTimeoutMs);

  typedef bool GUIDialog_Numeric_ShowAndGetSeconds
      (char         &timeString,
       unsigned int &iMaxStringSize,
       const char   *strHeading);

  typedef struct CB_GUILib_Dialog_Numeric
  {
    GUIDialog_Numeric_ShowAndVerifyNewPassword*          ShowAndVerifyNewPassword;
    GUIDialog_Numeric_ShowAndVerifyPassword*             ShowAndVerifyPassword;
    GUIDialog_Numeric_ShowAndVerifyInput*                ShowAndVerifyInput;
    GUIDialog_Numeric_ShowAndGetTime*                    ShowAndGetTime;
    GUIDialog_Numeric_ShowAndGetDate*                    ShowAndGetDate;
    GUIDialog_Numeric_ShowAndGetIPAddress*               ShowAndGetIPAddress;
    GUIDialog_Numeric_ShowAndGetNumber*                  ShowAndGetNumber;
    GUIDialog_Numeric_ShowAndGetSeconds*                 ShowAndGetSeconds;
  } CB_GUILib_Dialog_Numeric;

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
