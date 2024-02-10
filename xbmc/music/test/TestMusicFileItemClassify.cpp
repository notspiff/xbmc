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
