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
/// \addtogroup kodi_addon_key_action_ids Addon action Id's
/// @{
/// @brief Actions that we have defined.
///
///
enum AddonGUIActionType  { ADDON_ACTION_NONE                    = 0,    //!<
                           /// Action string: <b><c>Left</c></b>
                           ADDON_ACTION_MOVE_LEFT               = 1,    //!< Move left off a control.
                           /// Action string: <b><c>Right</c></b>
                           ADDON_ACTION_MOVE_RIGHT              = 2,    //!< Move right off a control.
                           /// Action string: <b><c>Up</c></b>
                           ADDON_ACTION_MOVE_UP                 = 3,    //!< Move up off a control.
                           /// Action string: <b><c>Down</c></b>
                           ADDON_ACTION_MOVE_DOWN               = 4,    //!< Move down off a control.
                           /// Action string: <b><c>PageUp</c></b>
                           ADDON_ACTION_PAGE_UP                 = 5,    //!< Scroll up on page in a list, thumb, or text view.
                           /// Action string: <b><c>PageDown</c></b>
                           ADDON_ACTION_PAGE_DOWN               = 6,    //!< Scroll down on page in a list, thumb, or text view.
                           /// Action string: <b><c>Select</c></b>
                           ADDON_ACTION_SELECT_ITEM             = 7,    //!< Select a button, or an item from a list of thumb view.
                           /// Action string: <b><c>Highlight</c></b>
                           ADDON_ACTION_HIGHLIGHT_ITEM          = 8,    //!< Highlight an item in a list or thumb view.
                           /// Action string: <b><c>ParentDir</c></b>
                           ADDON_ACTION_PARENT_DIR              = 9,    //!< Go up a folder to the parent folder.
                           /// Action string: <b><c>PreviousMenu</c></b>
                           ADDON_ACTION_PREVIOUS_MENU           = 10,   //!< Go back to the previous menu screen.
                           /// Action string: <b><c>Info</c></b>
                           ADDON_ACTION_SHOW_INFO               = 11,   //!< Show the information about the currently highlighted item, or currently playing item.

                           /// Action string: <b><c>Pause</c></b>
                           ADDON_ACTION_PAUSE                   = 12,   //!< Pause the currently playing item.
                           /// Action string: <b><c>Stop</c></b>
                           ADDON_ACTION_STOP                    = 13,   //!< Stop the currently playing item.
                           /// Action string: <b><c>SkipNext</c></b>
                           ADDON_ACTION_NEXT_ITEM               = 14,   //!< Skip to next video in playlist. If no playlist, then skip to next chapter in video
                           /// Action string: <b><c>SkipPrevious</c></b>
                           ADDON_ACTION_PREV_ITEM               = 15,   //!< Skip to previous video in playlist. If no playlist, then skip to previous chapter in video.
                           ADDON_ACTION_FORWARD                 = 16,   //!< Can be used to specify specific action in a window, Playback control is handled in ACTION_PLAYER_*
                           ADDON_ACTION_REWIND                  = 17,   //!< Can be used to specify specific action in a window, Playback control is handled in ACTION_PLAYER_*

                           /// Action string: <b><c>Fullscreen</c></b>
                           ADDON_ACTION_SHOW_GUI                = 18,   //!< toggle between GUI and movie or GUI and visualisation.
                           /// Action string: <b><c>AspectRatio</c></b>
                           ADDON_ACTION_ASPECT_RATIO            = 19,   //!< toggle quick-access zoom modes. Can b used in videoFullScreen.zml window id=2005
                           /// Action string: <b><c>StepForward</c></b>
                           ADDON_ACTION_STEP_FORWARD            = 20,   //!< seek +1% in the movie. Can b used in videoFullScreen.xml window id=2005
                           /// Action string: <b><c>StepBack</c></b>
                           ADDON_ACTION_STEP_BACK               = 21,   //!< seek -1% in the movie. Can b used in videoFullScreen.xml window id=2005
                           /// Action string: <b><c>BigStepForward</c></b>
                           ADDON_ACTION_BIG_STEP_FORWARD        = 22,   //!< seek +10% in the movie. Can b used in videoFullScreen.xml window id=2005
                           /// Action string: <b><c>BigStepBack</c></b>
                           ADDON_ACTION_BIG_STEP_BACK           = 23,   //!< seek -10% in the movie. Can b used in videoFullScreen.xml window id=2005
                           /// Action string: <b><c>OSD</c></b>
                           ADDON_ACTION_SHOW_OSD                = 24,   //!< show/hide OSD. Can b used in videoFullScreen.xml window id=2005
                           /// Action string: <b><c>ShowSubtitles</c></b>
                           ADDON_ACTION_SHOW_SUBTITLES          = 25,   //!< turn subtitles on/off. Can b used in videoFullScreen.xml window id=2005
                           /// Action string: <b><c>NextSubtitle</c></b>
                           ADDON_ACTION_NEXT_SUBTITLE           = 26,   //!< switch to next subtitle of movie. Can b used in videoFullScreen.xml window id=2005
                           /// Action string: <b><c>CodecInfo</c></b>
                           ADDON_ACTION_SHOW_CODEC              = 27,   //!< show information about file. Can b used in videoFullScreen.xml window id=2005 and in slideshow.xml window id=2007
                           /// Action string: <b><c>NextPicture</c></b>
                           ADDON_ACTION_NEXT_PICTURE            = 28,   //!< show next picture of slideshow. Can b used in slideshow.xml window id=2007
                           /// Action string: <b><c>PreviousPicture</c></b>
                           ADDON_ACTION_PREV_PICTURE            = 29,   //!< show previous picture of slideshow. Can b used in slideshow.xml window id=2007
                           /// Action string: <b><c>ZoomOut</c></b>
                           ADDON_ACTION_ZOOM_OUT                = 30,   //!< zoom in picture during slideshow. Can b used in slideshow.xml window id=2007
                           /// Action string: <b><c>ZoomIn</c></b>
                           ADDON_ACTION_ZOOM_IN                 = 31,   //!< zoom out picture during slideshow. Can b used in slideshow.xml window id=2007
                           ADDON_ACTION_TOGGLE_SOURCE_DEST      = 32,   //!< used to toggle between source view and destination view. Can be used in myfiles.xml window id=3
                           /// Action string: <b><c>Playlist</c></b>
                           ADDON_ACTION_SHOW_PLAYLIST           = 33,   //!< used to toggle between current view and playlist view. Can b used in all mymusic xml files
                           /// Action string: <b><c>Queue</c></b>
                           ADDON_ACTION_QUEUE_ITEM              = 34,   //!< used to queue a item to the playlist. Can b used in all mymusic xml files
                           ADDON_ACTION_REMOVE_ITEM             = 35,   //!< not used anymore
                           ADDON_ACTION_SHOW_FULLSCREEN         = 36,   //!< not used anymore
                           /// Action string: <b><c>ZoomNormal</c></b>
                           ADDON_ACTION_ZOOM_LEVEL_NORMAL       = 37,   //!< Zoom 1x picture during slideshow. Can b used in slideshow.xml window id=2007
                           /// Action string: <b><c>ZoomLevel1</c></b>
                           ADDON_ACTION_ZOOM_LEVEL_1            = 38,   //!< Zoom 2x picture during slideshow. Can b used in slideshow.xml window id=2007
                           /// Action string: <b><c>ZoomLevel2</c></b>
                           ADDON_ACTION_ZOOM_LEVEL_2            = 39,   //!< Zoom 3x picture during slideshow. Can b used in slideshow.xml window id=2007
                           /// Action string: <b><c>ZoomLevel3</c></b>
                           ADDON_ACTION_ZOOM_LEVEL_3            = 40,   //!< Zoom 4x picture during slideshow. Can b used in slideshow.xml window id=2007
                           /// Action string: <b><c>ZoomLevel4</c></b>
                           ADDON_ACTION_ZOOM_LEVEL_4            = 41,   //!< Zoom 5x picture during slideshow. Can b used in slideshow.xml window id=2007
                           /// Action string: <b><c>ZoomLevel5</c></b>
                           ADDON_ACTION_ZOOM_LEVEL_5            = 42,   //!< Zoom 6x picture during slideshow. Can b used in slideshow.xml window id=2007
                           /// Action string: <b><c>ZoomLevel6</c></b>
                           ADDON_ACTION_ZOOM_LEVEL_6            = 43,   //!< Zoom 7x picture during slideshow. Can b used in slideshow.xml window id=2007
                           /// Action string: <b><c>ZoomLevel7</c></b>
                           ADDON_ACTION_ZOOM_LEVEL_7            = 44,   //!< Zoom 8x picture during slideshow. Can b used in slideshow.xml window id=2007
                           /// Action string: <b><c>ZoomLevel8</c></b>
                           ADDON_ACTION_ZOOM_LEVEL_8            = 45,   //!< Zoom 9x picture during slideshow. Can b used in slideshow.xml window id=2007
                           /// Action string: <b><c>ZoomLevel9</c></b>
                           ADDON_ACTION_ZOOM_LEVEL_9            = 46,   //!< Zoom 10x picture during slideshow. Can b used in slideshow.xml window id=2007

                           /// Action string: <b><c>NextCalibration</c></b>
                           ADDON_ACTION_CALIBRATE_SWAP_ARROWS   = 47,   //!< select next arrow. Can b used in: settingsScreenCalibration.xml windowid=11
                           /// Action string: <b><c>ResetCalibration</c></b>
                           ADDON_ACTION_CALIBRATE_RESET         = 48,   //!< reset calibration to defaults. Can b used in: settingsScreenCalibration.xml windowid=11/settingsUICalibration.xml windowid=10
                           /// Action string: <b><c>AnalogMove</c></b>
                           ADDON_ACTION_ANALOG_MOVE             = 49,   //!< analog thumbstick move. Can b used in: slideshow.xml window id=2007/settingsScreenCalibration.xml windowid=11/settingsUICalibration.xml windowid=10
                           //! see also ACTION_ANALOG_MOVE_X, ACTION_ANALOG_MOVE_Y

                           /// Action string: <b><c>Rotate</c></b>
                           ADDON_ACTION_ROTATE_PICTURE_CW       = 50,   //!< rotate current picture clockwise during slideshow. Can be used in slideshow.xml window id=2007
                           /// Action string: <b><c>RotateCCW</c></b>
                           ADDON_ACTION_ROTATE_PICTURE_CCW      = 51,   //!< rotate current picture counterclockwise during slideshow. Can be used in slideshow.xml window id=2007

                           /// Action string: <b><c>SubtitleDelayMin</c></b>
                           ADDON_ACTION_SUBTITLE_DELAY_MIN      = 52,   //!< Decrease subtitle/movie Delay.  Can b used in videoFullScreen.xml window id=2005
                           /// Action string: <b><c>SubtitleDelayPlus</c></b>
                           ADDON_ACTION_SUBTITLE_DELAY_PLUS     = 53,   //!< Increase subtitle/movie Delay.  Can b used in videoFullScreen.xml window id=2005
                           /// Action string: <b><c>AudioDelayMinus</c></b>
                           ADDON_ACTION_AUDIO_DELAY_MIN         = 54,   //!< Increase avsync delay.  Can b used in videoFullScreen.xml window id=2005
                           /// Action string: <b><c>AudioDelayPlus</c></b>
                           ADDON_ACTION_AUDIO_DELAY_PLUS        = 55,   //!< Decrease avsync delay.  Can b used in videoFullScreen.xml window id=2005
                           /// Action string: <b><c>AudioNextLanguage</c></b>
                           ADDON_ACTION_AUDIO_NEXT_LANGUAGE     = 56,   //!< Select next language in movie.  Can b used in videoFullScreen.xml window id=2005
                           /// Action string: <b><c>NextResolution</c></b>
                           ADDON_ACTION_CHANGE_RESOLUTION       = 57,   //!< switch 2 next resolution. Can b used during screen calibration settingsScreenCalibration.xml windowid=11

                           /// Action string: <b><c>Number0</c></b>
                           ADDON_REMOTE_0                       = 58,   //!< remote keys 0-9. are used by multiple windows
                           /// Action string: <b><c>Number1</c></b>
                           ADDON_REMOTE_1                       = 59,   ///  for example in videoFullScreen.xml window id=2005 you can
                           /// Action string: <b><c>Number2</c></b>
                           ADDON_REMOTE_2                       = 60,   ///  enter time (mmss) to jump to particular point in the movie
                           /// Action string: <b><c>Number3</c></b>
                           ADDON_REMOTE_3                       = 61,   ///
                           /// Action string: <b><c>Number4</c></b>
                           ADDON_REMOTE_4                       = 62,   ///  with spincontrols you can enter 3digit number to quickly set
                           /// Action string: <b><c>Number5</c></b>
                           ADDON_REMOTE_5                       = 63,   ///  spincontrol to desired value
                           /// Action string: <b><c>Number6</c></b>
                           ADDON_REMOTE_6                       = 64,
                           /// Action string: <b><c>Number7</c></b>
                           ADDON_REMOTE_7                       = 65,
                           /// Action string: <b><c>Number8</c></b>
                           ADDON_REMOTE_8                       = 66,
                           /// Action string: <b><c>Number9</c></b>
                           ADDON_REMOTE_9                       = 67,

                           ADDON_ACTION_PLAY                    = 68,   //!< Unused at the moment
                           /// Action string: <b><c>SmallStepBack</c></b>
                           ADDON_ACTION_SMALL_STEP_BACK         = 76,   //!< jumps a few seconds back during playback of movie. Can b used in videoFullScreen.xml window id=2005

                           /// Action string: <b><c>FastForward</c></b>
                           ADDON_ACTION_PLAYER_FORWARD          = 77,   //!< FF in current file played. global action, can be used anywhere
                           /// Action string: <b><c>Rewind</c></b>
                           ADDON_ACTION_PLAYER_REWIND           = 78,   //!< RW in current file played. global action, can be used anywhere
                           /// Action string: <b><c>Play</c></b>
                           ADDON_ACTION_PLAYER_PLAY             = 79,   //!< Play current song. Unpauses song and sets playspeed to 1x. global action, can be used anywhere

                           /// Action string: <b><c>Delete</c></b>
                           ADDON_ACTION_DELETE_ITEM             = 80,   //!< delete current selected item. Can be used in myfiles.xml window id=3 and in myvideoTitle.xml window id=25
                           /// Action string: <b><c>Copy</c></b>
                           ADDON_ACTION_COPY_ITEM               = 81,   //!< copy current selected item. Can be used in myfiles.xml window id=3
                           /// Action string: <b><c>Move</c></b>
                           ADDON_ACTION_MOVE_ITEM               = 82,   //!< move current selected item. Can be used in myfiles.xml window id=3
                           /// Action string: <b><c>Sreenshot</c></b>
                           ADDON_ACTION_TAKE_SCREENSHOT         = 85,   //!< take a screenshot
                           /// Action string: <b><c>Rename</c></b>
                           ADDON_ACTION_RENAME_ITEM             = 87,   //!< rename item

                           /// Action string: <b><c>VolumeUp</c></b>
                           ADDON_ACTION_VOLUME_UP               = 88,   //!< Increase the volume of playback.
                           /// Action string: <b><c>VolumeDown</c></b>
                           ADDON_ACTION_VOLUME_DOWN             = 89,   //!< Decrease the volume of playback.
                           /// Action string: <b><c>VolumeAmplification</c></b>
                           ADDON_ACTION_VOLAMP                  = 90,   //!<
                           /// Action string: <b><c>Mute</c></b>
                           ADDON_ACTION_MUTE                    = 91,   //!< Mute the volume.
                           /// Action string: <b><c>ParentDir</c></b>
                           ADDON_ACTION_NAV_BACK                = 92,   //!< Go back in navigation.
                           /// Action string: <b><c>VolAmpUp</c></b>
                           ADDON_ACTION_VOLAMP_UP               = 93,   //!<
                           /// Action string: <b><c>VolAmpDown</c></b>
                           ADDON_ACTION_VOLAMP_DOWN             = 94,   //!<

                           /// Action string: <b><c>CreateEpisodeBookmark</c></b>
                           ADDON_ACTION_CREATE_EPISODE_BOOKMARK = 95,   //!< Creates an episode bookmark on the currently playing video file containing more than one episode
                           /// Action string: <b><c>CreateBookmark</c></b>
                           ADDON_ACTION_CREATE_BOOKMARK         = 96,   //!< Creates a bookmark of the currently playing video file

                           /// Action string: <b><c>ChapterOrBigStepForward</c></b>
                           ADDON_ACTION_CHAPTER_OR_BIG_STEP_FORWARD = 97, //!< Goto the next chapter, if not available perform a big step forward
                           /// Action string: <b><c></c>ChapterOrBigStepBack</b>
                           ADDON_ACTION_CHAPTER_OR_BIG_STEP_BACK    = 98, //!< Goto the previous chapter, if not available perform a big step back

                           /// Action string: <b><c>CycleSubtitle</c></b>
                           ADDON_ACTION_CYCLE_SUBTITLE          = 99,    //!< switch to next subtitle of movie, but will not enable/disable the subtitles. Can be used in videoFullScreen.xml window id=2005

                           /// Action string: <b><c>LeftClick</c></b>
                           ADDON_ACTION_MOUSE_LEFT_CLICK        = 100,   //!<
                           /// Action string: <b><c>RightClick</c></b>
                           ADDON_ACTION_MOUSE_RIGHT_CLICK       = 101,   //!<
                           /// Action string: <b><c>MiddleClick</c></b>
                           ADDON_ACTION_MOUSE_MIDDLE_CLICK      = 102,   //!<
                           /// Action string: <b><c>DoubleClick</c></b>
                           ADDON_ACTION_MOUSE_DOUBLE_CLICK      = 103,   //!<
                           /// Action string: <b><c>WheelUp</c></b>
                           ADDON_ACTION_MOUSE_WHEEL_UP          = 104,   //!<
                           /// Action string: <b><c>WheelDown</c></b>
                           ADDON_ACTION_MOUSE_WHEEL_DOWN        = 105,   //!<
                           /// Action string: <b><c>MouseDrag</c></b>
                           ADDON_ACTION_MOUSE_DRAG              = 106,   //!<
                           /// Action string: <b><c>MouseMove</c></b>
                           ADDON_ACTION_MOUSE_MOVE              = 107,   //!<
                           /// Action string: <b><c>LongClick</c></b>
                           ADDON_ACTION_MOUSE_LONG_CLICK        = 108,   //!<

                           /// Action string: <b><c>Backspace</c></b>
                           ADDON_ACTION_BACKSPACE               = 110,   //!< Used in the virtual keyboards to delete one letter.
                           /// Action string: <b><c>ScrollUp</c></b>
                           ADDON_ACTION_SCROLL_UP               = 111,   //!< Variable speed scroll up for analog keys (stick or triggers)
                           /// Action string: <b><c>ScrollDown</c></b>
                           ADDON_ACTION_SCROLL_DOWN             = 112,   //!< Variable speed scroll down for analog keys (stick or triggers)
                           /// Action string: <b><c>AnalogFastForward</c></b>
                           ADDON_ACTION_ANALOG_FORWARD          = 113,   //!<
                           /// Action string: <b><c>AnalogRewind</c></b>
                           ADDON_ACTION_ANALOG_REWIND           = 114,   //!< Variable speed rewind for analog keys (stick or triggers)

                           /// Action string: <b><c>MoveItemUp</c></b>
                           ADDON_ACTION_MOVE_ITEM_UP            = 115,   //!< move item up in playlist
                           /// Action string: <b><c>MoveItemDown</c></b>
                           ADDON_ACTION_MOVE_ITEM_DOWN          = 116,   //!< move item down in playlist
                           /// Action string: <b><c>ContextMenu</c></b>
                           ADDON_ACTION_CONTEXT_MENU            = 117,   //!< pops up the context menu

                           /// Action string: <b><c>Shift</c></b>
                           ADDON_ACTION_SHIFT                   = 118,   //!< Used in Virtual Keyboard to switch to upper or lower case letters
                           /// Action string: <b><c>Symbols</c></b>
                           ADDON_ACTION_SYMBOLS                 = 119,   //!< Used in Virtual Keyboard to switch to or from symbols mode
                           /// Action string: <b><c>CursorLeft</c></b>
                           ADDON_ACTION_CURSOR_LEFT             = 120,   //!< Used in Virtual Keyboard to move the current cursor point to the left
                           /// Action string: <b><c>CursorRight</c></b>
                           ADDON_ACTION_CURSOR_RIGHT            = 121,   //!< Used in Virtual Keyboard to move the current cursor point to the right

                           ADDON_ACTION_BUILT_IN_FUNCTION       = 122,   //!<

                           /// Action string: <b><c>ShowTime</c></b>
                           ADDON_ACTION_SHOW_OSD_TIME           = 123,   //!< displays current time, can be used in videoFullScreen.xml window id=2005
                           /// Action string: <b><c>AnalogSeekForward</c></b>
                           ADDON_ACTION_ANALOG_SEEK_FORWARD     = 124,   //!< seeks forward, and displays the seek bar.
                           /// Action string: <b><c>AnalogSeekBack</c></b>
                           ADDON_ACTION_ANALOG_SEEK_BACK        = 125,   //!< seeks backward, and displays the seek bar.

                           /// Action string: <b><c>ShowPreset</c></b>
                           ADDON_ACTION_VIS_PRESET_SHOW         = 126,   //!< Shows the current visualisation preset (milkdrop/spectrum)
                           /// Action string: <b><c>NextPresent</c></b>
                           ADDON_ACTION_VIS_PRESET_NEXT         = 128,   //!< Next visualisation preset
                           /// Action string: <b><c></c>PreviousPreset</b>
                           ADDON_ACTION_VIS_PRESET_PREV         = 129,   //!< Previous visualisation preset
                           /// Action string: <b><c>LockPreset</c></b>
                           ADDON_ACTION_VIS_PRESET_LOCK         = 130,   //!< Lock the current visualisation preset
                           /// Action string: <b><c>RandomPreset</c></b>
                           ADDON_ACTION_VIS_PRESET_RANDOM       = 131,   //!< Switch to a new random preset
                           /// Action string: <b><c>IncreaseVisRating</c></b>
                           ADDON_ACTION_VIS_RATE_PRESET_PLUS    = 132,   //!< Used to increase track rating in full screen playback (press info on track and use pageplus on keyboard/remote
                           /// Action string: <b><c>DecreaseVisRating</c></b>
                           ADDON_ACTION_VIS_RATE_PRESET_MINUS   = 133,   //!< Used to decrease track rating in full screen playback (press info on track and use pageminus on keyboard/remote

                           /// Action string: <b><c>ShowVideoMenu</c></b>
                           ADDON_ACTION_SHOW_VIDEOMENU          = 134,   //!< Go to the DVD Video menu when playing a DVD.
                           /// Action string: <b><c>Enter</c></b>
                           ADDON_ACTION_ENTER                   = 135,   //!< ? (ACTION_ENTER) Not sure about all areas, but on some windows this will be the same as the "done" on screen button.

                           /// Action string: <b><c>IncreaseRating</c></b>
                           ADDON_ACTION_INCREASE_RATING         = 136,   //!< Used to increase track rating in full screen playback (press info on track and use pageplus on keyboard/remote
                           /// Action string: <b><c>DecreaseRating</c></b>
                           ADDON_ACTION_DECREASE_RATING         = 137,   //!< Used to decrease track rating in full screen playback (press info on track and use pageminus on keyboard/remote

                           /// Action string: <b><c>NextScene</c></b>
                           ADDON_ACTION_NEXT_SCENE              = 138,   //!< switch to next scene/cutpoint in movie
                           /// Action string: <b><c>PreviousScene</c></b>
                           ADDON_ACTION_PREV_SCENE              = 139,   //!< switch to previous scene/cutpoint in movie

                           /// Action string: <b><c>NextLetter</c></b>
                           ADDON_ACTION_NEXT_LETTER             = 140,   //!< jump through a list or container by letter
                           /// Action string: <b><c>PrevLetter</c></b>
                           ADDON_ACTION_PREV_LETTER             = 141,   //!< 

                           /// Action string: <b><c>JumpSMS2</c></b>
                           ADDON_ACTION_JUMP_SMS2               = 142,   //!< Jump through a list using SMS-style input 2 (eg press 2 twice to jump to the B's.)
                           /// Action string: <b><c>JumpSMS3</c></b>
                           ADDON_ACTION_JUMP_SMS3               = 143,   //!< Jump through a list using SMS-style input 3 (eg press 2 twice to jump to the B's.)
                           /// Action string: <b><c>JumpSMS4</c></b>
                           ADDON_ACTION_JUMP_SMS4               = 144,   //!< Jump through a list using SMS-style input 4 (eg press 2 twice to jump to the B's.)
                           /// Action string: <b><c>JumpSMS5</c></b>
                           ADDON_ACTION_JUMP_SMS5               = 145,   //!< Jump through a list using SMS-style input 5 (eg press 2 twice to jump to the B's.)
                           /// Action string: <b><c>JumpSMS6</c></b>
                           ADDON_ACTION_JUMP_SMS6               = 146,   //!< Jump through a list using SMS-style input 6 (eg press 2 twice to jump to the B's.)
                           /// Action string: <b><c>JumpSMS7</c></b>
                           ADDON_ACTION_JUMP_SMS7               = 147,   //!< Jump through a list using SMS-style input 7 (eg press 2 twice to jump to the B's.)
                           /// Action string: <b><c>JumpSMS8</c></b>
                           ADDON_ACTION_JUMP_SMS8               = 148,   //!< Jump through a list using SMS-style input 8 (eg press 2 twice to jump to the B's.)
                           /// Action string: <b><c>JumpSMS9</c></b>
                           ADDON_ACTION_JUMP_SMS9               = 149,   //!< Jump through a list using SMS-style input 9 (eg press 2 twice to jump to the B's.)

                           /// Action string: <b><c>FilterClear</c></b>
                           ADDON_ACTION_FILTER_CLEAR            = 150,   //!< Filter a list in music or videos using SMS-style input.
                           /// Action string: <b><c>FilterSMS2</c></b>
                           ADDON_ACTION_FILTER_SMS2             = 151,   //!< Filter a list in music or videos using SMS-style input.
                           /// Action string: <b><c>FilterSMS3</c></b>
                           ADDON_ACTION_FILTER_SMS3             = 152,   //!< Filter a list in music or videos using SMS-style input.
                           /// Action string: <b><c>FilterSMS4</c></b>
                           ADDON_ACTION_FILTER_SMS4             = 153,   //!< Filter a list in music or videos using SMS-style input.
                           /// Action string: <b><c>FilterSMS5</c></b>
                           ADDON_ACTION_FILTER_SMS5             = 154,   //!< Filter a list in music or videos using SMS-style input.
                           /// Action string: <b><c>FilterSMS6</c></b>
                           ADDON_ACTION_FILTER_SMS6             = 155,   //!< Filter a list in music or videos using SMS-style input.
                           /// Action string: <b><c>FilterSMS7</c></b>
                           ADDON_ACTION_FILTER_SMS7             = 156,   //!< Filter a list in music or videos using SMS-style input.
                           /// Action string: <b><c>FilterSMS8</c></b>
                           ADDON_ACTION_FILTER_SMS8             = 157,   //!< Filter a list in music or videos using SMS-style input.
                           /// Action string: <b><c>FilterSMS9</c></b>
                           ADDON_ACTION_FILTER_SMS9             = 158,   //!< Filter a list in music or videos using SMS-style input.

                           /// Action string: <b><c>FirstPage</c></b>
                           ADDON_ACTION_FIRST_PAGE              = 159,   //!<
                           /// Action string: <b><c>LastPage</c></b>
                           ADDON_ACTION_LAST_PAGE               = 160,   //!<

                           /// Action string: <b><c>AudioDelay</c></b>
                           ADDON_ACTION_AUDIO_DELAY             = 161,   //!<
                           /// Action string: <b><c>SubtitleDelay</c></b>
                           ADDON_ACTION_SUBTITLE_DELAY          = 162,   //!<
                           /// Action string: <b><c>Menu</c></b>
                           ADDON_ACTION_MENU                    = 163,   //!<

                           /// Action string: <b><c>Record</c></b>
                           ADDON_ACTION_RECORD                  = 170,   //!< PVR record current playing channel or selected item in windows like EPG

                           ADDON_ACTION_PASTE                   = 180,   //!<
                           ADDON_ACTION_NEXT_CONTROL            = 181,   //!<
                           ADDON_ACTION_PREV_CONTROL            = 182,   //!<
                           ADDON_ACTION_CHANNEL_SWITCH          = 183,   //!< PVR Used to switch channel. Works only if you playback TV or radio 
                           /// Action string: <b><c>ChannelUp</c></b>
                           ADDON_ACTION_CHANNEL_UP              = 184,   //!< PVR Used to switch up to the next channel. Works only if you playback TV or radio 
                           /// Action string: <b><c>ChannelDown</c></b>
                           ADDON_ACTION_CHANNEL_DOWN            = 185,   //!< PVR Used to switch down to the previous channel. Works only if you playback TV or radio
                           /// Action string: <b><c>NextChannelGroup</c></b>
                           ADDON_ACTION_NEXT_CHANNELGROUP       = 186,   //!< PVR Goes to the next channel group when using live TV. Works only within PVR windows + channel osd.
                           /// Action string: <b><c>PreviousChannelGroup</c></b>
                           ADDON_ACTION_PREVIOUS_CHANNELGROUP   = 187,   //!< PVR Goes to the previous channel group when using live TV. Works only within PVR windows + channel osd.
                           /// Action string: <b><c>PlayPVR</c></b>
                           ADDON_ACTION_PVR_PLAY                = 188,   //!< PVR Starts playback a TV or radio channel depends on the last played channel.
                           /// Action string: <b><c>PlayPVRTV</c></b>
                           ADDON_ACTION_PVR_PLAY_TV             = 189,   //!< PVR Starts playback a TV channel. Will playback the last played channel if available.
                           /// Action string: <b><c>PlayPVRRadio</c></b>
                           ADDON_ACTION_PVR_PLAY_RADIO          = 190,   //!< PVR Starts playback a radio channel. Will playback the last played channel if available.

                           /// Action string: <b><c>ToggleFullsreen</c></b>
                           ADDON_ACTION_TOGGLE_FULLSCREEN       = 199,   //!< switch 2 desktop resolution
                           /// Action string: <b><c>ToggleWatched</c></b>
                           ADDON_ACTION_TOGGLE_WATCHED          = 200,   //!< Toggle watched status (videos)
                           /// Action string: <b><c>ScanItem</c></b>
                           ADDON_ACTION_SCAN_ITEM               = 201,   //!< scan item
                           /// Action string: <b><c>AudioToggleDigital</c></b>
                           ADDON_ACTION_TOGGLE_DIGITAL_ANALOG   = 202,   //!< switch digital <-> analog
                           /// Action string: <b><c>ReloadKeymaps</c></b>
                           ADDON_ACTION_RELOAD_KEYMAPS          = 203,   //!< reloads CButtonTranslator's keymaps
                           /// Action string: <b><c>GUIProfile</c></b>
                           ADDON_ACTION_GUIPROFILE_BEGIN        = 204,   //!< start the GUIControlProfiler running

                           /// Action string: <b><c>Red</c></b>
                           ADDON_ACTION_TELETEXT_RED            = 215,   //!< Teletext Color buttons to control TopText
                           /// Action string: <b><c>Green</c></b>
                           ADDON_ACTION_TELETEXT_GREEN          = 216,   //!<    "       "      "    "     "       "
                           /// Action string: <b><c>Yellow</c></b>
                           ADDON_ACTION_TELETEXT_YELLOW         = 217,   //!<    "       "      "    "     "       "
                           /// Action string: <b><c>Blue</c></b>
                           ADDON_ACTION_TELETEXT_BLUE           = 218,   //!<    "       "      "    "     "       "

                           /// Action string: <b><c>IncreasePar</c></b>
                           ADDON_ACTION_INCREASE_PAR            = 219,   //!< Used in video fullscreen to increase the pixel aspect ratio (stretch).
                           /// Action string: <b><c>DecreasePar</c></b>
                           ADDON_ACTION_DECREASE_PAR            = 220,   //!< Used in video fullscreen to decrease the pixel aspect ratio (stretch).

                           /// Action string: <b><c>VerticalShiftUp</c></b>
                           ADDON_ACTION_VSHIFT_UP               = 227,   //!< shift up video image in DVDPlayer
                           /// Action string: <b><c>VerticalShiftDown</c></b>
                           ADDON_ACTION_VSHIFT_DOWN             = 228,   //!< shift down video image in DVDPlayer

                           /// Action string: <b><c>PlayPause</c></b>
                           ADDON_ACTION_PLAYER_PLAYPAUSE        = 229,   //!< Play/pause. If playing it pauses, if paused it plays.

                           /// Action string: <b><c>SubtitleShiftUp</c></b>
                           ADDON_ACTION_SUBTITLE_VSHIFT_UP      = 230,   //!< shift up subtitles in DVDPlayer
                           /// Action string: <b><c>SubtitleShiftDown</c></b>
                           ADDON_ACTION_SUBTITLE_VSHIFT_DOWN    = 231,   //!< shift down subtitles in DVDPlayer
                           /// Action string: <b><c>SubtitleAlign</c></b>
                           ADDON_ACTION_SUBTITLE_ALIGN          = 232,   //!< toggle vertical alignment of subtitles

                           /// Action string: <b><c>Filter</c></b>
                           ADDON_ACTION_FILTER                  = 233,   //!< Opens the mediafilter dialog in the video and musiclibrary.

                           /// Action string: <b><c>SwitchPlayer</c></b>
                           ADDON_ACTION_SWITCH_PLAYER           = 234,   //!< Select player to use, such as internal (DVDPlayer/PAPlayer), UPnP "play using" targets, external players (defined in playercorefactory.xml).

                           /// Action string: <b><c></c>NextStereoMode</b>
                           ADDON_ACTION_STEREOMODE_NEXT         = 235,   //!<
                           /// Action string: <b><c>PreviousStereoMode</c></b>
                           ADDON_ACTION_STEREOMODE_PREVIOUS     = 236,   //!<
                           /// Action string: <b><c>ToggleStereoMode</c></b>
                           ADDON_ACTION_STEREOMODE_TOGGLE       = 237,   //!< Toggle 3D/Stereoscopic mode
                           /// Action string: <b><c>StereoMode</c></b>
                           ADDON_ACTION_STEREOMODE_SELECT       = 238,   //!<
                           /// Action string: <b><c>StereoModeToMono</c></b>
                           ADDON_ACTION_STEREOMODE_TOMONO       = 239,   //!<
                           ADDON_ACTION_STEREOMODE_SET          = 240,   //!<

                           /// Action string: <b><c>SettingsReset</c></b>
                           ADDON_ACTION_SETTINGS_RESET          = 241,   //!<
                           /// Action string: <b><c>SettingsLevelChange</c></b>
                           ADDON_ACTION_SETTINGS_LEVEL_CHANGE   = 242,   //!<

                           ADDON_ACTION_TRIGGER_OSD             = 243,   //!< show autoclosing OSD. Can b used in videoFullScreen.xml window id=2005
                           ADDON_ACTION_INPUT_TEXT              = 244,   //!<
                           ADDON_ACTION_VOLUME_SET              = 245,   //!<

                           /// Action string: <b><c>Tap</c></b>
                           ADDON_ACTION_TOUCH_TAP               = 401,   //!< touch actions
                           ADDON_ACTION_TOUCH_TAP_TEN           = 410,   //!< To define the highest value possible for ADDON_ACTION_TOUCH_TAP
                           /// Action string: <b><c>LongPress</c></b>
                           ADDON_ACTION_TOUCH_LONGPRESS         = 411,   //!< touch actions
                           ADDON_ACTION_TOUCH_LONGPRESS_TEN     = 420,   //!< To define the highest value possible for ADDON_ACTION_TOUCH_LONGPRESS

                           ADDON_ACTION_GESTURE_NOTIFY          = 500,   //!<
                           ADDON_ACTION_GESTURE_BEGIN           = 501,   //!<
                           /// Action string: <b><c>ZoomGesture</c></b>
                           ADDON_ACTION_GESTURE_ZOOM            = 502,   //!< sendaction with point and currentPinchScale (fingers together < 1.0 -> fingers apart > 1.0)
                           /// Action string: <b><c>RotateGesture</c></b>
                           ADDON_ACTION_GESTURE_ROTATE          = 503,   //!<
                           /// Action string: <b><c>PanGesture</c></b>
                           ADDON_ACTION_GESTURE_PAN             = 504,   //!<

                           /// Action string: <b><c>SwipeLeft</c></b>
                           ADDON_ACTION_GESTURE_SWIPE_LEFT      = 511,   //!<
                           ADDON_ACTION_GESTURE_SWIPE_LEFT_TEN  = 520,   //!< To define the highest value possible for ADDON_ACTION_GESTURE_SWIPE_LEFT
                           /// Action string: <b><c>SwipeRight</c></b>
                           ADDON_ACTION_GESTURE_SWIPE_RIGHT     = 521,   //!<
                           ADDON_ACTION_GESTURE_SWIPE_RIGHT_TEN = 530,   //!< To define the highest value possible for ADDON_ACTION_GESTURE_SWIPE_RIGHT
                           /// Action string: <b><c>SwipeUp</c></b>
                           ADDON_ACTION_GESTURE_SWIPE_UP        = 531,   //!<
                           ADDON_ACTION_GESTURE_SWIPE_UP_TEN    = 540,   //!< To define the highest value possible for ADDON_ACTION_GESTURE_SWIPE_UP
                           /// Action string: <b><c>SwipeDown</c></b>
                           ADDON_ACTION_GESTURE_SWIPE_DOWN      = 541,   //!<
                           ADDON_ACTION_GESTURE_SWIPE_DOWN_TEN  = 550,   //!< To define the highest value possible for ADDON_ACTION_GESTURE_SWIPE_DOWN

                           /// Action string: <b><c>AnalogMoveX</c></b>
                           ADDON_ACTION_ANALOG_MOVE_X           = 601,   //!< analog thumbstick move, horizontal axis; see ACTION_ANALOG_MOVE
                           /// Action string: <b><c>AnalogMoveY</c></b>
                           ADDON_ACTION_ANALOG_MOVE_Y           = 602,   //!< analog thumbstick move, vertical axis; see ACTION_ANALOG_MOVE

                           /// Action string: <b><c>Error</c></b>
                           ADDON_ACTION_ERROR                   = 998,   //!< ERROR action is used to play an error sound

                           /// @brief Action string: <b><c>Noop</c></b>
                           ///
                           /// The NOOP action can be specified to disable an input event. This is
                           /// useful in user keyboard.xml etc to disable actions specified in the
                           /// system mappings.
                           ADDON_ACTION_NOOP                    = 999
};
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
