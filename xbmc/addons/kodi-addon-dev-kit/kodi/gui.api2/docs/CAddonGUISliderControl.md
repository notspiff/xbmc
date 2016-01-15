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
## *<p align="center">Slider control</p>*
-------------

General
-------------

The slider control is used for things where a sliding bar best represents the operation at hand (such as a volume control or seek control). You can choose the position, size, and look of the slider control.

It has the header [`#include <kodi/gui.api2/GUIControlSlider.h>`](../GUIControlSlider.h) be included to enjoy it.

> ***Note:*** The call of the control is only possible from the corresponding window as its class and identification number is required.

Skin XML
-------------

Example below shows the most of possible parts for xml file of related Window / Dialog. Not all are really required and must be checked during creation on skin.

> ***Note:*** The example below is shown for add-on development from code, skin developers should follow the [Kodi Wiki](http://kodi.wiki/view/Skinning).

```xml
	<control type="slider" id="17">
		<description>My first slider control</description>
		<posx>80</posx>
		<posy>60</posy>
		<width>250</width>
		<height>30</height>
		<visible>true</visible>
		<texturesliderbar>mybackgroundtexture.png</texturesliderbar>
		<textureslidernib>mydowntexture.png</textureslidernib>
		<textureslidernibfocus>mydownfocustexture.png</textureslidernibfocus>
		<info></info>
		<action></action>
		<controloffsetx></controloffsetx>
		<controloffsety></controloffsety>
		<pulseonselect></pulseonselect>
		<onup>2</onup>
		<ondown>3</ondown>
		<onleft>1</onleft>
		<onright>1</onright>
	</control>
```

**Possible values:**
- **`control type="slider"`:** Control type name on xml
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

- **Control dependent:** ([see Kodi wiki "Slider Control" for details](http://kodi.wiki/view/Slider_Control)):
  - **`texturesliderbar`:** Specifies the image file which should be displayed in the background of the slider control. [See here for additional information about textures](http://kodi.wiki/view/Texture_Attributes).
  - **`textureslidernib`:** Specifies the image file which should be displayed for the slider nib.
  - **`textureslidernibfocus`:** Specifies the image file which should be displayed for the slider nib when it has focus.
  - **`controloffsetx`:** Amount to offset the slider background texture from the left edge of the control. Only useful if a value is being rendered as well (ie in int or float mode).
  - **`controloffsety`:** Amount to offset the slider background texture from the top edge of the control.
  - **`info`:** Specifies the information that the slider controls. See here for more information.
  - **`action`:** Can be 'volume' to adjust the volume or 'seek' to change the seek position.

> ***Note:*** Check always used skin on Kodi about default values for control.

C++ Classes
-------------

#### Class: `CAddonGUISliderControl::CAddonGUISliderControl();`

> ***NOTE:*** This class functions are used to override the on window `*.xml` defined control values.
> It can only use one type from `ìnt`, `float` or `percent` and not all functions used together.

*  **`CAddonGUISliderControl(CAddonGUIWindow* window, int controlId);`**
    * Construct a new control
      * **`window`:** related window control class
      * **`controlId`:** Used skin xml control id

*  **`virtual ~CAddonGUISliderControl();`**
    * Destructor

*  **`void SetVisible(bool visible);`**
    * Set's the control's visible/hidden state.
      * **`visible`:** True=visible / False=hidden.

*  **`void SetEnabled(bool enabled);`**
    * Set's the control's enabled/disabled state.
      * **`enabled`:** True=enabled / False=disabled.

*  **`void Reset();`**
    * Reset control to initial condition

*  **`std::string GetDescription() const;`**
    * To get string of current selected slider position value
      * **Return:** String with currently selected value.

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
