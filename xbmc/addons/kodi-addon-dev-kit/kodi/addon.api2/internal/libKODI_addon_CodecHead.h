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

class DemuxPacket;

namespace AddOnLIB
{
namespace V2
{

  typedef kodi_codec _get_codec_by_name(void* HANDLE, const char* strCodecName);
  typedef DemuxPacket* _allocate_demux_packet(void* HANDLE, int iDataSize);
  typedef void _free_demux_packet(void* HANDLE, DemuxPacket* pPacket);

  typedef struct CB_Addon_Codec
  {
    _get_codec_by_name*             get_codec_by_name;
    _allocate_demux_packet*         allocate_demux_packet;
    _free_demux_packet*             free_demux_packet;
  } CB_AddonLib_Codec;

}; /* namespace V2 */
}; /* namespace AddOnLIB */
