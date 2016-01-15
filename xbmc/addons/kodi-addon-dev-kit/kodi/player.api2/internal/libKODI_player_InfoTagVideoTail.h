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

  inline CPlayerLib_InfoTagVideo::CPlayerLib_InfoTagVideo(CPlayerLib_Player* player)
   : m_Handle((ADDON::AddonCB*)CGUILib::g_libKODI_Internal->m_Handle),
     m_cb(CGUILib::g_libKODI_Internal->m_Callbacks)
  {
    if (!player || !player->m_ControlHandle)
    {
      return;
    }

    AddonInfoTagVideo infoTag;
    if (m_cb->AddonInfoTagVideo.GetFromPlayer(m_Handle->addonData, player->m_ControlHandle, &infoTag))
    {
      TransferInfoTag(infoTag);
      m_cb->AddonInfoTagVideo.Release(&infoTag);
    }
  }

  inline CPlayerLib_InfoTagVideo::~CPlayerLib_InfoTagVideo()
  {
  }

  inline const std::string& CPlayerLib_InfoTagVideo::GetDirector() const
  {
    return m_director;
  }

  inline const std::string& CPlayerLib_InfoTagVideo::GetWritingCredits() const
  {
    return m_writingCredits;
  }

  inline const std::string& CPlayerLib_InfoTagVideo::GetGenre() const
  {
    return m_genre;
  }

  inline const std::string& CPlayerLib_InfoTagVideo::GetCountry() const
  {
    return m_country;
  }

  inline const std::string& CPlayerLib_InfoTagVideo::GetTagLine() const
  {
    return m_tagLine;
  }

  inline const std::string& CPlayerLib_InfoTagVideo::GetPlotOutline() const
  {
    return m_plotOutline;
  }

  inline const std::string& CPlayerLib_InfoTagVideo::GetPlot() const
  {
    return m_plot;
  }

  inline const std::string& CPlayerLib_InfoTagVideo::GetTrailer() const
  {
    return m_trailer;
  }

  inline const std::string& CPlayerLib_InfoTagVideo::GetPictureURL() const
  {
    return m_pictureURL;
  }

  inline const std::string& CPlayerLib_InfoTagVideo::GetTitle() const
  {
    return m_title;
  }

  inline const std::string& CPlayerLib_InfoTagVideo::GetVotes() const
  {
    return m_votes;
  }

  inline const std::string& CPlayerLib_InfoTagVideo::GetCast() const
  {
    return m_cast;
  }

  inline const std::string& CPlayerLib_InfoTagVideo::GetFile() const
  {
    return m_file;
  }

  inline const std::string& CPlayerLib_InfoTagVideo::GetPath() const
  {
    return m_path;
  }

  inline const std::string& CPlayerLib_InfoTagVideo::GetIMDBNumber() const
  {
    return m_IMDBNumber;
  }

  inline const std::string& CPlayerLib_InfoTagVideo::GetMPAARating() const
  {
    return m_MPAARating;
  }

  inline int CPlayerLib_InfoTagVideo::GetYear() const
  {
    return m_year;
  }

  inline double CPlayerLib_InfoTagVideo::GetRating() const
  {
    return m_rating;
  }

  inline int CPlayerLib_InfoTagVideo::GetPlayCount() const
  {
    return m_playCount;
  }

  inline const std::string& CPlayerLib_InfoTagVideo::GetLastPlayed() const
  {
    return m_lastPlayed;
  }

  inline const std::string& CPlayerLib_InfoTagVideo::GetOriginalTitle() const
  {
    return m_originalTitle;
  }

  inline const std::string& CPlayerLib_InfoTagVideo::GetPremiered() const
  {
    return m_premiered;
  }

  inline const std::string& CPlayerLib_InfoTagVideo::GetFirstAired() const
  {
    return m_firstAired;
  }

  inline unsigned int CPlayerLib_InfoTagVideo::GetDuration() const
  {
    return m_duration;
  }

  inline void CPlayerLib_InfoTagVideo::TransferInfoTag(AddonInfoTagVideo& infoTag)
  {
    m_director = infoTag.m_director;
    m_writingCredits = infoTag.m_writingCredits;
    m_genre = infoTag.m_genre;
    m_country = infoTag.m_country;
    m_tagLine = infoTag.m_tagLine;
    m_plotOutline = infoTag.m_plotOutline;
    m_plot = infoTag.m_plot;
    m_trailer = infoTag.m_trailer;
    m_pictureURL = infoTag.m_pictureURL;
    m_title = infoTag.m_title;
    m_votes = infoTag.m_votes;
    m_cast = infoTag.m_cast;
    m_file = infoTag.m_file;
    m_path = infoTag.m_path;
    m_IMDBNumber = infoTag.m_IMDBNumber;
    m_MPAARating = infoTag.m_MPAARating;
    m_year = infoTag.m_year;
    m_rating = infoTag.m_rating;
    m_playCount = infoTag.m_playCount;
    m_lastPlayed = infoTag.m_lastPlayed;
    m_originalTitle = infoTag.m_originalTitle;
    m_premiered = infoTag.m_premiered;
    m_firstAired = infoTag.m_firstAired;
    m_duration = infoTag.m_duration;
  }

}; /* extern "C" */
}; /* V2 */
}; /* PlayerLIB */
