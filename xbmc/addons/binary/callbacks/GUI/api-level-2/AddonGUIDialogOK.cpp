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
#include "dialogs/GUIDialogOK.h"
#include "utils/Variant.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIDialogOK.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{
extern "C"
{

void CAddonGUI_Dialog_OK::Init(CB_GUILib *callbacks)
{
  callbacks->Dialogs.OK.ShowAndGetInputSingleText = CAddonGUI_Dialog_OK::ShowAndGetInputSingleText;
  callbacks->Dialogs.OK.ShowAndGetInputLineText   = CAddonGUI_Dialog_OK::ShowAndGetInputLineText;
}

void CAddonGUI_Dialog_OK::ShowAndGetInputSingleText(const char *heading, const char *text)
{
  try
  {
    CGUIDialogOK::ShowAndGetInput(CVariant{heading}, CVariant{text});
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Dialog_OK::ShowAndGetInputLineText(const char *heading, const char *line0, const char *line1, const char *line2)
{
  try
  {
    CGUIDialogOK::ShowAndGetInput(CVariant{heading}, CVariant{line0}, CVariant{line1}, CVariant{line2});
  }
  HANDLE_ADDON_EXCEPTION
}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
