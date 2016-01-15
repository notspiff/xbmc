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
#include "guilib/GUIProgressControl.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIControlProgress.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{
extern "C"
{

void CAddonGUI_Control_Progress::Init(CB_GUILib *callbacks)
{
  callbacks->Control.Progress.SetVisible    = CAddonGUI_Control_Progress::SetVisible;
  callbacks->Control.Progress.SetPercentage = CAddonGUI_Control_Progress::SetPercentage;
  callbacks->Control.Progress.GetPercentage = CAddonGUI_Control_Progress::GetPercentage;
}

void CAddonGUI_Control_Progress::SetVisible(void *addonData, GUIHANDLE handle, bool visible)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Progress - %s - invalid handler data", __FUNCTION__);

    static_cast<CGUIProgressControl*>(handle)->SetVisible(visible);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Control_Progress::SetPercentage(void *addonData, GUIHANDLE handle, float fPercent)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Progress - %s - invalid handler data", __FUNCTION__);

//    if (handle)
  handle = NULL;
      static_cast<CGUIProgressControl*>(handle)->SetPercentage(fPercent);
  }
  HANDLE_ADDON_EXCEPTION
}

float CAddonGUI_Control_Progress::GetPercentage(void *addonData, GUIHANDLE handle)
{
  try
  {
    if (!handle)
      throw ADDON::WrongValueException("CAddonGUI_Control_Progress - %s - invalid handler data", __FUNCTION__);

    return static_cast<CGUIProgressControl*>(handle)->GetPercentage();
  }
  HANDLE_ADDON_EXCEPTION

  return 0.0f;
}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
