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
#include "dialogs/GUIDialogSelect.h"
#include "guilib/GUIWindowManager.h"
#include "utils/Variant.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIDialogSelect.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{
extern "C"
{

void CAddonGUI_Dialog_Select::Init(CB_GUILib *callbacks)
{
  callbacks->Dialogs.Select.Open = CAddonGUI_Dialog_Select::Open;
}

int CAddonGUI_Dialog_Select::Open(const char *heading, const char *entries[], unsigned int size, int selected)
{
  try
  {
    CGUIDialogSelect* pDialog = (CGUIDialogSelect*)g_windowManager.GetWindow(WINDOW_DIALOG_SELECT);
    pDialog->Reset();
    pDialog->SetHeading(CVariant{heading});

    for (unsigned int i = 0; i < size; ++i)
      pDialog->Add(entries[i]);

    if (selected > 0)
      pDialog->SetSelected(selected);

    pDialog->Open();
    return pDialog->GetSelectedItem();
  }
  HANDLE_ADDON_EXCEPTION

  return -1;
}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
