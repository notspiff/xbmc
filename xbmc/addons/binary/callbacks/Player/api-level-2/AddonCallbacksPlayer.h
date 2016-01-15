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
#include "addons/kodi-addon-dev-kit/kodi/player.api2/PlayerLib.h"

#include "addons/binary/callbacks/IAddonCallback.h"
#include "addons/binary/callbacks/AddonCallbacks.h"

#include "PlayerCB_AddonPlayList.h"
#include "PlayerCB_AddonPlayer.h"
#include "PlayerCB_InfoTagMusic.h"
#include "PlayerCB_InfoTagVideo.h"

namespace ADDON
{
  class CAddon;
};

namespace PlayerLIB
{
namespace V2
{
extern "C"
{

/*!
 * Callbacks for a Player add-on to Kodi.
 *
 * Also translates the addon's C structures to Kodi's C++ structures.
 */
class CAddonCallbacksPlayer : public ADDON::IAddonCallback
{
public:
  CAddonCallbacksPlayer(ADDON::CAddon* addon);
  virtual ~CAddonCallbacksPlayer(void);

  static void FreeString(void* hdl, char* str);

  static int APILevel() { return PlayerLIB_apiLevel; }
  static std::string Version() { return PlayerLIB_version; }

  /*!
   * @return The callback table.
   */
  CB_PlayerLib *GetCallbacks() { return m_callbacks; }
  /*\___________________________________________________________________________
  \*/

private:
  CB_PlayerLib    *m_callbacks; /*!< callback addresses */
};

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace PlayerLIB */
