/*
 *      Copyright (C) 2012-2013 Team XBMC
 *      http://xbmc.org
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
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "AddonCallbacksAddon.h"

#include "Application.h"
#include "addons/Addon.h"
#include "addons/binary/ExceptionHandling.h"
#include "utils/log.h"

using namespace ADDON;

namespace AddOnLIB
{
namespace V2
{
extern "C"
{

CAddonCallbacksAddon::CAddonCallbacksAddon(CAddon* addon)
  : ADDON::IAddonCallback(addon, AddOnLIB_apiLevel, AddOnLIB_version),
    m_callbacks(new CB_AddOnLib)
{
  CAddonCB_Audio::Init(m_callbacks);
  CAddonCB_Codec::Init(m_callbacks);
  CAddonCB_Directory::Init(m_callbacks);
  CAddonCB_File::Init(m_callbacks);
  CAddonCB_General::Init(m_callbacks);
  CAddonCB_Network::Init(m_callbacks);
}

CAddonCallbacksAddon::~CAddonCallbacksAddon()
{
  delete m_callbacks;
}

A_DLLEXPORT CB_AddOnLib* ADDONLIB_V2_register_level(void *hdl, int level)
{
  CB_AddOnLib *cb = nullptr;

  try
  {
    if (!hdl)
      throw ADDON::WrongValueException("CAddonCallbacksAddon - %s - invalid handler data", __FUNCTION__);

    cb = static_cast<CB_AddOnLib*>(CAddonCallbacks::AddOnLib_RegisterLevel(((AddonCB*)hdl)->addonData, level));
    if (!cb)
      throw ADDON::WrongValueException("CAddonCallbacksAddon - %s - can't get callback table from Kodi !!!", __FUNCTION__);
  }
  HANDLE_ADDON_EXCEPTION

  return cb;
}

A_DLLEXPORT void ADDONLIB_V2_unregister(void *hdl, void* cb)
{
  try
  {
    if (!hdl || !cb)
      throw ADDON::WrongValueException("CAddonCallbacksAddon - %s - invalid handler data", __FUNCTION__);

    CAddonCallbacks::AddOnLib_UnRegisterMe(((AddonCB*)hdl)->addonData, ((CB_AddOnLib*)cb));
  }
  HANDLE_ADDON_EXCEPTION
}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace AddOnLIB */
