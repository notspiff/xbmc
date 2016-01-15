# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md#CAddonGUIFadeLabelControl)
</p>*
#### *<p align="center">Binary add-on GUI library, Version Level: 2</p>*
## *<p align="center">Fade label control</p>*
-------------

The fade label control is used for displaying multiple pieces of text in the same space in Kodi. You can choose the font, size, colour, location and contents of the text to be displayed. The first piece of information to display fades in over 50 frames, then scrolls off to the left. Once it is finished scrolling off screen, the second piece of information fades in and the process repeats. A fade label control is not supported in a list container.

It has the header [`#include <kodi/gui.api2/GUIControlFadeLabel.h>`](../GUIControlFadeLabel.h) be included to enjoy it.

> ***Note:*** The call of the control is only possible from the corresponding window as its class and identification number is required.

Skin XML
-------------

Example below shows the most of possible parts for xml file of related Window / Dialog. Not all are really required and must be checked during creation on skin.

> ***Note:*** The example below is shown for add-on development from code, skin developers should follow the [Kodi Wiki](http://kodi.wiki/view/Skinning).

```xml
	<control type="fadelabel" id="1">
		<description>My First fadelabel</description>
		<posx>80</posx>
		<posy>60</posy>
		<width>250</width>
		<visible>true</visible>
		<scrollout>true</scrollout>
		<pauseatend>200</pauseatend>
		<label>6</label>
		<info>MusicPlayer.Genre</info>
		<info>MusicPlayer.Artist</info>
		<info>MusicPlayer.Album</info>
		<info>MusicPlayer.Year</info>
		<font>font14</font>
		<textcolor>FFB2D4F5</textcolor>
		<textoffsetx>20</textoffsetx>
		<scroll>true</scroll>
		<randomize>true</randomize>
	</control>
```

**Possible values:**
- **`control type="fadelabel"`:** Control type name on xml
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

- **Control dependent:** ([see Kodi wiki "Fade label Control" for details](http://kodi.wiki/view/Fade_Label_Control)):
  - **`label`:** Specifies the text which should be drawn. You should specify an entry from the **strings.po** here, however you may also specify a piece of text yourself if you wish, though ofcourse it will not be localisable. [You may also specify more than one piece of information here by using the `$INFO` and `$LOCALIZE` formats.](http://kodi.wiki/view/Label_Parsing)
  - **`info`:** Specifies the information that should be presented. Kodi will auto-fill in this info in place of the <label>. [See here for more information](http://kodi.wiki/view/InfoLabels).
  - **`font`:** Specifies the font to use from the **font.xml** file.
  - **`textcolor`:** Specified the color the text should be, in hex **AARRGGBB** format, or a name from the [colour theme](http://kodi.wiki/view/Colour_Themes).
  - **`textoffsetx`:** Specify the offset from the left edge that the text should be rendered at when static (not scrolling). The scrolling text will still scroll using the full <width> of the control.
  - **`shadowcolor`:** Specifies the color of the drop shadow on the text, in **AARRGGBB** format, or a name from the [colour theme](http://kodi.wiki/view/Colour_Themes).
  - **`angle`:** Specifies the angle at which the text should be drawn, measured counter clockwise from the horizontal.
  - **`scrollout`:** If set to `false` the fadelabel will only scroll until the last char is to the right side of the width of the fadelabel instead of all the way out to the left.
  - **`pauseatend`:** Specifies the time that the text will wait until it fades away before it scrolls again or moves to the next item.
  - **`resetonlabelchange`:** If set to false the fadelabel will not reset the scrolling offset when the label's content changes. Useful if you have things such as the play time (in seconds) inside a fadelabel. Defaults to `true`.
  - **`scrollspeed`:** Scroll speed of text in pixels per second. Defaults to `60`.
  - **`scroll`:** If set to `false`, the labels won't scroll. Defaults to `true`.
  - **`randomize`:** If set to `true`, the labels will be displayed in a random order. Defaults to `false`.


C++ Classes
-------------

#### Class: `CAddonGUIFadeLabelControl::CAddonGUIFadeLabelControl();`

> ***NOTE:*** This class functions are used to override the on window `*.xml` defined control values.

*  **`CAddonGUIFadeLabelControl(CAddonGUIWindow* window, int controlId);`**
    * Construct a new control
      * **`window`:** related window control class
      * **`controlId`:** Used skin xml control id

*  **`virtual ~CAddonGUIFadeLabelControl();`**
    * Destructor

*  **`void SetVisible(bool visible);`**
    * Set the control on window to visible
      * **`visible`:** If true visible, otherwise hidden

*  **`void AddLabel(const std::string& text);`**
    * Add a label to this control for scrolling.
      * **`text`:** Text to show

*  **`std::string GetLabel() const;`**
    * Returns the text value for this label.
      * **Return:** Text shown

*  **`void SetScrolling(bool scroll);`**
    * Set scrolling.
      * **`scroll`:** True = enabled / False = disabled

*  **`void Reset();`**
    * Clear this fade label.
