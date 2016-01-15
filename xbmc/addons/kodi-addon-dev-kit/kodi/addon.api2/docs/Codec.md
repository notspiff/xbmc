# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md)
</p>*
#### *<p align="center">Group: ```Codec```</p>*
----------

Functions
-------------

The with ```#include <kodi/addon.api2/Codec.h>``` given functions are required if demux becomes done on add-on itself and stream packet is requested from Kodi, e.g. on PVR ```DemuxPacket* DemuxRead(void);```.

*  <b>```kodi_codec_t CAddOnLib_Codec::GetCodecByName(const std::string &strCodecName);```</b>
    * Get the codec id used by Kodi
	    * <b>```strCodecName```</b> The name of the codec, normally the from ffmpeg used ones
		* <b>return:</b> The codec_id, or a codec_id with 0 values when not supported

*  <b>```DemuxPacket* CAddOnLib_Codec::AllocateDemuxPacket(int iDataSize);```</b>
    * Allocate a demux packet. Free with FreeDemuxPacket
	    * <b>```iDataSize```</b> The size of the data that will go into the packet
		* <b>return:</b> The allocated packet

*  <b>```void CAddOnLib_Codec::FreeDemuxPacket(DemuxPacket* pPacket);```</b>
    * Free a packet that was allocated with AllocateDemuxPacket
	    * <b>```pPacket```</b>The packet to free

----------

Classes
-------------

#### Class: ```CodecDescriptor::CodecDescriptor();```
Adapter which converts codec names used by several backends into their FFmpeg equivalents.

*  <b>```CodecDescriptor::CodecDescriptor(kodi_codec_t codec, const char* name)```</b>
    * New class creation with given values, becomes done from static function ```GetCodecByName```
	    * <b>```codec```</b>The from Kodi's add-on system used iden
	    * <b>```name```</b>String name used on add-on to translate for Kodi
		    * Currently supported strings:
		      - MPEG2AUDIO: 
		      For mpeg2 audio stream
		      - MPEGTS:
		      For mpeg2 video stream
		      - TEXTSUB:
		      For teletext subtitle
		      - All others:
		      Are equal to ffmpeg's identification strings
*  <b>```const std::string& CodecDescriptor::Name(void) const;```</b>
	* Returns the used codec string name
*  <b>```kodi_codec_t CodecDescriptor::Codec(void) const;```</b>
	*  Returns the used Kodi's add-on codec structure.
*  <b>```static CodecDescriptor CodecDescriptor::GetCodecByName(const char* strCodecName);```</b>
	* Static creation function of class with string identification string, used to translate internal add-on format to on Kodi needed one.
	    * <b>```strCodecName```</b>The used codec name, see above
		* <b>return:</b> The created class

----------

Definations
-------------
```C++
typedef enum
{
  KODI_CODEC_TYPE_UNKNOWN = -1,
  KODI_CODEC_TYPE_VIDEO,
  KODI_CODEC_TYPE_AUDIO,
  KODI_CODEC_TYPE_DATA,
  KODI_CODEC_TYPE_SUBTITLE,
  KODI_CODEC_TYPE_RDS,
  KODI_CODEC_TYPE_NB
} kodi_codec_type_t;

typedef struct
{
  kodi_codec_type_t codec_type;
  kodi_codec_id_t   codec_id;
} kodi_codec_t;

#define KODI_INVALID_CODEC_ID   0
#define KODI_INVALID_CODEC      { KODI_CODEC_TYPE_UNKNOWN, KODI_INVALID_CODEC_ID }
```

----------
[TOC]
