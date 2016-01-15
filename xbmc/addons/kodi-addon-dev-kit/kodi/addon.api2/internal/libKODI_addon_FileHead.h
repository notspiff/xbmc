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

typedef void*   _open_file(void* hdl, const char* strFileName, unsigned int flags);
typedef void*   _open_file_for_write(void* hdl, const char* strFileName, bool bOverWrite);
typedef ssize_t _read_file(void* hdl, void* file, void* lpBuf, size_t uiBufSize);
typedef bool    _read_file_string(void* hdl, void* file, char *szLine, int iLineLength);
typedef ssize_t _write_file(void* hdl, void* file, const void* lpBuf, size_t uiBufSize);
typedef void    _flush_file(void* hdl, void* file);
typedef int64_t _seek_file(void* hdl, void* file, int64_t iFilePosition, int iWhence);
typedef int     _truncate_file(void* hdl, void* file, int64_t iSize);
typedef int64_t _get_file_position(void* hdl, void* file);
typedef int64_t _get_file_length(void* hdl, void* file);
typedef void    _close_file(void* hdl, void* file);
typedef int     _get_file_chunk_size(void* hdl, void* file);
typedef bool    _file_exists(void* hdl, const char *strFileName, bool bUseCache);
typedef int     _stat_file(void* hdl, const char *strFileName, struct __stat64* buffer);
typedef bool    _delete_file(void* hdl, const char *strFileName);
typedef char*   _get_file_md5(void* hdl, const char* strFileName);
typedef char*   _get_cache_thumb_name(void* hdl, const char* strFileName);
typedef char*   _make_legal_filename(void* hdl, const char* strFileName);
typedef char*   _make_legal_path(void* hdl, const char* strPath);

typedef struct CB_AddonLib_File
{
  _open_file*                     open_file;
  _open_file_for_write*           open_file_for_write;
  _read_file*                     read_file;
  _read_file_string*              read_file_string;
  _write_file*                    write_file;
  _flush_file*                    flush_file;
  _seek_file*                     seek_file;
  _truncate_file*                 truncate_file;
  _get_file_position*             get_file_position;
  _get_file_length*               get_file_length;
  _close_file*                    close_file;
  _get_file_chunk_size*           get_file_chunk_size;
  _file_exists*                   file_exists;
  _stat_file*                     stat_file;
  _delete_file*                   delete_file;
  _get_file_md5*                  get_file_md5;
  _get_cache_thumb_name*          get_cache_thumb_name;
  _make_legal_filename*           make_legal_filename;
  _make_legal_path*               make_legal_path;
} CB_AddonLib_File;

#define IMPL_FILE                                                              \
  private:                                                                     \
    void*         m_pFile;                                                     \
    void*         m_Handle;                                                    \
    CB_AddOnLib*  m_Callbacks;

}; /* namespace V2 */
}; /* namespace AddOnLIB */
