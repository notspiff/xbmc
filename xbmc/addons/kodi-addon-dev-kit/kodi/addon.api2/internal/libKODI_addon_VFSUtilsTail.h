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

  inline CAddonLib_VFSProperty::CAddonLib_VFSProperty(const std::string& name, const std::string& value)
    : m_name(name),
      m_value(value)
  {
  }

  inline const std::string& CAddonLib_VFSProperty::Name(void) const
  {
    return m_name;
  }

  inline const std::string& CAddonLib_VFSProperty::Value(void) const
  {
    return m_value;
  }

  inline void CAddonLib_VFSProperty::SetName(const std::string& name)
  {
    m_name = name;
  }

  inline void CAddonLib_VFSProperty::SetValue(const std::string& value)
  {
    m_value = value;
  }

  /*\___________________________________________________________________________
  \*/

  inline CAddonLib_VFSDirEntry::CAddonLib_VFSDirEntry(
        const std::string& label,
        const std::string& path,
        bool               bFolder,
        int64_t            size)
    : m_label(label),
      m_path(path),
      m_bFolder(bFolder),
      m_size(size)
  {
  }

  inline CAddonLib_VFSDirEntry::CAddonLib_VFSDirEntry(const VFSDirEntry& dirEntry)
    : m_label(dirEntry.label ? dirEntry.label : ""),
      m_path(dirEntry.path   ? dirEntry.path  : ""),
      m_bFolder(dirEntry.folder),
      m_size(dirEntry.size)
  {
    if (dirEntry.properties)
    {
      for (unsigned int i = 0; i < dirEntry.num_props; ++i)
      {
        if (dirEntry.properties[i].name && dirEntry.properties[i].val)
          m_properties.push_back(CAddonLib_VFSProperty(dirEntry.properties[i].name, dirEntry.properties[i].val));
      }
    }
  }

  inline const std::string& CAddonLib_VFSDirEntry::Label(void) const
  {
    return m_label;
  }

  inline const std::string& CAddonLib_VFSDirEntry::Path(void) const
  {
    return m_path;
  }

  inline bool CAddonLib_VFSDirEntry::IsFolder(void) const
  {
    return m_bFolder;
  }

  inline int64_t CAddonLib_VFSDirEntry::Size(void) const
  {
    return m_size;
  }

  inline const std::vector<CAddonLib_VFSProperty>& CAddonLib_VFSDirEntry::Properties(void) const
  {
    return m_properties;
  }

  inline void CAddonLib_VFSDirEntry::SetLabel(const std::string& label)
  {
    m_label = label;
  }

  inline void CAddonLib_VFSDirEntry::SetPath(const std::string& path)
  {
    m_path = path;
  }

  inline void CAddonLib_VFSDirEntry::SetFolder(bool bFolder)
  {
    m_bFolder = bFolder;
  }

  inline void CAddonLib_VFSDirEntry::SetSize(int64_t size)
  {
    m_size = size;
  }

  inline std::vector<CAddonLib_VFSProperty>& CAddonLib_VFSDirEntry::Properties(void)
  {
    return m_properties;
  }

  /*\___________________________________________________________________________
  \*/

  inline bool CAddonLib_VFSUtils::CreateDirectory(const std::string& strPath)
  {
    return CAddonLib::g_libKODI_Internal->CreateDirectory(strPath.c_str());
  }

  inline bool CAddonLib_VFSUtils::DirectoryExists(const std::string& strPath)
  {
    return CAddonLib::g_libKODI_Internal->DirectoryExists(strPath.c_str());
  }

  inline bool CAddonLib_VFSUtils::RemoveDirectory(const std::string& strPath)
  {
    return CAddonLib::g_libKODI_Internal->RemoveDirectory(strPath.c_str());
  }

  inline bool CAddonLib_VFSUtils::GetDirectory(
        const std::string&          path,
        const std::string&          mask,
        std::vector<CAddonLib_VFSDirEntry>&  items)
  {
    VFSDirEntry* dir_list  = nullptr;
    unsigned int num_items = 0;
    if (CAddonLib::g_libKODI_Internal->GetVFSDirectory(path.c_str(), mask.c_str(), &dir_list, &num_items))
    {
      if (dir_list)
      {
        for (unsigned int i = 0; i < num_items; ++i)
          items.push_back(CAddonLib_VFSDirEntry(dir_list[i]));

        CAddonLib::g_libKODI_Internal->FreeVFSDirectory(dir_list, num_items);
      }

      return true;
    }
    return false;
  }

  inline std::string CAddonLib_VFSUtils::MakeLegalFileName(const std::string& strFileName)
  {
    return CAddonLib::g_libKODI_Internal->MakeLegalFileName(strFileName);
  }

  inline std::string CAddonLib_VFSUtils::MakeLegalPath(const std::string& strPath)
  {
    return CAddonLib::g_libKODI_Internal->MakeLegalPath(strPath);
  }

}; /* namespace V2 */
}; /* namespace AddOnLIB */
