/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "application/IApplicationComponent.h"
#include "playlists/PlayListTypes.h"

class CApplication;
class CFileItem;
class IPlayerCallback;

namespace PLAYLIST
{
class CPlayList;
class CPlayListPlayer;
}

#include <string>

/*!
 * \brief Class handling application support for player info.
 */
class CApplicationPlayerControl : public IApplicationComponent
{
  friend class CApplication;
  friend class PLAYLIST::CPlayListPlayer;

public:
  explicit CApplicationPlayerControl(bool& bStop, IPlayerCallback& cb);

  //! \brief Play a file.
  bool PlayFile(CFileItem item,
                const std::string& player,
                bool bRestart = false);

  //! \brief Play a file using a specified playlist.
  bool PlayMedia(CFileItem& item,
                 const std::string& player,
                 PLAYLIST::Id playlistId);

  bool ProcessAndStartPlaylist(const std::string& strPlayList,
                               PLAYLIST::CPlayList& playlist,
                               PLAYLIST::Id playlistId,
                               int track = 0);

  //! \brief Seek currently playing media to the specified time in seconds.
  //! \details Fractional portions of a second are valid.  The passed
  //!          time is the time offset from the beginning of the file as opposed to a
  //!          delta from the current position.  This method accepts a double to be
  //!          consistent with GetTime() and GetTotalTime().
  void SeekTime(double dTime);

  //! \brief Seek currently playing media to the specified time in percentage.
  void SeekPercentage(float percent);

  //! \brief Stop playing media.
  void StopPlaying();

  const std::string& getCurrentPlaylistFile() const { return m_strPlayListFile; }

protected:
  //! \brief For playing a multi-file video.
  //! \details Particularly inefficient on startup, as we are required
  //!          to calculate the length of each video, so we open + close each one in turn.
  //!          A faster calculation of video time would improve this substantially.
  bool PlayStack(CFileItem& item, bool bRestart);

  bool& m_bStop;
  int m_nextPlaylistItem = -1;
  std::string m_strPlayListFile;

  IPlayerCallback& m_cb;
};
