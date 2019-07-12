/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "pvr/channels/PVRChannelsPath.h"

#include <gtest/gtest.h>

TEST(TestPVRChannelsPath, Channel)
{
  PVR::CPVRChannelsPath path(false, "Group1", "yo", 123);

  EXPECT_EQ(static_cast<std::string>(path), "pvr://channels/tv/Group1/yo_123.pvr");
  EXPECT_FALSE(path.IsEmpty());
  EXPECT_FALSE(path.IsRadio());
  EXPECT_FALSE(path.IsChannelGroup());
  EXPECT_FALSE(path.IsHiddenChannelGroup());
  EXPECT_TRUE(path.IsChannel());
  EXPECT_EQ(path.GetGroupName(), "Group1");
  EXPECT_EQ(path.GetClientID(), "yo");
  EXPECT_EQ(path.GetChannelUID(), 123);
}

TEST(TestPVRChannelsPath, Group)
{
  PVR::CPVRChannelsPath path(false, "Group1");

  EXPECT_EQ(static_cast<std::string>(path), "pvr://channels/tv/Group1");
  EXPECT_FALSE(path.IsEmpty());
  EXPECT_FALSE(path.IsRadio());
  EXPECT_FALSE(path.IsChannel());
  EXPECT_TRUE(path.IsChannelGroup());
  EXPECT_FALSE(path.IsHiddenChannelGroup());
  EXPECT_EQ(path.GetGroupName(), "Group1");
}

TEST(TestPVRChannelsPath, HiddenGroup)
{
  PVR::CPVRChannelsPath path(false, true, "Group2");

  EXPECT_EQ(static_cast<std::string>(path), "pvr://channels/tv/.hidden");
  EXPECT_FALSE(path.IsRadio());
  EXPECT_FALSE(path.IsChannel());
  EXPECT_TRUE(path.IsChannelGroup());
  EXPECT_EQ(path.GetGroupName(), ".hidden");
  EXPECT_TRUE(path.IsHiddenChannelGroup());
}

TEST(TestPVRChannelsPath, RadioGroup)
{
  PVR::CPVRChannelsPath path(true, "Group1");

  EXPECT_EQ(static_cast<std::string>(path), "pvr://channels/radio/Group1");

  EXPECT_FALSE(path.IsEmpty());
  EXPECT_TRUE(path.IsRadio());
  EXPECT_FALSE(path.IsChannel());
  EXPECT_TRUE(path.IsChannelGroup());
  EXPECT_EQ(path.GetGroupName(), "Group1");
}

TEST(TestPVRChannelsPath, Parse)
{
  PVR::CPVRChannelsPath path2(true, "Group1");
  PVR::CPVRChannelsPath path(static_cast<std::string>(path2));

  EXPECT_FALSE(path.IsEmpty());
  EXPECT_TRUE(path.IsRadio());
  EXPECT_TRUE(path.IsChannelGroup());
  EXPECT_EQ(path.GetGroupName(), "Group1");
}
