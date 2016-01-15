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

  inline bool CAddonGUIDialogYesNo::ShowAndGetInput(
          const std::string&      heading,
          const std::string&      text,
          bool&                   bCanceled,
          const std::string&      noLabel,
          const std::string&      yesLabel)
  {
    return CGUILib::g_libKODI_Internal->m_Callbacks->Dialogs.YesNo.ShowAndGetInputSingleText(heading.c_str(), text.c_str(), bCanceled, noLabel.c_str(), yesLabel.c_str());
  }

  inline bool CAddonGUIDialogYesNo::ShowAndGetInput(
          const std::string&      heading,
          const std::string&      line0,
          const std::string&      line1,
          const std::string&      line2,
          const std::string&      noLabel,
          const std::string&      yesLabel)
  {
    return CGUILib::g_libKODI_Internal->m_Callbacks->Dialogs.YesNo.ShowAndGetInputLineText(heading.c_str(), line0.c_str(), line1.c_str(), line2.c_str(), noLabel.c_str(), yesLabel.c_str());
  }

  inline bool CAddonGUIDialogYesNo::ShowAndGetInput(
          const std::string&      heading,
          const std::string&      line0,
          const std::string&      line1,
          const std::string&      line2,
          bool&                   bCanceled,
          const std::string&      noLabel,
          const std::string&      yesLabel)
  {
    return CGUILib::g_libKODI_Internal->m_Callbacks->Dialogs.YesNo.ShowAndGetInputLineButtonText(heading.c_str(), line0.c_str(), line1.c_str(), line2.c_str(), bCanceled, noLabel.c_str(), yesLabel.c_str());
  }

}; /* namespace V2 */
}; /* namespace GUILIB */
