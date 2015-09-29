#pragma once
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

#include "media/import/IMediaImporter.h"

class CPluginMediaImporter : public IMediaImporter
{
public:
  CPluginMediaImporter();
  virtual ~CPluginMediaImporter();

  // implementation of IMediaImporter
  virtual const char* GetIdentification() const override { return "PluginMediaImporter"; }

  virtual bool CanImport(const std::string &path) const override;
  virtual bool CanUpdateMetadataOnSource(const std::string &path) const override { return false; }
  virtual bool CanUpdatePlaycountOnSource(const std::string &path) const override { return false; } // TODO: could be possible (e.g. Trakt)
  virtual bool CanUpdateLastPlayedOnSource(const std::string &path) const override { return false; } // TODO: could be possible (e.g. Trakt)
  virtual bool CanUpdateResumePositionOnSource(const std::string &path) const override { return false; }

  virtual IMediaImporter* Create(const CMediaImport &import) const override;
  virtual bool Import(CMediaImportRetrievalTask *task) const override;
  virtual bool UpdateOnSource(CMediaImportUpdateTask* task) const override { return false; } // TODO: could be possible (e.g. Trakt)

protected:
  CPluginMediaImporter(const CMediaImport& import);

  // TODO
};
