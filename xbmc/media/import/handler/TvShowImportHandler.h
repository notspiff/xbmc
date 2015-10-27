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

#include "media/import/handler/VideoImportHandler.h"

class CTvShowImportHandler : public CVideoImportHandler
{
public:
  CTvShowImportHandler(const IMediaImportHandlerManager* importHandlerManager)
    : CVideoImportHandler(importHandlerManager)
  { }
  virtual ~CTvShowImportHandler() { }

  virtual CTvShowImportHandler* Create() const override { return new CTvShowImportHandler(m_importHandlerManager); }

  virtual MediaType GetMediaType() const override { return MediaTypeTvShow; }
  virtual MediaTypes GetRequiredMediaTypes() const override;
  virtual GroupedMediaTypes GetGroupedMediaTypes() const override;

  virtual bool AddImportedItem(const CMediaImport &import, CFileItem* item) override;
  virtual bool UpdateImportedItem(const CMediaImport &import, CFileItem* item) override;
  virtual bool RemoveImportedItem(const CMediaImport &import, const CFileItem* item) override;
  virtual bool CleanupImportedItems(const CMediaImport &import) override;

  virtual void SetImportedItemsEnabled(const CMediaImport &import, bool enable) override { }

protected:
  virtual bool GetLocalItems(CVideoDatabase &videodb, const CMediaImport &import, std::vector<CFileItemPtr>& items) const override;

  virtual CFileItemPtr FindMatchingLocalItem(const CFileItem* item, std::vector<CFileItemPtr>& localItems) const override;
  virtual MediaImportChangesetType DetermineChangeset(const CMediaImport &import, CFileItem* item, CFileItemPtr localItem, std::vector<CFileItemPtr>& localItems, bool updatePlaybackMetadata) override;

  virtual bool RemoveImportedItems(CVideoDatabase &videodb, const CMediaImport &import) const override;
  virtual void RemoveImportedItem(CVideoDatabase &videodb, const CMediaImport &import, const CFileItem* item) const override;
};
