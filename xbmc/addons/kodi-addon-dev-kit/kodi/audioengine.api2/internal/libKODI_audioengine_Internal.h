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

#include <memory>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#include "libKODI_audioengine_AEStreamHead.h"

#define IMPLEMENT_KODI_AUDIOENGINE_LIBRARY                                     \
namespace AudioEngineLIB                                                       \
{                                                                              \
namespace V2                                                                   \
{                                                                              \
  std::shared_ptr<CAELib_Internal> CAELib::g_libKODI_Internal;\
}; /* namespace V2 */                                                          \
}; /* namespace AudioEngineLIB */

#define KODI_AUDIOENGINE_LIBRARY                                               \
  public:                                                                      \
    static std::shared_ptr<CAELib_Internal> g_libKODI_Internal;       \
  public:                                                                      \
    CAELib() { }                                                      \
    virtual ~CAELib() { }

namespace AudioEngineLIB
{
namespace V2
{

  class CAELib_Stream;

  typedef void _add_dsp_menu_hook(void *hdl, AE_DSP_MENUHOOK *hook);
  typedef void _remove_dsp_menu_hook(void *hdl, AE_DSP_MENUHOOK *hook);

  typedef void _register_dsp_mode(void *hdl, AE_DSP_MODES::AE_DSP_MODE *mode);
  typedef void _unregister_dsp_Mode(void *hdl, AE_DSP_MODES::AE_DSP_MODE *mode);

  typedef bool _get_current_sink_format(void* hdl, AudioEngineFormat* sinkFormat);

  typedef AEStreamHandle* _make_stream(void* hdl, AudioEngineFormat Format, unsigned int Options);
  typedef void _free_stream(void* hdl, AEStreamHandle* StreamHandle);

  typedef struct CB_AudioEngineLib
  {
    _add_dsp_menu_hook*             add_dsp_menu_hook;
    _remove_dsp_menu_hook*          remove_dsp_menu_hook;

    _register_dsp_mode*             register_dsp_mode;
    _unregister_dsp_Mode*           unregister_dsp_Mode;

    _get_current_sink_format*       get_current_sink_format;

    _make_stream*                   make_stream;
    _free_stream*                   free_stream;
    CB_AudioEngineLib_Stream        Stream;

  } CB_AudioEngineLib;

  typedef CB_AudioEngineLib*  _register_level(void *HANDLE, int level);
  typedef void                _unregister(void* HANDLE, void* CB);

  class CAELib_Internal
  {
  public:
    CAELib_Internal()
      : m_libKODI_audioengine(nullptr),
        m_Handle(nullptr) { }

    virtual ~CAELib_Internal()
    {
      UnRegisterMe();
    }

    bool RegisterMe(void *Handle)
    {
      m_Handle = Handle;

      m_libKODI_audioengine = dlopen(nullptr, RTLD_LAZY);
      if (m_libKODI_audioengine == nullptr)
      {
        fprintf(stderr, "Unable to load %s\n", dlerror());
        return false;
      }

      KODI_register = (_register_level*)
        dlsym(m_libKODI_audioengine, "AudioEngineLIB_V2_register_level");
      if (KODI_register == nullptr)
      {
        fprintf(stderr, "Unable to assign function %s\n", dlerror());
        return false;
      }

      KODI_unregister = (_unregister*)
        dlsym(m_libKODI_audioengine, "AudioEngineLIB_V2_unregister");
      if (KODI_unregister == nullptr)
      {
        fprintf(stderr, "Unable to assign function %s\n", dlerror());
        return false;
      }

      m_Callbacks = KODI_register(m_Handle, 2);
      return m_Callbacks != nullptr;
    }

    void UnRegisterMe()
    {
      if (m_libKODI_audioengine)
      {
        KODI_unregister(m_Handle, m_Callbacks);
        dlclose(m_libKODI_audioengine);
        m_libKODI_audioengine = nullptr;
      }
    }
    /*\_________________________________________________________________________
    \*/
    void AddDSPMenuHook(AE_DSP_MENUHOOK* hook)
    {
      return m_Callbacks->add_dsp_menu_hook(m_Handle, hook);
    }

    void RemoveDSPMenuHook(AE_DSP_MENUHOOK* hook)
    {
      return m_Callbacks->remove_dsp_menu_hook(m_Handle, hook);
    }
    /*\_________________________________________________________________________
    \*/
    void RegisterDSPMode(AE_DSP_MODES::AE_DSP_MODE* mode)
    {
      return m_Callbacks->register_dsp_mode(m_Handle, mode);
    }

    void UnregisterDSPMode(AE_DSP_MODES::AE_DSP_MODE* mode)
    {
      return m_Callbacks->unregister_dsp_Mode(m_Handle, mode);
    }
    /*\_________________________________________________________________________
    \*/
    bool GetCurrentSinkFormat(AudioEngineFormat &SinkFormat)
    {
      return m_Callbacks->get_current_sink_format(m_Handle, &SinkFormat);
    }
    /*\_________________________________________________________________________
    \*/
  protected:
    _register_level*  KODI_register;
    _unregister*      KODI_unregister;

  private:
    void*               m_libKODI_audioengine;
    void*               m_Handle;
    CB_AudioEngineLib*  m_Callbacks;
    struct cb_array
    {
      const char* libPath;
    };
  };

}; /* namespace V2 */
}; /* namespace AudioEngineLIB */
