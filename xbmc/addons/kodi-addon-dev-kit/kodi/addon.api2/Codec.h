#pragma once
/*
 *      Copyright (C) 2015 Team KODI
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with KODI; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "definations.h"
#include "internal/libKODI_addon_CodecHead.h"
#include "internal/libKODI_addon_Internal.h"

namespace AddOnLIB
{
namespace V2
{

  ///
  /// \defgroup CAddonLib_Codec
  /// \ingroup AddOnLIB
  /// @{
  /// @brief <b>Demux packet handle and codec identification class</b>
  ///
  /// This class brings the support for obtaining required codec identifications
  /// and packages for handling stream demuxer.
  ///
  /// Currently, this class is only required under PVR systems where by
  /// CAddonLib_Codec::AllocateDemuxPacket(...) a package for the function
  /// <b><tt>DemuxPacket* DemuxRead (void);</tt></b> must be provided.
  ///
  /// These are pure static functions them no other initialization need.
  ///
  /// It has the header \ref Codec.h "#include <kodi/addon.api2/Codec.h>"
  /// to enjoy it.
  ///
  class CAddonLib_Codec
  {
  public:

    ///
    /// @ingroup CAddonLib_Codec
    /// @brief Get the codec id used by Kodi.
    ///
    /// This function is required on registration of streams to Kodi, what is
    /// currently needed on the PVR add-on system where the demuxing becomes
    /// handled from them.
    ///
    /// About available codec/demuxer names see [<b>see ffmpeg allformats.c</b>](https://www.ffmpeg.org/doxygen/2.8/allformats_8c_source.html)
    /// in function <b><tt>void av_register_all(void)</tt></b> with on macro <b><tt>REGISTER_DEMUXER</tt></b>
    /// defined values. Further are inside Kodi the two names <b><em>TELETEXT</em></b>
    /// and <b><em>RDS</em></b> used to get kodi_codec value.
    ///
    /// @param[in] strCodecName The name of the codec
    /// @return The codec_id, or a codec_id with 0 values when not supported
    ///
    static kodi_codec GetCodecByName(const std::string &strCodecName);

    ///
    /// @ingroup CAddonLib_Codec
    /// @brief Allocate a demux packet. Free with FreeDemuxPacket
    ///
    /// Create a free demux packet with requested size
    ///
    /// @param[in] iDataSize The size of the data that will go into the packet
    /// @return The allocated packet
    ///
    /// Here is a view of packet data structure:
    /// \code
    /// typedef struct DemuxPacket
    /// {
    ///   unsigned char* pData;   // data
    ///   int iSize;              // data size
    ///   int iStreamId;          // integer representing the stream index
    ///   int iGroupId;           // the group this data belongs to, used to
    ///                           // group data from different streams together
    ///
    ///   double pts;             // pts in DVD_TIME_BASE
    ///   double dts;             // dts in DVD_TIME_BASE
    ///   double duration;        // duration in DVD_TIME_BASE if available
    /// } DemuxPacket;
    /// \endcode
    ///
    static DemuxPacket* AllocateDemuxPacket(int iDataSize);

    ///
    /// @ingroup CAddonLib_Codec
    /// @brief Free a packet that was allocated with AllocateDemuxPacket
    /// @param[in] pPacket The packet to free
    ///
    static void FreeDemuxPacket(DemuxPacket* pPacket);

  }; /* class CAddonLib_Codec */
  /** @}*/


  ///
  /// \defgroup CodecDescriptor
  /// \ingroup AddOnLIB
  /// @{
  /// @brief <b>Codec type name converter</b>
  ///
  /// Some of the backends codec names don't match ffmpeg's, so translate
  /// them to something ffmpeg understands.
  ///
  /// Adapter which converts codec names used by several backends into their
  /// FFmpeg equivalents.
  ///
  /// This class is optional and is available here for two reasons. One is the
  /// some PVR add-ons need this and the other to provide an example if the own
  /// add-on also names are used not to ffmpeg are compatible. Then it might be
  /// a copy of this class to its own needs.
  ///
  /// It has the header \ref Codec.h "#include <kodi/addon.api2/Codec.h>" be included
  /// to enjoy it.
  ///
  class CodecDescriptor
  {
  public:

    ///
    /// \internal
    /// @ingroup CodecDescriptor
    /// @brief Class constructor
    ///
    /// @note Is internal used from the CodecDescriptor::GetCodecByName(...) call
    /// and not needed to create byself.
    ///
    CodecDescriptor(void)
    {
      m_codec.codec_id   = KODI_INVALID_CODEC_ID;
      m_codec.codec_type = KODI_CODEC_TYPE_UNKNOWN;
    }

    ///
    /// \internal
    /// @ingroup CodecDescriptor
    /// @brief Class constructor
    ///
    /// @param[in] codec Codec id used on Kodi (ffmpeg id)
    /// @param[in] name Name string about codec (ffmepg string)
    ///
    /// @note Is internal used from the CodecDescriptor::GetCodecByName(...) call
    /// and not needed to create byself.
    ///
    CodecDescriptor(kodi_codec codec, const char* name)
      : m_codec(codec),
        m_strName(name) {}

    ///
    /// \internal
    /// @ingroup CodecDescriptor
    /// @brief Destructor
    ///
    virtual ~CodecDescriptor(void) {}

    ///
    /// @ingroup CodecDescriptor
    /// @brief Function to retrieve used Kodi codec name.
    ///
    /// @return The string for codec based upon ffmpeg
    ///
    const std::string& Name(void) const  { return m_strName; }

    ///
    /// @ingroup CodecDescriptor
    /// @brief Function to retrieve used Kodi codec identification id.
    ///
    /// @return identification of codec
    ///
    kodi_codec Codec(void) const { return m_codec; }

    ///
    /// @ingroup CodecDescriptor
    /// @brief Static function to translate codec names who are different to them
    /// on Kodi (ffmpeg).
    ///
    /// @param[in] strCodecName The own used codec name, currently this are <b><em>MPEG2AUDIO</em></b>,
    /// <b><em>MPEGTS</em></b> and <b><em>TEXTSUB</em></b>
    /// @return This class generated with defined Name and Codec identifier
    ///
    static CodecDescriptor GetCodecByName(const char* strCodecName)
    {
      CodecDescriptor retVal;
      // some of the backends codec names don't match ffmpeg's, so translate them to something ffmpeg understands
      if (!strcmp(strCodecName, "MPEG2AUDIO"))
        retVal = CodecDescriptor(CAddonLib_Codec::GetCodecByName("MP2"), strCodecName);
      else if (!strcmp(strCodecName, "MPEGTS"))
        retVal = CodecDescriptor(CAddonLib_Codec::GetCodecByName("MPEG2VIDEO"), strCodecName);
      else if (!strcmp(strCodecName, "TEXTSUB"))
        retVal = CodecDescriptor(CAddonLib_Codec::GetCodecByName("TEXT"), strCodecName);
      else
        retVal = CodecDescriptor(CAddonLib_Codec::GetCodecByName(strCodecName), strCodecName);

      return retVal;
    }

  private:
    kodi_codec m_codec;
    std::string  m_strName;
  };
  /** @}*/

}; /* namespace V2 */
}; /* namespace AddOnLIB */
#include "internal/libKODI_addon_CodecTail.h"
