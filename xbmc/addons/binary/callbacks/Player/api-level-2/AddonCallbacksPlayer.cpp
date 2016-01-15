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

#include "AddonCallbacksPlayer.h"

#include "Application.h"
#include "addons/binary/ExceptionHandling.h"
#include "utils/log.h"
#include "utils/StringUtils.h"

using namespace ADDON;

namespace PlayerLIB
{
namespace V2
{
extern "C"
{

CAddonCallbacksPlayer::CAddonCallbacksPlayer(CAddon* addon)
  : ADDON::IAddonCallback(addon, PlayerLIB_apiLevel, PlayerLIB_version),
    m_callbacks(new CB_PlayerLib)
{
  /* write Kodi Player specific add-on function addresses to callback table */
  m_callbacks->FreeString = FreeString;

  CPlayerCB_AddonPlayList::Init(m_callbacks);
  CPlayerCB_AddonPlayer::Init(m_callbacks);
  CPlayerCB_InfoTagMusic::Init(m_callbacks);
  CPlayerCB_InfoTagVideo::Init(m_callbacks);
}

CAddonCallbacksPlayer::~CAddonCallbacksPlayer()
{
  /* delete the callback table */
  delete m_callbacks;
}

void CAddonCallbacksPlayer::FreeString(void* hdl, char* str)
{
  try
  {
    if (!hdl || !str)
      throw ADDON::WrongValueException("CAddonCallbacksPlayer - %s - invalid data (handle='%p', str='%p')",
                                        __FUNCTION__, hdl, str);

    free(str);
  }
  HANDLE_ADDON_EXCEPTION
}

/*\_____________________________________________________________________________
\*/
A_DLLEXPORT CB_PlayerLib* PlayerLIB_V2_register_level(void *hdl, int level)
{
  CB_PlayerLib *cb = nullptr;

  try
  {
    if (!hdl)
      throw ADDON::WrongValueException("CAddonCallbacksPlayer - %s - is called with NULL handle !!!", __FUNCTION__);

    cb = static_cast<CB_PlayerLib*>(CAddonCallbacks::PlayerLib_RegisterLevel(((AddonCB*)hdl)->addonData, level));
    if (!cb)
      throw ADDON::WrongValueException("CAddonCallbacksPlayer - %s - can't get callback table from Kodi !!!", __FUNCTION__);
  }
  HANDLE_ADDON_EXCEPTION

  return cb;
}

A_DLLEXPORT void PlayerLIB_V2_unregister(void *hdl, void* cb)
{
  try
  {
    if (!hdl || !cb)
      throw ADDON::WrongValueException("CAddonCallbacksPlayer - %s - invalid handler data", __FUNCTION__);

    CAddonCallbacks::PlayerLib_UnRegisterMe(((AddonCB*)hdl)->addonData, ((CB_PlayerLib*)cb));
  }
  HANDLE_ADDON_EXCEPTION
}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace PlayerLIB */
