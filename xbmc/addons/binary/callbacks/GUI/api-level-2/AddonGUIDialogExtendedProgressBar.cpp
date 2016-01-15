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
#include "dialogs/GUIDialogExtendedProgressBar.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

#include "AddonCallbacksGUI.h"
#include "AddonGUIDialogExtendedProgressBar.h"

using namespace ADDON;

namespace GUILIB
{
namespace V2
{
extern "C"
{

void CAddonGUI_Dialog_ExtendedProgress::Init(CB_GUILib *callbacks)
{
  callbacks->Dialogs.ExtendedProgress.New            = CAddonGUI_Dialog_ExtendedProgress::New;
  callbacks->Dialogs.ExtendedProgress.Delete         = CAddonGUI_Dialog_ExtendedProgress::Delete;
  callbacks->Dialogs.ExtendedProgress.Title          = CAddonGUI_Dialog_ExtendedProgress::Title;
  callbacks->Dialogs.ExtendedProgress.SetTitle       = CAddonGUI_Dialog_ExtendedProgress::SetTitle;
  callbacks->Dialogs.ExtendedProgress.Text           = CAddonGUI_Dialog_ExtendedProgress::Text;
  callbacks->Dialogs.ExtendedProgress.SetText        = CAddonGUI_Dialog_ExtendedProgress::SetText;
  callbacks->Dialogs.ExtendedProgress.IsFinished     = CAddonGUI_Dialog_ExtendedProgress::IsFinished;
  callbacks->Dialogs.ExtendedProgress.MarkFinished   = CAddonGUI_Dialog_ExtendedProgress::MarkFinished;
  callbacks->Dialogs.ExtendedProgress.Percentage     = CAddonGUI_Dialog_ExtendedProgress::Percentage;
  callbacks->Dialogs.ExtendedProgress.SetPercentage  = CAddonGUI_Dialog_ExtendedProgress::SetPercentage;
  callbacks->Dialogs.ExtendedProgress.SetProgress    = CAddonGUI_Dialog_ExtendedProgress::SetProgress;
}

GUIHANDLE CAddonGUI_Dialog_ExtendedProgress::New(void *addonData, const char *title)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper || !title)
      throw ADDON::WrongValueException("CAddonGUI_Dialog_ExtendedProgress - %s - invalid add-on data", __FUNCTION__);

    // setup the progress dialog
    CGUIDialogExtendedProgressBar* pDlgProgress = dynamic_cast<CGUIDialogExtendedProgressBar *>(g_windowManager.GetWindow(WINDOW_DIALOG_EXT_PROGRESS));
    CGUIDialogProgressBarHandle* dlgProgressHandle = pDlgProgress->GetHandle(title);
    return dlgProgressHandle;
  }
  HANDLE_ADDON_EXCEPTION

  return nullptr;
}

void CAddonGUI_Dialog_ExtendedProgress::Delete(void *addonData, GUIHANDLE handle)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper)
      throw ADDON::WrongValueException("CAddonGUI_Dialog_ExtendedProgress - %s - invalid add-on data", __FUNCTION__);

    if (!handle)
    {
      CAddonCallbacksGUI* guiHelper = static_cast<GUILIB::V2::CAddonCallbacksGUI*>(helper->GUILib_GetHelper());
      throw ADDON::WrongValueException("CAddonGUI_Dialog_ExtendedProgress - %s: %s/%s - No Dialog with invalid handler data",
                                         __FUNCTION__,
                                         TranslateType(guiHelper->GetAddon()->Type()).c_str(),
                                         guiHelper->GetAddon()->Name().c_str());
    }

    CGUIDialogProgressBarHandle* dlgProgressHandle = static_cast<CGUIDialogProgressBarHandle *>(handle);
    dlgProgressHandle->MarkFinished();
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Dialog_ExtendedProgress::Title(void *addonData, GUIHANDLE handle, char &title, unsigned int &iMaxStringSize)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper)
      throw ADDON::WrongValueException("CAddonGUI_Dialog_ExtendedProgress - %s - invalid add-on data", __FUNCTION__);

    if (!handle)
    {
      CAddonCallbacksGUI* guiHelper = static_cast<GUILIB::V2::CAddonCallbacksGUI*>(helper->GUILib_GetHelper());
      throw ADDON::WrongValueException("CAddonGUI_Dialog_ExtendedProgress - %s: %s/%s - No Dialog with invalid handler data",
                                         __FUNCTION__,
                                         TranslateType(guiHelper->GetAddon()->Type()).c_str(),
                                         guiHelper->GetAddon()->Name().c_str());
    }

    CGUIDialogProgressBarHandle* dlgProgressHandle = static_cast<CGUIDialogProgressBarHandle *>(handle);
    strncpy(&title, dlgProgressHandle->Title().c_str(), iMaxStringSize);
    iMaxStringSize = dlgProgressHandle->Title().length();
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Dialog_ExtendedProgress::SetTitle(void *addonData, GUIHANDLE handle, const char *title)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper)
      throw ADDON::WrongValueException("CAddonGUI_Dialog_ExtendedProgress - %s - invalid add-on data", __FUNCTION__);

    if (!handle || !title)
    {
      CAddonCallbacksGUI* guiHelper = static_cast<GUILIB::V2::CAddonCallbacksGUI*>(helper->GUILib_GetHelper());
      throw ADDON::WrongValueException("CAddonGUI_Dialog_ExtendedProgress - %s: %s/%s - No Dialog with invalid handler data",
                                         __FUNCTION__,
                                         TranslateType(guiHelper->GetAddon()->Type()).c_str(),
                                         guiHelper->GetAddon()->Name().c_str());
    }

    CGUIDialogProgressBarHandle* dlgProgressHandle = static_cast<CGUIDialogProgressBarHandle *>(handle);
    dlgProgressHandle->SetTitle(title);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Dialog_ExtendedProgress::Text(void *addonData, GUIHANDLE handle, char &text, unsigned int &iMaxStringSize)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper)
      throw ADDON::WrongValueException("CAddonGUI_Dialog_ExtendedProgress - %s - invalid add-on data", __FUNCTION__);

    if (!handle)
    {
      CAddonCallbacksGUI* guiHelper = static_cast<GUILIB::V2::CAddonCallbacksGUI*>(helper->GUILib_GetHelper());
      throw ADDON::WrongValueException("CAddonGUI_Dialog_ExtendedProgress - %s: %s/%s - No Dialog with invalid handler data",
                                         __FUNCTION__,
                                         TranslateType(guiHelper->GetAddon()->Type()).c_str(),
                                         guiHelper->GetAddon()->Name().c_str());
    }

    CGUIDialogProgressBarHandle* dlgProgressHandle = static_cast<CGUIDialogProgressBarHandle *>(handle);
    strncpy(&text, dlgProgressHandle->Text().c_str(), iMaxStringSize);
    iMaxStringSize = dlgProgressHandle->Text().length();
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Dialog_ExtendedProgress::SetText(void *addonData, GUIHANDLE handle, const char *text)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper)
      throw ADDON::WrongValueException("CAddonGUI_Dialog_ExtendedProgress - %s - invalid add-on data", __FUNCTION__);

    if (!handle || !text)
    {
      CAddonCallbacksGUI* guiHelper = static_cast<GUILIB::V2::CAddonCallbacksGUI*>(helper->GUILib_GetHelper());
      throw ADDON::WrongValueException("CAddonGUI_Dialog_ExtendedProgress - %s: %s/%s - No Dialog with invalid handler data",
                                         __FUNCTION__,
                                         TranslateType(guiHelper->GetAddon()->Type()).c_str(),
                                         guiHelper->GetAddon()->Name().c_str());
    }

    CGUIDialogProgressBarHandle* dlgProgressHandle = static_cast<CGUIDialogProgressBarHandle *>(handle);
    dlgProgressHandle->SetText(text);
  }
  HANDLE_ADDON_EXCEPTION
}

bool CAddonGUI_Dialog_ExtendedProgress::IsFinished(void *addonData, GUIHANDLE handle)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper)
      throw ADDON::WrongValueException("CAddonGUI_Dialog_ExtendedProgress - %s - invalid add-on data", __FUNCTION__);

    if (!handle)
    {
      CAddonCallbacksGUI* guiHelper = static_cast<GUILIB::V2::CAddonCallbacksGUI*>(helper->GUILib_GetHelper());
      throw ADDON::WrongValueException("CAddonGUI_Dialog_ExtendedProgress - %s: %s/%s - No Dialog with invalid handler data",
                                         __FUNCTION__,
                                         TranslateType(guiHelper->GetAddon()->Type()).c_str(),
                                         guiHelper->GetAddon()->Name().c_str());
    }

    CGUIDialogProgressBarHandle* dlgProgressHandle = static_cast<CGUIDialogProgressBarHandle *>(handle);
    return dlgProgressHandle->IsFinished();
  }
  HANDLE_ADDON_EXCEPTION

  return false;
}

void CAddonGUI_Dialog_ExtendedProgress::MarkFinished(void *addonData, GUIHANDLE handle)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper)
      throw ADDON::WrongValueException("CAddonGUI_Dialog_ExtendedProgress - %s - invalid add-on data", __FUNCTION__);

    if (!handle)
    {
      CAddonCallbacksGUI* guiHelper = static_cast<GUILIB::V2::CAddonCallbacksGUI*>(helper->GUILib_GetHelper());
      throw ADDON::WrongValueException("CAddonGUI_Dialog_ExtendedProgress - %s: %s/%s - No Dialog with invalid handler data",
                                         __FUNCTION__,
                                         TranslateType(guiHelper->GetAddon()->Type()).c_str(),
                                         guiHelper->GetAddon()->Name().c_str());
    }

    CGUIDialogProgressBarHandle* dlgProgressHandle = static_cast<CGUIDialogProgressBarHandle *>(handle);
    dlgProgressHandle->MarkFinished();
  }
  HANDLE_ADDON_EXCEPTION
}

float CAddonGUI_Dialog_ExtendedProgress::Percentage(void *addonData, GUIHANDLE handle)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper)
      throw ADDON::WrongValueException("CAddonGUI_Dialog_ExtendedProgress - %s - invalid add-on data", __FUNCTION__);

    if (!handle)
    {
      CAddonCallbacksGUI* guiHelper = static_cast<GUILIB::V2::CAddonCallbacksGUI*>(helper->GUILib_GetHelper());
      throw ADDON::WrongValueException("CAddonGUI_Dialog_ExtendedProgress - %s: %s/%s - No Dialog with invalid handler data",
                                         __FUNCTION__,
                                         TranslateType(guiHelper->GetAddon()->Type()).c_str(),
                                         guiHelper->GetAddon()->Name().c_str());
    }

    CGUIDialogProgressBarHandle* dlgProgressHandle = static_cast<CGUIDialogProgressBarHandle *>(handle);
    return dlgProgressHandle->Percentage();
  }
  HANDLE_ADDON_EXCEPTION

  return 0.0f;
}

void CAddonGUI_Dialog_ExtendedProgress::SetPercentage(void *addonData, GUIHANDLE handle, float fPercentage)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper)
      throw ADDON::WrongValueException("CAddonGUI_Dialog_ExtendedProgress - %s - invalid add-on data", __FUNCTION__);

    if (!handle)
    {
      CAddonCallbacksGUI* guiHelper = static_cast<GUILIB::V2::CAddonCallbacksGUI*>(helper->GUILib_GetHelper());
      throw ADDON::WrongValueException("CAddonGUI_Dialog_ExtendedProgress - %s: %s/%s - No Dialog with invalid handler data",
                                         __FUNCTION__,
                                         TranslateType(guiHelper->GetAddon()->Type()).c_str(),
                                         guiHelper->GetAddon()->Name().c_str());
    }

    CGUIDialogProgressBarHandle* dlgProgressHandle = static_cast<CGUIDialogProgressBarHandle *>(handle);
    dlgProgressHandle->SetPercentage(fPercentage);
  }
  HANDLE_ADDON_EXCEPTION
}

void CAddonGUI_Dialog_ExtendedProgress::SetProgress(void *addonData, GUIHANDLE handle, int currentItem, int itemCount)
{
  try
  {
    CAddonCallbacks* helper = static_cast<CAddonCallbacks *>(addonData);
    if (!helper)
      throw ADDON::WrongValueException("CAddonGUI_Dialog_ExtendedProgress - %s - invalid add-on data", __FUNCTION__);

    if (!handle)
    {
      CAddonCallbacksGUI* guiHelper = static_cast<GUILIB::V2::CAddonCallbacksGUI*>(helper->GUILib_GetHelper());
      throw ADDON::WrongValueException("CAddonGUI_Dialog_ExtendedProgress - %s: %s/%s - No Dialog with invalid handler data",
                                         __FUNCTION__,
                                         TranslateType(guiHelper->GetAddon()->Type()).c_str(),
                                         guiHelper->GetAddon()->Name().c_str());
    }

    CGUIDialogProgressBarHandle* dlgProgressHandle = static_cast<CGUIDialogProgressBarHandle *>(handle);
    dlgProgressHandle->SetProgress(currentItem, itemCount);
  }
  HANDLE_ADDON_EXCEPTION
}

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
