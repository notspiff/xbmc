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

#ifdef BUILD_KODI_ADDON
  #include "kodi/AudioEngine/AEChannelData.h"
  #include "kodi/AudioEngine/AEChannelInfo.h"
  #include "kodi/AudioEngine/AEStreamData.h"
#else
  #include "cores/AudioEngine/Utils/AEChannelData.h"
  #include "cores/AudioEngine/Utils/AEChannelInfo.h"
  #include "cores/AudioEngine/Utils/AEStreamData.h"
#endif

#include "addons/kodi-addon-dev-kit/kodi/kodi_audioengine_types.h"
#include "addons/kodi-addon-dev-kit/kodi/kodi_adsp_types.h"
#include "addons/kodi-addon-dev-kit/kodi/addon.api2/AddonLib.h"

namespace AudioEngineLIB
{
namespace V2
{

#define IMPLEMENT_ADDON_AE_STREAM                                              \
  private:                                                                     \
    AEStreamHandle* m_StreamHandle;                                            \
    CB_AddOnLib*    m_Callbacks;                                               \
    void*           m_AddonHandle;

  // Audio Engine Stream definitions
  typedef unsigned int            _Stream_GetSpace(void *addonData, AEStreamHandle *handle);
  typedef unsigned int            _Stream_AddData(void *addonData, AEStreamHandle *handle, uint8_t* const *Data, unsigned int Offset, unsigned int Frames);
  typedef double                  _Stream_GetDelay(void *addonData, AEStreamHandle *handle);
  typedef bool                    _Stream_IsBuffering(void *addonData, AEStreamHandle *handle);
  typedef double                  _Stream_GetCacheTime(void *addonData, AEStreamHandle *handle);
  typedef double                  _Stream_GetCacheTotal(void *addonData, AEStreamHandle *handle);
  typedef void                    _Stream_Pause(void *addonData, AEStreamHandle *handle);
  typedef void                    _Stream_Resume(void *addonData, AEStreamHandle *handle);
  typedef void                    _Stream_Drain(void *addonData, AEStreamHandle *handle, bool Wait);
  typedef bool                    _Stream_IsDraining(void *addonData, AEStreamHandle *handle);
  typedef bool                    _Stream_IsDrained(void *addonData, AEStreamHandle *handle);
  typedef void                    _Stream_Flush(void *addonData, AEStreamHandle *handle);
  typedef float                   _Stream_GetVolume(void *addonData, AEStreamHandle *handle);
  typedef void                    _Stream_SetVolume(void *addonData, AEStreamHandle *handle, float Volume);
  typedef float                   _Stream_GetAmplification(void *addonData, AEStreamHandle *handle);
  typedef void                    _Stream_SetAmplification(void *addonData, AEStreamHandle *handle, float Amplify);
  typedef const unsigned int      _Stream_GetFrameSize(void *addonData, AEStreamHandle *handle);
  typedef const unsigned int      _Stream_GetChannelCount(void *addonData, AEStreamHandle *handle);
  typedef const unsigned int      _Stream_GetSampleRate(void *addonData, AEStreamHandle *handle);
  typedef const AEDataFormat      _Stream_GetDataFormat(void *addonData, AEStreamHandle *handle);
  typedef double                  _Stream_GetResampleRatio(void *addonData, AEStreamHandle *handle);
  typedef void                    _Stream_SetResampleRatio(void *addonData, AEStreamHandle *handle, double Ratio);

  typedef struct CB_AudioEngineLib_Stream
  {
    // AudioEngine stream callbacks
    _Stream_GetSpace*               AEStream_GetSpace;
    _Stream_AddData*                AEStream_AddData;
    _Stream_GetDelay*               AEStream_GetDelay;
    _Stream_IsBuffering*            AEStream_IsBuffering;
    _Stream_GetCacheTime*           AEStream_GetCacheTime;
    _Stream_GetCacheTotal*          AEStream_GetCacheTotal;
    _Stream_Pause*                  AEStream_Pause;
    _Stream_Resume*                 AEStream_Resume;
    _Stream_Drain*                  AEStream_Drain;
    _Stream_IsDraining*             AEStream_IsDraining;
    _Stream_IsDrained*              AEStream_IsDrained;
    _Stream_Flush*                  AEStream_Flush;
    _Stream_GetVolume*              AEStream_GetVolume;
    _Stream_SetVolume*              AEStream_SetVolume;
    _Stream_GetAmplification*       AEStream_GetAmplification;
    _Stream_SetAmplification*       AEStream_SetAmplification;
    _Stream_GetFrameSize*           AEStream_GetFrameSize;
    _Stream_GetChannelCount*        AEStream_GetChannelCount;
    _Stream_GetSampleRate*          AEStream_GetSampleRate;
    _Stream_GetDataFormat*          AEStream_GetDataFormat;
    _Stream_GetResampleRatio*       AEStream_GetResampleRatio;
    _Stream_SetResampleRatio*       AEStream_SetResampleRatio;
  } CB_AudioEngineLib_Stream;

}; /* namespace V2 */
}; /* namespace AudioEngineLIB */
