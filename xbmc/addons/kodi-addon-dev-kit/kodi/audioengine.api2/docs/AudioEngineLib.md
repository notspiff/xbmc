# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md#CAudioEngineLib)
</p>*
#### *<p align="center">Group: ```General audio engine functions```</p>*
----------

Functions
-------------

The with ```#include <kodi/audioengine.api2/AEStream.h``` given functions are basically used to allow add-on access to Kodi's audio engine system functions and used for related add-ons

1. [bool RegisterMe(void *handle);](#CAudioEngineLib_RegisterMe)
* [void UnRegisterMe();](#CAudioEngineLib_UnRegisterMe)
* [void AddMenuHook(AE_DSP_MENUHOOK* hook);](#CAudioEngineLib_AddMenuHook)
* [void RemoveDSPMenuHook(AE_DSP_MENUHOOK* hook);](#CAudioEngineLib_RemoveDSPMenuHook)
* [void RegisterDSPMode(AE_DSP_MODES::AE_DSP_MODE* mode);](#CAudioEngineLib_RegisterDSPMode)
* [void UnregisterDSPMode(AE_DSP_MODES::AE_DSP_MODE* mode);](#CAudioEngineLib_UnregisterDSPMode)
* [bool GetCurrentSinkFormat(AudioEngineFormat &SinkFormat);](#CAudioEngineLib_GetCurrentSinkFormat)

-------------

*  <a id="CAudioEngineLib_RegisterMe"></a><b>```bool CAudioEngineLib::RegisterMe(void *handle);```</b>
    * Resolve all callback methods for Audio DSP system
	    * <b>```handle```</b> Pointer to the add-on
      * <b>return:</b> True when all methods were resolved, false otherwise.

	```C++
	  ADDON_STATUS ADDON_Create(void* hdl, void* props)
	  {
	    ...
	    if (!CAudioEngineLib::RegisterMe(hdl))
	      return ADDON_STATUS_PERMANENT_FAILURE;
	    ...
	```

*  <a id="CAudioEngineLib_UnRegisterMe"></a><b>```void CAudioEngineLib::UnRegisterMe();```</b>
    * Release all callback methods and close handling with them

-------------

*  <a id="CAudioEngineLib_AddMenuHook"></a><b>```void CAudioEngineLib::AddMenuHook(AE_DSP_MENUHOOK* hook);```</b>
    * Add or replace a menu hook for the context menu on audio DSP add-on.
      Related menu becomes called with ```AE_DSP_ERROR CallMenuHook(const AE_DSP_MENUHOOK& menuhook, const AE_DSP_MENUHOOK_DATA &item);``` from Kodi.
	    * <b>```hook```</b> The hook to add
	```C++
	    // need stored on a place to become access on access on ```RemoveDSPMenuHook``` if it becomes used.
      AE_DSP_MENUHOOK hook;
  	  ...
  	  // available categories are:
  	  // - AE_DSP_MENUHOOK_ALL             = all categories
  	  // - AE_DSP_MENUHOOK_PRE_PROCESS     = for pre processing
  	  // - AE_DSP_MENUHOOK_MASTER_PROCESS  = for master processing
  	  // - AE_DSP_MENUHOOK_POST_PROCESS    = for post processing
  	  // - AE_DSP_MENUHOOK_RESAMPLE        = for re sample
  	  // - AE_DSP_MENUHOOK_MISCELLANEOUS   = for miscellaneous dialogues
  	  // - AE_DSP_MENUHOOK_INFORMATION     = dialogue to show processing information
  	  // - AE_DSP_MENUHOOK_SETTING         = for settings

      hook.iHookId = 1;                               // (required) this hook's identifier
      hook.iLocalizedStringId = 30107;                // (required) the id of the label for this hook in g_localizeStrings
      hook.categor = AE_DSP_MENUHOOK_MASTER_PROCESS;  // (required) category of menu hook
      hook.iRelevantModeId = 1;                       // (required) except category AE_DSP_MENUHOOK_SETTING and AE_DSP_MENUHOOK_ALL must be the related mode id present here
      hook.bNeedPlayback = true;                      // (required) set to true if menu hook need playback and active processing
      CAudioEngineLib::AddMenuHook(&hook);
  	  ...
	```

*  <a id="CAudioEngineLib_RemoveDSPMenuHook"></a><b>```void RemoveDSPMenuHook(AE_DSP_MENUHOOK* hook);```</b>
    * Remove a menu hook for the context menu for this add-on
      Usage is optional, if add-on never change the menu can be on ```AddMenuHook``` also a local structure used.
	    * <b>```hook```</b> The hook to remove

-------------

*  <a id="CAudioEngineLib_RegisterDSPMode"></a><b>```void RegisterDSPMode(AE_DSP_MODES::AE_DSP_MODE* mode);```</b>
    * Add or replace mode information inside audio dsp database.
      Identifier becomes written to structure on field iModeID if it was 0 (undefined)
	    * <b>```mode```</b> The mode to add or update inside database

*  <a id="CAudioEngineLib_UnregisterDSPMode"></a><b>```void UnregisterDSPMode(AE_DSP_MODES::AE_DSP_MODE* mode);```</b>
    * Remove a mode from audio dsp database
	    * <b>```mode```</b> The Mode to remove

-------------

*  <a id="CAudioEngineLib_GetCurrentSinkFormat"></a><b>```void GetCurrentSinkFormat(AudioEngineFormat &SinkFormat);```</b>
    * Get the current sink data format
	    * <b>```SinkFormat```</b> Current sink data format. For more details see AudioEngineFormat.
      * <b>return:</b> Returns true on success, else false.
