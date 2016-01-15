# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md)
</p>*
#### *<p align="center">Group: ```File```</p>*
----------

Functions
-------------

The with ```#include <kodi/addon.api2/File.h``` given functions are basically used to allow add-on access to file system.

*  <b>```bool CAddOnLib_File::FileExists(const std::string& strFileName, bool bUseCache);```</b>
    * Check if a file exists.
	    * <b>```strFileName```</b> The filename to check.
	    * <b>```bUseCache```</b> Check in file cache.
		* <b>return:</b> true if the file exists false otherwise.

*  <b>```int CAddOnLib_File::StatFile(const std::string& strFileName, struct __stat64* buffer);```</b>
    * Reads file status.
	    * <b>```strFileName```</b> The filename to read the status from.
 	    * <b>```buffer```</b> The file status is written into this buffer.
		* <b>return:</b> true if file status was successfully read.

*  <b>```bool CAddOnLib_File::DeleteFile(const std::string& strFileName);```</b>
    * Deletes a file.
	    * <b>```strFileName```</b> The filename to delete.
		* <b>return:</b> true if the file was successfully deleted.

*  <b>```std::string CAddOnLib_File::GetFileMD5(const std::string& strPath);```</b>
    * Retrieve MD5sum of a file
	    * <b>```strPath```</b> The file to MD5sum
		* <b>return:</b> md5 sum of the file.

*  <b>```unsigned int CAddOnLib_File::GetChunkSize(unsigned int chunk, unsigned int minimum);```</b>
    * Return a size aligned to the chunk size at least as large as the 
	    * <b>```chunk```</b> The chunk size
	    * <b>```minimum```</b> The minimum size (or maybe the minimum number of chunks?)
		* <b>return:</b> The aligned size

*  <b>```std::string CAddOnLib_File::GetFileName(const std::string&  path, char separator = PATH_SEPARATOR_CHAR);```</b>
    * Return the file name from given complete path string
	    * <b>```path```</b> The URL of the directory to check.
	    * <b>```separator```</b> The used folder separator (Windows ```\```, the others ```/```.
		* <b>return:</b>  File with removed directory path

*  <b>```std::string CAddOnLib_File::GetDirectoryName(const std::string& path, char separator = PATH_SEPARATOR_CHAR);```</b>
    * Return the directory name from given complete path string
	    * <b>```path```</b> The URL of the directory to check.
	    * <b>```separator```</b> The used folder separator (Windows ```\```, the others ```/```.
		* <b>return:</b>  Directory with removed file name

----------

Classes
-------------

#### Class: ```CVFSFile::CVFSFile();```

*  <b>```CVFSFile();```</b>
    * Construct a new, unopened file

*  <b>```virtual ~CVFSFile();```</b>
    * Close() is called from the destructor, so explicitly closing the file isn't required

*  <b>```bool Open(const std::string& strFileName, unsigned int flags = 0);```</b>
    * Open the file with filename via KODI's CFile. Needs to be closed by calling CloseFile() when done.
		* <b>```strFileName```</b> The filename to open.
		* <b>```flags```</b> The flags to pass. Documented in KODI's File.h
		* <b>return:</b> True on success or false on failure.

*  <b>```bool OpenForWrite(const std::string& strFileName, bool bOverWrite = false);```</b>
    * Open the file with filename via KODI's CFile in write mode. Needs to be closed by calling CloseFile() when done.
		* <b>```strFileName```</b> The filename to open.
		* <b>```bOverWrite```</b> True to overwrite, false otherwise.
		* <b>return:</b> True on success or false on failure.

*  <b>```ssize_t Read(void* lpBuf, size_t uiBufSize);```</b>
    * Read from an open file.
		* <b>```lpBuf```</b> The buffer to store the data in.
		* <b>```uiBufSize```</b> The size of the buffer.
		* <b>return:</b> of successfully read bytes if any bytes were read and stored in buffer, zero if no bytes are available to read (end of file was reached) or undetectable error occur, -1 in case of any explicit error.

*  <b>```bool ReadLine(std::string &strLine);```</b>
    * Read a string from an open file.
		* <b>```strLine```</b> The buffer to store the data in.
		* <b>return:</b> True when a line was read, false otherwise.

*  <b>```ssize_t Write(const void* lpBuf, size_t uiBufSize);```</b>
    * Write to a file opened in write mode.
		* <b>```lpBuf```</b> The data to write.
		* <b>```uiBufSize```</b> Size of the data to write.
		* <b>return:</b> Number of successfully written bytes if any bytes were.

*  <b>```void Flush();```</b>
    * Flush buffered data.

*  <b>```int64_t Seek(int64_t iFilePosition, int iWhence);```</b>
    * Seek in an open file.
		* <b>```iFilePosition```</b> The new position.
		* <b>```iWhence```</b> Seek argument. See stdio.h for possible values.
		* <b>return:</b> The new position.

*  <b>```int Truncate(int64_t iSize);```</b>
    * Truncate a file to the requested size.
		* <b>```iSize```</b> The new max size.
		* <b>return:</b> New size?

*  <b>```int64_t GetPosition();```</b>
    * The current position in an open file.
		* <b>return:</b> The requested position.

*  <b>```int64_t GetLength();```</b>
    * Get the file size of an open file.
		* <b>return:</b> The requested size.

*  <b>```void Close();```</b>
    * Close an open file.
		* <b>return:</b> The file handle to close.

*  <b>```int GetChunkSize();```</b>
    * Get the chunk size for an open file.
		* <b>return:</b> The requested size.

----------
