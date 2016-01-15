# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md#CAddonGUIDialogFileBrowser)
</p>*
#### *<p align="center">Binary add-on GUI library, Version Level: 2</p>*
## *<p align="center">File browser dialog</p>*
-------------

General
-------------

The functions listed below of the class "CAddonGUIDialogFileBrowser" offer the possibility to select to a file by the user of the add-on. 

It allows all the options that are possible in Kodi itself and offers all support file types.

These are pure static functions them no other initialization need.

It has the header `#include <kodi/gui.api2/GUIDialogFileBrowser.h` be included to enjoy it.

Functions
-------------

1. [bool ShowAndGetDirectory(const std::string& shares, const std::string& heading, std::string& path, bool bWriteOnly);](#CAddonGUIDialogFileBrowser_ShowAndGetDirectory)
* [bool ShowAndGetFile(const std::string& shares, const std::string& mask, const std::string& heading, std::string& file, bool useThumbs, bool useFileDirectories);](#CAddonGUIDialogFileBrowser_ShowAndGetFile)
* [bool ShowAndGetFileFromDir(const std::string& directory, const std::string& mask, const std::string& heading, std::string& strPath, bool useThumbs, bool useFileDirectories, bool singleList );](#CAddonGUIDialogFileBrowser_ShowAndGetFileFromDir)
* [bool ShowAndGetFileList(const std::string& shares, const std::string& mask, const std::string& heading, std::vector< std::string >& path, bool useThumbs, bool useFileDirectories);](#CAddonGUIDialogFileBrowser_ShowAndGetFileList)
* [bool ShowAndGetSource(std::string& path, bool allowNetworkShares, const std::string& additionalShare, const std::string& strType);](#CAddonGUIDialogFileBrowser_ShowAndGetSource)
* [bool ShowAndGetImage(const std::string& shares, const std::string& heading, std::string& strPath);](#CAddonGUIDialogFileBrowser_ShowAndGetImage)
* [bool ShowAndGetImageList(const std::string& shares, const std::string& heading, std::vector< std::string >& path);](#CAddonGUIDialogFileBrowser_ShowAndGetImageList)

-------------

*<p align="center">![SUID](help.GUIDialogFileBrowser.ShowAndGetDirectory.png)</p>*

-------------

*  <a id="CAddonGUIDialogFileBrowser_ShowAndGetDirectory"></a><b>`bool CAddonGUIDialogFileBrowser::ShowAndGetDirectory(const std::string& shares, const std::string& heading, std::string& path, bool bWriteOnly = false);`</b>
    * Function through a dialog to choose a folder by a user of the add-ons.
	    * **`shares`:**             With the value of [shares](../Readme.md#directorysharestrings) it is selected which
	                                source are accessible by the user and defines by text, as for example
                                  "local|network|removable".
	    * **`heading`:**            Define the title name of the dialog.
	    * **`path`:**               The well-chosen folder is stored in added pointer.
	    * **`bWriteOnly`:**         If set, only folders can be selected allow the writing access by the user.
	    * **return:**               False when was canceled by the user.

      Code example:
      ```cpp
      #include <kodi/gui.api2/GUIDialogFileBrowser.h>
      
      /*
      * Example show directory selection dialog with on 'share' (first value)
      * defined directory types.
      *
      * If this becomes leaved empty and 'directory' is empty goes it to the
      * base path of the hard disk.
      *
      * Also can be with path written to 'directory' before the dialog forced
      * to a start place.
      */ 
      std::string directory;
      bool ret = CAddonGUIDialogFileBrowser::ShowAndGetDirectory("local|network|removable",
                                                         "Test directory selection",
                                                         directory,
                                                         false);
      fprintf(stderr, "Selected directory is : %s and was %s\n", directory.c_str(), ret ? "OK" : "Canceled");
      ```

*  <a id="CAddonGUIDialogFileBrowser_ShowAndGetFile"></a><b>`bool CAddonGUIDialogFileBrowser::ShowAndGetFile(const std::string& shares, const std::string& mask, const std::string& heading, std::string& path, bool useThumbs = false, bool useFileDirectories = false);`</b>
    * File selection dialog
      * **`shares`:**             With the value of [shares](../Readme.md#directorysharestrings) it is selected which source are accessible by the user and defines by text, as for example "local|network|removable".
      * **`mask`:**               The value "mask" defines, the file types shown on the list, e.g. ".avi|.mpg". Everyone is shown if it is left empty.
      * **`heading`:**            Define the title name of the dialog.
      * **`path`:**               The selected file is stored in the passed pointer of "path".
      * **`useThumbs`:**          If it is set to "true" will be displayed with the images of the individual files.
      * **`useFileDirectories`:** Packed files (e. g. Zip) are used as a folder if this is "true".
      * **`singleList`:**         With this set point, the used Startup folder is used alone, can not be abandoned.
      * **return:**               False when was canceled by the user.

      Code example:
      ```cpp
      #include <kodi/gui.api2/GUIDialogFileBrowser.h>
      
      std::string file;
      CAddonGUIDialogFileBrowser::ShowAndGetFile("/",
                                                 ".avi",
                                                 "Test file selection",
                                                 file,
                                                 false,
                                                 true,
                                                 false);
      fprintf(stderr, "Selected file is : %s\n", file.c_str());
      ```
*  <a id="CAddonGUIDialogFileBrowser_ShowAndGetFileFromDir"></a><b>`bool CAddonGUIDialogFileBrowser::ShowAndGetFileFromDir(const std::string& directory, const std::string& mask, const std::string& heading, std::string& path, bool useThumbs = false, bool useFileDirectories = false, bool singleList = false);`</b>
    * File selection from a directory
      * **`directory`:**          Start directory of dialog
      * **`mask`:**               The value "mask" defines, the file types shown on the list, e.g. ".avi|.mpg". Everyone is                                   shown if it is left empty.
      * **`heading`:**            Define the title name of the dialog.
      * **`path`:**               To get the selected file name with path. 
      * **`useThumbs`:**          If it is set to "true" will be displayed with the images of the individual files.
      * **`useFileDirectories`:** Packed files (e. g. Zip) are used as a folder if this is "true".
      * **`singleList`:**         With this set point, the used Startup folder is used alone, can not be abandoned.
      * **return:**               False when was canceled by the user.

*  <a id="CAddonGUIDialogFileBrowser_ShowAndGetFileList"></a><b>`bool CAddonGUIDialogFileBrowser::ShowAndGetFileList(const std::string& shares, const std::string& mask, const std::string& heading, std::vector<std::string>& path, bool useThumbs = false, bool useFileDirectories = false);`</b>
    * File selection dialog to get several in to a list
      * **`shares`:**             With the value of [shares](../Readme.md#directorysharestrings) it is selected which
	                                source are accessible by the user and defines by text, as for example
                                  "local|network|removable".
      * **`mask`:**               The value "mask" defines, the file types shown on the list, e.g. ".avi|.mpg". Everyone is                                   shown if it is left empty.
      * **`heading`:**            To the define the title name of the dialog.
      * **`path`:**               Get the selected file name with path.
      * **`useThumbs`:**          If it is set to "true" will be displayed with the images of the individual files.
      * **`useFileDirectories`:** Packed files (e. g. Zip) are used as a folder if this is "true".
      * **return:**               False when was canceled by the user.

*  <a id="CAddonGUIDialogFileBrowser_ShowAndGetSource"></a><b>`bool CAddonGUIDialogFileBrowser::ShowAndGetSource(std::string& path, bool allowNetworkShares, const std::string& additionalShare, const std::string& strType = "");`</b>
    * Dialog to select a data source.
      Technique is:
      - 1.  Show Filebrowser with currently defined local, and optionally the network locations.
      - 2.  Have the "Add Network Location" option in addition.
      - 3a. If the "Add Network Location" is pressed, then:
          - a) Fire up the network location dialog to grab the new location
          - b) Check the location by doing a GetDirectory() - if it fails, prompt the user
             to allow them to add currently disconnected network shares.
          - c) Save this location to our xml file (network.xml)
          - d) Return to 1.
      - 3b. If the "Add Source" is pressed, then:
          - a) Fire up the media source dialog to add the new location
      - 4.  Optionally allow user to browse the local and network locations for their share.
      - 5.  On OK, return.
      * **`path`:**               Pointer for storing the selected source.
      * **`allowNetworkShares`:** Allow also access to network
      * **`additionalShare`:**    With [additionalShare](../Readme.md#directorysharestrings) becomes the available start folders be 
                                  set.
      * **`strType`:**            To define the type of source.
        <table>
            <thead>
                <tr>
                  <th><sub>Type:</sub></th>
                  <th><sub>Description:</sub></th>
                </tr>
            </thead>
            <tr>
                <td>programs</td>
                <td>Programs defined shares</td>
            </tr>
            <tr>
                <td>files</td>
                <td>Files defined shares</td>
            </tr>
            <tr>
                <td>music</td>
                <td>Music defined sources</td>
            </tr>
            <tr>
                <td>video</td>
                <td>Video defined shares</td>
            </tr>
            <tr>
                <td>pictures</td>
                <td>Pictures defined shares</td>
            </tr>
        </table>
      * **return:**               False if selection becomes canceled.

*  <a id="CAddonGUIDialogFileBrowser_ShowAndGetImage"></a><b>`bool CAddonGUIDialogFileBrowser::ShowAndGetImage(const std::string& shares, const std::string& heading, std::string& path);`</b>
    * To select an image from the dialog.
      * **`shares`:**             With the value of [shares](../Readme.md#directorysharestrings) it is selected which
	                                source are accessible by the user and defines by text, as for example
                                  "local|network|removable".
      * **`heading`:**            Define the title name of the dialog.
      * **`path`:**               Transmitted pointer for storing the selected image.
      * **return:**               False when was canceled by the user.

*  <a id="CAddonGUIDialogFileBrowser_ShowAndGetImageList"></a><b>`bool CAddonGUIDialogFileBrowser::ShowAndGetImageList(const std::string& shares, const std::string& heading, std::vector<std::string>& path);`</b>
    * To select multiple images from the dialog.
      * **`shares`:**             With the value of [shares](../Readme.md#directorysharestrings) it is selected which
	                                source are accessible by the user and defines by text, as for example
                                  "local|network|removable".
      * **`heading`:**            To the define the title name of the dialog.
      * **`path`:**               Transferred pointer to save the selected images in a list.
      * **return:**               False when was canceled by the user.

      Code example:
      ```cpp
      #include <kodi/gui.api2/GUIDialogFileBrowser.h>
      
      std::vector<std::string> imageList;
      bool ret = CAddonGUIDialogFileBrowser::ShowAndGetImageList("local|removable",
                                                 "Test image selection",
                                                 imageList);
      if (ret)
      {
        fprintf(stderr, "Selected images : %lu\n", imageList.size());
        for (unsigned int i = 0; i < imageList.size(); i++)
          fprintf(stderr, " - %02i : %s\n", i+1, imageList[i].c_str());
      }
      ```
