# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="docs/help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md)
</p>*
#### *<p align="center">Binary add-on GUI library, Version Level: 2</p>*
-------------
##### Binary classes and function to use on add-on's

Below is a code example do show what must be done on add-on base function to become support for library:

```cpp
#include "kodi/addon.api2/AddonLib.h"
#include "kodi/addon.api2/General.h"  // Needed for CAddOnLib_General::Log
#include "kodi/gui.api2/GUILib.h"

// Insert one macro on your add-on for it
IMPLEMENT_KODI_ADDON_LIBRARY;
IMPLEMENT_KODI_GUI_LIBRARY;
...

ADDON_STATUS ADDON_Create(void* hdl, void* props)
{
  if (!hdl || !props)
    return ADDON_STATUS_UNKNOWN;

  // Enable access to all add-on to Kodi functions
  if (!CAddonLib::RegisterMe(hdl))
    return ADDON_STATUS_PERMANENT_FAILURE;
  if (!CGUILib::RegisterMe(hdl))
    return ADDON_STATUS_PERMANENT_FAILURE;
  ...

  // Example lib call
  CAddOnLib_General::Log(LOG_INFO, "My add-on creation done");

  return ADDON_STATUS_OK;
}

void ADDON_Destroy()
{
  ...
  CGUILib::UnRegisterMe();
  CAddonLib::UnRegisterMe();
  ...
}
```

<b>Note:</b>
To use this library part must always ```CAddonLib``` be present!

-------------

Below is showing you a description and usage of parts which becomes usable on add-on. Also a small 
demonstration code is inserted there.

##### Functions

1. <a id="CGUILib"></a>[CGUILib](docs/CGUILib.md) - General GUI functions
   * [bool CGUILib::RegisterMe(void *handle);](docs/CGUILib.md#CGUILib_RegisterMe)
     - Resolve all callback methods
   * [void CGUILib::UnRegisterMe();](docs/CGUILib.md#CGUILib_UnRegisterMe)
     - Release all callback methods and close handling with them
   * [void CGUILib::Lock();](docs/CGUILib.md#CGUILib_Lock)
     - Performs a graphical lock of rendering engine
   * [void CGUILib::Unlock();](docs/CGUILib.md#CGUILib_Unlock)
     - Performs a graphical unlock of previous locked rendering engine
   * [int CGUILib::GetScreenHeight();](docs/CGUILib.md#CGUILib_GetScreenHeight)
     - Return the the current screen height with pixel
   * [int CGUILib::GetScreenWidth();](docs/CGUILib.md#CGUILib_GetScreenWidth)
     - Return the the current screen width with pixel
   * [int CGUILib::GetVideoResolution();](docs/CGUILib.md#CGUILib_GetVideoResolution)
     - Return the the current screen rendering resolution
   * [int GetCurrentWindowId();](#CGUILib_GetCurrentWindowId)
     - Returns the id for the current 'active' window as an integer.
   * [int GetCurrentWindowDialogId();](#CGUILib_GetCurrentWindowDialogId)
     - Returns the id for the current 'active' dialog as an integer.

2. <a id="CAddonGUIDialogFileBrowser"></a>[CAddonGUIDialogFileBrowser](docs/CAddonGUIDialogFileBrowser.md) - File browser dialogs
   * [<p align="bottom"><img src="docs/help.GUIDialogFileBrowser.ShowAndGetDirectory.png" width="192"></p>](docs/CAddonGUIDialogFileBrowser.md)
   * [bool CAddonGUIDialogFileBrowser::ShowAndGetDirectory(const std::string& shares, const std::string& heading, std::string& path, bool bWriteOnly);](docs/CAddonGUIDialogFileBrowser.md#CAddonGUIDialogFileBrowser_ShowAndGetDirectory)
     - Directory selection dialog
   * [bool CAddonGUIDialogFileBrowser::ShowAndGetFile(const std::string& shares, const std::string& mask, const std::string& heading, std::string& path, bool useThumbs, bool useFileDirectories);](docs/CAddonGUIDialogFileBrowser.md#CAddonGUIDialogFileBrowser_ShowAndGetFile)
     - File selection dialog
   * [bool CAddonGUIDialogFileBrowser::ShowAndGetFileFromDir(const std::string& directory, const std::string& mask, const std::string& heading, std::string& path, bool useThumbs, bool useFileDirectories, bool singleList);](docs/CAddonGUIDialogFileBrowser.md#CAddonGUIDialogFileBrowser_ShowAndGetFileFromDir)
     - File selection from a directory
  * [bool CAddonGUIDialogFileBrowser::ShowAndGetFileList(const std::string& shares, const std::string& mask, const std::string& heading, std::vector< std::string >& path, bool useThumbs, bool useFileDirectories);](docs/CAddonGUIDialogFileBrowser.md#CAddonGUIDialogFileBrowser_ShowAndGetFileList)
     - File selection dialog to get several in to a list
   * [bool CAddonGUIDialogFileBrowser::ShowAndGetSource(std::string& path, bool allowNetworkShares, const std::string& additionalShare, const std::string& type);](docs/CAddonGUIDialogFileBrowser.md#CAddonGUIDialogFileBrowser_ShowAndGetSource)
     - Source selection dialog
   * [bool CAddonGUIDialogFileBrowser::ShowAndGetImage(const std::string& shares, const std::string& heading, std::string& path);](docs/CAddonGUIDialogFileBrowser.md#CAddonGUIDialogFileBrowser_ShowAndGetImage)
     - Image selection dialog
   * [bool CAddonGUIDialogFileBrowser::ShowAndGetImageList(const std::string& shares, const std::string& heading, std::vector< std::string >& path);](docs/CAddonGUIDialogFileBrowser.md#CAddonGUIDialogFileBrowser_ShowAndGetImageList)
     - Image selection dialog to get several in to a list

3. <a id="CAddonGUIDialogKeyboard"></a>[CAddonGUIDialogKeyboard](docs/CAddonGUIDialogKeyboard.md) - Keyboard dialogs
   * [<p align="bottom"><img src="docs/help.GUIDialogKeyboard.ShowAndVerifyPassword.png" width="192"></p>](docs/CAddonGUIDialogFileBrowser.md)
   * [bool CAddonGUIDialogKeyboard::ShowAndGetInput(std::string& strText, const std::string& strHeading, bool allowEmptyResult, bool hiddenInput, unsigned int autoCloseMs);](docs/CAddonGUIDialogKeyboard.md#CAddonGUIDialogKeyboard_ShowAndGetInput_1)
     - Use dialog to get normal text
   * [bool CAddonGUIDialogKeyboard::ShowAndGetInput(std::string&strText, bool allowEmptyResult, unsigned int autoCloseMs);](docs/CAddonGUIDialogKeyboard.md#CAddonGUIDialogKeyboard_ShowAndGetInput_2)
     - Use dialog to get normal text
   * [bool CAddonGUIDialogKeyboard::ShowAndGetNewPassword(std::string& newPassword, const std::string& strHeading, bool allowEmptyResult, unsigned int autoCloseMs);](docs/CAddonGUIDialogKeyboard.md#CAddonGUIDialogKeyboard_ShowAndGetNewPassword_1)
     - Get a new password on dialog
   * [bool CAddonGUIDialogKeyboard::ShowAndGetNewPassword(std::string& newPassword, unsigned int autoCloseMs);](docs/CAddonGUIDialogKeyboard.md#CAddonGUIDialogKeyboard_ShowAndGetNewPassword_2)
     - Get a new password on dialog
   * [bool CAddonGUIDialogKeyboard::ShowAndVerifyNewPassword(std::string& newPassword, const std::string& strHeading, bool allowEmptyResult, unsigned int autoCloseMs);](docs/CAddonGUIDialogKeyboard.md#CAddonGUIDialogKeyboard_ShowAndVerifyNewPassword_1)
     - Shows dialog to insert new password with verification
   * [bool CAddonGUIDialogKeyboard::ShowAndVerifyNewPassword(std::string& newPassword, unsigned int autoCloseMs);](docs/CAddonGUIDialogKeyboard.md#CAddonGUIDialogKeyboard_ShowAndVerifyNewPassword_2)
     - Shows dialog to insert new password with verification
   * [int CAddonGUIDialogKeyboard::ShowAndVerifyPassword(std::string& strPassword, const std::string& strHeading, int iRetries, unsigned int autoCloseMs);](docs/CAddonGUIDialogKeyboard.md#CAddonGUIDialogKeyboard_ShowAndVerifyPassword)
     - Shows dialog to insert password and verify with on ```strPassword```
   * [bool CAddonGUIDialogKeyboard::ShowAndGetFilter(std::string& strText, bool searching, unsigned int autoCloseMs);](docs/CAddonGUIDialogKeyboard.md#CAddonGUIDialogKeyboard_ShowAndGetFilter)
     - Shows a filter related keyboard
   * [bool CAddonGUIDialogKeyboard::SendTextToActiveKeyboard(const std::string& aTextString, bool closeKeyboard);](docs/CAddonGUIDialogKeyboard.md#CAddonGUIDialogKeyboard_SendTextToActiveKeyboard)
     - Send a text to a visible keayboard
   * [bool iCAddonGUIDialogKeyboard::IsKeyboardActivated();](docs/CAddonGUIDialogKeyboard.md#CAddonGUIDialogKeyboard_IsKeyboardActivated)
     - Check for visible keyboard on GUI

4. <a id="CAddonGUIDialogNumeric"></a>[CAddonGUIDialogNumeric](docs/CAddonGUIDialogNumeric.md) - Numeric dialogs
   * [<p align="bottom"><img src="docs/help.GUIDialogNumeric.ShowAndGetDate.png" width="192"></p>](docs/CAddonGUIDialogFileBrowser.md)
   * [bool CAddonGUIDialogNumeric::ShowAndVerifyNewPassword(std::string& strNewPassword);](docs/CAddonGUIDialogNumeric.md#CAddonGUIDialogNumeric_ShowAndVerifyNewPassword)
     - Use dialog to get numeric new password
   * [int CAddonGUIDialogNumeric::ShowAndVerifyPassword(std::string& strPassword, const std::string& strHeading, int iRetries);](docs/CAddonGUIDialogNumeric.md#CAddonGUIDialogNumeric_ShowAndVerifyPassword)
     - Use dialog to verify numeric password
   * [bool CAddonGUIDialogNumeric::ShowAndVerifyInput(std::string& strPassword, const std::string& strHeading, bool bGetUserInput);](docs/CAddonGUIDialogNumeric.md#CAddonGUIDialogNumeric_ShowAndVerifyInput)
     - Use dialog to verify numeric input
   * [bool CAddonGUIDialogNumeric::ShowAndGetTime(tm& time, const std::string& strHeading);](docs/CAddonGUIDialogNumeric.md#CAddonGUIDialogNumeric_ShowAndGetTime)
     - Use dialog to get time value
   * [bool CAddonGUIDialogNumeric::ShowAndGetDate(tm& date, const std::string& strHeading);](docs/CAddonGUIDialogNumeric.md#CAddonGUIDialogNumeric_ShowAndGetDate)
     - Use dialog to get date value
   * [bool CAddonGUIDialogNumeric::ShowAndGetIPAddress(std::string& strIPAddress, const std::string& strHeading);](docs/CAddonGUIDialogNumeric.md#CAddonGUIDialogNumeric_ShowAndGetIPAddress)
     - Use dialog to get a IP
   * [bool CAddonGUIDialogNumeric::ShowAndGetNumber(std::string& strInput, const std::string& strHeading, unsigned int iAutoCloseTimeoutMs);](docs/CAddonGUIDialogNumeric.md#CAddonGUIDialogNumeric_ShowAndGetNumber)
     - Use dialog to get normal number
   * [bool CAddonGUIDialogNumeric::ShowAndGetSeconds(std::string& strTime, const std::string& strHeading);](docs/CAddonGUIDialogNumeric.md#CAddonGUIDialogNumeric_ShowAndGetSeconds)
     - Use dialog to get seconds value

5. <a id="CAddonGUIDialogOK"></a>[CAddonGUIDialogOK](docs/CAddonGUIDialogOK.md) - OK Dialog
   * [<p align="bottom"><img src="docs/help.GUIDialogOK.png" width="192"></p>](docs/CAddonGUIDialogOK.md)
   * [void CAddonGUIDialogOK::ShowAndGetInput(const std::string& heading, const std::string& text);](docs/CAddonGUIDialogOK.md#CAddonGUIDialogOK_ShowAndGetInput_1)
     - Use dialog to inform user with text and confirmation with OK
   * [void CAddonGUIDialogOK::ShowAndGetInput(const std::string& heading, const std::string& line0, const std::string& line1, const std::string& line2);](docs/CAddonGUIDialogOK.md#CAddonGUIDialogOK_ShowAndGetInput_2)
     - Use dialog to inform user with text and confirmation with OK

6. <a id="CAddonGUIDialogSelect"></a>[CAddonGUIDialogSelect](docs/CAddonGUIDialogSelect.md) - Selection Dialog
   * [<p align="bottom"><img src="docs/help.GUIDialogSelect.png" width="192"></p>](docs/CAddonGUIDialogSelect.md)
   * [int CAddonGUIDialogSelect::Show(const std::string& heading, const std::vector< std::string >& entries, int selected);](docs/CAddonGUIDialogSelect.md#CAddonGUIDialogSelect_Show)
     - Show a selection dialog about given parts

7. <a id="CAddonGUIDialogTextViewer"></a>[CAddonGUIDialogTextViewer](docs/CAddonGUIDialogTextViewer.md) - Text Dialog
   * [<p align="bottom"><img src="docs/help.GUIDialogTextViewer.png" width="192"></p>](docs/CAddonGUIDialogTextViewer.md)
   * [void CAddonGUIDialogTextViewer::Show(const std::string& heading, const std::string& text);](docs/CAddonGUIDialogTextViewer.md#CAddonGUIDialogTextViewer_Show)
     - Show info text dialog

8. <a id="CAddonGUIDialogYesNo"></a>[CAddonGUIDialogYesNo](docs/CAddonGUIDialogYesNo.md) - Yes / no dialog
   * [<p align="bottom"><img src="docs/help.GUIDialogYesNo.png" width="192"></p>](docs/CAddonGUIDialogYesNo.md)
   * [bool CAddonGUIDialogYesNo::ShowAndGetInput(const std::string& heading, const std::string& text, bool& bCanceled, const std::string& noLabel, const std::string& yesLabel);](docs/CAddonGUIDialogYesNo.md#CAddonGUIDialogYesNo_ShowAndGetInput_1)
     - Show yes / no confirmation dialog
   * [bool CAddonGUIDialogYesNo::ShowAndGetInput(const std::string& heading, const std::string& line0, const std::string& line1, const std::string& line2, const std::string& noLabel, const std::string& yesLabel);](docs/CAddonGUIDialogYesNo.md#CAddonGUIDialogYesNo_ShowAndGetInput_2)
     - Show yes / no confirmation dialog
   * [bool CAddonGUIDialogYesNo::ShowAndGetInput(const std::string& heading, const std::string& line0, const std::string& line1, const std::string& line2, bool& bCanceled, const std::string& noLabel, const std::string& yesLabel);](docs/CAddonGUIDialogYesNo.md#CAddonGUIDialogYesNo_ShowAndGetInput_3)
     - Show yes / no confirmation dialog

##### Classes
###### Dialogs
1. <a id="CAddonGUIDialogExtendedProgress">[CAddonGUIDialogExtendedProgress](docs/CAddonGUIDialogExtendedProgress.md) - Extended progress dialog 
  - [<p align="bottom"><img src="docs/help.GUIDialogExtendedProgress.png" width="192"></p>](docs/CAddonGUIDialogExtendedProgress.md)
2. <a id="CAddonGUIDialogProgress">[CAddonGUIDialogProgress](docs/CAddonGUIDialogProgress.md) - Progress dialog
  - [<p align="bottom"><img src="docs/help.GUIDialogProgress.png" width="192"></p>](docs/CAddonGUIDialogExtendedProgress.md)

###### GUI controls
3. <a id="CAddonGUIButtonControl">[CAddonGUIButtonControl](docs/CAddonGUIButtonControl.md) - Standard push button control for window.
4. <a id="CAddonGUIEditControl">[CAddonGUIEditControl](docs/CAddonGUIEditControl.md) - Editable window text control used as an input control for the osd keyboard and other input fields.
5. <a id="CAddonGUIFadeLabelControl">[CAddonGUIFadeLabelControl](docs/CAddonGUIFadeLabelControl.md) - Window control used to show multiple pieces of text in the same position, by fading from one to the other.
6. <a id="CAddonGUIImageControl">[CAddonGUIImageControl](docs/CAddonGUIImageControl.md) - Window control used to show an image.
5. <a id="CAddonGUILabelControl">[CAddonGUILabelControl](docs/CAddonGUILabelControl.md) - Window control used to show some lines of text.
6. <a id="CAddonGUIProgressControl">[CAddonGUIProgressControl](docs/CAddonGUIProgressControl.md) - Window control to show the progress of a particular operation.
7. <a id="CAddonGUIRadioButtonControl">[CAddonGUIRadioButtonControl](docs/CAddonGUIRadioButtonControl.md) - Window control for a radio button (as used for on/off settings).
8. <a id="CAddonGUIRenderingControl">[CAddonGUIRenderingControl](docs/CAddonGUIRenderingControl.md) - Window control for rendering own parts
9. <a id="CAddonGUISettingsSliderControl">[CAddonGUISettingsSliderControl](docs/CAddonGUISettingsSliderControl.md) - Window control for moveable slider with text name
10. <a id="CAddonGUISliderControl">[CAddonGUISliderControl](docs/CAddonGUISliderControl.md) - Window control for moveable slider
11. <a id="CAddonGUISpinControl">[CAddonGUISpinControl](docs/CAddonGUISpinControl.md) - Window control used for cycling up/down controls.
12. <a id="CAddonGUITextBoxControl">[CAddonGUITextBoxControl](docs/CAddonGUITextBoxControl.md) - Used to show a multi-page piece of text.
13. <a id="CAddonGUIListItem">[CAddonGUIListItem](docs/CAddonGUIListItem.md) - Selectable window list item
14. <a id="CAddonGUIWindow">[CAddonGUIWindow](docs/CAddonGUIWindow.md) - Main window control class

##### Definations

<a id="directorysharestrings">
###### Directory share strings

String values to define selectable directories on related dialogs.

Values can be used together with the '|' character like this: ```"local|network|removable"```

<table>
    <thead>
        <tr>
          <th><sub>String:</sub></th>
          <th><sub>Description:</sub></th>
        </tr>
    </thead>
    <tr>
        <td>local</td>
        <td>Include local directories and hard disks</td>
    </tr>
    <tr>
        <td>network</td>
        <td>Include network access</td>
    </tr>
    <tr>
        <td>removable</td>
        <td>Include removable media sources</td>
    </tr>
    <tr>
        <td>programs</td>
        <td>Include kodi programs defined sources</td>
    </tr>
    <tr>
        <td>files</td>
        <td>Include kodi files defined sources</td>
    </tr>
    <tr>
        <td>music</td>
        <td>Include kodi music defined sources</td>
    </tr>
    <tr>
        <td>video</td>
        <td>Include kodi video defined sources</td>
    </tr>
    <tr>
        <td>pictures</td>
        <td>Include kodi pictures defined sources</td>
    </tr>
</table>

<a id="AddonGUIFontAlignment">
###### Flags for text font alignment

```cpp
typedef enum AddonGUIFontAlignment
{
  ADDON_FONT_LEFT       = 0x00000000,
  ADDON_FONT_RIGHT      = 0x00000001,
  ADDON_FONT_CENTER_X   = 0x00000002,
  ADDON_FONT_CENTER_Y   = 0x00000004,
  ADDON_FONT_TRUNCATED  = 0x00000008,
  ADDON_FONT_JUSTIFIED  = 0x00000010
} AddonGUIFontAlignment;
```

<a id="AddonGUIIconOverlay">
###### Overlay icon types

```cpp
enum AddonGUIIconOverlay {
  ADDON_ICON_OVERLAY_NONE = 0,
  ADDON_ICON_OVERLAY_RAR,
  ADDON_ICON_OVERLAY_ZIP,
  ADDON_ICON_OVERLAY_LOCKED,
  ADDON_ICON_OVERLAY_UNWATCHED,
  ADDON_ICON_OVERLAY_WATCHED,
  ADDON_ICON_OVERLAY_HD
};
```

<a id="AddonGUIInputType">
###### Text field input types

```cpp
enum AddonGUIInputType   { 
  ADDON_INPUT_TYPE_READONLY = -1,
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
  ADDON_INPUT_TYPE_PASSWORD_NUMBER_VERIFY_NEW
};
```

<a id="AddonGUIActionType">
###### GUI action types

```cpp
enum AddonGUIActionType  {
  ADDON_ACTION_NONE                    = 0,
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
  ADDON_ACTION_ANALOG_MOVE             = 49,   //!< analog thumbstick move. Can b used in: slideshow.xml window id=2007/settingsScreenCalibration.xml windowid=11/settingsUICalibrat
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
  ADDON_ACTION_NOOP            = 999
};
```

