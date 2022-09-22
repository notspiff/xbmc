/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "ApplicationPlayerInfo.h"

#include "ServiceBroker.h"
#include "application/ApplicationComponents.h"
#include "application/ApplicationPlayer.h"
#include "application/ApplicationPlayerCallback.h"
#include "application/ApplicationStackHelper.h"
#include "music/tags/MusicInfoTag.h"
#include "settings/AdvancedSettings.h"
#include "settings/SettingsComponent.h"

CApplicationPlayerInfo::CApplicationPlayerInfo(const CApplicationPlayerCallback& cb)
  : m_cb(cb)
{
}

double CApplicationPlayerInfo::GetTime() const
{
  double rc = 0.0;

  auto& components = CServiceBroker::GetAppComponents();
  const auto appPlayer = components.GetComponent<CApplicationPlayer>();
  const auto stackHelper = components.GetComponent<CApplicationStackHelper>();
  if (appPlayer && appPlayer->IsPlaying())
  {
    if (stackHelper && stackHelper->IsPlayingRegularStack())
    {
      uint64_t startOfCurrentFile = stackHelper->GetCurrentStackPartStartTimeMs();
      rc = (startOfCurrentFile + appPlayer->GetTime()) * 0.001;
    }
    else
      rc = appPlayer->GetTime() * 0.001;
  }

  return rc;
}

double CApplicationPlayerInfo::GetTotalTime() const
{
  double rc = 0.0;

  auto& components = CServiceBroker::GetAppComponents();
  const auto appPlayer = components.GetComponent<CApplicationPlayer>();
  const auto stackHelper = components.GetComponent<CApplicationStackHelper>();
  if (appPlayer && appPlayer->IsPlaying())
  {
    if (stackHelper && stackHelper->IsPlayingRegularStack())
      rc = stackHelper->GetStackTotalTimeMs() * 0.001;
    else
      rc = appPlayer->GetTotalTime() * 0.001;
  }

  return rc;
}

int CApplicationPlayerInfo::GetAudioDelay()
{
  auto& components = CServiceBroker::GetAppComponents();
  const auto appPlayer = components.GetComponent<CApplicationPlayer>();
  if (!appPlayer)
    return 0;

  // converts audio delay to a percentage
  const auto& advSettings = CServiceBroker::GetSettingsComponent()->GetAdvancedSettings();
  const auto delay = appPlayer->GetVideoSettings().m_AudioDelay;
  const auto range = advSettings->m_videoAudioDelayRange;
  return static_cast<int>(0.5f + (delay + range) / (2.f*range) * 100.0f);
}

int CApplicationPlayerInfo::GetSubtitleDelay()
{
  auto& components = CServiceBroker::GetAppComponents();
  const auto appPlayer = components.GetComponent<CApplicationPlayer>();
  if (!appPlayer)
    return 0;

  // converts subtitle delay to a percentage
  const auto& advSettings = CServiceBroker::GetSettingsComponent()->GetAdvancedSettings();
  const auto delay = appPlayer->GetVideoSettings().m_SubtitleDelay;
  const auto range = advSettings->m_videoSubsDelayRange;
  return static_cast<int>(0.5f + (delay + range) / (2.f*range) * 100.0f);
}

float CApplicationPlayerInfo::GetPercentage() const
{
  auto& components = CServiceBroker::GetAppComponents();
  const auto appPlayer = components.GetComponent<CApplicationPlayer>();
  const auto stackHelper = components.GetComponent<CApplicationStackHelper>();

  if (appPlayer && appPlayer->IsPlaying())
  {
    if (appPlayer->GetTotalTime() == 0 && appPlayer->IsPlayingAudio() &&
        m_cb.CurrentFileItem().HasMusicInfoTag())
    {
      const MUSIC_INFO::CMusicInfoTag& tag = *m_cb.CurrentFileItem().GetMusicInfoTag();
      if (tag.GetDuration() > 0)
        return (float)(GetTime() / tag.GetDuration() * 100);
    }

    if (stackHelper->IsPlayingRegularStack())
    {
      double totalTime = GetTotalTime();
      if (totalTime > 0.0)
        return (float)(GetTime() / totalTime * 100);
    }
    else
      return appPlayer->GetPercentage();
  }
  return 0.0f;
}

float CApplicationPlayerInfo::GetCachePercentage() const
{
  auto& components = CServiceBroker::GetAppComponents();
  const auto appPlayer = components.GetComponent<CApplicationPlayer>();
  const auto stackHelper = components.GetComponent<CApplicationStackHelper>();

  if (appPlayer && appPlayer->IsPlaying())
  {
    // Note that the player returns a relative cache percentage and we want an absolute percentage
    if (stackHelper && stackHelper->IsPlayingRegularStack())
    {
      float stackedTotalTime = static_cast<float>(GetTotalTime());
      // We need to take into account the stack's total time vs. currently playing file's total time
      if (stackedTotalTime > 0.0f)
        return std::min(100.0f, GetPercentage() + (appPlayer->GetCachePercentage() * appPlayer->GetTotalTime() * 0.001f / stackedTotalTime ));
    }
    else
      return std::min( 100.0f, appPlayer->GetPercentage() + appPlayer->GetCachePercentage() );
  }
  return 0.0f;
}

const std::string& CApplicationPlayerInfo::CurrentFile() const
{
  return m_cb.CurrentFileItem().GetPath();
}

const CFileItem& CApplicationPlayerInfo::CurrentFileItem() const
{
  return m_cb.CurrentFileItem();
}

const CFileItem& CApplicationPlayerInfo::CurrentUnstackedItem()
{
  auto& components = CServiceBroker::GetAppComponents();
  const auto stackHelper = components.GetComponent<CApplicationStackHelper>();

  if (stackHelper && (stackHelper->IsPlayingISOStack() ||
                      stackHelper->IsPlayingRegularStack()))
    return stackHelper->GetCurrentStackPartFileItem();
  else
    return m_cb.CurrentFileItem();
}
