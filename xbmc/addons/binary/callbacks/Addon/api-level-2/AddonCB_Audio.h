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

#include "PlatformDefs.h" // for __stat64, ssize_t
#include "addons/kodi-addon-dev-kit/kodi/addon.api2/AddonLib.h"
#include "cores/AudioEngine/Utils/AEChannelData.h"

extern "C"
{
namespace AddOnLIB
{
namespace V2
{

  class CAddonCB_Audio
  {
  public:
    CAddonCB_Audio();

    void Init(CB_AddOnLib *callbacks);

    static IAESound* soundplay_get_handle(
        void*                     hdl,
        const char*               filename);

    static void soundplay_release_handle(
        void*                     hdl,
        IAESound*                 sndHandle);

    static void soundplay_play(
        void*                     hdl,
        IAESound*                 sndHandle,
        bool                      waitUntilEnd);

    static void soundplay_stop(
        void*                     hdl,
        IAESound*                 sndHandle);

    static bool soundplay_is_playing(
        void*                     hdl,
        IAESound*                 sndHandle);

    static void soundplay_set_channel(
        void*                     hdl,
        IAESound*                 sndHandle,
        audio_channel           channel);

    static audio_channel soundplay_get_channel(
        void*                     hdl,
        IAESound*                 sndHandle);

    static void soundplay_set_volume(
        void*                     hdl,
        IAESound*                 sndHandle,
        float                     volume);

    static float soundplay_get_volume(
        void*                     hdl,
        IAESound*                 sndHandle);

  private:
    static enum AEChannel GetKODIChannel(audio_channel channel);
    static audio_channel GetAddonChannel(enum AEChannel channel);
  };

}; /* namespace V2 */
}; /* namespace AddOnLIB */
}; /* extern "C" */
