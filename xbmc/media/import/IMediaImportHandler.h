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

#include <memory>

#include "media/MediaType.h"
#include "media/import/MediaImportChangesetTypes.h"

class CFileItem;
typedef std::shared_ptr<CFileItem> CFileItemPtr;

class CMediaImport;
class IMediaImportHandlerManager;

/*!
 * \brief Interface of a handler capable of handling imported media items of a
 * specific media type.
 */
class IMediaImportHandler
{
public:
  virtual ~IMediaImportHandler() { }

  virtual IMediaImportHandler* Create() const = 0;

  /*!
   * \brief Returns the media type the implementation is capable of handling.
   */
  virtual MediaType GetMediaType() const = 0;

  /*!
   * \brief Returns a list of media types which must be importable for
   * this implementation to be usable.
   */
  virtual MediaTypes GetRequiredMediaTypes() const { return MediaTypes(); }

  /*!
   * \brief Returns a list of media types which can be grouped together
   * with the media type of this implementation.
   */
  virtual GroupedMediaTypes GetGroupedMediaTypes() const { return GroupedMediaTypes(); }

  /*!
  * \brief Get the translated label representing the given item
  *
  * \param item Item to get the label for
  * \return Translated label representing the given item
  */
  virtual std::string GetItemLabel(const CFileItem* item) const = 0;

  /*!
  * \brief Gets a list of previously imported items from the given media import.
  *
  * \param import Place from where the given items were imported
  * \param items List of previously imported items from the given media import
  */
  virtual bool GetLocalItems(const CMediaImport &import, std::vector<CFileItemPtr>& items) const = 0;

  /*!
   * \brief Starts the task determining the changeset of the imported items against previously imported items.
   *
   * \param import Place from where the given items were imported
   * \return True if the preparations were successful, false otherwise
   */
  virtual bool StartChangeset(const CMediaImport &import) = 0;

  /*!
  * \brief Finishes the task determining the changeset of the imported items against previously imported items.
  *
  * \param import Place from where the given items were imported
  * \return True if the finalizations were successful, false otherwise
  */
  virtual bool FinishChangeset(const CMediaImport &import) = 0;

  /*!
  * \brief Determining the changeset of the imported item against the previously imported item.
  *
  * \param import Place from where the given items were imported
  * \param item Imported items
  * \param localItems Previously imported items
  * \return Type of the changeset of the two imported items
  */
  virtual MediaImportChangesetType DetermineChangeset(const CMediaImport &import, CFileItem* item, std::vector<CFileItemPtr>& localItems) = 0;

  /*!
  * \brief Starts the synchronisation process
  *
  * \param import Place from where the given items were imported
  * \return True if the preparations were successful, false otherwise
  */
  virtual bool StartSynchronisation(const CMediaImport &import) = 0;

  /*!
  * \brief Finishes the synchronisation process
  *
  * \param import Place from where the given items were imported
  * \return True if the finalizations were successful, false otherwise
  */
  virtual bool FinishSynchronisation(const CMediaImport &import) = 0;

  /*!
   * \brief Adds the given item from the given import to the library
   *
   * \param import Place from where the given items were imported
   * \param item Imported item to be added to the library
   * \return True if the item was successfully added, false otherwise
   */
  virtual bool AddImportedItem(const CMediaImport &import, CFileItem* item) = 0;

  /*!
   * \brief Updates the given item from the given import in the library
   *
   * \param import Place from where the given items were imported
   * \param item Imported item to be updated in the library
   * \return True if the item was successfully updated, false otherwise
   */
  virtual bool UpdateImportedItem(const CMediaImport &import, CFileItem* item) = 0;

  /*!
   * \brief Removes the given item from the given import from the library
   *
   * \param import Place from where the given items were imported
   * \param item Imported item to be removed from the library
   * \return True if the item was successfully removed, false otherwise
   */
  virtual bool RemoveImportedItem(const CMediaImport &import, const CFileItem* item) = 0;

  /*!
  * \brief Cleans up the imported items in the library
  *
  * \param import Place from where the given items were imported
  * \return True if the library was successfully cleaned up, false otherwise
  */
  virtual bool CleanupImportedItems(const CMediaImport &import) = 0;

  /*!
  * \brief Removes all imported items from the library
  *
  * \param import Place from where the given items were imported
  * \return True if the imported items were successfully removed from the library, false otherwise
  */
  virtual bool RemoveImportedItems(const CMediaImport &import) = 0;

  /*!
   * \brief Enable/disable imported items
   *
   * \param import Place from where the given items were imported
   * \param enable Whether to enable or disable imported items
   */
  virtual void SetImportedItemsEnabled(const CMediaImport &import, bool enable) = 0;

protected:
  IMediaImportHandler(const IMediaImportHandlerManager* importHandlerManager)
    : m_importHandlerManager(importHandlerManager)
  { }

  const IMediaImportHandlerManager* m_importHandlerManager;
};

typedef std::shared_ptr<IMediaImportHandler> MediaImportHandlerPtr;
typedef std::shared_ptr<const IMediaImportHandler> MediaImportHandlerConstPtr;
