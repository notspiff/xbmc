#pragma once
/*
 *      Copyright (C) 2012-2015 Team KODI
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

#include "system.h"

#include "addons/binary/callbacks/IAddonCallback.h"
#include "addons/binary/callbacks/AddonCallbacks.h"
#include "addons/kodi-addon-dev-kit/kodi/xbmc_pvr_types.h"
#include "addons/kodi-addon-dev-kit/kodi/pvr.api2/PVRLib.h"

namespace PVR
{
  class CPVRClient;
}

namespace ADDON
{
  class CAddon;
};

namespace PVRLIB
{
namespace V2
{
extern "C"
{

  /*!
   * Callbacks for a PVR add-on to Kodi.
   *
   * Also translates the addon's C structures to Kodi's C++ structures.
   */
  class CAddonCallbacksPVR : public ADDON::IAddonCallback
  {
  public:
    CAddonCallbacksPVR(ADDON::CAddon* addon);
    virtual ~CAddonCallbacksPVR(void);

    static int APILevel() { return PVRLIB_apiLevel; }
    static std::string Version() { return PVRLIB_version; }

    /*!
     * @return The callback table.
     */
    CB_PVRLib *GetCallbacks() { return m_callbacks; }
    /*\___________________________________________________________________________
    \*/
    static void add_menu_hook(void* hdl, PVR_MENUHOOK* hook);
    static void recording(void* hdl, const char* strName, const char* strFileName, bool bOnOff);
    /*\___________________________________________________________________________
    \*/
    static void transfer_epg_entry(void *hdl, const ADDON_HANDLE handle, const EPG_TAG* epgentry);
    static void transfer_channel_entry(void *hdl, const ADDON_HANDLE handle, const PVR_CHANNEL* channel);
    static void transfer_channel_group(void *hdl, const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP* group);
    static void transfer_channel_group_member(void *hdl, const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP_MEMBER* member);
    static void transfer_timer_entry(void *hdl, const ADDON_HANDLE handle, const PVR_TIMER* timer);
    static void transfer_recording_entry(void *hdl, const ADDON_HANDLE handle, const PVR_RECORDING* recording);
    /*\___________________________________________________________________________
    \*/
    static void trigger_channel_update(void* hdl);
    static void trigger_channel_groups_update(void* hdl);
    static void trigger_timer_update(void* hdl);
    static void trigger_recording_update(void* hdl);
    static void trigger_epg_update(void* hdl, unsigned int iChannelUid);

  private:
    static PVR::CPVRClient* GetPVRClient(void* hdl);

    CB_PVRLib    *m_callbacks; /*!< callback addresses */
  };

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace PVRLIB */
