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
  class CAddonGUIControlRendering;

  typedef void GUIRenderAddon_SetCallbacks
      (void       *addonData, GUIHANDLE handle,
       GUIHANDLE   clienthandle,
       bool        (*createCB)(GUIHANDLE,int,int,int,int,void*),
       void        (*renderCB)(GUIHANDLE),
       void        (*stopCB)(GUIHANDLE),
       bool        (*dirtyCB)(GUIHANDLE));

  typedef void GUIRenderAddon_Delete
      (void       *addonData,
       GUIHANDLE   handle);

  typedef struct CB_GUILib_Control_Rendering
  {
    GUIRenderAddon_SetCallbacks*         SetCallbacks;
    GUIRenderAddon_Delete*               Delete;
  } CB_GUILib_Control_Rendering;

  #define IMPL_GUI_RENDERING_CONTROL                                           \
    private:                                                                   \
      CAddonGUIWindow*  m_Window;                                              \
      int               m_ControlId;                                           \
      GUIHANDLE         m_ControlHandle;                                       \
      ADDON::AddonCB*   m_Handle;                                              \
      CB_GUILib*        m_cb;                                                  \
      static bool OnCreateCB(GUIHANDLE cbhdl, int x, int y, int w, int h, void* device); \
      static void OnRenderCB(GUIHANDLE cbhdl);                                 \
      static void OnStopCB(GUIHANDLE cbhdl);                                   \
      static bool OnDirtyCB(GUIHANDLE cbhdl);

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
