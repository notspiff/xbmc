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
extern "C"
{

  struct VFSProperty
  {
    char* name;
    char* val;
  };

  struct VFSDirEntry
  {
    char* label;             //!< item label
    char* path;              //!< item path
    int num_props;           //!< Number of properties attached to item
    VFSProperty* properties; //!< Properties
    bool folder;             //!< Item is a folder
    uint64_t size;           //!< Size of file represented by item
  };

  /*\___________________________________________________________________________
  \*/

  typedef bool    _create_directory(
        void*                     HANDLE,
        const char*               strPath);

  typedef bool    _directory_exists(
        void*                     HANDLE,
        const char*               strPath);

  typedef bool    _remove_directory(
        void*                     HANDLE,
        const char*               strPath);

  typedef bool    _get_vfs_directory(
        void*                     HANDLE,
        const char*               strPath,
        const char*               mask,
        VFSDirEntry**             items,
        unsigned int*             num_items);

  typedef void    _free_vfs_directory(
        void*                     HANDLE,
        VFSDirEntry*              items,
        unsigned int              num_items);

  typedef struct CB_Addon_VFS
  {
    _create_directory*              create_directory;
    _directory_exists*              directory_exists;
    _remove_directory*              remove_directory;
    _get_vfs_directory*             get_vfs_directory;
    _free_vfs_directory*            free_vfs_directory;
  } CB_AddonLib_VFS;

  /*\___________________________________________________________________________
  \*/

  #define IMPL_VFS_PROPERTY                                                    \
    private:                                                                   \
      std::string m_name;                                                      \
      std::string m_value;

  #define IMPL_VFS_DIR_ENTRY                                                   \
    private:                                                                   \
      std::string m_label;                                                     \
      std::string m_path;                                                      \
      bool m_bFolder;                                                          \
      int64_t m_size;                                                          \
      std::vector<CAddonLib_VFSProperty> m_properties;

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace AddOnLIB */
