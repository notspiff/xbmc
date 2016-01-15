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

  class CPlayerLib_InfoTagMusic;

  typedef struct AddonInfoTagMusic
  {
    char* m_url;
    char* m_title;
    char* m_artist;
    char* m_album;
    char* m_albumArtist;
    char* m_genre;
    int m_duration;
    int m_tracks;
    int m_disc;
    char* m_releaseDate;
    int m_listener;
    int m_playCount;
    char* m_lastPlayed;
    char* m_comment;
    char* m_lyrics;
  } AddonInfoTagMusic;

  typedef bool AddonInfoTagMusic_GetFromPlayer(
        void*               addonData,
        PLAYERHANDLE        player,
        AddonInfoTagMusic*  tag);

  typedef void AddonInfoTagMusic_Release(
        void*               addonData,
        AddonInfoTagMusic*  tag);

  typedef struct CB_PlayerLib_AddonInfoTagMusic
  {
    AddonInfoTagMusic_GetFromPlayer*  GetFromPlayer;
    AddonInfoTagMusic_Release*        Release;
  } CB_PlayerLib_AddonInfoTagMusic;

  #define IMPL_ADDON_INFO_TAG_MUSIC                                            \
    private:                                                                   \
      inline void TransferInfoTag(AddonInfoTagMusic& infoTag);                 \
                                                                               \
      PLAYERHANDLE      m_ControlHandle;                                       \
      ADDON::AddonCB*   m_Handle;                                              \
      CB_PlayerLib*     m_cb;                                                  \
      std::string       m_url;                                                 \
      std::string       m_title;                                               \
      std::string       m_artist;                                              \
      std::string       m_album;                                               \
      std::string       m_albumArtist;                                         \
      std::string       m_genre;                                               \
      int               m_duration;                                            \
      int               m_tracks;                                              \
      int               m_disc;                                                \
      std::string       m_releaseDate;                                         \
      int               m_listener;_                                           \
      int               m_playCount;                                           \
      std::string       m_lastPlayed;                                          \
      std::string       m_comment;                                             \
      std::string       m_lyrics;

}; /* extern "C" */
}; /* V2 */
}; /* PlayerLIB */
