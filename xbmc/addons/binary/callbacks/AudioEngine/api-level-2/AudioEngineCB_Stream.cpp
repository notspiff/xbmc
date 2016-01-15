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

#include "AudioEngineCB_Stream.h"
#include "AddonCallbacksAudioEngine.h"

#include "addons/binary/ExceptionHandling.h"
#include "cores/AudioEngine/AEFactory.h"
#include "cores/AudioEngine/Interfaces/AEStream.h"
#include "cores/AudioEngine/Utils/AEChannelData.h"
#include "utils/log.h"

using namespace ADDON;

namespace AudioEngineLIB
{
namespace V2
{
extern "C"
{

  CAudioEngineCB_Stream::CAudioEngineCB_Stream()
  {

  }

  void CAudioEngineCB_Stream::Init(CB_AudioEngineLib* callbacks)
  {
    callbacks->Stream.AEStream_GetSpace              = AEStream_GetSpace;
    callbacks->Stream.AEStream_AddData               = AEStream_AddData;
    callbacks->Stream.AEStream_GetDelay              = AEStream_GetDelay;
    callbacks->Stream.AEStream_IsBuffering           = AEStream_IsBuffering;
    callbacks->Stream.AEStream_GetCacheTime          = AEStream_GetCacheTime;
    callbacks->Stream.AEStream_GetCacheTotal         = AEStream_GetCacheTotal;
    callbacks->Stream.AEStream_Pause                 = AEStream_Pause;
    callbacks->Stream.AEStream_Resume                = AEStream_Resume;
    callbacks->Stream.AEStream_Drain                 = AEStream_Drain;
    callbacks->Stream.AEStream_IsDraining            = AEStream_IsDraining;
    callbacks->Stream.AEStream_IsDrained             = AEStream_IsDrained;
    callbacks->Stream.AEStream_Flush                 = AEStream_Flush;
    callbacks->Stream.AEStream_GetVolume             = AEStream_GetVolume;
    callbacks->Stream.AEStream_SetVolume             = AEStream_SetVolume;
    callbacks->Stream.AEStream_GetAmplification      = AEStream_GetAmplification;
    callbacks->Stream.AEStream_SetAmplification      = AEStream_SetAmplification;
    callbacks->Stream.AEStream_GetFrameSize          = AEStream_GetFrameSize;
    callbacks->Stream.AEStream_GetChannelCount       = AEStream_GetChannelCount;
    callbacks->Stream.AEStream_GetSampleRate         = AEStream_GetSampleRate;
    callbacks->Stream.AEStream_GetDataFormat         = AEStream_GetDataFormat;
    callbacks->Stream.AEStream_GetResampleRatio      = AEStream_GetResampleRatio;
    callbacks->Stream.AEStream_SetResampleRatio      = AEStream_SetResampleRatio;
  }

unsigned int CAudioEngineCB_Stream::AEStream_GetSpace(void* addonData, AEStreamHandle* streamHandle)
{
  try
  {
    if (!addonData || !streamHandle)
      throw ADDON::WrongValueException("CAudioEngineCB_Stream - %s - invalid data (addonData='%p', streamHandle='%p')",
                                         __FUNCTION__, addonData, streamHandle);

    return static_cast<IAEStream*>(streamHandle)->GetSpace();
  }
  HANDLE_ADDON_EXCEPTION
  return 0;
}

unsigned int CAudioEngineCB_Stream::AEStream_AddData(void* addonData, AEStreamHandle* streamHandle, uint8_t* const *Data, unsigned int Offset, unsigned int Frames)
{
  try
  {
    if (!addonData || !streamHandle)
      throw ADDON::WrongValueException("CAudioEngineCB_Stream - %s - invalid data (addonData='%p', streamHandle='%p')",
                                         __FUNCTION__, addonData, streamHandle);

    return static_cast<IAEStream*>(streamHandle)->AddData(Data, Offset, Frames);
  }
  HANDLE_ADDON_EXCEPTION
  return 0;
}

double CAudioEngineCB_Stream::AEStream_GetDelay(void* addonData, AEStreamHandle* streamHandle)
{
  try
  {
    if (!addonData || !streamHandle)
      throw ADDON::WrongValueException("CAudioEngineCB_Stream - %s - invalid data (addonData='%p', streamHandle='%p')",
                                         __FUNCTION__, addonData, streamHandle);

    return static_cast<IAEStream*>(streamHandle)->GetDelay();
  }
  HANDLE_ADDON_EXCEPTION
  return 0;
}

bool CAudioEngineCB_Stream::AEStream_IsBuffering(void* addonData, AEStreamHandle* streamHandle)
{
  try
  {
    if (!addonData || !streamHandle)
      throw ADDON::WrongValueException("CAudioEngineCB_Stream - %s - invalid data (addonData='%p', streamHandle='%p')",
                                         __FUNCTION__, addonData, streamHandle);

    return static_cast<IAEStream*>(streamHandle)->IsBuffering();
  }
  HANDLE_ADDON_EXCEPTION
  return false;
}

double CAudioEngineCB_Stream::AEStream_GetCacheTime(void* addonData, AEStreamHandle* streamHandle)
{
  try
  {
    if (!addonData || !streamHandle)
      throw ADDON::WrongValueException("CAudioEngineCB_Stream - %s - invalid data (addonData='%p', streamHandle='%p')",
                                         __FUNCTION__, addonData, streamHandle);

    return static_cast<IAEStream*>(streamHandle)->GetCacheTime();
  }
  HANDLE_ADDON_EXCEPTION

  return -1.0;
}

double CAudioEngineCB_Stream::AEStream_GetCacheTotal(void* addonData, AEStreamHandle* streamHandle)
{
  try
  {
    if (!addonData || !streamHandle)
      throw ADDON::WrongValueException("CAudioEngineCB_Stream - %s - invalid data (addonData='%p', streamHandle='%p')",
                                         __FUNCTION__, addonData, streamHandle);

    return static_cast<IAEStream*>(streamHandle)->GetCacheTotal();
  }
  HANDLE_ADDON_EXCEPTION

  return -1.0;
}

void CAudioEngineCB_Stream::AEStream_Pause(void* addonData, AEStreamHandle* streamHandle)
{
  try
  {
    if (!addonData || !streamHandle)
      throw ADDON::WrongValueException("CAudioEngineCB_Stream - %s - invalid data (addonData='%p', streamHandle='%p')",
                                         __FUNCTION__, addonData, streamHandle);

    static_cast<IAEStream*>(streamHandle)->Pause();
  }
  HANDLE_ADDON_EXCEPTION
}

void CAudioEngineCB_Stream::AEStream_Resume(void* addonData, AEStreamHandle* streamHandle)
{
  try
  {
    if (!addonData || !streamHandle)
      throw ADDON::WrongValueException("CAudioEngineCB_Stream - %s - invalid data (addonData='%p', streamHandle='%p')",
                                         __FUNCTION__, addonData, streamHandle);

    static_cast<IAEStream*>(streamHandle)->Resume();
  }
  HANDLE_ADDON_EXCEPTION
}

void CAudioEngineCB_Stream::AEStream_Drain(void* addonData, AEStreamHandle* streamHandle, bool Wait)
{
  try
  {
    if (!addonData || !streamHandle)
      throw ADDON::WrongValueException("CAudioEngineCB_Stream - %s - invalid data (addonData='%p', streamHandle='%p')",
                                         __FUNCTION__, addonData, streamHandle);

    static_cast<IAEStream*>(streamHandle)->Drain(Wait);
  }
  HANDLE_ADDON_EXCEPTION
}

bool CAudioEngineCB_Stream::AEStream_IsDraining(void* addonData, AEStreamHandle* streamHandle)
{
  try
  {
    if (!addonData || !streamHandle)
      throw ADDON::WrongValueException("CAudioEngineCB_Stream - %s - invalid data (addonData='%p', streamHandle='%p')",
                                         __FUNCTION__, addonData, streamHandle);

    return static_cast<IAEStream*>(streamHandle)->IsDraining();
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

bool CAudioEngineCB_Stream::AEStream_IsDrained(void* addonData, AEStreamHandle* streamHandle)
{
  try
  {
    if (!addonData || !streamHandle)
      throw ADDON::WrongValueException("CAudioEngineCB_Stream - %s - invalid data (addonData='%p', streamHandle='%p')",
                                         __FUNCTION__, addonData, streamHandle);

    return static_cast<IAEStream*>(streamHandle)->IsDrained();
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

void CAudioEngineCB_Stream::AEStream_Flush(void* addonData, AEStreamHandle* streamHandle)
{
  try
  {
    if (!addonData || !streamHandle)
      throw ADDON::WrongValueException("CAudioEngineCB_Stream - %s - invalid data (addonData='%p', streamHandle='%p')",
                                         __FUNCTION__, addonData, streamHandle);

    static_cast<IAEStream*>(streamHandle)->Flush();
  }
  HANDLE_ADDON_EXCEPTION
}

float CAudioEngineCB_Stream::AEStream_GetVolume(void* addonData, AEStreamHandle* streamHandle)
{
  try
  {
    if (!addonData || !streamHandle)
      throw ADDON::WrongValueException("CAudioEngineCB_Stream - %s - invalid data (addonData='%p', streamHandle='%p')",
                                         __FUNCTION__, addonData, streamHandle);

    return static_cast<IAEStream*>(streamHandle)->GetVolume();
  }
  HANDLE_ADDON_EXCEPTION

  return -1.0f;
}

void CAudioEngineCB_Stream::AEStream_SetVolume(void* addonData, AEStreamHandle* streamHandle, float Volume)
{
  try
  {
    if (!addonData || !streamHandle)
      throw ADDON::WrongValueException("CAudioEngineCB_Stream - %s - invalid data (addonData='%p', streamHandle='%p')",
                                         __FUNCTION__, addonData, streamHandle);

    static_cast<IAEStream*>(streamHandle)->SetVolume(Volume);
  }
  HANDLE_ADDON_EXCEPTION
}

float CAudioEngineCB_Stream::AEStream_GetAmplification(void* addonData, AEStreamHandle* streamHandle)
{
  try
  {
    if (!addonData || !streamHandle)
      throw ADDON::WrongValueException("CAudioEngineCB_Stream - %s - invalid data (addonData='%p', streamHandle='%p')",
                                         __FUNCTION__, addonData, streamHandle);

    return static_cast<IAEStream*>(streamHandle)->GetAmplification();
  }
  HANDLE_ADDON_EXCEPTION

  return -1.0f;
}

void CAudioEngineCB_Stream::AEStream_SetAmplification(void* addonData, AEStreamHandle* streamHandle, float Amplify)
{
  try
  {
    if (!addonData || !streamHandle)
      throw ADDON::WrongValueException("CAudioEngineCB_Stream - %s - invalid data (addonData='%p', streamHandle='%p')",
                                         __FUNCTION__, addonData, streamHandle);

    static_cast<IAEStream*>(streamHandle)->SetAmplification(Amplify);
  }
  HANDLE_ADDON_EXCEPTION
}

const unsigned int CAudioEngineCB_Stream::AEStream_GetFrameSize(void* addonData, AEStreamHandle* streamHandle)
{
  try
  {
    if (!addonData || !streamHandle)
      throw ADDON::WrongValueException("CAudioEngineCB_Stream - %s - invalid data (addonData='%p', streamHandle='%p')",
                                         __FUNCTION__, addonData, streamHandle);

    return static_cast<IAEStream*>(streamHandle)->GetFrameSize();
  }
  HANDLE_ADDON_EXCEPTION

  return 0;
}

const unsigned int CAudioEngineCB_Stream::AEStream_GetChannelCount(void* addonData, AEStreamHandle* streamHandle)
{
  try
  {
    if (!addonData || !streamHandle)
      throw ADDON::WrongValueException("CAudioEngineCB_Stream - %s - invalid data (addonData='%p', streamHandle='%p')",
                                         __FUNCTION__, addonData, streamHandle);

    return static_cast<IAEStream*>(streamHandle)->GetChannelCount();
  }
  HANDLE_ADDON_EXCEPTION

  return 0;
}

const unsigned int CAudioEngineCB_Stream::AEStream_GetSampleRate(void* addonData, AEStreamHandle* streamHandle)
{
  try
  {
    if (!addonData || !streamHandle)
      throw ADDON::WrongValueException("CAudioEngineCB_Stream - %s - invalid data (addonData='%p', streamHandle='%p')",
                                         __FUNCTION__, addonData, streamHandle);

    return static_cast<IAEStream*>(streamHandle)->GetSampleRate();
  }
  HANDLE_ADDON_EXCEPTION

  return 0;
}

const AEDataFormat CAudioEngineCB_Stream::AEStream_GetDataFormat(void* addonData, AEStreamHandle* streamHandle)
{
  try
  {
    if (!addonData || !streamHandle)
      throw ADDON::WrongValueException("CAudioEngineCB_Stream - %s - invalid data (addonData='%p', streamHandle='%p')",
                                         __FUNCTION__, addonData, streamHandle);

    return static_cast<IAEStream*>(streamHandle)->GetDataFormat();
  }
  HANDLE_ADDON_EXCEPTION

  return AE_FMT_INVALID;
}

double CAudioEngineCB_Stream::AEStream_GetResampleRatio(void* addonData, AEStreamHandle* streamHandle)
{
  try
  {
    if (!addonData || !streamHandle)
      throw ADDON::WrongValueException("CAudioEngineCB_Stream - %s - invalid data (addonData='%p', streamHandle='%p')",
                                         __FUNCTION__, addonData, streamHandle);

    return static_cast<IAEStream*>(streamHandle)->GetResampleRatio();
  }
  HANDLE_ADDON_EXCEPTION

  return -1.0;
}

void CAudioEngineCB_Stream::AEStream_SetResampleRatio(void* addonData, AEStreamHandle* streamHandle, double Ratio)
{
  try
  {
    if (!addonData || !streamHandle)
      throw ADDON::WrongValueException("CAudioEngineCB_Stream - %s - invalid data (addonData='%p', streamHandle='%p')",
                                         __FUNCTION__, addonData, streamHandle);

    static_cast<IAEStream*>(streamHandle)->SetResampleRatio(Ratio);
  }
  HANDLE_ADDON_EXCEPTION
}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace AudioEngineLIB */
