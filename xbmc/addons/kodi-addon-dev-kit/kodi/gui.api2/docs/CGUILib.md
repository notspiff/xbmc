# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md#CGUILib)
</p>*
#### *<p align="center">Binary add-on GUI library, Version Level: 2</p>*
## *<p align="center">General parts</p>*
-------------

General
-------------

General GUI related functions.

It has the header [`#include <kodi/gui.api2/GUILib.h`](../GUILib.h) be included to enjoy it.

Functions
-------------

1. [bool RegisterMe(void *handle);](#CGUILib_RegisterMe)
* [void UnRegisterMe();](#CGUILib_UnRegisterMe)
* [void Lock();](#CGUILib_Lock)
* [void Unlock();](#CGUILib_Unlock)
* [int GetScreenHeight();](#CGUILib_GetScreenHeight)
* [int GetScreenWidth();](#CGUILib_GetScreenWidth)
* [int GetVideoResolution();](#CGUILib_GetVideoResolution)
* [int GetCurrentWindowId();](#CGUILib_GetCurrentWindowId)
* [int GetCurrentWindowDialogId();](#CGUILib_GetCurrentWindowDialogId)

-------------

*  <a id="CGUILib_RegisterMe"></a>
**`bool CGUILib::RegisterMe(void *handle);`**
    * Resolve all callback methods for GUI control system
	  * **`handle`:** Pointer to the add-on
      * **return:** True when all methods were resolved, false otherwise.

	```cpp
	  ADDON_STATUS ADDON_Create(void* hdl, void* props)
	  {
	    ...
	    if (!CGUILib::RegisterMe(hdl))
	      return ADDON_STATUS_PERMANENT_FAILURE;
	    ...
	```

*  <a id="CGUILib_UnRegisterMe"></a>
**`void CGUILib::UnRegisterMe();`**
    * Release all callback methods and close handling with them

-------------

*  <a id="CGUILib_Lock"></a>
**`void CGUILib::Lock();`**
    * Performs a graphical lock of rendering engine

*  <a id="CGUILib_Unlock"></a>
**`void CGUILib::Unlock();`**
    * Performs a graphical unlock of previous locked rendering engine

-------------

*  <a id="CGUILib_GetScreenHeight"></a>
**`int CGUILib::GetScreenHeight();`**
    * Return the the current screen height with pixel
      * **return:** The height in pixels

*  <a id="CGUILib_GetScreenWidth"></a>
**`int CGUILib::GetScreenWidth();`**
    * Return the the current screen width with pixel
      * **return:** The width in pixels

*  <a id="CGUILib_GetVideoResolution"></a>
**`int CGUILib::GetVideoResolution();`**
    * Return the the current screen rendering resolution
      * **return:** The resolution

-------------

*  <a id="CGUILib_GetCurrentWindowId"></a>
**`int CGUILib::GetCurrentWindowId();`** **
    * Returns the id for the current 'active' window as an integer.
      * **return:** Acitive window id

*  <a id="CGUILib_GetCurrentWindowDialogId"></a>
**`int CGUILib::GetCurrentWindowDialogId();`**
    * Returns the id for the current 'active' dialog as an integer.
      * **return:** Active dialog id, or -1 if nothing
