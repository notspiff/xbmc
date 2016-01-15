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
#include "internal/libKODI_player_InfoTagVideoHead.h"
#include "internal/libKODI_player_Internal.h"

namespace PlayerLIB
{
namespace V2
{

  ///
  /// \defgroup CPlayerLib_InfoTagVideo
  /// \ingroup PlayerLIB
  /// @{
  /// @brief <b>Used for present video information</b>
  ///
  /// Class contains after request the on Kodi present information of played
  /// video.
  ///
  /// It has the header \ref InfoTagVideo.h "#include <kodi/player.api2/InfoTagVideo.h>" be included
  /// to enjoy it.
  ///
  class CPlayerLib_InfoTagVideo
  {
  public:
    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    CPlayerLib_InfoTagVideo(CPlayerLib_Player* player);

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    virtual ~CPlayerLib_InfoTagVideo();

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    const std::string& GetDirector() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    const std::string& GetWritingCredits() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    const std::string& GetGenre() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    const std::string& GetCountry() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    const std::string& GetTagLine() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    const std::string& GetPlotOutline() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    const std::string& GetPlot() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    const std::string& GetTrailer() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    const std::string& GetPictureURL() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    const std::string& GetTitle() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    const std::string& GetVotes() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    const std::string& GetCast() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    const std::string& GetFile() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    const std::string& GetPath() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    const std::string& GetIMDBNumber() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    const std::string& GetMPAARating() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    int GetYear() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    double GetRating() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    int GetPlayCount() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    const std::string& GetLastPlayed() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    const std::string& GetOriginalTitle() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    const std::string& GetPremiered() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    const std::string& GetFirstAired() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    ///
    unsigned int GetDuration() const;

    IMPL_ADDON_INFO_TAG_VIDEO;
  };
  /// @}

}; /* namespace V2 */
}; /* namespace PlayerLIB */
#include "internal/libKODI_player_InfoTagVideoTail.h"
