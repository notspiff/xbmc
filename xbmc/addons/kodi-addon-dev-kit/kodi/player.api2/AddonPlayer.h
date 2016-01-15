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
#include "PlayList.h"
#include "internal/libKODI_player_AddonPlayerHead.h"
#include "internal/libKODI_player_Internal.h"

using namespace GUILIB::V2;

namespace PlayerLIB
{
namespace V2
{

  ///
  /// \defgroup CPlayerLib_Player
  /// \ingroup PlayerLIB
  /// @{
  /// @brief <b>Creates a new Player</b>
  ///
  ///
  ///
  /// It has the header \ref AddonPlayer.h "#include <kodi/player.api2/AddonPlayer.h>" be included
  /// to enjoy it.
  ///
  class CPlayerLib_Player
  {
  public:
    ///
    /// @ingroup CPlayerLib_Player
    ///
    CPlayerLib_Player();

    ///
    /// @ingroup CPlayerLib_Player
    ///
    virtual ~CPlayerLib_Player();

    ///
    /// @ingroup CPlayerLib_Player
    ///
    static std::string GetSupportedMedia(AddonPlayListType mediaType);

    ///
    /// @ingroup CPlayerLib_Player
    ///
    bool Play(const std::string& item, bool windowed = false);

    ///
    /// @ingroup CPlayerLib_Player
    ///
    bool Play(const CAddonGUIListItem* listitem, bool windowed = false);

    ///
    /// @ingroup CPlayerLib_Player
    ///
    bool Play(const CAddonPlayList* list, bool windowed = false, int startpos = -1);

    ///
    /// @ingroup CPlayerLib_Player
    ///
    void Stop();

    ///
    /// @ingroup CPlayerLib_Player
    ///
    void Pause();

    ///
    /// @ingroup CPlayerLib_Player
    ///
    void PlayNext();

    ///
    /// @ingroup CPlayerLib_Player
    ///
    void PlayPrevious();

    ///
    /// @ingroup CPlayerLib_Player
    ///
    void PlaySelected(int selected);

    ///
    /// @ingroup CPlayerLib_Player
    ///
    bool IsPlaying();

    ///
    /// @ingroup CPlayerLib_Player
    ///
    bool IsPlayingAudio();

    ///
    /// @ingroup CPlayerLib_Player
    ///
    bool IsPlayingVideo();

    ///
    /// @ingroup CPlayerLib_Player
    ///
    bool IsPlayingRDS();

    ///
    /// @ingroup CPlayerLib_Player
    ///
    bool GetPlayingFile(std::string& file);

    ///
    /// @ingroup CPlayerLib_Player
    ///
    double GetTotalTime();

    ///
    /// @ingroup CPlayerLib_Player
    ///
    double GetTime();

    ///
    /// @ingroup CPlayerLib_Player
    ///
    void SeekTime(double seekTime);

    ///
    /// @ingroup CPlayerLib_Player
    ///
    bool GetAvailableAudioStreams(std::vector<std::string> &streams);

    ///
    /// @ingroup CPlayerLib_Player
    ///
    void SetAudioStream(int iStream);

    ///
    /// @ingroup CPlayerLib_Player
    ///
    bool GetAvailableSubtitleStreams(std::vector<std::string> &streams);

    ///
    /// @ingroup CPlayerLib_Player
    ///
    void SetSubtitleStream(int iStream);

    ///
    /// @ingroup CPlayerLib_Player
    ///
    void ShowSubtitles(bool bVisible);

    ///
    /// @ingroup CPlayerLib_Player
    ///
    bool GetCurrentSubtitleName(std::string& name);

    ///
    /// @ingroup CPlayerLib_Player
    ///
    void AddSubtitle(std::string& subPath);

    ///
    /// @defgroup CPlayerLib_Player_callbacks Callback functions from Kodi to add-on
    /// \ingroup CPlayerLib_Player
    /// @brief Functions to handle control callbacks from Kodi
    ///
    /// @link CPlayerLib_Player Go back to normal functions from CPlayerLib_Player@endlink
    ///

    ///
    /// @ingroup CPlayerLib_Player_callbacks
    ///
    virtual void OnPlayBackStarted() { }

    ///
    /// @ingroup CPlayerLib_Player_callbacks
    ///
    virtual void OnPlayBackEnded() { }

    ///
    /// @ingroup CPlayerLib_Player_callbacks
    ///
    virtual void OnPlayBackStopped() { }

    ///
    /// @ingroup CPlayerLib_Player_callbacks
    ///
    virtual void OnPlayBackPaused() { }

    ///
    /// @ingroup CPlayerLib_Player_callbacks
    ///
    virtual void OnPlayBackResumed() { }

    ///
    /// @ingroup CPlayerLib_Player_callbacks
    ///
    virtual void OnQueueNextItem() { }

    ///
    /// @ingroup CPlayerLib_Player_callbacks
    ///
    virtual void OnPlayBackSpeedChanged(int iSpeed) { }

    ///
    /// @ingroup CPlayerLib_Player_callbacks
    ///
    virtual void OnPlayBackSeek(int iTime, int seekOffset) { }

    ///
    /// @ingroup CPlayerLib_Player_callbacks
    ///
    virtual void OnPlayBackSeekChapter(int iChapter) { }

    ///
    /// @ingroup CPlayerLib_Player_callbacks
    /// @brief If the class is used independent (with "new CPlayerLib_Player")
    /// and not as parent (with "cCLASS_own : CPlayerLib_Player") from own must
    /// be the callback from Kodi to add-on overdriven with own functions!
    ///
    void SetIndependentCallbacks(
        PLAYERHANDLE     cbhdl,
        void      (*CBOnPlayBackStarted)     (PLAYERHANDLE cbhdl),
        void      (*CBOnPlayBackEnded)       (PLAYERHANDLE cbhdl),
        void      (*CBOnPlayBackStopped)     (PLAYERHANDLE cbhdl),
        void      (*CBOnPlayBackPaused)      (PLAYERHANDLE cbhdl),
        void      (*CBOnPlayBackResumed)     (PLAYERHANDLE cbhdl),
        void      (*CBOnQueueNextItem)       (PLAYERHANDLE cbhdl),
        void      (*CBOnPlayBackSpeedChanged)(PLAYERHANDLE cbhdl, int iSpeed),
        void      (*CBOnPlayBackSeek)        (PLAYERHANDLE cbhdl, int iTime, int seekOffset),
        void      (*CBOnPlayBackSeekChapter) (PLAYERHANDLE cbhdl, int iChapter));

    IMPL_ADDON_PLAYER;
  };
  /** @}*/

}; /* namespace V2 */
}; /* namespace PlayerLIB */
#include "internal/libKODI_player_AddonPlayerTail.h"
