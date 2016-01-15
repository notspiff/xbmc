# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="docs/help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md)
</p>*
#### *<p align="center">Binary add-on audio engine library, Version Level: 2</p>*
-------------
##### Binary classes and function to use on add-on's

Below is a code example do show what must be done on add-on base function to become support for library:

```cpp
#include "kodi/addon.api2/AddonLib.h"
#include "kodi/addon.api2/General.h"
#include "kodi/audioengine.api2/AudioEngineLib.h"

// Insert one macro on your add-on for it
IMPLEMENT_KODI_ADDON_LIBRARY;
IMPLEMENT_KODI_AUDIOENGINE_LIBRARY;
...

ADDON_STATUS ADDON_Create(void* hdl, void* props)
{
  if (!hdl || !props)
    return ADDON_STATUS_UNKNOWN;

  // Enable access to all add-on to Kodi functions
  if (!CAddonLib::RegisterMe(hdl))
    return ADDON_STATUS_PERMANENT_FAILURE;
  if (!CAudioEngineLib::RegisterMe(hdl))
    return ADDON_STATUS_PERMANENT_FAILURE;
  ...

  // Example lib call
  CAddOnLib_General::Log(LOG_INFO, "My add-on creation done");

  return ADDON_STATUS_OK;
}

void ADDON_Destroy()
{
  ...
  CAudioEngineLib::UnRegisterMe();
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

1. <a id="CAudioEngineLib"></a>[CAudioEngineLib](docs/AudioEngineLib.md) - General CAudioEngineLib functions
   * [bool CAudioEngineLib::RegisterMe(void *handle);](docs/AudioEngineLib.md#CAudioEngineLib_RegisterMe)
     - Resolve all callback methods
   * [void CAudioEngineLib::UnRegisterMe(void *handle);](docs/AudioEngineLib.md#CAudioEngineLib_UnRegisterMe)
     - Release all callback methods and close handling with them
   * [void CAudioEngineLib::AddDSPMenuHook(AE_DSP_MENUHOOK* hook);](docs/AudioEngineLib.md#CAudioEngineLib_AddDSPMenuHook)
     - Add or replace a menu hook for the context menu for a DSP add-on
   * [void CAudioEngineLib::RemoveDSPMenuHook(AE_DSP_MENUHOOK* hook);](docs/AudioEngineLib.md#CAudioEngineLib_RemoveDSPMenuHook)
     - Remove a menu hook for the context menu for this add-on
   * [void CAudioEngineLib::RegisterDSPMode(AE_DSP_MODES::AE_DSP_MODE* mode);](docs/AudioEngineLib.md#CAudioEngineLib_RegisterDSPMode)
     - Add or replace a menu hook for the context menu for a DSP add-on
   * [void CAudioEngineLib::UnregisterDSPMode(AE_DSP_MODES::AE_DSP_MODE* mode);](docs/AudioEngineLib.md#CAudioEngineLib_UnregisterDSPMode)
     - Remove a menu hook for the context menu for this add-on
   * [void CAudioEngineLib::GetCurrentSinkFormat(AudioEngineFormat &SinkFormat);](docs/AudioEngineLib.md#CAudioEngineLib_GetCurrentSinkFormat)
     - Current sink data format. For more details see AudioEngineFormat.

###### Classes
1. <a id="AEStream">[CStreamProperties](docs/AEStream.md)
  * [CAELibStream](docs/StreamUtils.md#CAELibStream) - Audio Engine Stream Class
