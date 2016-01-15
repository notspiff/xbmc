# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md#CAddonGUIDialogExtendedProgress)
</p>*
#### *<p align="center">GUI dialog</p>*
-------------

The with `#include <kodi/addon.api2/GUIDialogExtendedProgress.h>` given class are basically used to create Kodi's extended progress

##### Progress dialog shown for background work

Code example:
```cpp
#include <kodi/addon.api2/GUIDialogExtendedProgress.h>

CAddonGUIDialogExtendedProgress *ext_progress = new CAddonGUIDialogExtendedProgress("Test Extended progress");
ext_progress->SetText("Test progress");
for (unsigned int i = 0; i < 50; i += 10)
{
  ext_progress->SetProgress(i, 100);
  sleep(1);
}

ext_progress->SetTitle("Test Extended progress - Second round");
ext_progress->SetText("Test progress - Step 2");

for (unsigned int i = 50; i < 100; i += 10)
{
  ext_progress->SetProgress(i, 100);
  sleep(1);
}
delete ext_progress;
```

-------------

*<p align="center">![SUID](help.GUIDialogExtendedProgress.png)</p>*

Classes
-------------

#### Class: `CAddonGUIDialogExtendedProgress::CAddonGUIDialogExtendedProgress();`

It use the **DialogExtendedProgressBar.xml** skin file from Kodi.

*  **`CAddonGUIDialogExtendedProgress(const std::string& title = "");`**
    * Construct a new dialog
      * **`title`:** 

*  **`~CAddonGUIDialogExtendedProgress();`**
    * Destructor

*  **`std::string Title() const;`**
    * Get the used title
      * **Return:** Title string

*  **`void SetTitle(const std::string& strTitle);`**
    * To set the title of dialog
      * **`strTitle`:** Title string

*  **`std::string Text() const;`**
    * Get the used text information string
      * **Return:** Text string

*  **`void SetText(const std::string& strText);`**
    * To set the used text information string
      * **`strText`:** 

*  **`bool IsFinished() const;`**
    * To ask dialog is finished
      * **Return:** True if on end

*  **`void MarkFinished();`**
    * Mark progress finished

*  **`float Percentage() const;`**
    * Get the current progress position as percent
      * **Return:** Position

*  **`void SetPercentage(float fPercentage);`**
    * To set the current progress position as percent
      * **`fPercentage`:** Position to use from 0.0 to 100.0

*  **`void SetProgress(int currentItem, int itemCount);`**
    * To set progress position with predefined places
      * **`currentItem`:** Place position to use
      * **`itemCount`:** Amount of used places
