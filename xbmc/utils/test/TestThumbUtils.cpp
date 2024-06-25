/*
 *  Copyright (C) 2024 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "utils/ThumbUtils.h"

#include "FileItem.h"

#include <gtest/gtest.h>

#include <array>
#include <filesystem>
#include <fstream>

#include <fmt/format.h>

using namespace KODI;

struct TbnTest
{
  std::string path;
  std::string result;
  bool isFolder = false;
};

class GetTbnTest : public testing::WithParamInterface<TbnTest>, public testing::Test
{
};

TEST_P(GetTbnTest, TbnTest)
{
  EXPECT_EQ(THUMBS::GetTBNFile(CFileItem(GetParam().path, GetParam().isFolder)), GetParam().result);
}

const auto tbn_tests = std::array{
    TbnTest{"/home/user/video.avi", "/home/user/video.tbn"},
    TbnTest{"/home/user/video/", "/home/user/video.tbn", true},
    TbnTest{"/home/user/bar.xbt", "/home/user/bar.tbn", true},
    TbnTest{"zip://%2fhome%2fuser%2fbar.zip/foo.avi", "/home/user/foo.tbn"},
    TbnTest("stack:///home/user/foo-cd1.avi , /home/user/foo-cd2.avi", "/home/user/foo.tbn")
};

INSTANTIATE_TEST_SUITE_P(TestThumbUtils,
                         GetTbnTest,
                         testing::ValuesIn(tbn_tests));

TEST(TestThumbUtils, GetTbnStack)
{
  auto path = std::filesystem::temp_directory_path();
  {
    std::ofstream of(path / "foo-cd1.tbn", std::ios::out);
  }
  const std::string stackPath = fmt::format("stack://{}/foo-cd1.avi , {}/foo-cd2.avi", path.generic_string(), path.generic_string());
  CFileItem item(stackPath, false);
  EXPECT_EQ(THUMBS::GetTBNFile(item), (path / "foo-cd1.tbn").generic_string());
  std::filesystem::remove(path / "foo-cd1.tbn");
}
