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

#include "system.h"
#include "addons/kodi-addon-dev-kit/kodi/addon.api2/AddonLib.h"

#include "AddonCB_Audio.h"
#include "AddonCB_Codec.h"
#include "AddonCB_Directory.h"
#include "AddonCB_File.h"
#include "AddonCB_General.h"
#include "AddonCB_Network.h"

#include "addons/binary/callbacks/IAddonCallback.h"
#include "addons/binary/callbacks/AddonCallbacks.h"

namespace ADDON
{
  class CAddon;
};

extern "C"
{
namespace AddOnLIB
{
namespace V2
{

  class CAddonCallbacksAddon
    : public ADDON::IAddonCallback,
      private CAddonCB_Audio,
      private CAddonCB_Codec,
      private CAddonCB_Directory,
      private CAddonCB_File,
      private CAddonCB_General,
      private CAddonCB_Network
  {
  public:
    CAddonCallbacksAddon(ADDON::CAddon* addon);
    virtual ~CAddonCallbacksAddon();

    static int APILevel() { return AddOnLIB_apiLevel; }
    static std::string Version() { return AddOnLIB_version; }

    /*!
     * @return The callback table.
     */
    CB_AddOnLib *GetCallbacks() { return m_callbacks; }

  private:
    CB_AddOnLib  *m_callbacks; /*!< callback addresses */
  };

}; /* namespace V2 */
}; /* namespace AddOnLIB */
}; /* extern "C" */
