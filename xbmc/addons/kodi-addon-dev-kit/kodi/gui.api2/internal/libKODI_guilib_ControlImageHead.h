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

  class CAddonGUIWindow;
  class CAddonGUIControlImage;

  typedef void GUIControl_Image_SetVisible(
       void         *addonData,
       GUIHANDLE     handle,
       bool          visible);

  typedef void GUIControl_Image_SetFileName(
       void         *addonData,
       GUIHANDLE     handle,
       const char*   strFileName,
       const bool    useCache);

  typedef void GUIControl_Image_SetColorDiffuse(
       void         *addonData,
       GUIHANDLE     handle,
       uint32_t      colorDiffuse);

  typedef struct CB_GUILib_Control_Image
  {
    GUIControl_Image_SetVisible*       SetVisible;
    GUIControl_Image_SetFileName*      SetFileName;
    GUIControl_Image_SetColorDiffuse*  SetColorDiffuse;
  } CB_GUILib_Control_Image;

  #define IMPL_GUI_IMAGE_CONTROL                \
    private:                                    \
      CAddonGUIWindow*  m_Window;               \
      int               m_ControlId;            \
      GUIHANDLE         m_ControlHandle;        \
      ADDON::AddonCB*   m_Handle;               \
      CB_GUILib*        m_cb;

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
