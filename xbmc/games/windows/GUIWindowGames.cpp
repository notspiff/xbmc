/*
 *      Copyright (C) 2012-2016 Team Kodi
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
 *  along with this Program; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "GUIWindowGames.h"
#include "addons/GUIDialogAddonInfo.h"
#include "Application.h"
#include "dialogs/GUIDialogContextMenu.h"
#include "dialogs/GUIDialogMediaSource.h"
#include "dialogs/GUIDialogProgress.h"
#include "FileItem.h"
#include "games/tags/GameInfoTag.h"
#include "games/addons/GameClient.h"
#include "games/addons/savestates/SavestateDatabase.h"
#include "guilib/GUIWindowManager.h"
#include "guilib/WindowIDs.h"
#include "GUIPassword.h"
#include "input/Key.h"
#include "settings/MediaSourceSettings.h"
#include "settings/Settings.h"
#include "URL.h"
#include "Util.h"
#include "utils/StringUtils.h"

#include <algorithm>

using namespace GAME;

CGUIWindowGames::CGUIWindowGames() :
  CGUIMediaWindow(WINDOW_GAMES, "MyGames.xml"),
  m_dlgProgress(nullptr)
{
}

bool CGUIWindowGames::OnMessage(CGUIMessage& message)
{
  switch (message.GetMessage())
  {
    case GUI_MSG_WINDOW_INIT:
    {
      m_rootDir.AllowNonLocalSources(true); // TODO

      // Is this the first time the window is opened?
      if (m_vecItems->GetPath() == "?" && message.GetStringParam().empty())
        message.SetStringParam(CMediaSourceSettings::GetInstance().GetDefaultSource("games"));

      // TODO
      m_dlgProgress = dynamic_cast<CGUIDialogProgress*>(g_windowManager.GetWindow(WINDOW_DIALOG_PROGRESS));

      break;
    }
    case GUI_MSG_CLICKED:
    {
      if (OnClickMsg(message.GetSenderId(), message.GetParam1()))
        return true;
      break;
    }
    default:
      break;
  }
  return CGUIMediaWindow::OnMessage(message);
}

bool CGUIWindowGames::OnClickMsg(int controlId, int actionId)
{
  if (!m_viewControl.HasControl(controlId))  // list/thumb control
    return false;

  const int iItem = m_viewControl.GetSelectedItem();

  CFileItemPtr pItem = m_vecItems->Get(iItem);
  if (!pItem)
    return false;

  switch (actionId)
  {
  case ACTION_DELETE_ITEM:
  {
    // Is delete allowed?
    if (CSettings::GetInstance().GetBool(CSettings::SETTING_FILELISTS_ALLOWFILEDELETION))
    {
      OnDeleteItem(iItem);
      return true;
    }
    break;
  }
  case ACTION_PLAYER_PLAY:
  {
    if (OnClick(iItem))
      return true;
    break;
  }
  case ACTION_SHOW_INFO:
  {
    if (!m_vecItems->IsPlugin())
    {
      if (pItem->HasAddonInfo())
      {
        CGUIDialogAddonInfo::ShowForItem(pItem);
        return true;
      }
    }
    break;
  }
  default:
    break;
  }

  return false;
}

void CGUIWindowGames::SetupShares()
{
  CGUIMediaWindow::SetupShares();
  // XBMC downloads a list of supported extensions from the remote add-ons
  // repo. Zip files are treated as directories and scanned recursively; if
  // they don't contain valid extensions (such as MAME arcade games), the
  // entire zip will be missing from the MyGames window. Skipping the recursive
  // scan always shows zip files (note: entering the zip will show an empty
  // folder) and speeds up directory listing as a nice side effect.
  //m_rootDir.SetFlags(XFILE::DIR_FLAG_NO_FILE_DIRS);
}

bool CGUIWindowGames::OnClick(int iItem, const std::string &player /* = "" */)
{
  CFileItemPtr item = m_vecItems->Get(iItem);
  if (item && !item->m_bIsFolder)
  {
    PlayGame(*item);
    return true;
  }

  return CGUIMediaWindow::OnClick(iItem);
}

void CGUIWindowGames::GetContextButtons(int itemNumber, CContextButtons &buttons)
{
  CFileItemPtr item = m_vecItems->Get(itemNumber);

  if (item && !item->GetProperty("pluginreplacecontextitems").asBoolean())
  {
    if (m_vecItems->IsSourcesPath())
    {
      // Context buttons for a sources path, like "Add source", "Remove Source", etc.
      CGUIDialogContextMenu::GetContextButtons("games", item, buttons);
    }
    else if (m_vecItems->IsVirtualDirectoryRoot() || m_vecItems->GetPath() == "sources://games/")
    {
      CGUIDialogContextMenu::GetContextButtons("games", item, buttons);
    }
    else
    {
      if (item->IsGame())
      {
        buttons.Add(CONTEXT_BUTTON_PLAY_ITEM, 208); // Play

        bool bHasSavestates = false;

        CSavestateDatabase db;
        if (db.Open())
        {
          CFileItemList items;
          if (db.GetSavestatesNav(items, item->GetPath()))
            bHasSavestates = items.Size() > 0;
        }

        if (bHasSavestates)
          buttons.Add(CONTEXT_BUTTON_MANAGE_SAVESTATES, 35273); // Manage saves
      }

      if (!m_vecItems->IsPlugin() && item->HasAddonInfo())
        buttons.Add(CONTEXT_BUTTON_INFO, 24003); // Add-on information

      if (CSettings::GetInstance().GetBool("filelists.allowfiledeletion") && !item->IsReadOnly())
      {
        buttons.Add(CONTEXT_BUTTON_DELETE, 117);
        buttons.Add(CONTEXT_BUTTON_RENAME, 118);
      }
    }
  }

  CGUIMediaWindow::GetContextButtons(itemNumber, buttons);
}

bool CGUIWindowGames::OnContextButton(int itemNumber, CONTEXT_BUTTON button)
{
  CFileItemPtr item = m_vecItems->Get(itemNumber);
  if (item)
  {
    if (m_vecItems->IsSourcesPath())
    {
      if (CGUIDialogContextMenu::OnContextButton("games", item, button))
      {
        Update("sources://games/");
        return true;
      }
    }
    switch (button)
    {
    case CONTEXT_BUTTON_PLAY_ITEM:
      PlayGame(*item);
      return true;
    case CONTEXT_BUTTON_INFO:
      CGUIDialogAddonInfo::ShowForItem(item);
      return true;
    case CONTEXT_BUTTON_DELETE:
      OnDeleteItem(itemNumber);
      return true;
    case CONTEXT_BUTTON_RENAME:
      OnRenameItem(itemNumber);
      return true;
    case CONTEXT_BUTTON_MANAGE_SAVESTATES:
      g_windowManager.ActivateWindow(WINDOW_DIALOG_SAVESTATES, item->GetPath());
      return true;
    default:
      break;
    }
  }
  return CGUIMediaWindow::OnContextButton(itemNumber, button);
}

bool CGUIWindowGames::OnAddMediaSource()
{
  return CGUIDialogMediaSource::ShowAndAddMediaSource("games");
}

bool CGUIWindowGames::GetDirectory(const std::string &strDirectory, CFileItemList& items)
{
  if (!CGUIMediaWindow::GetDirectory(strDirectory, items))
    return false;

  // Set label
  std::string label;
  if (items.GetLabel().empty())
    m_rootDir.IsSource(items.GetPath(), CMediaSourceSettings::GetInstance().GetSources("games"), &label);

  if (!label.empty())
    items.SetLabel(label);

  // Set content
  std::string content;
  if (items.GetContent().empty())
  {
    if (!items.IsVirtualDirectoryRoot() && // Don't set content for root directory
        !items.IsPlugin())                 // Don't set content for plugins
    {
      content = "games";
    }
  }

  if (!content.empty())
    items.SetContent(content);

  return true;
}

std::string CGUIWindowGames::GetStartFolder(const std::string &dir)
{
  // From CGUIWindowPictures::GetStartFolder()

  if (StringUtils::EqualsNoCase(dir, "plugins") ||
      StringUtils::EqualsNoCase(dir, "addons"))
  {
    return "addons://sources/game/";
  }

  SetupShares();
  VECSOURCES shares;
  m_rootDir.GetSources(shares);
  bool bIsSourceName = false;
  int iIndex = CUtil::GetMatchingSource(dir, shares, bIsSourceName);
  if (iIndex >= 0)
  {
    if (iIndex < (int)shares.size() && shares[iIndex].m_iHasLock == 2)
    {
      CFileItem item(shares[iIndex]);
      if (!g_passwordManager.IsItemUnlocked(&item, "games"))
        return "";
    }
    if (bIsSourceName)
      return shares[iIndex].strPath;
    return dir;
  }
  return CGUIMediaWindow::GetStartFolder(dir);
}

void CGUIWindowGames::OnItemInfo(int itemNumber)
{
  CFileItemPtr item = m_vecItems->Get(itemNumber);
  if (!item)
    return;

  if (!m_vecItems->IsPlugin())
  {
    if (item->IsPlugin() || item->IsScript())
      CGUIDialogAddonInfo::ShowForItem(item);
  }

  /* TODO
  CGUIDialogGameInfo* gameInfo = dynamic_cast<CGUIDialogGameInfo*>(g_windowManager.GetWindow(WINDOW_DIALOG_PICTURE_INFO));
  if (gameInfo)
  {
    gameInfo->SetGame(item);
    gameInfo->Open();
  }
  */
}

bool CGUIWindowGames::PlayGame(const CFileItem &item)
{
  return g_application.PlayFile(item, "") == PLAYBACK_OK;
}