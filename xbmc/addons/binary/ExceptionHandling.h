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
#include "threads/IThreadCrashProtection.h"

namespace ADDON
{
  XBMCCOMMONS_STANDARD_EXCEPTION(WrongValueException);

  /**
   * UnimplementedException Can be used in places like the control hierarchy
   * where the requirements of dynamic language usage force us to add
   * unimplmenented methods to a class hierarchy. See the detailed explanation
   * on the class Control for more.
   */
  class UnimplementedException : public XbmcCommons::Exception
  {
  public:
    inline UnimplementedException(const UnimplementedException& other) : Exception(other) { }
    inline UnimplementedException(const char* classname, const char* methodname) :
      Exception("UnimplementedException")
    { SetMessage("Unimplemented method: %s::%s(...)", classname, methodname); }
  };

  /**
   * This is what callback exceptions from the scripting language are translated
   * to.
   */
  class UnhandledException : public XbmcCommons::Exception
  {
  public:
    inline UnhandledException(const UnhandledException& other) : Exception(other) { }
    inline UnhandledException(const char* _message,...) : Exception("UnhandledException") { XBMCCOMMONS_COPYVARARGS(_message); }
  };

  class CAddon;

  class CAddonExceptionHandler
  {
  public:
    static void Handle(XbmcThreads::SegFaultException& e, bool onCrashProtectionStart = false);
    static void Handle(const ADDON::WrongValueException& e, bool onCrashProtectionStart = false);
    static void Handle(const ADDON::UnimplementedException e, bool onCrashProtectionStart = false);
    static void Handle(const XbmcCommons::Exception& e, bool onCrashProtectionStart = false);
    static void HandleUnknown(std::string functionName, bool onCrashProtectionStart = false);

  private:
    static void DestroyAddon(CAddon* addon);
  };

/**
 * These macros allow the easy declaration (and definition) of parent class
 * virtual methods that are not implemented until the child class.
 *
 * This is to support the idosyncracies of dynamically typed scripting
 * languages. See the comment in AddonControl.h for more details.
 */
#define THROW_UNIMP(classname) throw ADDON::UnimplementedException(classname, __FUNCTION__)

#define HANDLE_ADDON_EXCEPTION                                       \
  XBMCCOMMONS_HANDLE_UNCHECKED                                       \
  catch (XbmcThreads::SegFaultException& e)                          \
  {                                                                  \
    CAddonExceptionHandler::Handle(e);                               \
  }                                                                  \
  catch (const ADDON::WrongValueException& e)                        \
  {                                                                  \
    CAddonExceptionHandler::Handle(e);                               \
  }                                                                  \
  catch (const ADDON::UnimplementedException& e)                     \
  {                                                                  \
    CAddonExceptionHandler::Handle(e);                               \
  }                                                                  \
  catch (const XbmcCommons::Exception& e)                            \
  {                                                                  \
    CAddonExceptionHandler::Handle(e);                               \
  }                                                                  \
  catch (...)                                                        \
  {                                                                  \
    CAddonExceptionHandler::HandleUnknown(__PRETTY_FUNCTION__);      \
  }

}; /* namespace ADDON */
