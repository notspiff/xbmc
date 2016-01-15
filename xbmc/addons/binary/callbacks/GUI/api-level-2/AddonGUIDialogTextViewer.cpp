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

#include "addons/Addon.h"
#include "addons/binary/ExceptionHandling.h"
#include "addons/binary/callbacks/AddonCallbacks.h"
#include "dialogs/GUIDialogTextViewer.h"
#include "guilib/GUIWindowManager.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIDialogTextViewer.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{
extern "C"
{

void CAddonGUI_Dialog_TextViewer::Init(CB_GUILib *callbacks)
{
  callbacks->Dialogs.TextViewer.Open = CAddonGUI_Dialog_TextViewer::Open;
}

void CAddonGUI_Dialog_TextViewer::Open(const char *heading, const char *text)
{
  try
  {
    CGUIDialogTextViewer* pDialog = dynamic_cast<CGUIDialogTextViewer *>(g_windowManager.GetWindow(WINDOW_DIALOG_TEXT_VIEWER));
    pDialog->SetHeading(heading);
    pDialog->SetText(text);
    pDialog->Open();
  }
  HANDLE_ADDON_EXCEPTION
}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
