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

#include "definations.h"
#include "internal/libKODI_guilib_DialogFileBrowserHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  ///
  /// \defgroup CAddonGUIDialogFileBrowser
  /// \ingroup GUILIB
  /// @{
  /// @brief <b>File browser dialog</b>
  ///
  /// The functions listed below of the class "CAddonGUIDialogFileBrowser" offer
  /// the possibility to select to a file by the user of the add-on.
  ///
  /// It allows all the options that are possible in Kodi itself and offers all
  /// support file types.
  ///
  /// These are pure static functions them no other initialization need.
  ///
  /// It has the header \ref GUIDialogFileBrowser.h "#include <kodi/gui.api2/GUIDialogFileBrowser.h>"
  /// be included to enjoy it.
  ///
  /// \image html help.GUIDialogFileBrowser.png
  ///
  class CAddonGUIDialogFileBrowser
  {
  public:
     ///
     /// \ingroup CAddonGUIDialogFileBrowser
     /// @brief Directory selection dialog
     ///
     /// @param shares With Shares becomes the available start folders be set.
     /// @param heading Dialog header name
     /// @param path Return value about selected directory
     /// @param bWriteOnly If set only writeable folders are shown.
     /// @return False if selection becomes canceled.
     ///
     /// <b>Code example:</b>
     /// \code
     /// #include <kodi/gui.api2/GUIDialogFileBrowser.h>
     ///
     /// /*
     ///  * Example show directory selection dialog with on 'share' (first value)
     ///  * defined directory types.
     ///  *
     ///  * If this becomes leaved empty and 'directory' is empty goes it to the
     ///  * base path of the hard disk.
     ///  *
     ///  * Also can be with path written to 'directory' before the dialog forced
     ///  * to a start place.
     ///  */
     /// std::string directory;
     /// bool ret = CAddonGUIDialogFileBrowser::ShowAndGetDirectory("local|network|removable",
     ///                                                    "Test directory selection",
     ///                                                    directory,
     ///                                                    false);
     /// fprintf(stderr, "Selected directory is : %s and was %s\n", directory.c_str(), ret ? "OK" : "Canceled");
     /// \endcode
     ///
    static bool ShowAndGetDirectory(
      const std::string&      shares,
      const std::string&      heading,
      std::string&            path,
      bool                    bWriteOnly = false);

    ///
    /// \ingroup CAddonGUIDialogFileBrowser
    /// @brief File selection dialog
    ///
    /// @param shares With Shares becomes the available start folders be set.
    /// @param mask The mask to filter visible files, e.g. ".m3u|.pls|.b4s|.wpl".
    /// @param heading Dialog header name
    /// @param path Return value about selected file
    /// @param useThumbs If set show thumbs if possible on dialog.
    /// @param useFileDirectories If set also packages (e.g. *.zip) are handled
    ///        as directories.
    /// @return False if selection becomes canceled.
    ///
    static bool ShowAndGetFile(
      const std::string&      shares,
      const std::string&      mask,
      const std::string&      heading,
      std::string&            path,
      bool                    useThumbs = false,
      bool                    useFileDirectories = false);

    ///
    /// \ingroup CAddonGUIDialogFileBrowser
    /// @brief File selection from a directory
    ///
    /// @param directory The directory name where the dialog start, possible are
    ///        normal names and kodi's special names.
    /// @param mask The mask to filter visible files, e.g. ".m3u|.pls|.b4s|.wpl".
    /// @param heading Dialog header name
    /// @param path Return value about selected file
    /// @param useThumbs If set show thumbs if possible on dialog.
    /// @param useFileDirectories If set also packages (e.g. *.zip) are handled
    /// as directories.
    /// @param
    /// @return False if selection becomes canceled.
    ///
    static bool ShowAndGetFileFromDir(
      const std::string&      directory,
      const std::string&      mask,
      const std::string&      heading,
      std::string&            path,
      bool                    useThumbs = false,
      bool                    useFileDirectories = false,
      bool                    singleList = false);

    ///
    /// \ingroup CAddonGUIDialogFileBrowser
    /// @brief File selection dialog to get several in to a list
    ///
    /// @param shares With Shares becomes the available start folders be set.
    /// @param mask The mask to filter visible files, e.g. ".m3u|.pls|.b4s|.wpl".
    /// @param heading Dialog header name
    /// @param path Return value about selected files
    /// @param useThumbs If set show thumbs if possible on dialog.
    /// @param useFileDirectories If set also packages (e.g. *.zip) are handled
    ///        as directories.
    /// @return False if selection becomes canceled.
    ///
    static bool ShowAndGetFileList(
      const std::string&      shares,
      const std::string&      mask,
      const std::string&      heading,
      std::vector<std::string> &path,
      bool                    useThumbs = false,
      bool                    useFileDirectories = false);

    ///
    /// \ingroup CAddonGUIDialogFileBrowser
    /// @brief Source selection dialog
    ///
    /// @param Return value about selected source
    /// @param Allow also access to network
    /// @param With additionalShare becomes the available start folders be set.
    /// @param type
    /// @return False if selection becomes canceled.
    ///
    static bool ShowAndGetSource(
      std::string&            path,
      bool                    allowNetworkShares,
      const std::string&      additionalShare = "",
      const std::string&      type = "");

    ///
    /// \ingroup CAddonGUIDialogFileBrowser
    /// @brief Image selection dialog
    ///
    /// @param shares With Shares becomes the available start folders be set.
    /// @param heading Dialog header name
    /// @param path Return value about selected image
    /// @return False if selection becomes canceled.
    ///
    static bool ShowAndGetImage(
      const std::string&      shares,
      const std::string&      heading,
      std::string&            path);

    ///
    /// \ingroup CAddonGUIDialogFileBrowser
    /// @brief Image selection dialog to get several in to a list
    ///
    /// @param shares With Shares becomes the available start folders be set.
    /// @param heading Dialog header name
    /// @param path Return value about selected images
    /// @return False if selection becomes canceled.
    ///
    static bool ShowAndGetImageList(
      const std::string&      shares,
      const std::string&      heading,
      std::vector<std::string> &path);
  };
  /** @}*/

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_DialogFileBrowserTail.h"
