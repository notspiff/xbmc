/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "FileItem.h"
#include "ServiceBroker.h"
#include "games/tags/GameInfoTag.h"
#include "music/MusicFileItemClassify.h"
#include "music/tags/MusicInfoTag.h"
#include "pictures/PictureInfoTag.h"
#include "utils/FileExtensionProvider.h"
#include "video/VideoInfoTag.h"

#include <gtest/gtest.h>

#include <array>

struct AudioClassifyTest
{
  AudioClassifyTest(const std::string& path, bool res = true,
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
      default: break;
    }
  }

  CFileItem item;
  bool result;
};

class AudioTest : public testing::WithParamInterface<AudioClassifyTest>
                , public testing::Test
{};

TEST_P(AudioTest, IsAudio)
{
  EXPECT_EQ(IsAudio(GetParam().item), GetParam().result);
}

const auto audio_tests = std::array{
  AudioClassifyTest{"/home/user/song.avi", true, "audio/mp3"},
  AudioClassifyTest{"/home/user/song.avi", false, "", 1},
  AudioClassifyTest{"/home/user/song.avi", false, "", 2},
  AudioClassifyTest{"/home/user/song.avi", true, "", 3},
  AudioClassifyTest{"/home/user/song.avi", false, "", 4},
  AudioClassifyTest{"cdda://1"},
  AudioClassifyTest{"/home/user/song.avi", true, "application/ogg"},
  AudioClassifyTest{"/home/user/video.not", true, "application/mp4"},
  AudioClassifyTest{"/home/user/video.not", true, "application/mxf"},
};

INSTANTIATE_TEST_SUITE_P(TestMusicFileItemClassify, AudioTest, testing::ValuesIn(audio_tests));

TEST(TestMusicFileItemClassify, MusicExtensions)
{
  const auto& exts = CServiceBroker::GetFileExtensionProvider().GetMusicExtensions();
  for (const auto& ext : StringUtils::Split(exts, "|"))
  {
    if (!ext.empty())
      EXPECT_TRUE(IsAudio(CFileItem(ext, false)));
  }
}

struct SimpleDefinition
{
  std::string path;
  bool result;
};

class AudioBookTest : public testing::WithParamInterface<SimpleDefinition>
                    , public testing::Test
{};

TEST_P(AudioBookTest, IsAudioBook)
{
  EXPECT_EQ(IsAudioBook(CFileItem(GetParam().path, false)), GetParam().result);
}

const auto audiobook_tests = std::array{
  SimpleDefinition{"/home/user/test.m4b", true},
  SimpleDefinition{"/home/user/test.mka", true},
  SimpleDefinition{"/home/user/test.not", false},
};

INSTANTIATE_TEST_SUITE_P(TestMusicFileItemClassify, AudioBookTest, testing::ValuesIn(audiobook_tests));

class CuesheetTest : public testing::WithParamInterface<SimpleDefinition>
                   , public testing::Test
{};

TEST_P(CuesheetTest, IsCUESheet)
{
  EXPECT_EQ(IsCUESheet(CFileItem(GetParam().path, false)), GetParam().result);
}

const auto cuesheet_tests = std::array{
  SimpleDefinition{"/home/user/test.cue", true},
  SimpleDefinition{"/home/user/test.foo", false},
};

INSTANTIATE_TEST_SUITE_P(TestMusicFileItemClassify, CuesheetTest, testing::ValuesIn(cuesheet_tests));

class LyricsTest : public testing::WithParamInterface<SimpleDefinition>
                 , public testing::Test
{};

TEST_P(LyricsTest, IsLyrics)
{
  EXPECT_EQ(IsLyrics(CFileItem(GetParam().path, false)), GetParam().result);
}

const auto lyrics_tests = std::array{
  SimpleDefinition{"/home/user/test.lrc", true},
  SimpleDefinition{"/home/user/test.cdg", true},
  SimpleDefinition{"/home/user/test.not", false},
};

INSTANTIATE_TEST_SUITE_P(TestMusicFileItemClassify, LyricsTest, testing::ValuesIn(lyrics_tests));
