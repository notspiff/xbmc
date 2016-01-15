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

#include "AddonCallbacksGUIBase.h"

#include "messaging/ApplicationMessenger.h"

using namespace KODI::MESSAGING;

namespace ADDON
{

int CAddonCallbacksGUIBase::APILevel()
{
  return GUILIB::V2::CAddonCallbacksGUI::APILevel();
}

int CAddonCallbacksGUIBase::MinAPILevel()
{
  return GUILIB::V1::CAddonCallbacksGUI::APILevel();
}

std::string CAddonCallbacksGUIBase::Version()
{
  return GUILIB::V2::CAddonCallbacksGUI::Version();
}

std::string CAddonCallbacksGUIBase::MinVersion()
{
  return GUILIB::V1::CAddonCallbacksGUI::Version();
}

void* CAddonCallbacksGUIBase::CreateHelper(CAddonCallbacks* addon, int level)
{
  switch (level)
  {
  case 1:
    addon->m_helperGUI = new GUILIB::V1::CAddonCallbacksGUI(addon->m_addon);
    return static_cast<GUILIB::V1::CAddonCallbacksGUI*>(addon->m_helperGUI)->GetCallbacks();
  case 2:
    addon->m_helperGUI = new GUILIB::V2::CAddonCallbacksGUI(addon->m_addon);
    return static_cast<GUILIB::V2::CAddonCallbacksGUI*>(addon->m_helperGUI)->GetCallbacks();
  };
  return nullptr;
}

void CAddonCallbacksGUIBase::DestroyHelper(CAddonCallbacks* addon)
{
  if (!addon->m_helperGUI)
    return;

  switch (static_cast<IAddonCallback*>(addon->m_helperGUI)->APILevel())
  {
  case 1:
    delete static_cast<GUILIB::V1::CAddonCallbacksGUI*>(addon->m_helperGUI);
    break;
  case 2:
    delete static_cast<GUILIB::V2::CAddonCallbacksGUI*>(addon->m_helperGUI);
    break;
  };
  addon->m_helperGUI = nullptr;
}

void CAddonCallbacksGUIBase::OnApplicationMessage(ThreadMessage* pMsg)
{
  switch (pMsg->dwMessage)
  {
  case TMSG_GUI_ADDON_DIALOG:
  {
    if (pMsg->lpVoid)
    { // TODO: This is ugly - really these binary add-on dialogs should just be normal Kodi dialogs
      switch (pMsg->param1)
      {
      case 1:
        static_cast<GUILIB::V1::CGUIAddonWindowDialog*>(pMsg->lpVoid)->Show_Internal(pMsg->param2 > 0);
        break;
      case 2:
        static_cast<GUILIB::V2::CGUIAddonWindowDialog*>(pMsg->lpVoid)->Show_Internal(pMsg->param2 > 0);
        break;
      };
    }
  }
  break;
  }
}

}; /* namespace ADDON */
