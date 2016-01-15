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

namespace AddOnLIB
{
namespace V2
{
  inline CAddonLib_SoundPlay::CAddonLib_SoundPlay(const std::string& filename)
   : m_PlayHandle(nullptr),
     m_Handle(CAddonLib::g_libKODI_Internal->m_Handle),
     m_Callbacks(CAddonLib::g_libKODI_Internal->m_Callbacks)
  {
    if (!m_Handle || !m_Callbacks)
      fprintf(stderr, "libKODI_addon-ERROR: CAddonLib_SoundPlay is called with NULL handle !!!\n");
    else
    {
      m_PlayHandle = m_Callbacks->Audio.soundplay_get_handle(m_Handle, filename.c_str());
      if (!m_PlayHandle)
        fprintf(stderr, "libKODI_addon-ERROR: CAddonLib_SoundPlay can't get callback table from KODI !!!\n");
    }
  }

  inline CAddonLib_SoundPlay::~CAddonLib_SoundPlay()
  {
    if (m_PlayHandle)
      m_Callbacks->Audio.soundplay_release_handle(m_Handle, m_PlayHandle);
  }

  inline void CAddonLib_SoundPlay::Play(bool waitUntilEnd)
  {
    if (m_PlayHandle)
      m_Callbacks->Audio.soundplay_play(m_Handle, m_PlayHandle, waitUntilEnd);
  }

  inline void CAddonLib_SoundPlay::Stop()
  {
    if (m_PlayHandle)
      m_Callbacks->Audio.soundplay_stop(m_Handle, m_PlayHandle);
  }

  inline bool CAddonLib_SoundPlay::IsPlaying()
  {
    if (!m_PlayHandle)
      return false;
    return m_Callbacks->Audio.soundplay_is_playing(m_Handle, m_PlayHandle);
  }

  inline void CAddonLib_SoundPlay::SetChannel(audio_channel channel)
  {
    if (m_PlayHandle)
      m_Callbacks->Audio.soundplay_set_channel(m_Handle, m_PlayHandle, channel);
  }

  inline audio_channel CAddonLib_SoundPlay::GetChannel()
  {
    if (!m_PlayHandle)
      return AUDIO_CH_INVALID;
    return m_Callbacks->Audio.soundplay_get_channel(m_Handle, m_PlayHandle);
  }

  inline void CAddonLib_SoundPlay::SetVolume(float volume)
  {
    if (m_PlayHandle)
      m_Callbacks->Audio.soundplay_set_volume(m_Handle, m_PlayHandle, volume);
  }

  inline float CAddonLib_SoundPlay::GetVolume()
  {
    if (!m_PlayHandle)
      return 0.0f;
    return m_Callbacks->Audio.soundplay_get_volume(m_Handle, m_PlayHandle);
  }

}; /* namespace V2 */
}; /* namespace AddOnLIB */
