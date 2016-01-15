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

struct CAddonGUI_ListItem
{
  static void Init(CB_GUILib *callbacks);

  static GUIHANDLE Create(void *addonData, const char *label, const char *label2, const char *iconImage, const char *thumbnailImage, const char *path);
  static void Destroy(void *addonData, GUIHANDLE handle);
  static void GetLabel(void *addonData, GUIHANDLE handle, char &label, unsigned int &iMaxStringSize);
  static void SetLabel(void *addonData, GUIHANDLE handle, const char *label);
  static void GetLabel2(void *addonData, GUIHANDLE handle, char &label, unsigned int &iMaxStringSize);
  static void SetLabel2(void *addonData, GUIHANDLE handle, const char *label);
  static void GetIconImage(void *addonData, GUIHANDLE handle, char &image, unsigned int &iMaxStringSize);
  static void SetIconImage(void *addonData, GUIHANDLE handle, const char *image);
  static void GetOverlayImage(void *addonData, GUIHANDLE handle, char &image, unsigned int &iMaxStringSize);
  static void SetOverlayImage(void *addonData, GUIHANDLE handle, unsigned int image, bool bOnOff /* = false*/);
  static void SetThumbnailImage(void *addonData, GUIHANDLE handle, const char *image);
  static void SetArt(void *addonData, GUIHANDLE handle, const char *type, const char *url);
  static void SetArtFallback(void *addonData, GUIHANDLE handle, const char *from, const char *to);
  static bool HasArt(void *addonData, GUIHANDLE handle, const char *type);
  static void SetSortLabel(void *addonData, GUIHANDLE handle, const char *label);
  static void Select(void *addonData, GUIHANDLE handle, bool bOnOff);
  static bool IsSelected(void *addonData, GUIHANDLE handle);
  static bool HasIcon(void *addonData, GUIHANDLE handle);
  static bool HasOverlay(void *addonData, GUIHANDLE handle);
  static bool IsFileItem(void *addonData, GUIHANDLE handle);
  static bool IsFolder(void *addonData, GUIHANDLE handle);
  static void SetProperty(void *addonData, GUIHANDLE handle, const char *key, const char *value);
  static void GetProperty(void *addonData, GUIHANDLE handle, const char *key, char &property, unsigned int &iMaxStringSize);
  static void IncrementProperty(void *addonData, GUIHANDLE handle, const char *key, int nVal);
  static void ClearProperty(void *addonData, GUIHANDLE handle, const char *key);
  static void ClearProperties(void *addonData, GUIHANDLE handle);
  static bool HasProperties(void *addonData, GUIHANDLE handle);
  static bool HasProperty(void *addonData, GUIHANDLE handle, const char *key);
  static void SetPath(void *addonData, GUIHANDLE handle, const char *path);
};

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
