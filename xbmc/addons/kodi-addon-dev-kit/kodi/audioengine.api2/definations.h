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

#include <stdint.h>
#ifdef BUILD_KODI_ADDON
#include "kodi/AEChannelData.h"
#else
#include "cores/AudioEngine/Utils/AEChannelData.h"
#endif

#ifdef __cplusplus
namespace AudioEngineLIB
{
namespace V2
{
extern "C"
{
#endif

  /*!
   * \ingroup AudioEngineLIB
   * @{
   */

  static constexpr const int   AudioEngineLIB_apiLevel = 2;
  static constexpr const char* AudioEngineLIB_version  = "0.0.1";

  /**
   * A stream handle pointer, which is only used internally by the addon stream handle
   */
  typedef void AEStreamHandle;

  /**
   * The audio format structure that fully defines a stream's audio information
   */
  typedef struct AudioEngineFormat
  {
    /**
     * The stream's data format (eg, AE_FMT_S16LE)
     */
    enum AEDataFormat m_dataFormat;

    /**
     * The stream's sample rate (eg, 48000)
     */
    unsigned int m_sampleRate;

    /**
     * The encoded streams sample rate if a bitstream, otherwise undefined
     */
    unsigned int m_encodedRate;

    /**
     * The amount of used speaker channels
     */
    unsigned int m_channelCount;

    /**
     * The stream's channel layout
     */
    enum AEChannel m_channels[AE_CH_MAX];

    /**
     * The number of frames per period
     */
    unsigned int m_frames;

    /**
     * The number of samples in one frame
     */
    unsigned int m_frameSamples;

    /**
     * The size of one frame in bytes
     */
    unsigned int m_frameSize;

    AudioEngineFormat()
    {
      m_dataFormat = AE_FMT_INVALID;
      m_sampleRate = 0;
      m_encodedRate = 0;
      m_frames = 0;
      m_frameSamples = 0;
      m_frameSize = 0;
      m_channelCount = 0;

      for (unsigned int ch = 0; ch < AE_CH_MAX; ch++)
      {
        m_channels[ch] = AE_CH_NULL;
      }
    }

    bool compareFormat(const AudioEngineFormat *fmt)
    {
      if (!fmt)
      {
        return false;
      }

      if (m_dataFormat    != fmt->m_dataFormat    ||
          m_sampleRate    != fmt->m_sampleRate    ||
          m_encodedRate   != fmt->m_encodedRate   ||
          m_frames        != fmt->m_frames        ||
          m_frameSamples  != fmt->m_frameSamples  ||
          m_frameSize     != fmt->m_frameSize     ||
          m_channelCount  != fmt->m_channelCount)
      {
        return false;
      }

      for (unsigned int ch = 0; ch < AE_CH_MAX; ch++)
      {
        if (fmt->m_channels[ch] != m_channels[ch])
        {
          return false;
        }
      }

      return true;
    }
  } AudioEngineFormat;

  /*@}*/

#ifdef __cplusplus
}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace AudioEngineLIB */
#if defined(BUILD_KODI_ADDON)
  using namespace AudioEngineLIB::V2;
#endif
#endif
