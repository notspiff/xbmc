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

#include "PlatformDefs.h" // for __stat64, ssize_t
#include "addons/kodi-addon-dev-kit/kodi/addon.api2/AddonLib.h"

extern "C"
{
namespace AddOnLIB
{
namespace V2
{

  class CAddonCB_General
  {
  public:
    CAddonCB_General();

    void Init(CB_AddOnLib *callbacks);

    static char* get_addon_info(
          void*                     hdl,
          const char*               id);

    static void addon_log_msg(
          void*                     hdl,
          const addon_log           addonLogLevel,
          const char*               strMessage);

    static void queue_notification(
          void*                     hdl,
          const queue_msg           type,
          const char*               strMessage);

    static bool get_setting(
          void*                     hdl,
          const char*               strSettingName,
          void*                     settingValue,
          bool                      global);

    static void open_settings_dialog(
          void*                     hdl);

    static void queue_notification_from_type(
          void*                     hdl,
          const queue_msg           type,
          const char*               aCaption,
          const char*               aDescription,
          unsigned int              displayTime,
          bool                      withSound,
          unsigned int              messageTime);

    static void queue_notification_with_image(
          void*                     hdl,
          const char*               aImageFile,
          const char*               aCaption,
          const char*               aDescription,
          unsigned int              displayTime,
          bool                      withSound,
          unsigned int              messageTime);

    static void get_md5(
          const char*               text,
          char&                     md5);

    static char* unknown_to_utf8(
          void*                     hdl,
          const char*               strSource,
          bool&                     ret,
          bool                      failOnBadChar);

    static char* get_localized_string(
          void*                     hdl,
          uint32_t                  labelId);

    static void get_language(
          void*                     hdl,
          char&                     language,
          unsigned int&             iMaxStringSize,
          int                       format,
          bool                      region);

    static void get_dvd_menu_language(
          void*                     hdl,
          char&                     language,
          unsigned int&             iMaxStringSize);

    static void free_string(
          void*                     hdl,
          char*                     str);

    static bool start_server(
          void*                     hdl,
          int                       iTyp,
          bool                      bStart,
          bool                      bWait);

    static void audio_suspend(
          void*                     hdl);

    static void audio_resume(
          void*                     hdl);

    static float get_volume(
          void*                     hdl,
          bool                      percentage);

    static void set_volume(
          void*                     hdl,
          float                     value,
          bool                      isPercentage);

    static bool is_muted(
          void*                     hdl);

    static void toggle_mute(
          void*                     hdl);

    static void enable_nav_sounds(
          void*                     hdl,
          bool                      yesNo);

    static long get_optical_state(
          void*                     hdl);

    static bool eject_optical_drive(
          void*                     hdl);

    static void kodi_version(
          void*                     hdl,
          char*&                    compile_name,
          int&                      major,
          int&                      minor,
          char*&                    revision,
          char*&                    tag,
          char*&                    tagversion);

    static void kodi_quit(
          void*                     hdl);

    static void htpc_shutdown(
          void*                     hdl);

    static void htpc_restart(
          void*                     hdl);

    static void execute_script(
          void*                     hdl,
          const char*               script);

    static void execute_builtin(
          void*                     hdl,
          const char*               function,
          bool                      wait);

    static char* execute_jsonrpc(
          void*                     hdl,
          const char*               jsonrpccommand);

    static char* get_region(
          void*                     hdl,
          const char*               id);

    static long get_free_mem(
          void*                     hdl);

    static int get_global_idle_time(
          void*                     hdl);

    static char* translate_path(
          void*                     hdl,
          const char*               path);
  };

}; /* namespace V2 */
}; /* namespace AddOnLIB */
}; /* extern "C" */
