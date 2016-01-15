/*
 *      Copyright (C) 2014-2015 Team KODI
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

#include "AddonCallbacksAudioEngine.h"
#include "addons/binary/ExceptionHandling.h"
#include "addons/kodi-addon-dev-kit/kodi/kodi_audioengine_types.h"
#include "cores/AudioEngine/AEFactory.h"
#include "cores/AudioEngine/DSPAddons/ActiveAEDSP.h"
#include "cores/AudioEngine/DSPAddons/ActiveAEDSPMode.h"
#include "cores/AudioEngine/Interfaces/AEStream.h"
#include "cores/AudioEngine/Utils/AEChannelData.h"
#include "utils/log.h"

using namespace ADDON;
using namespace ActiveAE;

namespace AudioEngineLIB
{
namespace V2
{
extern "C"
{

CAddonCallbacksAudioEngine::CAddonCallbacksAudioEngine(CAddon* addon)
  : ADDON::IAddonCallback(addon, AudioEngineLIB_apiLevel, AudioEngineLIB_version),
    m_callbacks(new CB_AudioEngineLib)
{
  m_callbacks->add_dsp_menu_hook        = CAddonCallbacksAudioEngine::add_dsp_menu_hook;
  m_callbacks->remove_dsp_menu_hook     = CAddonCallbacksAudioEngine::remove_dsp_menu_hook;

  m_callbacks->register_dsp_mode        = CAddonCallbacksAudioEngine::register_dsp_mode;
  m_callbacks->unregister_dsp_Mode      = CAddonCallbacksAudioEngine::unregister_dsp_Mode;

  m_callbacks->get_current_sink_format  = CAddonCallbacksAudioEngine::get_current_sink_format;

  m_callbacks->make_stream              = CAddonCallbacksAudioEngine::make_stream;
  m_callbacks->free_stream              = CAddonCallbacksAudioEngine::free_stream;

  CAudioEngineCB_Stream::Init(m_callbacks);
}

CAddonCallbacksAudioEngine::~CAddonCallbacksAudioEngine()
{
  /* delete the callback table */
  delete m_callbacks;
}

A_DLLEXPORT CB_AudioEngineLib* AudioEngineLIB_V2_register_level(void *hdl, int level)
{
  CB_AudioEngineLib *cb = nullptr;

  try
  {
    if (!hdl)
      throw ADDON::WrongValueException("CAddonCallbacksAudioEngine - %s - is called with NULL handle !!!", __FUNCTION__);

    cb = static_cast<CB_AudioEngineLib*>(CAddonCallbacks::AudioEngineLib_RegisterLevel(((AddonCB*)hdl)->addonData, level));
    if (!cb)
      throw ADDON::WrongValueException("CAddonCallbacksAudioEngine - %s - can't get callback table from Kodi !!!", __FUNCTION__);
  }
  HANDLE_ADDON_EXCEPTION

  return cb;
}

A_DLLEXPORT void AudioEngineLIB_V2_unregister(void *hdl, void* cb)
{
  try
  {
    if (!hdl || !cb)
      throw ADDON::WrongValueException("CAddonCallbacksAudioEngine - %s - invalid handler data", __FUNCTION__);

    CAddonCallbacks::AudioEngineLib_UnRegisterMe(((AddonCB*)hdl)->addonData, ((CB_AudioEngineLib*)cb));
  }
  HANDLE_ADDON_EXCEPTION
}
/*\_____________________________________________________________________________
\*/
CActiveAEDSPAddon *CAddonCallbacksAudioEngine::GetAudioDSPAddon(void *hdl)
{
  try
  {
    CAddonCallbacks* addon = static_cast<CAddonCallbacks*>(static_cast<AddonCB*>(hdl)->addonData);
    if (addon && addon->AudioEngineLib_GetHelper())
      return dynamic_cast<CActiveAEDSPAddon*>(static_cast<CAddonCallbacksAudioEngine*>(addon->AudioEngineLib_GetHelper())->m_addon);

    throw ADDON::WrongValueException("CAddonCallbacksAudioEngine - %s - invalid handler data", __FUNCTION__);
  }
  HANDLE_ADDON_EXCEPTION

  return nullptr;
}
/*\_____________________________________________________________________________
\*/
void CAddonCallbacksAudioEngine::add_dsp_menu_hook(void *hdl, AE_DSP_MENUHOOK *hook)
{
  try
  {
    CActiveAEDSPAddon *addon = GetAudioDSPAddon(hdl);
    if (!hook || !addon)
      throw ADDON::WrongValueException("CAddonCallbacksAudioEngine - %s - invalid data (addon='%p', hook='%p')", __FUNCTION__, addon, hook);

    AE_DSP_MENUHOOKS *hooks = addon->GetMenuHooks();
    if (hooks)
    {
      AE_DSP_MENUHOOK hookInt;
      hookInt.iHookId            = hook->iHookId;
      hookInt.iLocalizedStringId = hook->iLocalizedStringId;
      hookInt.category           = hook->category;
      hookInt.iRelevantModeId    = hook->iRelevantModeId;
      hookInt.bNeedPlayback      = hook->bNeedPlayback;

      /* add this new hook */
      hooks->push_back(hookInt);
    }
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonCallbacksAudioEngine::remove_dsp_menu_hook(void *hdl, AE_DSP_MENUHOOK *hook)
{
  try
  {
    CActiveAEDSPAddon *addon = GetAudioDSPAddon(hdl);
    if (!hook || !addon)
      throw ADDON::WrongValueException("CAddonCallbacksAudioEngine - %s - invalid data (addon='%p', hook='%p')", __FUNCTION__, addon, hook);

    AE_DSP_MENUHOOKS *hooks = addon->GetMenuHooks();
    if (hooks)
    {
      for (unsigned int i = 0; i < hooks->size(); ++i)
      {
        if (hooks->at(i).iHookId == hook->iHookId)
        {
          /* remove this hook */
          hooks->erase(hooks->begin()+i);
          break;
        }
      }
    }
  }
  HANDLE_ADDON_EXCEPTION
}
/*\_____________________________________________________________________________
\*/
void CAddonCallbacksAudioEngine::register_dsp_mode(void* hdl, AE_DSP_MODES::AE_DSP_MODE* mode)
{
  try
  {
    CActiveAEDSPAddon *addon = GetAudioDSPAddon(hdl);
    if (!mode || !addon)
      throw ADDON::WrongValueException("CAddonCallbacksAudioEngine - %s - invalid data (addon='%p', mode='%p')", __FUNCTION__, addon, mode);

    CActiveAEDSPMode transferMode(*mode, addon->GetID());
    int idMode = transferMode.AddUpdate();
    mode->iUniqueDBModeId = idMode;

    if (idMode > AE_DSP_INVALID_ADDON_ID)
    {
      CLog::Log(LOGDEBUG, "CAddonCallbacksAudioEngine - %s - successfull registered mode %s of %s adsp-addon", __FUNCTION__, mode->strModeName, addon->Name().c_str());
    }
    else
    {
      CLog::Log(LOGERROR, "CAddonCallbacksAudioEngine - %s - failed to register mode %s of %s adsp-addon", __FUNCTION__, mode->strModeName, addon->Name().c_str());
    }
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonCallbacksAudioEngine::unregister_dsp_Mode(void* hdl, AE_DSP_MODES::AE_DSP_MODE* mode)
{
  try
  {
    CActiveAEDSPAddon *addon = GetAudioDSPAddon(hdl);
    if (!mode || !addon)
      throw ADDON::WrongValueException("CAddonCallbacksAudioEngine - %s - invalid data (addon='%p', mode='%p')", __FUNCTION__, addon, mode);

    CActiveAEDSPMode transferMode(*mode, addon->GetID());
    transferMode.Delete();
  }
  HANDLE_ADDON_EXCEPTION
}
/*\_____________________________________________________________________________
\*/

AEStreamHandle* CAddonCallbacksAudioEngine::make_stream(void* hdl, AudioEngineFormat Format, unsigned int Options)
{
  try
  {
    AEAudioFormat format;
    format.m_dataFormat = Format.m_dataFormat;
    format.m_sampleRate = Format.m_sampleRate;
    format.m_channelLayout = Format.m_channels;
    return CAEFactory::MakeStream(format, Options);
  }
  HANDLE_ADDON_EXCEPTION

  return nullptr;
}

void CAddonCallbacksAudioEngine::free_stream(void* hdl, AEStreamHandle *StreamHandle)
{
  try
  {
    if (!StreamHandle)
      throw ADDON::WrongValueException("CAddonCallbacksAudioEngine - %s - invalid handler data", __FUNCTION__);

    CAEFactory::FreeStream((IAEStream*)StreamHandle);
  }
  HANDLE_ADDON_EXCEPTION
}

bool CAddonCallbacksAudioEngine::get_current_sink_format(void *hdl, AudioEngineFormat *sinkFormat)
{
  try
  {
    if (!sinkFormat)
      throw ADDON::WrongValueException("CAddonCallbacksAudioEngine - %s - invalid data (handle='%p', sinkFormat='%p')", __FUNCTION__, hdl, sinkFormat);

    AEAudioFormat AESinkFormat;
    if (!CAEFactory::GetEngine() || !CAEFactory::GetEngine()->GetCurrentSinkFormat(AESinkFormat))
    {
      CLog::Log(LOGERROR, "CAddonCallbacksAudioEngine - %s - failed to get current sink format from AE!", __FUNCTION__);
      return false;
    }

    sinkFormat->m_channelCount = AESinkFormat.m_channelLayout.Count();
    for (unsigned int ch = 0; ch < sinkFormat->m_channelCount; ++ch)
    {
      sinkFormat->m_channels[ch] = AESinkFormat.m_channelLayout[ch];
    }

    sinkFormat->m_dataFormat   = AESinkFormat.m_dataFormat;
    sinkFormat->m_sampleRate   = AESinkFormat.m_sampleRate;
    sinkFormat->m_frames       = AESinkFormat.m_frames;
    sinkFormat->m_frameSize    = AESinkFormat.m_frameSize;

    return true;
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace AudioEngineLIB */
