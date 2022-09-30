/*
 *  Copyright (C) 2022 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "ServiceBroker.h"
#include "application/IApplicationComponent.h"
#include "utils/ComponentContainer.h"

#include <type_traits>
#include <variant>

//! \brief Convenience alias for application components.
using CApplicationComponents = CComponentContainer<IApplicationComponent>;

namespace Application
{

template<typename... Args>
auto GetComponents()
{
  return CServiceBroker::GetAppComponents().GetComponents<Args...>();
}

}
