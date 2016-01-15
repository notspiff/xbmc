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
## *<p align="center">Image control</p>*
-------------

The image control is used for displaying images in Kodi. You can choose the position, size, transparency and contents of the image to be displayed.

It has the header [`#include <kodi/gui.api2/GUIControlImage.h>`](../GUIControlImage.h) be included to enjoy it.

> ***Note:*** The call of the control is only possible from the corresponding window as its class and identification number is required.

Skin XML
-------------

Example below shows the most of possible parts for xml file of related Window / Dialog. Not all are really required and must be checked during creation on skin.

> ***Note:*** The example below is shown for add-on development from code, skin developers should follow the [Kodi Wiki](http://kodi.wiki/view/Skinning).

```xml
	<control type="image" id="15">
		<description>My first image control</description>
		<posx>80</posx>
		<posy>60</posy>
		<width>250</width>
		<height>200</height>
		<visible>true</visible>
		<colordiffuse>FFFFFFFF</colordiffuse>
		<fadetime>200</fadetime>
		<texture border="5" flipy="true" flipx="false">mytexture.png</texture>
		<bordertexture border="5">mybordertexture.png</bordertexture>
		<bordersize>5</bordersize>
		<aspectratio>keep</aspectratio>
	</control>
```

**Possible values:**
- **`control type="image"`:** Control type name on xml
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

- **Control dependent:** ([see Kodi wiki "Image Control" for details](http://kodi.wiki/view/Image_control)):
  - **`aspectratio`:** This specifies how the image will be drawn inside the box defined by `<width>` and `<height>`. [See here for more information](http://kodi.wiki/view/Aspect_Ratio).
  - **`texture`:** Specifies the image file which should be displayed. [See here for additional information about textures](http://kodi.wiki/view/Texture_Attributes). Can also be done by `void SetFileName(const std::string& strFileName, const bool useCache);`
  - **`bordertexture`:** Specifies the image file which should be displayed as a border around the image. Use the `<bordersize>` to specify the size of the border. The `<width>`,`<height>` box specifies the size of the image plus border.
  - **`bordersize`:** Specifies the size of the border. A single number specifies the border should be the same size all the way around the image, whereas a comma separated list of 4 values indicates left, top, right, bottom values.
  - **`info`:** Specifies the information that this image control is presenting. Kodi will select the texture to use based on this tag. [See here for more information](http://kodi.wiki/view/InfoLabels).
  - **`fadetime`:** This specifies a crossfade time that will be used whenever the underlying `<texture>` filename changes. The previous image will be held until the new image is ready, and then they will be crossfaded. This is particularly useful for a large thumbnail image showing the focused item in a list, or for fanart or other large backdrops.
  - **`background`:** For images inside a container, you can specify `background="true"` to load the textures in a background worker thread. [See here for additional information about background loading](http://kodi.wiki/view/Background_Image_Loader).
  - **`colordiffuse`:** This specifies the color to be used for the texture basis. It's in hex **AARRGGBB** format. If you define `<colordiffuse>FFFF00FF</colordiffuse>` *(magenta)*, the image will be given a magenta tint when rendered. Defaults to **FFFFFFFF** *(no tint)*. You can also specify this as a name from the [colour theme](http://kodi.wiki/view/Colour_Themes). Can also be done by `void SetColorDiffuse(uint32_t colorDiffuse);`

C++ Classes
-------------

#### Class: `CAddonGUIImageControl::CAddonGUIImageControl();`

> ***NOTE:*** This class functions are used to override the on window `*.xml` defined control values.

*  **`CAddonGUIImageControl(CAddonGUIWindow* window, int controlId);`**
    * Construct a new control
      * **`window`:** related window control class
      * **`controlId`:** Used skin xml control id

*  **`virtual ~CAddonGUIImageControl();`**
    * Destructor

*  **`void SetVisible(bool visible);`**
    * Set's the control's visible/hidden state.
      * **`visible`:** `true` = visible / `false` = hidden.

*  **`void SetFileName(const std::string& strFileName, const bool useCache = true);`**
    * Changes the image.
      * **`strFileName`:** image filename.
      * **`useCache`:** `true` = use cache (default) / `false` = don't use cache.

*  **`void SetColorDiffuse(uint32_t colorDiffuse);`**
    * Changes the images color.
      * **`colorDiffuse`:** color, example `0xC0FF0000` (red tint)
