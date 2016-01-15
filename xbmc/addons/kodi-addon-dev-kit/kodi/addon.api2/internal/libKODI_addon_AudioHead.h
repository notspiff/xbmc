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

class IAESound;

namespace AddOnLIB
{
namespace V2
{

  typedef IAESound* _soundplay_get_handle(void* HANDLE, const char *filename);
  typedef void _soundplay_release_handle(void* HANDLE, IAESound* sndHandle);
  typedef void _soundplay_play(void* HANDLE, IAESound* sndHandle, bool waitUntilEnd);
  typedef void _soundplay_stop(void* HANDLE, IAESound* sndHandle);
  typedef bool _soundplay_is_playing(void* HANDLE, IAESound* sndHandle);
  typedef void _soundplay_set_channel(void* HANDLE, IAESound* sndHandle, audio_channel channel);
  typedef audio_channel _soundplay_get_channel(void* HANDLE, IAESound* sndHandle);
  typedef void _soundplay_set_volume(void* HANDLE, IAESound* sndHandle, float volume);
  typedef float _soundplay_get_volume(void* HANDLE, IAESound* sndHandle);

  typedef struct CB_AddonLib_Audio
  {
    _soundplay_get_handle*      soundplay_get_handle;
    _soundplay_release_handle*  soundplay_release_handle;
    _soundplay_play*            soundplay_play;
    _soundplay_stop*            soundplay_stop;
    _soundplay_is_playing*      soundplay_is_playing;
    _soundplay_set_channel*     soundplay_set_channel;
    _soundplay_get_channel*     soundplay_get_channel;
    _soundplay_set_volume*      soundplay_set_volume;
    _soundplay_get_volume*      soundplay_get_volume;
  } CB_AddonLib_Audio;

#define IMPL_ADDONSOUNDPLAY                                                    \
  private:                                                                     \
    IAESound*     m_PlayHandle;                                                \
    void*         m_Handle;                                                    \
    CB_AddOnLib*  m_Callbacks;

}; /* namespace V2 */
}; /* namespace AddOnLIB */
