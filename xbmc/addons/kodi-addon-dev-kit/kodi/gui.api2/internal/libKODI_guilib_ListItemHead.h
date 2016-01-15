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

  typedef GUIHANDLE   GUIListItem_Create
      (void         *addonData,
       const char   *label,
       const char   *label2,
       const char   *iconImage,
       const char   *thumbnailImage,
       const char   *path);

  typedef void        GUIListItem_Destroy
      (void         *addonData,
       GUIHANDLE     handle);

  typedef void        GUIListItem_GetLabel
      (void         *addonData,
       GUIHANDLE     handle,
       char         &label,
       unsigned int &iMaxStringSize);

  typedef void        GUIListItem_SetLabel
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *label);

  typedef void        GUIListItem_GetLabel2
      (void         *addonData,
       GUIHANDLE     handle,
       char         &label,
       unsigned int &iMaxStringSize);

  typedef void        GUIListItem_SetLabel2
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *label);

  typedef void        GUIListItem_GetIconImage
      (void         *addonData,
       GUIHANDLE     handle,
       char         &image,
       unsigned int &iMaxStringSize);

  typedef void        GUIListItem_SetIconImage
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *image);

  typedef void        GUIListItem_GetOverlayImage
      (void         *addonData,
       GUIHANDLE     handle,
       char         &image,
       unsigned int &iMaxStringSize);

  typedef void        GUIListItem_SetOverlayImage
      (void         *addonData,
       GUIHANDLE     handle,
       unsigned int  image,
       bool          bOnOff);

  typedef void        GUIListItem_SetThumbnailImage
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *image);

  typedef void        GUIListItem_SetArt
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *type,
       const char   *url);

  typedef void        GUIListItem_SetArtFallback
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *from,
       const char   *to);

  typedef void        GUIListItem_SetLabel
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *label);

  typedef bool        GUIListItem_HasArt
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *type);

  typedef void        GUIListItem_SetSortLabel
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *image);

  typedef void        GUIListItem_Select
      (void         *addonData,
       GUIHANDLE     handle,
       bool          bOnOff);

  typedef bool        GUIListItem_IsSelected
      (void         *addonData,
       GUIHANDLE     handle);

  typedef bool        GUIListItem_HasIcon
      (void         *addonData,
       GUIHANDLE     handle);

  typedef bool        GUIListItem_HasOverlay
      (void         *addonData,
       GUIHANDLE     handle);

  typedef bool        GUIListItem_IsFileItem
      (void         *addonData,
       GUIHANDLE     handle);

  typedef bool        GUIListItem_IsFolder
      (void         *addonData,
       GUIHANDLE     handle);

  typedef void        GUIListItem_SetProperty
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *key,
       const char   *value);

  typedef void        GUIListItem_GetProperty
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *key,
       char         &property,
       unsigned int &iMaxStringSize);

  typedef void        GUIListItem_IncrementProperty
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *key,
       int           nVal);

  typedef void        GUIListItem_ClearProperty
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *key);

  typedef void        GUIListItem_ClearProperties
      (void         *addonData,
       GUIHANDLE     handle);

  typedef bool        GUIListItem_HasProperties
      (void         *addonData,
       GUIHANDLE     handle);

  typedef bool        GUIListItem_HasProperty
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *key);

  typedef void        GUIListItem_SetPath
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *path);

  typedef struct CB_GUILib_ListItem
  {
    GUIListItem_Create*                  Create;
    GUIListItem_Destroy*                 Destroy;
    GUIListItem_GetLabel*                GetLabel;
    GUIListItem_SetLabel*                SetLabel;
    GUIListItem_GetLabel2*               GetLabel2;
    GUIListItem_SetLabel2*               SetLabel2;
    GUIListItem_GetIconImage*            GetIconImage;
    GUIListItem_SetIconImage*            SetIconImage;
    GUIListItem_GetOverlayImage*         GetOverlayImage;
    GUIListItem_SetOverlayImage*         SetOverlayImage;
    GUIListItem_SetThumbnailImage*       SetThumbnailImage;
    GUIListItem_SetArt*                  SetArt;
    GUIListItem_SetArtFallback*          SetArtFallback;
    GUIListItem_HasArt*                  HasArt;
    GUIListItem_SetSortLabel*            SetSortLabel;
    GUIListItem_Select*                  Select;
    GUIListItem_IsSelected*              IsSelected;
    GUIListItem_HasIcon*                 HasIcon;
    GUIListItem_HasOverlay*              HasOverlay;
    GUIListItem_IsFileItem*              IsFileItem;
    GUIListItem_IsFolder*                IsFolder;
    GUIListItem_SetProperty*             SetProperty;
    GUIListItem_GetProperty*             GetProperty;
    GUIListItem_IncrementProperty*       IncrementProperty;
    GUIListItem_ClearProperty*           ClearProperty;
    GUIListItem_ClearProperties*         ClearProperties;
    GUIListItem_HasProperties*           HasProperties;
    GUIListItem_HasProperty*             HasProperty;
    GUIListItem_SetPath*                 SetPath;
  } CB_GUILib_ListItem;

  class CAddonGUIListItem;

  #define IMPL_ADDON_GUI_LIST                   \
    public:                                     \
      const GUIHANDLE GetListItemHandle() const \
      {                                         \
        return m_ListItemHandle;                \
      }                                         \
    protected:                                  \
      GUIHANDLE         m_ListItemHandle;       \
      ADDON::AddonCB*   m_Handle;               \
      CB_GUILib*        m_cb;                   \
    private:                                    \
      friend class CAddonGUIWindow;

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
