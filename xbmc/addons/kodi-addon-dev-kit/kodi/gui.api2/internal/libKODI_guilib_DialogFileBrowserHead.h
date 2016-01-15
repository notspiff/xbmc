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

  class CAddonGUIDialogFileBrowser;

  typedef bool GUIDialog_FileBrowser_ShowAndGetDirectory(
       const char*   shares,
       const char*   heading,
       char&         path,
       unsigned int& iMaxStringSize,
       bool          bWriteOnly);

  typedef bool GUIDialog_FileBrowser_ShowAndGetFile(
       const char*   shares,
       const char*   mask,
       const char*   heading,
       char&         file,
       unsigned int& iMaxStringSize,
       bool          useThumbs,
       bool          useFileDirectories);

  typedef bool GUIDialog_FileBrowser_ShowAndGetFileFromDir(
       const char*   directory,
       const char*   mask,
       const char*   heading,
       char&         file,
       unsigned int& iMaxStringSize,
       bool          useThumbs,
       bool          useFileDirectories,
       bool          singleList);

  typedef bool GUIDialog_FileBrowser_ShowAndGetFileList(
       const char*   shares,
       const char*   mask,
       const char*   heading,
       char**&       path,
       unsigned int& entries,
       bool          useThumbs,
       bool          useFileDirectories);

  typedef bool GUIDialog_FileBrowser_ShowAndGetSource(
       char&         path,
       unsigned int& iMaxStringSize,
       bool          allowNetworkShares,
       const char*   additionalShare,
       const char*   strType);

  typedef bool GUIDialog_FileBrowser_ShowAndGetImage(
       const char*   shares,
       const char*   heading,
       char&         path,
       unsigned int& iMaxStringSize);

  typedef bool GUIDialog_FileBrowser_ShowAndGetImageList(
       const char*   shares,
       const char*   heading,
       char**&       path,
       unsigned int& entries);

   typedef void GUIDialog_FileBrowser_ClearList(
       char**&       path,
       unsigned int  entries);

  typedef struct CB_GUILib_Dialog_FileBrowser
  {
    GUIDialog_FileBrowser_ShowAndGetDirectory*     ShowAndGetDirectory;
    GUIDialog_FileBrowser_ShowAndGetFile*          ShowAndGetFile;
    GUIDialog_FileBrowser_ShowAndGetFileFromDir*   ShowAndGetFileFromDir;
    GUIDialog_FileBrowser_ShowAndGetFileList*      ShowAndGetFileList;
    GUIDialog_FileBrowser_ShowAndGetSource*        ShowAndGetSource;
    GUIDialog_FileBrowser_ShowAndGetImage*         ShowAndGetImage;
    GUIDialog_FileBrowser_ShowAndGetImageList*     ShowAndGetImageList;
    GUIDialog_FileBrowser_ClearList*               ClearList;
  } CB_GUILib_Dialog_FileBrowser;

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
