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

#include "AddonCallbacksPVRBase.h"

namespace ADDON
{

int CAddonCallbacksPVRBase::APILevel()
{
  return PVRLIB::V2::CAddonCallbacksPVR::APILevel();
}

int CAddonCallbacksPVRBase::MinAPILevel()
{
  return PVRLIB::V1::CAddonCallbacksPVR::APILevel();
}

std::string CAddonCallbacksPVRBase::Version()
{
  return PVRLIB::V2::CAddonCallbacksPVR::Version();
}

std::string CAddonCallbacksPVRBase::MinVersion()
{
  return PVRLIB::V1::CAddonCallbacksPVR::Version();
}

void* CAddonCallbacksPVRBase::CreateHelper(CAddonCallbacks* addon, int level)
{
  switch (level)
  {
  case 1:
    addon->m_helperPVR = new PVRLIB::V1::CAddonCallbacksPVR(addon->m_addon);
    return static_cast<PVRLIB::V1::CAddonCallbacksPVR*>(addon->m_helperPVR)->GetCallbacks();
  case 2:
    addon->m_helperPVR = new PVRLIB::V2::CAddonCallbacksPVR(addon->m_addon);
    return static_cast<PVRLIB::V2::CAddonCallbacksPVR*>(addon->m_helperPVR)->GetCallbacks();
  };
  return nullptr;
}

void CAddonCallbacksPVRBase::DestroyHelper(CAddonCallbacks* addon)
{
  if (!addon->m_helperPVR)
    return;

  switch (static_cast<IAddonCallback*>(addon->m_helperPVR)->APILevel())
  {
  case 1:
    delete static_cast<PVRLIB::V1::CAddonCallbacksPVR*>(addon->m_helperPVR);
    break;
  case 2:
    delete static_cast<PVRLIB::V2::CAddonCallbacksPVR*>(addon->m_helperPVR);
    break;
  };
  addon->m_helperPVR = nullptr;
}

}; /* namespace ADDON */
