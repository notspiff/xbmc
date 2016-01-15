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

#include "BinaryAddonManager.h"

#include "system.h"
#include "Util.h"
#include "utils/log.h"

#include <algorithm>

#define LOCK_AND_COPY(type, dest, src) \
  if (!m_bInitialized) return; \
  CSingleLock lock(src); \
  src.hadSomethingRemoved = false; \
  type dest; \
  dest = src

#define CHECK_FOR_ENTRY(l,v) \
  (l.hadSomethingRemoved ? (std::find(l.begin(),l.end(),v) != l.end()) : true)

namespace ADDON
{

CBinaryAddonManager::CBinaryAddonManager()
  : m_bInitialized(true) //< Forced, becomes used on further development after class is bigger
{

}

CBinaryAddonManager::~CBinaryAddonManager()
{

}

CBinaryAddonManager &CBinaryAddonManager::GetInstance()
{
  static CBinaryAddonManager managerInstance;
  return managerInstance;
}

void CBinaryAddonManager::RegisterPlayerCallBack(IPlayerCallback* pCallback)
{
  CSingleLock lock(m_vecPlayerCallbackList);
  m_vecPlayerCallbackList.push_back(pCallback);
}

void CBinaryAddonManager::UnregisterPlayerCallBack(IPlayerCallback* pCallback)
{
  CSingleLock lock(m_vecPlayerCallbackList);
  PlayerCallbackList::iterator it = m_vecPlayerCallbackList.begin();
  while (it != m_vecPlayerCallbackList.end())
  {
    if (*it == pCallback)
    {
      it = m_vecPlayerCallbackList.erase(it);
      m_vecPlayerCallbackList.hadSomethingRemoved = true;
    }
    else
      ++it;
  }
}

void CBinaryAddonManager::OnPlayBackStarted()
{
  LOCK_AND_COPY(std::vector<PVOID>,tmp,m_vecPlayerCallbackList);
  for (PlayerCallbackList::iterator it = tmp.begin(); (it != tmp.end()); ++it)
  {
    if (CHECK_FOR_ENTRY(m_vecPlayerCallbackList,(*it)))
      ((IPlayerCallback*)(*it))->OnPlayBackStarted();
  }
}

void CBinaryAddonManager::OnPlayBackPaused()
{
  LOCK_AND_COPY(std::vector<PVOID>,tmp,m_vecPlayerCallbackList);
  for (PlayerCallbackList::iterator it = tmp.begin(); (it != tmp.end()); ++it)
  {
    if (CHECK_FOR_ENTRY(m_vecPlayerCallbackList,(*it)))
      ((IPlayerCallback*)(*it))->OnPlayBackPaused();
  }
}

void CBinaryAddonManager::OnPlayBackResumed()
{
  LOCK_AND_COPY(std::vector<PVOID>,tmp,m_vecPlayerCallbackList);
  for (PlayerCallbackList::iterator it = tmp.begin(); (it != tmp.end()); ++it)
  {
    if (CHECK_FOR_ENTRY(m_vecPlayerCallbackList,(*it)))
      ((IPlayerCallback*)(*it))->OnPlayBackResumed();
  }
}

void CBinaryAddonManager::OnPlayBackEnded()
{
  LOCK_AND_COPY(std::vector<PVOID>,tmp,m_vecPlayerCallbackList);
  for (PlayerCallbackList::iterator it = tmp.begin(); (it != tmp.end()); ++it)
  {
    if (CHECK_FOR_ENTRY(m_vecPlayerCallbackList,(*it)))
      ((IPlayerCallback*)(*it))->OnPlayBackEnded();
  }
}

void CBinaryAddonManager::OnPlayBackStopped()
{
  LOCK_AND_COPY(std::vector<PVOID>,tmp,m_vecPlayerCallbackList);
  for (PlayerCallbackList::iterator it = tmp.begin(); (it != tmp.end()); ++it)
  {
    if (CHECK_FOR_ENTRY(m_vecPlayerCallbackList,(*it)))
      ((IPlayerCallback*)(*it))->OnPlayBackStopped();
  }
}

void CBinaryAddonManager::OnPlayBackSpeedChanged(int iSpeed)
{
  LOCK_AND_COPY(std::vector<PVOID>,tmp,m_vecPlayerCallbackList);
  for (PlayerCallbackList::iterator it = tmp.begin(); (it != tmp.end()); ++it)
  {
    if (CHECK_FOR_ENTRY(m_vecPlayerCallbackList,(*it)))
      ((IPlayerCallback*)(*it))->OnPlayBackSpeedChanged(iSpeed);
  }
}

void CBinaryAddonManager::OnPlayBackSeek(int iTime, int seekOffset)
{
  LOCK_AND_COPY(std::vector<PVOID>,tmp,m_vecPlayerCallbackList);
  for (PlayerCallbackList::iterator it = tmp.begin(); (it != tmp.end()); ++it)
  {
    if (CHECK_FOR_ENTRY(m_vecPlayerCallbackList,(*it)))
      ((IPlayerCallback*)(*it))->OnPlayBackSeek(iTime, seekOffset);
  }
}

void CBinaryAddonManager::OnPlayBackSeekChapter(int iChapter)
{
  LOCK_AND_COPY(std::vector<PVOID>,tmp,m_vecPlayerCallbackList);
  for (PlayerCallbackList::iterator it = tmp.begin(); (it != tmp.end()); ++it)
  {
    if (CHECK_FOR_ENTRY(m_vecPlayerCallbackList,(*it)))
      ((IPlayerCallback*)(*it))->OnPlayBackSeekChapter(iChapter);
  }
}

void CBinaryAddonManager::OnQueueNextItem()
{
  LOCK_AND_COPY(std::vector<PVOID>,tmp,m_vecPlayerCallbackList);
  for (PlayerCallbackList::iterator it = tmp.begin(); (it != tmp.end()); ++it)
  {
    if (CHECK_FOR_ENTRY(m_vecPlayerCallbackList,(*it)))
      ((IPlayerCallback*)(*it))->OnQueueNextItem();
  }
}

}; /* namespace ADDON */
