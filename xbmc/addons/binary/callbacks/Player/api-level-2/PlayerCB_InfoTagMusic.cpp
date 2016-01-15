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

#include "Application.h"
#include "FileItem.h"
#include "GUIInfoManager.h"
#include "addons/Addon.h"
#include "addons/binary/ExceptionHandling.h"
#include "addons/binary/callbacks/AddonCallbacks.h"
#include "music/tags/MusicInfoTag.h"
#include "settings/AdvancedSettings.h"

#include "AddonCallbacksPlayer.h"
#include "PlayerCB_InfoTagMusic.h"

using namespace ADDON;

namespace PlayerLIB
{
namespace V2
{
extern "C"
{

void CPlayerCB_InfoTagMusic::Init(CB_PlayerLib *callbacks)
{
  callbacks->AddonInfoTagMusic.GetFromPlayer  = CPlayerCB_InfoTagMusic::GetFromPlayer;
  callbacks->AddonInfoTagMusic.Release        = CPlayerCB_InfoTagMusic::Release;
}

bool CPlayerCB_InfoTagMusic::GetFromPlayer(
        void*               addonData,
        PLAYERHANDLE        player,
        AddonInfoTagMusic*  tag)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks*>(addonData);
    if (!helper || !player | !tag)
      throw ADDON::WrongValueException("CPlayerCB_AddonPlayer - %s - invalid data (addonData='%p', player='%p', tag='%p')",
                                        __FUNCTION__, helper, player, tag);

    memset(tag, 0, sizeof(AddonInfoTagMusic));

    if (g_application.m_pPlayer->IsPlayingVideo() || !g_application.m_pPlayer->IsPlayingAudio())
      throw ADDON::WrongValueException("CPlayerCB_InfoTagMusic - %s: %s/%s - Kodi is not playing any music file",
                                         __FUNCTION__,
                                         TranslateType(helper->GetAddon()->Type()).c_str(),
                                         helper->GetAddon()->Name().c_str());

    const MUSIC_INFO::CMusicInfoTag* infoTag = g_infoManager.GetCurrentSongTag();
    if (!infoTag)
    {
      CLog::Log(LOGERROR, "CPlayerCB_InfoTagMusic - %s: %s/%s - Failed to get song info",
                                         __FUNCTION__,
                                         TranslateType(helper->GetAddon()->Type()).c_str(),
                                         helper->GetAddon()->Name().c_str());
      return false;
    }

    tag->m_url = strdup(infoTag->GetURL().c_str());
    tag->m_title = strdup(infoTag->GetTitle().c_str());
    tag->m_artist = strdup(infoTag->GetArtistString().c_str());
    tag->m_album = strdup(infoTag->GetAlbum().c_str());
    tag->m_albumArtist = strdup(infoTag->GetAlbumArtistString().c_str());
    tag->m_genre = strdup(StringUtils::Join(infoTag->GetGenre(), g_advancedSettings.m_musicItemSeparator).c_str());
    tag->m_duration = infoTag->GetDuration();
    tag->m_tracks = infoTag->GetTrackNumber();
    tag->m_disc = infoTag->GetDiscNumber();
    tag->m_releaseDate = strdup(infoTag->GetYearString().c_str());
    tag->m_listener = infoTag->GetListeners();
    tag->m_playCount = infoTag->GetPlayCount();
    tag->m_lastPlayed = strdup(infoTag->GetLastPlayed().GetAsLocalizedDate().c_str());
    tag->m_comment = strdup(infoTag->GetComment().c_str());
    tag->m_lyrics = strdup(infoTag->GetLyrics().c_str());

    return true;
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

void CPlayerCB_InfoTagMusic::Release(
        void*               addonData,
        AddonInfoTagMusic*  tag)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !tag)
      throw ADDON::WrongValueException("CPlayerCB_InfoTagMusic - %s - invalid data (addonData='%p', tag='%p')",
                                        __FUNCTION__, helper, tag);
    if (tag->m_url)
      free(tag->m_url);
    if (tag->m_title)
      free(tag->m_title);
    if (tag->m_artist)
      free(tag->m_artist);
    if (tag->m_album)
      free(tag->m_album);
    if (tag->m_albumArtist)
      free(tag->m_albumArtist);
    if (tag->m_genre)
      free(tag->m_genre);
    if (tag->m_releaseDate)
      free(tag->m_releaseDate);
    if (tag->m_lastPlayed)
      free(tag->m_lastPlayed);
    if (tag->m_comment)
      free(tag->m_comment);
    if (tag->m_lyrics)
      free(tag->m_lyrics);

    memset(tag, 0, sizeof(AddonInfoTagMusic));
  }
  HANDLE_ADDON_EXCEPTION
}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace PlayerLIB */
