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
#include "internal/libKODI_guilib_DialogExtendedProgressHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  ///
  /// \defgroup CAddonGUIDialogExtendedProgress
  /// \ingroup GUILIB
  /// @{
  /// @brief <b>Progress dialog shown for background work</b>
  ///
  /// The with \ref GUIDialogExtendedProgress.h "#include <kodi/addon.api2/GUIDialogExtendedProgress.h>"
  /// given class are basically used to create Kodi's extended progress
  ///
  /// \image html help.GUIDialogExtendedProgress.png
  ///
  /// <b>Code example:</b>
  /// \code
  /// #include <kodi/addon.api2/GUIDialogExtendedProgress.h>
  ///
  /// CAddonGUIDialogExtendedProgress *ext_progress = new CAddonGUIDialogExtendedProgress("Test Extended progress");
  /// ext_progress->SetText("Test progress");
  /// for (unsigned int i = 0; i < 50; i += 10)
  /// {
  ///   ext_progress->SetProgress(i, 100);
  ///   sleep(1);
  /// }
  ///
  /// ext_progress->SetTitle("Test Extended progress - Second round");
  /// ext_progress->SetText("Test progress - Step 2");
  ///
  /// for (unsigned int i = 50; i < 100; i += 10)
  /// {
  ///   ext_progress->SetProgress(i, 100);
  ///   sleep(1);
  /// }
  /// delete ext_progress;
  /// \endcode
  ///
  class CAddonGUIDialogExtendedProgress
  {
  public:
    ///
    /// \ingroup CAddonGUIDialogExtendedProgress
    /// Construct a new dialog
    ///
    /// @param title Title string
    ///
    CAddonGUIDialogExtendedProgress(const std::string& title = "");

    ///
    /// \ingroup CAddonGUIDialogExtendedProgress
    /// Destructor
    ///
    ~CAddonGUIDialogExtendedProgress();

    ///
    /// \ingroup CAddonGUIDialogExtendedProgress
    /// @brief Get the used title
    ///
    /// @return Title string
    ///
    std::string Title() const;

    ///
    /// \ingroup CAddonGUIDialogExtendedProgress
    /// @brief To set the title of dialog
    ///
    /// @param strTitle Title string
    ///
    void SetTitle(const std::string& strTitle);

    ///
    /// \ingroup CAddonGUIDialogExtendedProgress
    /// @brief Get the used text information string
    ///
    /// @return Text string
    ///
    std::string Text() const;

    ///
    /// \ingroup CAddonGUIDialogExtendedProgress
    /// @brief To set the used text information string
    ///
    /// @param strText
    ///
    void SetText(const std::string& strText);

    ///
    /// \ingroup CAddonGUIDialogExtendedProgress
    /// @brief To ask dialog is finished
    ///
    /// @return True if on end
    ///
    bool IsFinished() const;

    ///
    /// \ingroup CAddonGUIDialogExtendedProgress
    /// @brief Mark progress finished
    ///
    void MarkFinished();

    ///
    /// \ingroup CAddonGUIDialogExtendedProgress
    /// @brief Get the current progress position as percent
    ///
    /// @return Position
    ///
    float Percentage() const;

    ///
    /// \ingroup CAddonGUIDialogExtendedProgress
    /// @brief To set the current progress position as percent
    ///
    /// @param fPercentage Position to use from 0.0 to 100.0
    ///
    void SetPercentage(float fPercentage);

    ///
    /// \ingroup CAddonGUIDialogExtendedProgress
    /// @brief To set progress position with predefined places
    ///
    /// @param currentItem Place position to use
    /// @param itemCount Amount of used places
    ///
    void SetProgress(int currentItem, int itemCount);

    IMPL_GUI_EXTENDED_PROGRESS_DIALOG;
  };
  /** @}*/

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_DialogExtendedProgressTail.h"
