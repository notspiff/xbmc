/*
 *  Copyright (C) 2015-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "application/ApplicationComponents.h"
#include "application/ApplicationActionListeners.h"
#include "application/ApplicationPlayer.h"

#include <gtest/gtest.h>

TEST(TestApplicationComponents, GetComponents)
{
  const auto& [c1, c2, c3] = Application::GetComponents<CApplicationActionListeners,
                                                        const CApplicationPlayer,
                                                        CApplicationPlayer>();

  bool same1 = std::is_same<decltype(c1),
                             const std::shared_ptr<CApplicationActionListeners>>::value;
  EXPECT_TRUE(same1);
  EXPECT_TRUE(c1 != nullptr);
  bool same2 = std::is_same<decltype(c2),
                             const std::shared_ptr<const CApplicationPlayer>>::value;
  EXPECT_TRUE(same2);
  EXPECT_TRUE(c2 != nullptr);

  bool same3 = std::is_same<decltype(c3),
                             const std::shared_ptr<CApplicationPlayer>>::value;
  EXPECT_TRUE(same3);
  EXPECT_TRUE(c3 != nullptr);
}
