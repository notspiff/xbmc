# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md#CAddonGUISpinControl)
</p>*
#### *<p align="center">Binary add-on GUI library, Version Level: 2</p>*
## *<p align="center">Text box control</p>*
-------------

General
-------------

The text box control can be used to display descriptions, help texts or other larger texts. It corresponds to the representation which is also to be seen on the [CAddonGUIDialogTextViewer](CAddonGUIDialogTextViewer.md).

In order to achieve a line break is a `\n` directly in the text or in the ***"./resources/language/resource.language.??_??/strings.po"*** to call with [`std::string CAddOnLib_General::GetLocalizedString(...);`](..//../addon.api2/docs/General.md#CAddOnLib_General_GetLocalizedString).

It has the header [`#include <kodi/gui.api2/GUIControlTextBox.h>`](../GUIControlTextBox.h) be included to enjoy it.

> ***Note:*** The call of the control is only possible from the corresponding window as its class and identification number is required.

Skin XML
-------------

Example below shows the most of possible parts for xml file of related Window / Dialog. Not all are really required and must be checked during creation on skin.

> ***Note:*** The example below is shown for add-on development from code, skin developers should follow the [Kodi Wiki](http://kodi.wiki/view/Skinning).

```xml
	<control type="textbox" id ="10">
		<description>description area</description>
		<onleft>9</onleft>
		<onright>11</onright>
		<onup>5</onup>
		<ondown>6</ondown>
		<left>320</left>
		<top>60</top>
		<width>736</width>
		<height>200</height>
		<font>font12</font>
		<label>Test label</label>
		<align>justify</align>
		<pagecontrol>-</pagecontrol>
		<textcolor>white</textcolor>
		<autoscroll time="3000" delay="4000" repeat="5000">true</autoscroll>
		<visible>Control.Hasfocus(4)</visible>
	</control>
```
**Possible values:**
- **`control type="textbox"`:** Control type name on xml
- **`id="10"`:** Id to communicate with other controls (required if accessed of code)
- **Global:** ([see Kodi wiki "Default control tags" for details](http://kodi.wiki/view/Default_Control_Tags))
  - **`description`:** Only used to make things clear for the skinner. Not read by Kodi at all.
  - **`onleft`:** Jump to control on left
  - **`onright`:** Jump to control on right
  - **`onup`:** Jump to control on up
  - **`ondown`:** Jump to control on down
  - **`left`:** Position from left (optional can `right` be used)
  - **`right`:** Position from right (optional can `left` be used)
  - **`top`:** Position from top (optional can `bottom` be used)
  - **`bottom`:** Position from bottom (optional can `top` be used)
  - **`width`:** Width of control on skin
  - **`height`:** Height of control on skin
  - **`visible`:** Needed condition to have visible, can also be done by `void SetVisible(bool visible);`

- **Control dependent:** ([see Kodi wiki "Settings Spin Control" for details](http://kodi.wiki/view/Settings_Spin_Control)):
  - **`label`:** Label to use, can be leaved empty if set by `void SetText(const std::string& text);`
  - **`font`:** Used skin font for text
  - **`textcolor`:** Color used for displaying the label. In **AARRGGBB** hex format, or a name from the [colour theme](http://kodi.wiki/view/Colour_Themes).
  - **`align`:** Text horizontal alignment
    - `left`: Align text to left
    - `center`: Align text to center
    - `right`: Align text to right
    - `justify`: Expand text to line width
  - **`pagecontrol`:** (Optional) If used, include id of a other control to handle page changes
  - **`autoscroll`:** Set autoscrolling times, can also be done by `void SetAutoScrolling(int delay, int time, int repeat);`
    - `delay`: integer - Scroll delay (in ms) time
    - `time`: integer - Scroll time (in ms) repeat
    - `repeat`: integer - Repeat time

> ***Note:*** Check always used skin on Kodi about default values for control.

C++ Classes
-------------

#### Class: `CAddonGUITextBoxControl::CAddonGUITextBoxControl();`

> ***Note:*** This class functions are used to override the on window `*.xml` defined control values.

*  **`CAddonGUITextBoxControl(CAddonGUIWindow* window, int controlId);`**
    * Construct a new control
      * **`window`:** related window control class
      * **`controlId`:** Used skin xml control id

*  **`virtual ~CAddonGUITextBoxControl();`**
    * Destructor

*  **`void SetVisible(bool visible);`**
    * Set's the control's visible/hidden state.
    * ***Note:*** It is recommended the path of the XML to use.
      * **`visible`:** If true visible, otherwise hidden

*  **`bool IsVisible();`**
    * Get's the control's visible/hidden state.
      * **return:** If true visible, otherwise hidden

*  **`void Reset();`**
    * Clear's this textbox.

*  **`void SetText(const std::string& text);`**
    * Set the text value for this textbox.
      * **`text`:** The text.

*  **`std::string GetText();`**
    * Returns the text value for this textbox.
    * ***Note*** Does not work on `bool CAddonGUIWindow::OnInit()`
      * **return:** Text shown

*  **`void Scroll(unsigned int position);`**
    * Scrolls to the given position.
    * ***Note*** Does not work on `bool CAddonGUIWindow::OnInit()`
      * **`position`:** Position to scroll to.

*  **`void SetAutoScrolling(int delay, int time, int repeat);`**
    * Set autoscrolling times
    * ***Note:*** It is recommended the path of the XML to use.
      * **`delay`:** Scroll delay (in ms).
      * **`time`:** Scroll time (in ms).
      * **`repeat`:** Repeat time.
