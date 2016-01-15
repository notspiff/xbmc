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
#include "internal/libKODI_guilib_ControlRenderingHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  ///
  /// \defgroup CAddonGUIControlRendering
  /// \ingroup GUILIB
  /// @{
  /// @brief <b>Window control for rendering own parts</b>
  ///
  /// This rendering control is used when own parts are needed. You have the
  /// control over them to render direct OpenGL or DirectX content to the
  /// screen set by the size of them.
  ///
  /// It has the header \ref GUIControlRendering.h "#include <kodi/gui.api2/GUIControlRendering.h>" be included
  /// to enjoy it.
  ///
  /// @note The call of the control is only possible from the corresponding
  /// window as its class and identification number is required.
  ///
  class CAddonGUIControlRendering
  {
  public:

    ///
    /// \ingroup CAddonGUIControlRendering
    /// @brief
    ///
    ///
    ///
    CAddonGUIControlRendering(CAddonGUIWindow* window, int controlId);

    ///
    /// \ingroup CAddonGUIControlRendering
    /// @brief
    ///
    ///
    ///
    virtual ~CAddonGUIControlRendering();

    ///
    /// \ingroup CAddonGUIControlRendering
    /// @brief
    ///
    ///
    ///
    virtual bool Create(int x, int y, int w, int h, void* device) { return false; }

    ///
    /// \ingroup CAddonGUIControlRendering
    /// @brief
    ///
    ///
    ///
    virtual void Render() { }

    ///
    /// \ingroup CAddonGUIControlRendering
    /// @brief
    ///
    ///
    ///
    virtual void Stop() { }

    ///
    /// \ingroup CAddonGUIControlRendering
    /// @brief
    ///
    ///
    ///
    virtual bool Dirty() { return false; }

    ///
    /// @brief If the class is used independent (with "new CAddonGUIControlRendering")
    /// and not as parent (with "cCLASS_own : CAddonGUIControlRendering") from own must
    /// be the callback from Kodi to add-on overdriven with own functions!
    ///
    void SetIndependentCallbacks(
        GUIHANDLE             cbhdl,
        bool      (*CBCreate)(GUIHANDLE cbhdl,
                              int       x,
                              int       y,
                              int       w,
                              int       h,
                              void*     device),
        void      (*CBRender)(GUIHANDLE cbhdl),
        void      (*CBStop)  (GUIHANDLE cbhdl),
        bool      (*CBDirty) (GUIHANDLE cbhdl));

    IMPL_GUI_RENDERING_CONTROL;
  };
  /** @}*/

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_ControlRenderingTail.h"
