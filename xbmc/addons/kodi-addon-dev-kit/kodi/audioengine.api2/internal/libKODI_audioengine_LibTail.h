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

  inline bool CAELib::RegisterMe(void *handle)
  {
    g_libKODI_Internal = std::shared_ptr<CAELib_Internal>(new CAELib_Internal);
    return g_libKODI_Internal->RegisterMe(handle);
  }

  inline void CAELib::UnRegisterMe()
  {
    if (g_libKODI_Internal)
    {
      g_libKODI_Internal->UnRegisterMe();
      g_libKODI_Internal.reset();
    }
  }

  inline void CAELib::AddDSPMenuHook(AE_DSP_MENUHOOK* hook)
  {
    CAELib::g_libKODI_Internal->AddDSPMenuHook(hook);
  }

  inline void CAELib::RemoveDSPMenuHook(AE_DSP_MENUHOOK* hook)
  {
    CAELib::g_libKODI_Internal->RemoveDSPMenuHook(hook);
  }

  inline void CAELib::RegisterDSPMode(AE_DSP_MODES::AE_DSP_MODE* mode)
  {
    CAELib::g_libKODI_Internal->RegisterDSPMode(mode);
  }

  inline void CAELib::UnregisterDSPMode(AE_DSP_MODES::AE_DSP_MODE* mode)
  {
    CAELib::g_libKODI_Internal->UnregisterDSPMode(mode);
  }

}; /* namespace V2 */
}; /* namespace AudioEngineLIB */
