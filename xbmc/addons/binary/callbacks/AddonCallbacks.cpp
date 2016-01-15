/*
 *      Copyright (C) 2012-2013 Team XBMC
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

#include "AddonCallbacks.h"

#include "addons/Addon.h"
#include "addons/binary/ExceptionHandling.h"
#include "addons/binary/callbacks/Addon/AddonCallbacksAddonBase.h"
#include "addons/binary/callbacks/AudioDSP/AddonCallbacksAudioDSPBase.h"
#include "addons/binary/callbacks/AudioEngine/AddonCallbacksAudioEngineBase.h"
#include "addons/binary/callbacks/Codec/AddonCallbacksCodecBase.h"
#include "addons/binary/callbacks/GUI/AddonCallbacksGUIBase.h"
#include "addons/binary/callbacks/Player/AddonCallbacksPlayerBase.h"
#include "addons/binary/callbacks/PVR/AddonCallbacksPVRBase.h"
#include "filesystem/SpecialProtocol.h"
#include "utils/log.h"

namespace ADDON
{

CAddonCallbacks::CAddonCallbacks(CAddon* addon)
  : m_callbacks(new AddonCB),
    m_addon(addon),
    m_helperAddOn(nullptr),
    m_helperAudioEngine(nullptr),
    m_helperGUI(nullptr),
    m_helperPlayer(nullptr),
    m_helperPVR(nullptr),
    m_helperADSP(nullptr),
    m_helperCODEC(nullptr)
{
  m_callbacks->libBasePath                  = strdup(CSpecialProtocol::TranslatePath("special://xbmcbin/addons").c_str());
  m_callbacks->addonData                    = this;

  m_callbacks->AddOnLib_RegisterLevel       = CAddonCallbacks::AddOnLib_RegisterLevel;
  m_callbacks->AddOnLib_UnRegisterMe        = CAddonCallbacks::AddOnLib_UnRegisterMe;

  m_callbacks->AudioEngineLib_RegisterLevel = CAddonCallbacks::AudioEngineLib_RegisterLevel;
  m_callbacks->AudioEngineLib_UnRegisterMe  = CAddonCallbacks::AudioEngineLib_UnRegisterMe;

  m_callbacks->GUILib_RegisterLevel         = CAddonCallbacks::GUILib_RegisterLevel;
  m_callbacks->GUILib_UnRegisterMe          = CAddonCallbacks::GUILib_UnRegisterMe;

  m_callbacks->PlayerLib_RegisterLevel      = CAddonCallbacks::PlayerLib_RegisterLevel;
  m_callbacks->PlayerLib_UnRegisterMe       = CAddonCallbacks::PlayerLib_UnRegisterMe;

  m_callbacks->PVRLib_RegisterLevel         = CAddonCallbacks::PVRLib_RegisterLevel;
  m_callbacks->PVRLib_UnRegisterMe          = CAddonCallbacks::PVRLib_UnRegisterMe;

  /*!
   * Deprecated old libraries
   */
  m_callbacks->AddOnLib_RegisterMe          = CAddonCallbacks::AddOnLib_RegisterMe;
  m_callbacks->AudioEngineLib_RegisterMe    = CAddonCallbacks::AudioEngineLib_RegisterMe;
  m_callbacks->GUILib_RegisterMe            = CAddonCallbacks::GUILib_RegisterMe;
  m_callbacks->PVRLib_RegisterMe            = CAddonCallbacks::PVRLib_RegisterMe;
  m_callbacks->ADSPLib_RegisterMe           = CAddonCallbacks::ADSPLib_RegisterMe;
  m_callbacks->ADSPLib_UnRegisterMe         = CAddonCallbacks::ADSPLib_UnRegisterMe;
  m_callbacks->CodecLib_RegisterMe          = CAddonCallbacks::CodecLib_RegisterMe;
  m_callbacks->CodecLib_UnRegisterMe        = CAddonCallbacks::CodecLib_UnRegisterMe;
}

CAddonCallbacks::~CAddonCallbacks()
{
  CAddonCallbacksAddonBase::DestroyHelper(this);
  CAddonCallbacksAudioEngineBase::DestroyHelper(this);
  CAddonCallbacksGUIBase::DestroyHelper(this);
  CAddonCallbacksPlayerBase::DestroyHelper(this);
  CAddonCallbacksPVRBase::DestroyHelper(this);

  delete static_cast<ADSPLIB::V1::CAddonCallbacksADSP*>(m_helperADSP);
  delete static_cast<CodecLib::V1::CAddonCallbacksCodec*>(m_helperCODEC);

  free((char*)m_callbacks->libBasePath);
  delete m_callbacks;
}

/*\_____________________________________________________________________________
\*/

void* CAddonCallbacks::AddOnLib_RegisterMe(void *addonData)
{
  return AddOnLib_RegisterLevel(addonData, 1);
}

void* CAddonCallbacks::AddOnLib_RegisterLevel(void *addonData, int level)
{
  try
  {
    CAddonCallbacks* addon = static_cast<CAddonCallbacks *>(addonData);
    if (addon == nullptr)
    {
      CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
      return nullptr;
    }

    void* cb = CAddonCallbacksAddonBase::CreateHelper(addon, level);
    if (!cb)
      CLog::Log(LOGERROR, "%s: %s/%s - called with not supported API level '%i'",
                            __FUNCTION__,
                            TranslateType(addon->m_addon->Type()).c_str(),
                            addon->m_addon->Name().c_str(), level);
    return cb;
  }
  HANDLE_ADDON_EXCEPTION

  return nullptr;
}

void CAddonCallbacks::AddOnLib_UnRegisterMe(void *addonData, void *cbTable)
{
  try
  {
    CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(addonData);
    if (addon == nullptr)
    {
      CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
      return;
    }

    CAddonCallbacksAddonBase::DestroyHelper(addon);
  }
  HANDLE_ADDON_EXCEPTION
}

int CAddonCallbacks::AddOnLib_APILevel()
{
  return CAddonCallbacksAddonBase::APILevel();
}

int CAddonCallbacks::AddOnLib_MinAPILevel()
{
  return CAddonCallbacksAddonBase::MinAPILevel();
}

std::string CAddonCallbacks::AddOnLib_Version()
{
  return CAddonCallbacksAddonBase::Version();
}

std::string CAddonCallbacks::AddOnLib_MinVersion()
{
  return CAddonCallbacksAddonBase::MinVersion();
}

/*\_____________________________________________________________________________
\*/
void* CAddonCallbacks::AudioEngineLib_RegisterMe(void *addonData)
{
  return AudioEngineLib_RegisterLevel(addonData, 1);
}

void* CAddonCallbacks::AudioEngineLib_RegisterLevel(void *addonData, int level)
{
  try
  {
    CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(addonData);
    if (addon == nullptr)
    {
      CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
      return nullptr;
    }

    void* cb = CAddonCallbacksAudioEngineBase::CreateHelper(addon, level);
    if (!cb)
      CLog::Log(LOGERROR, "%s: %s/%s - called with not supported API level '%i'",
                            __FUNCTION__,
                            TranslateType(addon->m_addon->Type()).c_str(),
                            addon->m_addon->Name().c_str(), level);
    return cb;
  }
  HANDLE_ADDON_EXCEPTION

  return nullptr;
}

void CAddonCallbacks::AudioEngineLib_UnRegisterMe(void *addonData, void *cbTable)
{
  try
  {
    CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(addonData);
    if (addon == nullptr)
    {
      CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
      return;
    }

    CAddonCallbacksAudioEngineBase::DestroyHelper(addon);
  }
  HANDLE_ADDON_EXCEPTION
}

int CAddonCallbacks::AudioEngineLib_APILevel()
{
  return CAddonCallbacksAudioEngineBase::APILevel();
}

int CAddonCallbacks::AudioEngineLib_MinAPILevel()
{
  return CAddonCallbacksAudioEngineBase::MinAPILevel();
}

std::string CAddonCallbacks::AudioEngineLib_Version()
{
  return CAddonCallbacksAudioEngineBase::Version();
}

std::string CAddonCallbacks::AudioEngineLib_MinVersion()
{
  return CAddonCallbacksAudioEngineBase::MinVersion();
}
/*\_____________________________________________________________________________
\*/
void* CAddonCallbacks::GUILib_RegisterMe(void *addonData)
{
  return GUILib_RegisterLevel(addonData, 1);
}

void* CAddonCallbacks::GUILib_RegisterLevel(void *addonData, int level)
{
  try
  {
    CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(addonData);
    if (addon == nullptr)
    {
      CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
      return nullptr;
    }

    void* cb = CAddonCallbacksGUIBase::CreateHelper(addon, level);
    if (!cb)
      CLog::Log(LOGERROR, "%s: %s/%s - called with not supported API level '%i'",
                            __FUNCTION__,
                            TranslateType(addon->m_addon->Type()).c_str(),
                            addon->m_addon->Name().c_str(), level);
    return cb;
  }
  HANDLE_ADDON_EXCEPTION

  return nullptr;
}

void CAddonCallbacks::GUILib_UnRegisterMe(void *addonData, void *cbTable)
{
  try
  {
    CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(addonData);
    if (addon == nullptr)
    {
      CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
      return;
    }

    CAddonCallbacksGUIBase::DestroyHelper(addon);
  }
  HANDLE_ADDON_EXCEPTION
}

int CAddonCallbacks::GUILib_APILevel()
{
  return CAddonCallbacksGUIBase::APILevel();
}

int CAddonCallbacks::GUILib_MinAPILevel()
{
  return CAddonCallbacksGUIBase::MinAPILevel();
}

std::string CAddonCallbacks::GUILib_Version()
{
  return CAddonCallbacksGUIBase::Version();
}

std::string CAddonCallbacks::GUILib_MinVersion()
{
  return CAddonCallbacksGUIBase::MinVersion();
}
/*\_____________________________________________________________________________
\*/
void* CAddonCallbacks::PlayerLib_RegisterLevel(void *addonData, int level)
{
  try
  {
    CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(addonData);
    if (addon == nullptr)
    {
      CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
      return nullptr;
    }

    void* cb = CAddonCallbacksPlayerBase::CreateHelper(addon, level);
    if (!cb)
      CLog::Log(LOGERROR, "%s: %s/%s - called with not supported API level '%i'",
                            __FUNCTION__,
                            TranslateType(addon->m_addon->Type()).c_str(),
                            addon->m_addon->Name().c_str(), level);
    return cb;
  }
  HANDLE_ADDON_EXCEPTION

  return nullptr;
}

void CAddonCallbacks::PlayerLib_UnRegisterMe(void *addonData, void *cbTable)
{
  try
  {
    CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(addonData);
    if (addon == nullptr)
    {
      CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
      return;
    }

    CAddonCallbacksPlayerBase::DestroyHelper(addon);
  }
  HANDLE_ADDON_EXCEPTION
}

int CAddonCallbacks::PlayerLib_APILevel()
{
  return CAddonCallbacksPlayerBase::APILevel();
}

int CAddonCallbacks::PlayerLib_MinAPILevel()
{
  return CAddonCallbacksPlayerBase::MinAPILevel();
}

std::string CAddonCallbacks::PlayerLib_Version()
{
  return CAddonCallbacksPlayerBase::Version();
}

std::string CAddonCallbacks::PlayerLib_MinVersion()
{
  return CAddonCallbacksPlayerBase::MinVersion();
}
/*\_____________________________________________________________________________
\*/
void* CAddonCallbacks::PVRLib_RegisterMe(void *addonData)
{
  return PVRLib_RegisterLevel(addonData, 1);
}

void* CAddonCallbacks::PVRLib_RegisterLevel(void *addonData, int level)
{
  try
  {
    CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(addonData);
    if (addon == nullptr)
    {
      CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
      return nullptr;
    }

    void* cb = CAddonCallbacksPVRBase::CreateHelper(addon, level);
    if (!cb)
      CLog::Log(LOGERROR, "%s: %s/%s - called with not supported API level '%i'",
                            __FUNCTION__,
                            TranslateType(addon->m_addon->Type()).c_str(),
                            addon->m_addon->Name().c_str(), level);
    return cb;
  }
  HANDLE_ADDON_EXCEPTION

  return nullptr;
}

void CAddonCallbacks::PVRLib_UnRegisterMe(void *addonData, void *cbTable)
{
  try
  {
    CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(addonData);
    if (addon == nullptr)
    {
      CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
      return;
    }

    CAddonCallbacksPVRBase::DestroyHelper(addon);
  }
  HANDLE_ADDON_EXCEPTION
}

int CAddonCallbacks::PVRLib_APILevel()
{
  return CAddonCallbacksPVRBase::APILevel();
}

int CAddonCallbacks::PVRLib_MinAPILevel()
{
  return CAddonCallbacksPVRBase::MinAPILevel();
}

std::string CAddonCallbacks::PVRLib_Version()
{
  return CAddonCallbacksPVRBase::Version();
}

std::string CAddonCallbacks::PVRLib_MinVersion()
{
  return CAddonCallbacksPVRBase::MinVersion();
}
/*\_____________________________________________________________________________
\*/
void* CAddonCallbacks::ADSPLib_RegisterMe(void *addonData)
{
  try
  {
    CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(addonData);
    if (addon == nullptr)
    {
      CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
      return nullptr;
    }

    addon->m_helperCODEC = new ADSPLIB::V1::CAddonCallbacksADSP(addon->m_addon);
    return static_cast<ADSPLIB::V1::CAddonCallbacksADSP*>(addon->m_helperADSP)->GetCallbacks();
  }
  HANDLE_ADDON_EXCEPTION

  return nullptr;
}

void CAddonCallbacks::ADSPLib_UnRegisterMe(void *addonData, void *cbTable)
{
  try
  {
    CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(addonData);
    if (addon == nullptr)
    {
      CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
      return;
    }

    delete static_cast<ADSPLIB::V1::CAddonCallbacksADSP*>(addon->m_helperADSP);
    addon->m_helperADSP = nullptr;
  }
  HANDLE_ADDON_EXCEPTION
}
/*\_____________________________________________________________________________
\*/
void* CAddonCallbacks::CodecLib_RegisterMe(void *addonData)
{
  try
  {
    CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(addonData);
    if (addon == nullptr)
    {
      CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
      return NULL;
    }

    addon->m_helperCODEC = new CodecLib::V1::CAddonCallbacksCodec(addon->m_addon);
    return static_cast<CodecLib::V1::CAddonCallbacksCodec*>(addon->m_helperCODEC)->GetCallbacks();
  }
  HANDLE_ADDON_EXCEPTION

  return nullptr;
}

void CAddonCallbacks::CodecLib_UnRegisterMe(void *addonData, void *cbTable)
{
  try
  {
    CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(addonData);
    if (addon == nullptr)
    {
      CLog::Log(LOGERROR, "CAddonCallbacks - %s - called with a null pointer", __FUNCTION__);
      return;
    }

    delete static_cast<CodecLib::V1::CAddonCallbacksCodec*>(addon->m_helperCODEC);
    addon->m_helperCODEC = nullptr;
  }
  HANDLE_ADDON_EXCEPTION
}

}; /* namespace ADDON */
