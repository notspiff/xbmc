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

#include "addons/kodi-addon-dev-kit/kodi/gui.api2/GUILib.h"

namespace GUILIB
{
namespace V2
{
extern "C"
{

  struct CB_GUILib;

  struct CAddonGUI_Control_Image
  {
    static void Init(CB_GUILib *callbacks);

    static void SetVisible(void *addonData, GUIHANDLE handle, bool visible);
    static void SetFileName(void *addonData, GUIHANDLE handle, const char* strFileName, const bool useCache);
    static void SetColorDiffuse(void *addonData, GUIHANDLE handle, uint32_t colorDiffuse);
  };

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
