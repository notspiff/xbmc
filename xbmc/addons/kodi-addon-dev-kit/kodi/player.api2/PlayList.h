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
#include "internal/libKODI_player_AddonPlayListHead.h"
#include "internal/libKODI_player_Internal.h"

using namespace GUILIB::V2;

namespace PlayerLIB
{
namespace V2
{

  ///
  /// \defgroup CPlayerLib_PlayList
  /// \ingroup PlayerLIB
  /// @{
  /// @brief <b>Playpack control list</b>
  ///
  /// Class to create a list of different sources to a continuous playback of
  /// this. This also supports a random mode (shuffle) to select the next source.
  ///
  /// It has the header \ref PlayList.h "#include <kodi/player.api2/PlayList.h>" be included
  /// to enjoy it.
  ///
  class CPlayerLib_PlayList
  {
  public:
    ///
    /// @ingroup CPlayerLib_PlayList
    ///
    CPlayerLib_PlayList(AddonPlayListType playList);

    ///
    /// @ingroup CPlayerLib_PlayList
    ///
    virtual ~CPlayerLib_PlayList();

    ///
    /// @ingroup CPlayerLib_PlayList
    ///
    AddonPlayListType GetPlayListType() const;

    ///
    /// @ingroup CPlayerLib_PlayList
    ///
    bool LoadPlaylist(const std::string& filename);

    ///
    /// @ingroup CPlayerLib_PlayList
    ///
    void AddItem(const std::string& url, int index = -1);

    ///
    /// @ingroup CPlayerLib_PlayList
    ///
    void AddItem(const CAddonGUIListItem* listitem, int index = -1);

    ///
    /// @ingroup CPlayerLib_PlayList
    ///
    void RemoveItem(const std::string& url);

    ///
    /// @ingroup CPlayerLib_PlayList
    ///
    void ClearList();

    ///
    /// @ingroup CPlayerLib_PlayList
    ///
    int GetListSize();

    ///
    /// @ingroup CPlayerLib_PlayList
    ///
    int GetListPosition();

    ///
    /// @ingroup CPlayerLib_PlayList
    ///
    void Shuffle(bool shuffle);

    ///
    /// @ingroup CPlayerLib_PlayList
    ///
    CAddonGUIListItem* operator[](long i);

    IMPL_ADDON_PLAYLIST;
  };
  /** @}*/

}; /* namespace V2 */
}; /* namespace PlayerLIB */
#include "internal/libKODI_player_AddonPlayListTail.h"
