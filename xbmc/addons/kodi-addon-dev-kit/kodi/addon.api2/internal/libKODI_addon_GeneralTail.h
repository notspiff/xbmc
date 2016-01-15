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

namespace AddOnLIB
{
namespace V2
{

  inline void CAddonLib_General::Log(const addon_log loglevel, const char *format, ... )
  {
    va_list args;
    va_start(args, format);
    CAddonLib::g_libKODI_Internal->Log(loglevel, format, args);
  }

  inline bool CAddonLib_General::GetSettingString(
      const std::string& settingName,
      std::string&       settingValue,
      bool               global)
  {
    char * buffer = (char*) malloc(1024);
    buffer[0] = 0; /* Set the end of string */
    bool ret = CAddonLib::g_libKODI_Internal->GetSetting(settingName, buffer, global);
    if (ret)
      settingValue = buffer;
    free(buffer);
    return ret;
  }

  inline bool CAddonLib_General::GetSettingInt(
      const std::string& settingName,
      int&               settingValue,
      bool               global)
  {
    return CAddonLib::g_libKODI_Internal->GetSetting(settingName, &settingValue, global);
  }

  inline bool CAddonLib_General::GetSettingBoolean(
      const std::string& settingName,
      bool&              settingValue,
      bool               global)
  {
    return CAddonLib::g_libKODI_Internal->GetSetting(settingName, &settingValue, global);
  }

  inline bool CAddonLib_General::GetSettingFloat(
      const std::string& settingName,
      float&             settingValue,
      bool               global)
  {
    return CAddonLib::g_libKODI_Internal->GetSetting(settingName, &settingValue, global);
  }

  inline void CAddonLib_General::OpenSettings()
  {
    return CAddonLib::g_libKODI_Internal->OpenSettings();
  }

  inline void CAddonLib_General::QueueFormattedNotification(const queue_msg type, const char *format, ... )
  {
    va_list args;
    va_start(args, format);
    CAddonLib::g_libKODI_Internal->QueueFormattedNotification(type, format, args);
  }

  inline void CAddonLib_General::QueueNotification(
    const queue_msg  type,
    const std::string& aCaption,
    const std::string& aDescription,
    unsigned int       displayTime,
    bool               withSound,
    unsigned int       messageTime)
  {
    CAddonLib::g_libKODI_Internal->QueueNotification(
                          type, aCaption, aDescription,
                          displayTime, withSound, messageTime);
  }

  inline void CAddonLib_General::QueueNotification(
    const std::string& aCaption,
    const std::string& aDescription)
  {
    CAddonLib::g_libKODI_Internal->QueueNotification(aCaption, aDescription);
  }

  inline void CAddonLib_General::QueueNotification(
    const std::string& aImageFile,
    const std::string& aCaption,
    const std::string& aDescription,
    unsigned int       displayTime,
    bool               withSound,
    unsigned int       messageTime)
  {
    CAddonLib::g_libKODI_Internal->QueueNotification(
                          aImageFile, aCaption, aDescription,
                          displayTime, withSound, messageTime);
  }

  inline void CAddonLib_General::GetMD5(const std::string& text, std::string& md5)
  {
    CAddonLib::g_libKODI_Internal->GetMD5(text, md5);
  }

  inline bool CAddonLib_General::UnknownToUTF8(const std::string& stringSrc, std::string& utf8StringDst, bool failOnBadChar)
  {
    return CAddonLib::g_libKODI_Internal->UnknownToUTF8(stringSrc, utf8StringDst, failOnBadChar);
  }

  inline std::string CAddonLib_General::GetLocalizedString(uint32_t labelId, const std::string& strDefault)
  {
    return CAddonLib::g_libKODI_Internal->GetLocalizedString(labelId, strDefault);
  }

  inline std::string CAddonLib_General::GetLanguage(lang_formats format, bool region)
  {
    return CAddonLib::g_libKODI_Internal->GetLanguage(format, region);
  }

  inline std::string CAddonLib_General::GetDVDMenuLanguage()
  {
    return CAddonLib::g_libKODI_Internal->GetDVDMenuLanguage();
  }

  inline bool CAddonLib_General::StartServer(eservers typ, bool start, bool wait)
  {
    return CAddonLib::g_libKODI_Internal->StartServer(typ, start, wait);
  }

  inline void CAddonLib_General::AudioSuspend()
  {
    CAddonLib::g_libKODI_Internal->AudioSuspend();
  }

  inline void CAddonLib_General::AudioResume()
  {
    CAddonLib::g_libKODI_Internal->AudioResume();
  }

  inline float CAddonLib_General::GetVolume(bool percentage)
  {
    return CAddonLib::g_libKODI_Internal->GetVolume(percentage);
  }

  inline void CAddonLib_General::SetVolume(float value, bool isPercentage)
  {
    CAddonLib::g_libKODI_Internal->SetVolume(value, isPercentage);
  }

  inline bool CAddonLib_General::IsMuted()
  {
    return CAddonLib::g_libKODI_Internal->IsMuted();
  }

  inline void CAddonLib_General::ToggleMute(void)
  {
    CAddonLib::g_libKODI_Internal->ToggleMute();
  }

  inline void CAddonLib_General::SetMute(bool mute)
  {
    CAddonLib::g_libKODI_Internal->SetMute(mute);
  }

  inline dvd_state CAddonLib_General::GetOpticalDriveState()
  {
    return CAddonLib::g_libKODI_Internal->GetOpticalDriveState();
  }

  inline bool CAddonLib_General::EjectOpticalDrive()
  {
    return CAddonLib::g_libKODI_Internal->EjectOpticalDrive();
  }

  inline void CAddonLib_General::KodiVersion(kodi_version& version)
  {
    CAddonLib::g_libKODI_Internal->KodiVersion(version);
  }

  inline void CAddonLib_General::KodiQuit()
  {
    CAddonLib::g_libKODI_Internal->KodiQuit();
  }

  inline void CAddonLib_General::HTPCShutdown()
  {
    CAddonLib::g_libKODI_Internal->HTPCShutdown();
  }

  inline void CAddonLib_General::HTPCRestart()
  {
    CAddonLib::g_libKODI_Internal->HTPCRestart();
  }

  inline void CAddonLib_General::ExecuteScript(const std::string& script)
  {
    CAddonLib::g_libKODI_Internal->ExecuteScript(script);
  }

  inline void CAddonLib_General::ExecuteBuiltin(const std::string& function, bool wait)
  {
    CAddonLib::g_libKODI_Internal->ExecuteBuiltin(function, wait);
  }

  inline std::string CAddonLib_General::ExecuteJSONRPC(const std::string& jsonrpccommand)
  {
    return CAddonLib::g_libKODI_Internal->ExecuteJSONRPC(jsonrpccommand);
  }

  inline std::string CAddonLib_General::GetRegion(const std::string& id)
  {
    return CAddonLib::g_libKODI_Internal->GetRegion(id);
  }

  inline long CAddonLib_General::GetFreeMem()
  {
    return CAddonLib::g_libKODI_Internal->GetFreeMem();
  }

  inline int CAddonLib_General::GetGlobalIdleTime()
  {
    return CAddonLib::g_libKODI_Internal->GetGlobalIdleTime();
  }

  inline std::string CAddonLib_General::GetAddonInfo(std::string id)
  {
    return CAddonLib::g_libKODI_Internal->GetAddonInfo(id);
  }

  inline std::string CAddonLib_General::TranslatePath(const std::string& path)
  {
    return CAddonLib::g_libKODI_Internal->TranslatePath(path);
  }

  inline std::string CAddonLib_General::TranslateAddonStatus(ADDON_STATUS status)
  {
    return CAddonLib::g_libKODI_Internal->TranslateAddonStatus(status);
  }


}; /* namespace V2 */
}; /* namespace AddOnLIB */
