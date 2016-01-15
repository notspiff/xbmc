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

namespace PVRLIB
{
namespace V2
{
  inline bool CPVRLib::RegisterMe(void *handle)
  {
    g_libKODI_Internal = std::shared_ptr<CPVRLib_Internal>(new CPVRLib_Internal);
    return g_libKODI_Internal->RegisterMe(handle);
  }

  inline void CPVRLib::UnRegisterMe()
  {
    if (g_libKODI_Internal)
    {
      g_libKODI_Internal->UnRegisterMe();
      g_libKODI_Internal.reset();
    }
  }
  /*\___________________________________________________________________________
  \*/
  inline void CPVRLib::AddMenuHook(PVR_MENUHOOK* hook)
  {
    return CPVRLib::g_libKODI_Internal->AddMenuHook(hook);
  }

  inline void CPVRLib::Recording(const char* strRecordingName, const char* strFileName, bool bOn)
  {
    return CPVRLib::g_libKODI_Internal->Recording(strRecordingName, strFileName, bOn);
  }
  /*\___________________________________________________________________________
  \*/
  inline void CPVRLib_Transfer::EpgEntry(const ADDON_HANDLE handle, const EPG_TAG* entry)
  {
    return CPVRLib::g_libKODI_Internal->TransferEpgEntry(handle, entry);
  }

  inline void CPVRLib_Transfer::ChannelEntry(const ADDON_HANDLE handle, const PVR_CHANNEL* entry)
  {
    return CPVRLib::g_libKODI_Internal->TransferChannelEntry(handle, entry);
  }

  inline void CPVRLib_Transfer::TimerEntry(const ADDON_HANDLE handle, const PVR_TIMER* entry)
  {
    return CPVRLib::g_libKODI_Internal->TransferTimerEntry(handle, entry);
  }

  inline void CPVRLib_Transfer::RecordingEntry(const ADDON_HANDLE handle, const PVR_RECORDING* entry)
  {
    return CPVRLib::g_libKODI_Internal->TransferRecordingEntry(handle, entry);
  }

  inline void CPVRLib_Transfer::ChannelGroup(const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP* entry)
  {
    return CPVRLib::g_libKODI_Internal->TransferChannelGroup(handle, entry);
  }

  inline void CPVRLib_Transfer::ChannelGroupMember(const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP_MEMBER* entry)
  {
    return CPVRLib::g_libKODI_Internal->TransferChannelGroupMember(handle, entry);
  }
  /*\___________________________________________________________________________
  \*/
  inline void CPVRLib_Trigger::TimerUpdate(void)
  {
    return CPVRLib::g_libKODI_Internal->TriggerTimerUpdate();
  }

  inline void CPVRLib_Trigger::RecordingUpdate(void)
  {
    return CPVRLib::g_libKODI_Internal->TriggerRecordingUpdate();
  }

  inline void CPVRLib_Trigger::ChannelUpdate(void)
  {
    return CPVRLib::g_libKODI_Internal->TriggerChannelUpdate();
  }

  inline void CPVRLib_Trigger::EpgUpdate(unsigned int iChannelUid)
  {
    return CPVRLib::g_libKODI_Internal->TriggerEpgUpdate(iChannelUid);
  }

  inline void CPVRLib_Trigger::ChannelGroupsUpdate(void)
  {
    return CPVRLib::g_libKODI_Internal->TriggerChannelGroupsUpdate();
  }

}; /* V2 */
}; /* PVRLIB */
