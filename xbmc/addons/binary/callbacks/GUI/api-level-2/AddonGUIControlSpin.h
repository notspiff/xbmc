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

  class CAddonGUI_Control_Spin
  {
  public:
    static void Init(CB_GUILib *callbacks);

    static void SetVisible(void *addonData, GUIHANDLE handle, bool visible);
    static void SetEnabled(void *addonData, GUIHANDLE handle, bool enabled);

    static void SetText(void *addonData, GUIHANDLE handle, const char *text);
    static void Reset(void *addonData, GUIHANDLE handle);
    static void SetType(void *addonData, GUIHANDLE handle, int type);

    static void AddStringLabel(void *addonData, GUIHANDLE handle, const char* label, const char* value);
    static void AddIntLabel(void *addonData, GUIHANDLE handle, const char* label, int value);

    static void SetStringValue(void *addonData, GUIHANDLE handle, const char* value);
    static void GetStringValue(void *addonData, GUIHANDLE handle, char &value, unsigned int &maxStringSize);

    static void SetIntRange(void *addonData, GUIHANDLE handle, int start, int end);
    static void SetIntValue(void *addonData, GUIHANDLE handle, int value);
    static int GetIntValue(void *addonData, GUIHANDLE handle);

    static void SetFloatRange(void *addonData, GUIHANDLE handle, float start, float end);
    static void SetFloatValue(void *addonData, GUIHANDLE handle, float value);
    static float GetFloatValue(void *addonData, GUIHANDLE handle);
    static void SetFloatInterval(void *addonData, GUIHANDLE handle, float interval);
  };

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
