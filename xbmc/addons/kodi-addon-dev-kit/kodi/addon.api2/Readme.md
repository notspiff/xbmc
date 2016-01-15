# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="docs/help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md)
</p>*
#### *<p align="center">Binary add-on library, Version Level: 2</p>*
-------------
##### Binary classes and function to use on add-on's

Below is a code example do show what must be done on add-on base function to become support for library:

```cpp
#include "kodi/addon.api2/AddonLib.h"
#include "kodi/addon.api2/General.h"  // Needed for CAddOnLib_General::Log

// Insert one macro on your add-on for it
IMPLEMENT_KODI_ADDON_LIBRARY;
...

ADDON_STATUS ADDON_Create(void* hdl, void* props)
{
  if (!hdl || !props)
    return ADDON_STATUS_UNKNOWN;

  // Enable access to all add-on to Kodi functions
  if (!CAddonLib::RegisterMe(hdl))
    return ADDON_STATUS_PERMANENT_FAILURE;
  ...
  
  // Example lib call
  CAddOnLib_General::Log(LOG_INFO, "My add-on creation done");

  return ADDON_STATUS_OK;
}

void ADDON_Destroy()
{
  ...
  CAddonLib::UnRegisterMe();
  ...
}
```

<b>Note:</b>
To use the add-on on Windows must be the [```dlfcn-win32.cpp```](dlfcn-win32.cpp) inserted on them. Is required to have translation functions from Windows to ```dlfcn```, requested for access to Kodi!

-------------

Below is showing you a description and usage of parts which becomes usable on add-on. Also a small 
demonstration code is inserted there.

###### Functions
* **`bool CAddonLib::RegisterMe(void *handle);`**
	* Get the codec id used by Kodi
		- **`handle`:** Pointer to the add-on
		- **return:** True when all methods were resolved, false otherwise

* **`void CAddonLib::UnRegisterMe();`**
	* Release all callback methods and close handling with them

1. [CAddOnLib_General](docs/General.md) - General functions
  * [void CAddOnLib_General::Log(const addon_log_t loglevel, const char* format, ...);](docs/General.md#Log)
    - Kodi log file write
  * [bool CAddOnLib_General::GetSettingString(const std::string& settingName, std::string& settingValue, bool global);](docs/General.md#GetSettingString)
    - Settings read about a string value
  * [bool CAddOnLib_General::GetSettingInt(const std::string& settingName, int& settingValue, bool global);](docs/General.md#GetSettingInt)
    - Settings read about a integer value
  * [bool CAddOnLib_General::GetSettingBoolean(const std::string& settingName, bool& settingValue, bool global);](docs/General.md#GetSettingBoolean)
    - Settings read about a boolean value
  * [bool CAddOnLib_General::GetSettingFloat(const std::string& settingName, float& settingValue, bool global);](docs/General.md#GetSettingFloat)
    - Settings read about a floating value
  * [void CAddOnLib_General::QueueNotification(const queue_msg_t type, const char* format, ...);](docs/General.md#QueueNotification_1)
    - Notification message
  * [void CAddOnLib_General::QueueNotification(const queue_msg_t type, const std::string& aCaption, const std::string& aDescription, unsigned int displayTime, bool withSound, unsigned int messageTime);](docs/General.md#QueueNotification_2)
    - Notification message
  * [void CAddOnLib_General::QueueNotification(const std::string& aCaption, const std::string& aDescription);](docs/General.md#QueueNotification_3)
    - Notification message
  * [void CAddOnLib_General::QueueNotification(const std::string& aImageFile, const std::string& aCaption, const std::string& aDescription, unsigned int displayTime, bool withSound, unsigned int messageTime);](docs/General.md#QueueNotification_4)
    - Notification message
  * [void CAddOnLib_General::GetMD5(const std::string& text, std::string& md5);](docs/General.md#GetMD5)
    - Get the MD5 digest of the given text
  * [bool CAddOnLib_General::UnknownToUTF8(const std::string& stringSrc, std::string& utf8StringDst, bool failOnBadChar = false);](docs/General.md#UnknownToUTF8)
    - String convert to UTF8
  * [std::string CAddOnLib_General::GetLocalizedString(uint32_t labelId, const std::string& strDefault = "");](docs/General.md#GetLocalizedString)
    - Localized string return
  * [std::string GetLanguage(lang_formats format = LANG_FMT_ENGLISH_NAME, bool region = false) const;](#GetLanguage)
    - Returns the active language as a string
  * [std::string CAddOnLib_General::GetDVDMenuLanguage();](docs/General.md#GetDVDMenuLanguage)
    - DVD language
  * [bool CAddOnLib_General::StartServer(eservers typ, bool start, bool wait = false);](docs/General.md#StartServer)
    - start or stop a server.
  * [void CAddOnLib_General::AudioSuspend();](docs/General.md#AudioSuspend)
    - Suspend Audio engine
  * [void CAddOnLib_General::AudioResume();](docs/General.md#AudioResume)
    - Resume Audio engine
  * [float CAddOnLib_General::GetVolume(bool percentage = true);](docs/General.md#GetVolume)
    - Current volume
  * [void CAddOnLib_General::SetVolume(float value, bool isPercentage = true);](docs/General.md#SetVolume)
    - Set volume
  * [bool CAddOnLib_General::IsMuted();](docs/General.md#IsMuted)
    - Is muted?
  * [void CAddOnLib_General::ToggleMute(void);](docs/General.md#ToggleMute)
    - Toogle mute
  * [void CAddOnLib_General::SetMute(bool mute);](docs/General.md#SetMute)
    - Set mute
  * [dvd_state GetOpticalDriveState();](#GetOpticalDriveState)
    - Returns the dvd state as an integer
  * [bool CAddOnLib_General::EjectOpticalDrive();](docs/General.md#EjectOpticalDrive)
    - Eject a drive
  * [void CAddOnLib_General::KodiVersion(kodi_version_t& version);](docs/General.md#KodiVersion)
    - Current version
  * [void CAddOnLib_General::KodiQuit();](docs/General.md#KodiQuit)
    - Quit Kodi
  * [void CAddOnLib_General::HTPCShutdown();](docs/General.md#HTPCShutdown)
    - Shutdown the htpc
  * [void CAddOnLib_General::HTPCRestart();](docs/General.md#HTPCRestart)
    - Restart the htpc
  * [void CAddOnLib_General::ExecuteScript(const std::string& script);](docs/General.md#ExecuteScript)
    - Execute a python script
  * [void CAddOnLib_General::ExecuteBuiltin(const std::string& function, bool wait = false);](docs/General.md#ExecuteBuiltin)
    - Execute a built in Kodi function.
  * [std::string CAddOnLib_General::ExecuteJSONRPC(const std::string& jsonrpccommand) const;](docs/General.md#ExecuteJSONRPC)
    - Execute an JSONRPC command.
  * [std::string CAddOnLib_General::GetRegion(const std::string& id) const;](docs/General.md#GetRegion)
    - Returns your regions setting as a string for the specified id.
  * [long CAddOnLib_General::GetFreeMem();](docs/General.md#GetFreeMem)
    - Returns the amount of free memory in MB as an integer.
  * [int CAddOnLib_General::GetGlobalIdleTime();](docs/General.md#GetGlobalIdleTime)
    - Returns the elapsed idle time in seconds as an integer.
  * [std::string CAddOnLib_General::TranslateAddonStatus(ADDON_STATUS status);](docs/General.md#TranslateAddonStatus)
    - Become string about error
  * [std::string CAddOnLib_General::GetAddonInfo(std::string& id) const;](docs/General.md#GetAddonInfo)
    - Returns the value of an addon property as a string

* [CAddOnLib_Codec](docs/Codec.md) - Codec functions
  * [kodi_codec_t CAddOnLib_Codec::GetCodecByName(const std::string &strCodecName);](docs/Codec.md#GetCodecByName)
    - Get the codec id used by Kodi
  * [DemuxPacket* CAddOnLib_Codec::AllocateDemuxPacket(int iDataSize);](docs/Codec.md) 
    - Allocate a demux packet. Free with FreeDemuxPacket
  * [void CAddOnLib_Codec::FreeDemuxPacket(DemuxPacket* pPacket);](docs/Codec.md) 
    - Free a packet that was allocated with AllocateDemuxPacket

* [CAddOnLib_Directory](docs/Directory.md) - Directory functions
  * [bool CAddOnLib_Directory::CanOpenDirectory(const std::string& strUrl);](docs/Directory.md) 
    - Checks whether a directory can be opened.
  * [bool CAddOnLib_Directory::CreateDirectory(const std::string& strPath);](docs/Directory.md) 
    - Creates a directory.
  * [bool CAddOnLib_Directory::DirectoryExists(const std::string& strPath);](docs/Directory.md) 
    - Checks if a directory exists.
  * [bool CAddOnLib_Directory::RemoveDirectory(const std::string& strPath);](docs/Directory.md) 
    - Removes a directory.

* [CAddOnLib_File](docs/File.md) - File functions
  * [bool CAddOnLib_File::FileExists(const std::string& strFileName, bool bUseCache);](docs/File.md) 
    - Check if a file exists
  * [int CAddOnLib_File::StatFile(const std::string& strFileName, struct __stat64* buffer);](docs/File.md) 
    - Reads file status
  * [bool CAddOnLib_File::DeleteFile(const std::string& strFileName);](docs/File.md) 
    - Deletes a file
  * [std::string CAddOnLib_File::GetFileMD5(const std::string& strPath);](docs/File.md) 
    - Retrieve MD5sum of a file
  * [unsigned int CAddOnLib_File::GetChunkSize(unsigned int chunk, unsigned int minimum);](docs/File.md) 
    - Return a size aligned to the chunk size
  * [std::string CAddOnLib_File::GetFileName(const std::string& path, char separator = PATH_SEPARATOR_CHAR);](docs/File.md)
    - Return the file name from given complete path string
  * [std::string CAddOnLib_File::GetDirectoryName(const std::string& path, char separator = PATH_SEPARATOR_CHAR)](docs/File.md) 
    - Return the directory name from given complete path string

* [CAddOnLib_Network](docs/Network.md) - Network functions
  * [bool CAddOnLib_Network::WakeOnLan(const char* mac);](docs/Network.md)
    - Send WakeOnLan magic packet
  * [std::string CAddOnLib_Network::GetIPAddress();](docs/Network.md)
    - Returns the current IP address as a string
  * [std::string CAddOnLib_Network::URLEncode(const std::string& url);](docs/Network.md)
    - Encode an URL
  * [bool CAddOnLib_Network::DNSLookup(const std::string& strHostName, std::string& strIpAddress);](docs/Network.md)
    - Lookup URL in DNS cache

* [CAddOnLib_VFSUtils](docs/VFSUtils.md) - Virtual file system (VFS) functions
  * [bool CAddOnLib_VFSUtils::GetDirectory(const std::string& path, const std::string& mask, std::vector< CVFSDirEntry>& items);](docs/VFSUtils.md)
    - Lists a directory

###### Classes

1. <a id="file_operation_classes"></a>File operation classes
  * [CVFSFile](docs/File.md)
* <a id="background_sound play_classes"></a>Background sound play classes
  * [CAddonSoundPlay](docs/SoundPlay.md)
* <a id="vfs_classes"></a>Virtual file system (VFS) classes
  * [CVFSDirEntry](docs/VFSUtils.md)
  * [CVFSProperty](docs/VFSUtils.md)
