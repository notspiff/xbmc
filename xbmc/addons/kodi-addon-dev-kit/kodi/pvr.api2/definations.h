#pragma once
/*
 *      Copyright (C) 2015 Team KODI
 *      Copyright (C) 2005-2013 Team XBMC
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

#include <string.h>
#include <time.h>

#undef ATTRIBUTE_PACKED
#undef PRAGMA_PACK_BEGIN
#undef PRAGMA_PACK_END

#if defined(__GNUC__)
#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 95)
#define ATTRIBUTE_PACKED __attribute__ ((packed))
#define PRAGMA_PACK 0
#endif
#endif

#if !defined(ATTRIBUTE_PACKED)
#define ATTRIBUTE_PACKED
#define PRAGMA_PACK 1
#endif

#define PVR_API_LEVELS_ACTIVE 1

#ifdef __cplusplus
namespace PVRLIB
{
namespace V2
{
extern "C"
{
#endif

  /*!
   * \ingroup PVRLIB
   * @{
   * @brief
   */
  /*! @name PVR Add-On API Level and Code Version */
  //@{
  static constexpr const int   PVRLIB_apiLevel = 2;
  static constexpr const char* PVRLIB_version  = "4.1.0";
  //@}

  /*! @name EPG entry content event types */
  //@{
  /* These IDs come from the DVB-SI EIT table "content descriptor"
   * Also known under the name "E-book genre assignments"
   */
  /*! <b>EPG event content:</b> Not defined and is unknown */
  #define EPG_EVENT_CONTENTMASK_UNDEFINED                0x00
  /*! <b>EPG event content:</b> Movie / Drama  */
  #define EPG_EVENT_CONTENTMASK_MOVIEDRAMA               0x10
  /*! <b>EPG event content:</b> News / Current affairs  */
  #define EPG_EVENT_CONTENTMASK_NEWSCURRENTAFFAIRS       0x20
  /*! <b>EPG event content:</b> Show / Game show  */
  #define EPG_EVENT_CONTENTMASK_SHOW                     0x30
  /*! <b>EPG event content:</b> Sports  */
  #define EPG_EVENT_CONTENTMASK_SPORTS                   0x40
  /*! <b>EPG event content:</b> Children's / Youth programmes */
  #define EPG_EVENT_CONTENTMASK_CHILDRENYOUTH            0x50
  /*! <b>EPG event content:</b> Music / Ballet / Dance */
  #define EPG_EVENT_CONTENTMASK_MUSICBALLETDANCE         0x60
  /*! <b>EPG event content:</b> Arts / Culture */
  #define EPG_EVENT_CONTENTMASK_ARTSCULTURE              0x70
  /*! <b>EPG event content:</b> Social / Political / Economics */
  #define EPG_EVENT_CONTENTMASK_SOCIALPOLITICALECONOMICS 0x80
  /*! <b>EPG event content:</b> Education / Science / Factua */
  #define EPG_EVENT_CONTENTMASK_EDUCATIONALSCIENCE       0x90
  /*! <b>EPG event content:</b> Leisure / Hobbies */
  #define EPG_EVENT_CONTENTMASK_LEISUREHOBBIES           0xA0
  /*! <b>EPG event content:</b> Specials */
  #define EPG_EVENT_CONTENTMASK_SPECIAL                  0xB0
  /*! <b>EPG event content:</b> User defined */
  #define EPG_EVENT_CONTENTMASK_USERDEFINED              0xF0
  //@}

  /*!
   * @name Set EPGTAG.iGenreType to EPG_GENRE_USE_STRING to transfer genre strings to Kodi
   */
  /*! Set <c>EPGTAG.iGenreType</c> to <c>EPG_GENRE_USE_STRING</c> to transfer genre strings to Kodi */
  #define EPG_GENRE_USE_STRING                          0x100

  /*!
   * @name EPG_TAG.iFlags values
   */
  //@{
  const unsigned int EPG_TAG_FLAG_UNDEFINED =           0x00000000; /*!< nothing special to say about this entry */
  const unsigned int EPG_TAG_FLAG_IS_SERIES =           0x00000001; /*!< this EPG entry is part of a series */
  //@}

  /*!
   * @brief Representation of an EPG event.
   */
  typedef struct EPG_TAG {
    unsigned int  iUniqueBroadcastId;  /*!< (required) identifier for this event */
    const char *  strTitle;            /*!< (required) this event's title */
    unsigned int  iChannelNumber;      /*!< (required) the number of the channel this event occurs on */
    time_t        startTime;           /*!< (required) start time in UTC */
    time_t        endTime;             /*!< (required) end time in UTC */
    const char *  strPlotOutline;      /*!< (optional) plot outline */
    const char *  strPlot;             /*!< (optional) plot */
    const char *  strOriginalTitle;    /*!< (optional) originaltitle */
    const char *  strCast;             /*!< (optional) cast */
    const char *  strDirector;         /*!< (optional) director */
    const char *  strWriter;           /*!< (optional) writer */
    int           iYear;               /*!< (optional) year */
    const char *  strIMDBNumber;       /*!< (optional) IMDBNumber */
    const char *  strIconPath;         /*!< (optional) icon path */
    int           iGenreType;          /*!< (optional) genre type */
    int           iGenreSubType;       /*!< (optional) genre sub type */
    const char *  strGenreDescription; /*!< (optional) genre. Will be used only when <c>iGenreType = EPG_GENRE_USE_STRING</c> */
    time_t        firstAired;          /*!< (optional) first aired in UTC */
    int           iParentalRating;     /*!< (optional) parental rating */
    int           iStarRating;         /*!< (optional) star rating */
    bool          bNotify;             /*!< (optional) notify the user when this event starts */
    int           iSeriesNumber;       /*!< (optional) series number */
    int           iEpisodeNumber;      /*!< (optional) episode number */
    int           iEpisodePartNumber;  /*!< (optional) episode part number */
    const char *  strEpisodeName;      /*!< (optional) episode name */
    unsigned int  iFlags;              /*!< (optional) bit field of independent flags associated with the EPG entry */
  } ATTRIBUTE_PACKED EPG_TAG;
  /*@}*/

#ifdef __cplusplus
}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace PVRLIB */
#if defined(BUILD_KODI_ADDON)
  using namespace PVRLIB::V2;
#endif
#endif
