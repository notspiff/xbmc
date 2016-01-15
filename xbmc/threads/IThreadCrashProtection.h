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

#include "utils/log.h"
#include "commons/Exception.h"

class CThread;
class IThreadCrashProtection;

namespace XbmcThreads
{
  class SegFaultException : public XbmcCommons::Exception
  {
  public:
    inline SegFaultException(const SegFaultException& other) : Exception(other) { }
    inline SegFaultException(int signum, IThreadCrashProtection* crashProtection, const char* _message, ...)
      : Exception("SegFaultException"),
        m_signum(signum),
        m_crashProtection(crashProtection)
    {
      XBMCCOMMONS_COPYVARARGS(_message);
    }
    inline int GetSigNum() const { return m_signum; }
    inline IThreadCrashProtection* GetCrashProtection() { return m_crashProtection; }

  private:
    int m_signum;
    IThreadCrashProtection *m_crashProtection;
  };
};

class IThreadCrashProtection
{
public:
  IThreadCrashProtection() {}
  virtual ~IThreadCrashProtection() {}

  virtual void HandleCrashProtection(int signum, CThread* thread)
  {

  }
};
