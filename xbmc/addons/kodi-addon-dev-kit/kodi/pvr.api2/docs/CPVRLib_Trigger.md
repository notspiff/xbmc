# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md#CPVRLib_Trigger)
</p>*
#### *<p align="center">Group: `Update triggering`</p>*
----------

Functions
-------------

The with `#include <kodi/pvr.api2/PVRLib.h` given functions are used to transfer data on Kodi after it becomes called from related add-on functions.

1. [void TimerUpdate(void);](#CPVRLib_Trigger_TimerUpdate)
* [void RecordingUpdate(void);](#CPVRLib_Trigger_RecordingUpdate)
* [void ChannelUpdate(void);](#CPVRLib_Trigger_ChannelUpdate)
* [void ChannelGroupsUpdate(void);](#CPVRLib_Trigger_ChannelGroupsUpdate)
* [void EpgUpdate(unsigned int iChannelUid);](#CPVRLib_Trigger_EpgUpdate)

-------------

*  <a id="CPVRLib_Trigger_TimerUpdate"></a>**`void CPVRLib_Trigger::TimerUpdate(void);`**
    * Request Kodi to update it's list of timers

*  <a id="CPVRLib_Trigger_RecordingUpdate"></a>**`void CPVRLib_Trigger::RecordingUpdate(void);`**
    * Request Kodi to update it's list of recordings

*  <a id="CPVRLib_Trigger_ChannelUpdate"></a>**`void CPVRLib_Trigger::ChannelUpdate(void);`**
    * Request Kodi to update it's list of channels

*  <a id="CPVRLib_Trigger_ChannelGroupsUpdate"></a>**`void CPVRLib_Trigger::ChannelGroupsUpdate(void);`**
    * Request Kodi to update it's list of channel groups

*  <a id="CPVRLib_Trigger_EpgUpdate"></a>**`void CPVRLib_Trigger::EpgUpdate(unsigned int iChannelUid);`**
    * Schedule an EPG update for the given channel channel
        * **`iChannelUid`** The unique id of the channel for this add-on
