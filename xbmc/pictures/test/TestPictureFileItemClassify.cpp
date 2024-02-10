/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "FileItem.h"
#include "LangInfo.h"
#include "ServiceBroker.h"
#include "addons/kodi-dev-kit/include/kodi/c-api/addon-instance/pvr/pvr_epg.h"
#include "games/tags/GameInfoTag.h"
#include "guilib/LocalizeStrings.h"
#include "music/tags/MusicInfoTag.h"
#include "pictures/PictureFileItemClassify.h"
#include "pictures/PictureInfoTag.h"
#include "pvr/channels/PVRChannel.h"
#include "pvr/channels/PVRChannelGroupMember.h"
#include "pvr/epg/EpgInfoTag.h"
#include "pvr/epg/EpgSearchFilter.h"
#include "pvr/recordings/PVRRecording.h"
#include "pvr/timers/PVRTimerInfoTag.h"
#include "utils/FileExtensionProvider.h"
#include "video/VideoInfoTag.h"

#include <gtest/gtest.h>

#include <array>

struct PictureClassifyTest
{
  PictureClassifyTest(const std::string& path, bool res = true,
                    const std::string& mime = "", int tag_type = 0)
    : item(path, false), result(res)
  {
    if (!mime.empty())
      item.SetMimeType(mime);

    switch (tag_type)
    {
      case 1: item.GetVideoInfoTag()->m_strFileNameAndPath = path; break;
      case 2: item.GetGameInfoTag()->SetGameClient("some_client"); break;
      case 3: item.GetMusicInfoTag()->SetPlayCount(1); break;
      case 4: item.GetPictureInfoTag()->SetInfo("foo", "bar"); break;
      case 5:
      {
        // type is very broken, needs advancedsettings or localizestrings in ctors.
/*        PVR_TIMER timer{};
        memset(&timer, 0, sizeof(PVR_TIMER));
        timer.firstDay = 0;
        item = CFileItem(std::make_shared<PVR::CPVRTimerInfoTag>(timer, nullptr, 1));*/
        break;
      }
      case 6:
      {
        // type is very broken, needs pvr manager to instance..
        // auto channel = std::make_shared<PVR::CPVRChannel>(false);
        // item = CFileItem(std::make_shared<PVR::CPVRChannelGroupMember>("foo", 1, 2, channel));
        break;
      }
      case 7: /*item = CFileItem(std::make_shared<PVR::CPVRChannelGroupMember>("foo", 1, 2, nullptr));*/ break;
      case 8: item = CFileItem(std::make_shared<PVR::CPVRRecording>()); break;
      case 9: /*item = CFileItem(std::make_shared<PVR::CPVREpgInfoTag>(EPG_TAG{}, 1, nullptr, 2));*/ break;
      case 10: item = CFileItem(std::make_shared<PVR::CPVREpgSearchFilter>(false)); break;
      default: break;
    }
  }

  CFileItem item;
  bool result;
};

class PictureTest : public testing::WithParamInterface<PictureClassifyTest>
                  , public testing::Test
{};

TEST_P(PictureTest, IsPicture)
{
  EXPECT_EQ(IsPicture(GetParam().item), GetParam().result);
}

const auto picture_tests = std::array{
  PictureClassifyTest{"/home/user/image.jpg", true, "image/jpg"},
  PictureClassifyTest{"/home/user/image.jpg", false, "", 1},
  PictureClassifyTest{"/home/user/image.jpg", false, "", 2},
  PictureClassifyTest{"/home/user/image.jpg", false, "", 3},
  PictureClassifyTest{"/home/user/image.jpg", true, "", 4},
  // PictureClassifyTest{"/home/user/image.jpg", false, "", 5},
  // PictureClassifyTest{"/home/user/image.jpg", false, "", 6},
  // PictureClassifyTest{"/home/user/image.jpg", false, "", 7},
  PictureClassifyTest{"/home/user/image.jpg", false, "", 8},
  // PictureClassifyTest{"/home/user/image.jpg", false, "", 9},
  PictureClassifyTest{"/home/user/image.jpg", false, "", 10},
  // PictureClassifyTest{"pvr://recordings/tv/1", true},
  // PictureClassifyTest{"pvr://123", false},
  // PictureClassifyTest{"dvd://VIDEO_TS/video_ts.ifo", true},
  // PictureClassifyTest{"dvd://1", true},
  // PictureClassifyTest{"/home/user/video.not", true, "application/ogg"},
  // PictureClassifyTest{"/home/user/video.not", true, "application/mp4"},
  // PictureClassifyTest{"/home/user/video.not", true, "application/mxf"},
};

INSTANTIATE_TEST_SUITE_P(TestPictureFileItemClassify, PictureTest, testing::ValuesIn(picture_tests));

TEST(TestPictureFileItemClassify, PictureExtensions)
{
  const auto& exts = CServiceBroker::GetFileExtensionProvider().GetPictureExtensions();
  for (const auto& ext : StringUtils::Split(exts, "|"))
  {
    if (!ext.empty())
      EXPECT_TRUE(IsPicture(CFileItem(ext, false)));
  }
}
