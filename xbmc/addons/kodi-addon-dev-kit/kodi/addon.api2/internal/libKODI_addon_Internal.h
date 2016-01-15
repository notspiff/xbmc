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

#include <memory>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#include "../definations.h"
#include "libKODI_addon_GeneralHead.h"
#include "libKODI_addon_AudioHead.h"
#include "libKODI_addon_CodecHead.h"
#include "libKODI_addon_DirectoryHead.h"
#include "libKODI_addon_FileHead.h"
#include "libKODI_addon_NetworkHead.h"
#include "libKODI_addon_VFSUtilsHead.h"

#include "kodi/xbmc_addon_types.h"

#ifdef _WIN32                   // windows
  #ifndef _SSIZE_T_DEFINED
    typedef intptr_t      ssize_t;
    #define _SSIZE_T_DEFINED
  #endif // !_SSIZE_T_DEFINED

  #if defined(BUILD_KODI_ADDON)
      #include "platform/windows/dlfcn-win32.h"
  #else
      #include "dlfcn-win32.h"
  #endif
#else
  #include <dlfcn.h>              // linux+osx
#endif

#ifdef LOG_DEBUG
#undef LOG_DEBUG
#endif
#ifdef LOG_INFO
#undef LOG_INFO
#endif
#ifdef LOG_NOTICE
#undef LOG_NOTICE
#endif
#ifdef LOG_ERROR
#undef LOG_ERROR
#endif

#ifdef BUILD_KODI_ADDON
namespace ADDON
{
  typedef struct AddonCB
  {
    const char* libBasePath;  ///< Never, never change this!!!
    void*       addonData;
  } AddonCB;
}
#endif

#define IMPLEMENT_KODI_ADDON_LIBRARY                                           \
namespace AddOnLIB                                                             \
{                                                                              \
namespace V2                                                                   \
{                                                                              \
  std::shared_ptr<CAddonLib_Internal> CAddonLib::g_libKODI_Internal;           \
}; /* namespace V2 */                                                          \
}; /* namespace AddOnLIB */

#define KODI_ADDON_LIBRARY                                                     \
  public:                                                                      \
    static std::shared_ptr<CAddonLib_Internal> g_libKODI_Internal;             \
  public:                                                                      \
    CAddonLib() { }                                                            \
    virtual ~CAddonLib() { }

class IAESound;

namespace AddOnLIB
{
namespace V2
{
extern "C"
{

  class CAddonLib_SoundPlay;

  typedef struct CB_AddOnLib
  {
    CB_AddonLib_General         General;
    CB_AddonLib_Audio           Audio;
    CB_AddonLib_Codec           Codec;
    CB_AddonLib_Directory       Directory;
    CB_AddonLib_VFS             VFS;
    CB_AddonLib_File            File;
    CB_AddonLib_Network         Network;
  } CB_AddOnLib;

  typedef CB_AddOnLib*  _register_level(void *HANDLE, int level);
  typedef void          _unregister_me(void* HANDLE, void* CB);

  class CAddonLib_Internal
  {
  public:
    CAddonLib_Internal()
      : m_libKODI_addon(nullptr),
        m_Handle(nullptr) { }

    virtual ~CAddonLib_Internal()
    {
      UnRegisterMe();
    }

    bool RegisterMe(void *Handle)
    {
      m_Handle = Handle;

      m_libKODI_addon = dlopen(nullptr, RTLD_LAZY);
      if (m_libKODI_addon == nullptr)
      {
        fprintf(stderr, "Unable to load %s\n", dlerror());
        return false;
      }

      KODI_register = (_register_level*)
        dlsym(m_libKODI_addon, "ADDONLIB_V2_register_level");
      if (KODI_register == nullptr)
      {
        fprintf(stderr, "Unable to assign function %s\n", dlerror());
        return false;
      }

      KODI_unregister = (_unregister_me*)
        dlsym(m_libKODI_addon, "ADDONLIB_V2_unregister");
      if (KODI_unregister == nullptr)
      {
        fprintf(stderr, "Unable to assign function %s\n", dlerror());
        return false;
      }

      m_Callbacks = KODI_register(m_Handle, 2);
      return m_Callbacks != nullptr;
    }

    void UnRegisterMe()
    {
      if (m_libKODI_addon)
      {
        KODI_unregister(m_Handle, m_Callbacks);
        dlclose(m_libKODI_addon);
        m_libKODI_addon = nullptr;
      }
    }
    /*\_________________________________________________________________________
    \*/
    std::string GetAddonInfo(std::string& id) const
    {
      std::string strReturn;
      char* strMsg = m_Callbacks->General.get_addon_info(m_Handle, id.c_str());
      if (strMsg != nullptr)
      {
        if (std::strlen(strMsg))
          strReturn = strMsg;
        m_Callbacks->General.free_string(m_Handle, strMsg);
      }
      return strReturn;
    }

    bool GetSetting(const std::string& settingName, void *settingValue, bool global)
    {
      return m_Callbacks->General.get_setting(m_Handle, settingName.c_str(), settingValue, global);
    }

    void OpenSettings()
    {
      m_Callbacks->General.open_settings_dialog(m_Handle);
    }

    void Log(const addon_log loglevel, const char *format, va_list &args)
    {
      char buffer[16384];
      vsprintf (buffer, format, args);
      va_end (args);
      m_Callbacks->General.addon_log_msg(m_Handle, loglevel, buffer);
    }

    void QueueFormattedNotification(const queue_msg type, const char *format, va_list &args)
    {
      char buffer[16384];
      vsprintf(buffer, format, args);
      va_end(args);
      m_Callbacks->General.queue_notification(m_Handle, type, buffer);
    }

    void QueueNotification
            (const queue_msg  type,
             const std::string& aCaption,
             const std::string& aDescription,
             unsigned int       displayTime,
             bool               withSound,
             unsigned int       messageTime)
    {
      m_Callbacks->General.queue_notification_from_type(m_Handle,
                                        type, aCaption.c_str(), aDescription.c_str(),
                                        displayTime, withSound, messageTime);
    }

    void QueueNotification
            (const std::string& aCaption,
             const std::string& aDescription)
    {
      m_Callbacks->General.queue_notification_with_image(m_Handle, "",
                                        aCaption.c_str(), aDescription.c_str(),
                                        5000, false, 1000);
    }

    void QueueNotification
          (const std::string& aImageFile,
           const std::string& aCaption,
           const std::string& aDescription,
           unsigned int       displayTime,
           bool               withSound,
           unsigned int       messageTime)
    {
      m_Callbacks->General.queue_notification_with_image(m_Handle, aImageFile.c_str(),
                                        aCaption.c_str(), aDescription.c_str(),
                                        displayTime, withSound, messageTime);
    }

    void GetMD5(const std::string& text, std::string& md5)
    {
      char* md5ret = (char*)malloc(40*sizeof(char)); // md5 size normally 32 bytes
      m_Callbacks->General.get_md5(text.c_str(), *md5ret);
      md5 = md5ret;
      free(md5ret);
    }

    bool UnknownToUTF8(const std::string& stringSrc, std::string& utf8StringDst, bool failOnBadChar)
    {
      bool ret = false;
      char* retString = m_Callbacks->General.unknown_to_utf8(m_Handle, stringSrc.c_str(), ret, failOnBadChar);
      if (retString != nullptr)
      {
        if (ret)
          utf8StringDst = retString;
        m_Callbacks->General.free_string(m_Handle, retString);
      }
      return ret;
    }

    std::string GetLocalizedString(uint32_t labelId, const std::string& strDefault) const
    {
      std::string strReturn = strDefault;
      char* strMsg = m_Callbacks->General.get_localized_string(m_Handle, labelId);
      if (strMsg != nullptr)
      {
        if (std::strlen(strMsg))
          strReturn = strMsg;
        m_Callbacks->General.free_string(m_Handle, strMsg);
      }
      return strReturn;
    }

    std::string GetLanguage(lang_formats format, bool region) const
    {
      std::string language;
      language.resize(256);
      unsigned int size = (unsigned int)language.capacity();
      m_Callbacks->General.get_language(m_Handle, language[0], size, format, region);
      language.resize(size);
      language.shrink_to_fit();
      return language;
    }

    std::string GetDVDMenuLanguage()
    {
      std::string language;
      language.resize(16);
      unsigned int size = (unsigned int)language.capacity();
      m_Callbacks->General.get_dvd_menu_language(m_Handle, language[0], size);
      language.resize(size);
      language.shrink_to_fit();
      return language;
    }

    bool StartServer(eservers typ, bool start, bool wait)
    {
      return m_Callbacks->General.start_server(m_Handle, (int)typ, start, wait);
    }

    void AudioSuspend()
    {
      m_Callbacks->General.audio_suspend(m_Handle);
    }

    void AudioResume()
    {
      m_Callbacks->General.audio_resume(m_Handle);
    }

    float GetVolume(bool percentage) const
    {
      return m_Callbacks->General.get_volume(m_Handle, percentage);
    }

    void SetVolume(float value, bool isPercentage)
    {
      m_Callbacks->General.set_volume(m_Handle, value, isPercentage);
    }

    bool IsMuted() const
    {
      return m_Callbacks->General.is_muted(m_Handle);
    }

    void ToggleMute(void)
    {
      m_Callbacks->General.toggle_mute(m_Handle);
    }

    void SetMute(bool mute)
    {
      if (m_Callbacks->General.is_muted(m_Handle) != mute)
        m_Callbacks->General.toggle_mute(m_Handle);
    }

    dvd_state GetOpticalDriveState()
    {
      return (dvd_state)m_Callbacks->General.get_optical_state(m_Handle);
    }

    bool EjectOpticalDrive()
    {
      return m_Callbacks->General.eject_optical_drive(m_Handle);
    }

    void KodiVersion(kodi_version& version)
    {
      char* compile_name = nullptr;
      char* revision     = nullptr;
      char* tag          = nullptr;
      char* tag_revision = nullptr;

      m_Callbacks->General.kodi_version(m_Handle, compile_name, version.major, version.minor, revision, tag, tag_revision);
      if (compile_name != nullptr)
      {
        version.compile_name  = compile_name;
        m_Callbacks->General.free_string(m_Handle, compile_name);
      }
      if (revision != nullptr)
      {
        version.revision = revision;
        m_Callbacks->General.free_string(m_Handle, revision);
      }
      if (tag != nullptr)
      {
        version.tag = tag;
        m_Callbacks->General.free_string(m_Handle, tag);
      }
      if (tag_revision != nullptr)
      {
        version.tag_revision = tag_revision;
        m_Callbacks->General.free_string(m_Handle, tag_revision);
      }
    }

    void KodiQuit()
    {
      m_Callbacks->General.kodi_quit(m_Handle);
    }

    void HTPCShutdown()
    {
      m_Callbacks->General.htpc_shutdown(m_Handle);
    }

    void HTPCRestart()
    {
      m_Callbacks->General.htpc_restart(m_Handle);
    }

    void ExecuteScript(const std::string& script)
    {
      m_Callbacks->General.execute_script(m_Handle, script.c_str());
    }

    void ExecuteBuiltin(const std::string& function, bool wait)
    {
      m_Callbacks->General.execute_builtin(m_Handle, function.c_str(), wait);
    }

    std::string ExecuteJSONRPC(const std::string& jsonrpccommand) const
    {
      std::string strReturn;
      char* strMsg = m_Callbacks->General.execute_jsonrpc(m_Handle, jsonrpccommand.c_str());
      if (strMsg != nullptr)
      {
        if (std::strlen(strMsg))
          strReturn = strMsg;
        m_Callbacks->General.free_string(m_Handle, strMsg);
      }
      return strReturn;
    }

    std::string GetRegion(const std::string& id) const
    {
      std::string strReturn;
      char* strMsg = m_Callbacks->General.get_region(m_Handle, id.c_str());
      if (strMsg != nullptr)
      {
        if (std::strlen(strMsg))
          strReturn = strMsg;
        m_Callbacks->General.free_string(m_Handle, strMsg);
      }
      return strReturn;
    }

    long GetFreeMem()
    {
      return m_Callbacks->General.get_free_mem(m_Handle);
    }

    int GetGlobalIdleTime()
    {
      return m_Callbacks->General.get_global_idle_time(m_Handle);
    }

    std::string TranslatePath(const std::string& path)
    {
      std::string strReturn;
      char* strMsg = m_Callbacks->General.translate_path(m_Handle, path.c_str());
      if (strMsg != nullptr)
      {
        if (std::strlen(strMsg))
          strReturn = strMsg;
        m_Callbacks->General.free_string(m_Handle, strMsg);
      }
      return strReturn;
    }

    /*\_________________________________________________________________________
    \*/
    bool WakeOnLan(const std::string& mac)
    {
      return m_Callbacks->Network.wake_on_lan(m_Handle, mac.c_str());
    }

    std::string GetIPAddress()
    {
      std::string ip;
      ip.resize(32);
      unsigned int size = (unsigned int)ip.capacity();
      m_Callbacks->Network.get_ip_address(m_Handle, ip[0], size);
      ip.resize(size);
      ip.shrink_to_fit();
      return ip;
    }

    bool DNSLookup(const std::string& strHostName, std::string& strIpAddress)
    {
      bool ret = false;
      char* ipAddress = m_Callbacks->Network.dns_lookup(m_Handle, strHostName.c_str(), ret);
      if (ipAddress != nullptr)
      {
        strIpAddress = ipAddress;
        m_Callbacks->General.free_string(m_Handle, ipAddress);
      }
      return ret;
    }

    std::string URLEncode(const std::string& url)
    {
      std::string retString;
      char* string = m_Callbacks->Network.url_encode(m_Handle, url.c_str());
      if (string != nullptr)
      {
        retString = string;
        m_Callbacks->General.free_string(m_Handle, string);
      }
      return retString;
    }
    /*\_________________________________________________________________________
    \*/
    void* OpenFile(const std::string& strFileName, unsigned int flags)
    {
      return m_Callbacks->File.open_file(m_Handle, strFileName.c_str(), flags);
    }

    void* OpenFileForWrite(const std::string& strFileName, bool bOverWrite)
    {
      return m_Callbacks->File.open_file_for_write(m_Handle, strFileName.c_str(), bOverWrite);
    }

    ssize_t ReadFile(void* file, void* lpBuf, size_t uiBufSize)
    {
      return m_Callbacks->File.read_file(m_Handle, file, lpBuf, uiBufSize);
    }

    bool ReadFileString(void* file, char *szLine, int iLineLength)
    {
      return m_Callbacks->File.read_file_string(m_Handle, file, szLine, iLineLength);
    }

    ssize_t WriteFile(void* file, const void* lpBuf, size_t uiBufSize)
    {
      return m_Callbacks->File.write_file(m_Handle, file, lpBuf, uiBufSize);
    }

    void FlushFile(void* file)
    {
       return m_Callbacks->File.flush_file(m_Handle, file);
    }

    int64_t SeekFile(void* file, int64_t iFilePosition, int iWhence)
    {
      return m_Callbacks->File.seek_file(m_Handle, file, iFilePosition, iWhence);
    }

    int TruncateFile(void* file, int64_t iSize)
    {
      return m_Callbacks->File.truncate_file(m_Handle, file, iSize);
    }

    int64_t GetFilePosition(void* file)
    {
      return m_Callbacks->File.get_file_position(m_Handle, file);
    }

    int64_t GetFileLength(void* file)
    {
      return m_Callbacks->File.get_file_length(m_Handle, file);
    }

    void CloseFile(void* file)
    {
      return m_Callbacks->File.close_file(m_Handle, file);
    }

    int GetFileChunkSize(void* file)
    {
      return m_Callbacks->File.get_file_chunk_size(m_Handle, file);
    }

    bool FileExists(const std::string& strFileName, bool bUseCache)
    {
      return m_Callbacks->File.file_exists(m_Handle, strFileName.c_str(), bUseCache);
    }

    int StatFile(const std::string& strFileName, struct __stat64* buffer)
    {
      return m_Callbacks->File.stat_file(m_Handle, strFileName.c_str(), buffer);
    }

    bool DeleteFile(const std::string& strFileName)
    {
      return m_Callbacks->File.delete_file(m_Handle, strFileName.c_str());
    }

    std::string GetFileMD5(const std::string& strFileName)
    {
      std::string strReturn;
      char* strMd5 = m_Callbacks->File.get_file_md5(m_Handle, strFileName.c_str());
      if (strMd5 != nullptr)
      {
        if (std::strlen(strMd5))
          strReturn = strMd5;
        m_Callbacks->General.free_string(m_Handle, strMd5);
      }
      return strReturn;
    }

    std::string GetCacheThumbName(const std::string& strFileName)
    {
      std::string strReturn;
      char* strThumbName = m_Callbacks->File.get_cache_thumb_name(m_Handle, strFileName.c_str());
      if (strThumbName != nullptr)
      {
        if (std::strlen(strThumbName))
          strReturn = strThumbName;
        m_Callbacks->General.free_string(m_Handle, strThumbName);
      }
      return strReturn;
    }

    std::string MakeLegalFileName(const std::string& strFileName)
    {
      std::string strReturn;
      char* strLegalFileName = m_Callbacks->File.make_legal_filename(m_Handle, strFileName.c_str());
      if (strLegalFileName != nullptr)
      {
        if (std::strlen(strLegalFileName))
          strReturn = strLegalFileName;
        m_Callbacks->General.free_string(m_Handle, strLegalFileName);
      }
      return strReturn;
    }

    std::string MakeLegalPath(const std::string& strPath)
    {
      std::string strReturn;
      char* strLegalPath = m_Callbacks->File.make_legal_path(m_Handle, strPath.c_str());
      if (strLegalPath != nullptr)
      {
        if (std::strlen(strLegalPath))
          strReturn = strLegalPath;
        m_Callbacks->General.free_string(m_Handle, strLegalPath);
      }
      return strReturn;
    }

    /*\_________________________________________________________________________
    \*/
    bool CanOpenDirectory(const std::string& strUrl)
    {
      return m_Callbacks->Directory.can_open_directory(m_Handle, strUrl.c_str());
    }

    bool CreateDirectory(const std::string& strPath)
    {
      return m_Callbacks->Directory.create_directory(m_Handle, strPath.c_str());
    }

    bool DirectoryExists(const std::string& strPath)
    {
      return m_Callbacks->Directory.directory_exists(m_Handle, strPath.c_str());
    }

    bool RemoveDirectory(const std::string& strPath)
    {
      return m_Callbacks->Directory.remove_directory(m_Handle, strPath.c_str());
    }

    /*\_________________________________________________________________________
    \*/

    bool GetVFSDirectory(const char *strPath, const char* mask, VFSDirEntry** items, unsigned int* num_items)
    {
      return m_Callbacks->VFS.get_vfs_directory(m_Handle, strPath, mask, items, num_items);
    }

    void FreeVFSDirectory(VFSDirEntry* items, unsigned int num_items)
    {
      return m_Callbacks->VFS.free_vfs_directory(m_Handle, items, num_items);
    }

    /*\_________________________________________________________________________
    \*/

    kodi_codec GetCodecByName(const char* strCodecName)
    {
      return m_Callbacks->Codec.get_codec_by_name(m_Handle, strCodecName);
    }

    DemuxPacket* AllocateDemuxPacket(int iDataSize)
    {
      return m_Callbacks->Codec.allocate_demux_packet(m_Handle, iDataSize);
    }

    void FreeDemuxPacket(DemuxPacket* pPacket)
    {
      return m_Callbacks->Codec.free_demux_packet(m_Handle, pPacket);
    }

    /*\_________________________________________________________________________
    \*/

    std::string TranslateAddonStatus(ADDON_STATUS status)
    {
      switch (status)
      {
        case ADDON_STATUS_OK:                 return "OK";
        case ADDON_STATUS_LOST_CONNECTION:    return "Lost connection";
        case ADDON_STATUS_NEED_RESTART:       return "Needs restart";
        case ADDON_STATUS_NEED_SETTINGS:      return "Needs settngs";
        case ADDON_STATUS_UNKNOWN:            return "Unknown";
        case ADDON_STATUS_NEED_SAVEDSETTINGS: return "Needs saved settings";
        case ADDON_STATUS_PERMANENT_FAILURE:  return "Permanent failure";
        default:
          break;
      }
      return "";
    }

  protected:
    _register_level*  KODI_register;
    _unregister_me*   KODI_unregister;

  private:
    friend class CAddonLib_SoundPlay;
    friend class CAddonLib_VFSFile;

    void*         m_libKODI_addon;
    void*         m_Handle;
    CB_AddOnLib*  m_Callbacks;
    struct cb_array
    {
      const char* libPath;
    };
  };

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace AddOnLIB */
