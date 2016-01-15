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

  class CAddonGUIDialogYesNo;

  typedef bool GUIDialog_YesNo_ShowAndGetInputSingleText
      (const char *heading,
       const char *text,
       bool       &bCanceled,
       const char *noLabel,
       const char *yesLabel);

  typedef bool GUIDialog_YesNo_ShowAndGetInputLineText
      (const char *heading,
       const char *line0,
       const char *line1,
       const char *line2,
       const char *noLabel,
       const char *yesLabel);

  typedef bool GUIDialog_YesNo_ShowAndGetInputLineButtonText
      (const char *heading,
       const char *line0,
       const char *line1,
       const char *line2,
       bool       &bCanceled,
       const char *noLabel,
       const char *yesLabel);

  typedef struct CB_GUILib_Dialog_YesNo
  {
    GUIDialog_YesNo_ShowAndGetInputSingleText*     ShowAndGetInputSingleText;
    GUIDialog_YesNo_ShowAndGetInputLineText*       ShowAndGetInputLineText;
    GUIDialog_YesNo_ShowAndGetInputLineButtonText* ShowAndGetInputLineButtonText;
  } CB_GUILib_Dialog_YesNo;

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
