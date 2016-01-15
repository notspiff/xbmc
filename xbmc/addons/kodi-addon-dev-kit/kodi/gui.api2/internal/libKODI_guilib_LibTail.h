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

namespace GUILIB
{
namespace V2
{

  inline bool CGUILib::RegisterMe(void *handle)
  {
    g_libKODI_Internal = std::shared_ptr<CGUILib_Internal>(new CGUILib_Internal);
    return g_libKODI_Internal->RegisterMe(handle);
  }

  inline void CGUILib::UnRegisterMe()
  {
    if (g_libKODI_Internal)
    {
      g_libKODI_Internal->UnRegisterMe();
      g_libKODI_Internal.reset();
    }
  }

  inline void  CGUILib::Lock()
  {
    g_libKODI_Internal->Lock();
  }

  inline void  CGUILib::Unlock()
  {
    g_libKODI_Internal->Unlock();
  }

  inline int  CGUILib::GetScreenHeight()
  {
    return g_libKODI_Internal->GetScreenHeight();
  }

  inline int  CGUILib::GetScreenWidth()
  {
    return g_libKODI_Internal->GetScreenWidth();
  }

  inline int  CGUILib::GetVideoResolution()
  {
    return g_libKODI_Internal->GetVideoResolution();
  }

  inline int  CGUILib::GetCurrentWindowDialogId()
  {
    return g_libKODI_Internal->GetCurrentWindowDialogId();
  }

  inline int  CGUILib::GetCurrentWindowId()
  {
    return g_libKODI_Internal->GetCurrentWindowId();
  }

}; /* namespace V2 */
}; /* namespace GUILIB */
