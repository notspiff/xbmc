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
#include "internal/libKODI_guilib_DialogProgressHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  ///
  /// \ingroup GUILIB
  /// \defgroup CAddonGUIDialogProgress
  /// @{
  /// @brief <b>Progress dialog shown in center</b>
  ///
  /// The with #include \ref GUIDialogProgress.h "<kodi/addon.api2/GUIDialogProgress.h>"
  /// given class are basically used to create Kodi's progress dialog with named
  /// text fields.
  ///
  /// \image html help.GUIDialogProgress.png
  ///
  /// <b>Code example:</b>
  /// \code
  /// #include <kodi/addon.api2/GUIDialogProgress.h>
  ///
  /// CAddonGUIDialogProgress *progress = new CAddonGUIDialogProgress;
  /// progress->SetHeading("Test progress");
  /// progress->SetLine(1, "line 1");
  /// progress->SetLine(2, "line 2");
  /// progress->SetLine(3, "line 3");
  /// progress->SetCanCancel(true);
  /// progress->ShowProgressBar(true);
  /// progress->Open();
  /// for (unsigned int i = 0; i < 100; i += 10)
  /// {
  ///   progress->SetPercentage(i);
  ///   sleep(1);
  /// }
  /// delete progress;
  /// \endcode
  ///
  class CAddonGUIDialogProgress
  {
  public:
    ///
    /// \ingroup CAddonGUIDialogProgress
    /// @brief Construct a new dialog
    ///
    CAddonGUIDialogProgress();

    ///
    /// \ingroup CAddonGUIDialogProgress
    /// @brief Destructor
    ///
    ~CAddonGUIDialogProgress();

    ///
    /// \ingroup CAddonGUIDialogProgress
    /// @brief To open the dialog
    ///
    void Open();

    ///
    /// \ingroup CAddonGUIDialogProgress
    /// @brief Set the heading title of dialog
    ///
    /// @param heading Title string to use
    ///
    void SetHeading(const std::string& heading);

    ///
    /// \ingroup CAddonGUIDialogProgress
    /// @brief To set the line text field on dialog from 0 - 2
    ///
    /// @param iLine Line number
    /// @param line Text string
    ///
    void SetLine(unsigned int iLine, const std::string& line);

    ///
    /// \ingroup CAddonGUIDialogProgress
    /// @brief To enable and show cancel button on dialog
    ///
    /// @param bCanCancel if true becomes it shown
    ///
    void SetCanCancel(bool bCanCancel);

    ///
    /// \ingroup CAddonGUIDialogProgress
    /// @brief To check dialog for clicked cancel button
    ///
    /// @return True if canceled
    ///
    bool IsCanceled() const;

    ///
    /// \ingroup CAddonGUIDialogProgress
    /// @brief Get the current progress position as percent
    ///
    /// @return Position
    ///
    void SetPercentage(int iPercentage);

    ///
    /// \ingroup CAddonGUIDialogProgress
    /// @brief To set the current progress position as percent
    ///
    /// @param fPercentage Position to use from 0.0 to 100.0
    ///
    int GetPercentage() const;

    ///
    /// \ingroup CAddonGUIDialogProgress
    /// @brief To show or hide progress bar dialog
    ///
    /// @param bOnOff If true becomes it shown
    ///
    void ShowProgressBar(bool bOnOff);

    ///
    /// \ingroup CAddonGUIDialogProgress
    /// @brief Set the maximum position of progress, needed if `SetProgressAdvance(...)` is used
    ///
    /// @param iMax Biggest usable position to use
    ///
    void SetProgressMax(int iMax);

    ///
    /// \ingroup CAddonGUIDialogProgress
    /// @brief To increase progress bar by defined step size until reach of maximum position
    ///
    /// @param nSteps Step size to increase, default is 1
    ///
    void SetProgressAdvance(int nSteps=1);

    ///
    /// \ingroup CAddonGUIDialogProgress
    /// @brief To check progress was canceled on work
    ///
    /// @return True if aborted
    ///
    bool Abort();

    IMPL_GUI_PROGRESS_DIALOG;
  };
  /** @}*/

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_DialogProgressTail.h"
