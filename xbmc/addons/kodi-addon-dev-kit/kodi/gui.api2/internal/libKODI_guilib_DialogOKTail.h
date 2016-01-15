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

  inline void CAddonGUIDialogOK::ShowAndGetInput(
          const std::string&      heading,
          const std::string&      text)
  {
    CGUILib::g_libKODI_Internal->m_Callbacks->Dialogs.OK.ShowAndGetInputSingleText(heading.c_str(), text.c_str());
  }

  inline void CAddonGUIDialogOK::ShowAndGetInput(
          const std::string&      heading,
          const std::string&      line0,
          const std::string&      line1,
          const std::string&      line2)
  {
    CGUILib::g_libKODI_Internal->m_Callbacks->Dialogs.OK.ShowAndGetInputLineText(heading.c_str(), line0.c_str(), line1.c_str(), line2.c_str());
  }

}; /* namespace V2 */
}; /* namespace GUILIB */
