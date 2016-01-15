# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md#CAddonGUIDialogOK)
</p>*
#### *<p align="center">Binary add-on GUI library, Version Level: 2</p>*
## *<p align="center">OK dialog</p>*
-------------

General
-------------

The functions listed below permit the call of a dialogue of information, a confirmation of the user by press from OK required.

It has the header [`#include <kodi/gui.api2/GUIDialogOK.h>`](../GUIDialogOK.h) be included to enjoy it.

Functions
-------------

1. [void ShowAndGetInput(const std::string& heading, const std::string& text);](#CAddonGUIDialogOK_ShowAndGetInput_1)
* [void ShowAndGetInput(const std::string& heading, const std::string& line0, const std::string& line1, const std::string& line2);](#CAddonGUIDialogOK_ShowAndGetInput_2)

-------------

*<p align="center">![SUID](help.GUIDialogOK.png)</p>*

-------------

*  <a id="CAddonGUIDialogOK_ShowAndGetInput_1"></a>
**`void CAddonGUIDialogOK::ShowAndGetInput(const std::string& heading, const std::string& text);`**
    * Use dialog to inform user with text and confirmation with OK with continued string.
      * **`heading`:** Dialog heading.
      * **`text`:** Multi-line text.

    Code example:
    ```cpp
    #include <kodi/gui.api2/GUIDialogOK.h>

    CAddonGUIDialogOK::ShowAndGetInput("Test dialog", "Hello World!\nI'm a call from add-on\n :) :D");
    ```

*  <a id="CAddonGUIDialogOK_ShowAndGetInput_2"></a>
**`void CAddonGUIDialogOK::ShowAndGetInput(const std::string& heading, const std::string& line0, const std::string& line1, const std::string& line2);`**
    * Use dialog to inform user with text and confirmation with OK with strings separated to the lines.
      * **`heading`:** Dialog heading.
      * **`line0`:** Line #1 text.
      * **`line1`:** Line #2 text.
      * **`line2`:** Line #3 text.

    Code example:
    ```cpp
    #include <kodi/gui.api2/GUIDialogOK.h>

    CAddonGUIDialogOK::ShowAndGetInput("Test dialog", "Hello World!", "I'm a call from add-on", " :) :D");
    ```
