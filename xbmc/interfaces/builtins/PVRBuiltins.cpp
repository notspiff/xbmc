/*
 *      Copyright (C) 2005-2015 Team XBMC
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

#include "PVRBuiltins.h"

#include "Application.h"
#include "pvr/PVRManager.h"

/*! \brief Start the PVR manager.
 *  \param params (ignored)
 */
static int Start(const std::vector<std::string>& params)
{
  g_application.StartPVRManager();

  return 0;
}

/*! \brief Stop the PVR manager.
 *   \param params (ignored)
 */
static int Stop(const std::vector<std::string>& params)
{
  g_application.StopPVRManager();

  return 0;
}

/*! \brief Search for missing channel icons
 *   \param params (ignored)
 */
static int SearchMissingIcons(const std::vector<std::string>& params)
{
  PVR::CPVRManager::GetInstance().TriggerSearchMissingChannelIcons();

  return 0;
}

// Note: For new Texts with komma add a "\" before!!! Is used for table text.
// field change and brings conflicts is not unseted on text!
//
/// \page page_List_of_built_in_functions
/// \section built_in_functions_10 PVR built-in's
///
/// -----------------------------------------------------------------------------
///
/// \table_start
///   \table_h2_l{
///     Function,
///     Description }
///   \table_row2_l{
///     <b>`PVR.StartManager`</b>\n
///     <b>`StartPVRManager`</b> (deprecated)
///     ,
///     (Re)Starts the PVR manager
///   }
///   \table_row2_l{
///     <b>`PVR.StartManager`</b>\n
///     <b>`StopPVRManager`</b> (deprecated)
///     ,
///     Stops the PVR manager
///   }
///   \table_row2_l{
///     <b>`PVR.SearchMissingChannelIcons`</b>
///     ,
///     Will start a search for missing channel icons
///   }
/// \table_end
///

CBuiltins::CommandMap CPVRBuiltins::GetOperations() const
{
  return {
           {"startpvrmanager",                {"(Re)Starts the PVR manager",       0, Start}}, // deprecated alias
           {"pvr.startmanager",               {"(Re)Starts the PVR manager",       0, Start}},
           {"stoppvrmanager",                 {"Stops the PVR manager",            0, Stop}},
           {"pvr.stopmanager",                {"Stops the PVR manager",            0, Stop}},
           {"pvr.searchmissingchannelicons",  {"Search for missing channel icons", 0, SearchMissingIcons}}
         };
}
