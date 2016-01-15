# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md#CPVRLib)
</p>*
#### *<p align="center">Group: ```General```</p>*
----------

Functions
-------------

The with ```#include <kodi/pvr.api2/PVRLib.h``` given functions are basically used to allow add-on access to Kodi's PVR system functions

1. [bool RegisterMe(void *handle);](#CPVRLib_RegisterMe) 
* [void UnRegisterMe();](#CPVRLib_UnRegisterMe) 
* [void AddMenuHook(PVR_MENUHOOK* hook);](#CPVRLib_AddMenuHook)
* [void Recording(const std::string& strRecordingName, const std::string& strFileName, bool bOn);](#CPVRLib_Recording)

-------------

*  <a id="CPVRLib_RegisterMe"></a><b>```bool CPVRLib::RegisterMe(void *handle);```</b>
    * Resolve all callback methods for PVR
        * <b>```handle```</b>Pointer to the add-on 
        * <b>return:</b> </b> True when all methods were resolved, false otherwise.
        ```C++
          ADDON_STATUS ADDON_Create(void* hdl, void* props)
          {
            ...
            if (!CPVRLib::RegisterMe(hdl))
              return ADDON_STATUS_PERMANENT_FAILURE;
        ...

*  <a id="CPVRLib_UnRegisterMe"></a><b>```void CPVRLib::UnRegisterMe();```</b>
    * Release all callback methods and close handling with them

-------------

*  <a id="CPVRLib_AddMenuHook"></a><b>```void CPVRLib::AddMenuHook(PVR_MENUHOOK* hook);```</b>
    * Add or replace a menu hook for the context menu on add-on.
      Related menu becomes called with ```PVR_ERROR CallMenuHook(const PVR_MENUHOOK& menuhook, const PVR_MENUHOOK_DATA &item);``` from Kodi.
        * <b>```hook```</b> The hook to add
	```C++
  	  ...
  	  // available categories are:
  	  // - PVR_MENUHOOK_ALL                = all categories
  	  // - PVR_MENUHOOK_CHANNEL            = for channels
  	  // - PVR_MENUHOOK_TIMER              = for timers
  	  // - PVR_MENUHOOK_EPG                = for EPG
  	  // - PVR_MENUHOOK_RECORDING          = for recordings
  	  // - PVR_MENUHOOK_DELETED_RECORDING  = deleted recordings
  	  // - PVR_MENUHOOK_SETTING            = for settings

      PVR_MENUHOOK hook;
      hook.iHookId = 1;
      hook.category = PVR_MENUHOOK_SETTING;
      hook.iLocalizedStringId = 30107;
      CPVRLib::AddMenuHook(&hook);
  	  ...
	```

*  <a id="CPVRLib_Recording"></a><b>```void CPVRLib::Recording(const std::string& strRecordingName, const std::string& strFileName, bool bOn);```</b>
    * Display a notification in Kodi that a recording started or stopped on the server
        * <b>```strRecordingName```</b> The name of the recording to display
        * <b>```strFileName```</b> The filename of the recording
        * <b>```bOn```</b> True when recording started, false when it stopped

