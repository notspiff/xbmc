# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md#AEStream)
</p>*
#### *<p align="center">Group: `Audio Engine Stream Class`</p>*

----------

The with #include `<kodi/audioengine.api2/AEStream.h>` given functions are basically used to allow add-on access to Kodi's functions

Classes
-------------

#### <a id="CAELibStream"></a>Class: `CAELibStream::CAELibStream(...);`

*  **`CAELibStream(AEDataFormat DataFormat, unsigned int SampleRate, unsigned int EncodedSampleRate, CAEChannelInfo& ChannelLayout, unsigned int Options = 0)`**
    * Constructor
      * **`DataFormat`:** 
      * **`SampleRate`:** 
      * **`EncodedSampleRate`:** 
      * **`ChannelLayout`:** 
      * **`Options`:** 

*  **`unsigned int GetSpace();`**
    * Returns the amount of space available in the stream
      * **return:** The number of bytes AddData will consume

*  **`unsigned int AddData(uint8_t* const *Data, unsigned int Offset, unsigned int Frames);`**
    * Add planar or interleaved PCM data to the stream
      * **`Data`:** array of pointers to the planes
      * **`Offset`:** Offset to frame in frames
      * **`Frames`:** number of frames
      * **return:** The number of frames consumed

*  **`double GetDelay();`**
    * Returns the time in seconds that it will take for the next added packet to be heard from the speakers.
      * **return:** seconds

*  **`bool IsBuffering();`**
    * Returns if the stream is buffering
      * **return:** True if the stream is buffering

*  **`double GetCacheTime();`**
    * Returns the time in seconds that it will take to underrun the cache if no sample is added.
      * **return:** seconds

*  **`double GetCacheTotal();`**
    * Returns the total time in seconds of the cache
      * **return:** seconds

*  **`void Pause();`**
    * Pauses the stream playback

*  **`void Resume();`**
    * Resumes the stream after pausing

*  **`void Drain(bool Wait);`**
    * Start draining the stream
    * ***Note:*** Once called AddData will not consume more data.
      * **`Wait`:** ???

*  **`bool IsDraining();`**
    * Returns true if the is stream draining
      * **return:** true if streaming

*  **`bool IsDrained();`**
    * Returns true if the is stream has finished draining
      * **return:** true if finished

*  **`void Flush();`**
    * Flush all buffers dropping the audio data

*  **`float GetVolume();`**
    * Return the stream's current volume level
      * **return:** The volume level between 0.0 and 1.0

*  **`void  SetVolume(float Volume);`**
    * Set the stream's volume level
      * **`Amplify`:** The new volume level between 0.0 and 1.0

*  **`float GetAmplification();`**
    * Gets the stream's volume amplification in linear units.
      * **return:** The volume amplification factor between 1.0 and 1000.0

*  **`void SetAmplification(float Amplify);`**
    * Sets the stream's volume amplification in linear units.
      * **`Amplify`:** The volume amplification factor between 1.0 and 1000.0

*  **`const unsigned int GetFrameSize() const;`**
    * Returns the size of one audio frame in bytes (channelCount * resolution)
      * **return:** The size in bytes of one frame

*  **`const unsigned int GetChannelCount() const;`**
    * Returns the number of channels the stream is configured to accept
      * **return:** The channel count

*  **`const unsigned int GetSampleRate() const;`**
    * Returns the stream's sample rate, if the stream is using a dynamic sample rate, this value will NOT reflect any changes 
      made by calls to SetResampleRatio()
      * **return:** The stream's sample rate (eg, 48000)

*  **`const unsigned int GetEncodedSampleRate() const;`**
    * Returns the stream's encoded sample rate if the stream is RAW
      * **return:** The stream's encoded sample rate

*  **`const AEDataFormat GetDataFormat() const;`**
    * Return the data format the stream has been configured with
      * **return:** The stream's data format (eg, `AE_FMT_S16LE`)
      
*  **`double GetResampleRatio();`**
    * Return the resample ratio
    * ***Note::*** This will return an undefined value if the stream is not resampling
      * **return:** the current resample ratio or undefined if the stream is not resampling

*  **`bool SetResampleRatio(double Ratio);`**
    * Sets the resample ratio
    * ***Note:*** This function may return false if the stream is not resampling, if you wish to use this be sure to set the AESTREAM_FORCE_RESAMPLE option
      * **`Ratio`:** ratio the new sample rate ratio, calculated by `((double)desiredRate / (double)GetSampleRate())`
      * **return:** true if was OK
