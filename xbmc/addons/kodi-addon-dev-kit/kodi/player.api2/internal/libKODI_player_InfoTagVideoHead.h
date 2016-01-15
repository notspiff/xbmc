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

  class CPlayerLib_InfoTagVideo;

  typedef struct AddonInfoTagVideo
  {
    char* m_director;
    char* m_writingCredits;
    char* m_genre;
    char* m_country;
    char* m_tagLine;
    char* m_plotOutline;
    char* m_plot;
    char* m_trailer;
    char* m_pictureURL;
    char* m_title;
    char* m_votes;
    char* m_cast;
    char* m_file;
    char* m_path;
    char* m_IMDBNumber;
    char* m_MPAARating;
    int m_year;
    double m_rating;
    int m_playCount;
    char* m_lastPlayed;
    char* m_originalTitle;
    char* m_premiered;
    char* m_firstAired;
    unsigned int m_duration;
  } AddonInfoTagVideo;

  typedef bool AddonInfoTagVideo_GetFromPlayer(
        void*               addonData,
        PLAYERHANDLE        player,
        AddonInfoTagVideo*  tag);

  typedef void AddonInfoTagVideo_Release(
        void*               addonData,
        AddonInfoTagVideo*  tag);

  typedef struct CB_PlayerLib_AddonInfoTagVideo
  {
    AddonInfoTagVideo_GetFromPlayer*  GetFromPlayer;
    AddonInfoTagVideo_Release*        Release;
  } CB_PlayerLib_AddonInfoTagVideo;

  #define IMPL_ADDON_INFO_TAG_VIDEO                                            \
    private:                                                                   \
      inline void TransferInfoTag(AddonInfoTagVideo& infoTag);                 \
                                                                               \
      PLAYERHANDLE      m_ControlHandle;                                       \
      ADDON::AddonCB*   m_Handle;                                              \
      CB_PlayerLib*     m_cb;                                                  \
      std::string       m_director;                                            \
      std::string       m_writingCredits;                                      \
      std::string       m_genre;                                               \
      std::string       m_country;                                             \
      std::string       m_tagLine;                                             \
      std::string       m_plotOutline;                                         \
      std::string       m_plot;                                                \
      std::string       m_trailer;                                             \
      std::string       m_pictureURL;                                          \
      std::string       m_title;                                               \
      std::string       m_votes;                                               \
      std::string       m_cast;                                                \
      std::string       m_file;                                                \
      std::string       m_path;                                                \
      std::string       m_IMDBNumber;                                          \
      std::string       m_MPAARating;                                          \
      int               m_year;                                                \
      double            m_rating;                                              \
      int               m_playCount;                                           \
      std::string       m_lastPlayed;                                          \
      std::string       m_originalTitle;                                       \
      std::string       m_premiered;                                           \
      std::string       m_firstAired;                                          \
      unsigned int      m_duration;

}; /* extern "C" */
}; /* V2 */
}; /* PlayerLIB */
