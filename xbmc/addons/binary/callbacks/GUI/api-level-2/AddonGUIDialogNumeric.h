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

#include "addons/kodi-addon-dev-kit/kodi/gui.api2/GUILib.h"

namespace GUILIB
{
namespace V2
{
extern "C"
{

  struct CAddonGUI_Dialog_Numeric
  {
    static void Init(CB_GUILib *callbacks);

    static bool ShowAndVerifyNewPassword(char         &strNewPassword,
                                         unsigned int &iMaxStringSized);

    static int  ShowAndVerifyPassword(char         &strPassword,
                                      unsigned int &iMaxStringSize,
                                      const char   *strHeading,
                                      int           iRetries);

    static bool ShowAndVerifyInput(char         &strToVerify,
                                   unsigned int &iMaxStringSize,
                                   const char   *strHeading,
                                   bool          bVerifyInput);

    static bool ShowAndGetTime(tm           &time,
                               const char   *strHeading);

    static bool ShowAndGetDate(tm           &date,
                               const char   *strHeading);

    static bool ShowAndGetIPAddress(char         &strIPAddress,
                                    unsigned int &iMaxStringSize,
                                    const char   *strHeading);

    static bool ShowAndGetNumber(char         &strInput,
                                 unsigned int &iMaxStringSize,
                                 const char   *strHeading,
                                 unsigned int  iAutoCloseTimeoutMs);

    static bool ShowAndGetSeconds(char         &timeString,
                                  unsigned int &iMaxStringSize,
                                  const char   *strHeading);
  };

}; /*  extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
