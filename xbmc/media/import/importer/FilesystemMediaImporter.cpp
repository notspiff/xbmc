/*
 *      Copyright (C) 2015 Team XBMC
 *      http://xbmc.org
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
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "FilesystemMediaImporter.h"
#include "URL.h"
#include "Util.h"
#include "filesystem/Directory.h"
#include "filesystem/File.h"
#include "media/import/task/MediaImportRetrievalTask.h"
#include "settings/AdvancedSettings.h"
#include "utils/log.h"
#include "utils/URIUtils.h"

static bool IsExcluded(const std::string& directory)
{
  std::string noMediaFile = URIUtils::AddFileToFolder(directory, ".nomedia");
  return XFILE::CFile::Exists(noMediaFile);
}

CFilesystemMediaImporter::CFilesystemMediaImporter()
  : IMediaImporter(CMediaImport("", { MediaTypeNone }))
{ }

CFilesystemMediaImporter::CFilesystemMediaImporter(const CMediaImport &import)
  : IMediaImporter(import)
{
  // TODO
}

CFilesystemMediaImporter::~CFilesystemMediaImporter()
{ }

bool CFilesystemMediaImporter::CanImport(const std::string& path) const
{
  // can't import non-existing directories
  if (path.empty() || !XFILE::CDirectory::Exists(path))
    return false;

  // TODO: find a better way to exclude UPnP
  if (URIUtils::IsUPnP(path))
    return false;

  return true;
}

IMediaImporter* CFilesystemMediaImporter::Create(const CMediaImport &import) const
{
  if (!CanImport(import.GetPath()))
    return NULL;

  return new CFilesystemMediaImporter(import);
}

bool CFilesystemMediaImporter::Import(CMediaImportRetrievalTask* task) const
{
  if (task == NULL)
    return false;

  const auto& import = GetImport();
  const auto& path = import.GetPath();

  bool containsEpisodes = std::find(import.GetMediaTypes().cbegin(), import.GetMediaTypes().cend(), MediaTypeEpisode) != import.GetMediaTypes().cend();

  // exclude folders that match our exclude regexps
  const auto& excludeRegExps = containsEpisodes ? g_advancedSettings.m_tvshowExcludeFromScanRegExps : g_advancedSettings.m_moviesExcludeFromScanRegExps;
  if (CUtil::ExcludeFileOrFolder(import.GetPath(), excludeRegExps))
    return false;

  // check if the directory should be excluded
  if (IsExcluded(path))
  {
    CLog::Log(LOGWARNING, "CFilesystemMediaImporter: skipping item '%s' with '.nomedia' file in parent directory, it won't be added to the library.", CURL::GetRedacted(path).c_str());
    return false;
  }

  // TODO

  for (const auto& importedMediaType : import.GetMediaTypes())
  {
    if (task->ShouldCancel(0, 1))
      return false;

    // TODO
  }

  // TODO

  return true;
}
