# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md#CAddonGUIEditControl)
</p>*
#### *<p align="center">Binary add-on GUI library, Version Level: 2</p>*
## *<p align="center">Edit control</p>*
-------------

The edit control allows a user to input text in Kodi. You can choose the font, size, colour, location and header of the text to be displayed.

It has the header [`#include <kodi/gui.api2/AddonGUIEditControl.h>`](../AddonGUIEditControl.h) be included to enjoy it.

> ***Note:*** The call of the control is only possible from the corresponding window as its class and identification number is required.

Skin XML
-------------

Example below shows the most of possible parts for xml file of related Window / Dialog. Not all are really required and must be checked during creation on skin.

> ***Note:*** The example below is shown for add-on development from code, skin developers should follow the [Kodi Wiki](http://kodi.wiki/view/Skinning).

```xml
	<control type="edit" id="10">
		<description>My First edit control</description>
		<top>80</left>
		<posy>60</top>
		<width>250</width>
		<visible>true</visible>
		<aligny>center</aligny>
		<label>Search</label>
		<hinttext>Enter search string</hinttext>
		<font>font14</font>
		<textoffsetx>10</textoffsetx>
		<textcolor>FFB2D4F5</textcolor>
		<disabledcolor>FF000000</disabledcolor>
		<invalidcolor>FFFFFFFF</invalidcolor>
		<texturefocus>button-focus.png</texturefocus>
		<texturenofocus>button-nofocus.png</texturenofocus>
		<pulseonselect>no</pulseonselect>
	</control>
```

**Possible values:**
- **`control type="edit"`:** Control type name on xml
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

- **Control dependent:** ([see Kodi wiki "Edit Control" for details](http://kodi.wiki/view/Edit_Control)):
  - **`aligny`:** Can be `top` or `center`. Aligns the text within its given control `<height>`. Defaults to `top`
  - **`label`:** Specifies the header text which should be shown. You should specify an entry from the strings.po here (either the Kodi strings.po, add-on strings.po or skin's strings.po file), however you may also hardcode a piece of text also if you wish, though of course it will not be localized. You can use the full [label formatting syntax](http://kodi.wiki/view/Label_Formatting) and [you may also specify more than one piece of information here by using the `$INFO` and `$LOCALIZE` formats strings.po](http://kodi.wiki/view/Label_Parsing) )
  - **`hinttext`:** Specifies the text which should be displayed in the edit label control, until the user enters some text. It can be used to provide a clue as to what a user should enter in this control.
  - **`font`:** Specifies the font to use from the **font.xml** file.
  - **`textcolor`:** Specifies the color the text should be, in hex **AARRGGBB** format, or a name from the colour theme.

C++ Classes
-------------

#### Class: `CAddonGUIEditControl::CAddonGUIEditControl();`

> ***NOTE:*** This class functions are used to override the on window `*.xml` defined control values.

*  **`CAddonGUIEditControl(CAddonGUIWindow* window, int controlId);`**
    * Construct a new control
      * **`window`:** related window control class
      * **`controlId`:** Used skin xml control id

*  **`virtual ~CAddonGUIEditControl();`**
    * Destructor

*  **`void SetVisible(bool visible);`**
    * Set the control on window to visible
      * **`visible`:** If true visible, otherwise hidden

*  **`void SetEnabled(bool enabled);`**
    * Set's the control's enabled/disabled state.
      * **`enabled`:** If true enabled, otherwise disabled

*  **`void SetLabel(const std::string& label);`**
    * Set's text heading for this edit control.
      * **`label`:** Text to show

*  **`std::string GetLabel() const;`**
    * Returns the text heading for this edit control.
      * **return:** Text shown

*  **`void SetText(const std::string& text);`**
    * Set's text value for this edit control.
      * **`text`:** Text to show

*  **`std::string GetText() const;`**
    * Returns the text value for this edit control.
      * **return:** Text shown

*  **`void SetCursorPosition(unsigned int iPosition);`**
    * Set the cursor on text field to selected position
      * **`iPosition`:** Character position

*  **`unsigned int GetCursorPosition();`**
    * Get the current position of cursor on text field
      * **return:** Cursor position

*  **`void SetInputType(AddonGUIInputType type, const std::string& heading);`**
    * Set the used input type about text field (follow the link below to see available types)
      * **`type`:** The used [string input type](../Readme.md#AddonGUIInputType)
      * **`heading`:** Heading text string
