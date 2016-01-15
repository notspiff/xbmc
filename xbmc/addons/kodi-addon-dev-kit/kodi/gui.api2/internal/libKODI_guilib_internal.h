#pragma once
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

#include <memory>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <vector>

#ifdef ADDON_ACTION_PREVIOUS_MENU
#undef ADDON_ACTION_PREVIOUS_MENU
#endif
#ifdef ADDON_ACTION_CLOSE_DIALOG
#undef ADDON_ACTION_CLOSE_DIALOG
#endif
#ifdef ADDON_ACTION_NAV_BACK
#undef ADDON_ACTION_NAV_BACK
#endif

#include "kodi/addon.api2/AddonLib.h"

#include "../definations.h"
#include "libKODI_guilib_ControlButtonHead.h"
#include "libKODI_guilib_ControlEditHead.h"
#include "libKODI_guilib_ControlFadeLabelHead.h"
#include "libKODI_guilib_ControlImageHead.h"
#include "libKODI_guilib_ControlLabelHead.h"
#include "libKODI_guilib_ControlProgressHead.h"
#include "libKODI_guilib_ControlRadioButtonHead.h"
#include "libKODI_guilib_ControlRenderingHead.h"
#include "libKODI_guilib_ControlSettingsSliderHead.h"
#include "libKODI_guilib_ControlSliderHead.h"
#include "libKODI_guilib_ControlSpinHead.h"
#include "libKODI_guilib_ControlTextBoxHead.h"
#include "libKODI_guilib_DialogExtendedProgressHead.h"
#include "libKODI_guilib_DialogFileBrowserHead.h"
#include "libKODI_guilib_DialogKeyboardHead.h"
#include "libKODI_guilib_DialogNumericHead.h"
#include "libKODI_guilib_DialogOKHead.h"
#include "libKODI_guilib_DialogProgressHead.h"
#include "libKODI_guilib_DialogSelectHead.h"
#include "libKODI_guilib_DialogTextViewerHead.h"
#include "libKODI_guilib_DialogYesNoHead.h"
#include "libKODI_guilib_ListItemHead.h"
#include "libKODI_guilib_WindowHead.h"

#define IMPLEMENT_KODI_GUI_LIBRARY                                             \
namespace GUILIB                                                               \
{                                                                              \
namespace V2                                                                   \
{                                                                              \
  std::shared_ptr<CGUILib_Internal> CGUILib::g_libKODI_Internal;               \
}; /* namespace V2 */                                                          \
}; /* namespace GUILIB */

#define KODI_GUI_LIBRARY                                                       \
  public:                                                                      \
    static std::shared_ptr<CGUILib_Internal> g_libKODI_Internal;               \
  public:                                                                      \
    CGUILib() { }                                                              \
    virtual ~CGUILib() { }

namespace GUILIB
{
namespace V2
{
extern "C"
{

  typedef void GUILock                    ();
  typedef void GUIUnlock                  ();
  typedef int  GUIGetScreenHeight         ();
  typedef int  GUIGetScreenWidth          ();
  typedef int  GUIGetVideoResolution      ();
  typedef int  GUIGetCurrentWindowDialogId();
  typedef int  GUIGetCurrentWindowId      ();

  typedef struct CB_GUILib_General
  {
    GUILock*                          Lock;
    GUIUnlock*                        Unlock;
    GUIGetScreenHeight*               GetScreenHeight;
    GUIGetScreenWidth*                GetScreenWidth;
    GUIGetVideoResolution*            GetVideoResolution;
    GUIGetCurrentWindowDialogId*      GetCurrentWindowDialogId;
    GUIGetCurrentWindowId*            GetCurrentWindowId;
  } CB_GUILib_General;

  typedef struct CB_GUILib_Controls
  {
    CB_GUILib_Control_Button             Button;
    CB_GUILib_Control_Edit               Edit;
    CB_GUILib_Control_FadeLabel          FadeLabel;
    CB_GUILib_Control_Image              Image;
    CB_GUILib_Control_Label              Label;
    CB_GUILib_Control_Progress           Progress;
    CB_GUILib_Control_RadioButton        RadioButton;
    CB_GUILib_Control_Rendering          Rendering;
    CB_GUILib_Control_SettingsSlider     SettingsSlider;
    CB_GUILib_Control_Slider             Slider;
    CB_GUILib_Control_Spin               Spin;
    CB_GUILib_Control_TextBox            TextBox;
  } CB_GUILib_Controls;

  typedef struct CB_GUILib_Dialogs
  {
    CB_GUILib_Dialog_ExtendedProgress    ExtendedProgress;
    CB_GUILib_Dialog_FileBrowser         FileBrowser;
    CB_GUILib_Dialog_Keyboard            Keyboard;
    CB_GUILib_Dialog_Numeric             Numeric;
    CB_GUILib_Dialog_OK                  OK;
    CB_GUILib_Dialog_Progress            Progress;
    CB_GUILib_Dialog_Select              Select;
    CB_GUILib_Dialog_TextViewer          TextViewer;
    CB_GUILib_Dialog_YesNo               YesNo;
  } CB_GUILib_Dialogs;

  typedef struct CB_GUILib
  {
    CB_GUILib_General                    General;
    CB_GUILib_Controls                   Control;
    CB_GUILib_Dialogs                    Dialogs;
    CB_GUILib_ListItem                   ListItem;
    CB_GUILib_Window                     Window;
  } CB_GUILib;

  typedef CB_GUILib*  _register_level(void *HANDLE, int level);
  typedef void        _unregister(void* HANDLE, void* CB);

  class CGUILib_Internal
  {
  public:
    CGUILib_Internal()
     : m_Handle(nullptr),
       m_libKODI_gui(nullptr) { }

    virtual ~CGUILib_Internal()
    {
      UnRegisterMe();
    }

    bool RegisterMe(void *Handle)
    {
      m_Handle = Handle;

      m_libKODI_gui = dlopen(nullptr, RTLD_LAZY);
      if (m_libKODI_gui == nullptr)
      {
        fprintf(stderr, "Unable to load %s\n", dlerror());
        return false;
      }

      KODI_register = (_register_level*)
        dlsym(m_libKODI_gui, "GUILIB_V2_register_level");
      if (KODI_register == nullptr)
      {
        fprintf(stderr, "Unable to assign function %s\n", dlerror());
        return false;
      }

      KODI_unregister = (_unregister*)
        dlsym(m_libKODI_gui, "GUILIB_V2_unregister");
      if (KODI_unregister == nullptr)
      {
        fprintf(stderr, "Unable to assign function %s\n", dlerror());
        return false;
      }

      m_Callbacks = KODI_register(m_Handle, 2);
      return m_Callbacks != nullptr;
    }

    void UnRegisterMe()
    {
      if (m_libKODI_gui)
      {
        KODI_unregister(m_Handle, m_Callbacks);
        dlclose(m_libKODI_gui);
        m_libKODI_gui = nullptr;
      }
    }
    /*\_________________________________________________________________________
    \*/
    void Lock()
    {
      m_Callbacks->General.Lock();
    }

    void Unlock()
    {
      m_Callbacks->General.Unlock();
    }

    int GetScreenHeight()
    {
      return m_Callbacks->General.GetScreenHeight();
    }

    int GetScreenWidth()
    {
      return m_Callbacks->General.GetScreenWidth();
    }

    int GetVideoResolution()
    {
      return m_Callbacks->General.GetVideoResolution();
    }

    int GetCurrentWindowDialogId()
    {
      return m_Callbacks->General.GetCurrentWindowDialogId();
    }

    int GetCurrentWindowId()
    {
      return m_Callbacks->General.GetCurrentWindowId();
    }
    /*\_________________________________________________________________________
    \*/
    int CAddonGUIDialogSelect_Show(
            const std::string&              heading,
            const std::vector<std::string>& entries,
            int                             selected)
    {
      if (entries.empty())
        return -1;

      const char **entries_tx = (const char **)malloc(entries.size()*sizeof(const char*));
      for (unsigned int i = 0; i < entries.size(); ++i)
        entries_tx[i] = entries[i].c_str();

      int selectedRet = m_Callbacks->Dialogs.Select.Open(heading.c_str(), entries_tx, entries.size(), selected);
      free(entries_tx);
      return selectedRet;
    }

    CB_GUILib*        m_Callbacks;
    void*             m_Handle;

  protected:
    _register_level*  KODI_register;
    _unregister*      KODI_unregister;

  private:
    void*             m_libKODI_gui;
    struct cb_array
    {
      const char* libPath;
    };
  };

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
