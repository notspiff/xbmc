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
#include "guilib/GUIWindowManager.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIGeneral.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{

int CAddonGUI_General::m_iAddonGUILockRef = 0;

extern "C"
{

void CAddonGUI_General::Init(CB_GUILib *callbacks)
{
  callbacks->General.Lock                     = CAddonGUI_General::Lock;
  callbacks->General.Unlock                   = CAddonGUI_General::Unlock;
  callbacks->General.GetScreenHeight          = CAddonGUI_General::GetScreenHeight;
  callbacks->General.GetScreenWidth           = CAddonGUI_General::GetScreenWidth;
  callbacks->General.GetVideoResolution       = CAddonGUI_General::GetVideoResolution;
  callbacks->General.GetCurrentWindowDialogId = CAddonGUI_General::GetCurrentWindowDialogId;
  callbacks->General.GetCurrentWindowId       = CAddonGUI_General::GetCurrentWindowId;
}

//@{
void CAddonGUI_General::Lock()
{
  if (m_iAddonGUILockRef == 0)
    g_graphicsContext.Lock();
  ++m_iAddonGUILockRef;
}

void CAddonGUI_General::Unlock()
{
  if (m_iAddonGUILockRef > 0)
  {
    --m_iAddonGUILockRef;
    if (m_iAddonGUILockRef == 0)
      g_graphicsContext.Unlock();
  }
}
//@}

//@{
int CAddonGUI_General::GetScreenHeight()
{
  try
  {
    return g_graphicsContext.GetHeight();
  }
  HANDLE_ADDON_EXCEPTION

  return -1;
}

int CAddonGUI_General::GetScreenWidth()
{
  try
  {
    return g_graphicsContext.GetWidth();
  }
  HANDLE_ADDON_EXCEPTION

  return -1;
}

int CAddonGUI_General::GetVideoResolution()
{
  try
  {
    return (int)g_graphicsContext.GetVideoResolution();
  }
  HANDLE_ADDON_EXCEPTION

  return -1;
}
//@}

//@{
int CAddonGUI_General::GetCurrentWindowDialogId()
{
  try
  {
    CSingleLock gl(g_graphicsContext);
    return g_windowManager.GetTopMostModalDialogID();
  }
  HANDLE_ADDON_EXCEPTION

  return -1;
}

int CAddonGUI_General::GetCurrentWindowId()
{
  try
  {
    CSingleLock gl(g_graphicsContext);
    return g_windowManager.GetActiveWindow();
  }
  HANDLE_ADDON_EXCEPTION

  return -1;
}
//@}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
