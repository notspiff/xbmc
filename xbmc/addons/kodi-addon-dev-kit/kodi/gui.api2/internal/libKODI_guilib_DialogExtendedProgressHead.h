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

  class CAddonGUIDialogExtendedProgress;

  typedef GUIHANDLE GUIDialog_ExtendedProgress_New
      (void         *addonData,
       const char   *title);

  typedef void GUIDialog_ExtendedProgress_Delete
      (void         *addonData,
       GUIHANDLE     handle);

  typedef void GUIDialog_ExtendedProgress_Title
      (void         *addonData,
       GUIHANDLE     handle,
       char         &title,
       unsigned int &iMaxStringSize);

  typedef void GUIDialog_ExtendedProgress_SetTitle
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *title);

  typedef void GUIDialog_ExtendedProgress_Text
      (void         *addonData,
       GUIHANDLE     handle,
       char         &text,
       unsigned int &iMaxStringSize);

  typedef void GUIDialog_ExtendedProgress_SetText
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *text);

  typedef bool GUIDialog_ExtendedProgress_IsFinished
      (void         *addonData,
       GUIHANDLE     handle);

  typedef void GUIDialog_ExtendedProgress_MarkFinished
      (void         *addonData,
       GUIHANDLE     handle);

  typedef float GUIDialog_ExtendedProgress_Percentage
      (void         *addonData,
       GUIHANDLE     handle);

  typedef void GUIDialog_ExtendedProgress_SetPercentage
      (void         *addonData,
       GUIHANDLE     handle,
       float         fPercentage);

  typedef void GUIDialog_ExtendedProgress_SetProgress
      (void         *addonData,
       GUIHANDLE     handle,
       int           currentItem,
       int           itemCount);

  typedef struct CB_GUILib_Dialog_ExtendedProgress
  {
    GUIDialog_ExtendedProgress_New*            New;
    GUIDialog_ExtendedProgress_Delete*         Delete;
    GUIDialog_ExtendedProgress_Title*          Title;
    GUIDialog_ExtendedProgress_SetTitle*       SetTitle;
    GUIDialog_ExtendedProgress_Text*           Text;
    GUIDialog_ExtendedProgress_SetText*        SetText;
    GUIDialog_ExtendedProgress_IsFinished*     IsFinished;
    GUIDialog_ExtendedProgress_MarkFinished*   MarkFinished;
    GUIDialog_ExtendedProgress_Percentage*     Percentage;
    GUIDialog_ExtendedProgress_SetPercentage*  SetPercentage;
    GUIDialog_ExtendedProgress_SetProgress*    SetProgress;
  } CB_GUILib_Dialog_ExtendedProgress;

  #define IMPL_GUI_EXTENDED_PROGRESS_DIALOG     \
    private:                                    \
      GUIHANDLE         m_DialogHandle;         \
      ADDON::AddonCB*   m_Handle;               \
      CB_GUILib*        m_cb;

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
