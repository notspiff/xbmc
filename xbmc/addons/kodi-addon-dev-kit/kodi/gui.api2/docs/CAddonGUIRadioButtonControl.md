# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md#CAddonGUIRadioButtonControl)
</p>*
#### *<p align="center">Binary add-on GUI library, Version Level: 2</p>*
## *<p align="center">Radio button control</p>*
-------------

The radio button control is used for creating push button on/off settings in XBMC. You can choose the position, size, and look of the button. When the user clicks on the radio button, the state will change, toggling the extra textures (textureradioon and textureradiooff). Used for settings controls.

It has the header [`#include <kodi/gui.api2/GUIControlRadioButton.h>`](../GUIControlRadioButton.h) be included to enjoy it.

> ***Note:*** The call of the control is only possible from the corresponding window as its class and identification number is required.

Skin XML
-------------

Example below shows the most of possible parts for xml file of related Window / Dialog. Not all are really required and must be checked during creation on skin.

> ***Note:*** The example below is shown for add-on development from code, skin developers should follow the [Kodi Wiki](http://kodi.wiki/view/Skinning).

```xml
	<control type="radiobutton" id="2">
		<description>My first radiobutton control</description>
		<type>radiobutton</type>
		<left>80</left>
		<top>60</top>
		<width>250</width>
		<height>200</height>
		<visible>true</visible>
		<colordiffuse>FFFFFFFF</colordiffuse>
		<texturefocus>myfocustexture.png</texturefocus>
		<texturenofocus>mynormaltexture.png</texturenofocus>
		<textureradioonfocus colordiffuse="FFFFAAFF">myradiobutton.png</textureradioonfocus>
		<textureradioonnofocus colordiffuse="FFFFAAFF">myradiobutton.png</textureradioonnofocus>
		<textureradioofffocus colordiffuse="FFFFAAFF">myradiobutton_nf.png</textureradioofffocus>
		<textureradiooffnofocus colordiffuse="FFFFAAFF">myradiobutton_nf.png</textureradiooffnofocus>
		<selected>Player.Paused</selected>
		<onclick>PlayerControls(Pause)</onclick>
		<label>29</label>
		<font>font12</font>
		<textcolor>FFFFFFFF</textcolor>
		<focusedcolor>FFFFFFFF</focusedcolor>
		<disabledcolor>80FFFFFF</disabledcolor>
		<align>left</align>
		<aligny>center</aligny>
		<textoffsetx>4</textoffsetx>
		<textoffsety>5</textoffsety>
		<pulseonselect>false</pulseonselect>
		<onfocus>-</onfocus>
		<onunfocus>-</onunfocus>
		<onup>2</onup>
		<ondown>3</ondown>
		<onleft>1</onleft>
		<onright>1</onright>
	</control>
```

**Possible values:**
- **`control type="radiobutton"`:** Control type name on xml
- **`id="2"`:** Id to communicate with other controls (required if accessed of code)
- **Global:** ([see Kodi wiki "Default control tags" for details](http://kodi.wiki/view/Default_Control_Tags))
  - **`description`:** Only used to make things clear for the skinner. Not read by Kodi at all.
  - **`left`:** Position from left (optional can `right` be used)
  - **`right`:** Position from right (optional can `left` be used)
  - **`top`:** Position from top (optional can `bottom` be used)
  - **`bottom`:** Position from bottom (optional can `top` be used)
  - **`width`:** Width of control on skin
  - **`height`:** Height of control on skin
  - **`visible`:** Specifies a condition as to when this control will be visible. Can be true, false, or a condition. See [Conditional Visibility](http://kodi.wiki/view/Conditional_Visibility) for more information. Defaults to true, can also be done by `void SetVisible(bool visible);`

- **Control dependent:** ([see Kodi wiki "Radio button Control" for details](http://kodi.wiki/view/Radio_button_control)):
- **`texturefocus`:** 
Specifies the image file which should be displayed when the button has focus. [See here for additional information about textures](http://kodi.wiki/view/Texture_Attributes).
- **`texturenofocus`:** Specifies the image file which should be displayed when the button does not have focus.
- **`textureradioonfocus`:** Specifies the image file which should be displayed for the radio button portion when it's the button is on and focused. This texture is positioned on the right of the button – it's positioned 24 pixels from the right edge of the button, and 8 pixels above the center vertically.
- **`textureradioonnofocus`:** Specifies the image file which should be displayed for the radio button portion when it's the button is on and unfocused. This texture is positioned on the right of the button – it's positioned 24 pixels from the right edge of the button, and 8 pixels above the center vertically.
- **`textureradioon`:** A shortcut to set both of the above textures to the same image file.
- **`textureradioondisabled`:** Specifies the image file which should be displayed for the radio button portion when the button is on and disabled.
- **`textureradioofffocus`:** Specifies the image file which should be displayed for the radio button portion when the button is off and focused.
- **`textureradiooffnofocus`:** Specifies the image file which should be displayed for the radio button portion when the button is off and unfocused.
- **`textureradiooff`:** A shortcut to set both of the above textures to the same image file.
- **`textureradioondisabled`:** Specifies the image file which should be displayed for the radio button portion when the button is off and disabled.
- **`label`:** The label used on the button. It can be a link into strings.xml, or an actual text label.
- **`label2`:** Optional. Will display an `on` or `off` label. Only available if you specify an empty radiowidth and radioheight.
- **`font`:** Font used for the button label. From fonts.xml.
- **`textcolor`:** Color used for displaying the button label. In **AARRGGBB** hex format, or a name from the [colour theme](http://kodi.wiki/view/Colour_Themes).
- **`focusedcolor`:** Color used for the button label when the button has in focus. In **AARRGGBB** hex format or a name from the [colour theme](http://kodi.wiki/view/Colour_Themes).
- **`disabledcolor`:** Color used for the button label if the button is disabled. In **AARRGGBB** hex format, or a name from the [colour theme](http://kodi.wiki/view/Colour_Themes).
- **`shadowcolor`:** Specifies the color of the drop shadow on the text, in **AARRGGBB** format, or a name from the [colour theme](http://kodi.wiki/view/Colour_Themes).
- **`align`:** Label horizontal alignment on the button. Defaults to `left`, can also be `center` or `right`.
- **`aligny`:** Label vertical alignment on the button. Defaults to top, can also be center.
- **`textoffsetx`:** Amount to offset the label from the left (or right) edge of the button when using left or right alignment.
- **`textoffsety`:** Amount to offset the label from the top edge of the button when using top alignment.
- **`selected`:** The boolean condition that when met will cause the control to become selected. [See here for more information](http://kodi.wiki/view/Conditional_Visibility).
- **`onclick`:** The function to perform when the radio button is clicked. [Should be a built in function](http://kodi.wiki/view/Built-in_functions_available_to_FTP,_Webserver,_skins,_keymap_and_to_python). Can be leaved empty and controlled by function `bool CAddonGUIWindow::OnClick(int controlId)`
- **`radioposx`:** X offset of the dot or radio button itself
- **`radioposy`:** Y offset of the dot or radio button itself
- **`radiowidth`:** Width in Pixels of the dot or radio button itself
- **`radioheight`:** Height in Pixels of the dot or radio button itself
- **`onfocus`:** Specifies the action to perform when the button is focused. Should be a built in function. The action is performed after any focus animations have completed. See here for more information. Can be leaved empty and controlled by function `bool CAddonGUIWindow::OnFocus(int controlId)`
- **`onunfocus`:** Specifies the action to perform when the button loses focus. Should be a built in function.

Classes
-------------

#### Class: `CAddonGUIRadioButtonControl::CAddonGUIRadioButtonControl();`

> ***NOTE:*** This class functions are used to override the on window `*.xml` defined control values.

*  **`CAddonGUIRadioButtonControl(CAddonGUIWindow* window, int controlId);`**
    * Construct a new control
      * **`window`:** related window control class
      * **`controlId`:** Used skin xml control id

*  **`virtual ~CAddonGUIRadioButtonControl();`**
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

*  **`void SetSelected(bool selected);`**
    * Set boolean radio field selected
      * **`selected`:** true if selected

*  **`bool IsSelected() const;`**
    * Get the boolean value from radio field
      * **return:** true if selected
