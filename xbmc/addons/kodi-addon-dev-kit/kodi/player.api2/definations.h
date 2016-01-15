#pragma once
/*
 *      Copyright (C) 2015 Team KODI
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with KODI; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#undef ATTRIBUTE_PACKED
#undef PRAGMA_PACK_BEGIN
#undef PRAGMA_PACK_END

#if defined(__GNUC__)
#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 95)
#define ATTRIBUTE_PACKED __attribute__ ((packed))
#define PRAGMA_PACK 0
#endif
#endif

#if !defined(ATTRIBUTE_PACKED)
#define ATTRIBUTE_PACKED
#define PRAGMA_PACK 1
#endif

#ifdef __cplusplus
namespace PlayerLIB
{
namespace V2
{
extern "C"
{
#endif

  /*!
   * \ingroup PlayerLIB
   * @{
   */
  static constexpr const int   PlayerLIB_apiLevel = 2;
  static constexpr const char* PlayerLIB_version  = "4.1.0";

  typedef void* PLAYERHANDLE;

  #define DVD_TIME_BASE 1000000
  #define DVD_NOPTS_VALUE    (-1LL<<52) // should be possible to represent in both double and __int64
  /** @}*/

  /*!
   * \ingroup CAddonPlayList
   * @{
   */
  typedef enum AddonPlayListType
  {
    PlayList_Music   = 0,
    PlayList_Video   = 1,
    PlayList_Picture = 2
  } AddonPlayListType;
  /** @}*/

#ifdef __cplusplus
}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace PlayerLIB */
#if defined(BUILD_KODI_ADDON)
  using namespace PlayerLIB::V2;
#endif
#endif
