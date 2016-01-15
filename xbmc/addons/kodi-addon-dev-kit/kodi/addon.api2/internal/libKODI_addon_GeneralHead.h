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

namespace AddOnLIB
{
namespace V2
{

  typedef char*   _get_addon_info(void* hdl, const char* id);
  typedef bool    _get_setting(void* hdl, const char* settingName, void *settingValue, bool global);
  typedef void    _open_settings_dialog(void* hdl);
  typedef void    _addon_log_msg(void* hdl, const addon_log loglevel, const char *msg);
  typedef void    _queue_notification(void* hdl, const queue_msg type, const char *msg);
  typedef void    _queue_notification_from_type(void* hdl, const queue_msg type, const char* aCaption, const char* aDescription, unsigned int displayTime, bool withSound, unsigned int messageTime);
  typedef void    _queue_notification_with_image(void* hdl, const char* aImageFile, const char* aCaption, const char* aDescription, unsigned int displayTime, bool withSound, unsigned int messageTime);
  typedef void    _get_md5(const char* text, char& md5);
  typedef char*   _unknown_to_utf8(void* hdl, const char* str, bool &ret, bool failOnBadChar);
  typedef char*   _get_localized_string(void* hdl, uint32_t labelId);
  typedef void    _get_language(void* hdl, char& language, unsigned int& iMaxStringSize, int format, bool region);
  typedef void    _get_dvd_menu_language(void* hdl, char &language, unsigned int &iMaxStringSize);
  typedef void    _free_string(void* hdl, char* str);
  typedef bool    _start_server(void* hdl, int typ, bool start, bool wait);
  typedef void    _audio_suspend(void* hdl);
  typedef void    _audio_resume(void* hdl);
  typedef float   _get_volume(void* hdl, bool percentage);
  typedef void    _set_volume(void* hdl, float value, bool isPercentage);
  typedef bool    _is_muted(void* hdl);
  typedef void    _toggle_mute(void* hdl);
  typedef long    _get_optical_state(void* hdl);
  typedef bool    _eject_optical_drive(void* hdl);
  typedef void    _kodi_version(void* hdl, char*& compile_name, int& major, int& minor, char*& revision, char*& tag, char*& tagversion);
  typedef void    _kodi_quit(void* hdl);
  typedef void    _htpc_shutdown(void* hdl);
  typedef void    _htpc_restart(void* hdl);
  typedef void    _execute_script(void* hdl, const char* script);
  typedef void    _execute_builtin(void* hdl, const char* function, bool wait);
  typedef char*   _execute_jsonrpc(void* hdl, const char* jsonrpccommand);
  typedef char*   _get_region(void* hdl, const char* id);
  typedef long    _get_free_mem(void* hdl);
  typedef int     _get_global_idle_time(void* hdl);
  typedef char*   _translate_path(void* hdl, const char* path);

  typedef struct CB_Addon_General
  {
    _get_addon_info*                get_addon_info;
    _get_setting*                   get_setting;
    _open_settings_dialog*          open_settings_dialog;
    _addon_log_msg*                 addon_log_msg;
    _queue_notification*            queue_notification;
    _queue_notification_from_type*  queue_notification_from_type;
    _queue_notification_with_image* queue_notification_with_image;
    _get_md5*                       get_md5;
    _unknown_to_utf8*               unknown_to_utf8;
    _get_localized_string*          get_localized_string;
    _get_language*                  get_language;
    _get_dvd_menu_language*         get_dvd_menu_language;
    _free_string*                   free_string;
    _start_server*                  start_server;
    _audio_suspend*                 audio_suspend;
    _audio_resume*                  audio_resume;
    _get_volume*                    get_volume;
    _set_volume*                    set_volume;
    _is_muted*                      is_muted;
    _toggle_mute*                   toggle_mute;
    _get_optical_state*             get_optical_state;
    _eject_optical_drive*           eject_optical_drive;
    _kodi_version*                  kodi_version;
    _kodi_quit*                     kodi_quit;
    _htpc_shutdown*                 htpc_shutdown;
    _htpc_restart*                  htpc_restart;
    _execute_script*                execute_script;
    _execute_builtin*               execute_builtin;
    _execute_jsonrpc*               execute_jsonrpc;
    _get_region*                    get_region;
    _get_free_mem*                  get_free_mem;
    _get_global_idle_time*          get_global_idle_time;
    _translate_path*                translate_path;
  } CB_AddonLib_General;

}; /* namespace V2 */
}; /* namespace AddOnLIB */
