#pragma once
/*
 *      Copyright (C) 2015 Team KODI
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with KODI; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "definations.h"
#include "internal/libKODI_addon_VFSUtilsHead.h"
#include "internal/libKODI_addon_Internal.h"

namespace AddOnLIB
{
namespace V2
{

  ///
  /// \defgroup CAddonLib_VFSProperty
  /// \ingroup AddOnLIB
  /// @{
  /// @brief <b>Virtual file system entry property</b>
  ///
  /// The CAddonLib_VFSProperty is used to manage additional file information,
  /// if present it will be used in CAddonLib_VFSDirEntry as a list.
  ///
  /// The additional information will be provided with text, either for the name as well
  /// as for the value.
  ///
  /// It has the header \ref VFSUtils.h "#include <kodi/addon.api2/VFSUtils.h>" be included
  /// to enjoy it.
  ///
  class CAddonLib_VFSProperty
  {
  public:
    ///
    /// @ingroup CAddonLib_VFSProperty
    /// @brief Constructor
    ///
    /// @param[in] name Property name
    /// @param[in] value Defined value to use
    ///
    CAddonLib_VFSProperty(const std::string& name, const std::string& value);

    ///
    /// @ingroup CAddonLib_VFSProperty
    /// @brief Used Name
    ///
    /// @return Defined name
    ///
    const std::string& Name(void) const;

    ///
    /// @ingroup CAddonLib_VFSProperty
    /// @brief Get defined value
    ///
    /// @return Defined value
    ///
    const std::string& Value(void) const;

    ///
    /// @ingroup CAddonLib_VFSProperty
    /// @brief Set name to use
    ///
    /// @param[in] name Property name
    ///
    void SetName(const std::string& name);

    ///
    /// @ingroup CAddonLib_VFSProperty
    /// @brief Set defined value
    ///
    /// @param[in] value Defined value to use
    ///
    void SetValue(const std::string& value);

    IMPL_VFS_PROPERTY;
  };
  /// @}

  /*\___________________________________________________________________________
  \*/

  ///
  /// \defgroup CAddonLib_VFSDirEntry
  /// \ingroup AddOnLIB
  /// @{
  /// @brief <b>Virtual file system directory entry</b>
  ///
  /// This class is used as an entry for files and folders in
  /// CAddonLib_VFSUtils::GetDirectory(...).
  ///
  /// @b Example:
  /// @code
  /// #include <kodi/addon.api2/VFSUtils.h>
  ///
  /// std::vector<CAddonLib_VFSDirEntry> items;
  /// CAddonLib_VFSUtils::GetDirectory("special://temp", "", items);
  ///
  /// fprintf(stderr, "Directory have %lu entries\n", items.size());
  /// for (unsigned long i = 0; i < items.size(); i++)
  /// {
  ///   fprintf(stderr, " - %04lu -- Folder: %s -- Name: %s -- Path: %s\n",
  ///             i+1,
  ///             items[i].IsFolder() ? "yes" : "no ",
  ///             items[i].Label().c_str(),
  ///             items[i].Path().c_str());
  /// }
  /// @endcode
  ///
  /// It has the header \ref VFSUtils.h "#include <kodi/addon.api2/VFSUtils.h>" be included
  /// to enjoy it.
  ///
  class CAddonLib_VFSDirEntry
  {
  public:
    ///
    /// @ingroup CAddonLib_VFSDirEntry
    /// @brief Constructor for VFS directory entry
    ///
    /// @param[in] label   [opt] Name to use for entry
    /// @param[in] path    [opt] Used path of the entry
    /// @param[in] bFolder [opt] If set entry used as folder
    /// @param[in] size    [opt] If used as file, his size defined there
    ///
    CAddonLib_VFSDirEntry(
        const std::string&  label   = "",
        const std::string&  path    = "",
        bool                bFolder = false,
        int64_t             size    = -1);

    ///
    /// @ingroup CAddonLib_VFSDirEntry
    /// @brief Constructor to create own copy
    ///
    /// @param[in] dirEntry pointer to own class type
    ///
    CAddonLib_VFSDirEntry(const VFSDirEntry& dirEntry);

    ///
    /// @ingroup CAddonLib_VFSDirEntry
    /// @brief Get the directory entry name
    ///
    /// @return Name of the entry
    ///
    const std::string& Label(void) const;

    ///
    /// @ingroup CAddonLib_VFSDirEntry
    /// @brief Get the path of the entry
    ///
    /// @return File system path of the entry
    ///
    const std::string& Path(void) const;

    ///
    /// @ingroup CAddonLib_VFSDirEntry
    /// @brief Used to check entry is folder
    ///
    /// @return true if entry is a folder
    ///
    bool IsFolder(void) const;

    ///
    /// @ingroup CAddonLib_VFSDirEntry
    /// @brief If file, the size of the file
    ///
    /// @return Defined file size
    ///
    int64_t Size(void) const;

    ///
    /// @ingroup CAddonLib_VFSDirEntry
    /// @brief Get the properties of the entry
    ///
    /// @return Not editable array pointer to properties
    ///
    const std::vector<CAddonLib_VFSProperty>& Properties(void) const;

    ///
    /// @ingroup CAddonLib_VFSDirEntry
    /// @brief Set the label name
    ///
    /// @param[in] label name of entry
    ///
    void SetLabel(const std::string& label);

    ///
    /// @ingroup CAddonLib_VFSDirEntry
    /// @brief Set the path of the entry
    ///
    /// @param[in] path path of entry
    ///
    void SetPath(const std::string& path);

    ///
    /// @ingroup CAddonLib_VFSDirEntry
    /// @brief Set the entry defined as folder
    ///
    /// @param[in] bFolder If true becomes entry defined as folder
    ///
    void SetFolder(bool bFolder);

    ///
    /// @ingroup CAddonLib_VFSDirEntry
    /// @brief Set a file size for a new entry
    ///
    /// @param[in] size Size to set for dir entry
    ///
    void SetSize(int64_t size);

    ///
    /// @ingroup CAddonLib_VFSDirEntry
    /// @brief Get the editable array pointer for the entry
    ///
    /// @return Array pointer to properties
    ///
    std::vector<CAddonLib_VFSProperty>& Properties(void);

    IMPL_VFS_DIR_ENTRY;
  };
  /// @}

  /*\___________________________________________________________________________
  \*/

  ///
  /// \defgroup CAddonLib_VFSFile
  /// \ingroup AddOnLIB
  /// @{
  /// @brief <b>Virtual file system control</b>
  ///
  /// It has the header \ref VFSUtils.h "#include <kodi/addon.api2/VFSUtils.h>" be included
  /// to enjoy it.
  ///
  class CAddonLib_VFSFile
  {
  public:
    ///
    /// @ingroup CAddonLib_VFSFile
    /// @brief Construct a new, unopened file
    ///
    CAddonLib_VFSFile();

    ///
    /// @ingroup CAddonLib_VFSFile
    /// @brief Close() is called from the destructor, so explicitly closing the
    /// file isn't required
    ///
    virtual ~CAddonLib_VFSFile();

    ///
    /// @ingroup CAddonLib_VFSFile
    /// @brief Open the file with filename via KODI's CFile. Needs to be closed by calling CloseFile() when done.
    ///
    /// @param[in] strFileName The filename to open.
    /// @param[in] flags The flags to pass. Documented in KODI's VFSUtils.h
    /// @return True on success or false on failure
    ///
    bool OpenFile(const std::string& strFileName, unsigned int flags = 0);

    ///
    /// @ingroup CAddonLib_VFSFile
    /// @brief Open the file with filename via KODI's CFile in write mode. Needs to be closed by calling CloseFile() when done.
    ///
    /// @param[in] strFileName The filename to open.
    /// @param[in] bOverWrite True to overwrite, false otherwise.
    /// @return True on success or false on failure
    ///
    bool OpenFileForWrite(const std::string& strFileName, bool bOverWrite = false);

    ///
    /// @ingroup CAddonLib_VFSFile
    /// @brief Read from an open file.
    ///
    /// @param[in] lpBuf The buffer to store the data in.
    /// @param[in] uiBufSize The size of the buffer.
    /// @return number of successfully read bytes if any bytes were read and stored in
    ///         buffer, zero if no bytes are available to read (end of file was reached)
    ///         or undetectable error occur, -1 in case of any explicit error
    ///
    ssize_t Read(void* lpBuf, size_t uiBufSize);

    ///
    /// @ingroup CAddonLib_VFSFile
    /// @brief Read a string from an open file.
    ///
    /// @param[in] strLine The buffer to store the data in.
    /// @return True when a line was read, false otherwise.
    ///
    bool ReadLine(std::string &strLine);

    ///
    /// @ingroup CAddonLib_VFSFile
    /// @brief Write to a file opened in write mode.
    ///
    /// @param[in] lpBuf The data to write.
    /// @param[in] uiBufSize Size of the data to write.
    /// @return number of successfully written bytes if any bytes were written,
    ///         zero if no bytes were written and no detectable error occur,
    ///         -1 in case of any explicit error
    ///
    ssize_t Write(const void* lpBuf, size_t uiBufSize);

    ///
    /// @ingroup CAddonLib_VFSFile
    /// @brief Flush buffered data.
    ///
    void Flush();

    ///
    /// @ingroup CAddonLib_VFSFile
    /// @brief Seek in an open file.
    ///
    /// @param[in] iFilePosition The new position.
    /// @param[in] iWhence Seek argument. See stdio.h for possible values.
    /// @return The new position.
    ///
    int64_t Seek(int64_t iFilePosition, int iWhence);

    ///
    /// @ingroup CAddonLib_VFSFile
    /// @brief Truncate a file to the requested size.
    ///
    /// @param[in] iSize The new max size.
    /// @return New size?
    ///
    int Truncate(int64_t iSize);

    ///
    /// @ingroup CAddonLib_VFSFile
    /// @brief The current position in an open file.
    ///
    /// @return The requested position.
    ///
    int64_t GetPosition();

    ///
    /// @ingroup CAddonLib_VFSFile
    /// @brief Get the file size of an open file.
    ///
    /// @return The requested size.
    ///
    int64_t GetLength();

    ///
    /// @ingroup CAddonLib_VFSFile
    /// @brief Close an open file.
    ///
    void Close();

    ///
    /// @ingroup CAddonLib_VFSFile
    /// @brief Get the chunk size for an open file.
    ///
    /// @return The requested size.
    ///
    int GetChunkSize();

    IMPL_FILE;
  };
  /** @}*/

  /*\___________________________________________________________________________
  \*/

  ///
  /// \defgroup CAddonLib_VFSUtils
  /// \ingroup AddOnLIB
  /// @{
  /// @brief <b>Virtual file system utilities</b>
  ///
  /// These are pure static functions them no other initialization need.
  ///
  /// It has the header \ref VFSUtils.h "#include <kodi/addon.api2/VFSUtils.h>" be included
  /// to enjoy it.
  ///
  class CAddonLib_VFSUtils
  {
  public:

    ///
    /// @ingroup CAddonLib_VFSUtils
    /// @brief Make a directory
    ///
    /// The CAddonLib_VFSUtils::CreateDirectory(...) function shall create a new
    /// directory with name path.
    ///
    /// The newly created directory shall be an empty directory.
    ///
    /// @param[in] strPath Path to the directory.
    /// @return  Upon successful completion, CreateDirectory() shall return true.
    ///          Otherwise,false shall be returned, no directory shall be created,
    ///          and errno shall be set to indicate the error.
    ///
    /// @b Example:
    /// @code
    /// #include <kodi/addon.api2/VFSUtils.h>
    /// ...
    /// std::string directory = "C:\\my_dir";
    /// bool ret = CAddonLib_VFSUtils::CreateDirectory(directory);
    /// fprintf(stderr, "Directory '%s' successfull created: %s\n", directory.c_str(), ret ? "yes" : "no");
    /// ...
    /// @endcode
    ///
    static bool CreateDirectory(const std::string& strPath);

    ///
    /// @ingroup CAddonLib_VFSUtils
    /// @brief Verifying the Existence of a Directory
    ///
    /// The CAddonLib_VFSUtils::DirectoryExists(...) method determines whether
    /// a specified folder exists.
    ///
    /// @param[in] strPath Path to the directory.
    /// @return True when it exists, false otherwise.
    ///
    /// @b Example:
    /// @code
    /// #include <kodi/addon.api2/VFSUtils.h>
    /// ...
    /// std::string directory = "C:\\my_dir";
    /// bool ret = CAddonLib_VFSUtils::DirectoryExists(directory);
    /// fprintf(stderr, "Directory '%s' present: %s\n", directory.c_str(), ret ? "yes" : "no");
    /// ...
    /// @endcode
    ///
    static bool DirectoryExists(const std::string& strPath);

    ///
    /// @ingroup CAddonLib_VFSUtils
    /// @brief Removes a directory.
    ///
    /// The CAddonLib_VFSUtils::RemoveDirectory(...) function shall remove a
    /// directory whose name is given by path.
    ///
    /// @param[in] strPath Path to the directory.
    /// @return  Upon successful completion, the function RemoveDirectory() shall
    ///          return true. Otherwise, false shall be returned, and errno set
    ///          to indicate the error. If false is returned, the named directory
    ///          shall not be changed.
    ///
    /// @b Example:
    /// @code
    /// #include <kodi/addon.api2/VFSUtils.h>
    /// ...
    /// bool ret = CAddonLib_VFSUtils::RemoveDirectory("C:\\my_dir");
    /// ...
    /// @endcode
    ///
    static bool RemoveDirectory(const std::string& strPath);

    ///
    /// @ingroup CAddonLib_VFSUtils
    /// @brief Lists a directory.
    ///
    /// Return the list of files and directories which have been found in the
    /// specified directory and which respect the given constraint.
    ///
    /// It can handle the normal OS dependent paths and also the special virtual
    /// filesystem from Kodi what starts with \b special://.
    ///
    /// @param[in]  path  The path in which the files and directories are located.
    /// @param[in]  mask  Mask to filter out requested files, e.g. "*.avi|*.mpg" to
    ///                   files with this ending.
    /// @param[out] items The returned list directory entries.
    /// @return           True if listing was successful, false otherwise.
    ///
    /// @b Example:
    /// @code
    /// #include <kodi/addon.api2/VFSUtils.h>
    ///
    /// std::vector<CAddonLib_VFSDirEntry> items;
    /// CAddonLib_VFSUtils::GetDirectory("special://temp", "", items);
    ///
    /// fprintf(stderr, "Directory have %lu entries\n", items.size());
    /// for (unsigned long i = 0; i < items.size(); i++)
    /// {
    ///   fprintf(stderr, " - %04lu -- Folder: %s -- Name: %s -- Path: %s\n",
    ///             i+1,
    ///             items[i].IsFolder() ? "yes" : "no ",
    ///             items[i].Label().c_str(),
    ///             items[i].Path().c_str());
    /// }
    /// @endcode
    ///
    static bool GetDirectory(
               const std::string&          path,
               const std::string&          mask,
               std::vector<CAddonLib_VFSDirEntry>&  items);

    ///
    /// @ingroup CAddonLib_VFSUtils
    /// @brief Check if a file exists.
    ///
    /// @param[in] strFileName The filename to check.
    /// @param[in] bUseCache Check in file cache.
    /// @return true if the file exists false otherwise.
    ///
    /// @b Example:
    /// @code
    /// #include <kodi/addon.api2/VFSUtils.h>
    /// ...
    /// bool exists = CAddonLib_VFSUtils::FileExists("special://temp/kodi.log");
    /// fprintf(stderr, "Log file should be always present, is it present? %s\n", exists ? "yes" : "no");
    /// @endcode
    ///
    static bool FileExists(const std::string& strFileName, bool bUseCache = false);

    ///
    /// @ingroup CAddonLib_VFSUtils
    /// @brief Get file status.
    ///
    /// These function return information about a file. Execute (search)
    /// permission is required on all of the directories in path that
    /// lead to the file.
    ///
    /// The call return a stat structure, which contains the following fields:
    /// @code
    /// struct __stat64 {
    ///   dev_t     st_dev;     /* ID of device containing file */
    ///   ino_t     st_ino;     /* inode number */
    ///   mode_t    st_mode;    /* protection */
    ///   nlink_t   st_nlink;   /* number of hard links */
    ///   uid_t     st_uid;     /* user ID of owner */
    ///   gid_t     st_gid;     /* group ID of owner */
    ///   dev_t     st_rdev;    /* device ID (if special file) */
    ///   off_t     st_size;    /* total size, in bytes */
    ///   blksize_t st_blksize; /* blocksize for file system I/O */
    ///   blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
    ///   time_t    st_atime;   /* time of last access */
    ///   time_t    st_mtime;   /* time of last modification */
    ///   time_t    st_ctime;   /* time of last status change */
    /// };
    /// @endcode
    ///
    /// The st_dev field describes the device on which this file resides.
    /// The st_rdev field describes the device that this file (inode) represents.
    ///
    /// The st_size field gives the size of the file (if it is a regular file or
    /// a symbolic link) in bytes. The size of a symbolic link (only on Linux
    /// and Mac OS X) is the length of the pathname it contains, without a
    /// terminating null byte.
    ///
    /// The st_blocks field indicates the number of blocks allocated to the file,
    /// 512-byte units. (This may be smaller than st_size/512 when the file has
    /// holes.).
    ///
    /// The st_blksize field gives the "preferred" blocksize for efficient file
    /// system I/O. (Writing to a file in smaller chunks may cause an inefficient
    /// read-modify-rewrite.)
    ///
    /// @warning Not all of the OS file systems implement all of the time fields.
    ///
    /// @param[in] strFileName The filename to read the status from.
    /// @param[in] buffer The file status is written into this buffer.
    /// @return On success, zero is returned. On error, -1 is returned, and errno
    /// is set appropriately.
    ///
    /// @b Example:
    /// @code
    /// #include <kodi/addon.api2/VFSUtils.h>
    /// ...
    /// struct __stat64 statFile;
    /// int ret = CAddonLib_VFSUtils::StatFile("special://temp/kodi.log", &statFile);
    /// fprintf(stderr, "st_dev (ID of device containing file)       = %lu\n"
    ///                 "st_ino (inode number)                       = %lu\n"
    ///                 "st_mode (protection)                        = %u\n"
    ///                 "st_nlink (number of hard links)             = %lu\n"
    ///                 "st_uid (user ID of owner)                   = %u\n"
    ///                 "st_gid (group ID of owner)                  = %u\n"
    ///                 "st_rdev (device ID (if special file))       = %lu\n"
    ///                 "st_size (total size, in bytes)              = %lu\n"
    ///                 "st_blksize (blocksize for file system I/O)  = %lu\n"
    ///                 "st_blocks (number of 512B blocks allocated) = %lu\n"
    ///                 "st_atime (time of last access)              = %lu\n"
    ///                 "st_mtime (time of last modification)        = %lu\n"
    ///                 "st_ctime (time of last status change)       = %lu\n"
    ///                 "Return value                                = %i\n",
    ///                      statFile.st_dev,
    ///                      statFile.st_ino,
    ///                      statFile.st_mode,
    ///                      statFile.st_nlink,
    ///                      statFile.st_uid,
    ///                      statFile.st_gid,
    ///                      statFile.st_rdev,
    ///                      statFile.st_size,
    ///                      statFile.st_blksize,
    ///                      statFile.st_blocks,
    ///                      statFile.st_atime,
    ///                      statFile.st_mtime,
    ///                      statFile.st_ctime,
    ///                      ret);
    /// @endcode
    ///
    static int StatFile(const std::string& strFileName, struct __stat64* buffer);

    ///
    /// @ingroup CAddonLib_VFSUtils
    /// @brief Deletes a file.
    ///
    /// @param[in] strFileName The filename to delete.
    /// @return The file was successfully deleted.
    ///
    /// @b Example:
    /// @code
    /// #include <kodi/addon.api2/VFSUtils.h>
    /// #include <kodi/gui.api2/GUIDialogFileBrowser.h>
    /// #include <kodi/gui.api2/GUIDialogOK.h>
    /// ...
    /// std::string filename;
    /// if (CAddonGUIDialogFileBrowser::ShowAndGetFile("local", "",
    ///                                                "Test File selection and delete of them!",
    ///                                                filename))
    /// {
    ///   bool successed = CAddonLib_VFSUtils::DeleteFile(filename);
    ///   if (!successed)
    ///     CAddonGUIDialogOK::ShowAndGetInput("Error", "Delete of File", filename, "failed!");
    ///   else
    ///     CAddonGUIDialogOK::ShowAndGetInput("Information", "Delete of File", filename, "successfull done.");
    /// }
    /// @endcode
    ///
    static bool DeleteFile(const std::string& strFileName);

    ///
    /// @ingroup CAddonLib_VFSUtils
    /// @brief Retrieve MD5sum of a file
    ///
    /// @param[in] strPath path to the file to MD5sum
    /// @return md5 sum of the file
    ///
    /// @b Example:
    /// @code
    /// #include <kodi/addon.api2/VFSUtils.h>
    /// #include <kodi/gui.api2/GUIDialogFileBrowser.h>
    /// ...
    /// std::string md5;
    /// std::string filename;
    /// if (CAddonGUIDialogFileBrowser::ShowAndGetFile("local", "*.avi|*.mpg|*.mp4",
    ///                                                "Test File selection to get MD5",
    ///                                                filename))
    /// {
    ///   md5 = CAddonLib_VFSUtils::GetFileMD5(filename);
    ///   fprintf(stderr, "MD5 of file '%s' is %s\n", md5.c_str(), filename.c_str());
    /// }
    /// @endcode
    ///
    static std::string GetFileMD5(const std::string& strPath);

    ///
    /// @ingroup CAddonLib_VFSUtils
    /// @brief Returns a thumb cache filename
    ///
    /// @param[in] strFileName path to file
    /// @return cache filename
    ///
    /// @b Example:
    /// @code
    /// #include <kodi/addon.api2/VFSUtils.h>
    /// #include <kodi/gui.api2/GUIDialogFileBrowser.h>
    /// ...
    /// std::string thumb;
    /// std::string filename;
    /// if (CAddonGUIDialogFileBrowser::ShowAndGetFile("local", "*.avi|*.mpg|*.mp4",
    ///                                                "Test File selection to get Thumnail",
    ///                                                filename))
    /// {
    ///   thumb = CAddonLib_VFSUtils::GetCacheThumbName(filename);
    ///   fprintf(stderr, "Thumb name of file '%s' is %s\n", thumb.c_str(), filename.c_str());
    /// }
    /// @endcode
    ///
    static std::string GetCacheThumbName(const std::string& strFileName);

    ///
    /// @ingroup CAddonLib_VFSUtils
    /// @brief Make filename valid
    ///
    /// Function to replace not valid characters with '_'. It can be also
    /// compared with original before in a own loop until it is equal
    /// (no invalid characters).
    ///
    /// @param[in] strFileName Filename to check and fix
    /// @return            The legal filename
    ///
    /// @b Example:
    /// @code
    /// #include <kodi/addon.api2/VFSUtils.h>
    /// ...
    /// std::string fileName = "///\\jk???lj????.mpg";
    /// std::string legalName = CAddonLib_VFSUtils::MakeLegalFileName(fileName);
    /// fprintf(stderr, "Legal name of '%s' is '%s'\n", fileName.c_str(), legalName.c_str());
    ///
    /// /* Returns as legal: 'jk___lj____.mpg' */
    /// @endcode
    ///
    static std::string MakeLegalFileName(const std::string& strFileName);

    ///
    /// @ingroup CAddonLib_VFSUtils
    /// @brief Make directory name valid
    ///
    /// Function to replace not valid characters with '_'. It can be also
    /// compared with original before in a own loop until it is equal
    /// (no invalid characters).
    ///
    /// @param[in] strPath Directory name to check and fix
    /// @return        The legal directory name
    ///
    /// @b Example:
    /// @code
    /// #include <kodi/addon.api2/VFSUtils.h>
    /// ...
    /// std::string path = "///\\jk???lj????\\hgjkg";
    /// std::string legalPath = CAddonLib_VFSUtils::MakeLegalPath(path);
    /// fprintf(stderr, "Legal name of '%s' is '%s'\n", path.c_str(), legalPath.c_str());
    ///
    /// /* Returns as legal: '/jk___lj____/hgjkg' */
    /// @endcode
    ///
    static std::string MakeLegalPath(const std::string& strPath);

    ///
    /// @ingroup CAddonLib_VFSUtils
    /// @brief Return a size aligned to the chunk size at least as large as the chunk size.
    ///
    /// @param[in] chunk The chunk size
    /// @param[in] minimum The minimum size (or maybe the minimum number of chunks?)
    /// @return The aligned size
    ///
    static unsigned int GetChunkSize(unsigned int chunk, unsigned int minimum);

    ///
    /// @ingroup CAddonLib_VFSUtils
    /// @brief Return the file name from given complate path string
    ///
    /// @param[in] path The complete path include file and directory
    /// @return Filename from path
    ///
    /// @b Example:
    /// @code
    /// #include <kodi/addon.api2/VFSUtils.h>
    /// ...
    /// std::string fileName = CAddonLib_VFSUtils::GetFileName("special://temp/kodi.log");
    /// fprintf(stderr, "File name is '%s'\n", fileName.c_str());
    /// @endcode
    ///
    static std::string GetFileName(const std::string& path);

    ///
    /// @ingroup CAddonLib_VFSUtils
    /// @brief Return the directory name from given complate path string
    ///
    /// @param[in] path The complete path include file and directory
    /// @return Directory name from path
    ///
    /// @b Example:
    /// @code
    /// #include <kodi/addon.api2/VFSUtils.h>
    /// ...
    /// std::string dirName = CAddonLib_VFSUtils::GetDirectoryName("special://temp/kodi.log");
    /// fprintf(stderr, "Directory name is '%s'\n", dirName.c_str());
    /// @endcode
    ///
    static std::string GetDirectoryName(const std::string& path);
  };
  /// @}

}; /* namespace V2 */
}; /* namespace AddOnLIB */
#include "internal/libKODI_addon_VFSUtilsTail.h"
