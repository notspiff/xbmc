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

#include "PluginMediaImporter.h"

#include "media/import/MediaImport.h"
#include "media/import/task/MediaImportRetrievalTask.h"
#include "utils/URIUtils.h"

CPluginMediaImporter::CPluginMediaImporter()
  : IMediaImporter(CMediaImport("", { MediaTypeNone }))
{ }

CPluginMediaImporter::CPluginMediaImporter(const CMediaImport &import)
  : IMediaImporter(import)
{
  // TODO
}

CPluginMediaImporter::~CPluginMediaImporter()
{ }

bool CPluginMediaImporter::CanImport(const std::string& path) const
{
  // can't import non-plugin:// paths
  if (path.empty() || !URIUtils::IsPlugin(path))
    return false;

  return true;
}

IMediaImporter* CPluginMediaImporter::Create(const CMediaImport &import) const
{
  if (!CanImport(import.GetPath()))
    return NULL;

  return new CPluginMediaImporter(import);
}

bool CPluginMediaImporter::Import(CMediaImportRetrievalTask* task) const
{
  if (task == NULL)
    return false;

  const auto& import = GetImport();
  const auto& path = import.GetPath();

  // TODO

  return true;
}
