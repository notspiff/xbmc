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

#ifdef TARGET_WINDOWS
#include <windows.h>
#else
#ifndef __cdecl
#define __cdecl
#endif
#ifndef __declspec
#define __declspec(X)
#endif
#endif

#include <string>
#include <sys/stat.h>

typedef int ADDON_STATUS;

#ifdef __cplusplus
namespace AddOnLIB
{
namespace V2
{
extern "C"
{
#endif

  /*!
   * \ingroup AddOnLIB
   * @{
   */

  ///
  /// \ingroup AddOnLIB
  /// @brief API level and Add-On to Kodi interface Version.
  ///
  /// Here the values define for the Add-On and also for Kodi the version of the
  /// interface between the both.
  ///
  /// @{
  static constexpr const int   AddOnLIB_apiLevel = 2;       //!< API level version
  static constexpr const char* AddOnLIB_version  = "0.0.1"; //!< Code version of add-on interface system
  /// @}

  ///
  /// @brief For CAddonLib_General::Log used message types
  ///
  typedef enum addon_log
  {
    LOG_DEBUG,                                   //!< In depth information about the status of Kodi. This information can pretty much only be deciphered by a developer or long time Kodi power user.
    LOG_INFO,                                    //!< Something has happened. It's not a problem, we just thought you might want to know. Fairly excessive output that most people won't care about.
    LOG_NOTICE,                                  //!< Similar to INFO but the average Joe might want to know about these events. This level and above are logged by default.
    LOG_WARNING,                                 //!< Something potentially bad has happened. If Kodi did something you didn't expect, this is probably why. Watch for errors to follow.
    LOG_ERROR,                                   //!< This event is bad. Something has failed. You likely noticed problems with the application be it skin artifacts, failure of playback a crash, etc.
    LOG_SEVERE,                                  //!<
    LOG_FATAL                                    //!< We're screwed. Kodi is about to crash.
  } addon_log;

  ///
  /// @brief For CAddonLib_General::QueueNotification used message types
  ///
  typedef enum queue_msg
  {
    QUEUE_INFO,                                  //!< Show info notification message
    QUEUE_WARNING,                               //!< Show warning notification message
    QUEUE_ERROR                                  //!< Show error notification message
  } queue_msg;

  ///
  /// @brief Format codes to get string from them.
  ///
  typedef enum lang_formats
  {
    LANG_FMT_ISO_639_1,                          //!< two letter code as defined in ISO 639-1
    LANG_FMT_ISO_639_2,                          //!< three letter code as defined in ISO 639-2/T or ISO 639-2/B
    LANG_FMT_ENGLISH_NAME                        //!< full language name in English
  } lang_formats;

  ///
  /// @enum dvd_state State values about optical drive
  ///
  typedef enum dvd_state
  {
    ADDON_DRIVE_NOT_READY           = 0x01,      //!<
    ADDON_DRIVE_CLOSED_NO_MEDIA     = 0x03,      //!<
    ADDON_TRAY_OPEN                 = 0x10,      //!<
    ADDON_TRAY_CLOSED_NO_MEDIA      = 0x40,      //!<
    ADDON_TRAY_CLOSED_MEDIA_PRESENT = 0x60       //!<
  } dvd_state;

  ///
  /// @brief Kodi server identificators
  ///
  typedef enum eservers
  {
    ADDON_ES_WEBSERVER = 1,                      //!< [To control Kodi's builtin webserver](http://kodi.wiki/view/Webserver)
    ADDON_ES_AIRPLAYSERVER,                      //!< [AirPlay is a proprietary protocol stack/suite developed by Apple Inc.](http://kodi.wiki/view/AirPlay)
    ADDON_ES_JSONRPCSERVER,                      //!< [Control JSON-RPC HTTP/TCP socket-based interface](http://kodi.wiki/view/JSON-RPC_API)
    ADDON_ES_UPNPRENDERER,                       //!< [UPnP client (aka UPnP renderer)](http://kodi.wiki/view/UPnP/Client)
    ADDON_ES_UPNPSERVER,                         //!< [Control built-in UPnP A/V media server (UPnP-server)](http://kodi.wiki/view/UPnP/Server)
    ADDON_ES_EVENTSERVER,                        //!< [Set eventServer part that accepts remote device input on all platforms](http://kodi.wiki/view/EventServer)
    ADDON_ES_ZEROCONF                            //!< [Control Kodi's Avahi Zeroconf](http://kodi.wiki/view/Zeroconf)
  } eservers;

  ///
  /// \ingroup CAddonLib_General
  /// @brief For CAddonLib_General::KodiVersion used structure
  ///
  typedef struct kodi_version
  {
    std::string compile_name;                    //!< Application name, normally 'Kodi'
    int         major;                           //!< Major code version of Kodi
    int         minor;                           //!< Minor code version of Kodi
    std::string revision;                        //!< The Revision contains a id and the build date, e.g. 2015-11-30-74edffb-dirty
    std::string tag;                             //!< The version canditate e.g. alpha, beta or release
    std::string tag_revision;                    //!< The revision of tag before
  } kodi_version;

  ///
  /// @ingroup CAddonLib_SoundPlay
  /// @brief For class CAddonLib_SoundPlay used values
  ///
  /// The values are used to identify a channel and can also serve as a pointer
  /// to memory can be used. Currently supported Kodi not all listed position
  /// and are only available in order to avoid major changes after it is placed.
  ///
  typedef enum audio_channel
  {
    AUDIO_CH_INVALID = -1,                       //!< Invalid channel identifier, also used on CAddonLib_SoundPlay to reset selection
    AUDIO_CH_FL = 0,                             //!< Front left
    AUDIO_CH_FR,                                 //!< Front right
    AUDIO_CH_FC,                                 //!< Front center
    AUDIO_CH_LFE,                                //!< LFE (Bass)
    AUDIO_CH_BL,                                 //!< Back left
    AUDIO_CH_BR,                                 //!< Back right
    AUDIO_CH_FLOC,                               //!< Front left over center (currently not supported on Kodi)
    AUDIO_CH_FROC,                               //!< Front right over center (currently not supported on Kodi)
    AUDIO_CH_BC,                                 //!< Back center
    AUDIO_CH_SL,                                 //!< Side left
    AUDIO_CH_SR,                                 //!< Side right
    AUDIO_CH_TFL,                                //!< Top front left (currently not supported on Kodi)
    AUDIO_CH_TFR,                                //!< Top front right (currently not supported on Kodi)
    AUDIO_CH_TFC,                                //!< Top front center (currently not supported on Kodi)
    AUDIO_CH_TC,                                 //!< Top center (currently not supported on Kodi)
    AUDIO_CH_TBL,                                //!< Top back left (currently not supported on Kodi)
    AUDIO_CH_TBR,                                //!< Top back right (currently not supported on Kodi)
    AUDIO_CH_TBC,                                //!< Top back center (currently not supported on Kodi)
    AUDIO_CH_BLOC,                               //!< Back left over center (currently not supported on Kodi)
    AUDIO_CH_BROC,                               //!< Back right over center (currently not supported on Kodi)

    AUDIO_CH_MAX                                 //!< Used as max value for a array size, not a position
  } audio_channel;

  ///
  /// @brief Codec identifier
  ///
  typedef unsigned int kodi_codec_id;

  ///
  /// @brief Codecs stream type definations
  ///
  typedef enum kodi_codec_type
  {
    KODI_CODEC_TYPE_UNKNOWN = -1,                //!< Unknown identifier
    KODI_CODEC_TYPE_VIDEO,                       //!< Video stream format
    KODI_CODEC_TYPE_AUDIO,                       //!< Audio stream format
    KODI_CODEC_TYPE_DATA,                        //!< Data stream format
    KODI_CODEC_TYPE_SUBTITLE,                    //!< Subtitle stream format
    KODI_CODEC_TYPE_RDS,                         //!< Radio RDS stream format
    KODI_CODEC_TYPE_NB                           //!< Not used
  } kodi_codec_type;

  ///
  /// @brief Codec identification structure.
  ///
  typedef struct
  {
    kodi_codec_type codec_type;                  //!< Stream type identification
    kodi_codec_id   codec_id;                    //!< Needed codec identification (is code based upon ffmpeg)
  } kodi_codec;

  #define KODI_INVALID_CODEC_ID 0
  #define KODI_INVALID_CODEC    { AddOnLIB::V2::KODI_CODEC_TYPE_UNKNOWN, KODI_INVALID_CODEC_ID }
  /// @}

  ///
  /// @brief Platform dependent path separator
  ///
  #ifndef PATH_SEPARATOR_CHAR
    #if (defined(_WIN32) || defined(_WIN64))
      #define PATH_SEPARATOR_CHAR '\\'
    #else
      #define PATH_SEPARATOR_CHAR '/'
    #endif
  #endif

  #if !defined(__stat64)
    #if defined(__APPLE__)
      #define __stat64 stat
    #else
      #define __stat64 stat64
    #endif
  #endif

  /*@}*/

#ifdef __cplusplus
}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace AddOnLIB */
#if defined(BUILD_KODI_ADDON)
  using namespace AddOnLIB::V2;
#endif
#endif
