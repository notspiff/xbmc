/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "FileItem.h"
#include "music/MusicFileItemClassify.h"

#include <gtest/gtest.h>

#include <array>

struct CueDefinition
{
  std::string path;
  bool result;
};

class CuesheetTest : public testing::WithParamInterface<CueDefinition>
                   , public testing::Test
{};

TEST_P(CuesheetTest, IsCUESheet)
{
  EXPECT_EQ(IsCUESheet(CFileItem(GetParam().path, false)), GetParam().result);
}

const auto cuesheet_tests = std::array{
  CueDefinition{"/home/user/test.cue", true},
  CueDefinition{"/home/user/test.foo", false},
};

INSTANTIATE_TEST_SUITE_P(TestMusicFileItemClassify, CuesheetTest, testing::ValuesIn(cuesheet_tests));
