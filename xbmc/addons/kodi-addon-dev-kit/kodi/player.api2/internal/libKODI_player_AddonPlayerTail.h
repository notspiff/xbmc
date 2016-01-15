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

  inline CPlayerLib_Player::CPlayerLib_Player()
   : m_Handle((ADDON::AddonCB*)CGUILib::g_libKODI_Internal->m_Handle),
     m_cb(CPlayerLib::g_libKODI_Internal->m_Callbacks)
  {
    if (m_Handle && m_cb)
    {
      m_ControlHandle = m_cb->AddonPlayer.New(m_Handle->addonData);
      if (m_ControlHandle)
        m_cb->AddonPlayer.SetCallbacks(m_Handle->addonData, m_ControlHandle, this,
                                       CBOnPlayBackStarted, CBOnPlayBackEnded,
                                       CBOnPlayBackStopped, CBOnPlayBackPaused,
                                       CBOnPlayBackResumed, CBOnQueueNextItem,
                                       CBOnPlayBackSpeedChanged, CBOnPlayBackSeek,
                                       CBOnPlayBackSeekChapter);
      else
        fprintf(stderr, "ERROR: CPlayerLib_Player can't create control class from Kodi !!!\n");
    }
  }

  inline CPlayerLib_Player::~CPlayerLib_Player()
  {
    m_cb->AddonPlayer.Delete(m_Handle->addonData, m_ControlHandle);
  }

  inline std::string CPlayerLib_Player::GetSupportedMedia(AddonPlayListType mediaType)
  {
    std::string strReturn;
    char* strMsg = CPlayerLib::g_libKODI_Internal->m_Callbacks->AddonPlayer.GetSupportedMedia(CPlayerLib::g_libKODI_Internal->m_Handle, mediaType);
    if (strMsg != nullptr)
    {
      if (std::strlen(strMsg))
        strReturn = strMsg;
      CPlayerLib::g_libKODI_Internal->m_Callbacks->FreeString(CPlayerLib::g_libKODI_Internal->m_Handle, strMsg);
    }
    return strReturn;
  }

  inline bool CPlayerLib_Player::Play(const std::string& item, bool windowed)
  {
    return m_cb->AddonPlayer.PlayFile(m_Handle->addonData, m_ControlHandle, item.c_str(), windowed);
  }

  inline bool CPlayerLib_Player::Play(const CAddonGUIListItem *listitem, bool windowed)
  {
    return m_cb->AddonPlayer.PlayFileItem(m_Handle->addonData, m_ControlHandle, listitem->GetListItemHandle(), windowed);
  }

  inline bool CPlayerLib_Player::Play(const CPlayerLib_PlayList *list, bool windowed, int startpos)
  {
    return m_cb->AddonPlayer.PlayList(m_Handle->addonData, m_ControlHandle, list->GetListHandle(), list->GetListType(), windowed, startpos);
  }

  inline void CPlayerLib_Player::Stop()
  {
    m_cb->AddonPlayer.Stop(m_Handle->addonData, m_ControlHandle);
  }

  inline void CPlayerLib_Player::Pause()
  {
    m_cb->AddonPlayer.Pause(m_Handle->addonData, m_ControlHandle);
  }

  inline void CPlayerLib_Player::PlayNext()
  {
    m_cb->AddonPlayer.PlayNext(m_Handle->addonData, m_ControlHandle);
  }

  inline void CPlayerLib_Player::PlayPrevious()
  {
    m_cb->AddonPlayer.PlayPrevious(m_Handle->addonData, m_ControlHandle);
  }

  inline void CPlayerLib_Player::PlaySelected(int selected)
  {
    m_cb->AddonPlayer.PlaySelected(m_Handle->addonData, m_ControlHandle, selected);
  }

  inline bool CPlayerLib_Player::IsPlaying()
  {
    return m_cb->AddonPlayer.IsPlaying(m_Handle->addonData, m_ControlHandle);
  }

  inline bool CPlayerLib_Player::IsPlayingAudio()
  {
    return m_cb->AddonPlayer.IsPlayingAudio(m_Handle->addonData, m_ControlHandle);
  }

  inline bool CPlayerLib_Player::IsPlayingVideo()
  {
    return m_cb->AddonPlayer.IsPlayingVideo(m_Handle->addonData, m_ControlHandle);
  }

  inline bool CPlayerLib_Player::IsPlayingRDS()
  {
    return m_cb->AddonPlayer.IsPlayingRDS(m_Handle->addonData, m_ControlHandle);
  }

  inline bool CPlayerLib_Player::GetPlayingFile(std::string& file)
  {
    file.resize(1024);
    unsigned int size = (unsigned int)file.capacity();
    bool ret = m_cb->AddonPlayer.GetPlayingFile(m_Handle->addonData, m_ControlHandle, file[0], size);
    file.resize(size);
    file.shrink_to_fit();
    return ret;
  }

  inline double CPlayerLib_Player::GetTotalTime()
  {
    return m_cb->AddonPlayer.GetTotalTime(m_Handle->addonData, m_ControlHandle);
  }

  inline double CPlayerLib_Player::GetTime()
  {
    return m_cb->AddonPlayer.GetTime(m_Handle->addonData, m_ControlHandle);
  }

  inline void CPlayerLib_Player::SeekTime(double seekTime)
  {
    m_cb->AddonPlayer.SeekTime(m_Handle->addonData, m_ControlHandle, seekTime);
  }

  inline bool CPlayerLib_Player::GetAvailableAudioStreams(std::vector<std::string> &streams)
  {
    char** list;
    unsigned int listSize = 0;
    bool ret = m_cb->AddonPlayer.GetAvailableAudioStreams(m_Handle->addonData, m_ControlHandle, list, listSize);
    if (ret)
    {
      for (unsigned int i = 0; i < listSize; ++i)
        streams.push_back(list[i]);
      m_cb->AddonPlayer.ClearList(list, listSize);
    }
    return ret;
  }

  inline void CPlayerLib_Player::SetAudioStream(int iStream)
  {
    m_cb->AddonPlayer.SetAudioStream(m_Handle->addonData, m_ControlHandle, iStream);
  }

  inline bool CPlayerLib_Player::GetAvailableSubtitleStreams(std::vector<std::string> &streams)
  {
    char** list;
    unsigned int listSize = 0;
    bool ret = m_cb->AddonPlayer.GetAvailableSubtitleStreams(m_Handle->addonData, m_ControlHandle, list, listSize);
    if (ret)
    {
      for (unsigned int i = 0; i < listSize; ++i)
        streams.push_back(list[i]);
      m_cb->AddonPlayer.ClearList(list, listSize);
    }
    return ret;
  }

  inline void CPlayerLib_Player::SetSubtitleStream(int iStream)
  {
    m_cb->AddonPlayer.SetSubtitleStream(m_Handle->addonData, m_ControlHandle, iStream);
  }

  inline void CPlayerLib_Player::ShowSubtitles(bool bVisible)
  {
    m_cb->AddonPlayer.ShowSubtitles(m_Handle->addonData, m_ControlHandle, bVisible);
  }

  inline bool CPlayerLib_Player::GetCurrentSubtitleName(std::string& name)
  {
    name.resize(1024);
    unsigned int size = (unsigned int)name.capacity();
    bool ret = m_cb->AddonPlayer.GetCurrentSubtitleName(m_Handle->addonData, m_ControlHandle, name[0], size);
    name.resize(size);
    name.shrink_to_fit();
    return ret;
  }

  inline void CPlayerLib_Player::AddSubtitle(std::string& subPath)
  {
    m_cb->AddonPlayer.AddSubtitle(m_Handle->addonData, m_ControlHandle, subPath.c_str());
  }

  /*!
   * Kodi to add-on override defination function to use if class becomes used
   * independet.
   */

  inline void CPlayerLib_Player::SetIndependentCallbacks(
        PLAYERHANDLE     cbhdl,
        void      (*IndptCBOnPlayBackStarted)     (PLAYERHANDLE cbhdl),
        void      (*IndptCBOnPlayBackEnded)       (PLAYERHANDLE cbhdl),
        void      (*IndptCBOnPlayBackStopped)     (PLAYERHANDLE cbhdl),
        void      (*IndptCBOnPlayBackPaused)      (PLAYERHANDLE cbhdl),
        void      (*IndptCBOnPlayBackResumed)     (PLAYERHANDLE cbhdl),
        void      (*IndptCBOnQueueNextItem)       (PLAYERHANDLE cbhdl),
        void      (*IndptCBOnPlayBackSpeedChanged)(PLAYERHANDLE cbhdl, int iSpeed),
        void      (*IndptCBOnPlayBackSeek)        (PLAYERHANDLE cbhdl, int iTime, int seekOffset),
        void      (*IndptCBOnPlayBackSeekChapter) (PLAYERHANDLE cbhdl, int iChapter))
  {
    if (!m_Handle || !m_cb || !cbhdl ||
        !IndptCBOnPlayBackStarted || !IndptCBOnPlayBackEnded || !IndptCBOnPlayBackStopped || !IndptCBOnPlayBackPaused ||
        !IndptCBOnPlayBackResumed || !IndptCBOnQueueNextItem || !IndptCBOnPlayBackSpeedChanged ||
        !IndptCBOnPlayBackSeek    || !IndptCBOnPlayBackSeekChapter)
    {
        fprintf(stderr, "ERROR: CPlayerLib_Player - SetIndependentCallbacks: called with nullptr !!!\n");
        return;
    }

    m_cb->AddonPlayer.SetCallbacks(m_Handle->addonData, m_ControlHandle, cbhdl,
                                   IndptCBOnPlayBackStarted, IndptCBOnPlayBackEnded,
                                   IndptCBOnPlayBackStopped, IndptCBOnPlayBackPaused,
                                   IndptCBOnPlayBackResumed, IndptCBOnQueueNextItem,
                                   IndptCBOnPlayBackSpeedChanged, IndptCBOnPlayBackSeek,
                                   IndptCBOnPlayBackSeekChapter);
  }

  /*!
   * Defined callback functions from Kodi to add-on, for use in parent / child system
   * (is private)!
   */

  inline void CPlayerLib_Player::CBOnPlayBackStarted(PLAYERHANDLE cbhdl)
  {
    static_cast<CPlayerLib_Player*>(cbhdl)->OnPlayBackStarted();
  }

  inline void CPlayerLib_Player::CBOnPlayBackEnded(PLAYERHANDLE cbhdl)
  {
    static_cast<CPlayerLib_Player*>(cbhdl)->OnPlayBackEnded();
  }

  inline void CPlayerLib_Player::CBOnPlayBackStopped(PLAYERHANDLE cbhdl)
  {
    static_cast<CPlayerLib_Player*>(cbhdl)->OnPlayBackStopped();
  }

  inline void CPlayerLib_Player::CBOnPlayBackPaused(PLAYERHANDLE cbhdl)
  {
    static_cast<CPlayerLib_Player*>(cbhdl)->OnPlayBackPaused();
  }

  inline void CPlayerLib_Player::CBOnPlayBackResumed(PLAYERHANDLE cbhdl)
  {
    static_cast<CPlayerLib_Player*>(cbhdl)->OnPlayBackResumed();
  }

  inline void CPlayerLib_Player::CBOnQueueNextItem(PLAYERHANDLE cbhdl)
  {
    static_cast<CPlayerLib_Player*>(cbhdl)->OnQueueNextItem();
  }

  inline void CPlayerLib_Player::CBOnPlayBackSpeedChanged(PLAYERHANDLE cbhdl, int iSpeed)
  {
    static_cast<CPlayerLib_Player*>(cbhdl)->OnPlayBackSpeedChanged(iSpeed);
  }

  inline void CPlayerLib_Player::CBOnPlayBackSeek(PLAYERHANDLE cbhdl, int iTime, int seekOffset)
  {
    static_cast<CPlayerLib_Player*>(cbhdl)->OnPlayBackSeek(iTime, seekOffset);
  }

  inline void CPlayerLib_Player::CBOnPlayBackSeekChapter(PLAYERHANDLE cbhdl, int iChapter)
  {
    static_cast<CPlayerLib_Player*>(cbhdl)->OnPlayBackSeekChapter(iChapter);
  }

}; /* extern "C" */
}; /* V2 */
}; /* PlayerLIB */
