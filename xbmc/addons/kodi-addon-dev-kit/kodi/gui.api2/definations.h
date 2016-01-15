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

#ifdef KODI_GUILIB_API_VERSION
#undef KODI_GUILIB_API_VERSION
#endif
#ifdef KODI_GUILIB_MIN_API_VERSION
#undef KODI_GUILIB_MIN_API_VERSION
#endif

#ifdef __cplusplus
namespace GUILIB
{
namespace V2
{
extern "C"
{
#endif

  /*!
   * \ingroup GUILIB
   * @{
   * @brief
   */
static constexpr const int   GUILIB_apiLevel = 2;
static constexpr const char* GUILIB_version  = "5.8.0";

typedef void* GUIHANDLE;

/* current ADDONGUI API version */
#define KODI_GUILIB_API_VERSION "5.8.0"

/* min. ADDONGUI API version */
#define KODI_GUILIB_MIN_API_VERSION "5.8.0"

// flags for text font alignment
typedef enum AddonGUIFontAlignment
{
  ADDON_FONT_LEFT       = 0x00000000,
  ADDON_FONT_RIGHT      = 0x00000001,
  ADDON_FONT_CENTER_X   = 0x00000002,
  ADDON_FONT_CENTER_Y   = 0x00000004,
  ADDON_FONT_TRUNCATED  = 0x00000008,
  ADDON_FONT_JUSTIFIED  = 0x00000010
} AddonGUIFontAlignment;

enum AddonGUIIconOverlay { ADDON_ICON_OVERLAY_NONE = 0,
                           ADDON_ICON_OVERLAY_RAR,
                           ADDON_ICON_OVERLAY_ZIP,
                           ADDON_ICON_OVERLAY_LOCKED,
                           ADDON_ICON_OVERLAY_UNWATCHED,
                           ADDON_ICON_OVERLAY_WATCHED,
                           ADDON_ICON_OVERLAY_HD };

enum AddonGUIInputType   { ADDON_INPUT_TYPE_READONLY = -1,
                           ADDON_INPUT_TYPE_TEXT = 0,
                           ADDON_INPUT_TYPE_NUMBER,
                           ADDON_INPUT_TYPE_SECONDS,
                           ADDON_INPUT_TYPE_TIME,
                           ADDON_INPUT_TYPE_DATE,
                           ADDON_INPUT_TYPE_IPADDRESS,
                           ADDON_INPUT_TYPE_PASSWORD,
                           ADDON_INPUT_TYPE_PASSWORD_MD5,
                           ADDON_INPUT_TYPE_SEARCH,
                           ADDON_INPUT_TYPE_FILTER,
                           ADDON_INPUT_TYPE_PASSWORD_NUMBER_VERIFY_NEW };

///
/// \defgroup kodi_addon_key_action_ids Addon action Id's
/// \ingroup CAddonGUIWindow_callbacks
/// @{
/// @brief Actions that we have defined.
///
enum AddonGUIActionType  { ADDON_ACTION_NONE                    = 0,
                           ADDON_ACTION_MOVE_LEFT               = 1,
                           ADDON_ACTION_MOVE_RIGHT              = 2,
                           ADDON_ACTION_MOVE_UP                 = 3,
                           ADDON_ACTION_MOVE_DOWN               = 4,
                           ADDON_ACTION_PAGE_UP                 = 5,
                           ADDON_ACTION_PAGE_DOWN               = 6,
                           ADDON_ACTION_SELECT_ITEM             = 7,
                           ADDON_ACTION_HIGHLIGHT_ITEM          = 8,
                           ADDON_ACTION_PARENT_DIR              = 9,
                           ADDON_ACTION_PREVIOUS_MENU           = 10,
                           ADDON_ACTION_SHOW_INFO               = 11,

                           ADDON_ACTION_PAUSE                   = 12,
                           ADDON_ACTION_STOP                    = 13,
                           ADDON_ACTION_NEXT_ITEM               = 14,
                           ADDON_ACTION_PREV_ITEM               = 15,
                           ADDON_ACTION_FORWARD                 = 16,   //!< Can be used to specify specific action in a window, Playback control is handled in ACTION_PLAYER_*
                           ADDON_ACTION_REWIND                  = 17,   //!< Can be used to specify specific action in a window, Playback control is handled in ACTION_PLAYER_*

                           ADDON_ACTION_SHOW_GUI                = 18,   //!< toggle between GUI and movie or GUI and visualisation.
                           ADDON_ACTION_ASPECT_RATIO            = 19,   //!< toggle quick-access zoom modes. Can b used in videoFullScreen.zml window id=2005
                           ADDON_ACTION_STEP_FORWARD            = 20,   //!< seek +1% in the movie. Can b used in videoFullScreen.xml window id=2005
                           ADDON_ACTION_STEP_BACK               = 21,   //!< seek -1% in the movie. Can b used in videoFullScreen.xml window id=2005
                           ADDON_ACTION_BIG_STEP_FORWARD        = 22,   //!< seek +10% in the movie. Can b used in videoFullScreen.xml window id=2005
                           ADDON_ACTION_BIG_STEP_BACK           = 23,   //!< seek -10% in the movie. Can b used in videoFullScreen.xml window id=2005
                           ADDON_ACTION_SHOW_OSD                = 24,   //!< show/hide OSD. Can b used in videoFullScreen.xml window id=2005
                           ADDON_ACTION_SHOW_SUBTITLES          = 25,   //!< turn subtitles on/off. Can b used in videoFullScreen.xml window id=2005
                           ADDON_ACTION_NEXT_SUBTITLE           = 26,   //!< switch to next subtitle of movie. Can b used in videoFullScreen.xml window id=2005
                           ADDON_ACTION_SHOW_CODEC              = 27,   //!< show information about file. Can b used in videoFullScreen.xml window id=2005 and in slideshow.xml window id=2007
                           ADDON_ACTION_NEXT_PICTURE            = 28,   //!< show next picture of slideshow. Can b used in slideshow.xml window id=2007
                           ADDON_ACTION_PREV_PICTURE            = 29,   //!< show previous picture of slideshow. Can b used in slideshow.xml window id=2007
                           ADDON_ACTION_ZOOM_OUT                = 30,   //!< zoom in picture during slideshow. Can b used in slideshow.xml window id=2007
                           ADDON_ACTION_ZOOM_IN                 = 31,   //!< zoom out picture during slideshow. Can b used in slideshow.xml window id=2007
                           ADDON_ACTION_TOGGLE_SOURCE_DEST      = 32,   //!< used to toggle between source view and destination view. Can be used in myfiles.xml window id=3
                           ADDON_ACTION_SHOW_PLAYLIST           = 33,   //!< used to toggle between current view and playlist view. Can b used in all mymusic xml files
                           ADDON_ACTION_QUEUE_ITEM              = 34,   //!< used to queue a item to the playlist. Can b used in all mymusic xml files
                           ADDON_ACTION_REMOVE_ITEM             = 35,   //!< not used anymore
                           ADDON_ACTION_SHOW_FULLSCREEN         = 36,   //!< not used anymore
                           ADDON_ACTION_ZOOM_LEVEL_NORMAL       = 37,   //!< zoom 1x picture during slideshow. Can b used in slideshow.xml window id=2007
                           ADDON_ACTION_ZOOM_LEVEL_1            = 38,   //!< zoom 2x picture during slideshow. Can b used in slideshow.xml window id=2007
                           ADDON_ACTION_ZOOM_LEVEL_2            = 39,   //!< zoom 3x picture during slideshow. Can b used in slideshow.xml window id=2007
                           ADDON_ACTION_ZOOM_LEVEL_3            = 40,   //!< zoom 4x picture during slideshow. Can b used in slideshow.xml window id=2007
                           ADDON_ACTION_ZOOM_LEVEL_4            = 41,   //!< zoom 5x picture during slideshow. Can b used in slideshow.xml window id=2007
                           ADDON_ACTION_ZOOM_LEVEL_5            = 42,   //!< zoom 6x picture during slideshow. Can b used in slideshow.xml window id=2007
                           ADDON_ACTION_ZOOM_LEVEL_6            = 43,   //!< zoom 7x picture during slideshow. Can b used in slideshow.xml window id=2007
                           ADDON_ACTION_ZOOM_LEVEL_7            = 44,   //!< zoom 8x picture during slideshow. Can b used in slideshow.xml window id=2007
                           ADDON_ACTION_ZOOM_LEVEL_8            = 45,   //!< zoom 9x picture during slideshow. Can b used in slideshow.xml window id=2007
                           ADDON_ACTION_ZOOM_LEVEL_9            = 46,   //!< zoom 10x picture during slideshow. Can b used in slideshow.xml window id=2007

                           ADDON_ACTION_CALIBRATE_SWAP_ARROWS   = 47,   //!< select next arrow. Can b used in: settingsScreenCalibration.xml windowid=11
                           ADDON_ACTION_CALIBRATE_RESET         = 48,   //!< reset calibration to defaults. Can b used in: settingsScreenCalibration.xml windowid=11/settingsUICalibration.xml windowid=10
                           ADDON_ACTION_ANALOG_MOVE             = 49,   //!< analog thumbstick move. Can b used in: slideshow.xml window id=2007/settingsScreenCalibration.xml windowid=11/settingsUICalibration.xml windowid=10
                           //! see also ACTION_ANALOG_MOVE_X, ACTION_ANALOG_MOVE_Y

                           ADDON_ACTION_ROTATE_PICTURE_CW       = 50,   //!< rotate current picture clockwise during slideshow. Can be used in slideshow.xml window id=2007
                           ADDON_ACTION_ROTATE_PICTURE_CCW      = 51,   //!< rotate current picture counterclockwise during slideshow. Can be used in slideshow.xml window id=2007

                           ADDON_ACTION_SUBTITLE_DELAY_MIN      = 52,   //!< Decrease subtitle/movie Delay.  Can b used in videoFullScreen.xml window id=2005
                           ADDON_ACTION_SUBTITLE_DELAY_PLUS     = 53,   //!< Increase subtitle/movie Delay.  Can b used in videoFullScreen.xml window id=2005
                           ADDON_ACTION_AUDIO_DELAY_MIN         = 54,   //!< Increase avsync delay.  Can b used in videoFullScreen.xml window id=2005
                           ADDON_ACTION_AUDIO_DELAY_PLUS        = 55,   //!< Decrease avsync delay.  Can b used in videoFullScreen.xml window id=2005
                           ADDON_ACTION_AUDIO_NEXT_LANGUAGE     = 56,   //!< Select next language in movie.  Can b used in videoFullScreen.xml window id=2005
                           ADDON_ACTION_CHANGE_RESOLUTION       = 57,   //!< switch 2 next resolution. Can b used during screen calibration settingsScreenCalibration.xml windowid=11

                           ADDON_REMOTE_0                       = 58,   //!< remote keys 0-9. are used by multiple windows
                           ADDON_REMOTE_1                       = 59,   ///  for example in videoFullScreen.xml window id=2005 you can
                           ADDON_REMOTE_2                       = 60,   ///  enter time (mmss) to jump to particular point in the movie
                           ADDON_REMOTE_3                       = 61,   ///
                           ADDON_REMOTE_4                       = 62,   ///  with spincontrols you can enter 3digit number to quickly set
                           ADDON_REMOTE_5                       = 63,   ///  spincontrol to desired value
                           ADDON_REMOTE_6                       = 64,
                           ADDON_REMOTE_7                       = 65,
                           ADDON_REMOTE_8                       = 66,
                           ADDON_REMOTE_9                       = 67,

                           ADDON_ACTION_PLAY                    = 68,   //!< Unused at the moment
                           ADDON_ACTION_SMALL_STEP_BACK         = 76,   //!< jumps a few seconds back during playback of movie. Can b used in videoFullScreen.xml window id=2005

                           ADDON_ACTION_PLAYER_FORWARD          = 77,   //!< FF in current file played. global action, can be used anywhere
                           ADDON_ACTION_PLAYER_REWIND           = 78,   //!< RW in current file played. global action, can be used anywhere
                           ADDON_ACTION_PLAYER_PLAY             = 79,   //!< Play current song. Unpauses song and sets playspeed to 1x. global action, can be used anywhere

                           ADDON_ACTION_DELETE_ITEM             = 80,   //!< delete current selected item. Can be used in myfiles.xml window id=3 and in myvideoTitle.xml window id=25
                           ADDON_ACTION_COPY_ITEM               = 81,   //!< copy current selected item. Can be used in myfiles.xml window id=3
                           ADDON_ACTION_MOVE_ITEM               = 82,   //!< move current selected item. Can be used in myfiles.xml window id=3
                           ADDON_ACTION_TAKE_SCREENSHOT         = 85,   //!< take a screenshot
                           ADDON_ACTION_RENAME_ITEM             = 87,   //!< rename item

                           ADDON_ACTION_VOLUME_UP               = 88,
                           ADDON_ACTION_VOLUME_DOWN             = 89,
                           ADDON_ACTION_VOLAMP                  = 90,
                           ADDON_ACTION_MUTE                    = 91,
                           ADDON_ACTION_NAV_BACK                = 92,
                           ADDON_ACTION_VOLAMP_UP               = 93,
                           ADDON_ACTION_VOLAMP_DOWN             = 94,

                           ADDON_ACTION_CREATE_EPISODE_BOOKMARK = 95,   //!< Creates an episode bookmark on the currently playing video file containing more than one episode
                           ADDON_ACTION_CREATE_BOOKMARK         = 96,   //!< Creates a bookmark of the currently playing video file

                           ADDON_ACTION_CHAPTER_OR_BIG_STEP_FORWARD = 97, //!< Goto the next chapter, if not available perform a big step forward
                           ADDON_ACTION_CHAPTER_OR_BIG_STEP_BACK    = 98, //!< Goto the previous chapter, if not available perform a big step back

                           ADDON_ACTION_CYCLE_SUBTITLE          = 99,   //!< switch to next subtitle of movie, but will not enable/disable the subtitles. Can be used in videoFullScreen.xml window id=2005

                           ADDON_ACTION_MOUSE_LEFT_CLICK        = 100,
                           ADDON_ACTION_MOUSE_RIGHT_CLICK       = 101,
                           ADDON_ACTION_MOUSE_MIDDLE_CLICK      = 102,
                           ADDON_ACTION_MOUSE_DOUBLE_CLICK      = 103,
                           ADDON_ACTION_MOUSE_WHEEL_UP          = 104,
                           ADDON_ACTION_MOUSE_WHEEL_DOWN        = 105,
                           ADDON_ACTION_MOUSE_DRAG              = 106,
                           ADDON_ACTION_MOUSE_MOVE              = 107,
                           ADDON_ACTION_MOUSE_LONG_CLICK        = 108,

                           ADDON_ACTION_BACKSPACE               = 110,
                           ADDON_ACTION_SCROLL_UP               = 111,
                           ADDON_ACTION_SCROLL_DOWN             = 112,
                           ADDON_ACTION_ANALOG_FORWARD          = 113,
                           ADDON_ACTION_ANALOG_REWIND           = 114,

                           ADDON_ACTION_MOVE_ITEM_UP            = 115,   //!< move item up in playlist
                           ADDON_ACTION_MOVE_ITEM_DOWN          = 116,   //!< move item down in playlist
                           ADDON_ACTION_CONTEXT_MENU            = 117,   //!< pops up the context menu

                           //!> stuff for virtual keyboard shortcuts
                           ADDON_ACTION_SHIFT                   = 118,
                           ADDON_ACTION_SYMBOLS                 = 119,
                           ADDON_ACTION_CURSOR_LEFT             = 120,
                           ADDON_ACTION_CURSOR_RIGHT            = 121,

                           ADDON_ACTION_BUILT_IN_FUNCTION       = 122,

                           ADDON_ACTION_SHOW_OSD_TIME           = 123,   //!< displays current time, can be used in videoFullScreen.xml window id=2005
                           ADDON_ACTION_ANALOG_SEEK_FORWARD     = 124,   //!< seeks forward, and displays the seek bar.
                           ADDON_ACTION_ANALOG_SEEK_BACK        = 125,   //!< seeks backward, and displays the seek bar.

                           ADDON_ACTION_VIS_PRESET_SHOW         = 126,
                           ADDON_ACTION_VIS_PRESET_NEXT         = 128,
                           ADDON_ACTION_VIS_PRESET_PREV         = 129,
                           ADDON_ACTION_VIS_PRESET_LOCK         = 130,
                           ADDON_ACTION_VIS_PRESET_RANDOM       = 131,
                           ADDON_ACTION_VIS_RATE_PRESET_PLUS    = 132,
                           ADDON_ACTION_VIS_RATE_PRESET_MINUS   = 133,

                           ADDON_ACTION_SHOW_VIDEOMENU          = 134,
                           ADDON_ACTION_ENTER                   = 135,

                           ADDON_ACTION_INCREASE_RATING         = 136,
                           ADDON_ACTION_DECREASE_RATING         = 137,

                           ADDON_ACTION_NEXT_SCENE              = 138,   //!< switch to next scene/cutpoint in movie
                           ADDON_ACTION_PREV_SCENE              = 139,   //!< switch to previous scene/cutpoint in movie

                           ADDON_ACTION_NEXT_LETTER             = 140,   //!< jump through a list or container by letter
                           ADDON_ACTION_PREV_LETTER             = 141,

                           ADDON_ACTION_JUMP_SMS2               = 142,   //!< jump direct to a particular letter using SMS-style input
                           ADDON_ACTION_JUMP_SMS3               = 143,
                           ADDON_ACTION_JUMP_SMS4               = 144,
                           ADDON_ACTION_JUMP_SMS5               = 145,
                           ADDON_ACTION_JUMP_SMS6               = 146,
                           ADDON_ACTION_JUMP_SMS7               = 147,
                           ADDON_ACTION_JUMP_SMS8               = 148,
                           ADDON_ACTION_JUMP_SMS9               = 149,

                           ADDON_ACTION_FILTER_CLEAR            = 150,
                           ADDON_ACTION_FILTER_SMS2             = 151,
                           ADDON_ACTION_FILTER_SMS3             = 152,
                           ADDON_ACTION_FILTER_SMS4             = 153,
                           ADDON_ACTION_FILTER_SMS5             = 154,
                           ADDON_ACTION_FILTER_SMS6             = 155,
                           ADDON_ACTION_FILTER_SMS7             = 156,
                           ADDON_ACTION_FILTER_SMS8             = 157,
                           ADDON_ACTION_FILTER_SMS9             = 158,

                           ADDON_ACTION_FIRST_PAGE              = 159,
                           ADDON_ACTION_LAST_PAGE               = 160,

                           ADDON_ACTION_AUDIO_DELAY             = 161,
                           ADDON_ACTION_SUBTITLE_DELAY          = 162,
                           ADDON_ACTION_MENU                    = 163,

                           ADDON_ACTION_RECORD                  = 170,

                           ADDON_ACTION_PASTE                   = 180,
                           ADDON_ACTION_NEXT_CONTROL            = 181,
                           ADDON_ACTION_PREV_CONTROL            = 182,
                           ADDON_ACTION_CHANNEL_SWITCH          = 183,
                           ADDON_ACTION_CHANNEL_UP              = 184,
                           ADDON_ACTION_CHANNEL_DOWN            = 185,
                           ADDON_ACTION_NEXT_CHANNELGROUP       = 186,
                           ADDON_ACTION_PREVIOUS_CHANNELGROUP   = 187,
                           ADDON_ACTION_PVR_PLAY                = 188,
                           ADDON_ACTION_PVR_PLAY_TV             = 189,
                           ADDON_ACTION_PVR_PLAY_RADIO          = 190,

                           ADDON_ACTION_TOGGLE_FULLSCREEN       = 199,   //!< switch 2 desktop resolution
                           ADDON_ACTION_TOGGLE_WATCHED          = 200,   //!< Toggle watched status (videos)
                           ADDON_ACTION_SCAN_ITEM               = 201,   //!< scan item
                           ADDON_ACTION_TOGGLE_DIGITAL_ANALOG   = 202,   //!< switch digital <-> analog
                           ADDON_ACTION_RELOAD_KEYMAPS          = 203,   //!< reloads CButtonTranslator's keymaps
                           ADDON_ACTION_GUIPROFILE_BEGIN        = 204,   //!< start the GUIControlProfiler running

                           ADDON_ACTION_TELETEXT_RED            = 215,   //!< Teletext Color buttons to control TopText
                           ADDON_ACTION_TELETEXT_GREEN          = 216,   //!<    "       "      "    "     "       "
                           ADDON_ACTION_TELETEXT_YELLOW         = 217,   //!<    "       "      "    "     "       "
                           ADDON_ACTION_TELETEXT_BLUE           = 218,   //!<    "       "      "    "     "       "

                           ADDON_ACTION_INCREASE_PAR            = 219,
                           ADDON_ACTION_DECREASE_PAR            = 220,

                           ADDON_ACTION_VSHIFT_UP               = 227,   //!< shift up video image in DVDPlayer
                           ADDON_ACTION_VSHIFT_DOWN             = 228,   //!< shift down video image in DVDPlayer

                           ADDON_ACTION_PLAYER_PLAYPAUSE        = 229,   //!< Play/pause. If playing it pauses, if paused it plays.

                           ADDON_ACTION_SUBTITLE_VSHIFT_UP      = 230,   //!< shift up subtitles in DVDPlayer
                           ADDON_ACTION_SUBTITLE_VSHIFT_DOWN    = 231,   //!< shift down subtitles in DVDPlayer
                           ADDON_ACTION_SUBTITLE_ALIGN          = 232,   //!< toggle vertical alignment of subtitles

                           ADDON_ACTION_FILTER                  = 233,

                           ADDON_ACTION_SWITCH_PLAYER           = 234,

                           ADDON_ACTION_STEREOMODE_NEXT         = 235,
                           ADDON_ACTION_STEREOMODE_PREVIOUS     = 236,
                           ADDON_ACTION_STEREOMODE_TOGGLE       = 237,   //!< turns 3d mode on/off
                           ADDON_ACTION_STEREOMODE_SELECT       = 238,
                           ADDON_ACTION_STEREOMODE_TOMONO       = 239,
                           ADDON_ACTION_STEREOMODE_SET          = 240,

                           ADDON_ACTION_SETTINGS_RESET          = 241,
                           ADDON_ACTION_SETTINGS_LEVEL_CHANGE   = 242,

                           ADDON_ACTION_TRIGGER_OSD             = 243,   //!< show autoclosing OSD. Can b used in videoFullScreen.xml window id=2005
                           ADDON_ACTION_INPUT_TEXT              = 244,
                           ADDON_ACTION_VOLUME_SET              = 245,

                           //!> touch actions
                           ADDON_ACTION_TOUCH_TAP               = 401,
                           ADDON_ACTION_TOUCH_TAP_TEN           = 410,
                           ADDON_ACTION_TOUCH_LONGPRESS         = 411,
                           ADDON_ACTION_TOUCH_LONGPRESS_TEN     = 420,

                           ADDON_ACTION_GESTURE_NOTIFY          = 500,
                           ADDON_ACTION_GESTURE_BEGIN           = 501,
                           ADDON_ACTION_GESTURE_ZOOM            = 502,   //!< sendaction with point and currentPinchScale (fingers together < 1.0 -> fingers apart > 1.0)
                           ADDON_ACTION_GESTURE_ROTATE          = 503,
                           ADDON_ACTION_GESTURE_PAN             = 504,

                           ADDON_ACTION_GESTURE_SWIPE_LEFT      = 511,
                           ADDON_ACTION_GESTURE_SWIPE_LEFT_TEN  = 520,
                           ADDON_ACTION_GESTURE_SWIPE_RIGHT     = 521,
                           ADDON_ACTION_GESTURE_SWIPE_RIGHT_TEN = 530,
                           ADDON_ACTION_GESTURE_SWIPE_UP        = 531,
                           ADDON_ACTION_GESTURE_SWIPE_UP_TEN    = 540,
                           ADDON_ACTION_GESTURE_SWIPE_DOWN      = 541,
                           ADDON_ACTION_GESTURE_SWIPE_DOWN_TEN  = 550,

                           //!> other, non-gesture actions

                           ADDON_ACTION_ANALOG_MOVE_X           = 601,   //!< analog thumbstick move, horizontal axis; see ACTION_ANALOG_MOVE
                           ADDON_ACTION_ANALOG_MOVE_Y           = 602,   //!< analog thumbstick move, vertical axis; see ACTION_ANALOG_MOVE

                           //!> The NOOP action can be specified to disable an input event. This is
                           ///  useful in user keyboard.xml etc to disable actions specified in the
                           ///  system mappings. ERROR action is used to play an error sound
                           ADDON_ACTION_ERROR           = 998,
                           ADDON_ACTION_NOOP            = 999 };
//@}
/*@}*/

#ifdef __cplusplus
}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
#if defined(BUILD_KODI_ADDON)
  using namespace GUILIB::V2;
#endif
#endif
