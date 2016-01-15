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

#include "kodi/gui.api2/definations.h"

namespace PlayerLIB
{
namespace V2
{
extern "C"
{

  class CPlayerLib_Player;
  class CPlayerLib_InfoTagVideo;
  class CPlayerLib_InfoTagMusic;

  typedef char* AddonPlayer_GetSupportedMedia(
        void*             addonData,
        int               mediaType);

  typedef PLAYERHANDLE AddonPlayer_New(
        void*             addonData);

  typedef void AddonPlayer_Delete(
        void*             addonData,
        PLAYERHANDLE      handle);

  typedef void AddonPlayer_SetCallbacks(
        void*             addonData,
        PLAYERHANDLE      handle,
        PLAYERHANDLE      cbhdl,
        void      (*CBOnPlayBackStarted)     (PLAYERHANDLE cbhdl),
        void      (*CBOnPlayBackEnded)       (PLAYERHANDLE cbhdl),
        void      (*CBOnPlayBackStopped)     (PLAYERHANDLE cbhdl),
        void      (*CBOnPlayBackPaused)      (PLAYERHANDLE cbhdl),
        void      (*CBOnPlayBackResumed)     (PLAYERHANDLE cbhdl),
        void      (*CBOnQueueNextItem)       (PLAYERHANDLE cbhdl),
        void      (*CBOnPlayBackSpeedChanged)(PLAYERHANDLE cbhdl, int iSpeed),
        void      (*CBOnPlayBackSeek)        (PLAYERHANDLE cbhdl, int iTime, int seekOffset),
        void      (*CBOnPlayBackSeekChapter) (PLAYERHANDLE cbhdl, int iChapter));

  typedef bool AddonPlayer_PlayFile(
        void*             addonData,
        PLAYERHANDLE      handle,
        const char*       item,
        bool              windowed);

  typedef bool AddonPlayer_PlayFileItem(
        void*             addonData,
        PLAYERHANDLE      handle,
        const GUILIB::V2::GUIHANDLE listitem,
        bool              windowed);

  typedef bool AddonPlayer_PlayList(
        void*             addonData,
        PLAYERHANDLE      handle,
        const PLAYERHANDLE list,
        int               playList,
        bool              windowed,
        int               startpos);

  typedef void AddonPlayer_Stop(
        void*             addonData,
        PLAYERHANDLE      handle);

  typedef void AddonPlayer_Pause(
        void*             addonData,
        PLAYERHANDLE      handle);

  typedef void AddonPlayer_PlayNext(
        void*             addonData,
        PLAYERHANDLE      handle);

  typedef void AddonPlayer_PlayPrevious(
        void*             addonData,
        PLAYERHANDLE      handle);

  typedef void AddonPlayer_PlaySelected(
        void*             addonData,
        PLAYERHANDLE      handle,
        int               selected);

  typedef bool AddonPlayer_IsPlaying(
        void*             addonData,
        PLAYERHANDLE      handle);

  typedef bool AddonPlayer_IsPlayingAudio(
        void*             addonData,
        PLAYERHANDLE      handle);

  typedef bool AddonPlayer_IsPlayingVideo(
        void*             addonData,
        PLAYERHANDLE      handle);

  typedef bool AddonPlayer_IsPlayingRDS(
        void*             addonData,
        PLAYERHANDLE      handle);

  typedef bool AddonPlayer_GetPlayingFile(
        void*             addonData,
        PLAYERHANDLE      handle,
        char&             file,
        unsigned int&     iMaxStringSize);

  typedef double AddonPlayer_GetTotalTime(
        void*             addonData,
        PLAYERHANDLE      handle);

  typedef double AddonPlayer_GetTime(
        void*             addonData,
        PLAYERHANDLE      handle);

  typedef void AddonPlayer_SeekTime(
        void*             addonData,
        PLAYERHANDLE      handle,
        double            seekTime);

  typedef bool AddonPlayer_GetAvailableAudioStreams(
        void*             addonData,
        PLAYERHANDLE      handle,
        char**&           streams,
        unsigned int&     entries);

  typedef void AddonPlayer_SetAudioStream(
        void*             addonData,
        PLAYERHANDLE      handle,
        int               iStream);

  typedef bool AddonPlayer_GetAvailableSubtitleStreams(
        void*             addonData,
        PLAYERHANDLE      handle,
        char**&           streams,
        unsigned int&     entries);

  typedef void AddonPlayer_SetSubtitleStream(
        void*             addonData,
        PLAYERHANDLE      handle,
        int               iStream);

  typedef void AddonPlayer_ShowSubtitles(
        void*             addonData,
        PLAYERHANDLE      handle,
        bool              bVisible);

  typedef bool AddonPlayer_GetCurrentSubtitleName(
        void*             addonData,
        PLAYERHANDLE      handle,
        char&             name,
        unsigned int&     iMaxStringSize);

  typedef void AddonPlayer_AddSubtitle(
        void*             addonData,
        PLAYERHANDLE      handle,
        const char*       strSubPath);

  typedef void AddonPlayer_ClearList(
        char**&       path,
        unsigned int  entries);

  typedef struct CB_PlayerLib_AddonPlayer
  {
    AddonPlayer_GetSupportedMedia*            GetSupportedMedia;

    AddonPlayer_New*                          New;
    AddonPlayer_Delete*                       Delete;
    AddonPlayer_SetCallbacks*                 SetCallbacks;

    AddonPlayer_PlayFile*                     PlayFile;
    AddonPlayer_PlayFileItem*                 PlayFileItem;
    AddonPlayer_PlayList*                     PlayList;
    AddonPlayer_Stop*                         Stop;
    AddonPlayer_Pause*                        Pause;
    AddonPlayer_PlayNext*                     PlayNext;
    AddonPlayer_PlayPrevious*                 PlayPrevious;
    AddonPlayer_PlaySelected*                 PlaySelected;
    AddonPlayer_IsPlaying*                    IsPlaying;
    AddonPlayer_IsPlayingAudio*               IsPlayingAudio;
    AddonPlayer_IsPlayingVideo*               IsPlayingVideo;
    AddonPlayer_IsPlayingRDS*                 IsPlayingRDS;

    AddonPlayer_GetPlayingFile*               GetPlayingFile;
    AddonPlayer_GetTotalTime*                 GetTotalTime;
    AddonPlayer_GetTime*                      GetTime;
    AddonPlayer_SeekTime*                     SeekTime;

    AddonPlayer_GetAvailableAudioStreams*     GetAvailableAudioStreams;
    AddonPlayer_SetAudioStream*               SetAudioStream;

    AddonPlayer_GetAvailableSubtitleStreams*  GetAvailableSubtitleStreams;
    AddonPlayer_SetSubtitleStream*            SetSubtitleStream;
    AddonPlayer_ShowSubtitles*                ShowSubtitles;
    AddonPlayer_GetCurrentSubtitleName*       GetCurrentSubtitleName;
    AddonPlayer_AddSubtitle*                  AddSubtitle;

    AddonPlayer_ClearList*                    ClearList;
  } CB_PlayerLib_AddonPlayer;

  #define IMPL_ADDON_PLAYER                                                    \
    private:                                                                   \
      friend class CPlayerLib_InfoTagMusic;                                    \
      friend class CPlayerLib_InfoTagVideo;                                    \
      PLAYERHANDLE      m_ControlHandle;                                       \
      ADDON::AddonCB*   m_Handle;                                              \
      CB_PlayerLib*     m_cb;                                                  \
      static void CBOnPlayBackStarted(PLAYERHANDLE cbhdl);                     \
      static void CBOnPlayBackEnded(PLAYERHANDLE cbhdl);                       \
      static void CBOnPlayBackStopped(PLAYERHANDLE cbhdl);                     \
      static void CBOnPlayBackPaused(PLAYERHANDLE cbhdl);                      \
      static void CBOnPlayBackResumed(PLAYERHANDLE cbhdl);                     \
      static void CBOnQueueNextItem(PLAYERHANDLE cbhdl);                       \
      static void CBOnPlayBackSpeedChanged(PLAYERHANDLE cbhdl, int iSpeed);    \
      static void CBOnPlayBackSeek(PLAYERHANDLE cbhdl, int iTime, int seekOffset);\
      static void CBOnPlayBackSeekChapter(PLAYERHANDLE cbhdl, int iChapter);

}; /* extern "C" */
}; /* V2 */
}; /* PlayerLIB */
