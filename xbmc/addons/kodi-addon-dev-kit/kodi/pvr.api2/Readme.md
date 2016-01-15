# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="docs/help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md)
</p>*
#### *<p align="center">Binary add-on PVR library, Version Level: 2</p>*
-------------
##### Binary classes and function to use on add-on's

This library is for PVR add-ons to allow cross talk. Becomes needed to inform Kodi about changes on the PVR system.

<b>Note:</b>
This library part is only needed on PVR add-ons, for other types is nothing inside.

Below is a code example do show what must be done on add-on base function to become support for library:

```cpp
#include "kodi/addon.api2/AddonLib.h"
#include "kodi/addon.api2/General.h"  // Needed for CAddOnLib_General::Log
#include "kodi/pvr.api2/PVRLib.h"

// Insert one macro on your add-on for it
IMPLEMENT_KODI_ADDON_LIBRARY;
IMPLEMENT_KODI_PVR_LIBRARY;
...

ADDON_STATUS ADDON_Create(void* hdl, void* props)
{
  if (!hdl || !props)
    return ADDON_STATUS_UNKNOWN;

  // Enable access to all add-on to Kodi functions
  if (!CAddonLib::RegisterMe(hdl))
    return ADDON_STATUS_PERMANENT_FAILURE;
  if (!CPVRLib::RegisterMe(hdl))
    return ADDON_STATUS_PERMANENT_FAILURE;
  ...

  // Example lib call
  CAddOnLib_General::Log(LOG_INFO, "My add-on creation done");

  return ADDON_STATUS_OK;
}

void ADDON_Destroy()
{
  ...
  CPVRLib::UnRegisterMe();
  CAddonLib::UnRegisterMe();
  ...
}
```

<b>Note:</b>
To use this library part must always ```CAddonLib``` be present!

-------------

Below is showing you a description and usage of parts which becomes usable on add-on. Also a small 
demonstration code is inserted there.

###### Functions

1. <a id="CPVRLib"></a>[CPVRLib](docs/CPVRLib.md) - General CPVRLib functions
   * [bool CPVRLib::RegisterMe(void *handle);](docs/CPVRLib.md#CPVRLib_RegisterMe)
     - Resolve all callback methods
   * [void CPVRLib::UnRegisterMe();](docs/CPVRLib.md#CPVRLib_UnRegisterMe)
     - Release all callback methods and close handling with them
   * [void CPVRLib::AddMenuHook();](docs/CPVRLib.md#CPVRLib_AddMenuHook)
     - Add or replace a menu hook for the context menu for this PVR add-on
   * [void CPVRLib::Recording();](docs/CPVRLib.md#CPVRLib_Recording)
     - Display a notification in Kodi that a recording started or stopped on the server
2. <a id="CPVRLib_Transfer"></a>[CPVRLib_Transfer](docs/CPVRLib_Transfer.md) - Functions to transfer add-on data to Kodi
   * [void CPVRLib_Transfer::EpgEntry(const ADDON_HANDLE handle, const EPG_TAG* entry);](docs/CPVRLib_Transfer.md#CPVRLib_Transfer_EpgEntry)
     - Transfer an EPG tag from the add-on to Kodi
   * [void CPVRLib_Transfer::ChannelEntry(const ADDON_HANDLE handle, const PVR_CHANNEL* entry);](docs/CPVRLib_Transfer.md#CPVRLib_Transfer_ChannelEntry)
     - Transfer a channel entry from the add-on to Kodi
   * [void CPVRLib_Transfer::TimerEntry(const ADDON_HANDLE handle, const PVR_TIMER*   entry);](docs/CPVRLib_Transfer.md#CPVRLib_Transfer_TimerEntry)
     - Transfer a timer entry from the add-on to Kodi
   * [void CPVRLib_Transfer::RecordingEntry(const ADDON_HANDLE handle, const PVR_RECORDING* entry);](docs/CPVRLib_Transfer.md#CPVRLib_Transfer_RecordingEntry)
     - Transfer a recording entry from the add-on to Kodi
   * [void CPVRLib_Transfer::ChannelGroup(const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP* entry);](docs/CPVRLib_Transfer.md#CPVRLib_Transfer_ChannelGroup)
     - Transfer a channel group from the add-on to Kodi.
   * [void CPVRLib_Transfer::ChannelGroupMember(const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP_MEMBER* entry);](docs/CPVRLib_Transfer.md#CPVRLib_Transfer_ChannelGroupMember)
     - Transfer a channel group member entry from the add-on to Kodi.
3. <a id="CPVRLib_Trigger"></a>[CPVRLib_Trigger](docs/CPVRLib_Trigger.md) - Trigger work in Kodi functions
   * [void CPVRLib_Trigger::TimerUpdate(void);](docs/CPVRLib_Trigger.md#CPVRLib_Trigger_TimerUpdate)
     - Request Kodi to update it's list of timers
   * [void CPVRLib_Trigger::RecordingUpdate(void);](docs/CPVRLib_Trigger.md#CPVRLib_Trigger_RecordingUpdate)
     - Request Kodi to update it's list of recordings
   * [void CPVRLib_Trigger::ChannelUpdate(void);](docs/CPVRLib_Trigger.md#CPVRLib_Trigger_ChannelUpdate)
     - Request Kodi to update it's list of channels
   * [void CPVRLib_Trigger::ChannelGroupsUpdate(void);](docs/CPVRLib_Trigger.md#CPVRLib_Trigger_ChannelGroupsUpdate)
     - Request Kodi to update it's list of channel groups
   * [void CPVRLib_Trigger::EpgUpdate(unsigned int iChannelUid);](docs/CPVRLib_Trigger.md#CPVRLib_Trigger_EpgUpdate)
     - Schedule an EPG update for the given channel channel
    
###### Classes
1. <a id="StreamUtils">[CStreamProperties](docs/StreamUtils.md#CStreamProperties)
* [CPVRStream](docs/StreamUtils.md#CPVRStream)
