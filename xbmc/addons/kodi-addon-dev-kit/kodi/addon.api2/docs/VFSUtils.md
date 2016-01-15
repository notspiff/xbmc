# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md#vfs_classes)
</p>*
#### *<p align="center">Group: ```Virtual file system (VFS) utils```</p>*
----------

The with #include ```<kodi/addon.api2/VFSUtils.h>``` given functions are basically used to allow add-on access to Kodi's functions

Functions
-------------

*  <b>```bool CAddOnLib_VFSUtils::GetDirectory(const std::string& path, const std::string& mask, std::vector<CVFSDirEntry>& items);```</b>
    * Lists a directory.
	    * <b>```path```</b> Path to the directory.
	    * <b>```mask```</b> File mask
	    * <b>```items```</b> The returned directory entries
		* <b>return:</b> True if listing was successful, false otherwise.
     
Classes
-------------

#### Class: ```CVFSDirEntry::CVFSDirEntry(...);```
               
*  <b>```CVFSDirEntry(const std::string&  label   = "", const std::string& path = "", bool bFolder = false, int64_t size = -1)```</b>
    * Constructor
	    * <b>```label```</b> Name to use for entry
	    * <b>```path```</b> Used path of the entry
	    * <b>```bFolder```</b> If set entry used as folder
	    * <b>```size```</b> If used as file, his size defined there

*  <b>```CVFSDirEntry(const VFSDirEntry&  dirEntry);```</b>
    * Constructor to create own copy 
	    * <b>```dirEntry```</b> pointer to own class type

*  <b>```const std::string& Label(void) const;```</b>
    * Get the directory entry name
	    * <b>return:</b> Name of the entry

*  <b>```const std::string& Path(void) const;```</b>
    * Get the path of the entry
	    * <b>return:</b> File system path of the entry

*  <b>```bool IsFolder(void) const;```</b>
    * Used to check entry is folder
	    * <b>return:</b> true if entry is a folder

*  <b>```int64_t Size(void) const;```</b>
    * If file, the size of the file
	    * <b>return:</b> Defined file size

* <b>```const std::vector<CVFSProperty>& Properties(void);```</b>
    * Get the properties of the entry
	    * <b>return:</b> Not editable array pointer to properties

*  <b>```void SetLabel(const std::string& label);```</b>
    * Set the label name
	    * <b>```label```</b> name of entry

* <b>```void SetPath(const std::string& path);```</b>
    * Set the path of the entry
	    * <b>```path```</b> path of entry
    
*  <b>```void SetFolder(bool bFolder);```</b>
    * Set the entry defined as folder
	    * <b>```bFolder```</b> If true becomes entry defined as folder
    
*  <b>```void SetSize(int64_t size);```</b>
    * Set a file size for a new entry
	   * <b>```size```</b> Size to set for dir entry
    
*  <b>```std::vector<CVFSProperty>& Properties(void);```</b>
    * Get the editable array pointer for the entry
	    * <b>return:</b> Array pointer to properties
    
-------------

#### Class: ```CVFSProperty::CVFSProperty(...);```

*  <b>```CVFSProperty(const std::string& name, const std::string& value)```</b>
    * Constructor
	    * <b>```name```</b>  Property name
	    * <b>```value```</b>  Defined value to use

*  <b>```const std::string& Name(void) const;```</b>
    * Used Name
		* <b>return:</b> Defined name

*  <b>```const std::string& Value(void) const;```</b>
    * Get defined value
		* <b>return:</b> Defined value

*  <b>```void SetName(const std::string& name);```</b>
    * Set name to use
	    * <b>```name```</b>  Property name

*  <b>```void SetValue(const std::string& value);```</b>
    * Set defined value
	    * <b>```value```</b>  Defined value to use
