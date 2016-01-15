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

  typedef GUIHANDLE   GUIWindow_New
      (void        *addonData,
       const char  *xmlFilename,
       const char  *defaultSkin,
       bool         forceFallback,
       bool         asDialog);

  typedef void        GUIWindow_Delete
      (void        *addonData,
       GUIHANDLE    handle);

  typedef void        GUIWindow_SetCallbacks
      (void        *addonData,
       GUIHANDLE    handle,
       GUIHANDLE    clienthandle,
       bool (*)(GUIHANDLE handle),
       bool (*)(GUIHANDLE handle, int),
       bool (*)(GUIHANDLE handle, int),
       bool (*)(GUIHANDLE handle, int));

  typedef bool        GUIWindow_Show
      (void        *addonData,
       GUIHANDLE    handle);

  typedef bool        GUIWindow_Close
      (void        *addonData,
       GUIHANDLE    handle);

  typedef bool        GUIWindow_DoModal
      (void        *addonData,
       GUIHANDLE    handle);

  typedef bool        GUIWindow_SetFocusId
      (void        *addonData,
       GUIHANDLE    handle,
       int          iControlId);

  typedef int         GUIWindow_GetFocusId
      (void        *addonData,
       GUIHANDLE    handle);

  typedef bool        GUIWindow_SetCoordinateResolution
      (void        *addonData,
       GUIHANDLE    handle,
       int          res);

  typedef void        GUIWindow_SetProperty
      (void        *addonData,
       GUIHANDLE    handle,
       const char  *key,
       const char  *value);

  typedef void        GUIWindow_SetPropertyInt
      (void        *addonData,
       GUIHANDLE    handle,
       const char  *key,
       int          value);

  typedef void        GUIWindow_SetPropertyBool
      (void        *addonData,
       GUIHANDLE    handle,
       const char  *key,
       bool         value);

  typedef void        GUIWindow_SetPropertyDouble
      (void        *addonData,
       GUIHANDLE    handle,
       const char  *key,
       double       value);

  typedef void        GUIWindow_GetProperty
      (void        *addonData,
       GUIHANDLE    handle,
       const char  *key,
       char        &property,
       unsigned int &iMaxStringSize);

  typedef int         GUIWindow_GetPropertyInt
      (void        *addonData,
       GUIHANDLE    handle,
       const char  *key);

  typedef bool        GUIWindow_GetPropertyBool
      (void        *addonData,
       GUIHANDLE    handle,
       const char  *key);

  typedef double      GUIWindow_GetPropertyDouble
      (void        *addonData,
       GUIHANDLE    handle,
       const char  *key);

  typedef void        GUIWindow_ClearProperties
      (void        *addonData,
       GUIHANDLE    handle);

  typedef int         GUIWindow_GetListSize
      (void        *addonData,
       GUIHANDLE    handle);

  typedef void        GUIWindow_ClearList
      (void        *addonData,
       GUIHANDLE    handle);

  typedef GUIHANDLE   GUIWindow_AddItem
      (void        *addonData,
       GUIHANDLE    handle,
       GUIHANDLE    item,
       int          itemPosition);

  typedef GUIHANDLE   GUIWindow_AddStringItem
      (void        *addonData,
       GUIHANDLE    handle,
       const char  *itemName,
       int          itemPosition);

  typedef void        GUIWindow_RemoveItem
      (void        *addonData,
       GUIHANDLE    handle,
       int          itemPosition);

  typedef GUIHANDLE   GUIWindow_GetListItem
      (void        *addonData,
       GUIHANDLE    handle,
       int          listPos);

  typedef void        GUIWindow_SetCurrentListPosition
      (void        *addonData,
       GUIHANDLE    handle,
       int          listPos);

  typedef int         GUIWindow_GetCurrentListPosition
      (void        *addonData,
       GUIHANDLE    handle);

  typedef void        GUIWindow_SetControlLabel
      (void        *addonData,
       GUIHANDLE    handle,
       int          controlId,
       const char  *label);

  typedef void        GUIWindow_MarkDirtyRegion
      (void        *addonData,
       GUIHANDLE    handle);

  typedef GUIHANDLE   GUIWindow_GetControl
      (void         *addonData,
       GUIHANDLE     handle,
       int           controlId);

  typedef struct CB_GUILib_Window
  {
    GUIWindow_New*                       New;
    GUIWindow_Delete*                    Delete;
    GUIWindow_SetCallbacks*              SetCallbacks;
    GUIWindow_Show*                      Show;
    GUIWindow_Close*                     Close;
    GUIWindow_DoModal*                   DoModal;
    GUIWindow_SetFocusId*                SetFocusId;
    GUIWindow_GetFocusId*                GetFocusId;
    GUIWindow_SetCoordinateResolution*   SetCoordinateResolution;
    GUIWindow_SetProperty*               SetProperty;
    GUIWindow_SetPropertyInt*            SetPropertyInt;
    GUIWindow_SetPropertyBool*           SetPropertyBool;
    GUIWindow_SetPropertyDouble*         SetPropertyDouble;
    GUIWindow_GetProperty*               GetProperty;
    GUIWindow_GetPropertyInt*            GetPropertyInt;
    GUIWindow_GetPropertyBool*           GetPropertyBool;
    GUIWindow_GetPropertyDouble*         GetPropertyDouble;
    GUIWindow_ClearProperties*           ClearProperties;
    GUIWindow_GetListSize*               GetListSize;
    GUIWindow_ClearList*                 ClearList;
    GUIWindow_AddItem*                   AddItem;
    GUIWindow_AddStringItem*             AddStringItem;
    GUIWindow_RemoveItem*                RemoveItem;
    GUIWindow_GetListItem*               GetListItem;
    GUIWindow_SetCurrentListPosition*    SetCurrentListPosition;
    GUIWindow_GetCurrentListPosition*    GetCurrentListPosition;
    GUIWindow_SetControlLabel*           SetControlLabel;
    GUIWindow_MarkDirtyRegion*           MarkDirtyRegion;

    GUIWindow_GetControl*                GetControl_Button;
    GUIWindow_GetControl*                GetControl_Edit;
    GUIWindow_GetControl*                GetControl_FadeLabel;
    GUIWindow_GetControl*                GetControl_Image;
    GUIWindow_GetControl*                GetControl_Label;
    GUIWindow_GetControl*                GetControl_Spin;
    GUIWindow_GetControl*                GetControl_RadioButton;
    GUIWindow_GetControl*                GetControl_Progress;
    GUIWindow_GetControl*                GetControl_RenderAddon;
    GUIWindow_GetControl*                GetControl_Slider;
    GUIWindow_GetControl*                GetControl_SettingsSlider;
    GUIWindow_GetControl*                GetControl_TextBox;

  } CB_GUILib_Window;

  class CAddonGUIWindow;

  #define IMPLEMENT_ADDON_GUI_WINDOW                                           \
    protected:                                                                 \
      GUIHANDLE         m_WindowHandle;                                        \
      ADDON::AddonCB*   m_Handle;                                              \
      CB_GUILib*        m_cb;                                                  \
    private:                                                                   \
      static bool OnInitCB(GUIHANDLE cbhdl);                                   \
      static bool OnClickCB(GUIHANDLE cbhdl, int controlId);                   \
      static bool OnFocusCB(GUIHANDLE cbhdl, int controlId);                   \
      static bool OnActionCB(GUIHANDLE cbhdl, int actionId);                   \
      friend class CAddonGUIControlButton;                                     \
      friend class CAddonGUIControlEdit;                                       \
      friend class CAddonGUIControlImage;                                      \
      friend class CAddonGUIControlFadeLabel;                                  \
      friend class CAddonGUIControlLabel;                                      \
      friend class CAddonGUIControlSpin;                                       \
      friend class CAddonGUIControlProgress;                                   \
      friend class CAddonGUIControlRadioButton;                                \
      friend class CAddonGUIControlRendering;                                  \
      friend class CAddonGUIControlSlider;                                     \
      friend class CAddonGUIControlSettingsSlider;                             \
      friend class CAddonGUIControlTextBox;

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
