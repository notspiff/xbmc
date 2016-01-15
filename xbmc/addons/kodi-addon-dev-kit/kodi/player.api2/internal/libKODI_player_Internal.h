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

#include "kodi/addon.api2/AddonLib.h"

#include "../definations.h"
#include "libKODI_player_AddonPlayListHead.h"
#include "libKODI_player_AddonPlayerHead.h"
#include "libKODI_player_InfoTagMusicHead.h"
#include "libKODI_player_InfoTagVideoHead.h"

#define IMPLEMENT_KODI_PLAYER_LIBRARY                                          \
namespace PlayerLIB                                                            \
{                                                                              \
namespace V2                                                                   \
{                                                                              \
  std::shared_ptr<CPlayerLib_Internal> CPlayerLib::g_libKODI_Internal;         \
}; /* namespace V2 */                                                          \
}; /* namespace PlayerLIB */

#define KODI_PLAYER_LIBRARY                                                    \
  public:                                                                      \
    static std::shared_ptr<CPlayerLib_Internal> g_libKODI_Internal;            \
  public:                                                                      \
    CPlayerLib() { }                                                           \
    virtual ~CPlayerLib() { }

namespace PlayerLIB
{
namespace V2
{
extern "C"
{

  typedef void CB_PlayerLib_FreeString(void* hdl, char* str);

  typedef struct CB_PlayerLib
  {
    CB_PlayerLib_FreeString*          FreeString;
    CB_PlayerLib_AddonPlayer          AddonPlayer;
    CB_PlayerLib_AddonPlayList        AddonPlayList;
    CB_PlayerLib_AddonInfoTagMusic    AddonInfoTagMusic;
    CB_PlayerLib_AddonInfoTagVideo    AddonInfoTagVideo;
  } CB_PlayerLib;

  typedef CB_PlayerLib* _register_level(void *HANDLE, int level);
  typedef void _unregister(void* HANDLE, void* CB);

  class CPlayerLib_Internal
  {
  public:
    CPlayerLib_Internal()
      : m_libKODI_player(nullptr),
        m_Handle(nullptr) { }

    virtual ~CPlayerLib_Internal()
    {
      UnRegisterMe();
    }

    bool RegisterMe(void *Handle)
    {
      m_Handle = Handle;

      m_libKODI_player = dlopen(nullptr, RTLD_LAZY);
      if (m_libKODI_player == nullptr)
      {
        fprintf(stderr, "Unable to load %s\n", dlerror());
        return false;
      }

      KODI_register = (_register_level*)
        dlsym(m_libKODI_player, "PlayerLIB_V2_register_level");
      if (KODI_register == nullptr)
      {
        fprintf(stderr, "Unable to assign function %s\n", dlerror());
        return false;
      }

      KODI_unregister = (_unregister*)
        dlsym(m_libKODI_player, "PlayerLIB_V2_unregister");
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
      if (m_libKODI_player)
      {
        KODI_unregister(m_Handle, m_Callbacks);
        dlclose(m_libKODI_player);
        m_libKODI_player = nullptr;
      }
    }

  protected:
    _register_level*  KODI_register;
    _unregister*      KODI_unregister;

  private:
    friend class CPlayerLib_Player;
    friend class CPlayerLib_PlayList;

    void*         m_libKODI_player;
    void*         m_Handle;
    CB_PlayerLib*    m_Callbacks;
    struct cb_array
    {
      const char* libPath;
    };
  };

}; /* extern "C" */
}; /* V2 */
}; /* PlayerLIB */
