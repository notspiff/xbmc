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

#include "LIRCBuiltins.h"
#include "system.h"

#ifdef HAS_LIRC
#include "input/linux/LIRC.h"
#endif
#ifdef HAS_IRSERVERSUITE
#include "input/windows/IRServerSuite.h"
#endif

#if defined(HAS_LIRC) || defined(HAS_IRSERVERSUITE)

using namespace KODI::MESSAGING;

/*! \brief Disconnect from LIRC
 *  \param params (ignored)
 */
static int Stop(const std::vector<std::string>& params)
{
  g_RemoteControl.Disconnect();
  g_RemoteControl.setUsed(false);

  return 0;
}

/*! \brief Connect to LIRC.
 *  \param params (ignored)
 */
static int Start(const std::vector<std::string>& params)
{
  g_RemoteControl.setUsed(true);
  g_RemoteControl.Initialize();

  return 0;
}

/*! \brief Submit a LIRC command
 *  \param params LIRC commands to submit
 */
static int Send(const std::vector<std::string>& params)
{
  std::string command;
  for (const auto& it : params) {
    command += it;
    command += ' ';
  }
  command.erase(command.size()-1);
  g_RemoteControl.AddSendCommand(command);

  return 0;
}

/// \page page_List_of_built_in_functions
/// \section built_in_functions_4 LIRC built-in's
///
/// -----------------------------------------------------------------------------
///
/// \table_start
///   \table_h2_l{
///     Function,
///     Description }
///   \table_row2_l{
///     <b>`LIRC.Start`</b>
///     ,
///     Connect to LIRC. 
///   }
///   \table_row2_l{
///     <b>`LIRC.Stop`</b>
///     ,
///     Disconnect from LIRC.
///   }
///   \table_row2_l{
///     <b>`LIRC.Send`</b>
///     ,
//      Send a command string to LIRC.
///   }
///  \table_end
///

CBuiltins::CommandMap CLIRCBuiltins::GetOperations() const
{
  return {
           {"LIRC.Stop",    {"Disconnect from LIRC.", 0, Stop}},
           {"LIRC.Start",   {"Connect to LIRC.",      0, Start}},
           {"LIRC.Send",    {"Send a command to LIRC.", 1, Send}},
         };
}
#endif
