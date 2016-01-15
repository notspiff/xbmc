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

#include "AddonCB_Network.h"
#include "AddonCallbacksAddon.h"

#include "Application.h"
#include "PasswordManager.h"
#include "URL.h"
#include "addons/Addon.h"
#include "addons/binary/ExceptionHandling.h"
#include "network/DNSNameCache.h"
#include "network/Network.h"

using namespace ADDON;

namespace AddOnLIB
{
namespace V2
{

CAddonCB_Network::CAddonCB_Network()
{

}

void CAddonCB_Network::Init(CB_AddOnLib *callbacks)
{
  callbacks->Network.wake_on_lan    = CAddonCB_Network::wake_on_lan;
  callbacks->Network.get_ip_address = CAddonCB_Network::get_ip_address;
  callbacks->Network.dns_lookup     = CAddonCB_Network::dns_lookup;
  callbacks->Network.url_encode     = CAddonCB_Network::url_encode;
}

bool CAddonCB_Network::wake_on_lan(
        void*                     hdl,
        const char*               mac)
{
  try
  {
    if (!hdl || !mac)
      throw ADDON::WrongValueException("CAddonCB_Network - %s - invalid data (handle='%p', mac='%p')", __FUNCTION__, hdl, mac);

    return g_application.getNetwork().WakeOnLan(mac);
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

void CAddonCB_Network::get_ip_address(
        void*                     hdl,
        char&                     ip,
        unsigned int&             iMaxStringSize)
{
  try
  {
    if (!hdl)
      throw ADDON::WrongValueException("CAddonCB_Network - %s - invalid data (handle='%p')", __FUNCTION__, hdl);

    std::string titleIP;
    CNetworkInterface* iface = g_application.getNetwork().GetFirstConnectedInterface();
    if (iface)
      titleIP = iface->GetCurrentIPAddress();
    else
      titleIP = "127.0.0.1";

    strncpy(&ip, titleIP.c_str(), iMaxStringSize);
  }
  HANDLE_ADDON_EXCEPTION
}

char* CAddonCB_Network::dns_lookup(
        void*                     hdl,
        const char*               url,
        bool&                     ret)
{
  try
  {
    if (!hdl || !url)
      throw ADDON::WrongValueException("CAddonCB_Network - %s - invalid data (handle='%p', url='%p')", __FUNCTION__, hdl, url);

    std::string string;
    ret = CDNSNameCache::Lookup(url, string);
    char* buffer = nullptr;
    if (!string.empty())
      buffer = strdup(string.c_str());
    return buffer;
  }
  HANDLE_ADDON_EXCEPTION

  return nullptr;
}

char* CAddonCB_Network::url_encode(
        void*                     hdl,
        const char*               url)
{
  try
  {
    if (!hdl || !url)
      throw ADDON::WrongValueException("CAddonCB_Network - %s - invalid data (handle='%p', url='%p')", __FUNCTION__, hdl, url);

    std::string string = CURL::Encode(url);
    char* buffer = nullptr;
    if (!string.empty())
      buffer = strdup(string.c_str());
    return buffer;
  }
  HANDLE_ADDON_EXCEPTION

  return nullptr;
}

}; /* namespace V2 */
}; /* namespace AddOnLIB */
