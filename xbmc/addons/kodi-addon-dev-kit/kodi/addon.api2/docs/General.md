# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md)
</p>*
#### *<p align="center">Binary add-on library, Version Level: 2</p>*
## *<p align="center">General parts</p>*
----------

General
-------------

The below listed general functions allow to send your own commands to perform either there commands, or to obtain information.

It has the header [`#include <kodi/addon.api2/General.h`](../General.h) be included to enjoy it.

Functions
-------------

1. [bool GetSettingString(const std::string& settingName, std::string& settingValue, bool global = false);](#GetSettingString)
* [bool GetSettingInt(const std::string& settingName, int& settingValue, bool global = false);](#GetSettingInt)
* [bool GetSettingBoolean(const std::string& settingName, bool& settingValue, bool global = false);](#GetSettingBoolean)
* [bool GetSettingFloat(const std::string& settingName, float& settingValue, bool global = false);](#GetSettingFloat)
* [void Log(const addon_log_t loglevel, const char* format, ...);](#Log)
* [void QueueNotification(const queue_msg_t type, const char* format, ...);](#QueueNotification_1)
* [void QueueNotification(const queue_msg_t type, const std::string& aCaption, const std::string& aDescription, unsigned int displayTime, bool withSound, unsigned int messageTime);](#QueueNotification_2)
* [void QueueNotification(const std::string& aCaption, const std::string& aDescription);](#QueueNotification_3)
* [void QueueNotification(const std::string& aImageFile, const std::string& aCaption, const std::string& aDescription, unsigned int displayTime, bool withSound, unsigned int messageTime);](#QueueNotification_4)
* [void GetMD5(const std::string& text, std::string& md5);](#GetMD5)
* [bool UnknownToUTF8(const std::string& stringSrc, std::string& utf8StringDst, bool failOnBadChar = false);](#UnknownToUTF8)
* [std::string GetLocalizedString(uint32_t labelId, const std::string& strDefault = "") const;](#GetLocalizedString)
* [std::string GetLanguage(lang_formats format = LANG_FMT_ENGLISH_NAME, bool region = false) const;](#GetLanguage)
* [std::string GetDVDMenuLanguage();](#GetDVDMenuLanguage)
* [bool StartServer(eservers typ, bool start, bool wait = false);](#StartServer)
* [void AudioSuspend();](#AudioSuspend)
* [void AudioResume();](#AudioResume)
* [float GetVolume(bool percentage = true);](#GetVolume)
* [void SetVolume(float value, bool isPercentage = true);](#SetVolume)
* [bool IsMuted();](#IsMuted)
* [void ToggleMute(void);](#ToggleMute)
* [dvd_state GetOpticalDriveState();](#GetOpticalDriveState)
* [bool EjectOpticalDrive();](#EjectOpticalDrive)
* [void KodiVersion(kodi_version_t& version);](#KodiVersion)
* [void KodiQuit();](#KodiQuit)
* [void HTPCShutdown();](#HTPCShutdown)
* [void HTPCRestart();](#HTPCRestart)
* [void ExecuteScript(const std::string& script);](#ExecuteScript)
* [void ExecuteBuiltin(const std::string& function, bool wait = false);](#ExecuteBuiltin)
* [std::string ExecuteJSONRPC(const std::string& jsonrpccommand) const;](#ExecuteJSONRPC)
* [std::string GetRegion(const std::string& id) const;](#GetRegion)
* [long GetFreeMem();](#GetFreeMem)
* [int GetGlobalIdleTime();](#GetGlobalIdleTime)
* [std::string TranslateAddonStatus(ADDON_STATUS status);](#TranslateAddonStatus)
* [std::string GetAddonInfo(std::string& id) const;](#GetAddonInfo)

-------------

* <a id="Settings">**Add-on settings handling**
    - `settings.xml` is a XML file that contains the current configuration for the addon and should be placed in the 
      resources direcory. If your addon has configurable items that are set by the user, put them here. This file defines 
      what the user sees when they click on Addon settings for your addon. You don't need to do any coding to utilise this 
      functionality. The format for the settings file is relatively straightforward as can be seen in the following.
    - Example:

  	```xml
    <?xml version="1.0" encoding="utf-8" standalone="yes"?>
    <settings>
      <category label="32100">
        <setting id="scrolldelay" type="slider" label="32101" option="int" default="1" range="0,10" />
        <setting id="scrollmode" type="enum" label="32102" lvalues="32401|32402" default="0" />
        <setting id="navtimeout" type="slider" label="32103" option="int" default="2" range="1,10" />
        <setting id="refreshrate" type="slider" label="32104" option="int" default="1" range="1,20" />
        <setting id="sep1" type="sep" />
        <setting id="usealternatecharset" type="bool" label="32105" default="false" />
        <setting id="charset" enable="eq(-1,true)" type="enum" label="32106" lvalues="32411|32412|32413|32414|32415|32416|32417" default="0" subsetting="true"/>
        <setting id="sep2" type="sep" />
        <setting id="useextraelements" type="bool" label="32107" default="true" />
      </category>
      <category label="32200">
        <setting label="32206" type="lsep" />
        <setting id="dimonvideoplayback" type="bool" label="32203" default="false" subsetting="true" />
        <setting id="dimonmusicplayback" type="bool" label="32204" default="false" subsetting="true" />
        <setting id="dimonscreensaver" type="bool" label="32201" default="false" subsetting="true" />
        <setting id="dimdelay" type="slider" label="32205" default="0" range="0,30" subsetting="true" />
        <setting id="sep3" type="sep" />
        <setting id="dimonshutdown" type="bool" label="32202" default="false" />
      </category>
      <category label="32300">
        <setting id="remotelcdproc" type="bool" label="32301" default="false" />
        <setting id="hostip" enable="eq(-1,true)" type="ipaddress" label="32302" default="127.0.0.1" subsetting="true" />
        <setting id="hostport" enable="eq(-2,true)" type="number" label="32303" default="13666" subsetting="true" />
        <setting id="sep4" type="sep" />
        <setting id="heartbeat" type="bool" label="32304" default="false" />
        <setting id="sep5" type="sep" />
        <setting id="hideconnpopups" type="bool" label="32305" default="true" />
      </category>
    </settings>
    ```
      
    Settings can have additional attributes:

    |  Type                   | Description                                                                               |
    | :---------------------: | ----------------------------------------------------------------------------------------- |
    | **source=""**           | **video**, **music**, **pictures**, **programs**, **files**, **local** or **blank**.      |
    |     	                  | if source is blank it will use the type for shares if it is a valid share if not a valid  |
    |     	                  | share it will use, both local and network drives.                                         |
    |     	                  |                                                                                           |
    |     	                  |                                                                                           |
    |     	                  |                                                                                           |
    | **visible=""**          | **"true"**, **"false"** or **conditional**.                                               |
    |     	                  | Determines if the setting is displayed in the settings dialog (default = 'true')"         |
    |     	                  |                                                                                           |
    |     	                  | You can also use a conditional statement:                                                 |
    |     	                  |   ***`visible="System.HasAddon(plugin.video.youtube)"`***                                 |
    |     	                  |   ***`visible="eq(-2,true)"`*** ( same syntax like for enable="" )                        |
    |     	                  |                                                                                           |
    |     	                  |                                                                                           |
    |     	                  |                                                                                           |
    | **enable=""**           | Allows you to determine whether this setting should be shown based on the value of        |
    |     	                  | another setting.                                                                          |
    |     	                  | 3 comparators are available:                                                              |
    |     	                  |   - ***`eq()`*** Equal to                                                                 |
    |     	                  |   - ***`gt()`*** Greater than                                                             |
    |     	                  |   - ***`lt()`*** Less than                                                                |
    |     	                  |                                                                                           |
    |     	                  | You can AND the comparators using the + symbol and negate it using the ! symbol           |
    |     	                  |  (e.g. !eq()). Each comparator takes 2 operands:                                          |
    |     	                  | Relative position of setting to compare                                                   |
    |     	                  | Value to compare against                                                                  |
    |     	                  | Thus if we place settings in our file in this order:                                      |
    |     	                  | - myFirst setting                                                                         |
    |     	                  | - mySecondSetting                                                                         |
    |     	                  | - myThirdSetting                                                                          |
    |     	                  |                                                                                           |
    |     	                  | for the third setting we might add the option:                                            |
    |     	                  | - **`enable="gt(-2,3) + lt(-2,10)"`**                                                     |
    |     	                  |                                                                                           |
    |     	                  | You can also use a conditional statement:                                                 |
    |     	                  | - **`enable="System.HasAddon(plugin.video.youtube)"`**                                    |
    |     	                  |                                                                                           |
    |     	                  |                                                                                           |
    |     	                  |                                                                                           |
    | **subsetting="true"**   | Add dash in front of option                                                               |
    |     	                  |                                                                                           |

   **Void type examples for add-on `./resources/settings.xml`:**
    - Line separators add a horizontal separating line between other element. They are purely user-interface elements 
      that do not allow user input and therefore have no meaningful value as a setting.
    - `lsep`
        - Shows a horizontal line with a text.
        - **`label="id"`** (required) - an id from the language file that indicates which text to display.
        ```xml
        <setting label="32024" type="lsep"/>
        ```

    - `sep`
        - Shows a horizontal line.
      	```xml
        <setting type="sep"/>
        <setting id="sep1" type="sep" />
        ```

    - `action`
        - Adds line to configuration windows which allow to execute action
      	```xml
      	<setting label="32002" type="action" id="backend" action="XBMC.NotifyAll(service.xbmc.tts,SETTINGS.BACKEND_DIALOG)"/>
        ```

-------------
*  <a id="GetSettingString">
   **`bool CAddOnLib_General::GetSettingString(const std::string& settingName, std::string& settingValue, bool global = false);`**
    * Get a string settings value for this add-on.
    * ***WARNING:*** For this function and others below is no access on Kodi about passwords, paths and
      network parts allowed!
    * Text input elements allow a user to input text in various formats. The "label" attribute must contain an id from the 
      language file that indicates which text to display for the input field.
    * To get path from add-on can be from `GetSettingString` the `settingValue`***__addonpath__*** used.
      * **`settingName`:** The name of the setting to get.
      * **`settingValue`:** The value.
      * **`global`:** If set to true becomes Kodi itself asked about a setting _(Default: `false`)_.
      * **return:** true if successfull done

    **String type examples for add-on `./resources/settings.xml`:**
      - `text`
        - Allow a user to enter one line of text.
          - **`id="string"`** (required) - the name of the setting.
          - **`label="id"`** (required) - an id from the language file that indicates which text to display.
          - **`option="hidden"|"urlencoded"`** (optional)
            - if set to **"hidden"**, each characters entered by the user will be obfuscated with an asterisks ("*"), as is usual for entering passwords.
            - if set to **"urlencoded"**, each non-alphanumeric characters entered by the user will be "escaped" using %XX encoding.
          - **`default="value"`** (optional) - the default value.
      	```xml
        <setting id="addon.language" type="text" label="30523" default="en-US"/>
        ```

      - `folder`
        - Allow the user to browse for and select a folder.
          - **`id="string"`** (required) - the name of the setting
          - **`label="id"`** (required) - an id from the language file that indicates which text to display.
          - **`source="auto"|"images"|...`** (optional, default="auto") - select a starting folder for the browse dialog.

          | Source types      | Description                            |
          |:-----------------:|----------------------------------------|
          | music	            | Include music related sources          |
          | video		          |	Include video related sources          |
          | pictures          |	Include pictures related sources       |
          | programs          |	Include praograms related sources      |
          | local             | Include local system related sources   |

          - **`value="value"`** (optional, default="") - the default value.
          - **`option="writeable"`** (optional, default="") - the user can be allowed to create and select new folders by setting this argument.

      	```xml
        <setting id="iconpath" type="folder" source="files" label="30048" default="" />
        <setting id="download-folder" type="folder" label="32010"/>
        <setting id="image_path" type="folder" source="pictures" label="32012" visible="eq(-2,1)" default=""/>
        <setting label="32033" type="folder" id="folder" source="auto" option="writeable"/>
        ```

      - `file`
        - To select file by the user.
      	```xml
        <setting id="rtmp_binary" type="file" label="103" default="" />
        ```

      - `ipaddress`
        - To use setting for ip address with the related dialog.
          - **`id="string"`** (required) - the name of the setting.
          - **`label="id"`** (required) - an id from the language file that indicates which text to display.
          - **`default="value"`** (optional) - the default value.
      	```xml
        <setting id="hostip" enable="eq(-1,true)" type="ipaddress" label="32302" default="127.0.0.1" subsetting="true" />
        ```

      - `fileenum`
        - Display files in a folder as an enum selector.
          - **`mask="value"`** - filter selectable files. Examples: "/" - display only folders. "*.txt" - display only .txt
               files.
          - **`option="hideext"`** - hide file extensions.
        - Example: List sub-folders of the 'resources' folder for this add-on in the settings.
      	```xml
      	<setting id="myenum" type="fileenum" values="resources" mask="/"/>
      	<setting id="trailer.ratingMax" label="32062" type="fileenum" values="$PROFILE/settings/ratings" default="MPAA" mask="/"/>
        ```

      - `labelenum`
        - Shows a spin control about given string values and use a string value from selection.

      	```xml
        <setting id="bitrate" type="labelenum" label="30003" default="Max" values="Min|Max|Select" />
        <setting id="trailer.quality" label="32067" type="labelenum" values="480p|720p|1080p" default="720p" />
        <setting id="scope" label="32092" type="labelenum" values="16:9|2.35:1|2.40:1" default="0" />
        <setting id="quality" type="labelenum" label="$LOCALIZE[622]" values="720p|480p" default="720p" />
        ```

        Code example:
        ```cpp
        #include <kodi/addon.api2/General.h>

        std::string bitrate = "Max";
        if (!CAddOnLib_General::GetSettingString("bitrate", bitrate))
          CAddOnLib_General::Log(LOG_ERROR, "Couldn't get 'bitrate' setting, falling back to default");
        ```

-------------
*  <a id="GetSettingInt">
   **`bool CAddOnLib_General::GetSettingInt(const std::string& settingName, int& settingValue, bool global = false);`**
    * Numeric input elements allow a user to enter a number. The "label" attribute must contain an id from the language 
      file that indicates which text to display for the input field.
      * **`settingName`:** The name of the setting to get.
      * **`settingValue`:** The value.
      * **`global`:** If set to true becomes Kodi itself asked about a setting _(Default: `false`)_.
      * **return:** true if successfull done

      **Integer type examples for add-on `./resources/settings.xml`:**
      - `number`
        - To get a numeric entry
          * **`id="string"`** (required) - the name of the setting.
          * **`label="id"`** (required) - an id from the language file that indicates which text to display.
          * **`default="value"`** (optional) - the default value.
      	```xml
        <setting id="kodion.view.default" type="number" label="30027" default="50"/>
        ```

      - `enum`
        - Shows a spin control about given string values and use a integer value from selection
          * **`id="string"`** (required) - the name of the setting
          * **`label="id"`** (required) - an id from the language file that indicates which text to display.
          * **`values="value1[|value2[...]]"`** - or -
          * **`lvalues="id1[|id2[...]]"`** (required):
                - A list of values or language file ids from which the user can choose.
                - values="$HOURS" is special case to select hour ( works only for type="enum" )
          * **`sort="yes"`** - sorts labels ( works only for type="labelenum" )
      	```xml
        <setting id="kodion.video.quality" type="enum" label="30010" enable="eq(1,false)" lvalues="30016|30017|30011|30012|30013" default="3" />
        <setting id="notification_length" type="enum" label="101" values="1|2|3|4|5|6|7|8|9|10" default="5" />
        <setting id="time-of-day" type="enum" values="All|Day only|Night only|Smart" label="32006" visible="true" default="0"/>
        ```

      - `slider`
        - Allows the user to enter a number using a horizontal sliding bar.
          * **`id="string"`** (required) - the name of the setting.
          * **`label="id"`** (required) - an id from the language file that indicates which text to display.
          * **`range="min[,step],max"`** (required) - specify the range of valid values.
          * **`option="int"|"float"|"percent"`** (required) - specifies whether to allow the user to choose between 
                                                 integers, floating point numbers or a percentage.
          * **`default="value"`** (optional) - the default value.
      	```xml
        <setting id="kodion.cache.size" type="slider" label="30024" default="5" range="1,1,20" option="int"/>
        <setting label="32053" type="slider" id="limit" default="20" range="5,5,100" option="int" />
        <setting label="32053" type="slider" id="limit" default="20" range="0,100"/>
        ```

        Code example:
        ```cpp
        #include <kodi/addon.api2/General.h>

        int cachesize = 5;
        if (!CAddOnLib_General::GetSettingInt("kodion.cache.size", bitrate))
          CAddOnLib_General::Log(LOG_ERROR, "Couldn't get 'kodion.cache.size' setting, falling back to default");
        ```

-------------
*  <a id="GetSettingBoolean">
   **`bool CAddOnLib_General::GetSettingBoolean(const std::string& settingName, bool& settingValue, bool global = false);`**
    * Get a boolean settings value for this add-on.
      * **`settingName`:** The name of the setting to get.
      * **`settingValue`:** The value.
      * **`global`:** If set to true becomes Kodi itself asked about a setting _(Default: `false`)_.
      * **return:** true if successfull done

      **Boolean type examples for add-on `./resources/settings.xml`:**
      - `bool`
        - Shows a boolean check point to settings dialog
          * **`id="string"`** (required) - the name of the setting
          * **`label="id"`** (required) - an id from the language file that indicates which text to display.
          * **`default="true"|"false"`** (optional) - the default value.
      	```xml
        <setting id="kodion.setup_wizard" type="bool" label="30025" default="true"/>
        <setting id="show-notifications" type="bool" label="32018" default="true" />
        ```

        Code example:
        ```cpp
        #include <kodi/addon.api2/General.h>

        bool show_notifications = true;
        if (!CAddOnLib_General::GetSettingBoolean("show-notifications", show_notifications))
          CAddOnLib_General::Log(LOG_ERROR, "Couldn't get 'show-notifications' setting, falling back to default");
        ```

-------------
*  <a id="GetSettingFloat">
   **`bool CAddOnLib_General::GetSettingFloat(const std::string& settingName, float& settingValue, bool global = false);`**
    * Get a float settings value for this add-on.
      * **`settingName`:** The name of the setting to get.
      * **`settingValue`:** The value.
      * **`global`:** If set to true becomes Kodi itself asked about a setting _(Default: `false`)_.
      * **return:** true if successful done

      **Floating type examples for add-on `./resources/settings.xml`:**
      - `slider`
        - Shows a moveable slider control to get values from range
      	```xml
        <setting id="kodi.amplication.volume" type="slider" label="30024" default="1.0" range="0.0,0.1,2.0" option="float"/>
        ```

        Code example:
        ```cpp
        #include <kodi/addon.api2/General.h>

        float volume = 1.0;
        if (!CAddOnLib_General::GetSettingFloat("kodi.amplication.volume", volume))
          CAddOnLib_General::Log(LOG_ERROR, "Couldn't get 'kodi.amplication.volume' setting, falling back to default");
        ```

-------------
*  <a id="Log">
   **`void CAddOnLib_General::Log(const addon_log_t loglevel, const char* format, ...);`**
    * Add a message to [KODI's log](http://kodi.wiki/view/Log_file/Advanced#Log_levels).
      * **`loglevel`:** The log level of the message

        |  enum code:  | Description:          |
        |-------------:|-----------------------|
        |  LOG_DEBUG   | In depth information about the status of Kodi. This information can pretty much only be deciphered by a developer or long time Kodi power user.
        |  LOG_INFO    | Something has happened. It's not a problem, we just thought you might want to know. Fairly excessive output that most people won't care about.
        |  LOG_NOTICE  | Similar to INFO but the average Joe might want to know about these events. This level and above are logged by default.
        |  LOG_WARNING | Something potentially bad has happened. If Kodi did something you didn't expect, this is probably why. Watch for errors to follow.
        |  LOG_ERROR   | This event is bad. Something has failed. You likely noticed problems with the application be it skin artifacts, failure of playback a crash, etc.
        |  LOG_FATAL   | We're screwed. Kodi is about to crash.
      * **`format`:** The format of the message to pass to KODI.
      * **`...`:** Added string values

*  <a id="QueueNotification_1">
   **`void CAddOnLib_General::QueueNotification(const queue_msg_t  type, const char* format, ...);`**
    * Queue a notification in the GUI.
      * **`type`:** The message type.

        |  enum code:    | Description:                      |
        |---------------:|-----------------------------------|
        |  QUEUE_INFO    | Show info notification message    |
        |  QUEUE_WARNING | Show warning notification message |
        |  QUEUE_ERROR   | Show error notification message   |
      * **`format`:** The format of the message to pass to display in Kodi.
      * **`...`:** Added string values

*  <a id="QueueNotification_2">
   **`void CAddOnLib_General::QueueNotification(const queue_msg_t  type, const std::string& aCaption, const std::string& aDescription, unsigned int displayTime = 5000, bool withSound = true, unsigned int messageTime = 1000);`**
    * Queue a notification in the GUI.
      * **`type`:** The message type.

        |  enum code:    | Description:                      |
        |---------------:|-----------------------------------|
        |  QUEUE_INFO    | Show info notification message    |
        |  QUEUE_WARNING | Show warning notification message |
        |  QUEUE_ERROR   | Show error notification message   |
      * **`aCaption`:** Header Name
      * **`aDescription`:** Message to display on Kodi
      * **`displayTime`:** The time how long message is displayed _(default 5 sec)_
      * **`withSound`:** if true also warning sound becomes played _(default with sound)_
      * **`messageTime`:** how many milli seconds start show of notification _(default 1 sec)_

*  <a id="QueueNotification_3">
   **`void CAddOnLib_General::QueueNotification(const std::string& aCaption, const std::string& aDescription);`**
    * Queue a notification in the GUI.
      * **`aCaption`:** Header Name
      * **`aDescription`:** Message to display on Kodi

*  <a id="QueueNotification_4">
   **`void CAddOnLib_General::QueueNotification(const std::string& aImageFile, const std::string& aCaption, const std::string& aDescription, unsigned int displayTime = 5000, bool withSound   = true, unsigned int messageTime = 1000);`**
    * Queue a notification in the GUI.
      * **`aImageFile`:** The image file to show on message
      * **`aCaption`:** Header Name
      * **`aDescription`:** Message to display on Kodi
      * **`displayTime`:** The time how long message is displayed _(default 5 sec)_
      * **`withSound`:** true also warning sound becomes played _(default with sound)_
      * **`messageTime`:** in how many milli seconds start show of notification _(default 1 sec)_

*  <a id="GetMD5">
   **`void CAddOnLib_General::GetMD5(const std::string& text, std::string& md5);`**
    * Get the MD5 digest of the given text
      * **`text`:** text to compute the MD5 for
      * **`md5`:** Returned MD5 digest

*  <a id="UnknownToUTF8">
   **`bool CAddOnLib_General::UnknownToUTF8(const std::string& stringSrc, std::string& utf8StringDst, bool failOnBadChar = false);`**
    * Translate a string with an unknown encoding to UTF8.
      * **`stringSrc`:** The string to translate.
      * **`utf8StringDst`:** The translated string.
      * **`failOnBadChar`:** return failed if bad character is inside _(default is `false`)_
      * **return:** true if OK

*  <a id="GetLocalizedString">
   **`std::string CAddOnLib_General::GetLocalizedString(uint32_t labelId, const std::string&  strDefault = "") const;`**
    * Get a localized message.
      * **`labelId`:** The code of the message to get.
      * **`strDefault`:** The default message, also helps to identify the code that is used
      * **return:** The localized message, or strDefault if the add-on helper fails to return a message

*  <a id="GetLanguage">
   **`std::string CAddOnLib_General::GetLanguage(lang_formats format = LANG_FMT_ENGLISH_NAME, bool region = false) const;`**
    * Returns the active language as a string.
      * **`format`:** Used format of the returned language string

        | enum code:            | Description:                                               |
        |----------------------:|------------------------------------------------------------|
        | LANG_FMT_ENGLISH_NAME | full language name in English (Default)                    |
        | LANG_FMT_ISO_639_1    | two letter code as defined in ISO 639-1                    |
        | LANG_FMT_ISO_639_2    | three letter code as defined in ISO 639-2/T or ISO 639-2/B |
      * **`region`:** append the region delimited by "-" of the language (setting) to the returned language string

*  <a id="GetDVDMenuLanguage">
   **`std::string CAddOnLib_General::GetDVDMenuLanguage();`**
    * Get the DVD menu language.
      * **return:** The DVD menu langauge, or empty if unknown

*  <a id="StartServer">
   **`bool CAddOnLib_General::StartServer(eservers typ, bool start, bool wait = false);`**
    * start or stop a server.
      * **`typ`:** Used format of the returned language string

        | enum code:             | Description:                                               |
        |-----------------------:|------------------------------------------------------------|
        | ADDON_ES_WEBSERVER     | [To control Kodi's builtin webserver](http://kodi.wiki/view/Webserver)
        | ADDON_ES_AIRPLAYSERVER | [AirPlay is a proprietary protocol stack/suite developed by Apple Inc.](http://kodi.wiki/view/AirPlay)
        | ADDON_ES_JSONRPCSERVER | [Control JSON-RPC HTTP/TCP socket-based interface](http://kodi.wiki/view/JSON-RPC_API)
        | ADDON_ES_UPNPRENDERER  | [UPnP client (aka UPnP renderer)](http://kodi.wiki/view/UPnP/Client)
        | ADDON_ES_UPNPSERVER    | [Control built-in UPnP A/V media server (UPnP-server)](http://kodi.wiki/view/UPnP/Server)
        | ADDON_ES_EVENTSERVER   | [Set eventServer part that accepts remote device input on all platforms](http://kodi.wiki/view/EventServer)
        | ADDON_ES_ZEROCONF      | [Control Kodi's Avahi Zeroconf](http://kodi.wiki/view/Zeroconf)
      * **`start`:** start (True) or stop (False) a server
      * **`wait`:** wait on stop before returning (not supported by all servers)
      * **return:** true if successfull done

*  <a id="AudioSuspend">
   **`void CAddOnLib_General::AudioSuspend();`**
    * Suspend Audio engine

*  <a id="AudioResume">
   **`void CAddOnLib_General::AudioResume();`**
    * Resume Audio engine

*  <a id="GetVolume">
   **`float CAddOnLib_General::GetVolume(bool percentage = true);`**
    * Get the current global Kodi audio volume
      * **`percentage`:** if set to false becomes amplication level returned
      * **return:** The volume value

*  <a id="SetVolume">
   **`void CAddOnLib_General::SetVolume(float value, bool isPercentage = true);`**
    * Set the current global Kodi audio volume
      * **`value`:** the volume to use
      * **`isPercentage`:** if set to false becomes amplication level use

*  <a id="IsMuted">
   **`bool CAddOnLib_General::IsMuted();`**
    * Ask if Kodi audio is muted
      * **return:** true if audio is muted

*  <a id="ToggleMute">
   **`void CAddOnLib_General::ToggleMute(void);`**
    * Toggle the audio volume between on and off

*  <a id="SetMute">
   **`void CAddOnLib_General::SetMute(bool mute);`**
    * Set Kodi's mute
      * **`mute`:** with set to true becomes it muted otherwise audio is present

*  <a id="GetOpticalDriveState">
   **`dvd_state CAddOnLib_General::GetOpticalDriveState();`**
    * Returns the dvd state as an integer
      * **return:** state

        | enum code:                | Description:                                               |
        |--------------------------:|------------------------------------------------------------|
        | DRIVE_NOT_READY           | Not present or Opening... Closing...                       |
        | TRAY_OPEN                 | two letter code as defined in ISO 639-1                    |
        | TRAY_CLOSED_NO_MEDIA      | closed, but no media in drive                              |
        | TRAY_CLOSED_MEDIA_PRESENT | closed with media present inside                           |

*  <a id="EjectOpticalDrive">
   **`bool CAddOnLib_General::EjectOpticalDrive();`**
    * Send eject signal to optical drive
      * **return:** true if successfull done

*  <a id="KodiVersion">
   **`void CAddOnLib_General::KodiVersion(kodi_version_t& version);`**
	```cpp
	  typedef struct kodi_version
	  {
	    std::string compile_name;
	    int         major;
	    int         minor;
	    std::string revision;
	    std::string tag;
	    std::string tag_revision;
	  } kodi_version_t;
	```
    * Get current Kodi informations and versions, returned data from the following
        `kodi_version_t version; CAddOnLib_General::KodiVersion(version);`
      is e.g.:
	```cpp
		version.compile_name = Kodi
		version.major        = 16
		version.minor        = 0
		version.revision     = 2015-11-30-74edffb-dirty
		version.tag          = beta
		version.tag_revision = 1
	```
	*  **`version`** version structure to store data from kodi
	*  Example:
	```cpp
  kodi_version_t version;
  CAddOnLib_General::KodiVersion(version);
  fprintf(stderr,
	    "kodi_version_t version;\n"
	    "CAddOnLib_General::KodiVersion(version);\n"
	    " - version.compile_name = %s\n"
	    " - version.major        = %i\n"
	    " - version.minor        = %i\n"
	    " - version.revision     = %s\n"
	    " - version.tag          = %s\n"
	    " - version.tag_revision = %s\n",
	    	    version.compile_name.c_str(), version.major, version.minor,
	    	    version.revision.c_str(), version.tag.c_str(), version.tag_revision.c_str());
	```
*  <a id="KodiQuit">
   **`void CAddOnLib_General::KodiQuit();`**
    * Tell Kodi to stop work, go to exit and stop his work.
      * ***WARNING:*** Kodi is really quited!

*  <a id="HTPCShutdown">
   **`void CAddOnLib_General::HTPCShutdown();`**
    * Shutdown the htpc

*  <a id="HTPCRestart">
   **`void CAddOnLib_General::HTPCRestart();`**
    * Restart the htpc

*  <a id="ExecuteScript">
   **`void CAddOnLib_General::ExecuteScript(const std::string& script);`**
    * Execute a python script
      * **`script`:** filename to execute

*  <a id="ExecuteBuiltin">
   **`void CAddOnLib_General::ExecuteBuiltin(const std::string& function, bool wait = false);`**
    * Execute a built in Kodi function
      * **`function`:** function builtin function to execute
      * **`wait`:** wait if true wait until finished

*  <a id="ExecuteJSONRPC">
   **`std::string CAddOnLib_General::ExecuteJSONRPC(const std::string& jsonrpccommand) const;`**
    * Execute an JSONRPC command
      * **`jsonrpccommand`:** jsonrpc command to execute
      * **return:** From jsonrpc returned string for command

*  <a id="GetRegion">
   **`std::string CAddOnLib_General::GetRegion(const std::string& id) const;`**
    * Returns your regions setting as a string for the specified id
      * **`id`:** id of setting to return

        |              | Choices are  |              |
        |:------------:|:------------:|:------------:|
        |  dateshort   | time         | tempunit     |
        |  datelong    | meridiem     | speedunit    |
      * **return:** settings string

*  <a id="GetFreeMem">
   **`long CAddOnLib_General::GetFreeMem();`**
    * Returns the amount of free memory in MB as an integer
      * **return:** free memory

*  <a id="GetGlobalIdleTime">
   **`int CAddOnLib_General::GetGlobalIdleTime();`**
    * Returns the elapsed idle time in seconds as an integer
      * **return:** idle time

*  <a id="TranslateAddonStatus">
   **`std::string CAddOnLib_General::TranslateAddonStatus(ADDON_STATUS status);`**
    * Translate an add-on status return code into a human-readable string
      * **`status`:** The return code
      * **return:** A human-readable string suitable for logging

*  <a id="GetAddonInfo">
   **`std::string CAddOnLib_General::GetAddonInfo(std::string& id) const;`**
    * Returns the value of an addon property as a string
      * **`id`:** id of the property that the module needs to access

        |              | Choices are  |              |
        |:------------:|:------------:|:------------:|
        |  author      | icon         | stars        |
        |  changelog   | id           | summary      |
        |  description | name         | type         |
        |  disclaimer  | path         | version      |
        |  fanart      | profile      |              |
      * **return:** Returned information string