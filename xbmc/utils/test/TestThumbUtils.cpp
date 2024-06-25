/*
 *  Copyright (C) 2024 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "URL.h"
#include "utils/ThumbUtils.h"

#include "FileItem.h"
#include "utils/StringUtils.h"
#include "utils/URIUtils.h"
#include "video/VideoInfoTag.h"

#include <gtest/gtest.h>

#include <array>
#include <filesystem>
#include <fstream>
#include <random>

#include <fmt/format.h>

using namespace KODI;

namespace
{

std::string unique_path(const std::string& input)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  auto randchar = [&gen]()
  {
    const std::string set = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::uniform_int_distribution<> select(0, set.size()-1);
    return set[select(gen)];
  };

  std::string ret;
  ret.reserve(input.size());
  std::transform(input.begin(), input.end(), std::back_inserter(ret),
                 [&randchar](const char c)
                 {
                   return (c == '%') ? randchar() : c;
                 });

  return ret;
}

struct FanartTest
{
  std::string path;
  std::string result;
};

class GetLocalFanartTest : public testing::WithParamInterface<FanartTest>, public testing::Test
{
};

const auto local_fanart_tests = std::array{
    FanartTest{"stack://#DIRECTORY#/foo-cd1.avi , #DIRECTORY#/foo-cd2.avi", "foo-fanart.jpg"},
    FanartTest{"stack://#DIRECTORY#/foo-cd1.avi , #DIRECTORY#/foo-cd2.avi", "foo-cd1-fanart.jpg"},
    FanartTest{"zip://#URLENCODED_DIRECTORY#%2fbar.zip/foo.avi", "foo-fanart.jpg"},
    FanartTest{"ftp://some.where/foo.avi", ""},
    FanartTest{"https://some.where/foo.avi", ""},
    FanartTest{"upnp://some.where/123", ""},
    FanartTest{"bluray://1",  ""},
    FanartTest{"/home/user/1.pvr", ""},
    FanartTest{"plugin://random.video/1", ""},
    FanartTest{"addons://plugins/video/1", ""},
    FanartTest{"dvd://1",  ""},
    FanartTest{"", ""},
    FanartTest{"foo.avi", ""},
    FanartTest{"foo.avi", "foo-fanart.jpg"},
    FanartTest{"videodb://movies/1", ""},
    FanartTest{"videodb://movies/1", "foo-fanart.jpg"},
};

struct IconTest
{
  std::string path;
  std::string icon;
  std::string overlay{};
  bool isFolder = true;
  bool valid = true;
};

class FillInDefaultIconTest : public testing::WithParamInterface<IconTest>, public testing::Test
{
};

const auto icon_tests = std::array{
    IconTest{"pvr://guide", "", "", false, false},
    IconTest{"/home/user/test.pvr", "DefaultTVShows.png"},
    IconTest{"/home/user/test.zip", "DefaultFile.png"},
    IconTest{"/home/user/test.mp3", "DefaultAudio.png"},
    IconTest{"/home/user/test.avi", "DefaultVideo.png"},
    IconTest{"/home/user/test.jpg", "DefaultPicture.png"},
    IconTest{"/home/user/test.m3u", "DefaultPlaylist.png"},
    IconTest{"/home/user/test.xsp", "DefaultPlaylist.png"},
    IconTest{"/home/user/test.py", "DefaultScript.png"},
};

struct TbnTest
{
  std::string path;
  std::string result;
  bool isFolder = false;
};

class GetTbnTest : public testing::WithParamInterface<TbnTest>, public testing::Test
{
};

const auto tbn_tests = std::array{
    TbnTest{"/home/user/video.avi", "/home/user/video.tbn"},
    TbnTest{"/home/user/video/", "/home/user/video.tbn", true},
    TbnTest{"/home/user/bar.xbt", "/home/user/bar.tbn", true},
    TbnTest{"zip://%2fhome%2fuser%2fbar.zip/foo.avi", "/home/user/foo.tbn"},
    TbnTest("stack:///home/user/foo-cd1.avi , /home/user/foo-cd2.avi", "/home/user/foo.tbn")
};

}

TEST_P(GetTbnTest, TbnTest)
{
  EXPECT_EQ(THUMBS::GetTBNFile(CFileItem(GetParam().path, GetParam().isFolder)), GetParam().result);
}

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
  EXPECT_EQ(THUMBS::GetTBNFile(item), path / "foo-cd1.tbn");
  std::filesystem::remove(path / "foo-cd1.tbn");
}

TEST_P(FillInDefaultIconTest, FillInDefaultIcon)
{
  CFileItem item(GetParam().path, false);
  if (!GetParam().valid)
    item.SetArt("icon", "InvalidImage.png");
  THUMBS::FillInDefaultIcon(item);
  EXPECT_EQ(item.GetArt("icon"), GetParam().valid ? GetParam().icon : "InvalidImage.png");
  EXPECT_EQ(item.GetOverlayImage(), GetParam().overlay);
}

INSTANTIATE_TEST_SUITE_P(TestThumbUtils,
                         FillInDefaultIconTest,
                         testing::ValuesIn(icon_tests));

TEST_P(GetLocalFanartTest, GetLocalFanart)
{
  std::string path, file_path, uniq;
  if (GetParam().result.empty())
    file_path = GetParam().path;
  else
  {
    auto tmpdir = std::filesystem::temp_directory_path();
    uniq = unique_path("FanartTest%%%%%");
    std::filesystem::create_directory(tmpdir / uniq);
    std::ofstream of(tmpdir / uniq / GetParam().result, std::ios::out);
    path = tmpdir / uniq;
    if (GetParam().path.find("#DIRECTORY#") !=  std::string::npos)
    {
      file_path = GetParam().path;
      StringUtils::Replace(file_path, "#DIRECTORY#", tmpdir / uniq);
    }
    else if (GetParam().path.find("#URLENCODED_DIRECTORY#") != std::string::npos)
    {
      file_path = GetParam().path;
      StringUtils::Replace(file_path, "#URLENCODED_DIRECTORY#", CURL::Encode(path));
    }
    else if (GetParam().path.starts_with("videodb://"))
    {
      file_path = GetParam().path;
    }
    else
      file_path = tmpdir / uniq / GetParam().path;
  }

  CFileItem item(file_path, false);
  if (GetParam().path.starts_with("videodb://") && !GetParam().result.empty()) {
    item.GetVideoInfoTag()->m_strFileNameAndPath = URIUtils::AddFileToFolder(path, "foo.avi");
  }
  const std::string res = THUMBS::GetLocalFanart(item);

  EXPECT_EQ(URIUtils::GetFileName(res), GetParam().result);

  if (!GetParam().result.empty())
    std::filesystem::remove_all(path);
}

INSTANTIATE_TEST_SUITE_P(TestThumbUtils,
                         GetLocalFanartTest,
                         testing::ValuesIn(local_fanart_tests));
