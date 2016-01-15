# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md#CAddonGUILabelControl)
</p>*
#### *<p align="center">Binary add-on GUI library, Version Level: 2</p>*
## *<p align="center">Label control</p>*
-------------

he label control is used for displaying text in XBMC. You can choose the font, size, colour, location and contents of the text to be displayed.

It has the header [`#include <kodi/gui.api2/GUIControlLabel.h>`](../GUIControlLabel.h) be included to enjoy it.

> ***Note:*** The call of the control is only possible from the corresponding window as its class and identification number is required.

Skin XML
-------------

Example below shows the most of possible parts for xml file of related Window / Dialog. Not all are really required and must be checked during creation on skin.

> ***Note:*** The example below is shown for add-on development from code, skin developers should follow the [Kodi Wiki](http://kodi.wiki/view/Skinning).

```xml
	<control type="label" id="10">
		<description>My First label</description>
		<posx>80</posx>
		<posy>60</posy>
		<width>250</width>
		<visible>true</visible>
		<align>center</align>
		<aligny>center</aligny>
		<scroll>false</scroll>
		<label>6</label>
		<info>MusicPlayer.Artist</info>
		<number></number>
		<angle>30</angle>
		<haspath>false</haspath>
		<font>font14</font>
		<textcolor>FFB2D4F5</textcolor>
		<shadowcolor>ff000000</shadowcolor>
		<wrapmultiline>false</wrapmultiline>
		<scrollspeed>50</scrollspeed>
		<scrollsuffix>-</scrollsuffix>
	</control>
```

**Possible values:**
- **`control type="label"`:** Control type name on xml
- **`id="10"`:** Id to communicate with other controls (required if accessed of code)
- **Global:** ([see Kodi wiki "Default control tags" for details](http://kodi.wiki/view/Default_Control_Tags))
  - **`description`:** Only used to make things clear for the skinner. Not read by Kodi at all.
  - **`left`:** Position from left (optional can `right` be used)
  - **`right`:** Position from right (optional can `left` be used)
  - **`top`:** Position from top (optional can `bottom` be used)
  - **`bottom`:** Position from bottom (optional can `top` be used)
  - **`width`:** Width of control on skin
  - **`height`:** Height of control on skin
  - **`visible`:** Specifies a condition as to when this control will be visible. Can be true, false, or a condition. See [Conditional Visibility](http://kodi.wiki/view/Conditional_Visibility) for more information. Defaults to true, can also be done by `void SetVisible(bool visible);`

- **Control dependent:** ([see Kodi wiki "Label Control" for details](http://kodi.wiki/view/Label_Control)):
  - **`align`:** Can be left, right, or center. Aligns the text within the given label `<width>`. Defaults to left
  - **`aligny`:** Can be top or center. Aligns the text within its given label `<height>`. Defaults to top
  - **`scroll`:** When `true`, the text will scroll if longer than the label's `<width>`. If false, the text will be truncated. Defaults to `false`.
  - **`label`:** Specifies the text which should be drawn. You should specify an entry from the strings.po here (either the Kodi strings.po, addon strings.po or skin's strings.po file), however you may also hardcode a piece of text also if you wish, though of course it will not be localisable. You can use the full label formatting syntax and [you may also specify more than one piece of information here by using the `$INFO` and `$LOCALIZE` formats](http://kodi.wiki/view/Label_Parsing).
  - **`info`:** Specifies the information that should be presented. Kodi will auto-fill in this info in place of the `<label>`. [See here for more information](http://kodi.wiki/view/InfoLabels).
  - **`number`:** Specifies a number that should be presented. This is just here to allow a skinner to use a number rather than a text label (as any number given to `<label>` will be used to lookup in strings.po)
  - **`angle`:** The angle the text should be rendered at, in degrees. A value of `0` is horizontal.
  - **`haspath`:** Specifies whether or not this label is filled with a path. Long paths are shortened by compressing the file path while keeping the actual filename full length.
  - **`font`:** Specifies the font to use from the font.xml file.
  - **`textcolor`:** Specifies the color the text should be, in hex **AARRGGBB** format, or a name from the [colour theme](http://kodi.wiki/view/Colour_Themes).
  - **`shadowcolor`:** Specifies the color of the drop shadow on the text, in **AARRGGBB** format, or a name from the [colour theme](http://kodi.wiki/view/Colour_Themes).
  - **`wrapmultiline`:** If `true`, any text that doesn't fit on one line will be wrapped onto multiple lines.
  - **`scrollspeed`:** Scroll speed of text in pixels per second. Defaults to `60`.
  - **`scrollsuffix`:** Specifies the suffix used in scrolling labels. Defaults to " | ".

C++ Classes
-------------

#### Class: `CAddonGUILabelControl::CAddonGUILabelControl();`

> ***NOTE:*** This class functions are used to override the on window `*.xml` defined control values.

*  **`CAddonGUILabelControl(CAddonGUIWindow* window, int controlId);`**
    * Construct a new control
      * **`window`:** related window control class
      * **`controlId`:** Used skin xml control id

*  **`virtual ~CAddonGUILabelControl();`**
    * Destructor

*  **`void SetVisible(bool visible);`**
    * Set the control on window to visible
      * **`visible`:** If true visible, otherwise hidden

*  **`void SetLabel(const std::string& text);`**
    * Set's text for this label.
      * **`text`:** Text to show

*  **`std::string GetLabel() const;`**
    * Returns the text value for this label.
      * **return:** Text string.
