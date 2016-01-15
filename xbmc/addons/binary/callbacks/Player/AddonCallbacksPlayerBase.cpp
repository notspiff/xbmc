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

#include "AddonCallbacksPlayerBase.h"

namespace ADDON
{

int CAddonCallbacksPlayerBase::APILevel()
{
  return PlayerLIB::V2::CAddonCallbacksPlayer::APILevel();
}

int CAddonCallbacksPlayerBase::MinAPILevel()
{
  return PlayerLIB::V2::CAddonCallbacksPlayer::APILevel();
}

std::string CAddonCallbacksPlayerBase::Version()
{
  return PlayerLIB::V2::CAddonCallbacksPlayer::Version();
}

std::string CAddonCallbacksPlayerBase::MinVersion()
{
  return PlayerLIB::V2::CAddonCallbacksPlayer::Version();
}

void* CAddonCallbacksPlayerBase::CreateHelper(CAddonCallbacks* addon, int level)
{
  switch (level)
  {
  case 2:
    addon->m_helperPlayer = new PlayerLIB::V2::CAddonCallbacksPlayer(addon->m_addon);
    return static_cast<PlayerLIB::V2::CAddonCallbacksPlayer*>(addon->m_helperPlayer)->GetCallbacks();
  };
  return nullptr;
}

void CAddonCallbacksPlayerBase::DestroyHelper(CAddonCallbacks* addon)
{
  if (!addon->m_helperPlayer)
    return;

  switch (static_cast<IAddonCallback*>(addon->m_helperPlayer)->APILevel())
  {
  case 2:
    delete static_cast<PlayerLIB::V2::CAddonCallbacksPlayer*>(addon->m_helperPlayer);
    break;
  };
  addon->m_helperPlayer = nullptr;
}

}; /* namespace ADDON */
