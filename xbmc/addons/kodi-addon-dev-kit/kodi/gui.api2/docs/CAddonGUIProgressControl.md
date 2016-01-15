# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md#CAddonGUIProgressControl)
</p>*
#### *<p align="center">Binary add-on GUI library, Version Level: 2</p>*
## *<p align="center">Progress control</p>*
-------------

The progress control is used to show the progress of an item that may take a long time, or to show how far through a movie you are. You can choose the position, size, and look of the progress control.

It has the header [`#include <kodi/gui.api2/GUIControlProgress.h>`](../GUIControlProgress.h) be included to enjoy it.

> ***Note:*** The call of the control is only possible from the corresponding window as its class and identification number is required.

Skin XML
-------------

Example below shows the most of possible parts for xml file of related Window / Dialog. Not all are really required and must be checked during creation on skin.

> ***Note:*** The example below is shown for add-on development from code, skin developers should follow the [Kodi Wiki](http://kodi.wiki/view/Skinning).

```xml
	<control type="progress" id="12">
		<description>My first progress control</description>
		<left>80</left>
		<top>60</top>
		<width>250</width>
		<height>30</height>
		<visible>true</visible>
		<reveal>false</reveal>
		<texturebg>mybackgroundtexture.png</texturebg>
		<lefttexture>mydowntexture.png</lefttexture>
		<midtexture>mymidtexture.png</midtexture>
		<righttexture>myrighttexture.png</righttexture>
		<overlaytexture>myoverlaytexture.png</overlaytexture>
		<info></info>
	</control>
```

**Possible values:**
- **`control type="progress"`:** Control type name on xml
- **`id="12"`:** Id to communicate with other controls (required if accessed of code)
- **Global:** ([see Kodi wiki "Default control tags" for details](http://kodi.wiki/view/Default_Control_Tags))
  - **`description`:** Only used to make things clear for the skinner. Not read by Kodi at all.
  - **`left`:** Position from left (optional can `right` be used)
  - **`right`:** Position from right (optional can `left` be used)
  - **`top`:** Position from top (optional can `bottom` be used)
  - **`bottom`:** Position from bottom (optional can `top` be used)
  - **`width`:** Width of control on skin
  - **`height`:** Height of control on skin
  - **`visible`:** Specifies a condition as to when this control will be visible. Can be true, false, or a condition. See [Conditional Visibility](http://kodi.wiki/view/Conditional_Visibility) for more information. Defaults to true, can also be done by `void SetVisible(bool visible);`

- **Control dependent:** ([see Kodi wiki "Progress Control" for details](http://kodi.wiki/view/Progress_Control)):
  - **`reveal`:** If set to `true` the midtexture will reveal itself instead of stretching to fill the gap (works best when its the same size as texturebg)
  - **`texturebg`:** Specifies the image file which should be displayed in the background of the progress control. [See here for additional information about textures](http://kodi.wiki/view/Texture_Attributes).
  - **`lefttexture`:** Specifies the image file which should be displayed for the left side of the progress bar. This is rendered on the left side of the bar.
  - **`midtexture`:** Specifies the image file which should be displayed for the middle portion of the progress bar. This is the fill texture used to fill up the bar. It's positioned on the right of the `<lefttexture>` texture, and fills the gap between the `<lefttexture>` and `<righttexture>` textures, depending on how far progressed the item is.
  - **`righttexture`:** Specifies the image file which should be displayed for the right side of the progress bar. This is rendered on the right side of the bar.
  - **`overlaytexture`:** Specifies the image file which should be displayed over the top of all other images in the progress bar. It is centered vertically and horizontally within the space taken up by the background image.
  - **`info`:** Specifies the information that the progress bar is reporting on. [See here for more information](http://kodi.wiki/view/InfoLabels).

C++ Classes
-------------

#### Class: `CAddonGUIProgressControl::CAddonGUIProgressControl();`

> ***NOTE:*** This class functions are used to override the on window `*.xml` defined control values.

*  **`CAddonGUIProgressControl(CAddonGUIWindow* window, int controlId);`**
    * Construct a new control
      * **`window`:** related window control class
      * **`controlId`:** Used skin xml control id

*  **`virtual ~CAddonGUIProgressControl();`**
    * Destructor

*  **`void SetVisible(bool visible);`**
    * Set the control on window to visible
      * **`visible`:** If true visible, otherwise hidden

*  **`void SetPercentage(float fPercent);`**
    * Set the position of progress by percent
      * **`fPercent`:** percent value from 0.0 - 100.0

*  **`float GetPercentage();`**
    * Get the progress position as percent
      * **return:** percent value from 0.0 - 100.0
