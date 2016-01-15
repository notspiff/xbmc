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

  typedef bool    _wake_on_lan(void* HANDLE, const char *mac);
  typedef void    _get_ip_address(void* HANDLE, char &ip, unsigned int &iMaxStringSize);
  typedef char*   _dns_lookup(void* HANDLE, const char* url, bool& ret);
  typedef char*   _url_encode(void* HANDLE, const char* url);

  typedef struct CB_Addon_Network
  {
    _wake_on_lan*                   wake_on_lan;
    _get_ip_address*                get_ip_address;
    _dns_lookup*                    dns_lookup;
    _url_encode*                    url_encode;
  } CB_AddonLib_Network;

}; /* namespace V2 */
}; /* namespace AddOnLIB
 */
