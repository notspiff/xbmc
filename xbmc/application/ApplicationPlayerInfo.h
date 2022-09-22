/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "application/IApplicationComponent.h"

#include <string>

class CApplicationPlayerCallback;
class CFileItem;

/*!
 * \brief Class handling application support for player info.
 */
class CApplicationPlayerInfo : public IApplicationComponent
{
public:
  CApplicationPlayerInfo(const CApplicationPlayerCallback& cb);

  //! \brief Returns the current time in seconds of the currently playing media.
  //! \details Fractional portions of a second are possible.  This returns a double to
  //!          be consistent with GetTotalTime() and SeekTime().
  double GetTime() const;

  //! \brief Returns the total time in fractional seconds of the currently playing media
  //! \details Beware that this method returns fractional seconds whereas
  //!          IPlayer::GetTotalTime() returns milliseconds.
  double GetTotalTime() const;

  //! \brief Returns current time as a percentage.
  float GetPercentage() const;

  //! \brief Returns current audio delay as a percentage.
  int GetAudioDelay();

  //! \brief Returns current subtitle delay as a percentage.
  int GetSubtitleDelay();

  //! \brief Get the percentage of data currently cached/buffered if applicable
  //! \details (aq/vq + FileCache).
  float GetCachePercentage() const;

  //! \brief Returns path to currently playing file.
  const std::string& CurrentFile() const;

  //! \brief Returns a const-ref to currently playing file.
  const CFileItem& CurrentFileItem() const;

  //! \brief Returns a const-ref to currently playing file or stack part.
  const CFileItem& CurrentUnstackedItem();

protected:
  const CApplicationPlayerCallback& m_cb; //!< Const-ref to player callback for current item access.
};
