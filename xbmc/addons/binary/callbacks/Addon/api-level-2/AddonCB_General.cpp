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

#include "AddonCB_General.h"
#include "AddonCallbacksAddon.h"

#include "Application.h"
#include "CompileInfo.h"
#include "LangInfo.h"
#include "addons/Addon.h"
#include "addons/GUIDialogAddonSettings.h"
#include "addons/binary/ExceptionHandling.h"
#include "cores/AudioEngine/AEFactory.h"
#include "dialogs/GUIDialogKaiToast.h"
#include "filesystem/SpecialProtocol.h"
#include "guilib/GUIAudioManager.h"
#include "interfaces/builtins/Builtins.h"
#include "interfaces/legacy/aojsonrpc.h" //<! @todo: On next cleanup to ./addons
#include "messaging/ApplicationMessenger.h"
#include "settings/Settings.h"
#include "settings/lib/Setting.h"
#include "storage/MediaManager.h"
#include "utils/CharsetConverter.h"
#include "utils/LangCodeExpander.h"
#include "utils/log.h"
#include "utils/md5.h"
#include "utils/StringUtils.h"
#include "utils/XMLUtils.h"

using namespace ADDON;
using namespace KODI::MESSAGING;

namespace AddOnLIB
{
namespace V2
{
extern "C"
{

CAddonCB_General::CAddonCB_General()
{
}

void CAddonCB_General::Init(CB_AddOnLib *callbacks)
{
  callbacks->General.get_addon_info                 = CAddonCB_General::get_addon_info;
  callbacks->General.get_setting                    = CAddonCB_General::get_setting;
  callbacks->General.open_settings_dialog           = CAddonCB_General::open_settings_dialog;
  callbacks->General.addon_log_msg                  = CAddonCB_General::addon_log_msg;
  callbacks->General.queue_notification             = CAddonCB_General::queue_notification;
  callbacks->General.queue_notification_from_type   = CAddonCB_General::queue_notification_from_type;
  callbacks->General.queue_notification_with_image  = CAddonCB_General::queue_notification_with_image;
  callbacks->General.get_md5                        = CAddonCB_General::get_md5;
  callbacks->General.unknown_to_utf8                = CAddonCB_General::unknown_to_utf8;
  callbacks->General.get_localized_string           = CAddonCB_General::get_localized_string;
  callbacks->General.get_language                   = CAddonCB_General::get_language;
  callbacks->General.get_dvd_menu_language          = CAddonCB_General::get_dvd_menu_language;
  callbacks->General.free_string                    = CAddonCB_General::free_string;
  callbacks->General.start_server                   = CAddonCB_General::start_server;
  callbacks->General.audio_suspend                  = CAddonCB_General::audio_suspend;
  callbacks->General.audio_resume                   = CAddonCB_General::audio_resume;
  callbacks->General.get_volume                     = CAddonCB_General::get_volume;
  callbacks->General.set_volume                     = CAddonCB_General::set_volume;
  callbacks->General.is_muted                       = CAddonCB_General::is_muted;
  callbacks->General.toggle_mute                    = CAddonCB_General::toggle_mute;
  callbacks->General.get_optical_state              = CAddonCB_General::get_optical_state;
  callbacks->General.eject_optical_drive            = CAddonCB_General::eject_optical_drive;
  callbacks->General.kodi_version                   = CAddonCB_General::kodi_version;
  callbacks->General.kodi_quit                      = CAddonCB_General::kodi_quit;
  callbacks->General.htpc_shutdown                  = CAddonCB_General::htpc_shutdown;
  callbacks->General.htpc_restart                   = CAddonCB_General::htpc_restart;
  callbacks->General.execute_script                 = CAddonCB_General::execute_script;
  callbacks->General.execute_builtin                = CAddonCB_General::execute_builtin;
  callbacks->General.execute_jsonrpc                = CAddonCB_General::execute_jsonrpc;
  callbacks->General.get_region                     = CAddonCB_General::get_region;
  callbacks->General.get_free_mem                   = CAddonCB_General::get_free_mem;
  callbacks->General.get_global_idle_time           = CAddonCB_General::get_global_idle_time;
  callbacks->General.translate_path                 = CAddonCB_General::translate_path;
}

bool CAddonCB_General::get_setting(
        void*                     hdl,
        const char*               strSettingName,
        void*                     settingValue,
        bool                      global)
{
  try
  {
    CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(static_cast<AddonCB*>(hdl)->addonData);
    if (addon == nullptr || strSettingName == nullptr || settingValue == nullptr)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (addon='%p', strSettingName='%p', settingValue='%p')",
                                        __FUNCTION__, addon, strSettingName, settingValue);

    CAddonCallbacksAddon* addonHelper = static_cast<CAddonCallbacksAddon*>(addon->AddOnLib_GetHelper());
    if (addonHelper == nullptr)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (addonHelper='%p')",
                                        __FUNCTION__, addonHelper);

    CLog::Log(LOGDEBUG, "CAddonCB_General - %s - add-on '%s' requests setting '%s' from '%s'",
                          __FUNCTION__, addonHelper->GetAddon()->Name().c_str(), strSettingName, global ? "global" : "add-on");

    if (global)
    {
      std::string settingName = strSettingName;
      if (StringUtils::EqualsNoCase(settingName, CSettings::SETTING_PVRPARENTAL_PIN) ||
          StringUtils::EqualsNoCase(settingName, CSettings::SETTING_MASTERLOCK_LOCKCODE) ||
          StringUtils::EqualsNoCase(settingName, CSettings::SETTING_SYSTEM_PLAYLISTSPATH) ||
          StringUtils::StartsWithNoCase(settingName, "services.") || // CSettings::SETTING_SERVICES_...)
          StringUtils::StartsWithNoCase(settingName, "smb.")      || // CSettings::SETTING_SMB_...)
          StringUtils::StartsWithNoCase(settingName, "network.")  || // CSettings::SETTING_NETWORK_...)
          StringUtils::StartsWithNoCase(settingName, "cache"))       // CSettings::SETTING_CACHE...)
      {
        CLog::Log(LOGERROR, "CAddonCB_General - %s - add-on '%s' requests not allowed global setting '%s'!",
                              __FUNCTION__, addonHelper->GetAddon()->Name().c_str(), settingName.c_str());
        return false;
      }


      const CSetting* setting = CSettings::GetInstance().GetSetting(settingName);
      if (setting == nullptr)
      {
        CLog::Log(LOGERROR, "CAddonCB_General - %s - can't find global setting '%s'", __FUNCTION__, settingName.c_str());
        return false;
      }

      switch (setting->GetType())
      {
      case SettingTypeBool:
        *(bool*) settingValue = dynamic_cast<const CSettingBool*>(setting)->GetValue();
      break;
      case SettingTypeInteger:
        *(int*) settingValue = dynamic_cast<const CSettingInt*>(setting)->GetValue();
      break;
      case SettingTypeNumber:
        *(float*) settingValue = dynamic_cast<const CSettingNumber*>(setting)->GetValue();
      break;
      case SettingTypeString:
        strcpy((char*) settingValue, dynamic_cast<const CSettingString*>(setting)->GetValue().c_str());
      break;
      default:
        CLog::Log(LOGERROR, "CAddonCB_General - %s - not supported type for global setting '%s'", __FUNCTION__, settingName.c_str());
        return false;
      }
      return true;
    }

    if (strcasecmp(strSettingName, "__addonpath__") == 0)
    {
      strcpy((char*) settingValue, addonHelper->GetAddon()->Path().c_str());
      return true;
    }

    if (!addonHelper->GetAddon()->ReloadSettings())
    {
      CLog::Log(LOGERROR, "CAddonCB_General - %s - could't get settings for add-on '%s'", __FUNCTION__, addonHelper->GetAddon()->Name().c_str());
      return false;
    }

    const TiXmlElement *category = addonHelper->GetAddon()->GetSettingsXML()->FirstChildElement("category");
    if (!category) // add a default one...
      category = addonHelper->GetAddon()->GetSettingsXML();

    while (category)
    {
      const TiXmlElement *setting = category->FirstChildElement("setting");
      while (setting)
      {
        const std::string   id = XMLUtils::GetAttribute(setting, "id");
        const std::string type = XMLUtils::GetAttribute(setting, "type");

        if (id == strSettingName && !type.empty())
        {
          if (type == "text"     || type == "ipaddress" ||
              type == "folder"   || type == "action"    ||
              type == "music"    || type == "pictures"  ||
              type == "programs" || type == "fileenum"  ||
              type == "file"     || type == "labelenum")
          {
            strcpy((char*) settingValue, addonHelper->GetAddon()->GetSetting(id).c_str());
            return true;
          }
          else if (type == "number" || type == "enum")
          {
            *(int*) settingValue = (int) atoi(addonHelper->GetAddon()->GetSetting(id).c_str());
            return true;
          }
          else if (type == "bool")
          {
            *(bool*) settingValue = (bool) (addonHelper->GetAddon()->GetSetting(id) == "true" ? true : false);
            return true;
          }
          else if (type == "slider")
          {
            const char *option = setting->Attribute("option");
            if (option && strcmpi(option, "int") == 0)
            {
              *(int*) settingValue = (int) atoi(addonHelper->GetAddon()->GetSetting(id).c_str());
              return true;
            }
            else
            {
              *(float*) settingValue = (float) atof(addonHelper->GetAddon()->GetSetting(id).c_str());
              return true;
            }
          }
        }
        setting = setting->NextSiblingElement("setting");
      }
      category = category->NextSiblingElement("category");
    }
    CLog::Log(LOGERROR, "CAddonCB_General - %s - can't find setting '%s' in '%s'", __FUNCTION__, strSettingName, addonHelper->GetAddon()->Name().c_str());
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

void CAddonCB_General::open_settings_dialog(
        void*                     hdl)
{
  try
  {
    if (hdl == nullptr)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p')",
                                        __FUNCTION__, hdl);

    CAddonCallbacks* addonCB = static_cast<CAddonCallbacks*>(static_cast<AddonCB*>(hdl)->addonData);
    if (addonCB == nullptr)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (addon='%p')",
                                        __FUNCTION__, addonCB);

    // show settings dialog
    ADDON::AddonPtr addon(addonCB->GetAddon());
    CGUIDialogAddonSettings::ShowAndGetInput(addon);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonCB_General::addon_log_msg(
        void*                     hdl,
        const addon_log           addonLogLevel,
        const char*               strMessage)
{
  try
  {
    CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(static_cast<AddonCB*>(hdl)->addonData);
    if (addon == nullptr || strMessage == nullptr)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (addon='%p', strMessage='%p')",
                                        __FUNCTION__, addon, strMessage);

    CAddonCallbacksAddon* addonHelper = static_cast<CAddonCallbacksAddon*>(addon->AddOnLib_GetHelper());
    if (addonHelper == nullptr)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (addonHelper='%p')",
                                        __FUNCTION__, addonHelper);

    int logLevel = LOGNONE;
    switch (addonLogLevel)
    {
      case LOG_FATAL:
        logLevel = LOGFATAL;
        break;
      case LOG_SEVERE:
        logLevel = LOGSEVERE;
        break;
      case LOG_ERROR:
        logLevel = LOGERROR;
        break;
      case LOG_WARNING:
        logLevel = LOGWARNING;
        break;
      case LOG_NOTICE:
        logLevel = LOGNOTICE;
        break;
      case LOG_INFO:
        logLevel = LOGINFO;
        break;
      case LOG_DEBUG:
        logLevel = LOGDEBUG;
        break;
      default:
        break;
    }

    CLog::Log(logLevel, "AddOnLog: %s: %s", addonHelper->GetAddon()->Name().c_str(), strMessage);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonCB_General::queue_notification(
        void*                     hdl,
        const queue_msg         type,
        const char*               strMessage)
{
  try
  {
    CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(static_cast<AddonCB*>(hdl)->addonData);
    if (addon == nullptr || strMessage == nullptr)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (addon='%p', strMessage='%p')",
                                        __FUNCTION__, addon, strMessage);

    CAddonCallbacksAddon* addonHelper = static_cast<CAddonCallbacksAddon*>(addon->AddOnLib_GetHelper());
    if (addonHelper == nullptr)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (addonHelper='%p')",
                                        __FUNCTION__, addonHelper);

    switch (type)
    {
      case QUEUE_WARNING:
        CGUIDialogKaiToast::QueueNotification(CGUIDialogKaiToast::Warning, addonHelper->GetAddon()->Name(), strMessage, 3000, true);
        CLog::Log(LOGDEBUG, "CAddonCB_General - %s - %s - Warning Message: '%s'", __FUNCTION__, addonHelper->GetAddon()->Name().c_str(), strMessage);
        break;

      case QUEUE_ERROR:
        CGUIDialogKaiToast::QueueNotification(CGUIDialogKaiToast::Error, addonHelper->GetAddon()->Name(), strMessage, 3000, true);
        CLog::Log(LOGDEBUG, "CAddonCB_General - %s - %s - Error Message : '%s'", __FUNCTION__, addonHelper->GetAddon()->Name().c_str(), strMessage);
        break;

      case QUEUE_INFO:
      default:
        CGUIDialogKaiToast::QueueNotification(CGUIDialogKaiToast::Info, addonHelper->GetAddon()->Name(), strMessage, 3000, false);
        CLog::Log(LOGDEBUG, "CAddonCB_General - %s - %s - Info Message : '%s'", __FUNCTION__, addonHelper->GetAddon()->Name().c_str(), strMessage);
        break;
    }
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonCB_General::queue_notification_from_type(
        void*                     hdl,
        const queue_msg           type,
        const char*               aCaption,
        const char*               aDescription,
        unsigned int              displayTime,
        bool                      withSound,
        unsigned int              messageTime)
{
  try
  {
    CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(static_cast<AddonCB*>(hdl)->addonData);
    if (addon == nullptr || aCaption == nullptr || aDescription == nullptr)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (addon='%p', aImageFile='%p', aDescription='%p')",
                                        __FUNCTION__, addon, aCaption, aDescription);

    CGUIDialogKaiToast::eMessageType usedType;
    switch (type)
    {
    case QUEUE_WARNING:
      usedType = CGUIDialogKaiToast::Warning;
      break;
    case QUEUE_ERROR:
      usedType = CGUIDialogKaiToast::Error;
      break;
    case QUEUE_INFO:
    default:
      usedType = CGUIDialogKaiToast::Info;
      break;
    }
    CGUIDialogKaiToast::QueueNotification(usedType, aCaption, aDescription, displayTime, withSound, messageTime);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonCB_General::queue_notification_with_image(
        void*                     hdl,
        const char*               aImageFile,
        const char*               aCaption,
        const char*               aDescription,
        unsigned int              displayTime,
        bool                      withSound,
        unsigned int              messageTime)
{
  try
  {
    CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(static_cast<AddonCB*>(hdl)->addonData);
    if (addon == nullptr || aImageFile == nullptr || aCaption == nullptr  || aDescription == nullptr)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (addon='%p', aImageFile='%p', aCaption='%p', aDescription='%p')",
                                        __FUNCTION__, addon, aImageFile, aCaption, aDescription);

    CGUIDialogKaiToast::QueueNotification(aImageFile, aCaption, aDescription, displayTime, withSound, messageTime);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonCB_General::get_md5(const char* text, char& md5)
{
  try
  {
    if (!text)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (text='%p')", __FUNCTION__, text);

    std::string md5Int = XBMC::XBMC_MD5::GetMD5(std::string(text));
    strncpy(&md5, md5Int.c_str(), 40);
  }
  HANDLE_ADDON_EXCEPTION
}

char* CAddonCB_General::unknown_to_utf8(
        void*                     hdl,
        const char*               strSource,
        bool&                     ret,
        bool                      failOnBadChar)
{
  try
  {
    if (!hdl || !strSource)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p', strSource='%p')", __FUNCTION__, hdl, strSource);

    std::string string;
    ret = g_charsetConverter.unknownToUTF8(strSource, string, failOnBadChar);
    char* buffer = strdup(string.c_str());
    return buffer;
  }
  HANDLE_ADDON_EXCEPTION

  return nullptr;
}

char* CAddonCB_General::get_localized_string(
        void*                     hdl,
        uint32_t                  labelId)
{
  try
  {
    CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(static_cast<AddonCB*>(hdl)->addonData);
    if (addon == nullptr)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p')", __FUNCTION__, hdl);
    else if (g_application.m_bStop)
      return nullptr;

    CAddonCallbacksAddon* addonHelper = static_cast<CAddonCallbacksAddon*>(static_cast<CAddonCallbacks*>(addon)->AddOnLib_GetHelper());

    std::string string;
    if (labelId >= 30000 && labelId <= 30999)
      string = addonHelper->GetAddon()->GetString(labelId).c_str();
    else if (labelId >= 32000 && labelId <= 32999)
      string = addonHelper->GetAddon()->GetString(labelId).c_str();
    else
      string = g_localizeStrings.Get(labelId).c_str();

    char* buffer = strdup(string.c_str());
    return buffer;
  }
  HANDLE_ADDON_EXCEPTION

  return nullptr;
}

void CAddonCB_General::get_language(void* hdl, char& language, unsigned int& iMaxStringSize, int format, bool region)
{
  try
  {
    if (!hdl)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p')", __FUNCTION__, hdl);

    std::string str = g_langInfo.GetEnglishLanguageName();
    switch (format)
    {
      case LANG_FMT_ISO_639_1:
      {
        std::string langCode;
        g_LangCodeExpander.ConvertToISO6391(str, langCode);
        str = langCode;
        if (region)
        {
          std::string region2Code;
          g_LangCodeExpander.ConvertToISO6391(g_langInfo.GetRegionLocale(), region2Code);
          if (!region2Code.empty())
            str += "-" + region2Code;
        }
        break;
      }
      case LANG_FMT_ISO_639_2:
      {
        std::string langCode;
        g_LangCodeExpander.ConvertToISO6392T(str, langCode);
        str = langCode;
        if (region)
        {
          std::string region3Code;
          g_LangCodeExpander.ConvertToISO6392T(g_langInfo.GetRegionLocale(), region3Code);
          if (!region3Code.empty())
            str += "-" + region3Code;
        }
        break;
      }
      case LANG_FMT_ENGLISH_NAME:
      default:
      {
        if (region)
          str += "-" + g_langInfo.GetCurrentRegion();
        break;
      }
    }

    strncpy(&language, str.c_str(), iMaxStringSize);
    iMaxStringSize = str.length();
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonCB_General::get_dvd_menu_language(void* hdl, char& language, unsigned int& iMaxStringSize)
{
  try
  {
    if (!hdl)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p')", __FUNCTION__, hdl);

    std::string str = g_langInfo.GetDVDMenuLanguage();
    strncpy(&language, str.c_str(), iMaxStringSize);
    iMaxStringSize = str.length();
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonCB_General::free_string(void* hdl, char* str)
{
  try
  {
    if (!hdl || !str)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p', str='%p')", __FUNCTION__, hdl, str);

    free(str);
  }
  HANDLE_ADDON_EXCEPTION
}

bool CAddonCB_General::start_server(void* hdl, int typ, bool bStart, bool bWait)
{
  try
  {
    if (!hdl)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p')",
                                        __FUNCTION__, hdl);

    CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(static_cast<AddonCB*>(hdl)->addonData);
    if (addon == nullptr)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (addon='%p')",
                                        __FUNCTION__, addon);

    CApplication::ESERVERS iTyp;
    switch (typ)
    {
    case ADDON_ES_WEBSERVER:     iTyp = CApplication::ES_WEBSERVER;     break;
    case ADDON_ES_AIRPLAYSERVER: iTyp = CApplication::ES_AIRPLAYSERVER; break;
    case ADDON_ES_JSONRPCSERVER: iTyp = CApplication::ES_JSONRPCSERVER; break;
    case ADDON_ES_UPNPRENDERER:  iTyp = CApplication::ES_UPNPRENDERER;  break;
    case ADDON_ES_UPNPSERVER:    iTyp = CApplication::ES_UPNPSERVER;    break;
    case ADDON_ES_EVENTSERVER:   iTyp = CApplication::ES_EVENTSERVER;   break;
    case ADDON_ES_ZEROCONF:      iTyp = CApplication::ES_ZEROCONF;      break;
    default:
      CLog::Log(LOGERROR, "CAddonCB_General - %s - %s - Error Message : Not supported server type '%i'",
                            __FUNCTION__, addon->GetAddon()->Name().c_str(), typ);
      return false;
    }
    return g_application.StartServer(iTyp, bStart, bWait);
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

void CAddonCB_General::audio_suspend(void* hdl)
{
  try
  {
    if (!hdl)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p')", __FUNCTION__, hdl);

    CAEFactory::Suspend();
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonCB_General::audio_resume(void* hdl)
{
  try
  {
    if (!hdl)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p')", __FUNCTION__, hdl);

    CAEFactory::Resume();
  }
  HANDLE_ADDON_EXCEPTION
}

float CAddonCB_General::get_volume(void* hdl, bool percentage)
{
  try
  {
    if (!hdl)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p')", __FUNCTION__, hdl);

    return g_application.GetVolume(percentage);
  }
  HANDLE_ADDON_EXCEPTION

  return 0.0f;
}

void CAddonCB_General::set_volume(
        void*                     hdl,
        float                     value,
        bool                      isPercentage)
{
  try
  {
    if (!hdl)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p')", __FUNCTION__, hdl);

    g_application.SetVolume(value, isPercentage);
  }
  HANDLE_ADDON_EXCEPTION
}

bool CAddonCB_General::is_muted(void* hdl)
{
  try
  {
    if (!hdl)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p')", __FUNCTION__, hdl);

    return g_application.IsMutedInternal();
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

void CAddonCB_General::toggle_mute(void* hdl)
{
  try
  {
    if (!hdl)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p')", __FUNCTION__, hdl);

    g_application.ToggleMute();
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonCB_General::enable_nav_sounds(void* hdl, bool yesNo)
{
  try
  {
    if (!hdl)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p')",
                                        __FUNCTION__, hdl);

    g_audioManager.Enable(yesNo);
  }
  HANDLE_ADDON_EXCEPTION
}

long CAddonCB_General::get_optical_state(void* hdl)
{
  try
  {
    if (!hdl)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p')", __FUNCTION__, hdl);

    return g_mediaManager.GetDriveStatus();
  }
  HANDLE_ADDON_EXCEPTION

  return 0;
}

bool CAddonCB_General::eject_optical_drive(void* hdl)
{
  try
  {
    if (!hdl)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p')", __FUNCTION__, hdl);

    return CBuiltins::GetInstance().Execute("EjectTray") == 0 ? true : false;
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

void CAddonCB_General::kodi_version(
      void*                     hdl,
      char*&                    compile_name,
      int&                      major,
      int&                      minor,
      char*&                    revision,
      char*&                    tag,
      char*&                    tagversion)
{
  try
  {
    if (!hdl)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p')", __FUNCTION__, hdl);

    compile_name = strdup(CCompileInfo::GetAppName());
    major        = CCompileInfo::GetMajor();
    minor        = CCompileInfo::GetMinor();
    revision     = strdup(CCompileInfo::GetSCMID());
    std::string tagStr = CCompileInfo::GetSuffix();
    if (StringUtils::StartsWithNoCase(tagStr, "alpha"))
    {
      tag = strdup("alpha");
      tagversion = strdup(StringUtils::Mid(tagStr, 5).c_str());
    }
    else if (StringUtils::StartsWithNoCase(tagStr, "beta"))
    {
      tag = strdup("beta");
      tagversion = strdup(StringUtils::Mid(tagStr, 4).c_str());
    }
    else if (StringUtils::StartsWithNoCase(tagStr, "rc"))
    {
      tag = strdup("releasecandidate");
      tagversion = strdup(StringUtils::Mid(tagStr, 2).c_str());
    }
    else if (tagStr.empty())
      tag = strdup("stable");
    else
      tag = strdup("prealpha");
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonCB_General::kodi_quit(void* hdl)
{
  try
  {
    if (!hdl)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p')", __FUNCTION__, hdl);

    CApplicationMessenger::GetInstance().PostMsg(TMSG_QUIT);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonCB_General::htpc_shutdown(void* hdl)
{
  try
  {
    if (!hdl)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p')", __FUNCTION__, hdl);

    CApplicationMessenger::GetInstance().PostMsg(TMSG_SHUTDOWN);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonCB_General::htpc_restart(void* hdl)
{
  try
  {
    if (!hdl)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p')", __FUNCTION__, hdl);

    CApplicationMessenger::GetInstance().PostMsg(TMSG_RESTART);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonCB_General::execute_script(void* hdl, const char* script)
{
  try
  {
    if (!hdl || !script)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p', script='%p')",
                                        __FUNCTION__, hdl, script);

    CApplicationMessenger::GetInstance().PostMsg(TMSG_EXECUTE_SCRIPT, -1, -1, nullptr, script);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonCB_General::execute_builtin(void* hdl, const char* function, bool wait)
{
  try
  {
    if (!hdl || !function)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p', function='%p')",
                                        __FUNCTION__, hdl, function);

    if (wait)
      CApplicationMessenger::GetInstance().SendMsg(TMSG_EXECUTE_BUILT_IN, -1, -1, nullptr, function);
    else
      CApplicationMessenger::GetInstance().PostMsg(TMSG_EXECUTE_BUILT_IN, -1, -1, nullptr, function);
  }
  HANDLE_ADDON_EXCEPTION
}

char* CAddonCB_General::execute_jsonrpc(void* hdl, const char* jsonrpccommand)
{
  try
  {
    if (!hdl || !jsonrpccommand)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p', jsonrpccommand='%p')",
                                        __FUNCTION__, hdl, jsonrpccommand);
#ifdef HAS_JSONRPC
    CAddOnTransport transport;
    CAddOnTransport::CAddOnClient client;
    std::string string = JSONRPC::CJSONRPC::MethodCall(/*method*/ jsonrpccommand, &transport, &client);
    char* buffer = strdup(string.c_str());
    return buffer;
#else
    THROW_UNIMP("execute_jsonrpc");
#endif
  }
  HANDLE_ADDON_EXCEPTION

  return nullptr;
}

char* CAddonCB_General::get_region(void* hdl, const char* id)
{
  try
  {
    CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(static_cast<AddonCB*>(hdl)->addonData);
    if (addon == nullptr || id == nullptr)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (addon='%p', id='%p')",
                                        __FUNCTION__, addon, id);
    std::string result;
    if (strcmpi(id, "datelong") == 0)
    {
      result = g_langInfo.GetDateFormat(true);
      StringUtils::Replace(result, "DDDD", "%A");
      StringUtils::Replace(result, "MMMM", "%B");
      StringUtils::Replace(result, "D", "%d");
      StringUtils::Replace(result, "YYYY", "%Y");
    }
    else if (strcmpi(id, "dateshort") == 0)
    {
      result = g_langInfo.GetDateFormat(false);
      StringUtils::Replace(result, "MM", "%m");
      StringUtils::Replace(result, "DD", "%d");
#ifdef TARGET_WINDOWS
      StringUtils::Replace(result, "M", "%#m");
      StringUtils::Replace(result, "D", "%#d");
#else
      StringUtils::Replace(result, "M", "%-m");
      StringUtils::Replace(result, "D", "%-d");
#endif
      StringUtils::Replace(result, "YYYY", "%Y");
    }
    else if (strcmpi(id, "tempunit") == 0)
      result = g_langInfo.GetTemperatureUnitString();
    else if (strcmpi(id, "speedunit") == 0)
      result = g_langInfo.GetSpeedUnitString();
    else if (strcmpi(id, "time") == 0)
    {
      result = g_langInfo.GetTimeFormat();
      StringUtils::Replace(result, "H", "%H");
      StringUtils::Replace(result, "h", "%I");
      StringUtils::Replace(result, "mm", "%M");
      StringUtils::Replace(result, "ss", "%S");
      StringUtils::Replace(result, "xx", "%p");
    }
    else if (strcmpi(id, "meridiem") == 0)
      result = StringUtils::Format("%s/%s",
                                   g_langInfo.GetMeridiemSymbol(MeridiemSymbolAM).c_str(),
                                   g_langInfo.GetMeridiemSymbol(MeridiemSymbolPM).c_str());
    else
      throw ADDON::WrongValueException("CAddonCB_General - %s - add-on '%s' requests invalid id '%s'",
                            __FUNCTION__, addon->GetAddon()->Name().c_str(), id);

    char* buffer = strdup(result.c_str());
    return buffer;
  }
  HANDLE_ADDON_EXCEPTION

  return nullptr;
}

long CAddonCB_General::get_free_mem(void* hdl)
{
  try
  {
    if (!hdl)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p')",
                                        __FUNCTION__, hdl);

    MEMORYSTATUSEX stat;
    stat.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&stat);
    return (long)(stat.ullAvailPhys  / ( 1024 * 1024 ));
  }
  HANDLE_ADDON_EXCEPTION

  return -1;
}

int CAddonCB_General::get_global_idle_time(void* hdl)
{
  try
  {
    if (!hdl)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p')",
                                        __FUNCTION__, hdl);

    return g_application.GlobalIdleTime();
  }
  HANDLE_ADDON_EXCEPTION

  return -1;
}

char* CAddonCB_General::get_addon_info(void* hdl, const char* id)
{
  try
  {
    CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(static_cast<AddonCB*>(hdl)->addonData);
    if (addon == nullptr || id == nullptr)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (addon='%p', id='%p')",
                                        __FUNCTION__, addon, id);

    ADDON::CAddon* pAddon = addon->GetAddon();
    std::string str;
    if (strcmpi(id, "author") == 0)
      str = pAddon->Author();
    else if (strcmpi(id, "changelog") == 0)
      str = pAddon->ChangeLog();
    else if (strcmpi(id, "description") == 0)
      str = pAddon->Description();
    else if (strcmpi(id, "disclaimer") == 0)
      str = pAddon->Disclaimer();
    else if (strcmpi(id, "fanart") == 0)
      str = pAddon->FanArt();
    else if (strcmpi(id, "icon") == 0)
      str = pAddon->Icon();
    else if (strcmpi(id, "id") == 0)
      str = pAddon->ID();
    else if (strcmpi(id, "name") == 0)
      str = pAddon->Name();
    else if (strcmpi(id, "path") == 0)
      str = pAddon->Path();
    else if (strcmpi(id, "profile") == 0)
      str = pAddon->Profile();
    else if (strcmpi(id, "stars") == 0)
      str = StringUtils::Format("%d", pAddon->Stars());
    else if (strcmpi(id, "summary") == 0)
      str = pAddon->Summary();
    else if (strcmpi(id, "type") == 0)
      str = ADDON::TranslateType(pAddon->Type());
    else if (strcmpi(id, "version") == 0)
      str = pAddon->Version().asString();
    else
      throw ADDON::WrongValueException("CAddonCB_General - %s - add-on '%s' requests invalid id '%s'",
                            __FUNCTION__, addon->GetAddon()->Name().c_str(), id);

    char* buffer = strdup(str.c_str());
    return buffer;
  }
  HANDLE_ADDON_EXCEPTION

  return nullptr;
}

char* CAddonCB_General::translate_path(void* hdl, const char* path)
{
  try
  {
    if (!hdl || !path)
      throw ADDON::WrongValueException("CAddonCB_General - %s - invalid data (handle='%p', path='%p')",
                                        __FUNCTION__, hdl, path);

    std::string string = CSpecialProtocol::TranslatePath(path);
    char* buffer = strdup(string.c_str());
    return buffer;
  }
  HANDLE_ADDON_EXCEPTION

  return nullptr;
}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace AddOnLIB */
