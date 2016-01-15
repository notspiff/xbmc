# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="https://github.com/EsMaSol/mupel/blob/master/icons/back-button.png" alt="Back" width="100" height="40">](../Readme.md#CAddonGUICheckMarkControl)
</p>*
#### *<p align="center">GUI control class</p>*
-------------

The with `#include <kodi/addon.api2/AddonGUICheckMarkControl.h>` given functions are basically used to control GUI check mark on a window.

Classes
-------------

#### Class: `CAddonGUICheckMarkControl::CAddonGUICheckMarkControl();`

> ***NOTE:*** This class functions are used to override the on window `*.xml` defined control values.

*  **`CAddonGUICheckMarkControl(CAddonGUIWindow* window, int controlId);`**
    * Construct a new control
      * **`window`:** related window control class
      * **`controlId`:** Used skin xml control id

*  **`virtual ~CAddonGUICheckMarkControl();`**
    * Destructor

*  **`virtual void SetVisible(bool visible);`**
    * Set the control on window to visible
      * **`visible`:** If true visible, otherwise hidden

*  **`virtual void SetLabel(const std::string& text);`**
    * To set the text string on button.
      * **`text`:** Text to show

*  **`virtual std::string GetLabel() const;`**
    * Get the used text from button
      * **return:** Text shown

*  **`virtual void SetSelected(bool selected);`**
    * To select the label on GUI
      * **`selected`:** if true becomes it selected

*  **`virtual bool GetSelected();`**
    * Check the control selected
      * **return:** True if control selected
