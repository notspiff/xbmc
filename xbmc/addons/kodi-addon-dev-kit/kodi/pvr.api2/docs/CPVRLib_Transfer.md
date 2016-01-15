# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md#CPVRLib_Transfer)
</p>*
#### *<p align="center">Group: `Data transfer from request calls`</p>*
----------

Functions
-------------

The with `#include <kodi/pvr.api2/PVRLib.h` given functions are used to transfer data on Kodi after it becomes called from related add-on functions.

1. [void EpgEntry(const ADDON_HANDLE handle, const EPG_TAG* entry);](#CPVRLib_Transfer_EpgEntry) 
* [void ChannelEntry(const ADDON_HANDLE handle, const PVR_CHANNEL* entry);](#CPVRLib_Transfer_ChannelEntry) 
* [void TimerEntry(const ADDON_HANDLE handle, const PVR_TIMER* entry);](#CPVRLib_Transfer_TimerEntry)
* [void RecordingEntry(const ADDON_HANDLE handle, const PVR_RECORDING* entry);](#CPVRLib_Transfer_RecordingEntry)
* [void ChannelGroup(const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP* entry);](#CPVRLib_Transfer_ChannelGroup)
* [void ChannelGroupMember(const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP_MEMBER* entry);](#CPVRLib_Transfer_ChannelGroupMember)

-------------

*  <a id="CPVRLib_Transfer_EpgEntry"></a>**`void CPVRLib_Transfer::EpgEntry(const ADDON_HANDLE handle, const EPG_TAG* entry);`**
    * Transfer an EPG tag from the add-on to Kodi, becomes needed on call from `PVR_ERROR GetEPGForChannel(ADDON_HANDLE handle, const PVR_CHANNEL& channel, time_t iStart, time_t iEnd);`.
        * **`handle`** The handle parameter that Kodi used when requesting the EPG data
        * **`entry`** The entry to transfer to Kodi

*  <a id="CPVRLib_Transfer_ChannelEntry"></a>**`void CPVRLib_Transfer::ChannelEntry(const ADDON_HANDLE handle, const PVR_CHANNEL* entry);`**
    * Transfer a channel entry from the add-on to Kodi, becomes needed on call from `PVR_ERROR GetChannels(ADDON_HANDLE handle, bool bRadio);`.
        * **`handle`** The handle parameter that Kodi used when requesting the channel list
        * **`entry`** The entry to transfer to Kodi

*  <a id="CPVRLib_Transfer_TimerEntry"></a>**`void CPVRLib_Transfer::TimerEntry(const ADDON_HANDLE handle, const PVR_TIMER* entry);`**
    * Transfer a timer entry from the add-on to Kodi, becomes needed on call from `PVR_ERROR GetTimers(ADDON_HANDLE handle);`.
        * **`handle`** The handle parameter that Kodi used when requesting the timers list
        * **`entry`** The entry to transfer to Kodi

*  <a id="CPVRLib_Transfer_RecordingEntry"></a>**`void CPVRLib_Transfer::RecordingEntry(const ADDON_HANDLE handle, const PVR_RECORDING* entry);`**
    * Transfer a recording entry from the add-on to Kodi, becomes needed on call from `
        * **`handle`** The handle parameter that Kodi used when requesting the recordings list
        * **`entry`** The entry to transfer to Kodi

*  <a id="CPVRLib_Transfer_ChannelGroup"></a>**`void CPVRLib_Transfer::ChannelGroup(const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP* entry);`**
    * Transfer a channel group from the add-on to Kodi. The group will be created if it doesn't exist.
      This becomes needed on call from `PVR_ERROR GetChannelGroups(ADDON_HANDLE handle, bool bRadio);`.
        * **`handle`** The handle parameter that Kodi used when requesting the channel groups list
        * **`entry`** entry The entry to transfer to Kodi

*  <a id="CPVRLib_Transfer_ChannelGroupMember"></a>**`void CPVRLib_Transfer::ChannelGroupMember(const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP_MEMBER* entry);`**
    * Transfer a channel group member entry from the add-on to Kodi. The channel will be added to the group if the group can be found.
      This becomes needed on call from `PVR_ERROR GetChannelGroupMembers(ADDON_HANDLE handle, const PVR_CHANNEL_GROUP& group);`.
        * **`handle`** The handle parameter that Kodi used when requesting the channel group members list
        * **`entry`** The entry to transfer to Kodi
