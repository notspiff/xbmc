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

namespace AddOnLIB
{
namespace V2
{

  inline CAddonLib_VFSFile::CAddonLib_VFSFile()
   : m_pFile(nullptr),
     m_Handle(CAddonLib::g_libKODI_Internal->m_Handle),
     m_Callbacks(CAddonLib::g_libKODI_Internal->m_Callbacks)
  {

  }

  inline CAddonLib_VFSFile::~CAddonLib_VFSFile()
  {
    Close();
  }

  inline bool CAddonLib_VFSFile::OpenFile(const std::string& strFileName, unsigned int flags)
  {
    Close();
    m_pFile = CAddonLib::g_libKODI_Internal->OpenFile(strFileName, flags);
    return m_pFile != nullptr;
  }

  inline bool CAddonLib_VFSFile::OpenFileForWrite(const std::string& strFileName, bool bOverWrite)
  {
    Close();

    // Try to open the file. If it fails, check if we need to create the directory first
    // This way we avoid checking if the directory exists every time
    m_pFile = CAddonLib::g_libKODI_Internal->OpenFileForWrite(strFileName.c_str(), bOverWrite);
    if (!m_pFile)
    {
      std::string cacheDirectory = CAddonLib_File::GetDirectoryName(strFileName);
      if (CAddonLib::g_libKODI_Internal->DirectoryExists(cacheDirectory) || CAddonLib::g_libKODI_Internal->CreateDirectory(cacheDirectory))
        m_pFile = CAddonLib::g_libKODI_Internal->OpenFileForWrite(strFileName.c_str(), bOverWrite);
    }
    return m_pFile != nullptr;
  }

  inline ssize_t CAddonLib_VFSFile::Read(void* lpBuf, size_t uiBufSize)
  {
    if (!m_pFile)
      return 0;
    return CAddonLib::g_libKODI_Internal->ReadFile(m_pFile, lpBuf, uiBufSize);
  }

  inline bool CAddonLib_VFSFile::ReadLine(std::string &strLine)
  {
    strLine.clear();
    if (!m_pFile)
      return false;
    // TODO: Read 1024 chars into buffer. If file position advanced that many
    // chars, we didn't hit a newline. Otherwise, if file position is 1 or 2
    // past the number of bytes read, we read (and skipped) a newline sequence.
    char buffer[1025];
    if (CAddonLib::g_libKODI_Internal->ReadFileString(m_pFile, buffer, sizeof(buffer))) // will read 1024 bytes
    {
      strLine = buffer;
      return !strLine.empty();
    }
    return false;
  }

  inline ssize_t CAddonLib_VFSFile::Write(const void* lpBuf, size_t uiBufSize)
  {
    if (!m_pFile)
      return 0;
    return CAddonLib::g_libKODI_Internal->WriteFile(m_pFile, lpBuf, uiBufSize);
  }

  inline void CAddonLib_VFSFile::Flush()
  {
    if (!m_pFile)
      return;
     CAddonLib::g_libKODI_Internal->FlushFile(m_pFile);
  }

  inline int64_t CAddonLib_VFSFile::Seek(int64_t iFilePosition, int iWhence)
  {
    if (!m_pFile)
      return 0;
    return CAddonLib::g_libKODI_Internal->SeekFile(m_pFile, iFilePosition, iWhence);
  }

  inline int CAddonLib_VFSFile::Truncate(int64_t iSize)
  {
    if (!m_pFile)
      return -1;
    return CAddonLib::g_libKODI_Internal->TruncateFile(m_pFile, iSize);
  }

  inline int64_t CAddonLib_VFSFile::GetPosition()
  {
    if (!m_pFile)
      return -1;
    return CAddonLib::g_libKODI_Internal->GetFilePosition(m_pFile);
  }

  inline int64_t CAddonLib_VFSFile::GetLength()
  {
    if (!m_pFile)
      return 0;
    return CAddonLib::g_libKODI_Internal->GetFileLength(m_pFile);
  }

  inline void CAddonLib_VFSFile::Close()
  {
    if (!m_pFile)
      return;
    CAddonLib::g_libKODI_Internal->CloseFile(m_pFile);
    m_pFile = nullptr;
  }

  inline int CAddonLib_VFSFile::GetChunkSize()
  {
    if (!m_pFile)
      return 0;
    return CAddonLib::g_libKODI_Internal->GetFileChunkSize(m_pFile);
  }

  /*\___________________________________________________________________________
  \*/

  inline bool CAddonLib_File::FileExists(const std::string& strFileName, bool bUseCache)
  {
    return CAddonLib::g_libKODI_Internal->FileExists(strFileName, bUseCache);
  }

  inline int CAddonLib_File::StatFile(const std::string& strFileName, struct __stat64* buffer)
  {
    return CAddonLib::g_libKODI_Internal->StatFile(strFileName, buffer);
  }

  inline bool CAddonLib_File::DeleteFile(const std::string& strFileName)
  {
    return CAddonLib::g_libKODI_Internal->DeleteFile(strFileName);
  }

  inline std::string CAddonLib_File::GetFileMD5(const std::string& strPath)
  {
    return CAddonLib::g_libKODI_Internal->GetFileMD5(strPath);
  }

  inline std::string CAddonLib_File::GetCacheThumbName(const std::string& strFileName)
  {
    return CAddonLib::g_libKODI_Internal->GetCacheThumbName(strFileName);
  }

  inline unsigned int CAddonLib_File::GetChunkSize(unsigned int chunk, unsigned int minimum)
  {
    if (chunk)
      return chunk * ((minimum + chunk - 1) / chunk);
    else
      return minimum;
  }

}; /* namespace V2 */
}; /* namespace AddOnLIB */
