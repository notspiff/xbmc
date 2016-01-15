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

  typedef GUIHANDLE GUIDialog_Progress_New
      (void         *addonData);

  typedef void GUIDialog_Progress_Delete
      (void         *addonData,
       GUIHANDLE     handle);

  typedef void GUIDialog_Progress_Open
      (void         *addonData,
       GUIHANDLE     handle);

  typedef void GUIDialog_Progress_SetHeading
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *heading);

  typedef void GUIDialog_Progress_SetLine
      (void         *addonData,
       GUIHANDLE     handle,
       unsigned int  iLine,
       const char   *line);

  typedef void GUIDialog_Progress_SetCanCancel
      (void         *addonData,
       GUIHANDLE     handle,
       bool          bCanCancel);

  typedef bool GUIDialog_Progress_IsCanceled
      (void         *addonData,
       GUIHANDLE     handle);

  typedef void GUIDialog_Progress_SetPercentage
      (void         *addonData,
       GUIHANDLE     handle,
       int           iPercentage);

  typedef int GUIDialog_Progress_GetPercentage
      (void         *addonData,
       GUIHANDLE     handle);

  typedef void GUIDialog_Progress_ShowProgressBar
      (void         *addonData,
       GUIHANDLE     handle,
       bool          bOnOff);

  typedef void GUIDialog_Progress_SetProgressMax
      (void         *addonData,
       GUIHANDLE     handle,
       int           iMax);

  typedef void GUIDialog_Progress_SetProgressAdvance
      (void         *addonData,
       GUIHANDLE     handle,
       int           nSteps);

  typedef bool GUIDialog_Progress_Abort
      (void         *addonData,
       GUIHANDLE     handle);

  typedef struct CB_GUILib_Dialog_Progress
  {
    GUIDialog_Progress_New*                New;
    GUIDialog_Progress_Delete*             Delete;
    GUIDialog_Progress_Open*               Open;
    GUIDialog_Progress_SetHeading*         SetHeading;
    GUIDialog_Progress_SetLine*            SetLine;
    GUIDialog_Progress_SetCanCancel*       SetCanCancel;
    GUIDialog_Progress_IsCanceled*         IsCanceled;
    GUIDialog_Progress_SetPercentage*      SetPercentage;
    GUIDialog_Progress_GetPercentage*      GetPercentage;
    GUIDialog_Progress_ShowProgressBar*    ShowProgressBar;
    GUIDialog_Progress_SetProgressMax*     SetProgressMax;
    GUIDialog_Progress_SetProgressAdvance* SetProgressAdvance;
    GUIDialog_Progress_Abort*              Abort;
  } CB_GUILib_Dialog_Progress;

  #define IMPL_GUI_PROGRESS_DIALOG              \
    private:                                    \
      GUIHANDLE         m_DialogHandle;         \
      ADDON::AddonCB*   m_Handle;               \
      CB_GUILib*        m_cb;

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
