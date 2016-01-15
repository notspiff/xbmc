# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md#CAddonGUIWindow)
</p>*
#### *<p align="center">GUI window / dialog class</p>*
-------------

The with `#include <kodi/addon.api2/GUIWindow.h>` included file brings support to create a window or dialog on Kodi.

Classes
-------------

#### Class: `CAddonGUIWindow::CAddonGUIWindow();`

*  **`CAddonGUIWindow(
      const std::string& xmlFilename,
      const std::string& defaultSkin,
      bool forceFallback,
      bool asDialog);`**
    * 
      * **`xmlFilename`:** XML file for the skin
      * **`defaultSkin`:** default skin to use if needed not available
      * **`forceFallback`:** 
      * **`asDialog`:** Use window as dialog if set

*  **`virtual ~CAddonGUIWindow();`**
    * 

*  **`virtual bool Show();`**
    * 
      * **Return:** 

*  **`virtual void Close();`**
    * 

*  **`virtual void DoModal();`**
    * 
    
*  **`virtual bool SetFocusId(int iControlId);`**
    * 
      * **`iControlId`:** 
      * **Return:** 

*  **`virtual int GetFocusId();`**
    * 
      * **Return:** 

*  **`virtual void SetControlLabel(int controlId, const std::string& label);`**
    * 
      * **`iControlId`:** 
      * **`label`:** 

*  **`virtual bool SetCoordinateResolution(int res);`**
    * 
      * **`res`:** 
      * **Return:** 

*  **`virtual void SetProperty(const std::string& key, const std::string& value);`**
    * 
      * **`key`:** 
      * **`value`:** 

*  **`virtual std::string GetProperty(const std::string& key) const;`**
    * 
      * **`key`:** 
      * **Return:** 

*  **`virtual void SetPropertyInt(const std::string& key, int value);`**
    * 
      * **`key`:** 
      * **`value`:** 

*  **`virtual int GetPropertyInt(const std::string& key) const;`**
    * 
      * **`key`:** 
      * **Return:** 

*  **`virtual void SetPropertyBool(const std::string& key, bool value);`**
    * 
      * **`key`:** 
      * **`value`:** 

*  **`virtual bool GetPropertyBool(const std::string& key) const;`**
    * 
      * **`key`:** 
      * **Return:** 

*  **`virtual void SetPropertyDouble(const std::string& key, double value);`**
    * 
      * **`key`:** 
      * **`value`:** 

*  **`virtual double GetPropertyDouble(const std::string& key) const;`**
    * 
      * **`key`:** 
      * **Return:** 

*  **`virtual void ClearProperties();`**
    * 

*  **`virtual GUIHANDLE AddStringItem(const std::string& name, int itemPosition = -1);`**
    * 
      * **`name`:** 
      * **`itemPosition`:** 
      * **Return:** 

*  **`virtual void AddItem(GUIHANDLE item, int itemPosition = -1);`**
    * 
      * **`item`:** 
      * **`itemPosition`:** 

*  **`virtual void AddItem(CAddonGUIListItem *item, int itemPosition = -1);`**
    * 
      * **`item`:** 
      * **`itemPosition`:** 

*  **`virtual void RemoveItem(int itemPosition);`**
    * 
      * **`itemPosition`:** 

*  **`virtual GUIHANDLE GetListItem(int listPos);`**
    * 
      * **`listPos`:** 
      * **Return:** 

*  **`virtual void SetCurrentListPosition(int listPos);`**
    * 
      * **`listPos`:** 

*  **`virtual int GetCurrentListPosition();`**
    * 
      * **Return:** 

*  **`virtual int GetListSize();`**
    * 
      * **Return:** 

*  **`virtual void ClearList();`**
    * 

*  **`virtual void MarkDirtyRegion();`**
    * 

##### Callback functions from Kodi to add-on

*  **`virtual bool OnClick(int controlId)`**
    * 
      * **`controlId`:** 
      * **Return:** 

*  **`virtual bool OnFocus(int controlId)`**
    * 
      * **`controlId`:** 
      * **Return:** 

*  **`virtual bool OnInit()`**
    * 
      * **Return:** 

*  **`virtual bool OnAction(int actionId)`**
    * 
      * **`actionId`:** 
      * **Return:** 

*  **`void SetIndependentCallbacks(
      GUIHANDLE             cbhdl,
      bool    (*CBOnInit)  (GUIHANDLE cbhdl),
      bool    (*CBOnFocus) (GUIHANDLE cbhdl, int controlId),
      bool    (*CBOnClick) (GUIHANDLE cbhdl, int controlId),
      bool    (*CBOnAction)(GUIHANDLE cbhdl, int actionId));`**
    * 
      * **`cbhdl`:** The pointer to own handle data structure / class
      * **`CBOnInit`:** Own defined window init function
      * **`CBOnFocus`:** Own defined focus function
      * **`CBOnClick`:** Own defined click function
      * **`CBOnAction`:** Own defined action function


