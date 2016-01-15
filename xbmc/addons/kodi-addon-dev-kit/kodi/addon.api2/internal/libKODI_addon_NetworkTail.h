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

namespace AddOnLIB
{
namespace V2
{

  inline bool CAddonLib_Network::WakeOnLan(const std::string& mac)
  {
    return CAddonLib::g_libKODI_Internal->WakeOnLan(mac);
  }

  inline std::string CAddonLib_Network::GetIPAddress()
  {
    return CAddonLib::g_libKODI_Internal->GetIPAddress();
  }

  inline bool CAddonLib_Network::DNSLookup(const std::string& strHostName, std::string& strIpAddress)
  {
    return CAddonLib::g_libKODI_Internal->DNSLookup(strHostName, strIpAddress);
  }

  inline std::string CAddonLib_Network::URLEncode(const std::string& url)
  {
    return CAddonLib::g_libKODI_Internal->URLEncode(url);
  }

}; /* namespace V2 */
}; /* namespace AddOnLIB */
