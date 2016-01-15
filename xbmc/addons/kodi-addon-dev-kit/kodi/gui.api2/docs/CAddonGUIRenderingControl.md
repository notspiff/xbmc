# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md#CAddonGUIRenderingControl)
</p>*
#### *<p align="center">Binary add-on GUI library, Version Level: 2</p>*
## *<p align="center">Special GUI control class for rendering </p>*
-------------


It has the header [`#include <kodi/gui.api2/GUIControlRendering.h>`](../GUIControlRendering.h) be included to enjoy it.

> ***Note:*** The call of the control is only possible from the corresponding window as its class and identification number is required.

Skin XML
-------------

Example below shows the most of possible parts for xml file of related Window / Dialog. Not all are really required and must be checked during creation on skin.

> ***Note:*** The example below is shown for add-on development from code, skin developers should follow the [Kodi Wiki](http://kodi.wiki/view/Skinning).

```xml
	<control type="renderaddon" id ="9">
		<description>My first addon rendering control</description>
		<left>5</left>
		<top>50</top>
		<width>780</width>
		<height>515</height>
		<onup>2</onup>
		<ondown>3</ondown>
		<onleft>1</onleft>
		<onright>1</onright>
		<visible>true</visible>
	</control>
```

**Possible values:**
- **`control type="renderaddon"`:** Control type name on xml
- **`id="9"`:** Id to communicate with other controls (required if accessed of code)
- **Global:** ([see Kodi wiki "Default control tags" for details](http://kodi.wiki/view/Default_Control_Tags))
  - **`description`:** Only used to make things clear for the skinner. Not read by Kodi at all.
  - **`left`:** Position from left (optional can `right` be used)
  - **`right`:** Position from right (optional can `left` be used)
  - **`top`:** Position from top (optional can `bottom` be used)
  - **`bottom`:** Position from bottom (optional can `top` be used)
  - **`width`:** Width of control on skin
  - **`height`:** Height of control on skin
  - **`visible`:** Specifies a condition as to when this control will be visible. Can be true, false, or a condition. See [Conditional Visibility](http://kodi.wiki/view/Conditional_Visibility) for more information. Defaults to true, can also be done by `void SetVisible(bool visible);`

C++ Classes
-------------

#### Class: `CAddonGUIRenderingControl::CAddonGUIRenderingControl();`

> ***NOTE:*** Parts of this class functions are used to override the on window `*.xml` defined control values.

*  **`CAddonGUIRenderingControl(CAddonGUIWindow* window, int controlId);`**
    * Construct a new control
      * **`window`:** related window control class
      * **`controlId`:** Used skin xml control id

*  **`virtual ~CAddonGUIRenderingControl();`**
    * Destructor

*  **`virtual bool Create(int x, int y, int w, int h, void* device);`**
    * Function to create and initialize control on add-on
      * ***Note:*** Control function called from Kodi it self
      * **`x`:** Requested X position
      * **`y`:** Requested Y position
      * **`w`:** Requested width of control
      * **`h`:** Requested height of control
      * **`device`:** Used device pointer (on Direct X system)

*  **`virtual void Render();`**
    * Rendering call
      * ***Note:*** Control function called from Kodi it self

*  **`virtual void Stop();`**
    * Stop and close rendering
      * ***Note:*** Control function called from Kodi it self

*  **`virtual vool Dirty();`**
    * If control is dirty and need rendering return true
      * ***Note:*** Control function called from Kodi it self
      * **return:** If dirty return true

*  **`void SetIndependentCallbacks(
        GUIHANDLE             cbhdl,
        bool      (*CBCreate)(GUIHANDLE cbhdl,
                              int       x,
                              int       y,
                              int       w,
                              int       h,
                              void*     device),
        void      (*CBRender)(GUIHANDLE cbhdl),
        void      (*CBStop)  (GUIHANDLE cbhdl),
        bool      (*CBDirty) (GUIHANDLE cbhdl));`**
    * If the class is used independent (with "new CAddonGUIRenderingControl") and not as parent (with "`cCLASS_own : 
      CAddonGUIRenderingControl`") from own must be the callback from Kodi to add-on overdriven with own functions!
      * **`cbhdl`:** Own handle pointer passed to given static callback function on add-on
      * **`CBCreate`:** Call back function `static bool Create(GUIHANDLE cbhdl,int x, int y, int w, int h, void* device) { ... }` for Creation of control rendering
      * **`CBRender`:** Call back function `static void Render(GUIHANDLE cbhdl) { ... }` for rendering
      * **`CBStop`:** Call back function `static void Stop(GUIHANDLE cbhdl) { ... }` for stop of control
      * **`CBDirty`:** Call back function `static bool Dirty(GUIHANDLE cbhdl) { ... }` to inform is dirty
      * ***Note*** Above functions behind values are examples about the functions needed for this way on add-on

