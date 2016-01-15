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

#include "AddonCallbacksAddonBase.h"

namespace ADDON
{

int CAddonCallbacksAddonBase::APILevel()
{
  return AddOnLIB::V2::CAddonCallbacksAddon::APILevel();
}

int CAddonCallbacksAddonBase::MinAPILevel()
{
  return AddOnLIB::V1::CAddonCallbacksAddon::APILevel();
}

std::string CAddonCallbacksAddonBase::Version()
{
  return AddOnLIB::V2::CAddonCallbacksAddon::Version();
}

std::string CAddonCallbacksAddonBase::MinVersion()
{
  return AddOnLIB::V1::CAddonCallbacksAddon::Version();
}

void* CAddonCallbacksAddonBase::CreateHelper(CAddonCallbacks* addon, int level)
{
  switch (level)
  {
  case 1:
    addon->m_helperAddOn = new AddOnLIB::V1::CAddonCallbacksAddon(addon->m_addon);
    return static_cast<AddOnLIB::V1::CAddonCallbacksAddon*>(addon->m_helperAddOn)->GetCallbacks();
  case 2:
    addon->m_helperAddOn = new AddOnLIB::V2::CAddonCallbacksAddon(addon->m_addon);
    return static_cast<AddOnLIB::V2::CAddonCallbacksAddon*>(addon->m_helperAddOn)->GetCallbacks();
  };
  return nullptr;
}

void CAddonCallbacksAddonBase::DestroyHelper(CAddonCallbacks* addon)
{
  if (!addon->m_helperAddOn)
    return;

  switch (static_cast<IAddonCallback*>(addon->m_helperAddOn)->APILevel())
  {
  case 1:
    delete static_cast<AddOnLIB::V1::CAddonCallbacksAddon*>(addon->m_helperAddOn);
    break;
  case 2:
    delete static_cast<AddOnLIB::V2::CAddonCallbacksAddon*>(addon->m_helperAddOn);
    break;
  };
  addon->m_helperAddOn = nullptr;
}

}; /* namespace ADDON */
