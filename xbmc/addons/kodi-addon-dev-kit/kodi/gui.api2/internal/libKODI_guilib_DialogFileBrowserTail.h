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

/*
 * GUILib.h EOF header, passed there (out of normal code style) to reduce
 * not needed parts, to have only add-on programming related stuff there.
 */

namespace GUILIB
{
namespace V2
{

  inline bool CAddonGUIDialogFileBrowser::ShowAndGetDirectory(
          const std::string&      shares,
          const std::string&      heading,
          std::string&            path,
          bool                    bWriteOnly)
  {
    path.resize(1024);
    unsigned int size = (unsigned int)path.capacity();
    bool ret = CGUILib::g_libKODI_Internal->m_Callbacks->Dialogs.FileBrowser.ShowAndGetDirectory(shares.c_str(), heading.c_str(), path[0], size, bWriteOnly);
    path.resize(size);
    path.shrink_to_fit();
    return ret;
  }

  inline bool CAddonGUIDialogFileBrowser::ShowAndGetFile(
          const std::string&      shares,
          const std::string&      mask,
          const std::string&      heading,
          std::string&            file,
          bool                    useThumbs,
          bool                    useFileDirectories)
  {
    file.resize(1024);
    unsigned int size = (unsigned int)file.capacity();;
    bool ret = CGUILib::g_libKODI_Internal->m_Callbacks->Dialogs.FileBrowser.ShowAndGetFile(shares.c_str(), mask.c_str(), heading.c_str(), file[0], size, useThumbs, useFileDirectories);
    file.resize(size);
    file.shrink_to_fit();
    return ret;
  }

  inline bool CAddonGUIDialogFileBrowser::ShowAndGetFileFromDir(
          const std::string&      directory,
          const std::string&      mask,
          const std::string&      heading,
          std::string&            path,
          bool                    useThumbs,
          bool                    useFileDirectories,
          bool                    singleList)
  {
    path.resize(1024);
    unsigned int size = (unsigned int)path.capacity();
    bool ret = CGUILib::g_libKODI_Internal->m_Callbacks->Dialogs.FileBrowser.ShowAndGetFileFromDir(directory.c_str(), mask.c_str(), heading.c_str(), path[0], size, useThumbs, useFileDirectories, singleList);
    path.resize(size);
    path.shrink_to_fit();
    return ret;
  }

  inline bool CAddonGUIDialogFileBrowser::ShowAndGetFileList(
          const std::string&      shares,
          const std::string&      mask,
          const std::string&      heading,
          std::vector<std::string> &path,
          bool                    useThumbs,
          bool                    useFileDirectories)
  {
    char** list;
    unsigned int listSize = 0;
    bool ret = CGUILib::g_libKODI_Internal->m_Callbacks->Dialogs.FileBrowser.ShowAndGetFileList(shares.c_str(), mask.c_str(), heading.c_str(), list, listSize, useThumbs, useFileDirectories);
    if (ret)
    {
      for (unsigned int i = 0; i < listSize; ++i)
        path.push_back(list[i]);
      CGUILib::g_libKODI_Internal->m_Callbacks->Dialogs.FileBrowser.ClearList(list, listSize);
    }
    return ret;
  }

  inline bool CAddonGUIDialogFileBrowser::ShowAndGetSource(
          std::string&            path,
          bool                    allowNetworkShares,
          const std::string&      additionalShare,
          const std::string&      strType)
  {
    path.resize(1024);
    unsigned int size = (unsigned int)path.capacity();
    bool ret = CGUILib::g_libKODI_Internal->m_Callbacks->Dialogs.FileBrowser.ShowAndGetSource(path[0], size, allowNetworkShares, additionalShare.c_str(), strType.c_str());
    path.resize(size);
    path.shrink_to_fit();
    return ret;
  }

  inline bool CAddonGUIDialogFileBrowser::ShowAndGetImage(
          const std::string&      shares,
          const std::string&      heading,
          std::string&            path)
  {
    path.resize(1024);
    unsigned int size = (unsigned int)path.capacity();
    bool ret = CGUILib::g_libKODI_Internal->m_Callbacks->Dialogs.FileBrowser.ShowAndGetImage(shares.c_str(), heading.c_str(), path[0], size);
    path.resize(size);
    path.shrink_to_fit();
    return ret;
  }

  inline bool CAddonGUIDialogFileBrowser::ShowAndGetImageList(
          const std::string&      shares,
          const std::string&      heading,
          std::vector<std::string> &path)
  {
    char** list;
    unsigned int listSize = 0;
    bool ret = CGUILib::g_libKODI_Internal->m_Callbacks->Dialogs.FileBrowser.ShowAndGetImageList(shares.c_str(), heading.c_str(), list, listSize);
    if (ret)
    {
      for (unsigned int i = 0; i < listSize; ++i)
        path.push_back(list[i]);
      CGUILib::g_libKODI_Internal->m_Callbacks->Dialogs.FileBrowser.ClearList(list, listSize);
    }
    return ret;
  }

}; /* namespace V2 */
}; /* namespace GUILIB */
