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

  inline bool CAddonLib_Directory::CanOpenDirectory(const std::string& strUrl)
  {
    return CAddonLib::g_libKODI_Internal->CanOpenDirectory(strUrl.c_str());
  }

  inline bool CAddonLib_Directory::CreateDirectory(const std::string& strPath)
  {
    return CAddonLib::g_libKODI_Internal->CreateDirectory(strPath.c_str());
  }

  inline bool CAddonLib_Directory::DirectoryExists(const std::string& strPath)
  {
    return CAddonLib::g_libKODI_Internal->DirectoryExists(strPath.c_str());
  }

  inline bool CAddonLib_Directory::RemoveDirectory(const std::string& strPath)
  {
    return CAddonLib::g_libKODI_Internal->RemoveDirectory(strPath.c_str());
  }

}; /* namespace V2 */
}; /* namespace AddOnLIB */
