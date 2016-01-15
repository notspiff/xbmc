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

#include "AddonCallbacksAudioEngineBase.h"

namespace ADDON
{

int CAddonCallbacksAudioEngineBase::APILevel()
{
  return AudioEngineLIB::V2::CAddonCallbacksAudioEngine::APILevel();
}

int CAddonCallbacksAudioEngineBase::MinAPILevel()
{
  return AudioEngineLIB::V1::CAddonCallbacksAudioEngine::APILevel();
}

std::string CAddonCallbacksAudioEngineBase::Version()
{
  return AudioEngineLIB::V2::CAddonCallbacksAudioEngine::Version();
}

std::string CAddonCallbacksAudioEngineBase::MinVersion()
{
  return AudioEngineLIB::V1::CAddonCallbacksAudioEngine::Version();
}

void* CAddonCallbacksAudioEngineBase::CreateHelper(CAddonCallbacks* addon, int level)
{
  switch (level)
  {
  case 1:
    addon->m_helperAudioEngine = new AudioEngineLIB::V1::CAddonCallbacksAudioEngine(addon->m_addon);
    return static_cast<AudioEngineLIB::V1::CAddonCallbacksAudioEngine*>(addon->m_helperAudioEngine)->GetCallbacks();
  case 2:
    addon->m_helperAudioEngine = new AudioEngineLIB::V2::CAddonCallbacksAudioEngine(addon->m_addon);
    return static_cast<AudioEngineLIB::V2::CAddonCallbacksAudioEngine*>(addon->m_helperAudioEngine)->GetCallbacks();
  };
  return nullptr;
}

void CAddonCallbacksAudioEngineBase::DestroyHelper(CAddonCallbacks* addon)
{
  if (!addon->m_helperAudioEngine)
    return;

  switch (static_cast<IAddonCallback*>(addon->m_helperAudioEngine)->APILevel())
  {
  case 1:
    delete static_cast<AudioEngineLIB::V1::CAddonCallbacksAudioEngine*>(addon->m_helperAudioEngine);
    break;
  case 2:
    delete static_cast<AudioEngineLIB::V2::CAddonCallbacksAudioEngine*>(addon->m_helperAudioEngine);
    break;
  };
  addon->m_helperAudioEngine = nullptr;
}

}; /* namespace ADDON */
