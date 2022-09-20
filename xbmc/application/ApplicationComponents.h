/*
 *  Copyright (C) 2016-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "application/IApplicationComponent.h"

#include "threads/CriticalSection.h"

#include <memory>
#include <mutex>
#include <typeindex>
#include <unordered_map>

class CApplication;

class CApplicationComponents
{
  friend class CApplication;
public:
  //! \brief Obtain an application component.
  template<class T>
  std::shared_ptr<T> GetComponent()
  {
    std::unique_lock<CCriticalSection> lock(m_critSection);
    const auto it = m_components.find(std::type_index(typeid(T)));
    if (it != m_components.end())
      return std::static_pointer_cast<T>((*it).second);

    return nullptr;
  }

  //! \brief Obtain an application component.
  template<class T>
  std::shared_ptr<const T> GetComponent() const
  {
    std::unique_lock<CCriticalSection> lock(m_critSection);
    const auto it = m_components.find(std::type_index(typeid(T)));
    if (it != m_components.end())
      return std::static_pointer_cast<const T>((*it).second);

    return nullptr;
  }

protected:
  //! \brief Register a new application component instance.
  void RegisterComponent(const std::shared_ptr<IApplicationComponent>& component)
  {
    if (!component)
      return;

    // Note: Extra var needed to avoid clang warning
    // "Expression with side effects will be evaluated despite being used as an operand to 'typeid'"
    // https://stackoverflow.com/questions/46494928/clang-warning-on-expression-side-effects
    const auto& componentRef = *component;

    std::unique_lock<CCriticalSection> lock(m_critSection);
    m_components.insert({std::type_index(typeid(componentRef)), component});
  }

  //! \brief Deregister an application component.
  void DeregisterComponent(const std::type_info& typeInfo)
  {
    std::unique_lock<CCriticalSection> lock(m_critSection);
    m_components.erase(typeInfo);
  }

private:
  mutable CCriticalSection m_critSection;
  std::unordered_map<std::type_index, std::shared_ptr<IApplicationComponent>> m_components;
};
