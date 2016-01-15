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

  typedef bool    _can_open_directory(void* HANDLE, const char* strURL);
  typedef bool    _create_directory(void* HANDLE, const char* strPath);
  typedef bool    _directory_exists(void* HANDLE, const char* strPath);
  typedef bool    _remove_directory(void* HANDLE, const char* strPath);

  typedef struct CB_Addon_Directory
  {
    _can_open_directory*            can_open_directory;
    _create_directory*              create_directory;
    _directory_exists*              directory_exists;
    _remove_directory*              remove_directory;
  } CB_AddonLib_Directory;


}; /* namespace V2 */
}; /* namespace AddOnLIB */
