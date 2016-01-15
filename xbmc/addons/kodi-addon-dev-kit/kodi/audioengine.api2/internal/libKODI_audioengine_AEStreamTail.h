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

namespace AudioEngineLIB
{
namespace V2
{

  inline CAELib_Stream::CAELib_Stream(
      AudioEngineFormat   Format,
      unsigned int        Options)
   : m_Handle((ADDON::AddonCB*)CGUILib::g_libKODI_Internal->m_Handle),
     m_Callbacks(CGUILib::g_libKODI_Internal->m_Callbacks)
  {
    m_StreamHandle = m_Callbacks->make_stream(m_Handle, Format, Options);
    if (!m_StreamHandle)
      fprintf(stderr, "libKODI_audioengine-ERROR: make_stream failed!\n");
  }

  inline CAELib_Stream::~CAELib_Stream()
  {
    m_Callbacks->free_stream(m_Handle, m_StreamHandle);
  }

  inline unsigned int CAELib_Stream::GetSpace()
  {
    return m_Callbacks->Stream.AEStream_GetSpace(m_AddonHandle, m_StreamHandle);
  }

  inline unsigned int CAELib_Stream::AddData(uint8_t* const *Data, unsigned int Offset, unsigned int Frames)
  {
    return m_Callbacks->Stream.AEStream_AddData(m_AddonHandle, m_StreamHandle, Data, Offset, Frames);
  }

  inline double CAELib_Stream::GetDelay()
  {
    return m_Callbacks->Stream.AEStream_GetDelay(m_AddonHandle, m_StreamHandle);
  }

  inline bool CAELib_Stream::IsBuffering()
  {
    return m_Callbacks->Stream.AEStream_IsBuffering(m_AddonHandle, m_StreamHandle);
  }

  inline double CAELib_Stream::GetCacheTime()
  {
    return m_Callbacks->Stream.AEStream_GetCacheTime(m_AddonHandle, m_StreamHandle);
  }

  inline double CAELib_Stream::GetCacheTotal()
  {
    return m_Callbacks->Stream.AEStream_GetCacheTotal(m_AddonHandle, m_StreamHandle);
  }

  inline void CAELib_Stream::Pause()
  {
    return m_Callbacks->Stream.AEStream_Pause(m_AddonHandle, m_StreamHandle);
  }

  inline void CAELib_Stream::Resume()
  {
    return m_Callbacks->Stream.AEStream_Resume(m_AddonHandle, m_StreamHandle);
  }

  inline void CAELib_Stream::Drain(bool Wait)
  {
    return m_Callbacks->Stream.AEStream_Drain(m_AddonHandle, m_StreamHandle, Wait);
  }

  inline bool CAELib_Stream::IsDraining()
  {
    return m_Callbacks->Stream.AEStream_IsDraining(m_AddonHandle, m_StreamHandle);
  }

  inline bool CAELib_Stream::IsDrained()
  {
    return m_Callbacks->Stream.AEStream_IsDrained(m_AddonHandle, m_StreamHandle);
  }

  inline void CAELib_Stream::Flush()
  {
    return m_Callbacks->Stream.AEStream_Flush(m_AddonHandle, m_StreamHandle);
  }

  inline float CAELib_Stream::GetVolume()
  {
    return m_Callbacks->Stream.AEStream_GetVolume(m_AddonHandle, m_StreamHandle);
  }

  inline void CAELib_Stream::SetVolume(float Volume)
  {
    return m_Callbacks->Stream.AEStream_SetVolume(m_AddonHandle, m_StreamHandle, Volume);
  }

  inline float CAELib_Stream::GetAmplification()
  {
    return m_Callbacks->Stream.AEStream_GetAmplification(m_AddonHandle, m_StreamHandle);
  }

  inline void CAELib_Stream::SetAmplification(float Amplify)
  {
    return m_Callbacks->Stream.AEStream_SetAmplification(m_AddonHandle, m_StreamHandle, Amplify);
  }

  inline const unsigned int CAELib_Stream::GetFrameSize() const
  {
    return m_Callbacks->Stream.AEStream_GetFrameSize(m_AddonHandle, m_StreamHandle);
  }

  inline const unsigned int CAELib_Stream::GetChannelCount() const
  {
    return m_Callbacks->Stream.AEStream_GetChannelCount(m_AddonHandle, m_StreamHandle);
  }

  inline const unsigned int CAELib_Stream::GetSampleRate() const
  {
    return m_Callbacks->Stream.AEStream_GetSampleRate(m_AddonHandle, m_StreamHandle);
  }

  inline const AEDataFormat CAELib_Stream::GetDataFormat() const
  {
    return m_Callbacks->Stream.AEStream_GetDataFormat(m_AddonHandle, m_StreamHandle);
  }

  inline double CAELib_Stream::GetResampleRatio()
  {
    return m_Callbacks->Stream.AEStream_GetResampleRatio(m_AddonHandle, m_StreamHandle);
  }

  inline void CAELib_Stream::SetResampleRatio(double Ratio)
  {
    m_Callbacks->Stream.AEStream_SetResampleRatio(m_AddonHandle, m_StreamHandle, Ratio);
  }

}; /* namespace V2 */
}; /* namespace AudioEngineLIB */
