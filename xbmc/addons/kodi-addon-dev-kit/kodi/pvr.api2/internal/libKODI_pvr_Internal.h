#pragma once
/*
 *      Copyright (C) 2015 Team KODI
 *      Copyright (C) 2005-2013 Team XBMC
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

#include "kodi/xbmc_pvr_types.h"
#include "kodi/addon.api2/AddonLib.h"

#define IMPLEMENT_KODI_PVR_LIBRARY                                             \
namespace PVRLIB                                                               \
{                                                                              \
namespace V2                                                                   \
{                                                                              \
  std::shared_ptr<CPVRLib_Internal> CPVRLib::g_libKODI_Internal;               \
}; /* namespace V2 */                                                          \
}; /* namespace PVRLIB */

#define KODI_PVR_LIBRARY                                                       \
  public:                                                                      \
    static std::shared_ptr<CPVRLib_Internal> g_libKODI_Internal;               \
  public:                                                                      \
    CPVRLib() { }                                                              \
    virtual ~CPVRLib() { }

namespace PVRLIB
{
namespace V2
{

  typedef void _add_menu_hook(void* addonData, PVR_MENUHOOK* hook);
  typedef void _recording(void* addonData, const char* strName, const char* strFileName, bool bOnOff);

  typedef void _transfer_epg_entry(void *addonData, const ADDON_HANDLE handle, const EPG_TAG *epgentry);
  typedef void _transfer_channel_entry(void *addonData, const ADDON_HANDLE handle, const PVR_CHANNEL *chan);
  typedef void _transfer_channel_group(void* addonData, const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP*);
  typedef void _transfer_channel_group_member(void* addonData, const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP_MEMBER*);
  typedef void _transfer_timer_entry(void *addonData, const ADDON_HANDLE handle, const PVR_TIMER *timer);
  typedef void _transfer_recording_entry(void *addonData, const ADDON_HANDLE handle, const PVR_RECORDING *recording);

  typedef void _trigger_channel_update(void* HANDLE);
  typedef void _trigger_channel_groups_update(void* HANDLE);
  typedef void _trigger_timer_update(void* HANDLE);
  typedef void _trigger_recording_update(void* HANDLE);
  typedef void _trigger_epg_update(void* HANDLE, unsigned int iChannelUid);

  typedef struct CB_PVRLib
  {
    _add_menu_hook*                 add_menu_hook;
    _recording*                     recording;

    _transfer_epg_entry*            transfer_epg_entry;
    _transfer_channel_entry*        transfer_channel_entry;
    _transfer_channel_group*        transfer_channel_group;
    _transfer_channel_group_member* transfer_channel_group_member;
    _transfer_timer_entry*          transfer_timer_entry;
    _transfer_recording_entry*      transfer_recording_entry;

    _trigger_channel_update*        trigger_channel_update;
    _trigger_channel_groups_update* trigger_channel_groups_update;
    _trigger_timer_update*          trigger_timer_update;
    _trigger_recording_update*      trigger_recording_update;
    _trigger_epg_update*            trigger_epg_update;
  } CB_PVRLib;

  typedef CB_PVRLib* _register_level(void *HANDLE, int level);
  typedef void _unregister(void* HANDLE, void* CB);

  class CPVRLib_Internal
  {
  public:
    CPVRLib_Internal()
      : m_libKODI_pvr(nullptr),
        m_Handle(nullptr) { }

    virtual ~CPVRLib_Internal()
    {
      UnRegisterMe();
    }

    bool RegisterMe(void *Handle)
    {
      m_Handle = Handle;

      m_libKODI_pvr = dlopen(nullptr, RTLD_LAZY);
      if (m_libKODI_pvr == nullptr)
      {
        fprintf(stderr, "Unable to load %s\n", dlerror());
        return false;
      }

      KODI_register = (_register_level*)
        dlsym(m_libKODI_pvr, "PVRLIB_V2_register_level");
      if (KODI_register == nullptr)
      {
        fprintf(stderr, "Unable to assign function %s\n", dlerror());
        return false;
      }

      KODI_unregister = (_unregister*)
        dlsym(m_libKODI_pvr, "PVRLIB_V2_unregister");
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
      if (m_libKODI_pvr)
      {
        KODI_unregister(m_Handle, m_Callbacks);
        dlclose(m_libKODI_pvr);
        m_libKODI_pvr = nullptr;
      }
    }
    /*\_________________________________________________________________________
    \*/
    void AddMenuHook(PVR_MENUHOOK* hook)
    {
      return m_Callbacks->add_menu_hook(m_Handle, hook);
    }

    void Recording(const std::string& strRecordingName, const std::string& strFileName, bool bOn)
    {
      return m_Callbacks->recording(m_Handle, strRecordingName.c_str(), strFileName.c_str(), bOn);
    }
    /*\_________________________________________________________________________
    \*/
    void TransferEpgEntry(const ADDON_HANDLE handle, const EPG_TAG* entry)
    {
      return m_Callbacks->transfer_epg_entry(m_Handle, handle, entry);
    }

    void TransferChannelEntry(const ADDON_HANDLE handle, const PVR_CHANNEL* entry)
    {
      return m_Callbacks->transfer_channel_entry(m_Handle, handle, entry);
    }

    void TransferTimerEntry(const ADDON_HANDLE handle, const PVR_TIMER* entry)
    {
      return m_Callbacks->transfer_timer_entry(m_Handle, handle, entry);
    }

    void TransferRecordingEntry(const ADDON_HANDLE handle, const PVR_RECORDING* entry)
    {
      return m_Callbacks->transfer_recording_entry(m_Handle, handle, entry);
    }

    void TransferChannelGroup(const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP* entry)
    {
      return m_Callbacks->transfer_channel_group(m_Handle, handle, entry);
    }

    void TransferChannelGroupMember(const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP_MEMBER* entry)
    {
      return m_Callbacks->transfer_channel_group_member(m_Handle, handle, entry);
    }
    /*\_________________________________________________________________________
    \*/
    void TriggerTimerUpdate(void)
    {
      return m_Callbacks->trigger_timer_update(m_Handle);
    }

    void TriggerRecordingUpdate(void)
    {
      return m_Callbacks->trigger_recording_update(m_Handle);
    }

    void TriggerChannelUpdate(void)
    {
      return m_Callbacks->trigger_channel_update(m_Handle);
    }

    void TriggerEpgUpdate(unsigned int iChannelUid)
    {
      return m_Callbacks->trigger_epg_update(m_Handle, iChannelUid);
    }

    void TriggerChannelGroupsUpdate(void)
    {
      return m_Callbacks->trigger_channel_groups_update(m_Handle);
    }

  protected:
    _register_level*  KODI_register;
    _unregister*      KODI_unregister;

  private:
    void*         m_libKODI_pvr;
    void*         m_Handle;
    CB_PVRLib*    m_Callbacks;
    struct cb_array
    {
      const char* libPath;
    };
  };

}; /* V2 */
}; /* PVRLIB */
