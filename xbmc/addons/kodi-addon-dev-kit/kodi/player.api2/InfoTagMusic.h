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

#include "definations.h"
#include "internal/libKODI_player_InfoTagMusicHead.h"
#include "internal/libKODI_player_Internal.h"

namespace PlayerLIB
{
namespace V2
{

  ///
  /// \defgroup CPlayerLib_InfoTagMusic
  /// \ingroup PlayerLIB
  /// @{
  /// @brief <b>Used for present music information</b>
  ///
  /// Class contains after request the on Kodi present information of played
  /// music.
  ///
  /// It has the header \ref InfoTagMusic.h "#include <kodi/player.api2/InfoTagMusic.h>" be included
  /// to enjoy it.
  ///
  class CPlayerLib_InfoTagMusic
  {
  public:
    ///
    /// @ingroup CPlayerLib_InfoTagMusic
    ///
    CPlayerLib_InfoTagMusic(CPlayerLib_Player* player);

    ///
    /// @ingroup CPlayerLib_InfoTagMusic
    ///
    virtual ~CPlayerLib_InfoTagMusic();

    ///
    /// @ingroup CPlayerLib_InfoTagMusic
    ///
    const std::string& GetURL() const;

    ///
    /// @ingroup CPlayerLib_InfoTagMusic
    ///
    const std::string& GetTitle() const;

    ///
    /// @ingroup CPlayerLib_InfoTagMusic
    ///
    const std::string& GetArtist() const;

    ///
    /// @ingroup CPlayerLib_InfoTagMusic
    ///
    const std::string& GetAlbum() const;

    ///
    /// @ingroup CPlayerLib_InfoTagMusic
    ///
    const std::string& GetAlbumArtist() const;

    ///
    /// @ingroup CPlayerLib_InfoTagMusic
    ///
    const std::string& GetGenre() const;

    ///
    /// @ingroup CPlayerLib_InfoTagMusic
    ///
    int GetDuration() const;

    ///
    /// @ingroup CPlayerLib_InfoTagMusic
    ///
    int GetTrack() const;

    ///
    /// @ingroup CPlayerLib_InfoTagMusic
    ///
    int GetDisc() const;

    ///
    /// @ingroup CPlayerLib_InfoTagMusic
    ///
    const std::string& GetReleaseDate() const;

    ///
    /// @ingroup CPlayerLib_InfoTagMusic
    ///
    int GetListeners() const;

    ///
    /// @ingroup CPlayerLib_InfoTagMusic
    ///
    int GetPlayCount() const;

    ///
    /// @ingroup CPlayerLib_InfoTagMusic
    ///
    const std::string& GetLastPlayed() const;

    ///
    /// @ingroup CPlayerLib_InfoTagMusic
    ///
    const std::string& GetComment() const;

    ///
    /// @ingroup CPlayerLib_InfoTagMusic
    ///
    const std::string& GetLyrics() const;

    IMPL_ADDON_INFO_TAG_MUSIC;
  };
  /** @}*/

}; /* namespace V2 */
}; /* namespace PlayerLIB */
#include "internal/libKODI_player_InfoTagMusicTail.h"
