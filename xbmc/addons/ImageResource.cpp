/*
*      Copyright (C) 2005-2013 Team XBMC
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
#include "ImageResource.h"
#include "addons/AddonManager.h"
#include "dialogs/GUIDialogKaiToast.h"
#include "dialogs/GUIDialogYesNo.h"
#include "guilib/GUIWindowManager.h"
#include "settings/Settings.h"
#include "utils/StringUtils.h"

using namespace std;

namespace ADDON
{

CImageResource::CImageResource(const cp_extension_t *ext)
  : CResource(ext)
{
  if (ext != NULL)
  {
    m_type = CAddonMgr::Get().GetExtValue(ext->configuration, "@type");
  }
}

CImageResource::CImageResource(const CImageResource &rhs)
  : CResource(rhs)
{ }

AddonPtr CImageResource::Clone() const
{
  return AddonPtr(new CImageResource(*this));
}

bool CImageResource::OnPreInstall()
{
  return true;
}

void CImageResource::OnPostInstall(bool restart, bool update, bool modal)
{
}

bool CImageResource::IsAllowed(const std::string &file) const
{
  return file.empty() ||
         StringUtils::EqualsNoCase(URIUtils::GetExtension(file), ".png") ||
         StringUtils::EqualsNoCase(URIUtils::GetExtension(file), ".jpg");
}
}
