/*
 *      Copyright (C) 2005-2014 Team XBMC
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

#pragma once
#include "DVDDemux.h"
#include <vector>

class CCaptionBlock;
class CDecoderCC708;

class CDVDDemuxCC : public CDVDDemux
{
public:
  CDVDDemuxCC(AVCodecID codec);
  virtual ~CDVDDemuxCC();

  void Reset() override {}
  void Abort() override {}
  void Flush() override {}
  DemuxPacket* Read() override { return nullptr; }
  bool SeekTime(double time, bool backwords = false,
                double* startpts = nullptr) override { return true; }
  void SetSpeed(int iSpeed) override {}
  int GetStreamLength() override { return 0; }
  CDemuxStream* GetStream(int iStreamId) const override;
  std::vector<CDemuxStream*> GetStreams() const override;
  int GetNrOfStreams() const override;
  std::string GetFileName() override { return ""; }

  DemuxPacket* Read(DemuxPacket *packet);
  static void Handler(int service, void *userdata);

protected:
  bool OpenDecoder();
  void Dispose();
  DemuxPacket* Decode();

  struct streamdata
  {
    int streamIdx;
    int service;
    bool hasData ;
    double pts;
  };
  std::vector<streamdata> m_streamdata;
  std::vector<CDemuxStreamSubtitle> m_streams;
  bool m_hasData;
  double m_curPts;
  std::vector<CCaptionBlock*> m_ccReorderBuffer;
  std::vector<CCaptionBlock*> m_ccTempBuffer;
  CDecoderCC708 *m_ccDecoder;
  AVCodecID m_codec;
};
