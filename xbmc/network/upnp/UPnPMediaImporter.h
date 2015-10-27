#pragma once
/*
 *      Copyright (C) 2013 Team XBMC
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
#include "PltDeviceData.h"

class CUPnPMediaImporter : public IMediaImporter
{
public:
  CUPnPMediaImporter();
  virtual ~CUPnPMediaImporter();

  // implementation of IMediaImporter
  virtual const char* GetIdentification() const override { return "UPnPMediaImporter"; }

  virtual bool CanImport(const std::string &path) const override;
  virtual bool CanUpdateMetadataOnSource(const std::string &path) const override { return false; }
  virtual bool CanUpdatePlaycountOnSource(const std::string &path) const override;
  virtual bool CanUpdateLastPlayedOnSource(const std::string &path) const override;
  virtual bool CanUpdateResumePositionOnSource(const std::string &path) const override;

  virtual IMediaImporter* Create(const CMediaImport &import) const override;
  virtual bool Import(CMediaImportRetrievalTask *task) const override;
  virtual bool UpdateOnSource(CMediaImportUpdateTask* task) const override;

protected:
  CUPnPMediaImporter(const CMediaImport &import);

  static bool validatePath(const std::string &path, PLT_DeviceDataReference &device);
  static bool isXbmcServer(const std::string &path);

  std::string m_deviceUUID;
};
