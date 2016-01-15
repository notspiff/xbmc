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

#include "addons/Addon.h"
#include "addons/binary/ExceptionHandling.h"
#include "addons/binary/callbacks/AddonCallbacks.h"
#include "guilib/GUIImage.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIControlImage.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{
extern "C"
{

void CAddonGUI_Control_Image::Init(CB_GUILib *callbacks)
{

  callbacks->Control.Image.SetVisible      = CAddonGUI_Control_Image::SetVisible;
  callbacks->Control.Image.SetFileName     = CAddonGUI_Control_Image::SetFileName;
  callbacks->Control.Image.SetColorDiffuse = CAddonGUI_Control_Image::SetColorDiffuse;
}

void CAddonGUI_Control_Image::SetVisible(void *addonData, GUIHANDLE handle, bool visible)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Image - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUIImage*>(handle)->SetVisible(visible);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Image::SetFileName(void *addonData, GUIHANDLE handle, const char* strFileName, const bool useCache)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Image - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUIImage*>(handle)->SetFileName(strFileName, false, useCache);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Image::SetColorDiffuse(void *addonData, GUIHANDLE handle, uint32_t colorDiffuse)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Image - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUIImage*>(handle)->SetColorDiffuse(colorDiffuse);
  }
  HANDLE_ADDON_EXCEPTION
}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
