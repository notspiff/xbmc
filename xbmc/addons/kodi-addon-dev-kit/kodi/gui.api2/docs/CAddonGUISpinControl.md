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
## *<p align="center">Spin control</p>*
-------------

General
-------------

The settings spin control is used in the settings screens for when a list of options can be chosen from using up/down arrows. You can choose the position, size, and look of the spin control. It is basically a cross between the button control and a spin control. It has a label and focus and non focus textures, as well as a spin control on the right.

The given class `CAddonGUISpinControl` are basically used to control a rotable value field with named text on a window.

It has the header [`#include <kodi/gui.api2/GUIControlSpin.h>`](../GUIControlSpin.h) be included to enjoy it.

> ***Note:*** The call of the control is only possible from the corresponding window as its class and identification number is required.

Skin XML
-------------

Example below shows the most of possible parts for xml file of related Window / Dialog. Not all are really required and must be checked during creation on skin.

> ***Note:*** The example below is shown for add-on development from code, skin developers should follow the [Kodi Wiki](http://kodi.wiki/view/Skinning).

```xml
	<control type="spincontrolex" id="12">
		<description>My first settings spin control</description>
		<posx>80</posx>
		<posy>60</posy>
		<width>250</width>
		<height>200</height>
		<spinposx>220</spinposx>
		<spinposy>180</spinposy>
		<spinwidth>16</spinwidth>
		<spinheight>16</spinheight>
		<visible>true</visible>
		<enable>Control.IsEnabled(5)</enable>
		<colordiffuse>FFFFFFFF</colordiffuse>
		<texturefocus>myfocustexture.png</texturefocus>
		<texturenofocus>mynofocustexture.png</texturenofocus>
		<textureup>myuptexture.png</textureup>
		<textureupfocus>myupfocustexture.png</textureupfocus>
		<texturedown>mydowntexture.png</texturedown>
		<texturedownfocus>mydownfocustexture.png</texturedownfocus>
		<textureupdisabled colordiffuse="AAFFAAFF">mydowntexture.png</textureupdisabled>
		<texturedowndisabled colordiffuse="AAFFAAFF">mydownfocustexture.png</texturedowndisabled>
		<label>46</label>
		<font>font12</font>
		<textcolor>FFFFFFFF</textcolor>
		<disabledcolor>80FFFFFF</disabledcolor>
		<align></align>
		<aligny></aligny>
		<textoffsetx></textoffsetx>
		<textoffsety></textoffsety>
		<pulseonselect></pulseonselect>
		<onup>2</onup>
		<ondown>3</ondown>
		<onleft>1</onleft>
		<onright>1</onright>
		<subtype>float</subtype>
	</control>
```
**Possible values:**
- **`control type="spincontrolex"`:** Control type name on xml
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
  - **`visible`:** Specifies a condition as to when this control will be visible. Can be true, false, or a condition. See [Conditional Visibility](http://kodi.wiki/view/Conditional_Visibility) for more information. Defaults to true, can also be done by `void SetVisible(bool visible);`.
  - **`enable`:** Needed [condition](http://kodi.wiki/view/Conditional_Visibility) to have enabled, can also be done by `void SetEnabled(bool enabled);`
  - **`colordiffuse`:** This specifies the color to be used for the texture basis. It's in hex **AARRGGBB** format. If you define `<colordiffuse>FFFF00FF</colordiffuse>` (magenta), the image will be given a magenta tint when rendered. Defaults to **FFFFFFFF** (no tint). You can also specify this as a name from the [colour theme](http://kodi.wiki/view/Colour_Themes).

- **Control dependent:** ([see Kodi wiki "Text Box" for details](http://kodi.wiki/view/Text_Box)):
  - **`label`:** Label to use, can be leaved empty if set by `void SetText(const std::string& text);`
  - **`font`:** Used skin font for text
  - **`textcolor`:** Color to use for text
  - **`focusedcolor`:** Focused color to use for text
  - **`disabledcolor`:** Color to use if disabled
  - **`spinposx`:** The horizontal position of the spin control for multipage lists. This is offset from the top left of the list.
  - **`spinposy`:** The vertical position of the spin control for multipage lists. This is offset from the top left of the list.
  - **`spinwidth`:** The width of one of the spin control buttons. The textures for this spin control will be scaled to fit this width.
  - **`spinheight`:** The height of one of the spin control buttons. The textures for this spin control will be scaled to fit this height.
  - **`texturefocus`:** Specifies the image file which should be displayed for the control when it has focus. [See here for additional information about textures](http://kodi.wiki/view/Texture_Attributes).
  - **`texturenofocus`:** Specifies the image file which should be displayed for the control when it doesn't focus.
  - **`textureup`:** Specifies the image file which should be displayed for the up arrow when it doesn't have focus. It is displayed to the left of the down arrow.
  - **`textureupfocus`:** Specifies the image file which should be displayed for the up arrow when it has focus.
  - **`textureupdisabled`:** Specifies the image file which should be displayed for the up arrow when the button is disabled.
  - **`texturedown`:** Specifies the image file which should be displayed for the down arrow when it is not focused. It is displayed to the right of the up arrow so that it's right edge is `<textoffsetx>` pixels away from the right edge of the control.
  - **`texturedownfocus`:** Specifies the image file which should be displayed for the down arrow when it has focus.
  - **`texturedowndisabled`:** Specifies the image file which should be displayed for the up arrow when the button is disabled.
  - **`label`:** Either a numeric reference into strings.xml (for localization), or a string that will be shown on the left of the control.
  - **`font`:** Font used for the controls label. From fonts.xml.
  - **`textcolor`:** Color used for displaying the label. In **AARRGGBB** hex format, or a name from the [colour theme](http://kodi.wiki/view/Colour_Themes).
  - **`disabledcolor`:** Color used for the label if the control is disabled. In **AARRGGBB** hex format, or a name from the [colour theme](http://kodi.wiki/view/Colour_Themes).
  - **`shadowcolor`:** Specifies the color of the drop shadow on the text. In **AARRGGBB** hex format, or a name from the [colour theme](http://kodi.wiki/view/Colour_Themes).
  - **`align`:** Label horizontal alignment on the control. Defaults to left.
    - `left`: Align text to left
    - `center`: Align text to center
    - `right`: Align text to right
  - **`aligny`:** Label vertical alignment on the control. Defaults to top, can also be center.
    - `top`: Align text to top
    - `center`: Align text to center
    - `bottom`: Align text to bottom
  - **`textoffsetx`:** Amount to offset the label from the left (or right) edge of the button when using left or right alignment.
  - **`textoffsety`:** Amount to offset the label from the top edge of the button when using top alignment.
  - **`subtype`:** Set the data type used on spin control, default is `text` if this entry not used. Can also set by function `void SetType(int type);`
    - `text`: Entries are pure text only
    - `int`: Entries are numbers
    - `float`: Entries are floating point numbers
    - `page`: To use for page selection
  - **`pulseonselect`:** This specifies whether or not a button type will "pulse" when it has focus. This is done by varying the alpha channel of the button. Defaults to true.

> ***Note:*** Check always used skin on Kodi about default values for control.

C++ Classes
-------------

#### Class: `CAddonGUISpinControl::CAddonGUISpinControl();`

> ***NOTE:*** This class functions are used to override the on window `*.xml` defined control values.

*  **`CAddonGUISpinControl(CAddonGUIWindow* window, int controlId);`**
    * Construct a new control
      * **`window`:** related window control class
      * **`controlId`:** Used skin xml control id

*  **`virtual ~CAddonGUISpinControl();`**
    * Destructor

*  **`void SetVisible(bool visible);`**
    * To set the control visible on skin
      * **`visible`:** true if visible, false for hidden

*  **`void SetEnabled(bool enabled);`**
    * Set's the control's enabled/disabled state.
      * **`enabled`:** true if enabled, false for disabled

*  **`void SetText(const std::string& text);`**
    * The Name used on skin for control
      * **`text`:** The name

*  **`void Reset();`**
    * Clear all with `Add...(...)` added entries

*  **`void SetType(int type);`**
    * Set the data type used on spin control, default is `ADDON_SPIN_CONTROL_TYPE_TEXT` if this call not used.
    * ***NOTE:*** Type can also be set on xml with `<subtype>...</subtype>` where values are `int`, `float`, `text` or `page`.
      * **`type`:** Data type to use
      ```cpp
        typedef enum AddonGUISpinControlType
        {
          ADDON_SPIN_CONTROL_TYPE_INT    = 1,
          ADDON_SPIN_CONTROL_TYPE_FLOAT  = 2,
          ADDON_SPIN_CONTROL_TYPE_TEXT   = 3,
          ADDON_SPIN_CONTROL_TYPE_PAGE   = 4
        } AddonGUISpinControlType;
      ```

*  **`void AddLabel(const std::string& label, const std::string& value);`**
    * Add a named label entry with related value as string to spin
      * **`label`:** Name of entry
      * **`value`:** Related value of entry

*  **`void AddLabel(const std::string& label, int value);`**
    * Add a named label entry with related value as integer to spin
      * **`label`:** Name of entry
      * **`value`:** Related value of entry

*  **`void SetStringValue(const std::string& value);`**
    * Set the current value as string
      * **`value`:** The value to set

*  **`std::string GetStringValue() const;`**
    * Get the currently selected value as string
      * **Return:** The current position value

*  **`void SetIntRange(int start, int end);`**
    * To set the spin range as integer values
      * **`start`:** Start position as integer of spin
      * **`end`:** End position as integer of spin

*  **`void SetIntValue(int value);`**
    * Set the current value as integer
      * **`value`:** The value to set

*  **`int GetIntValue() const;`**
    * Get the currently selected value as integer
      * **Return:** The current position value

*  **`void SetFloatRange(float start, float end);`**
    * To set the spin range as float values
      * **`start`:** Start position as float of spin
      * **`end`:** End position as float of spin

*  **`void SetFloatValue(float value);`**
    * Set the spin position with a float value
      * **`value`:** The value to set

*  **`float GetFloatValue() const;`**
    * Get the value from current spin position as float
      * **Return:** The current position value

*  **`void SetFloatInterval(float interval);`**
    * To set the size for steps if control is moved on skin as float
      * **`interval`:** Size to the next step
