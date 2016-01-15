# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md#CAddonGUIListItem)
</p>*
#### *<p align="center">GUI list item entry</p>*
-------------

The with `#include <kodi/addon.api2/GUIListItem.h>` given class is used to create a item entry for a list on window and to support it's control.

Classes
-------------

#### Class: `CAddonGUIListItem::CAddonGUIListItem(...);`

*  **`CAddonGUIListItem(
      const std::string& label,
      const std::string& label2,
      const std::string& iconImage,
      const std::string& thumbnailImage,
      const std::string& path);`**
    * Construct a new list item
      * **`label`:** First label for entry
      * **`label2`:** Second label for entry (optional)
      * **`iconImage`:** Used icon image (optional)
      * **`thumbnailImage`:** Thumbnail image (optional)
      * **`path`:** Path to use (optional)

*  **`virtual ~CAddonGUIListItem();`**
    * Destructor

*  **`virtual std::string GetLabel();`**
    * Get the used text for first list item entry
      * **Return:** First label name

*  **`virtual void SetLabel(const std::string& label);`**
    * To set the first text string on entry.
      * **`label`:** Text to show

*  **`virtual std::string GetLabel2();`**
    * Get the used text for second list item entry (if used)
      * **Return:** Second label name

*  **`virtual void SetLabel2(const std::string& label);`**
    * To set the second text string on entry (if used)
      * **`label`:** Text to show

*  **`virtual std::string GetIconImage();`**
    * Get the icon image path (if used)
      * **Return:** Path to image file

*  **`virtual void SetIconImage(const std::string& image);`**
    * To set the icon image for the list entry
      * **`image`:** Path of image to use

*  **`virtual std::string GetOverlayImage();`**
    * Get the overlay image path (if used)
      * **Return:** Path to image file

*  **`virtual void SetOverlayImage(unsigned int image, bool bOnOff = false);`**
    * Set the overlay image for entry and set it on / off
      * **`image`:** Image to use
      * **`bOnOff`:** To set it on (true) / off (false)

*  **`virtual void SetThumbnailImage(const std::string& image);`**
    * To set the thumbnail image for list entry
      * **`image`:** Image to use

*  **`virtual void SetSortLabel(const std::string& label);`**
    * Set entry sort label
      * **`label`:** Label to use

*  **`virtual void SetArt(const std::string& type, const std::string& url);`**
    * To set art type of entry with related URL
      * **`type`:** Type to use
      * **`url`:** URL defined for type

*  **`virtual void SetArtFallback(const std::string& from, const std::string& to);`**
    * To set art fallback in a range
      * **`from`:** 
      * **`to`:** 

*  **`virtual bool HasArt(const std::string& type);`**
    * Check entry fort art defined by type
      * **`type`:** Type to check
      * **Return:** True if art is present

*  **`virtual bool HasIcon();`**
    * Check list entry for a defined icon
      * **Return:** True if a icon is on it

*  **`virtual bool HasOverlay();`**
    * Check list entry for a defined overlay image
      * **Return:** True if a image is on it

*  **`virtual bool IsFileItem();`**
    * Check list entry is a file
      * **Return:** True if it is

*  **`virtual bool IsFolder();`**
    * Check list item entry is a folder
      * **Return:** True if it is

*  **`virtual void Select(bool bOnOff);`**
    * Select the list item entry (way to select more as one on list)
      * **`bOnOff`:** if true becomes it selected

*  **`virtual bool IsSelected();`**
    * Check list item entry for selection
      * **Return:** True if item is selected

*  **`virtual void SetProperty(const std::string& key, const std::string& value);`**
    * Set property with value on defined key 
      * **`key`:** 
      * **`value`:** 

*  **`virtual std::string GetProperty(const std::string& key);`**
    * Get property with defined key name
      * **`key`:** Key to use
      * **Return:** Property name on defined key

*  **`virtual void IncrementProperty(const std::string& key, int nVal);`**
    * Set value to property
      * **`key`:** Property key
      * **`nVal`:** Value to set on property

*  **`virtual void ClearProperty(const std::string& key);`**
    * Clear selected property
      * **`key`:** Property key

*  **`virtual void ClearProperties();`**
    * Clear the entry properties

*  **`virtual bool HasProperties();`**
    * Check for presence of properties
      * **Return:** True if minimum one property is present

*  **`virtual bool HasProperty(const std::string& key);`**
    * Check for presence of property defined by the key
      * **`key`:** Property key
      * **Return:** True if property is present

*  **`virtual void SetPath(const std::string& path);`**
    * Set the path of the list item
      * **`path`:** The path to use
