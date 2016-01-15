# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md)
</p>*
#### *<p align="center">Group: ```Sound playback```</p>*
----------

The with ```#include <kodi/addon.api2/SoundPlay.h>``` given functions are basically used to allow add-on access to Kodi's functions

Classes
-------------

#### Class: ```CAddonSoundPlay::CAddonSoundPlay(...);```

*  <b>```CAddonSoundPlay(const std::string& filename)```</b>
    * Construct a new sound play back for given file name

*  <b>```virtual ~CAddonSoundPlay();```</b>
    * Destructor

*  <b>```virtual void Play();```</b>
    * Start playback

*  <b>```virtual void Stop();```</b>
    * Stop active playback
    
*  <b>```virtual bool IsPlaying();```</b>
    * Check playback active
		* <b>return:</b> true if playing

*  <b>```virtual void SetChannel(audio_channel_t channel);```</b>
    * Set a channel channel playback position
	    * <b>channel:</b> Flag, ```AUDIO_CH_INVALID``` if nothing selected and playback on all 
			- <i>Flags: AUDIO_CH_INVALID, AUDIO_CH_FL. AUDIO_CH_FR, AUDIO_CH_FC, AUDIO_CH_LFE, AUDIO_CH_SL, AUDIO_CH_SR, AUDIO_CH_BL, AUDIO_CH_BR</i>

*  <b>```virtual audio_channel_t GetChannel();```</b>
    * Get the flag about current selected playback channel
	    * <b>return:</b> Used flag, ```AUDIO_CH_INVALID``` if nothing selected and playback on all channels
			- <i>Flags: AUDIO_CH_INVALID, AUDIO_CH_FL. AUDIO_CH_FR, AUDIO_CH_FC, AUDIO_CH_LFE, AUDIO_CH_SL, AUDIO_CH_SR, AUDIO_CH_BL, AUDIO_CH_BR</i>

*  <b>```virtual void SetVolume(float volume);```</b>
	* The playback volume for file
	    * <b>```volume```</b>The volume to set

*  <b>```virtual float GetVolume();```</b>
    * The current playback volume of file
		* <b>return:</b> The volume
