# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md#CAddonGUIButtonControl)
</p>*
#### *<p align="center">Binary add-on GUI library, Version Level: 2</p>*
## *<p align="center">Button control</p>*
-------------

The button control is used for creating push buttons in Kodi. You can choose the position, size, and look of the button, as well as choosing what action(s) should be performed when pushed.

It has the header [`#include <kodi/gui.api2/GUIControlButton.h>`](../GUIControlButton.h) be included to enjoy it.

> ***Note:*** The call of the control is only possible from the corresponding window as its class and identification number is required.

Skin XML
-------------

Example below shows the most of possible parts for xml file of related Window / Dialog. Not all are really required and must be checked during creation on skin.

> ***Note:*** The example below is shown for add-on development from code, skin developers should follow the [Kodi Wiki](http://kodi.wiki/view/Skinning).

```xml
	<control type="button" id="10">
		<description>My first button control</description>
		<posx>80</posx>
		<posy>60</posy>
		<width>250</width>
		<height>200</height>
		<visible>true</visible>
		<colordiffuse>FFFFFFFF</colordiffuse>
		<texturefocus colordiffuse="FFFFAAFF">myfocustexture.png</texturefocus>
		<texturenofocus colordiffuse="FFFFAAFF">mynormaltexture.png</texturenofocus>
		<label>29</label>
		<wrapmultiline>true</wrapmultiline>
		<font>font12</font>
		<textcolor>FFFFFFFF</textcolor>
		<focusedcolor>FFFFFFFF</focusedcolor>
		<disabledcolor>80FFFFFF</disabledcolor>
		<invalidcolor>FFFFFFFF</invalidcolor>
		<align></align>
		<aligny></aligny>
		<textoffsetx></textoffsetx>
		<textoffsety></textoffsety>
		<pulseonselect></pulseonselect>
		<onclick>XBMC.ActivateWindow(MyVideos)</onclick>
		<onfocus>-</onfocus>
		<onunfocus>-</onunfocus>
		<onup>2</onup>
		<ondown>3</ondown>
		<onleft>1</onleft>
		<onright>1</onright>
	</control>
```

**Possible values:**
- **`control type="button"`:** Control type name on xml
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
  - **`visible`:** Specifies a condition as to when this control will be visible. Can be true, false, or a condition. See [Conditional Visibility](http://kodi.wiki/view/Conditional_Visibility) for more information. Defaults to true, can also be done by `void SetVisible(bool visible);`
  - **`enable`:** Needed [condition](http://kodi.wiki/view/Conditional_Visibility) to have enabled, can also be done by `void SetEnabled(bool enabled);`

- **Control dependent:** ([see Kodi wiki "Button Control" for details](http://kodi.wiki/view/Button_control)):
  - **`texturefocus`:** Specifies the image file which should be displayed when the button has focus. [See here for additional information about textures](http://kodi.wiki/view/Texture_Attributes).
  - **`texturenofocus`:** Specifies the image file which should be displayed when the button does not have focus.
  - **`label`:** The label used on the button. It can be a link into strings.xml, or an actual text label. Can be leaved empty if set by `void SetText(const std::string& text)`;
  - **`font`:**	Font used for the button label. From fonts.xml.
  - **`textcolor`:** Color used for displaying the button label. In **AARRGGBB** hex format, or a name from the [colour theme](http://kodi.wiki/view/Colour_Themes).
  - **`focusedcolor`:** Color used for the button label when the button has in focus. In **AARRGGBB** hex format or a name from the [colour theme](http://kodi.wiki/view/Colour_Themes).
  - **`disabledcolor`:** Color used for the button label if the button is disabled. In **AARRGGBB** hex format or a name from the [colour theme](http://kodi.wiki/view/Colour_Themes).
  - **`invalidcolor`:** Color used for the button if the user entered some invalid value. In **AARRGGBB** hex format or a name from the [colour theme](http://kodi.wiki/view/Colour_Themes).
  - **`shadowcolor`:** Specifies the color of the drop shadow on the text, in **AARRGGBB** format, or a name from the colour theme.
  - **`angle`:** The angle the text should be rendered at, in degrees. A value of `0` is horizontal.
  - **`align`:** Label horizontal alignment on the button. Defaults to left, can also be center or right.
  - **`aligny`:** Label vertical alignment on the button. Defaults to top, can also be center.
  - **`textoffsetx`:** Amount to offset the label from the left (or right) edge of the button when using left or right alignment.
  - **`textoffsety`:** Amount to offset the label from the top edge of the button when using top alignment.
  - **`textwidth`:** Will truncate any text that's too long.
  - **`onclick`:** Specifies the action to perform when the button is pressed. Should be a built in function. [See here for more information](http://kodi.wiki/view/Built-in_functions_available_to_FTP,_Webserver,_skins,_keymap_and_to_python). You may have more than one `<onclick>` tag, and they'll be executed in sequence. Can be leaved empty and controlled by function `bool CAddonGUIWindow::OnClick(int controlId)`.
  - **`onfocus`:** Specifies the action to perform when the button is focused. Should be a built in function. The action is performed after any focus animations have completed. [See here for more information](http://kodi.wiki/view/Built-in_functions_available_to_FTP,_Webserver,_skins,_keymap_and_to_python). Can be leaved empty and controlled by function `bool CAddonGUIWindow::OnFocus(int controlId)`
  - **`onunfocus`:** Specifies the action to perform when the button loses focus. Should be a built in function.
  - **`wrapmultiline`:** Will wrap the label across multiple lines if the label exceeds the control width.

C++ Classes
-------------

#### Class: `CAddonGUIButtonControl::CAddonGUIButtonControl();`

> ***NOTE:*** This class functions are used to override the on window `*.xml` defined control values.

*  **`CAddonGUIButtonControl(CAddonGUIWindow* window, int controlId);`**
    * Construct a new control
      * **`window`:** related window control class
      * **`controlId`:** Used skin xml control id

*  **`virtual ~CAddonGUIButtonControl();`**
    * Destructor

*  **`void SetVisible(bool visible);`**
    * Set the control on window to visible
      * **`visible`:** If true visible, otherwise hidden

*  **`void SetEnabled(bool enabled);`**
    * Set's the control's enabled/disabled state.
      * **`enabled`:** If true enabled, otherwise disabled

*  **`void SetLabel(const std::string& text);`**
    * To set the text string on button.
      * **`text`:** Text to show

*  **`std::string GetLabel() const;`**
    * Get the used text from button
      * **return:** Text shown

*  **`void SetLabel2(const std::string& text);`**
    * If two labels are used for button becomes it set with them
      * **`text`:** Text for second label

*  **`std::string GetLabel2() const;`**
    * Get the second label if present
      * **return:** Second label
