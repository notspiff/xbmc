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

namespace PlayerLIB
{
namespace V2
{
extern "C"
{

  inline CPlayerLib_InfoTagMusic::CPlayerLib_InfoTagMusic(CPlayerLib_Player* player)
   : m_Handle((ADDON::AddonCB*)CGUILib::g_libKODI_Internal->m_Handle),
     m_cb(CGUILib::g_libKODI_Internal->m_Callbacks)
  {
    if (!player || !player->m_ControlHandle)
    {
      return;
    }

    AddonInfoTagMusic infoTag;
    if (m_cb->AddonInfoTagMusic.GetFromPlayer(m_Handle->addonData, player->m_ControlHandle, &infoTag))
    {
      TransferInfoTag(infoTag);
      m_cb->AddonInfoTagMusic.Release(&infoTag);
    }
  }

  inline CPlayerLib_InfoTagMusic::~CPlayerLib_InfoTagMusic()
  {
  }

  inline const std::string& CPlayerLib_InfoTagMusic::GetURL() const
  {
    return m_url;
  }

  inline const std::string& CPlayerLib_InfoTagMusic::GetTitle() const
  {
    return m_title;
  }

  inline const std::string& CPlayerLib_InfoTagMusic::GetArtist() const
  {
    return m_artist;
  }

  inline const std::string& CPlayerLib_InfoTagMusic::GetAlbum() const
  {
    return m_album;
  }

  inline const std::string& CPlayerLib_InfoTagMusic::GetAlbumArtist() const
  {
    return m_albumArtist;
  }

  inline const std::string& CPlayerLib_InfoTagMusic::GetGenre() const
  {
    return m_genre;
  }

  inline int CPlayerLib_InfoTagMusic::GetDuration() const
  {
    return m_duration;
  }

  inline int CPlayerLib_InfoTagMusic::GetTrack() const
  {
    return m_tracks;
  }

  inline int CPlayerLib_InfoTagMusic::GetDisc() const
  {
    return m_disc;
  }

  inline const std::string& CPlayerLib_InfoTagMusic::GetReleaseDate() const
  {
    return m_releaseDate;
  }

  inline int CPlayerLib_InfoTagMusic::GetListeners() const
  {
    return m_listener;
  }

  inline int CPlayerLib_InfoTagMusic::GetPlayCount() const
  {
    return m_playCount;
  }

  inline const std::string& CPlayerLib_InfoTagMusic::GetLastPlayed() const
  {
    return m_lastPlayed;
  }

  inline const std::string& CPlayerLib_InfoTagMusic::GetComment() const
  {
    return m_comment;
  }

  inline const std::string& CPlayerLib_InfoTagMusic::GetLyrics() const
  {
    return m_lyrics;
  }

  inline void CPlayerLib_InfoTagMusic::TransferInfoTag(AddonInfoTagMusic& infoTag)
  {
    m_url = infoTag.m_url;
    m_title = infoTag.m_title;
    m_artist = infoTag.m_artist;
    m_album = infoTag.m_album;
    m_albumArtist = infoTag.m_albumArtist;
    m_genre = infoTag.m_genre;
    m_duration = infoTag.m_duration;
    m_tracks = infoTag.m_tracks;
    m_disc = infoTag.m_disc;
    m_releaseDate = infoTag.m_releaseDate;
    m_listener = infoTag.m_listener;
    m_playCount = infoTag.m_playCount;
    m_lastPlayed = infoTag.m_lastPlayed;
    m_comment = infoTag.m_comment;
    m_lyrics = infoTag.m_lyrics;
  }

}; /* extern "C" */
}; /* V2 */
}; /* PlayerLIB */
