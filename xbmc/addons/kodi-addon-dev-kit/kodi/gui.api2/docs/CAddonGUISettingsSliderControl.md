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
## *<p align="center">Settings slider control</p>*
-------------

General
-------------

The settings slider control is used in the settings screens for when an option is best specified on a sliding scale. You can choose the position, size, and look of the slider control. It is basically a cross between the button control and a slider control. It has a label and focus and non focus textures, as well as a slider control on the right.

It has the header [`#include <kodi/gui.api2/GUIControlSettingsSlider.h>`](../GUIControlSettingsSlider.h) be included to enjoy it.

> ***Note:*** The call of the control is only possible from the corresponding window as its class and identification number is required.

Skin XML
-------------

Example below shows the most of possible parts for xml file of related Window / Dialog. Not all are really required and must be checked during creation on skin.

> ***Note:*** The example below is shown for add-on development from code, skin developers should follow the [Kodi Wiki](http://kodi.wiki/view/Skinning).

```xml
	<control type="sliderex" id="12">
		<description>My first settings slider control</description>
		<posx>80</posx>
		<posy>60</posy>
		<width>250</width>
		<height>200</height>
		<sliderwidth>100</sliderwidth>
		<sliderheight>20</sliderheight>
		<visible>true</visible>
		<texturefocus>myfocustexture.png</texturefocus>
		<texturenofocus>mynofocustexture.png</texturenofocus>
		<texturebg>mybackgroundtexture.png</texturebg>
		<textureslidernib>mydowntexture.png</textureslidernib>
		<textureslidernibfocus>mydownfocustexture.png</textureslidernibfocus>
		<info></info>
		<label>46</label>
		<font>font12</font>
		<textcolor>FFFFFFFF</textcolor>
		<disabledcolor>80FFFFFF</disabledcolor>
		<textoffsetx></textoffsetx>
		<pulseonselect></pulseonselect>
		<onup>2</onup>
		<ondown>3</ondown>
		<onleft>1</onleft>
		<onright>1</onright>
	</control>
```

**Possible values:**
- **`control type="sliderex"`:** Control type name on xml
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

- **Control dependent:** ([see Kodi wiki "Settings Slider Control" for details](http://kodi.wiki/view/Settings_Slider_Control)):
  - **`sliderwidth`:** Specifies the width of the slider portion of the slider control (ie without the text value, if present). The texture image for the slider background will be resized to fit into this width, and the nib textures will be resized by the same amount.
  - **`sliderheight`:** Specifies the height of the slider portion of the slider control (ie without the text value, if present). The texture image for the slider background will be resized to fit into this height, and the nib textures will be resized by the same amount.
  - **`texturefocus`:** Specifies the image file which should be displayed for the control when it has focus. [See here for additional information about textures](http://kodi.wiki/view/Texture_Attributes).
  - **`texturenofocus`:** Specifies the image file which should be displayed for the control when it doesn't focus.
  - **`texturebg`:** Specifies the image file which should be displayed in the background of the slider portion of the control. Will be positioned so that the right edge is `<textoffsetx>` away from the right edge of the `<texturefocus>` image, and centered vertically.
  - **`textureslidernib`:** Specifies the image file which should be displayed for the slider nib.
  - **`textureslidernibfocus`:** Specifies the image file which should be displayed for the slider nib when it has focus.
  - **`label`:** Either a numeric reference into strings.xml (for localization), or a string that will be shown on the left of the control.
  - **`font`:** Font used for the controls label. From fonts.xml.
  - **`textcolor`:** Color used for displaying the label. In **AARRGGBB** hex format, or a name from the [colour theme](http://kodi.wiki/view/Colour_Themes).
  - **`disabledcolor`:** Color used for the label if the control is disabled. In **AARRGGBB** hex format, or a name from the [colour theme](http://kodi.wiki/view/Colour_Themes).
  - **`shadowcolor`:** Specifies the color of the drop shadow on the text. In **AARRGGBB** ** hex format, or a name from the [colour theme](http://kodi.wiki/view/Colour_Themes).
  - **`textoffsetx`:** Amount to offset the label from the left edge of the control.
  - **`info`:** Specifies the information that the slider controls. [See here for more information](http://kodi.wiki/view/InfoLabels).

> ***Note:*** Check always used skin on Kodi about default values for control.

C++ Classes
-------------

#### Class: `CAddonGUISettingsSliderControl::CAddonGUISettingsSliderControl();`

> ***NOTE:*** This class functions are used to override the on window `*.xml` defined control values.

*  **`CAddonGUISettingsSliderControl(CAddonGUIWindow* window, int controlId);`**
    * Construct a new control
      * **`window`:** related window control class
      * **`controlId`:** Used skin xml control id

*  **`virtual ~CAddonGUISettingsSliderControl();`**
    * Destructor

*  **`void SetVisible(bool visible);`**
    * Set's the control's visible/hidden state.
      * **`visible`:** True=visible / False=hidden.

*  **`void SetEnabled(bool enabled);`**
    * Set's the control's enabled/disabled state.
      * **`enabled`:** True=enabled / False=disabled.

*  **`void SetText(const std::string& text);`**
    * Set's text name for this slider control.
      * **`text`:** Text to show

*  **`void Reset();`**
    * Reset control to initial condition

*  **`void SetIntRange(int start, int end);`**
    * Set the range for slider from start to end
      * **`start`:** Integer start position
      * **`end`:** Integer end position

*  **`void SetIntValue(int value);`**
    * Set the position from slider in the range
      * **`value`:** Text to show

*  **`int GetIntValue() const;`**
    * Get the current slider position
      * **Return:** The current position

*  **`void SetIntInterval(int interval);`**
    * To set the size for steps if control is moved on skin
      * **`interval`:** Interval size to move in range

*  **`void SetPercentage(float percent);`**
    * Sets the percent of the slider.
      * **`percent`:** Text to show

*  **`float GetPercentage() const;`**
    * Returns a float of the percent of the slider.
      * **Return:** The current position

*  **`void SetFloatRange(float start, float end);`**
    * To set the slider range as float values
      * **`start`:** Start position of slider
      * **`end`:** End position of slider

*  **`void SetFloatValue(float value);`**
    * Set the slider position with a float value
      * **`value`:** The value to set

*  **`float GetFloatValue() const;`**
    * Get the current slider position as float
      * **Return:** The current position

*  **`void SetFloatInterval(float interval);`**
    * To set the size for steps if control is moved on skin as float
      * **`interval`:** Text to show
