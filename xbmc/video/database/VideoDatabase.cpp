/*
 *  Copyright (C) 2016-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "VideoDatabase.h"

#include "Application.h"
#include "FileItem.h"
#include "GUIInfoManager.h"
#include "GUIPassword.h"
#include "ServiceBroker.h"
#include "TextureCache.h"
#include "URL.h"
#include "Util.h"
#include "VideoInfoScanner.h"
#include "XBDateTime.h"
#include "addons/AddonManager.h"
#include "dbwrappers/dataset.h"
#include "dialogs/GUIDialogExtendedProgressBar.h"
#include "dialogs/GUIDialogKaiToast.h"
#include "dialogs/GUIDialogProgress.h"
#include "dialogs/GUIDialogYesNo.h"
#include "filesystem/Directory.h"
#include "filesystem/File.h"
#include "filesystem/MultiPathDirectory.h"
#include "filesystem/PluginDirectory.h"
#include "filesystem/StackDirectory.h"
#include "guilib/GUIComponent.h"
#include "guilib/GUIWindowManager.h"
#include "guilib/LocalizeStrings.h"
#include "guilib/guiinfo/GUIInfoLabels.h"
#include "interfaces/AnnouncementManager.h"
#include "messaging/helpers/DialogOKHelper.h"
#include "playlists/SmartPlayList.h"
#include "profiles/ProfileManager.h"
#include "settings/AdvancedSettings.h"
#include "settings/MediaSettings.h"
#include "settings/MediaSourceSettings.h"
#include "settings/Settings.h"
#include "settings/SettingsComponent.h"
#include "storage/MediaManager.h"
#include "threads/SystemClock.h"
#include "utils/FileUtils.h"
#include "utils/GroupUtils.h"
#include "utils/LabelFormatter.h"
#include "utils/StringUtils.h"
#include "utils/URIUtils.h"
#include "utils/Variant.h"
#include "utils/XMLUtils.h"
#include "utils/log.h"
#include "video/VideoDbUrl.h"
#include "video/VideoInfoTag.h"
#include "video/windows/GUIWindowVideoBase.h"

#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace dbiplus;
using namespace XFILE;
using namespace VIDEO;
using namespace ADDON;
using namespace KODI::MESSAGING;
using namespace KODI::GUILIB;

//********************************************************************************************************************************
CVideoDatabase::CVideoDatabase(void) = default;

//********************************************************************************************************************************
CVideoDatabase::~CVideoDatabase(void) = default;

//********************************************************************************************************************************
bool CVideoDatabase::Open()
{
  return CDatabase::Open(CServiceBroker::GetSettingsComponent()->GetAdvancedSettings()->m_databaseVideo);
}

void CVideoDatabase::CreateTables()
{
  CLog::Log(LOGINFO, "create bookmark table");
  m_pDS->exec("CREATE TABLE bookmark ( idBookmark integer primary key, idFile integer, timeInSeconds double, totalTimeInSeconds double, thumbNailImage text, player text, playerState text, type integer)\n");

  CLog::Log(LOGINFO, "create settings table");
  m_pDS->exec("CREATE TABLE settings ( idFile integer, Deinterlace bool,"
              "ViewMode integer,ZoomAmount float, PixelRatio float, VerticalShift float, AudioStream integer, SubtitleStream integer,"
              "SubtitleDelay float, SubtitlesOn bool, Brightness float, Contrast float, Gamma float,"
              "VolumeAmplification float, AudioDelay float, ResumeTime integer,"
              "Sharpness float, NoiseReduction float, NonLinStretch bool, PostProcess bool,"
              "ScalingMethod integer, DeinterlaceMode integer, StereoMode integer, StereoInvert bool, VideoStream integer,"
              "TonemapMethod integer, TonemapParam float, Orientation integer, CenterMixLevel integer)\n");

  CLog::Log(LOGINFO, "create stacktimes table");
  m_pDS->exec("CREATE TABLE stacktimes (idFile integer, times text)\n");

  CLog::Log(LOGINFO, "create genre table");
  m_pDS->exec("CREATE TABLE genre ( genre_id integer primary key, name TEXT)\n");
  m_pDS->exec("CREATE TABLE genre_link (genre_id integer, media_id integer, media_type TEXT)");

  CLog::Log(LOGINFO, "create country table");
  m_pDS->exec("CREATE TABLE country ( country_id integer primary key, name TEXT)");
  m_pDS->exec("CREATE TABLE country_link (country_id integer, media_id integer, media_type TEXT)");

  CLog::Log(LOGINFO, "create movie table");
  std::string columns = "CREATE TABLE movie ( idMovie integer primary key, idFile integer";

  for (int i = 0; i < VIDEODB_MAX_COLUMNS; i++)
    columns += StringUtils::Format(",c%02d text", i);

  columns += ", idSet integer, userrating integer, premiered text)";
  m_pDS->exec(columns);

  CLog::Log(LOGINFO, "create actor table");
  m_pDS->exec("CREATE TABLE actor ( actor_id INTEGER PRIMARY KEY, name TEXT, art_urls TEXT )");
  m_pDS->exec("CREATE TABLE actor_link(actor_id INTEGER, media_id INTEGER, media_type TEXT, role TEXT, cast_order INTEGER)");
  m_pDS->exec("CREATE TABLE director_link(actor_id INTEGER, media_id INTEGER, media_type TEXT)");
  m_pDS->exec("CREATE TABLE writer_link(actor_id INTEGER, media_id INTEGER, media_type TEXT)");

  CLog::Log(LOGINFO, "create path table");
  m_pDS->exec("CREATE TABLE path ( idPath integer primary key, strPath text, strContent text, strScraper text, strHash text, scanRecursive integer, useFolderNames bool, strSettings text, noUpdate bool, exclude bool, dateAdded text, idParentPath integer)");

  CLog::Log(LOGINFO, "create files table");
  m_pDS->exec("CREATE TABLE files ( idFile integer primary key, idPath integer, strFilename text, playCount integer, lastPlayed text, dateAdded text)");

  CLog::Log(LOGINFO, "create tvshow table");
  columns = "CREATE TABLE tvshow ( idShow integer primary key";

  for (int i = 0; i < VIDEODB_MAX_COLUMNS; i++)
    columns += StringUtils::Format(",c%02d text", i);

  columns += ", userrating integer, duration INTEGER)";
  m_pDS->exec(columns);

  CLog::Log(LOGINFO, "create episode table");
  columns = "CREATE TABLE episode ( idEpisode integer primary key, idFile integer";
  for (int i = 0; i < VIDEODB_MAX_COLUMNS; i++)
  {
    std::string column;
    if ( i == VIDEODB_ID_EPISODE_SEASON || i == VIDEODB_ID_EPISODE_EPISODE || i == VIDEODB_ID_EPISODE_BOOKMARK)
      column = StringUtils::Format(",c%02d varchar(24)", i);
    else
      column = StringUtils::Format(",c%02d text", i);

    columns += column;
  }
  columns += ", idShow integer, userrating integer, idSeason integer)";
  m_pDS->exec(columns);

  CLog::Log(LOGINFO, "create tvshowlinkpath table");
  m_pDS->exec("CREATE TABLE tvshowlinkpath (idShow integer, idPath integer)\n");

  CLog::Log(LOGINFO, "create movielinktvshow table");
  m_pDS->exec("CREATE TABLE movielinktvshow ( idMovie integer, IdShow integer)\n");

  CLog::Log(LOGINFO, "create studio table");
  m_pDS->exec("CREATE TABLE studio ( studio_id integer primary key, name TEXT)\n");
  m_pDS->exec("CREATE TABLE studio_link (studio_id integer, media_id integer, media_type TEXT)");

  CLog::Log(LOGINFO, "create musicvideo table");
  columns = "CREATE TABLE musicvideo ( idMVideo integer primary key, idFile integer";
  for (int i = 0; i < VIDEODB_MAX_COLUMNS; i++)
    columns += StringUtils::Format(",c%02d text", i);

  columns += ", userrating integer, premiered text)";
  m_pDS->exec(columns);

  CLog::Log(LOGINFO, "create streaminfo table");
  m_pDS->exec("CREATE TABLE streamdetails (idFile integer, iStreamType integer, "
    "strVideoCodec text, fVideoAspect float, iVideoWidth integer, iVideoHeight integer, "
    "strAudioCodec text, iAudioChannels integer, strAudioLanguage text, "
    "strSubtitleLanguage text, iVideoDuration integer, strStereoMode text, strVideoLanguage text)");

  CLog::Log(LOGINFO, "create sets table");
  m_pDS->exec("CREATE TABLE sets ( idSet integer primary key, strSet text, strOverview text)");

  CLog::Log(LOGINFO, "create seasons table");
  m_pDS->exec("CREATE TABLE seasons ( idSeason integer primary key, idShow integer, season integer, name text, userrating integer)");

  CLog::Log(LOGINFO, "create art table");
  m_pDS->exec("CREATE TABLE art(art_id INTEGER PRIMARY KEY, media_id INTEGER, media_type TEXT, type TEXT, url TEXT)");

  CLog::Log(LOGINFO, "create tag table");
  m_pDS->exec("CREATE TABLE tag (tag_id integer primary key, name TEXT)");
  m_pDS->exec("CREATE TABLE tag_link (tag_id integer, media_id integer, media_type TEXT)");

  CLog::Log(LOGINFO, "create rating table");
  m_pDS->exec("CREATE TABLE rating (rating_id INTEGER PRIMARY KEY, media_id INTEGER, media_type TEXT, rating_type TEXT, rating FLOAT, votes INTEGER)");

  CLog::Log(LOGINFO, "create uniqueid table");
  m_pDS->exec("CREATE TABLE uniqueid (uniqueid_id INTEGER PRIMARY KEY, media_id INTEGER, media_type TEXT, value TEXT, type TEXT)");
}

void CVideoDatabase::CreateLinkIndex(const char *table)
{
  m_pDS->exec(PrepareSQL("CREATE UNIQUE INDEX ix_%s_1 ON %s (name(255))", table, table));
  m_pDS->exec(PrepareSQL("CREATE UNIQUE INDEX ix_%s_link_1 ON %s_link (%s_id, media_type(20), media_id)", table, table, table));
  m_pDS->exec(PrepareSQL("CREATE UNIQUE INDEX ix_%s_link_2 ON %s_link (media_id, media_type(20), %s_id)", table, table, table));
  m_pDS->exec(PrepareSQL("CREATE INDEX ix_%s_link_3 ON %s_link (media_type(20))", table, table));
}

void CVideoDatabase::CreateForeignLinkIndex(const char *table, const char *foreignkey)
{
  m_pDS->exec(PrepareSQL("CREATE UNIQUE INDEX ix_%s_link_1 ON %s_link (%s_id, media_type(20), media_id)", table, table, foreignkey));
  m_pDS->exec(PrepareSQL("CREATE UNIQUE INDEX ix_%s_link_2 ON %s_link (media_id, media_type(20), %s_id)", table, table, foreignkey));
  m_pDS->exec(PrepareSQL("CREATE INDEX ix_%s_link_3 ON %s_link (media_type(20))", table, table));
}

void CVideoDatabase::CreateAnalytics()
{
  /* indexes should be added on any columns that are used in in  */
  /* a where or a join. primary key on a column is the same as a */
  /* unique index on that column, so there is no need to add any */
  /* index if no other columns are refered                       */

  /* order of indexes are important, for an index to be considered all  */
  /* columns up to the column in question have to have been specified   */
  /* select * from foolink where foo_id = 1, can not take               */
  /* advantage of a index that has been created on ( bar_id, foo_id )   */
  /* however an index on ( foo_id, bar_id ) will be considered for use  */

  CLog::Log(LOGINFO, "%s - creating indices", __FUNCTION__);
  m_pDS->exec("CREATE INDEX ix_bookmark ON bookmark (idFile, type)");
  m_pDS->exec("CREATE UNIQUE INDEX ix_settings ON settings ( idFile )\n");
  m_pDS->exec("CREATE UNIQUE INDEX ix_stacktimes ON stacktimes ( idFile )\n");
  m_pDS->exec("CREATE INDEX ix_path ON path ( strPath(255) )");
  m_pDS->exec("CREATE INDEX ix_path2 ON path ( idParentPath )");
  m_pDS->exec("CREATE INDEX ix_files ON files ( idPath, strFilename(255) )");

  m_pDS->exec("CREATE UNIQUE INDEX ix_movie_file_1 ON movie (idFile, idMovie)");
  m_pDS->exec("CREATE UNIQUE INDEX ix_movie_file_2 ON movie (idMovie, idFile)");

  m_pDS->exec("CREATE UNIQUE INDEX ix_tvshowlinkpath_1 ON tvshowlinkpath ( idShow, idPath )\n");
  m_pDS->exec("CREATE UNIQUE INDEX ix_tvshowlinkpath_2 ON tvshowlinkpath ( idPath, idShow )\n");
  m_pDS->exec("CREATE UNIQUE INDEX ix_movielinktvshow_1 ON movielinktvshow ( idShow, idMovie)\n");
  m_pDS->exec("CREATE UNIQUE INDEX ix_movielinktvshow_2 ON movielinktvshow ( idMovie, idShow)\n");

  m_pDS->exec("CREATE UNIQUE INDEX ix_episode_file_1 on episode (idEpisode, idFile)");
  m_pDS->exec("CREATE UNIQUE INDEX id_episode_file_2 on episode (idFile, idEpisode)");
  std::string createColIndex = StringUtils::Format("CREATE INDEX ix_episode_season_episode on episode (c%02d, c%02d)", VIDEODB_ID_EPISODE_SEASON, VIDEODB_ID_EPISODE_EPISODE);
  m_pDS->exec(createColIndex);
  createColIndex = StringUtils::Format("CREATE INDEX ix_episode_bookmark on episode (c%02d)", VIDEODB_ID_EPISODE_BOOKMARK);
  m_pDS->exec(createColIndex);
  m_pDS->exec("CREATE INDEX ix_episode_show1 on episode(idEpisode,idShow)");
  m_pDS->exec("CREATE INDEX ix_episode_show2 on episode(idShow,idEpisode)");

  m_pDS->exec("CREATE UNIQUE INDEX ix_musicvideo_file_1 on musicvideo (idMVideo, idFile)");
  m_pDS->exec("CREATE UNIQUE INDEX ix_musicvideo_file_2 on musicvideo (idFile, idMVideo)");

  m_pDS->exec("CREATE INDEX ixMovieBasePath ON movie ( c23(12) )");
  m_pDS->exec("CREATE INDEX ixMusicVideoBasePath ON musicvideo ( c14(12) )");
  m_pDS->exec("CREATE INDEX ixEpisodeBasePath ON episode ( c19(12) )");

  m_pDS->exec("CREATE INDEX ix_streamdetails ON streamdetails (idFile)");
  m_pDS->exec("CREATE INDEX ix_seasons ON seasons (idShow, season)");
  m_pDS->exec("CREATE INDEX ix_art ON art(media_id, media_type(20), type(20))");

  m_pDS->exec("CREATE INDEX ix_rating ON rating(media_id, media_type(20))");

  m_pDS->exec("CREATE INDEX ix_uniqueid1 ON uniqueid(media_id, media_type(20), type(20))");
  m_pDS->exec("CREATE INDEX ix_uniqueid2 ON uniqueid(media_type(20), value(20))");

  CreateLinkIndex("tag");
  CreateLinkIndex("actor");
  CreateForeignLinkIndex("director", "actor");
  CreateForeignLinkIndex("writer", "actor");
  CreateLinkIndex("studio");
  CreateLinkIndex("genre");
  CreateLinkIndex("country");

  CLog::Log(LOGINFO, "%s - creating triggers", __FUNCTION__);
  m_pDS->exec("CREATE TRIGGER delete_movie AFTER DELETE ON movie FOR EACH ROW BEGIN "
              "DELETE FROM genre_link WHERE media_id=old.idMovie AND media_type='movie'; "
              "DELETE FROM actor_link WHERE media_id=old.idMovie AND media_type='movie'; "
              "DELETE FROM director_link WHERE media_id=old.idMovie AND media_type='movie'; "
              "DELETE FROM studio_link WHERE media_id=old.idMovie AND media_type='movie'; "
              "DELETE FROM country_link WHERE media_id=old.idMovie AND media_type='movie'; "
              "DELETE FROM writer_link WHERE media_id=old.idMovie AND media_type='movie'; "
              "DELETE FROM movielinktvshow WHERE idMovie=old.idMovie; "
              "DELETE FROM art WHERE media_id=old.idMovie AND media_type='movie'; "
              "DELETE FROM tag_link WHERE media_id=old.idMovie AND media_type='movie'; "
              "DELETE FROM rating WHERE media_id=old.idMovie AND media_type='movie'; "
              "DELETE FROM uniqueid WHERE media_id=old.idMovie AND media_type='movie'; "
              "END");
  m_pDS->exec("CREATE TRIGGER delete_tvshow AFTER DELETE ON tvshow FOR EACH ROW BEGIN "
              "DELETE FROM actor_link WHERE media_id=old.idShow AND media_type='tvshow'; "
              "DELETE FROM director_link WHERE media_id=old.idShow AND media_type='tvshow'; "
              "DELETE FROM studio_link WHERE media_id=old.idShow AND media_type='tvshow'; "
              "DELETE FROM tvshowlinkpath WHERE idShow=old.idShow; "
              "DELETE FROM genre_link WHERE media_id=old.idShow AND media_type='tvshow'; "
              "DELETE FROM movielinktvshow WHERE idShow=old.idShow; "
              "DELETE FROM seasons WHERE idShow=old.idShow; "
              "DELETE FROM art WHERE media_id=old.idShow AND media_type='tvshow'; "
              "DELETE FROM tag_link WHERE media_id=old.idShow AND media_type='tvshow'; "
              "DELETE FROM rating WHERE media_id=old.idShow AND media_type='tvshow'; "
              "DELETE FROM uniqueid WHERE media_id=old.idShow AND media_type='tvshow'; "
              "END");
  m_pDS->exec("CREATE TRIGGER delete_musicvideo AFTER DELETE ON musicvideo FOR EACH ROW BEGIN "
              "DELETE FROM actor_link WHERE media_id=old.idMVideo AND media_type='musicvideo'; "
              "DELETE FROM director_link WHERE media_id=old.idMVideo AND media_type='musicvideo'; "
              "DELETE FROM genre_link WHERE media_id=old.idMVideo AND media_type='musicvideo'; "
              "DELETE FROM studio_link WHERE media_id=old.idMVideo AND media_type='musicvideo'; "
              "DELETE FROM art WHERE media_id=old.idMVideo AND media_type='musicvideo'; "
              "DELETE FROM tag_link WHERE media_id=old.idMVideo AND media_type='musicvideo'; "
              "END");
  m_pDS->exec("CREATE TRIGGER delete_episode AFTER DELETE ON episode FOR EACH ROW BEGIN "
              "DELETE FROM actor_link WHERE media_id=old.idEpisode AND media_type='episode'; "
              "DELETE FROM director_link WHERE media_id=old.idEpisode AND media_type='episode'; "
              "DELETE FROM writer_link WHERE media_id=old.idEpisode AND media_type='episode'; "
              "DELETE FROM art WHERE media_id=old.idEpisode AND media_type='episode'; "
              "DELETE FROM rating WHERE media_id=old.idEpisode AND media_type='episode'; "
              "DELETE FROM uniqueid WHERE media_id=old.idEpisode AND media_type='episode'; "
              "END");
  m_pDS->exec("CREATE TRIGGER delete_season AFTER DELETE ON seasons FOR EACH ROW BEGIN "
              "DELETE FROM art WHERE media_id=old.idSeason AND media_type='season'; "
              "END");
  m_pDS->exec("CREATE TRIGGER delete_set AFTER DELETE ON sets FOR EACH ROW BEGIN "
              "DELETE FROM art WHERE media_id=old.idSet AND media_type='set'; "
              "END");
  m_pDS->exec("CREATE TRIGGER delete_person AFTER DELETE ON actor FOR EACH ROW BEGIN "
              "DELETE FROM art WHERE media_id=old.actor_id AND media_type IN ('actor','artist','writer','director'); "
              "END");
  m_pDS->exec("CREATE TRIGGER delete_tag AFTER DELETE ON tag_link FOR EACH ROW BEGIN "
              "DELETE FROM tag WHERE tag_id=old.tag_id AND tag_id NOT IN (SELECT DISTINCT tag_id FROM tag_link); "
              "END");
  m_pDS->exec("CREATE TRIGGER delete_file AFTER DELETE ON files FOR EACH ROW BEGIN "
              "DELETE FROM bookmark WHERE idFile=old.idFile; "
              "DELETE FROM settings WHERE idFile=old.idFile; "
              "DELETE FROM stacktimes WHERE idFile=old.idFile; "
              "DELETE FROM streamdetails WHERE idFile=old.idFile; "
              "END");

  CreateViews();
}

void CVideoDatabase::CreateViews()
{
  CLog::Log(LOGINFO, "create episode_view");
  std::string episodeview = PrepareSQL("CREATE VIEW episode_view AS SELECT "
                                      "  episode.*,"
                                      "  files.strFileName AS strFileName,"
                                      "  path.strPath AS strPath,"
                                      "  files.playCount AS playCount,"
                                      "  files.lastPlayed AS lastPlayed,"
                                      "  files.dateAdded AS dateAdded,"
                                      "  tvshow.c%02d AS strTitle,"
                                      "  tvshow.c%02d AS genre,"
                                      "  tvshow.c%02d AS studio,"
                                      "  tvshow.c%02d AS premiered,"
                                      "  tvshow.c%02d AS mpaa,"
                                      "  bookmark.timeInSeconds AS resumeTimeInSeconds, "
                                      "  bookmark.totalTimeInSeconds AS totalTimeInSeconds, "
                                      "  bookmark.playerState AS playerState, "
                                      "  rating.rating AS rating, "
                                      "  rating.votes AS votes, "
                                      "  rating.rating_type AS rating_type, "
                                      "  uniqueid.value AS uniqueid_value, "
                                      "  uniqueid.type AS uniqueid_type "
                                      "FROM episode"
                                      "  JOIN files ON"
                                      "    files.idFile=episode.idFile"
                                      "  JOIN tvshow ON"
                                      "    tvshow.idShow=episode.idShow"
                                      "  JOIN seasons ON"
                                      "    seasons.idSeason=episode.idSeason"
                                      "  JOIN path ON"
                                      "    files.idPath=path.idPath"
                                      "  LEFT JOIN bookmark ON"
                                      "    bookmark.idFile=episode.idFile AND bookmark.type=1"
                                      "  LEFT JOIN rating ON"
                                      "    rating.rating_id=episode.c%02d"
                                      "  LEFT JOIN uniqueid ON"
                                      "    uniqueid.uniqueid_id=episode.c%02d",
                                      VIDEODB_ID_TV_TITLE, VIDEODB_ID_TV_GENRE,
                                      VIDEODB_ID_TV_STUDIOS, VIDEODB_ID_TV_PREMIERED,
                                      VIDEODB_ID_TV_MPAA, VIDEODB_ID_EPISODE_RATING_ID,
                                      VIDEODB_ID_EPISODE_IDENT_ID);
  m_pDS->exec(episodeview);

  CLog::Log(LOGINFO, "create tvshowcounts");
  std::string tvshowcounts = PrepareSQL("CREATE VIEW tvshowcounts AS SELECT "
                                       "      tvshow.idShow AS idShow,"
                                       "      MAX(files.lastPlayed) AS lastPlayed,"
                                       "      NULLIF(COUNT(episode.c12), 0) AS totalCount,"
                                       "      COUNT(files.playCount) AS watchedcount,"
                                       "      NULLIF(COUNT(DISTINCT(episode.c12)), 0) AS totalSeasons, "
                                       "      MAX(files.dateAdded) as dateAdded "
                                       "    FROM tvshow"
                                       "      LEFT JOIN episode ON"
                                       "        episode.idShow=tvshow.idShow"
                                       "      LEFT JOIN files ON"
                                       "        files.idFile=episode.idFile "
                                       "GROUP BY tvshow.idShow");
  m_pDS->exec(tvshowcounts);

  CLog::Log(LOGINFO, "create tvshowlinkpath_minview");
  // This view only exists to workaround a limitation in MySQL <5.7 which is not able to
  // perform subqueries in joins.
  // Also, the correct solution is to remove the path information altogether, since a
  // TV series can always have multiple paths. It is used in the GUI at the moment, but
  // such usage should be removed together with this view and the path columns in tvshow_view.
  //!@todo Remove the hacky selection of a semi-random path for tvshows from the queries and UI
  std::string tvshowlinkpathview = PrepareSQL("CREATE VIEW tvshowlinkpath_minview AS SELECT "
                                             "  idShow, "
                                             "  min(idPath) AS idPath "
                                             "FROM tvshowlinkpath "
                                             "GROUP BY idShow");
  m_pDS->exec(tvshowlinkpathview);

  CLog::Log(LOGINFO, "create tvshow_view");
  std::string tvshowview = PrepareSQL("CREATE VIEW tvshow_view AS SELECT "
                                     "  tvshow.*,"
                                     "  path.idParentPath AS idParentPath,"
                                     "  path.strPath AS strPath,"
                                     "  tvshowcounts.dateAdded AS dateAdded,"
                                     "  lastPlayed, totalCount, watchedcount, totalSeasons, "
                                     "  rating.rating AS rating, "
                                     "  rating.votes AS votes, "
                                     "  rating.rating_type AS rating_type, "
                                     "  uniqueid.value AS uniqueid_value, "
                                     "  uniqueid.type AS uniqueid_type "
                                     "FROM tvshow"
                                     "  LEFT JOIN tvshowlinkpath_minview ON "
                                     "    tvshowlinkpath_minview.idShow=tvshow.idShow"
                                     "  LEFT JOIN path ON"
                                     "    path.idPath=tvshowlinkpath_minview.idPath"
                                     "  INNER JOIN tvshowcounts ON"
                                     "    tvshow.idShow = tvshowcounts.idShow "
                                     "  LEFT JOIN rating ON"
                                     "    rating.rating_id=tvshow.c%02d "
                                     "  LEFT JOIN uniqueid ON"
                                     "    uniqueid.uniqueid_id=tvshow.c%02d ",
                                     VIDEODB_ID_TV_RATING_ID, VIDEODB_ID_TV_IDENT_ID);
  m_pDS->exec(tvshowview);
  
  CLog::Log(LOGINFO, "create season_view");
  std::string seasonview = PrepareSQL("CREATE VIEW season_view AS SELECT "
                                     "  seasons.idSeason AS idSeason,"
                                     "  seasons.idShow AS idShow,"
                                     "  seasons.season AS season,"
                                     "  seasons.name AS name,"
                                     "  seasons.userrating AS userrating,"
                                     "  tvshow_view.strPath AS strPath,"
                                     "  tvshow_view.c%02d AS showTitle,"
                                     "  tvshow_view.c%02d AS plot,"
                                     "  tvshow_view.c%02d AS premiered,"
                                     "  tvshow_view.c%02d AS genre,"
                                     "  tvshow_view.c%02d AS studio,"
                                     "  tvshow_view.c%02d AS mpaa,"
                                     "  count(DISTINCT episode.idEpisode) AS episodes,"
                                     "  count(files.playCount) AS playCount,"
                                     "  min(episode.c%02d) AS aired "
                                     "FROM seasons"
                                     "  JOIN tvshow_view ON"
                                     "    tvshow_view.idShow = seasons.idShow"
                                     "  JOIN episode ON"
                                     "    episode.idShow = seasons.idShow AND episode.c%02d = seasons.season"
                                     "  JOIN files ON"
                                     "    files.idFile = episode.idFile "
                                     "GROUP BY seasons.idSeason,"
                                     "         seasons.idShow,"
                                     "         seasons.season,"
                                     "         seasons.name,"
                                     "         seasons.userrating,"
                                     "         tvshow_view.strPath,"
                                     "         tvshow_view.c%02d,"
                                     "         tvshow_view.c%02d,"
                                     "         tvshow_view.c%02d,"
                                     "         tvshow_view.c%02d,"
                                     "         tvshow_view.c%02d,"
                                     "         tvshow_view.c%02d ",
                                     VIDEODB_ID_TV_TITLE, VIDEODB_ID_TV_PLOT, VIDEODB_ID_TV_PREMIERED,
                                     VIDEODB_ID_TV_GENRE, VIDEODB_ID_TV_STUDIOS, VIDEODB_ID_TV_MPAA,
                                     VIDEODB_ID_EPISODE_AIRED, VIDEODB_ID_EPISODE_SEASON,
                                     VIDEODB_ID_TV_TITLE, VIDEODB_ID_TV_PLOT, VIDEODB_ID_TV_PREMIERED,
                                     VIDEODB_ID_TV_GENRE, VIDEODB_ID_TV_STUDIOS, VIDEODB_ID_TV_MPAA);
  m_pDS->exec(seasonview);

  CLog::Log(LOGINFO, "create musicvideo_view");
  m_pDS->exec("CREATE VIEW musicvideo_view AS SELECT"
              "  musicvideo.*,"
              "  files.strFileName as strFileName,"
              "  path.strPath as strPath,"
              "  files.playCount as playCount,"
              "  files.lastPlayed as lastPlayed,"
              "  files.dateAdded as dateAdded, "
              "  bookmark.timeInSeconds AS resumeTimeInSeconds, "
              "  bookmark.totalTimeInSeconds AS totalTimeInSeconds, "
              "  bookmark.playerState AS playerState "
              "FROM musicvideo"
              "  JOIN files ON"
              "    files.idFile=musicvideo.idFile"
              "  JOIN path ON"
              "    path.idPath=files.idPath"
              "  LEFT JOIN bookmark ON"
              "    bookmark.idFile=musicvideo.idFile AND bookmark.type=1");

  CLog::Log(LOGINFO, "create movie_view");

  std::string movieview = PrepareSQL("CREATE VIEW movie_view AS SELECT"
                                      "  movie.*,"
                                      "  sets.strSet AS strSet,"
                                      "  sets.strOverview AS strSetOverview,"
                                      "  files.strFileName AS strFileName,"
                                      "  path.strPath AS strPath,"
                                      "  files.playCount AS playCount,"
                                      "  files.lastPlayed AS lastPlayed, "
                                      "  files.dateAdded AS dateAdded, "
                                      "  bookmark.timeInSeconds AS resumeTimeInSeconds, "
                                      "  bookmark.totalTimeInSeconds AS totalTimeInSeconds, "
                                      "  bookmark.playerState AS playerState, "
                                      "  rating.rating AS rating, "
                                      "  rating.votes AS votes, "
                                      "  rating.rating_type AS rating_type, "
                                      "  uniqueid.value AS uniqueid_value, "
                                      "  uniqueid.type AS uniqueid_type "
                                      "FROM movie"
                                      "  LEFT JOIN sets ON"
                                      "    sets.idSet = movie.idSet"
                                      "  JOIN files ON"
                                      "    files.idFile=movie.idFile"
                                      "  JOIN path ON"
                                      "    path.idPath=files.idPath"
                                      "  LEFT JOIN bookmark ON"
                                      "    bookmark.idFile=movie.idFile AND bookmark.type=1"
                                      "  LEFT JOIN rating ON"
                                      "    rating.rating_id=movie.c%02d"
                                      "  LEFT JOIN uniqueid ON"
                                      "    uniqueid.uniqueid_id=movie.c%02d",
                                      VIDEODB_ID_RATING_ID, VIDEODB_ID_IDENT_ID);
  m_pDS->exec(movieview);
}

//********************************************************************************************************************************
int CVideoDatabase::GetPathId(const std::string& strPath)
{
  std::string strSQL;
  try
  {
    int idPath=-1;
    if (NULL == m_pDB.get()) return -1;
    if (NULL == m_pDS.get()) return -1;

    std::string strPath1(strPath);
    if (URIUtils::IsStack(strPath) || StringUtils::StartsWithNoCase(strPath, "rar://") || StringUtils::StartsWithNoCase(strPath, "zip://"))
      URIUtils::GetParentPath(strPath,strPath1);

    URIUtils::AddSlashAtEnd(strPath1);

    strSQL=PrepareSQL("select idPath from path where strPath='%s'",strPath1.c_str());
    m_pDS->query(strSQL);
    if (!m_pDS->eof())
      idPath = m_pDS->fv("path.idPath").get_asInt();

    m_pDS->close();
    return idPath;
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s unable to getpath (%s)", __FUNCTION__, strSQL.c_str());
  }
  return -1;
}

bool CVideoDatabase::GetPaths(std::set<std::string> &paths)
{
  try
  {
    if (NULL == m_pDB.get()) return false;
    if (NULL == m_pDS.get()) return false;

    paths.clear();

    // grab all paths with movie content set
    if (!m_pDS->query("select strPath,noUpdate from path"
                      " where (strContent = 'movies' or strContent = 'musicvideos')"
                      " and strPath NOT like 'multipath://%%'"
                      " order by strPath"))
      return false;

    while (!m_pDS->eof())
    {
      if (!m_pDS->fv("noUpdate").get_asBool())
        paths.insert(m_pDS->fv("strPath").get_asString());
      m_pDS->next();
    }
    m_pDS->close();

    // then grab all tvshow paths
    if (!m_pDS->query("select strPath,noUpdate from path"
                      " where ( strContent = 'tvshows'"
                      "       or idPath in (select idPath from tvshowlinkpath))"
                      " and strPath NOT like 'multipath://%%'"
                      " order by strPath"))
      return false;

    while (!m_pDS->eof())
    {
      if (!m_pDS->fv("noUpdate").get_asBool())
        paths.insert(m_pDS->fv("strPath").get_asString());
      m_pDS->next();
    }
    m_pDS->close();

    // finally grab all other paths holding a movie which is not a stack or a rar archive
    // - this isnt perfect but it should do fine in most situations.
    // reason we need it to hold a movie is stacks from different directories (cdx folders for instance)
    // not making mistakes must take priority
    if (!m_pDS->query("select strPath,noUpdate from path"
                       " where idPath in (select idPath from files join movie on movie.idFile=files.idFile)"
                       " and idPath NOT in (select idPath from tvshowlinkpath)"
                       " and idPath NOT in (select idPath from files where strFileName like 'video_ts.ifo')" // dvd folders get stacked to a single item in parent folder
                       " and idPath NOT in (select idPath from files where strFileName like 'index.bdmv')" // bluray folders get stacked to a single item in parent folder
                       " and strPath NOT like 'multipath://%%'"
                       " and strContent NOT in ('movies', 'tvshows', 'None')" // these have been added above
                       " order by strPath"))

      return false;
    while (!m_pDS->eof())
    {
      if (!m_pDS->fv("noUpdate").get_asBool())
        paths.insert(m_pDS->fv("strPath").get_asString());
      m_pDS->next();
    }
    m_pDS->close();
    return true;
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s failed", __FUNCTION__);
  }
  return false;
}

bool CVideoDatabase::GetPathsLinkedToTvShow(int idShow, std::vector<std::string> &paths)
{
  std::string sql;
  try
  {
    sql = PrepareSQL("SELECT strPath FROM path JOIN tvshowlinkpath ON tvshowlinkpath.idPath=path.idPath WHERE idShow=%i", idShow);
    m_pDS->query(sql);
    while (!m_pDS->eof())
    {
      paths.emplace_back(m_pDS->fv(0).get_asString());
      m_pDS->next();
    }
    return true;
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s error during query: %s",__FUNCTION__, sql.c_str());
  }
  return false;
}

bool CVideoDatabase::GetPathsForTvShow(int idShow, std::set<int>& paths)
{
  std::string strSQL;
  try
  {
    if (NULL == m_pDB.get()) return false;
    if (NULL == m_pDS.get()) return false;

    // add base path
    strSQL = PrepareSQL("SELECT strPath FROM tvshow_view WHERE idShow=%i", idShow);
    if (m_pDS->query(strSQL))
      paths.insert(GetPathId(m_pDS->fv(0).get_asString()));

    // add all other known paths
    strSQL = PrepareSQL("SELECT DISTINCT idPath FROM files JOIN episode ON episode.idFile=files.idFile WHERE episode.idShow=%i",idShow);
    m_pDS->query(strSQL);
    while (!m_pDS->eof())
    {
      paths.insert(m_pDS->fv(0).get_asInt());
      m_pDS->next();
    }
    m_pDS->close();
    return true;
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s error during query: %s",__FUNCTION__, strSQL.c_str());
  }
  return false;
}

int CVideoDatabase::RunQuery(const std::string &sql)
{
  unsigned int time = XbmcThreads::SystemClockMillis();
  int rows = -1;
  if (m_pDS->query(sql))
  {
    rows = m_pDS->num_rows();
    if (rows == 0)
      m_pDS->close();
  }
  CLog::Log(LOGDEBUG, LOGDATABASE, "%s took %d ms for %d items query: %s", __FUNCTION__, XbmcThreads::SystemClockMillis() - time, rows, sql.c_str());
  return rows;
}

bool CVideoDatabase::GetSubPaths(const std::string &basepath, std::vector<std::pair<int, std::string>>& subpaths)
{
  std::string sql;
  try
  {
    if (!m_pDB.get() || !m_pDS.get())
      return false;

    std::string path(basepath);
    URIUtils::AddSlashAtEnd(path);
    sql = PrepareSQL("SELECT idPath,strPath FROM path WHERE SUBSTR(strPath,1,%i)='%s'"
                     " AND idPath NOT IN (SELECT idPath FROM files WHERE strFileName LIKE 'video_ts.ifo')"
                     " AND idPath NOT IN (SELECT idPath FROM files WHERE strFileName LIKE 'index.bdmv')"
                     , StringUtils::utf8_strlen(path.c_str()), path.c_str());

    m_pDS->query(sql);
    while (!m_pDS->eof())
    {
      subpaths.emplace_back(m_pDS->fv(0).get_asInt(), m_pDS->fv(1).get_asString());
      m_pDS->next();
    }
    m_pDS->close();
    return true;
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s error during query: %s",__FUNCTION__, sql.c_str());
  }
  return false;
}

int CVideoDatabase::AddPath(const std::string& strPath, const std::string &parentPath /*= "" */, const CDateTime& dateAdded /* = CDateTime() */)
{
  std::string strSQL;
  try
  {
    int idPath = GetPathId(strPath);
    if (idPath >= 0)
      return idPath; // already have the path

    if (NULL == m_pDB.get()) return -1;
    if (NULL == m_pDS.get()) return -1;

    std::string strPath1(strPath);
    if (URIUtils::IsStack(strPath) || StringUtils::StartsWithNoCase(strPath, "rar://") || StringUtils::StartsWithNoCase(strPath, "zip://"))
      URIUtils::GetParentPath(strPath,strPath1);

    URIUtils::AddSlashAtEnd(strPath1);

    int idParentPath = GetPathId(parentPath.empty() ? URIUtils::GetParentPath(strPath1) : parentPath);

    // add the path
    if (idParentPath < 0)
    {
      if (dateAdded.IsValid())
        strSQL=PrepareSQL("insert into path (idPath, strPath, dateAdded) values (NULL, '%s', '%s')", strPath1.c_str(), dateAdded.GetAsDBDateTime().c_str());
      else
        strSQL=PrepareSQL("insert into path (idPath, strPath) values (NULL, '%s')", strPath1.c_str());
    }
    else
    {
      if (dateAdded.IsValid())
        strSQL = PrepareSQL("insert into path (idPath, strPath, dateAdded, idParentPath) values (NULL, '%s', '%s', %i)", strPath1.c_str(), dateAdded.GetAsDBDateTime().c_str(), idParentPath);
      else
        strSQL=PrepareSQL("insert into path (idPath, strPath, idParentPath) values (NULL, '%s', %i)", strPath1.c_str(), idParentPath);
    }
    m_pDS->exec(strSQL);
    idPath = (int)m_pDS->lastinsertid();
    return idPath;
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s unable to addpath (%s)", __FUNCTION__, strSQL.c_str());
  }
  return -1;
}

bool CVideoDatabase::GetPathHash(const std::string &path, std::string &hash)
{
  try
  {
    if (NULL == m_pDB.get()) return false;
    if (NULL == m_pDS.get()) return false;

    std::string strSQL=PrepareSQL("select strHash from path where strPath='%s'", path.c_str());
    m_pDS->query(strSQL);
    if (m_pDS->num_rows() == 0)
      return false;
    hash = m_pDS->fv("strHash").get_asString();
    return true;
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (%s) failed", __FUNCTION__, path.c_str());
  }

  return false;
}

bool CVideoDatabase::GetSourcePath(const std::string &path, std::string &sourcePath)
{
  SScanSettings dummy;
  return GetSourcePath(path, sourcePath, dummy);
}

bool CVideoDatabase::GetSourcePath(const std::string &path, std::string &sourcePath, SScanSettings& settings)
{
  try
  {
    if (path.empty() ||
        m_pDB.get() == NULL || m_pDS.get() == NULL)
      return false;

    std::string strPath2;

    if (URIUtils::IsMultiPath(path))
      strPath2 = CMultiPathDirectory::GetFirstPath(path);
    else
      strPath2 = path;

    std::string strPath1 = URIUtils::GetDirectory(strPath2);
    int idPath = GetPathId(strPath1);

    if (idPath > -1)
    {
      // check if the given path already is a source itself
      std::string strSQL = PrepareSQL("SELECT path.useFolderNames, path.scanRecursive, path.noUpdate, path.exclude FROM path WHERE "
                                        "path.idPath = %i AND "
                                        "path.strContent IS NOT NULL AND path.strContent != '' AND "
                                        "path.strScraper IS NOT NULL AND path.strScraper != ''", idPath);
      if (m_pDS->query(strSQL) && !m_pDS->eof())
      {
        settings.parent_name_root = settings.parent_name = m_pDS->fv(0).get_asBool();
        settings.recurse = m_pDS->fv(1).get_asInt();
        settings.noupdate = m_pDS->fv(2).get_asBool();
        settings.exclude = m_pDS->fv(3).get_asBool();

        m_pDS->close();
        sourcePath = path;
        return true;
      }
    }

    // look for parent paths until there is one which is a source
    std::string strParent;
    bool found = false;
    while (URIUtils::GetParentPath(strPath1, strParent))
    {
      std::string strSQL = PrepareSQL("SELECT path.strContent, path.strScraper, path.scanRecursive, path.useFolderNames, path.noUpdate, path.exclude FROM path WHERE strPath = '%s'", strParent.c_str());
      if (m_pDS->query(strSQL) && !m_pDS->eof())
      {
        std::string strContent = m_pDS->fv(0).get_asString();
        std::string strScraper = m_pDS->fv(1).get_asString();
        if (!strContent.empty() && !strScraper.empty())
        {
          settings.parent_name_root = settings.parent_name = m_pDS->fv(2).get_asBool();
          settings.recurse = m_pDS->fv(3).get_asInt();
          settings.noupdate = m_pDS->fv(4).get_asBool();
          settings.exclude = m_pDS->fv(5).get_asBool();
          found = true;
          break;
        }
      }

      strPath1 = strParent;
    }
    m_pDS->close();

    if (found)
    {
      sourcePath = strParent;
      return true;
    }
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s failed", __FUNCTION__);
  }
  return false;
}

//********************************************************************************************************************************
int CVideoDatabase::AddFile(const std::string& strFileNameAndPath)
{
  std::string strSQL = "";
  try
  {
    int idFile;
    if (NULL == m_pDB.get()) return -1;
    if (NULL == m_pDS.get()) return -1;

    std::string strFileName, strPath;
    SplitPath(strFileNameAndPath,strPath,strFileName);

    int idPath = AddPath(strPath);
    if (idPath < 0)
      return -1;

    std::string strSQL=PrepareSQL("select idFile from files where strFileName='%s' and idPath=%i", strFileName.c_str(),idPath);

    m_pDS->query(strSQL);
    if (m_pDS->num_rows() > 0)
    {
      idFile = m_pDS->fv("idFile").get_asInt() ;
      m_pDS->close();
      return idFile;
    }
    m_pDS->close();

    strSQL=PrepareSQL("insert into files (idFile, idPath, strFileName) values(NULL, %i, '%s')", idPath, strFileName.c_str());
    m_pDS->exec(strSQL);
    idFile = (int)m_pDS->lastinsertid();
    return idFile;
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s unable to addfile (%s)", __FUNCTION__, strSQL.c_str());
  }
  return -1;
}

int CVideoDatabase::AddFile(const CFileItem& item)
{
  if (item.IsVideoDb() && item.HasVideoInfoTag())
  {
    if (item.GetVideoInfoTag()->m_iFileId != -1)
      return item.GetVideoInfoTag()->m_iFileId;
    else
      return AddFile(item.GetVideoInfoTag()->m_strFileNameAndPath);
  }
  return AddFile(item.GetPath());
}

void CVideoDatabase::UpdateFileDateAdded(int idFile, const std::string& strFileNameAndPath, const CDateTime& dateAdded /* = CDateTime() */)
{
  if (idFile < 0 || strFileNameAndPath.empty())
    return;

  CDateTime finalDateAdded = dateAdded;
  try
  {
    if (NULL == m_pDB.get()) return;
    if (NULL == m_pDS.get()) return;

    if (!finalDateAdded.IsValid())
    {
      // Supress warnings if we have plugin source
      if (!URIUtils::IsPlugin(strFileNameAndPath))
      {
        // 1 preferring to use the files mtime(if it's valid) and only using the file's ctime if the mtime isn't valid
        if (CServiceBroker::GetSettingsComponent()->GetAdvancedSettings()->m_iVideoLibraryDateAdded == 1)
          finalDateAdded = CFileUtils::GetModificationDate(strFileNameAndPath, false);
        //2 using the newer datetime of the file's mtime and ctime
        else if (CServiceBroker::GetSettingsComponent()->GetAdvancedSettings()->m_iVideoLibraryDateAdded == 2)
          finalDateAdded = CFileUtils::GetModificationDate(strFileNameAndPath, true);
      }
      //0 using the current datetime if non of the above matches or one returns an invalid datetime
      if (!finalDateAdded.IsValid())
        finalDateAdded = CDateTime::GetCurrentDateTime();
    }

    m_pDS->exec(PrepareSQL("UPDATE files SET dateAdded='%s' WHERE idFile=%d", finalDateAdded.GetAsDBDateTime().c_str(), idFile));
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (%s, %s) failed", __FUNCTION__, CURL::GetRedacted(strFileNameAndPath).c_str(), finalDateAdded.GetAsDBDateTime().c_str());
  }
}

bool CVideoDatabase::SetPathHash(const std::string &path, const std::string &hash)
{
  try
  {
    if (NULL == m_pDB.get()) return false;
    if (NULL == m_pDS.get()) return false;

    int idPath = AddPath(path);
    if (idPath < 0) return false;

    std::string strSQL=PrepareSQL("update path set strHash='%s' where idPath=%ld", hash.c_str(), idPath);
    m_pDS->exec(strSQL);

    return true;
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (%s, %s) failed", __FUNCTION__, path.c_str(), hash.c_str());
  }

  return false;
}

//********************************************************************************************************************************
int CVideoDatabase::GetFileId(const std::string& strFilenameAndPath)
{
  try
  {
    if (NULL == m_pDB.get()) return -1;
    if (NULL == m_pDS.get()) return -1;
    std::string strPath, strFileName;
    SplitPath(strFilenameAndPath,strPath,strFileName);

    int idPath = GetPathId(strPath);
    if (idPath >= 0)
    {
      std::string strSQL;
      strSQL=PrepareSQL("select idFile from files where strFileName='%s' and idPath=%i", strFileName.c_str(),idPath);
      m_pDS->query(strSQL);
      if (m_pDS->num_rows() > 0)
      {
        int idFile = m_pDS->fv("files.idFile").get_asInt();
        m_pDS->close();
        return idFile;
      }
    }
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (%s) failed", __FUNCTION__, strFilenameAndPath.c_str());
  }
  return -1;
}

int CVideoDatabase::GetFileId(const CFileItem &item)
{
  if (item.IsVideoDb() && item.HasVideoInfoTag())
  {
    if (item.GetVideoInfoTag()->m_iFileId != -1)
      return item.GetVideoInfoTag()->m_iFileId;
    else
      return GetFileId(item.GetVideoInfoTag()->m_strFileNameAndPath);
  }
  return GetFileId(item.GetPath());
}

int CVideoDatabase::GetTvShowId(const std::string& strPath)
{
  try
  {
    if (NULL == m_pDB.get()) return -1;
    if (NULL == m_pDS.get()) return -1;
    int idTvShow = -1;

    // have to join movieinfo table for correct results
    int idPath = GetPathId(strPath);
    if (idPath < 0)
      return -1;

    std::string strSQL;
    std::string strPath1=strPath;
    std::string strParent;
    int iFound=0;

    strSQL=PrepareSQL("select idShow from tvshowlinkpath where tvshowlinkpath.idPath=%i",idPath);
    m_pDS->query(strSQL);
    if (!m_pDS->eof())
      iFound = 1;

    while (iFound == 0 && URIUtils::GetParentPath(strPath1, strParent))
    {
      strSQL=PrepareSQL("SELECT idShow FROM path INNER JOIN tvshowlinkpath ON tvshowlinkpath.idPath=path.idPath WHERE strPath='%s'",strParent.c_str());
      m_pDS->query(strSQL);
      if (!m_pDS->eof())
      {
        int idShow = m_pDS->fv("idShow").get_asInt();
        if (idShow != -1)
          iFound = 2;
      }
      strPath1 = strParent;
    }

    if (m_pDS->num_rows() > 0)
      idTvShow = m_pDS->fv("idShow").get_asInt();
    m_pDS->close();

    return idTvShow;
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (%s) failed", __FUNCTION__, strPath.c_str());
  }
  return -1;
}

bool CVideoDatabase::AddPathToTvShow(int idShow, const std::string &path, const std::string &parentPath, const CDateTime& dateAdded /* = CDateTime() */)
{
  // Check if this path is already added
  int idPath = GetPathId(path);
  if (idPath < 0)
  {
    CDateTime finalDateAdded = dateAdded;
    // Skip looking at the files ctime/mtime if defined by the user through as.xml
    if (!finalDateAdded.IsValid() && CServiceBroker::GetSettingsComponent()->GetAdvancedSettings()->m_iVideoLibraryDateAdded > 0)
    {
      struct __stat64 buffer;
      if (XFILE::CFile::Stat(path, &buffer) == 0)
      {
        time_t now = time(NULL);
        // Make sure we have a valid date (i.e. not in the future)
        if ((time_t)buffer.st_ctime <= now)
        {
          struct tm *time;
#ifdef HAVE_LOCALTIME_R
          struct tm result = {};
          time = localtime_r((const time_t*)&buffer.st_ctime, &result);
#else
          time = localtime((const time_t*)&buffer.st_ctime);
#endif
          if (time)
            finalDateAdded = *time;
        }
      }
    }

    if (!finalDateAdded.IsValid())
      finalDateAdded = CDateTime::GetCurrentDateTime();

    idPath = AddPath(path, parentPath, finalDateAdded);
  }

  return ExecuteQuery(PrepareSQL("REPLACE INTO tvshowlinkpath(idShow, idPath) VALUES (%i,%i)", idShow, idPath));
}

int CVideoDatabase::AddTvShow()
{
  if (ExecuteQuery("INSERT INTO tvshow(idShow) VALUES(NULL)"))
    return (int)m_pDS->lastinsertid();
  return -1;
}

//********************************************************************************************************************************
int CVideoDatabase::AddToTable(const std::string& table, const std::string& firstField, const std::string& secondField, const std::string& value)
{
  try
  {
    if (NULL == m_pDB.get()) return -1;
    if (NULL == m_pDS.get()) return -1;

    std::string strSQL = PrepareSQL("select %s from %s where %s like '%s'", firstField.c_str(), table.c_str(), secondField.c_str(), value.substr(0, 255).c_str());
    m_pDS->query(strSQL);
    if (m_pDS->num_rows() == 0)
    {
      m_pDS->close();
      // doesnt exists, add it
      strSQL = PrepareSQL("insert into %s (%s, %s) values(NULL, '%s')", table.c_str(), firstField.c_str(), secondField.c_str(), value.substr(0, 255).c_str());
      m_pDS->exec(strSQL);
      int id = (int)m_pDS->lastinsertid();
      return id;
    }
    else
    {
      int id = m_pDS->fv(firstField.c_str()).get_asInt();
      m_pDS->close();
      return id;
    }
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (%s) failed", __FUNCTION__, value.c_str() );
  }

  return -1;
}

int CVideoDatabase::UpdateUniqueIDs(int mediaId, const char *mediaType, const CVideoInfoTag& details)
{
  try
  {
    if (NULL == m_pDB.get()) return -1;
    if (NULL == m_pDS.get()) return -1;

    std::string sql = PrepareSQL("DELETE FROM uniqueid WHERE media_id=%i AND media_type='%s'", mediaId, mediaType);
    m_pDS->exec(sql);

    return AddUniqueIDs(mediaId, mediaType, details);
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s unable to update unique ids of (%s)", __FUNCTION__, mediaType);
  }
  return -1;
}

int CVideoDatabase::AddUniqueIDs(int mediaId, const char *mediaType, const CVideoInfoTag& details)
{
  int uniqueid = -1;
  try
  {
    if (NULL == m_pDB.get()) return -1;
    if (NULL == m_pDS.get()) return -1;

    for (const auto& i : details.GetUniqueIDs())
    {
      int id;
      std::string strSQL = PrepareSQL("SELECT uniqueid_id FROM uniqueid WHERE media_id=%i AND media_type='%s' AND type = '%s'", mediaId, mediaType, i.first.c_str());
      m_pDS->query(strSQL);
      if (m_pDS->num_rows() == 0)
      {
        m_pDS->close();
        // doesnt exists, add it
        strSQL = PrepareSQL("INSERT INTO uniqueid (media_id, media_type, value, type) VALUES (%i, '%s', '%s', '%s')", mediaId, mediaType, i.second.c_str(), i.first.c_str());
        m_pDS->exec(strSQL);
        id = (int)m_pDS->lastinsertid();
      }
      else
      {
        id = m_pDS->fv(0).get_asInt();
        m_pDS->close();
        strSQL = PrepareSQL("UPDATE uniqueid SET value = '%s', type = '%s' WHERE uniqueid_id = %i", i.second.c_str(), i.first.c_str(), id);
        m_pDS->exec(strSQL);
      }
      if (i.first == details.GetDefaultUniqueID())
        uniqueid = id;
    }
    return uniqueid;

  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (%i - %s) failed", __FUNCTION__, mediaId, mediaType);
  }

  return uniqueid;
}

int CVideoDatabase::AddActor(const std::string& name, const std::string& thumbURLs, const std::string &thumb)
{
  try
  {
    if (NULL == m_pDB.get()) return -1;
    if (NULL == m_pDS.get()) return -1;
    int idActor = -1;

    // ATTENTION: the trimming of actor names should really not be done here but after the scraping / NFO-parsing
    std::string trimmedName = name.c_str();
    StringUtils::Trim(trimmedName);

    std::string strSQL=PrepareSQL("select actor_id from actor where name like '%s'", trimmedName.substr(0, 255).c_str());
    m_pDS->query(strSQL);
    if (m_pDS->num_rows() == 0)
    {
      m_pDS->close();
      // doesnt exists, add it
      strSQL=PrepareSQL("insert into actor (actor_id, name, art_urls) values(NULL, '%s', '%s')", trimmedName.substr(0,255).c_str(), thumbURLs.c_str());
      m_pDS->exec(strSQL);
      idActor = (int)m_pDS->lastinsertid();
    }
    else
    {
      idActor = m_pDS->fv(0).get_asInt();
      m_pDS->close();
      // update the thumb url's
      if (!thumbURLs.empty())
      {
        strSQL=PrepareSQL("update actor set art_urls = '%s' where actor_id = %i", thumbURLs.c_str(), idActor);
        m_pDS->exec(strSQL);
      }
    }
    // add artwork
    if (!thumb.empty())
      SetArtForItem(idActor, "actor", "thumb", thumb);
    return idActor;
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (%s) failed", __FUNCTION__, name.c_str() );
  }
  return -1;
}



void CVideoDatabase::AddLinkToActor(int mediaId, const char *mediaType, int actorId, const std::string &role, int order)
{
  std::string sql=PrepareSQL("SELECT 1 FROM actor_link WHERE actor_id=%i AND media_id=%i AND media_type='%s'", actorId, mediaId, mediaType);

  if (GetSingleValue(sql).empty())
  { // doesnt exists, add it
    sql = PrepareSQL("INSERT INTO actor_link (actor_id, media_id, media_type, role, cast_order) VALUES(%i,%i,'%s','%s',%i)", actorId, mediaId, mediaType, role.c_str(), order);
    ExecuteQuery(sql);
  }
}

void CVideoDatabase::AddToLinkTable(int mediaId, const std::string& mediaType, const std::string& table, int valueId, const char *foreignKey)
{
  const char *key = foreignKey ? foreignKey : table.c_str();
  std::string sql = PrepareSQL("SELECT 1 FROM %s_link WHERE %s_id=%i AND media_id=%i AND media_type='%s'", table.c_str(), key, valueId, mediaId, mediaType.c_str());

  if (GetSingleValue(sql).empty())
  { // doesnt exists, add it
    sql = PrepareSQL("INSERT INTO %s_link (%s_id,media_id,media_type) VALUES(%i,%i,'%s')", table.c_str(), key, valueId, mediaId, mediaType.c_str());
    ExecuteQuery(sql);
  }
}

void CVideoDatabase::RemoveFromLinkTable(int mediaId, const std::string& mediaType, const std::string& table, int valueId, const char *foreignKey)
{
  const char *key = foreignKey ? foreignKey : table.c_str();
  std::string sql = PrepareSQL("DELETE FROM %s_link WHERE %s_id=%i AND media_id=%i AND media_type='%s'", table.c_str(), key, valueId, mediaId, mediaType.c_str());

  ExecuteQuery(sql);
}

void CVideoDatabase::AddLinksToItem(int mediaId, const std::string& mediaType, const std::string& field, const std::vector<std::string>& values)
{
  for (const auto &i : values)
  {
    if (!i.empty())
    {
      int idValue = AddToTable(field, field + "_id", "name", i);
      if (idValue > -1)
        AddToLinkTable(mediaId, mediaType, field, idValue);
    }
  }
}

void CVideoDatabase::UpdateLinksToItem(int mediaId, const std::string& mediaType, const std::string& field, const std::vector<std::string>& values)
{
  std::string sql = PrepareSQL("DELETE FROM %s_link WHERE media_id=%i AND media_type='%s'", field.c_str(), mediaId, mediaType.c_str());
  m_pDS->exec(sql);

  AddLinksToItem(mediaId, mediaType, field, values);
}

void CVideoDatabase::AddActorLinksToItem(int mediaId, const std::string& mediaType, const std::string& field, const std::vector<std::string>& values)
{
  for (const auto &i : values)
  {
    if (!i.empty())
    {
      int idValue = AddActor(i, "");
      if (idValue > -1)
        AddToLinkTable(mediaId, mediaType, field, idValue, "actor");
    }
  }
}

void CVideoDatabase::UpdateActorLinksToItem(int mediaId, const std::string& mediaType, const std::string& field, const std::vector<std::string>& values)
{
  std::string sql = PrepareSQL("DELETE FROM %s_link WHERE media_id=%i AND media_type='%s'", field.c_str(), mediaId, mediaType.c_str());
  m_pDS->exec(sql);

  AddActorLinksToItem(mediaId, mediaType, field, values);
}

//****Actors****
void CVideoDatabase::AddCast(int mediaId, const char *mediaType, const std::vector< SActorInfo > &cast)
{
  if (cast.empty())
    return;

  int order = std::max_element(cast.begin(), cast.end())->order;
  for (const auto &i : cast)
  {
    int idActor = AddActor(i.strName, i.thumbUrl.m_xml, i.thumb);
    AddLinkToActor(mediaId, mediaType, idActor, i.strRole, i.order >= 0 ? i.order : ++order);
  }
}

//********************************************************************************************************************************
bool CVideoDatabase::LoadVideoInfo(const std::string& strFilenameAndPath, CVideoInfoTag& details, int getDetails /* = VideoDbDetailsAll */)
{
  if (GetMovieInfo(strFilenameAndPath, details))
    return true;
  if (GetEpisodeInfo(strFilenameAndPath, details))
    return true;
  if (GetMusicVideoInfo(strFilenameAndPath, details))
    return true;
  if (GetFileInfo(strFilenameAndPath, details))
    return true;

  return false;
}

bool CVideoDatabase::HasTvShowInfo(const std::string& strPath)
{
  try
  {
    if (NULL == m_pDB.get()) return false;
    if (NULL == m_pDS.get()) return false;
    int idTvShow = GetTvShowId(strPath);
    return (idTvShow > 0); // index of zero is also invalid
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (%s) failed", __FUNCTION__, strPath.c_str());
  }
  return false;
}

void CVideoDatabase::DeleteDetailsForTvShow(const std::string& strPath)
{
  int idTvShow = GetTvShowId(strPath);
  if (idTvShow >= 0)
    DeleteDetailsForTvShow(idTvShow);
}

void CVideoDatabase::DeleteDetailsForTvShow(int idTvShow)
{
  try
  {
    if (NULL == m_pDB.get()) return ;
    if (NULL == m_pDS.get()) return ;

    std::string strSQL;
    strSQL=PrepareSQL("DELETE from genre_link WHERE media_id=%i AND media_type='tvshow'", idTvShow);
    m_pDS->exec(strSQL);

    strSQL=PrepareSQL("DELETE FROM actor_link WHERE media_id=%i AND media_type='tvshow'", idTvShow);
    m_pDS->exec(strSQL);

    strSQL=PrepareSQL("DELETE FROM director_link WHERE media_id=%i AND media_type='tvshow'", idTvShow);
    m_pDS->exec(strSQL);

    strSQL=PrepareSQL("DELETE FROM studio_link WHERE media_id=%i AND media_type='tvshow'", idTvShow);
    m_pDS->exec(strSQL);

    strSQL = PrepareSQL("DELETE FROM rating WHERE media_id=%i AND media_type='tvshow'", idTvShow);
    m_pDS->exec(strSQL);

    strSQL = PrepareSQL("DELETE FROM uniqueid WHERE media_id=%i AND media_type='tvshow'", idTvShow);
    m_pDS->exec(strSQL);

    // remove all info other than the id
    // we do this due to the way we have the link between the file + movie tables.

    std::vector<std::string> ids;
    for (int iType = VIDEODB_ID_TV_MIN + 1; iType < VIDEODB_ID_TV_MAX; iType++)
      ids.emplace_back(StringUtils::Format("c%02d=NULL", iType));

    strSQL = "update tvshow set ";
    strSQL += StringUtils::Join(ids, ", ");
    strSQL += PrepareSQL(" where idShow=%i", idTvShow);
    m_pDS->exec(strSQL);
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (%i) failed", __FUNCTION__, idTvShow);
  }
}

void CVideoDatabase::GetTvShowsByActor(const std::string& name, CFileItemList& items)
{
  Filter filter;
  filter.join  = "LEFT JOIN actor_link ON actor_link.media_id=tvshow_view.idShow AND actor_link.media_type='tvshow' "
                 "LEFT JOIN actor a ON a.actor_id=actor_link.actor_id "
                 "LEFT JOIN director_link ON director_link.media_id=tvshow_view.idShow AND director_link.media_type='tvshow' "
                 "LEFT JOIN actor d ON d.actor_id=director_link.actor_id";
  filter.where = PrepareSQL("a.name='%s' OR d.name='%s'", name.c_str(), name.c_str());
  GetTvShowsByWhere("videodb://tvshows/titles/", filter, items);
}

//********************************************************************************************************************************
bool CVideoDatabase::GetTvShowInfo(const std::string& strPath, CVideoInfoTag& details, int idTvShow /* = -1 */, CFileItem *item /* = NULL */, int getDetails /* = VideoDbDetailsAll */)
{
  try
  {
    if (m_pDB == nullptr || m_pDS == nullptr)
      return false;

    if (idTvShow < 0)
      idTvShow = GetTvShowId(strPath);
    if (idTvShow < 0) return false;

    std::string sql = PrepareSQL("SELECT * FROM tvshow_view WHERE idShow=%i GROUP BY idShow", idTvShow);
    if (!m_pDS->query(sql))
      return false;
    details = GetDetailsForTvShow(m_pDS, getDetails, item);
    return !details.IsEmpty();
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (%s) failed", __FUNCTION__, strPath.c_str());
  }
  return false;
}

bool CVideoDatabase::GetFileInfo(const std::string& strFilenameAndPath, CVideoInfoTag& details, int idFile /* = -1 */)
{
  try
  {
    if (idFile < 0)
      idFile = GetFileId(strFilenameAndPath);
    if (idFile < 0)
      return false;

    std::string sql = PrepareSQL("SELECT * FROM files "
                                "JOIN path ON path.idPath = files.idPath "
                                "LEFT JOIN bookmark ON bookmark.idFile = files.idFile AND bookmark.type = %i "
                                "WHERE files.idFile = %i", CBookmark::RESUME, idFile);
    if (!m_pDS->query(sql))
      return false;

    details.m_iFileId = m_pDS->fv("files.idFile").get_asInt();
    details.m_strPath = m_pDS->fv("path.strPath").get_asString();
    std::string strFileName = m_pDS->fv("files.strFilename").get_asString();
    ConstructPath(details.m_strFileNameAndPath, details.m_strPath, strFileName);
    details.SetPlayCount(std::max(details.GetPlayCount(), m_pDS->fv("files.playCount").get_asInt()));
    if (!details.m_lastPlayed.IsValid())
      details.m_lastPlayed.SetFromDBDateTime(m_pDS->fv("files.lastPlayed").get_asString());
    if (!details.m_dateAdded.IsValid())
      details.m_dateAdded.SetFromDBDateTime(m_pDS->fv("files.dateAdded").get_asString());
    if (!details.GetResumePoint().IsSet())
    {
      details.SetResumePoint(m_pDS->fv("bookmark.timeInSeconds").get_asInt(),
                             m_pDS->fv("bookmark.totalTimeInSeconds").get_asInt(),
                             m_pDS->fv("bookmark.playerState").get_asString());
    }

    // get streamdetails
    GetStreamDetails(details);

    return !details.IsEmpty();
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (%s) failed", __FUNCTION__, strFilenameAndPath.c_str());
  }
  return false;
}

std::string CVideoDatabase::GetValueString(const CVideoInfoTag &details, int min, int max, const SDbTableOffsets *offsets) const
{
  std::vector<std::string> conditions;
  for (int i = min + 1; i < max; ++i)
  {
    switch (offsets[i].type)
    {
    case VIDEODB_TYPE_STRING:
      conditions.emplace_back(PrepareSQL("c%02d='%s'", i, ((const std::string*)(((const char*)&details)+offsets[i].offset))->c_str()));
      break;
    case VIDEODB_TYPE_INT:
      conditions.emplace_back(PrepareSQL("c%02d='%i'", i, *(const int*)(((const char*)&details)+offsets[i].offset)));
      break;
    case VIDEODB_TYPE_COUNT:
      {
        int value = *(const int*)(((const char*)&details)+offsets[i].offset);
        if (value)
          conditions.emplace_back(PrepareSQL("c%02d=%i", i, value));
        else
          conditions.emplace_back(PrepareSQL("c%02d=NULL", i));
      }
      break;
    case VIDEODB_TYPE_BOOL:
      conditions.emplace_back(PrepareSQL("c%02d='%s'", i, *(const bool*)(((const char*)&details)+offsets[i].offset)?"true":"false"));
      break;
    case VIDEODB_TYPE_FLOAT:
      conditions.emplace_back(PrepareSQL("c%02d='%f'", i, *(const float*)(((const char*)&details)+offsets[i].offset)));
      break;
    case VIDEODB_TYPE_STRINGARRAY:
      conditions.emplace_back(PrepareSQL("c%02d='%s'", i, StringUtils::Join(*((const std::vector<std::string>*)(((const char*)&details)+offsets[i].offset)),
                                                                          CServiceBroker::GetSettingsComponent()->GetAdvancedSettings()->m_videoItemSeparator).c_str()));
      break;
    case VIDEODB_TYPE_DATE:
      conditions.emplace_back(PrepareSQL("c%02d='%s'", i, ((const CDateTime*)(((const char*)&details)+offsets[i].offset))->GetAsDBDate().c_str()));
      break;
    case VIDEODB_TYPE_DATETIME:
      conditions.emplace_back(PrepareSQL("c%02d='%s'", i, ((const CDateTime*)(((const char*)&details)+offsets[i].offset))->GetAsDBDateTime().c_str()));
      break;
    case VIDEODB_TYPE_UNUSED: // Skip the unused field to avoid populating unused data
      continue;
    }
  }
  return StringUtils::Join(conditions, ",");
}

//********************************************************************************************************************************
int CVideoDatabase::SetDetailsForItem(CVideoInfoTag& details, const std::map<std::string, std::string> &artwork)
{
  return SetDetailsForItem(details.m_iDbId, details.m_type, details, artwork);
}

int CVideoDatabase::SetDetailsForItem(int id, const MediaType& mediaType, CVideoInfoTag& details, const std::map<std::string, std::string> &artwork)
{
  if (mediaType == MediaTypeNone)
    return -1;

  if (mediaType == MediaTypeMovie)
    return SetDetailsForMovie(details.GetPath(), details, artwork, id);
  else if (mediaType == MediaTypeVideoCollection)
    return SetDetailsForMovieSet(details, artwork, id);
  else if (mediaType == MediaTypeTvShow)
  {
    std::map<int, std::map<std::string, std::string> > seasonArtwork;
    if (!UpdateDetailsForTvShow(id, details, artwork, seasonArtwork))
      return -1;

    return id;
  }
  else if (mediaType == MediaTypeSeason)
    return SetDetailsForSeason(details, artwork, details.m_iIdShow, id);
  else if (mediaType == MediaTypeEpisode)
    return SetDetailsForEpisode(details.GetPath(), details, artwork, details.m_iIdShow, id);
  else if (mediaType == MediaTypeMusicVideo)
    return SetDetailsForMusicVideo(details.GetPath(), details, artwork, id);

  return -1;
}

int CVideoDatabase::GetMatchingTvShow(const CVideoInfoTag &details)
{
  // first try matching on uniqueid, then on title + year
  int id = -1;
  if (!details.HasUniqueID())
    id = GetDbId(PrepareSQL("SELECT idShow FROM tvshow JOIN uniqueid ON uniqueid.media_id=tvshow.idShow AND uniqueid.media_type='tvshow' WHERE uniqueid.value='%s'", details.GetUniqueID().c_str()));
  if (id < 0)
    id = GetDbId(PrepareSQL("SELECT idShow FROM tvshow WHERE c%02d='%s' AND c%02d='%s'", VIDEODB_ID_TV_TITLE, details.m_strTitle.c_str(), VIDEODB_ID_TV_PREMIERED, details.GetPremiered().GetAsDBDate().c_str()));
  return id;
}

int CVideoDatabase::SetDetailsForTvShow(const std::vector<std::pair<std::string, std::string> > &paths,
    CVideoInfoTag& details, const std::map<std::string, std::string> &artwork,
    const std::map<int, std::map<std::string, std::string> > &seasonArt, int idTvShow /*= -1 */)
{

  /*
   The steps are as follows.
   1. Check if the tvshow is found on any of the given paths.  If found, we have the show id.
   2. Search for a matching show.  If found, we have the show id.
   3. If we don't have the id, add a new show.
   4. Add the paths to the show.
   5. Add details for the show.
   */

  if (idTvShow < 0)
  {
    for (const auto &i : paths)
    {
      idTvShow = GetTvShowId(i.first);
      if (idTvShow > -1)
        break;
    }
  }
  if (idTvShow < 0)
    idTvShow = GetMatchingTvShow(details);
  if (idTvShow < 0)
  {
    idTvShow = AddTvShow();
    if (idTvShow < 0)
      return -1;
  }

  // add any paths to the tvshow
  for (const auto &i : paths)
    AddPathToTvShow(idTvShow, i.first, i.second, details.m_dateAdded);

  UpdateDetailsForTvShow(idTvShow, details, artwork, seasonArt);

  return idTvShow;
}

bool CVideoDatabase::UpdateDetailsForTvShow(int idTvShow, CVideoInfoTag &details,
    const std::map<std::string, std::string> &artwork, const std::map<int, std::map<std::string, std::string>> &seasonArt)
{
  BeginTransaction();

  DeleteDetailsForTvShow(idTvShow);

  AddCast(idTvShow, "tvshow", details.m_cast);
  AddLinksToItem(idTvShow, MediaTypeTvShow, "genre", details.m_genre);
  AddLinksToItem(idTvShow, MediaTypeTvShow, "studio", details.m_studio);
  AddLinksToItem(idTvShow, MediaTypeTvShow, "tag", details.m_tags);
  AddActorLinksToItem(idTvShow, MediaTypeTvShow, "director", details.m_director);

  // add ratings
  details.m_iIdRating = AddRatings(idTvShow, MediaTypeTvShow, details.m_ratings, details.GetDefaultRating());

  // add unique ids
  details.m_iIdUniqueID = UpdateUniqueIDs(idTvShow, MediaTypeTvShow, details);

  // add "all seasons" - the rest are added in SetDetailsForEpisode
  AddSeason(idTvShow, -1);

  // add any named seasons
  for (const auto& namedSeason : details.m_namedSeasons)
  {
    // make sure the named season exists
    int seasonId = AddSeason(idTvShow, namedSeason.first, namedSeason.second);

    // get any existing details for the named season
    CVideoInfoTag season;
    if (!GetSeasonInfo(seasonId, season, false) || season.m_strSortTitle == namedSeason.second)
      continue;

    season.SetSortTitle(namedSeason.second);
    SetDetailsForSeason(season, std::map<std::string, std::string>(), idTvShow, seasonId);
  }

  SetArtForItem(idTvShow, MediaTypeTvShow, artwork);
  for (const auto &i : seasonArt)
  {
    int idSeason = AddSeason(idTvShow, i.first);
    if (idSeason > -1)
      SetArtForItem(idSeason, MediaTypeSeason, i.second);
  }

  // and insert the new row
  std::string sql = "UPDATE tvshow SET " + GetValueString(details, VIDEODB_ID_TV_MIN, VIDEODB_ID_TV_MAX, DbTvShowOffsets);
  if (details.m_iUserRating > 0 && details.m_iUserRating < 11)
    sql += PrepareSQL(", userrating = %i", details.m_iUserRating);
  else
    sql += ", userrating = NULL";
  if (details.GetDuration() > 0)
    sql += PrepareSQL(", duration = %i", details.GetDuration());
  else
    sql += ", duration = NULL";
  sql += PrepareSQL(" WHERE idShow=%i", idTvShow);
  if (ExecuteQuery(sql))
  {
    CommitTransaction();
    return true;
  }
  RollbackTransaction();
  return false;
}

//********************************************************************************************************************************
void CVideoDatabase::GetFilePathById(int idMovie, std::string &filePath, VIDEODB_CONTENT_TYPE iType)
{
  try
  {
    if (NULL == m_pDB.get()) return ;
    if (NULL == m_pDS.get()) return ;

    if (idMovie < 0) return ;

    std::string strSQL;
    if (iType == VIDEODB_CONTENT_MOVIES)
      strSQL=PrepareSQL("SELECT path.strPath, files.strFileName FROM path INNER JOIN files ON path.idPath=files.idPath INNER JOIN movie ON files.idFile=movie.idFile WHERE movie.idMovie=%i ORDER BY strFilename", idMovie );
    if (iType == VIDEODB_CONTENT_EPISODES)
      strSQL=PrepareSQL("SELECT path.strPath, files.strFileName FROM path INNER JOIN files ON path.idPath=files.idPath INNER JOIN episode ON files.idFile=episode.idFile WHERE episode.idEpisode=%i ORDER BY strFilename", idMovie );
    if (iType == VIDEODB_CONTENT_TVSHOWS)
      strSQL=PrepareSQL("SELECT path.strPath FROM path INNER JOIN tvshowlinkpath ON path.idPath=tvshowlinkpath.idPath WHERE tvshowlinkpath.idShow=%i", idMovie );
    if (iType ==VIDEODB_CONTENT_MUSICVIDEOS)
      strSQL=PrepareSQL("SELECT path.strPath, files.strFileName FROM path INNER JOIN files ON path.idPath=files.idPath INNER JOIN musicvideo ON files.idFile=musicvideo.idFile WHERE musicvideo.idMVideo=%i ORDER BY strFilename", idMovie );

    m_pDS->query( strSQL );
    if (!m_pDS->eof())
    {
      if (iType != VIDEODB_CONTENT_TVSHOWS)
      {
        std::string fileName = m_pDS->fv("files.strFilename").get_asString();
        ConstructPath(filePath,m_pDS->fv("path.strPath").get_asString(),fileName);
      }
      else
        filePath = m_pDS->fv("path.strPath").get_asString();
    }
    m_pDS->close();
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s failed", __FUNCTION__);
  }
}

void CVideoDatabase::DeleteTvShow(const std::string& strPath)
{
  int idTvShow = GetTvShowId(strPath);
  if (idTvShow >= 0)
    DeleteTvShow(idTvShow);
}

void CVideoDatabase::DeleteTvShow(int idTvShow, bool bKeepId /* = false */)
{
  if (idTvShow < 0)
    return;

  try
  {
    if (NULL == m_pDB.get()) return ;
    if (NULL == m_pDS.get()) return ;

    BeginTransaction();

    std::set<int> paths;
    GetPathsForTvShow(idTvShow, paths);

    std::string strSQL=PrepareSQL("SELECT episode.idEpisode FROM episode WHERE episode.idShow=%i",idTvShow);
    m_pDS2->query(strSQL);
    while (!m_pDS2->eof())
    {
      DeleteEpisode(m_pDS2->fv(0).get_asInt(), bKeepId);
      m_pDS2->next();
    }

    DeleteDetailsForTvShow(idTvShow);

    strSQL=PrepareSQL("delete from seasons where idShow=%i", idTvShow);
    m_pDS->exec(strSQL);

    // keep tvshow table and movielink table so we can update data in place
    if (!bKeepId)
    {
      strSQL=PrepareSQL("delete from tvshow where idShow=%i", idTvShow);
      m_pDS->exec(strSQL);

      for (const auto &i : paths)
      {
        std::string path = GetSingleValue(PrepareSQL("SELECT strPath FROM path WHERE idPath=%i", i));
        if (!path.empty())
          InvalidatePathHash(path);
      }
    }

    //! @todo move this below CommitTransaction() once UPnP doesn't rely on this anymore
    if (!bKeepId)
      AnnounceRemove(MediaTypeTvShow, idTvShow);

    CommitTransaction();

  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (%d) failed", __FUNCTION__, idTvShow);
    RollbackTransaction();
  }
}

int CVideoDatabase::GetDbId(const std::string &query)
{
  std::string result = GetSingleValue(query);
  if (!result.empty())
  {
    int idDb = strtol(result.c_str(), NULL, 10);
    if (idDb > 0)
      return idDb;
  }
  return -1;
}

void CVideoDatabase::GetDetailsFromDB(std::unique_ptr<Dataset> &pDS, int min, int max, const SDbTableOffsets *offsets, CVideoInfoTag &details, int idxOffset)
{
  GetDetailsFromDB(pDS->get_sql_record(), min, max, offsets, details, idxOffset);
}

void CVideoDatabase::GetDetailsFromDB(const dbiplus::sql_record* const record, int min, int max, const SDbTableOffsets *offsets, CVideoInfoTag &details, int idxOffset)
{
  for (int i = min + 1; i < max; i++)
  {
    switch (offsets[i].type)
    {
    case VIDEODB_TYPE_STRING:
      *(std::string*)(((char*)&details)+offsets[i].offset) = record->at(i+idxOffset).get_asString();
      break;
    case VIDEODB_TYPE_INT:
    case VIDEODB_TYPE_COUNT:
      *(int*)(((char*)&details)+offsets[i].offset) = record->at(i+idxOffset).get_asInt();
      break;
    case VIDEODB_TYPE_BOOL:
      *(bool*)(((char*)&details)+offsets[i].offset) = record->at(i+idxOffset).get_asBool();
      break;
    case VIDEODB_TYPE_FLOAT:
      *(float*)(((char*)&details)+offsets[i].offset) = record->at(i+idxOffset).get_asFloat();
      break;
    case VIDEODB_TYPE_STRINGARRAY:
    {
      std::string value = record->at(i+idxOffset).get_asString();
      if (!value.empty())
        *(std::vector<std::string>*)(((char*)&details)+offsets[i].offset) = StringUtils::Split(value, CServiceBroker::GetSettingsComponent()->GetAdvancedSettings()->m_videoItemSeparator);
      break;
    }
    case VIDEODB_TYPE_DATE:
      ((CDateTime*)(((char*)&details)+offsets[i].offset))->SetFromDBDate(record->at(i+idxOffset).get_asString());
      break;
    case VIDEODB_TYPE_DATETIME:
      ((CDateTime*)(((char*)&details)+offsets[i].offset))->SetFromDBDateTime(record->at(i+idxOffset).get_asString());
      break;
    case VIDEODB_TYPE_UNUSED: // Skip the unused field to avoid populating unused data
      continue;
    }
  }
}

DWORD movieTime = 0;
DWORD castTime = 0;

CVideoInfoTag CVideoDatabase::GetDetailsByTypeAndId(VIDEODB_CONTENT_TYPE type, int id)
{
  CVideoInfoTag details;
  details.Reset();

  switch (type)
  {
    case VIDEODB_CONTENT_MOVIES:
      GetMovieInfo("", details, id);
      break;
    case VIDEODB_CONTENT_TVSHOWS:
      GetTvShowInfo("", details, id);
      break;
    case VIDEODB_CONTENT_EPISODES:
      GetEpisodeInfo("", details, id);
      break;
    case VIDEODB_CONTENT_MUSICVIDEOS:
      GetMusicVideoInfo("", details, id);
      break;
    default:
      break;
  }

  return details;
}

CVideoInfoTag CVideoDatabase::GetDetailsForTvShow(std::unique_ptr<Dataset> &pDS, int getDetails /* = VideoDbDetailsNone */, CFileItem* item /* = NULL */)
{
  return GetDetailsForTvShow(pDS->get_sql_record(), getDetails, item);
}

CVideoInfoTag CVideoDatabase::GetDetailsForTvShow(const dbiplus::sql_record* const record, int getDetails /* = VideoDbDetailsNone */, CFileItem* item /* = NULL */)
{
  CVideoInfoTag details;

  if (record == NULL)
    return details;

  DWORD time = XbmcThreads::SystemClockMillis();
  int idTvShow = record->at(0).get_asInt();

  GetDetailsFromDB(record, VIDEODB_ID_TV_MIN, VIDEODB_ID_TV_MAX, DbTvShowOffsets, details, 1);
  details.m_bHasPremiered = details.m_premiered.IsValid();
  details.m_iDbId = idTvShow;
  details.m_type = MediaTypeTvShow;
  details.m_strPath = record->at(VIDEODB_DETAILS_TVSHOW_PATH).get_asString();
  details.m_basePath = details.m_strPath;
  details.m_parentPathID = record->at(VIDEODB_DETAILS_TVSHOW_PARENTPATHID).get_asInt();
  details.m_dateAdded.SetFromDBDateTime(record->at(VIDEODB_DETAILS_TVSHOW_DATEADDED).get_asString());
  details.m_lastPlayed.SetFromDBDateTime(record->at(VIDEODB_DETAILS_TVSHOW_LASTPLAYED).get_asString());
  details.m_iSeason = record->at(VIDEODB_DETAILS_TVSHOW_NUM_SEASONS).get_asInt();
  details.m_iEpisode = record->at(VIDEODB_DETAILS_TVSHOW_NUM_EPISODES).get_asInt();
  details.SetPlayCount(record->at(VIDEODB_DETAILS_TVSHOW_NUM_WATCHED).get_asInt());
  details.m_strShowTitle = details.m_strTitle;
  details.m_iUserRating = record->at(VIDEODB_DETAILS_TVSHOW_USER_RATING).get_asInt();
  details.SetRating(record->at(VIDEODB_DETAILS_TVSHOW_RATING).get_asFloat(),
                    record->at(VIDEODB_DETAILS_TVSHOW_VOTES).get_asInt(),
                    record->at(VIDEODB_DETAILS_TVSHOW_RATING_TYPE).get_asString(), true);
  details.SetUniqueID(record->at(VIDEODB_DETAILS_TVSHOW_UNIQUEID_VALUE).get_asString(), record->at(VIDEODB_DETAILS_TVSHOW_UNIQUEID_TYPE).get_asString(), true);
  details.SetDuration(record->at(VIDEODB_DETAILS_TVSHOW_DURATION).get_asInt());

  movieTime += XbmcThreads::SystemClockMillis() - time; time = XbmcThreads::SystemClockMillis();

  if (getDetails)
  {
    if (getDetails & VideoDbDetailsCast)
    {
      GetCast(details.m_iDbId, "tvshow", details.m_cast);
      castTime += XbmcThreads::SystemClockMillis() - time; time = XbmcThreads::SystemClockMillis();
    }

    if (getDetails & VideoDbDetailsTag)
      GetTags(details.m_iDbId, MediaTypeTvShow, details.m_tags);

    if (getDetails & VideoDbDetailsRating)
      GetRatings(details.m_iDbId, MediaTypeTvShow, details.m_ratings);

    if (getDetails & VideoDbDetailsUniqueID)
      GetUniqueIDs(details.m_iDbId, MediaTypeTvShow, details);

    details.m_strPictureURL.Parse();

    details.m_parsedDetails = getDetails;
  }

  if (item != NULL)
  {
    item->m_dateTime = details.GetPremiered();
    item->SetProperty("totalseasons", details.m_iSeason);
    item->SetProperty("totalepisodes", details.m_iEpisode);
    item->SetProperty("numepisodes", details.m_iEpisode); // will be changed later to reflect watchmode setting
    item->SetProperty("watchedepisodes", details.GetPlayCount());
    item->SetProperty("unwatchedepisodes", details.m_iEpisode - details.GetPlayCount());
  }
  details.SetPlayCount((details.m_iEpisode <= details.GetPlayCount()) ? 1 : 0);

  return details;
}

void CVideoDatabase::GetCast(int media_id, const std::string &media_type, std::vector<SActorInfo> &cast)
{
  try
  {
    if (!m_pDB.get()) return;
    if (!m_pDS2.get()) return;

    std::string sql = PrepareSQL("SELECT actor.name,"
                                 "  actor_link.role,"
                                 "  actor_link.cast_order,"
                                 "  actor.art_urls,"
                                 "  art.url "
                                 "FROM actor_link"
                                 "  JOIN actor ON"
                                 "    actor_link.actor_id=actor.actor_id"
                                 "  LEFT JOIN art ON"
                                 "    art.media_id=actor.actor_id AND art.media_type='actor' AND art.type='thumb' "
                                 "WHERE actor_link.media_id=%i AND actor_link.media_type='%s'"
                                 "ORDER BY actor_link.cast_order", media_id, media_type.c_str());
    m_pDS2->query(sql);
    while (!m_pDS2->eof())
    {
      SActorInfo info;
      info.strName = m_pDS2->fv(0).get_asString();
      bool found = false;
      for (const auto &i : cast)
      {
        if (i.strName == info.strName)
        {
          found = true;
          break;
        }
      }
      if (!found)
      {
        info.strRole = m_pDS2->fv(1).get_asString();
        info.order = m_pDS2->fv(2).get_asInt();
        info.thumbUrl.ParseString(m_pDS2->fv(3).get_asString());
        info.thumb = m_pDS2->fv(4).get_asString();
        cast.emplace_back(std::move(info));
      }
      m_pDS2->next();
    }
    m_pDS2->close();
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s(%i,%s) failed", __FUNCTION__, media_id, media_type.c_str());
  }
}

void CVideoDatabase::GetUniqueIDs(int media_id, const std::string &media_type, CVideoInfoTag& details)
{
  try
  {
    if (!m_pDB.get()) return;
    if (!m_pDS2.get()) return;

    std::string sql = PrepareSQL("SELECT type, value FROM uniqueid WHERE media_id = %i AND media_type = '%s'", media_id, media_type.c_str());
    m_pDS2->query(sql);
    while (!m_pDS2->eof())
    {
      details.SetUniqueID(m_pDS2->fv(1).get_asString(), m_pDS2->fv(0).get_asString());
      m_pDS2->next();
    }
    m_pDS2->close();
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s(%i,%s) failed", __FUNCTION__, media_id, media_type.c_str());
  }
}

/// \brief GetStackTimes() obtains any saved video times for the stacked file
/// \retval Returns true if the stack times exist, false otherwise.
bool CVideoDatabase::GetStackTimes(const std::string &filePath, std::vector<uint64_t> &times)
{
  try
  {
    // obtain the FileID (if it exists)
    int idFile = GetFileId(filePath);
    if (idFile < 0) return false;
    if (NULL == m_pDB.get()) return false;
    if (NULL == m_pDS.get()) return false;
    // ok, now obtain the settings for this file
    std::string strSQL=PrepareSQL("select times from stacktimes where idFile=%i\n", idFile);
    m_pDS->query( strSQL );
    if (m_pDS->num_rows() > 0)
    { // get the video settings info
      uint64_t timeTotal = 0;
      std::vector<std::string> timeString = StringUtils::Split(m_pDS->fv("times").get_asString(), ",");
      times.clear();
      for (const auto &i : timeString)
      {
        uint64_t partTime = static_cast<uint64_t>(atof(i.c_str()) * 1000.0f);
        times.push_back(partTime); // db stores in secs, convert to msecs
        timeTotal += partTime;
      }
      m_pDS->close();
      return (timeTotal > 0);
    }
    m_pDS->close();
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s failed", __FUNCTION__);
  }
  return false;
}

/// \brief Sets the stack times for a particular video file
void CVideoDatabase::SetStackTimes(const std::string& filePath, const std::vector<uint64_t> &times)
{
  try
  {
    if (NULL == m_pDB.get()) return ;
    if (NULL == m_pDS.get()) return ;
    int idFile = AddFile(filePath);
    if (idFile < 0)
      return;

    // delete any existing items
    m_pDS->exec( PrepareSQL("delete from stacktimes where idFile=%i", idFile) );

    // add the items
    std::string timeString = StringUtils::Format("%.3f", times[0] / 1000.0f);
    for (unsigned int i = 1; i < times.size(); i++)
      timeString += StringUtils::Format(",%.3f", times[i] / 1000.0f);

    m_pDS->exec( PrepareSQL("insert into stacktimes (idFile,times) values (%i,'%s')\n", idFile, timeString.c_str()) );
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (%s) failed", __FUNCTION__, filePath.c_str());
  }
}

class CArtItem
{
public:
  CArtItem() { art_id = 0; media_id = 0; };
  int art_id;
  std::string art_type;
  std::string art_url;
  int media_id;
  std::string media_type;
};

// used for database update to v83
class CShowItem
{
public:
  bool operator==(const CShowItem &r) const
  {
    return (!ident.empty() && ident == r.ident) || (title == r.title && year == r.year);
  };
  int    id;
  int    path;
  std::string title;
  std::string year;
  std::string ident;
};

// used for database update to v84
class CShowLink
{
public:
  int show;
  int pathId;
  std::string path;
};

void CVideoDatabase::UpdateTables(int iVersion)
{
  // Important: DO NOT use CREATE TABLE [...] AS SELECT [...] - it does not work on MySQL with GTID consistency enforced

  if (iVersion < 76)
  {
    m_pDS->exec("ALTER TABLE settings ADD StereoMode integer");
    m_pDS->exec("ALTER TABLE settings ADD StereoInvert bool");
  }
  if (iVersion < 77)
    m_pDS->exec("ALTER TABLE streamdetails ADD strStereoMode text");

  if (iVersion < 81)
  { // add idParentPath to path table
    m_pDS->exec("ALTER TABLE path ADD idParentPath integer");
    std::map<std::string, int> paths;
    m_pDS->query("select idPath,strPath from path");
    while (!m_pDS->eof())
    {
      paths.insert(make_pair(m_pDS->fv(1).get_asString(), m_pDS->fv(0).get_asInt()));
      m_pDS->next();
    }
    m_pDS->close();
    // run through these paths figuring out the parent path, and add to the table if found
    for (const auto &i : paths)
    {
      std::string parent = URIUtils::GetParentPath(i.first);
      auto j = paths.find(parent);
      if (j != paths.end())
        m_pDS->exec(PrepareSQL("UPDATE path SET idParentPath=%i WHERE idPath=%i", j->second, i.second));
    }
  }
  if (iVersion < 82)
  {
    // drop parent path id and basePath from tvshow table
    m_pDS->exec("UPDATE tvshow SET c16=NULL,c17=NULL");
  }
  if (iVersion < 83)
  {
    // drop duplicates in tvshow table, and update tvshowlinkpath accordingly
    std::string sql = PrepareSQL("SELECT tvshow.idShow,idPath,c%02d,c%02d,c%02d FROM tvshow JOIN tvshowlinkpath ON tvshow.idShow = tvshowlinkpath.idShow", VIDEODB_ID_TV_TITLE, VIDEODB_ID_TV_PREMIERED, VIDEODB_ID_TV_IDENT_ID);
    m_pDS->query(sql);
    std::vector<CShowItem> shows;
    while (!m_pDS->eof())
    {
      CShowItem show;
      show.id    = m_pDS->fv(0).get_asInt();
      show.path  = m_pDS->fv(1).get_asInt();
      show.title = m_pDS->fv(2).get_asString();
      show.year  = m_pDS->fv(3).get_asString();
      show.ident = m_pDS->fv(4).get_asString();
      shows.emplace_back(std::move(show));
      m_pDS->next();
    }
    m_pDS->close();
    if (!shows.empty())
    {
      for (auto i = shows.begin() + 1; i != shows.end(); ++i)
      {
        // has this show been found before?
        auto j = find(shows.begin(), i, *i);
        if (j != i)
        { // this is a duplicate
          // update the tvshowlinkpath table
          m_pDS->exec(PrepareSQL("UPDATE tvshowlinkpath SET idShow = %d WHERE idShow = %d AND idPath = %d", j->id, i->id, i->path));
          // update episodes, seasons, movie links
          m_pDS->exec(PrepareSQL("UPDATE episode SET idShow = %d WHERE idShow = %d", j->id, i->id));
          m_pDS->exec(PrepareSQL("UPDATE seasons SET idShow = %d WHERE idShow = %d", j->id, i->id));
          m_pDS->exec(PrepareSQL("UPDATE movielinktvshow SET idShow = %d WHERE idShow = %d", j->id, i->id));
          // delete tvshow
          m_pDS->exec(PrepareSQL("DELETE FROM genrelinktvshow WHERE idShow=%i", i->id));
          m_pDS->exec(PrepareSQL("DELETE FROM actorlinktvshow WHERE idShow=%i", i->id));
          m_pDS->exec(PrepareSQL("DELETE FROM directorlinktvshow WHERE idShow=%i", i->id));
          m_pDS->exec(PrepareSQL("DELETE FROM studiolinktvshow WHERE idShow=%i", i->id));
          m_pDS->exec(PrepareSQL("DELETE FROM tvshow WHERE idShow = %d", i->id));
        }
      }
      // cleanup duplicate seasons
      m_pDS->exec("DELETE FROM seasons WHERE idSeason NOT IN (SELECT idSeason FROM (SELECT min(idSeason) as idSeason FROM seasons GROUP BY idShow,season) AS sub)");
    }
  }
  if (iVersion < 84)
  { // replace any multipaths in tvshowlinkpath table
    m_pDS->query("SELECT idShow, tvshowlinkpath.idPath, strPath FROM tvshowlinkpath JOIN path ON tvshowlinkpath.idPath=path.idPath WHERE path.strPath LIKE 'multipath://%'");
    std::vector<CShowLink> shows;
    while (!m_pDS->eof())
    {
      CShowLink link;
      link.show   = m_pDS->fv(0).get_asInt();
      link.pathId = m_pDS->fv(1).get_asInt();
      link.path   = m_pDS->fv(2).get_asString();
      shows.emplace_back(std::move(link));
      m_pDS->next();
    }
    m_pDS->close();
    // update these
    for (auto i = shows.begin(); i != shows.end(); ++i)
    {
      std::vector<std::string> paths;
      CMultiPathDirectory::GetPaths(i->path, paths);
      for (auto j = paths.begin(); j != paths.end(); ++j)
      {
        int idPath = AddPath(*j, URIUtils::GetParentPath(*j));
        /* we can't rely on REPLACE INTO here as analytics (indices) aren't online yet */
        if (GetSingleValue(PrepareSQL("SELECT 1 FROM tvshowlinkpath WHERE idShow=%i AND idPath=%i", i->show, idPath)).empty())
          m_pDS->exec(PrepareSQL("INSERT INTO tvshowlinkpath(idShow, idPath) VALUES(%i,%i)", i->show, idPath));
      }
      m_pDS->exec(PrepareSQL("DELETE FROM tvshowlinkpath WHERE idShow=%i AND idPath=%i", i->show, i->pathId));
    }
  }
  if (iVersion < 85)
  {
    // drop multipaths from the path table - they're not needed for anything at all
    m_pDS->exec("DELETE FROM path WHERE strPath LIKE 'multipath://%'");
  }
  if (iVersion < 87)
  { // due to the tvshow merging above, there could be orphaned season or show art
    m_pDS->exec("DELETE from art WHERE media_type='tvshow' AND NOT EXISTS (SELECT 1 FROM tvshow WHERE tvshow.idShow = art.media_id)");
    m_pDS->exec("DELETE from art WHERE media_type='season' AND NOT EXISTS (SELECT 1 FROM seasons WHERE seasons.idSeason = art.media_id)");
  }
  if (iVersion < 91)
  {
    // create actor link table
    m_pDS->exec("CREATE TABLE actor_link(actor_id INT, media_id INT, media_type TEXT, role TEXT, cast_order INT)");
    m_pDS->exec("INSERT INTO actor_link(actor_id, media_id, media_type, role, cast_order) SELECT DISTINCT idActor, idMovie, 'movie', strRole, iOrder from actorlinkmovie");
    m_pDS->exec("INSERT INTO actor_link(actor_id, media_id, media_type, role, cast_order) SELECT DISTINCT idActor, idShow, 'tvshow', strRole, iOrder from actorlinktvshow");
    m_pDS->exec("INSERT INTO actor_link(actor_id, media_id, media_type, role, cast_order) SELECT DISTINCT idActor, idEpisode, 'episode', strRole, iOrder from actorlinkepisode");
    m_pDS->exec("DROP TABLE IF EXISTS actorlinkmovie");
    m_pDS->exec("DROP TABLE IF EXISTS actorlinktvshow");
    m_pDS->exec("DROP TABLE IF EXISTS actorlinkepisode");
    m_pDS->exec("CREATE TABLE actor(actor_id INTEGER PRIMARY KEY, name TEXT, art_urls TEXT)");
    m_pDS->exec("INSERT INTO actor(actor_id, name, art_urls) SELECT idActor,strActor,strThumb FROM actors");
    m_pDS->exec("DROP TABLE IF EXISTS actors");

    // directors
    m_pDS->exec("CREATE TABLE director_link(actor_id INTEGER, media_id INTEGER, media_type TEXT)");
    m_pDS->exec("INSERT INTO director_link(actor_id, media_id, media_type) SELECT DISTINCT idDirector, idMovie, 'movie' FROM directorlinkmovie");
    m_pDS->exec("INSERT INTO director_link(actor_id, media_id, media_type) SELECT DISTINCT idDirector, idShow, 'tvshow' FROM directorlinktvshow");
    m_pDS->exec("INSERT INTO director_link(actor_id, media_id, media_type) SELECT DISTINCT idDirector, idEpisode, 'episode' FROM directorlinkepisode");
    m_pDS->exec("INSERT INTO director_link(actor_id, media_id, media_type) SELECT DISTINCT idDirector, idMVideo, 'musicvideo' FROM directorlinkmusicvideo");
    m_pDS->exec("DROP TABLE IF EXISTS directorlinkmovie");
    m_pDS->exec("DROP TABLE IF EXISTS directorlinktvshow");
    m_pDS->exec("DROP TABLE IF EXISTS directorlinkepisode");
    m_pDS->exec("DROP TABLE IF EXISTS directorlinkmusicvideo");

    // writers
    m_pDS->exec("CREATE TABLE writer_link(actor_id INTEGER, media_id INTEGER, media_type TEXT)");
    m_pDS->exec("INSERT INTO writer_link(actor_id, media_id, media_type) SELECT DISTINCT idWriter, idMovie, 'movie' FROM writerlinkmovie");
    m_pDS->exec("INSERT INTO writer_link(actor_id, media_id, media_type) SELECT DISTINCT idWriter, idEpisode, 'episode' FROM writerlinkepisode");
    m_pDS->exec("DROP TABLE IF EXISTS writerlinkmovie");
    m_pDS->exec("DROP TABLE IF EXISTS writerlinkepisode");

    // music artist
    m_pDS->exec("INSERT INTO actor_link(actor_id, media_id, media_type) SELECT DISTINCT idArtist, idMVideo, 'musicvideo' FROM artistlinkmusicvideo");
    m_pDS->exec("DROP TABLE IF EXISTS artistlinkmusicvideo");

    // studios
    m_pDS->exec("CREATE TABLE studio_link(studio_id INTEGER, media_id INTEGER, media_type TEXT)");
    m_pDS->exec("INSERT INTO studio_link(studio_id, media_id, media_type) SELECT DISTINCT idStudio, idMovie, 'movie' FROM studiolinkmovie");
    m_pDS->exec("INSERT INTO studio_link(studio_id, media_id, media_type) SELECT DISTINCT idStudio, idShow, 'tvshow' FROM studiolinktvshow");
    m_pDS->exec("INSERT INTO studio_link(studio_id, media_id, media_type) SELECT DISTINCT idStudio, idMVideo, 'musicvideo' FROM studiolinkmusicvideo");
    m_pDS->exec("DROP TABLE IF EXISTS studiolinkmovie");
    m_pDS->exec("DROP TABLE IF EXISTS studiolinktvshow");
    m_pDS->exec("DROP TABLE IF EXISTS studiolinkmusicvideo");
    m_pDS->exec("CREATE TABLE studionew(studio_id INTEGER PRIMARY KEY, name TEXT)");
    m_pDS->exec("INSERT INTO studionew(studio_id, name) SELECT idStudio,strStudio FROM studio");
    m_pDS->exec("DROP TABLE IF EXISTS studio");
    m_pDS->exec("ALTER TABLE studionew RENAME TO studio");

    // genres
    m_pDS->exec("CREATE TABLE genre_link(genre_id INTEGER, media_id INTEGER, media_type TEXT)");
    m_pDS->exec("INSERT INTO genre_link(genre_id, media_id, media_type) SELECT DISTINCT idGenre, idMovie, 'movie' FROM genrelinkmovie");
    m_pDS->exec("INSERT INTO genre_link(genre_id, media_id, media_type) SELECT DISTINCT idGenre, idShow, 'tvshow' FROM genrelinktvshow");
    m_pDS->exec("INSERT INTO genre_link(genre_id, media_id, media_type) SELECT DISTINCT idGenre, idMVideo, 'musicvideo' FROM genrelinkmusicvideo");
    m_pDS->exec("DROP TABLE IF EXISTS genrelinkmovie");
    m_pDS->exec("DROP TABLE IF EXISTS genrelinktvshow");
    m_pDS->exec("DROP TABLE IF EXISTS genrelinkmusicvideo");
    m_pDS->exec("CREATE TABLE genrenew(genre_id INTEGER PRIMARY KEY, name TEXT)");
    m_pDS->exec("INSERT INTO genrenew(genre_id, name) SELECT idGenre,strGenre FROM genre");
    m_pDS->exec("DROP TABLE IF EXISTS genre");
    m_pDS->exec("ALTER TABLE genrenew RENAME TO genre");

    // country
    m_pDS->exec("CREATE TABLE country_link(country_id INTEGER, media_id INTEGER, media_type TEXT)");
    m_pDS->exec("INSERT INTO country_link(country_id, media_id, media_type) SELECT DISTINCT idCountry, idMovie, 'movie' FROM countrylinkmovie");
    m_pDS->exec("DROP TABLE IF EXISTS countrylinkmovie");
    m_pDS->exec("CREATE TABLE countrynew(country_id INTEGER PRIMARY KEY, name TEXT)");
    m_pDS->exec("INSERT INTO countrynew(country_id, name) SELECT idCountry,strCountry FROM country");
    m_pDS->exec("DROP TABLE IF EXISTS country");
    m_pDS->exec("ALTER TABLE countrynew RENAME TO country");

    // tags
    m_pDS->exec("CREATE TABLE tag_link(tag_id INTEGER, media_id INTEGER, media_type TEXT)");
    m_pDS->exec("INSERT INTO tag_link(tag_id, media_id, media_type) SELECT DISTINCT idTag, idMedia, media_type FROM taglinks");
    m_pDS->exec("DROP TABLE IF EXISTS taglinks");
    m_pDS->exec("CREATE TABLE tagnew(tag_id INTEGER PRIMARY KEY, name TEXT)");
    m_pDS->exec("INSERT INTO tagnew(tag_id, name) SELECT idTag,strTag FROM tag");
    m_pDS->exec("DROP TABLE IF EXISTS tag");
    m_pDS->exec("ALTER TABLE tagnew RENAME TO tag");
  }

  if (iVersion < 93)
  {
    // cleanup main tables
    std::string valuesSql;
    for(int i = 0; i < VIDEODB_MAX_COLUMNS; i++)
    {
      valuesSql += StringUtils::Format("c%02d = TRIM(c%02d)", i, i);
      if (i < VIDEODB_MAX_COLUMNS - 1)
        valuesSql += ",";
    }
    m_pDS->exec("UPDATE episode SET " + valuesSql);
    m_pDS->exec("UPDATE movie SET " + valuesSql);
    m_pDS->exec("UPDATE musicvideo SET " + valuesSql);
    m_pDS->exec("UPDATE tvshow SET " + valuesSql);

    // cleanup additional tables
    std::map<std::string, std::vector<std::string>> additionalTablesMap = {
      {"actor", {"actor_link", "director_link", "writer_link"}},
      {"studio", {"studio_link"}},
      {"genre", {"genre_link"}},
      {"country", {"country_link"}},
      {"tag", {"tag_link"}}
    };
    for (const auto& additionalTableEntry : additionalTablesMap)
    {
      std::string table = additionalTableEntry.first;
      std::string tablePk = additionalTableEntry.first + "_id";
      std::map<int, std::string> duplicatesMinMap;
      std::map<int, std::string> duplicatesMap;

      // cleanup name
      m_pDS->exec(PrepareSQL("UPDATE %s SET name = TRIM(name)",
                             table.c_str()));

      // shrink name to length 255
      m_pDS->exec(PrepareSQL("UPDATE %s SET name = SUBSTR(name, 1, 255) WHERE LENGTH(name) > 255",
                             table.c_str()));

      // fetch main entries
      m_pDS->query(PrepareSQL("SELECT MIN(%s), name FROM %s GROUP BY name HAVING COUNT(1) > 1",
                              tablePk.c_str(), table.c_str()));

      while (!m_pDS->eof())
      {
        duplicatesMinMap.insert(std::make_pair(m_pDS->fv(0).get_asInt(), m_pDS->fv(1).get_asString()));
        m_pDS->next();
      }
      m_pDS->close();

      // fetch duplicate entries
      for (const auto& entry : duplicatesMinMap)
      {
        m_pDS->query(PrepareSQL("SELECT %s FROM %s WHERE name = '%s' AND %s <> %i",
                                tablePk.c_str(), table.c_str(),
                                entry.second.c_str(), tablePk.c_str(), entry.first));

        std::stringstream ids;
        while (!m_pDS->eof())
        {
          int id = m_pDS->fv(0).get_asInt();
          m_pDS->next();

          ids << id;
          if (!m_pDS->eof())
            ids << ",";
        }
        m_pDS->close();

        duplicatesMap.insert(std::make_pair(entry.first, ids.str()));
      }

      // cleanup duplicates in link tables
      for (const auto& subTable : additionalTableEntry.second)
      {
        // create indexes to speed up things
        m_pDS->exec(PrepareSQL("CREATE INDEX ix_%s ON %s (%s)",
                               subTable.c_str(), subTable.c_str(), tablePk.c_str()));

        // migrate every duplicate entry to the main entry
        for (const auto& entry : duplicatesMap)
        {
          m_pDS->exec(PrepareSQL("UPDATE %s SET %s = %i WHERE %s IN (%s) ",
                                 subTable.c_str(), tablePk.c_str(), entry.first,
                                 tablePk.c_str(), entry.second.c_str()));
        }

        // clear all duplicates in the link tables
        if (subTable == "actor_link")
        {
          // as a distinct won't work because of role and cast_order and a group by kills a
          // low powered mysql, we de-dupe it with REPLACE INTO while using the real unique index
          m_pDS->exec("CREATE TABLE temp_actor_link(actor_id INT, media_id INT, media_type TEXT, role TEXT, cast_order INT)");
          m_pDS->exec("CREATE UNIQUE INDEX ix_temp_actor_link ON temp_actor_link (actor_id, media_type(20), media_id)");
          m_pDS->exec("REPLACE INTO temp_actor_link SELECT * FROM actor_link");
          m_pDS->exec("DROP INDEX ix_temp_actor_link ON temp_actor_link");
        }
        else
        {
          m_pDS->exec(PrepareSQL("CREATE TABLE temp_%s AS SELECT DISTINCT * FROM %s",
                                 subTable.c_str(), subTable.c_str()));
        }

        m_pDS->exec(PrepareSQL("DROP TABLE IF EXISTS %s",
                               subTable.c_str()));

        m_pDS->exec(PrepareSQL("ALTER TABLE temp_%s RENAME TO %s",
                               subTable.c_str(), subTable.c_str()));
      }

      // delete duplicates in main table
      for (const auto& entry : duplicatesMap)
      {
        m_pDS->exec(PrepareSQL("DELETE FROM %s WHERE %s IN (%s)",
                               table.c_str(), tablePk.c_str(), entry.second.c_str()));
      }
    }
  }

  if (iVersion < 96)
  {
    m_pDS->exec("ALTER TABLE movie ADD userrating integer");
    m_pDS->exec("ALTER TABLE episode ADD userrating integer");
    m_pDS->exec("ALTER TABLE tvshow ADD userrating integer");
    m_pDS->exec("ALTER TABLE musicvideo ADD userrating integer");
  }

  if (iVersion < 97)
    m_pDS->exec("ALTER TABLE sets ADD strOverview TEXT");

  if (iVersion < 98)
    m_pDS->exec("ALTER TABLE seasons ADD name text");

  if (iVersion < 99)
  {
    // Add idSeason to episode table, so we don't have to join via idShow and season in the future
    m_pDS->exec("ALTER TABLE episode ADD idSeason integer");

    m_pDS->query("SELECT idSeason, idShow, season FROM seasons");
    while (!m_pDS->eof())
    {
      m_pDS2->exec(PrepareSQL("UPDATE episode "
        "SET idSeason = %d "
        "WHERE "
        "episode.idShow = %d AND "
        "episode.c%02d = %d",
        m_pDS->fv(0).get_asInt(), m_pDS->fv(1).get_asInt(),
        VIDEODB_ID_EPISODE_SEASON, m_pDS->fv(2).get_asInt()));

      m_pDS->next();
    }
  }
  if (iVersion < 101)
    m_pDS->exec("ALTER TABLE seasons ADD userrating INTEGER");

  if (iVersion < 102)
  {
    m_pDS->exec("CREATE TABLE rating (rating_id INTEGER PRIMARY KEY, media_id INTEGER, media_type TEXT, rating_type TEXT, rating FLOAT, votes INTEGER)");

    std::string sql = PrepareSQL("SELECT DISTINCT idMovie, c%02d, c%02d FROM movie", VIDEODB_ID_RATING_ID, VIDEODB_ID_VOTES);
    m_pDS->query(sql);
    while (!m_pDS->eof())
    {
      m_pDS2->exec(PrepareSQL("INSERT INTO rating(media_id, media_type, rating_type, rating, votes) VALUES (%i, 'movie', 'default', %f, %i)", m_pDS->fv(0).get_asInt(), (float)strtod(m_pDS->fv(1).get_asString().c_str(), NULL), StringUtils::ReturnDigits(m_pDS->fv(2).get_asString())));
      int idRating = (int)m_pDS2->lastinsertid();
      m_pDS2->exec(PrepareSQL("UPDATE movie SET c%02d=%i WHERE idMovie=%i", VIDEODB_ID_RATING_ID, idRating, m_pDS->fv(0).get_asInt()));
      m_pDS->next();
    }
    m_pDS->close();

    sql = PrepareSQL("SELECT DISTINCT idShow, c%02d, c%02d FROM tvshow", VIDEODB_ID_TV_RATING_ID, VIDEODB_ID_TV_VOTES);
    m_pDS->query(sql);
    while (!m_pDS->eof())
    {
      m_pDS2->exec(PrepareSQL("INSERT INTO rating(media_id, media_type, rating_type, rating, votes) VALUES (%i, 'tvshow', 'default', %f, %i)", m_pDS->fv(0).get_asInt(), (float)strtod(m_pDS->fv(1).get_asString().c_str(), NULL), StringUtils::ReturnDigits(m_pDS->fv(2).get_asString())));
      int idRating = (int)m_pDS2->lastinsertid();
      m_pDS2->exec(PrepareSQL("UPDATE tvshow SET c%02d=%i WHERE idShow=%i", VIDEODB_ID_TV_RATING_ID, idRating, m_pDS->fv(0).get_asInt()));
      m_pDS->next();
    }
    m_pDS->close();

    sql = PrepareSQL("SELECT DISTINCT idEpisode, c%02d, c%02d FROM episode", VIDEODB_ID_EPISODE_RATING_ID, VIDEODB_ID_EPISODE_VOTES);
    m_pDS->query(sql);
    while (!m_pDS->eof())
    {
      m_pDS2->exec(PrepareSQL("INSERT INTO rating(media_id, media_type, rating_type, rating, votes) VALUES (%i, 'episode', 'default', %f, %i)", m_pDS->fv(0).get_asInt(), (float)strtod(m_pDS->fv(1).get_asString().c_str(), NULL), StringUtils::ReturnDigits(m_pDS->fv(2).get_asString())));
      int idRating = (int)m_pDS2->lastinsertid();
      m_pDS2->exec(PrepareSQL("UPDATE episode SET c%02d=%i WHERE idEpisode=%i", VIDEODB_ID_EPISODE_RATING_ID, idRating, m_pDS->fv(0).get_asInt()));
      m_pDS->next();
    }
    m_pDS->close();
  }

  if (iVersion < 103)
  {
    m_pDS->exec("ALTER TABLE settings ADD VideoStream integer");
    m_pDS->exec("ALTER TABLE streamdetails ADD strVideoLanguage text");
  }

  if (iVersion < 104)
  {
    m_pDS->exec("ALTER TABLE tvshow ADD duration INTEGER");

    std::string sql = PrepareSQL( "SELECT episode.idShow, MAX(episode.c%02d) "
                                  "FROM episode "

                                  "LEFT JOIN streamdetails "
                                  "ON streamdetails.idFile = episode.idFile "
                                  "AND streamdetails.iStreamType = 0 " // only grab video streams

                                  "WHERE episode.c%02d <> streamdetails.iVideoDuration "
                                  "OR streamdetails.iVideoDuration IS NULL "
                                  "GROUP BY episode.idShow", VIDEODB_ID_EPISODE_RUNTIME, VIDEODB_ID_EPISODE_RUNTIME);

    m_pDS->query(sql);
    while (!m_pDS->eof())
    {
      m_pDS2->exec(PrepareSQL("UPDATE tvshow SET duration=%i WHERE idShow=%i", m_pDS->fv(1).get_asInt(), m_pDS->fv(0).get_asInt()));
      m_pDS->next();
    }
    m_pDS->close();
  }

  if (iVersion < 105)
  {
    m_pDS->exec("ALTER TABLE movie ADD premiered TEXT");
    m_pDS->exec(PrepareSQL("UPDATE movie SET premiered=c%02d", VIDEODB_ID_YEAR));
    m_pDS->exec("ALTER TABLE musicvideo ADD premiered TEXT");
    m_pDS->exec(PrepareSQL("UPDATE musicvideo SET premiered=c%02d", VIDEODB_ID_MUSICVIDEO_YEAR));
  }

  if (iVersion < 107)
  {
    // need this due to the nested GetScraperPath query
    std::unique_ptr<Dataset> pDS;
    pDS.reset(m_pDB->CreateDataset());
    if (NULL == pDS.get()) return;

    pDS->exec("CREATE TABLE uniqueid (uniqueid_id INTEGER PRIMARY KEY, media_id INTEGER, media_type TEXT, value TEXT, type TEXT)");

    for (int i = 0; i < 3; ++i)
    {
      std::string mediatype, columnID;
      int columnUniqueID;
      switch (i)
      {
      case (0):
        mediatype = "movie";
        columnID = "idMovie";
        columnUniqueID = VIDEODB_ID_IDENT_ID;
        break;
      case (1):
        mediatype = "tvshow";
        columnID = "idShow";
        columnUniqueID = VIDEODB_ID_TV_IDENT_ID;
        break;
      case (2):
        mediatype = "episode";
        columnID = "idEpisode";
        columnUniqueID = VIDEODB_ID_EPISODE_IDENT_ID;
        break;
      default:
        continue;
      }
      pDS->query(PrepareSQL("SELECT %s, c%02d FROM %s", columnID.c_str(), columnUniqueID, mediatype.c_str()));
      while (!pDS->eof())
      {
        std::string uniqueid = pDS->fv(1).get_asString();
        if (!uniqueid.empty())
        {
          int mediaid = pDS->fv(0).get_asInt();
          if (StringUtils::StartsWith(uniqueid, "tt"))
            m_pDS2->exec(PrepareSQL("INSERT INTO uniqueid(media_id, media_type, type, value) VALUES (%i, '%s', 'imdb', '%s')", mediaid, mediatype.c_str(), uniqueid.c_str()));
          else
            m_pDS2->exec(PrepareSQL("INSERT INTO uniqueid(media_id, media_type, type, value) VALUES (%i, '%s', 'unknown', '%s')", mediaid, mediatype.c_str(), uniqueid.c_str()));
          m_pDS2->exec(PrepareSQL("UPDATE %s SET c%02d='%i' WHERE %s=%i", mediatype.c_str(), columnUniqueID, (int)m_pDS2->lastinsertid(), columnID.c_str(), mediaid));
        }
        pDS->next();
      }
      pDS->close();
    }
  }

  if (iVersion < 109)
  {
    m_pDS->exec("ALTER TABLE settings RENAME TO settingsold");
    m_pDS->exec("CREATE TABLE settings ( idFile integer, Deinterlace bool,"
                "ViewMode integer,ZoomAmount float, PixelRatio float, VerticalShift float, AudioStream integer, SubtitleStream integer,"
                "SubtitleDelay float, SubtitlesOn bool, Brightness float, Contrast float, Gamma float,"
                "VolumeAmplification float, AudioDelay float, ResumeTime integer,"
                "Sharpness float, NoiseReduction float, NonLinStretch bool, PostProcess bool,"
                "ScalingMethod integer, DeinterlaceMode integer, StereoMode integer, StereoInvert bool, VideoStream integer)");
    m_pDS->exec("INSERT INTO settings SELECT idFile, Deinterlace, ViewMode, ZoomAmount, PixelRatio, VerticalShift, AudioStream, SubtitleStream, SubtitleDelay, SubtitlesOn, Brightness, Contrast, Gamma, VolumeAmplification, AudioDelay, ResumeTime, Sharpness, NoiseReduction, NonLinStretch, PostProcess, ScalingMethod, DeinterlaceMode, StereoMode, StereoInvert, VideoStream FROM settingsold");
    m_pDS->exec("DROP TABLE settingsold");
  }

  if (iVersion < 110)
  {
    m_pDS->exec("ALTER TABLE settings ADD TonemapMethod integer");
    m_pDS->exec("ALTER TABLE settings ADD TonemapParam float");
  }

  if (iVersion < 111)
    m_pDS->exec("ALTER TABLE settings ADD Orientation integer");

  if (iVersion < 112)
    m_pDS->exec("ALTER TABLE settings ADD CenterMixLevel integer");

  if (iVersion < 113)
  {
    // fb9c25f5 and e5f6d204 changed the behavior of path splitting for plugin URIs (previously it would only use the root)
    // Re-split paths for plugin files in order to maintain watched state etc.
    m_pDS->query("SELECT files.idFile, files.strFilename, path.strPath FROM files LEFT JOIN path ON files.idPath = path.idPath WHERE files.strFilename LIKE 'plugin://%'");
    while (!m_pDS->eof())
    {
      std::string path, fn;
      SplitPath(m_pDS->fv(1).get_asString(), path, fn);
      if (path != m_pDS->fv(2).get_asString())
      {
        int pathid = -1;
        m_pDS2->query(PrepareSQL("SELECT idPath FROM path WHERE strPath='%s'", path.c_str()));
        if (!m_pDS2->eof())
          pathid = m_pDS2->fv(0).get_asInt();
        m_pDS2->close();
        if (pathid < 0)
        {
          std::string parent = URIUtils::GetParentPath(path);
          int parentid = -1;
          m_pDS2->query(PrepareSQL("SELECT idPath FROM path WHERE strPath='%s'", parent.c_str()));
          if (!m_pDS2->eof())
            parentid = m_pDS2->fv(0).get_asInt();
          m_pDS2->close();
          if (parentid < 0)
          {
            m_pDS2->exec(PrepareSQL("INSERT INTO path (strPath) VALUES ('%s')", parent.c_str()));
            parentid = (int)m_pDS2->lastinsertid();
          }
          m_pDS2->exec(PrepareSQL("INSERT INTO path (strPath, idParentPath) VALUES ('%s', %i)", path.c_str(), parentid));
          pathid = (int)m_pDS2->lastinsertid();
        }
        m_pDS2->query(PrepareSQL("SELECT idFile FROM files WHERE strFileName='%s' AND idPath=%i", fn.c_str(), pathid));
        bool exists = !m_pDS2->eof();
        m_pDS2->close();
        if (exists)
          m_pDS2->exec(PrepareSQL("DELETE FROM files WHERE idFile=%i", m_pDS->fv(0).get_asInt()));
        else
          m_pDS2->exec(PrepareSQL("UPDATE files SET idPath=%i WHERE idFile=%i", pathid, m_pDS->fv(0).get_asInt()));
      }
      m_pDS->next();
    }
    m_pDS->close();
  }
}

int CVideoDatabase::GetSchemaVersion() const
{
  return 116;
}

bool CVideoDatabase::LookupByFolders(const std::string &path, bool shows)
{
  SScanSettings settings;
  bool foundDirectly = false;
  ScraperPtr scraper = GetScraperForPath(path, settings, foundDirectly);
  if (scraper && scraper->Content() == CONTENT_TVSHOWS && !shows)
    return false; // episodes
  return settings.parent_name_root; // shows, movies, musicvids
}

void CVideoDatabase::UpdateMovieTitle(int idMovie, const std::string& strNewMovieTitle, VIDEODB_CONTENT_TYPE iType)
{
  try
  {
    if (NULL == m_pDB.get()) return ;
    if (NULL == m_pDS.get()) return ;
    std::string content;
    if (iType == VIDEODB_CONTENT_MOVIES)
    {
      CLog::Log(LOGINFO, "Changing Movie:id:%i New Title:%s", idMovie, strNewMovieTitle.c_str());
      content = MediaTypeMovie;
    }
    else if (iType == VIDEODB_CONTENT_EPISODES)
    {
      CLog::Log(LOGINFO, "Changing Episode:id:%i New Title:%s", idMovie, strNewMovieTitle.c_str());
      content = MediaTypeEpisode;
    }
    else if (iType == VIDEODB_CONTENT_TVSHOWS)
    {
      CLog::Log(LOGINFO, "Changing TvShow:id:%i New Title:%s", idMovie, strNewMovieTitle.c_str());
      content = MediaTypeTvShow;
    }
    else if (iType == VIDEODB_CONTENT_MUSICVIDEOS)
    {
      CLog::Log(LOGINFO, "Changing MusicVideo:id:%i New Title:%s", idMovie, strNewMovieTitle.c_str());
      content = MediaTypeMusicVideo;
    }
    else if (iType == VIDEODB_CONTENT_MOVIE_SETS)
    {
      CLog::Log(LOGINFO, "Changing Movie set:id:%i New Title:%s", idMovie, strNewMovieTitle.c_str());
      std::string strSQL = PrepareSQL("UPDATE sets SET strSet='%s' WHERE idSet=%i", strNewMovieTitle.c_str(), idMovie );
      m_pDS->exec(strSQL);
    }

    if (!content.empty())
    {
      SetSingleValue(iType, idMovie, FieldTitle, strNewMovieTitle);
      AnnounceUpdate(content, idMovie);
    }
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (int idMovie, const std::string& strNewMovieTitle) failed on MovieID:%i and Title:%s", __FUNCTION__, idMovie, strNewMovieTitle.c_str());
  }
}

bool CVideoDatabase::UpdateVideoSortTitle(int idDb, const std::string& strNewSortTitle, VIDEODB_CONTENT_TYPE iType /* = VIDEODB_CONTENT_MOVIES */)
{
  try
  {
    if (NULL == m_pDB.get() || NULL == m_pDS.get())
      return false;
    if (iType != VIDEODB_CONTENT_MOVIES && iType != VIDEODB_CONTENT_TVSHOWS)
      return false;

    std::string content = MediaTypeMovie;
    if (iType == VIDEODB_CONTENT_TVSHOWS)
      content = MediaTypeTvShow;

    if (SetSingleValue(iType, idDb, FieldSortTitle, strNewSortTitle))
    {
      AnnounceUpdate(content, idDb);
      return true;
    }
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (int idDb, const std::string& strNewSortTitle, VIDEODB_CONTENT_TYPE iType) failed on ID: %i and Sort Title: %s", __FUNCTION__, idDb, strNewSortTitle.c_str());
  }

  return false;
}

bool CVideoDatabase::GetGenresNav(const std::string& strBaseDir, CFileItemList& items, int idContent /* = -1 */, const Filter &filter /* = Filter() */, bool countOnly /* = false */)
{
  return GetNavCommon(strBaseDir, items, "genre", idContent, filter, countOnly);
}

bool CVideoDatabase::GetCountriesNav(const std::string& strBaseDir, CFileItemList& items, int idContent /* = -1 */, const Filter &filter /* = Filter() */, bool countOnly /* = false */)
{
  return GetNavCommon(strBaseDir, items, "country", idContent, filter, countOnly);
}

bool CVideoDatabase::GetStudiosNav(const std::string& strBaseDir, CFileItemList& items, int idContent /* = -1 */, const Filter &filter /* = Filter() */, bool countOnly /* = false */)
{
  return GetNavCommon(strBaseDir, items, "studio", idContent, filter, countOnly);
}

bool CVideoDatabase::GetNavCommon(const std::string& strBaseDir, CFileItemList& items, const char *type, int idContent /* = -1 */, const Filter &filter /* = Filter() */, bool countOnly /* = false */)
{
  try
  {
    if (NULL == m_pDB.get()) return false;
    if (NULL == m_pDS.get()) return false;

    std::string strSQL;
    Filter extFilter = filter;
    if (m_profileManager.GetMasterProfile().getLockMode() != LOCK_MODE_EVERYONE && !g_passwordManager.bMasterUser)
    {
      std::string view, view_id, media_type, extraField, extraJoin;
      if (idContent == VIDEODB_CONTENT_MOVIES)
      {
        view       = MediaTypeMovie;
        view_id    = "idMovie";
        media_type = MediaTypeMovie;
        extraField = "files.playCount";
      }
      else if (idContent == VIDEODB_CONTENT_TVSHOWS) //this will not get tvshows with 0 episodes
      {
        view       = MediaTypeEpisode;
        view_id    = "idShow";
        media_type = MediaTypeTvShow;
        // in order to make use of FieldPlaycount in smart playlists we need an extra join
        if (StringUtils::EqualsNoCase(type, "tag"))
          extraJoin  = PrepareSQL("JOIN tvshow_view ON tvshow_view.idShow = tag_link.media_id AND tag_link.media_type='tvshow'");
      }
      else if (idContent == VIDEODB_CONTENT_MUSICVIDEOS)
      {
        view       = MediaTypeMusicVideo;
        view_id    = "idMVideo";
        media_type = MediaTypeMusicVideo;
        extraField = "files.playCount";
      }
      else
        return false;

      strSQL = "SELECT %s " + PrepareSQL("FROM %s ", type);
      extFilter.fields = PrepareSQL("%s.%s_id, %s.name, path.strPath", type, type, type);
      extFilter.AppendField(extraField);
      extFilter.AppendJoin(PrepareSQL("JOIN %s_link ON %s.%s_id = %s_link.%s_id", type, type, type, type, type));
      extFilter.AppendJoin(PrepareSQL("JOIN %s_view ON %s_link.media_id = %s_view.%s AND %s_link.media_type='%s'", view.c_str(), type, view.c_str(), view_id.c_str(), type, media_type.c_str()));
      extFilter.AppendJoin(PrepareSQL("JOIN files ON files.idFile = %s_view.idFile", view.c_str()));
      extFilter.AppendJoin("JOIN path ON path.idPath = files.idPath");
      extFilter.AppendJoin(extraJoin);
    }
    else
    {
      std::string view, view_id, media_type, extraField, extraJoin;
      if (idContent == VIDEODB_CONTENT_MOVIES)
      {
        view       = MediaTypeMovie;
        view_id    = "idMovie";
        media_type = MediaTypeMovie;
        extraField = "count(1), count(files.playCount)";
        extraJoin  = PrepareSQL("JOIN files ON files.idFile = %s_view.idFile", view.c_str());
      }
      else if (idContent == VIDEODB_CONTENT_TVSHOWS)
      {
        view       = MediaTypeTvShow;
        view_id    = "idShow";
        media_type = MediaTypeTvShow;
      }
      else if (idContent == VIDEODB_CONTENT_MUSICVIDEOS)
      {
        view       = MediaTypeMusicVideo;
        view_id    = "idMVideo";
        media_type = MediaTypeMusicVideo;
        extraField = "count(1), count(files.playCount)";
        extraJoin  = PrepareSQL("JOIN files ON files.idFile = %s_view.idFile", view.c_str());
      }
      else
        return false;

      strSQL = "SELECT %s " + PrepareSQL("FROM %s ", type);
      extFilter.fields = PrepareSQL("%s.%s_id, %s.name", type, type, type);
      extFilter.AppendField(extraField);
      extFilter.AppendJoin(PrepareSQL("JOIN %s_link ON %s.%s_id = %s_link.%s_id", type, type, type, type, type));
      extFilter.AppendJoin(PrepareSQL("JOIN %s_view ON %s_link.media_id = %s_view.%s AND %s_link.media_type='%s'",
                                      view.c_str(), type, view.c_str(), view_id.c_str(), type, media_type.c_str()));
      extFilter.AppendJoin(extraJoin);
      extFilter.AppendGroup(PrepareSQL("%s.%s_id", type, type));
    }

    if (countOnly)
    {
      extFilter.fields = PrepareSQL("COUNT(DISTINCT %s.%s_id)", type, type);
      extFilter.group.clear();
      extFilter.order.clear();
    }
    strSQL = StringUtils::Format(strSQL.c_str(), !extFilter.fields.empty() ? extFilter.fields.c_str() : "*");

    CVideoDbUrl videoUrl;
    if (!BuildSQL(strBaseDir, strSQL, extFilter, strSQL, videoUrl))
      return false;

    int iRowsFound = RunQuery(strSQL);
    if (iRowsFound <= 0)
      return iRowsFound == 0;

    if (countOnly)
    {
      CFileItemPtr pItem(new CFileItem());
      pItem->SetProperty("total", iRowsFound == 1 ? m_pDS->fv(0).get_asInt() : iRowsFound);
      items.Add(pItem);

      m_pDS->close();
      return true;
    }

    if (m_profileManager.GetMasterProfile().getLockMode() != LOCK_MODE_EVERYONE && !g_passwordManager.bMasterUser)
    {
      std::map<int, std::pair<std::string,int> > mapItems;
      while (!m_pDS->eof())
      {
        int id = m_pDS->fv(0).get_asInt();
        std::string str = m_pDS->fv(1).get_asString();

        // was this already found?
        auto it = mapItems.find(id);
        if (it == mapItems.end())
        {
          // check path
          if (g_passwordManager.IsDatabasePathUnlocked(m_pDS->fv(2).get_asString(),*CMediaSourceSettings::GetInstance().GetSources("video")))
          {
            if (idContent == VIDEODB_CONTENT_MOVIES || idContent == VIDEODB_CONTENT_MUSICVIDEOS)
              mapItems.insert(std::pair<int, std::pair<std::string,int> >(id, std::pair<std::string, int>(str,m_pDS->fv(3).get_asInt()))); //fv(3) is file.playCount
            else if (idContent == VIDEODB_CONTENT_TVSHOWS)
              mapItems.insert(std::pair<int, std::pair<std::string,int> >(id, std::pair<std::string,int>(str,0)));
          }
        }
        m_pDS->next();
      }
      m_pDS->close();

      for (const auto &i : mapItems)
      {
        CFileItemPtr pItem(new CFileItem(i.second.first));
        pItem->GetVideoInfoTag()->m_iDbId = i.first;
        pItem->GetVideoInfoTag()->m_type = type;

        CVideoDbUrl itemUrl = videoUrl;
        std::string path = StringUtils::Format("%i/", i.first);
        itemUrl.AppendPath(path);
        pItem->SetPath(itemUrl.ToString());

        pItem->m_bIsFolder = true;
        if (idContent == VIDEODB_CONTENT_MOVIES || idContent == VIDEODB_CONTENT_MUSICVIDEOS)
          pItem->GetVideoInfoTag()->SetPlayCount(i.second.second);
        if (!items.Contains(pItem->GetPath()))
        {
          pItem->SetLabelPreformatted(true);
          items.Add(pItem);
        }
      }
    }
    else
    {
      while (!m_pDS->eof())
      {
        CFileItemPtr pItem(new CFileItem(m_pDS->fv(1).get_asString()));
        pItem->GetVideoInfoTag()->m_iDbId = m_pDS->fv(0).get_asInt();
        pItem->GetVideoInfoTag()->m_type = type;

        CVideoDbUrl itemUrl = videoUrl;
        std::string path = StringUtils::Format("%i/", m_pDS->fv(0).get_asInt());
        itemUrl.AppendPath(path);
        pItem->SetPath(itemUrl.ToString());

        pItem->m_bIsFolder = true;
        pItem->SetLabelPreformatted(true);
        if (idContent == VIDEODB_CONTENT_MOVIES || idContent == VIDEODB_CONTENT_MUSICVIDEOS)
        { // fv(3) is the number of videos watched, fv(2) is the total number.  We set the playcount
          // only if the number of videos watched is equal to the total number (i.e. every video watched)
          pItem->GetVideoInfoTag()->SetPlayCount((m_pDS->fv(3).get_asInt() == m_pDS->fv(2).get_asInt()) ? 1 : 0);
        }
        items.Add(pItem);
        m_pDS->next();
      }
      m_pDS->close();
    }
    return true;
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s failed", __FUNCTION__);
  }
  return false;
}

bool CVideoDatabase::GetWritersNav(const std::string& strBaseDir, CFileItemList& items, int idContent /* = -1 */, const Filter &filter /* = Filter() */, bool countOnly /* = false */)
{
  return GetPeopleNav(strBaseDir, items, "writer", idContent, filter, countOnly);
}

bool CVideoDatabase::GetDirectorsNav(const std::string& strBaseDir, CFileItemList& items, int idContent /* = -1 */, const Filter &filter /* = Filter() */, bool countOnly /* = false */)
{
  return GetPeopleNav(strBaseDir, items, "director", idContent, filter, countOnly);
}

bool CVideoDatabase::GetActorsNav(const std::string& strBaseDir, CFileItemList& items, int idContent /* = -1 */, const Filter &filter /* = Filter() */, bool countOnly /* = false */)
{
  if (GetPeopleNav(strBaseDir, items, "actor", idContent, filter, countOnly))
  { // set thumbs - ideally this should be in the normal thumb setting routines
    for (int i = 0; i < items.Size() && !countOnly; i++)
    {
      CFileItemPtr pItem = items[i];
      if (idContent == VIDEODB_CONTENT_MUSICVIDEOS)
        pItem->SetIconImage("DefaultArtist.png");
      else
        pItem->SetIconImage("DefaultActor.png");
    }
    return true;
  }
  return false;
}

bool CVideoDatabase::GetPeopleNav(const std::string& strBaseDir, CFileItemList& items, const char *type, int idContent /* = -1 */, const Filter &filter /* = Filter() */, bool countOnly /* = false */)
{
  if (NULL == m_pDB.get()) return false;
  if (NULL == m_pDS.get()) return false;

  try
  {
    //! @todo This routine (and probably others at this same level) use playcount as a reference to filter on at a later
    //!       point.  This means that we *MUST* filter these levels as you'll get double ups.  Ideally we'd allow playcount
    //!       to filter through as we normally do for tvshows to save this happening.
    //!       Also, we apply this same filtering logic to the locked or unlocked paths to prevent these from showing.
    //!       Whether or not this should happen is a tricky one - it complicates all the high level categories (everything
    //!       above titles).

    // General routine that the other actor/director/writer routines call

    // get primary genres for movies
    std::string strSQL;
    Filter extFilter = filter;
    if (m_profileManager.GetMasterProfile().getLockMode() != LOCK_MODE_EVERYONE && !g_passwordManager.bMasterUser)
    {
      std::string view, view_id, media_type, extraField, group;
      if (idContent == VIDEODB_CONTENT_MOVIES)
      {
        view       = MediaTypeMovie;
        view_id    = "idMovie";
        media_type = MediaTypeMovie;
        extraField = "files.playCount";
      }
      else if (idContent == VIDEODB_CONTENT_TVSHOWS)
      {
        view       = MediaTypeEpisode;
        view_id    = "idShow";
        media_type = MediaTypeTvShow;
        extraField = "count(DISTINCT idShow)";
        group = "actor.actor_id";
      }
      else if (idContent == VIDEODB_CONTENT_EPISODES)
      {
        view       = MediaTypeEpisode;
        view_id    = "idEpisode";
        media_type = MediaTypeEpisode;
        extraField = "files.playCount";
      }
      else if (idContent == VIDEODB_CONTENT_MUSICVIDEOS)
      {
        view       = MediaTypeMusicVideo;
        view_id    = "idMVideo";
        media_type = MediaTypeMusicVideo;
        extraField = "files.playCount";
      }
      else
        return false;

      strSQL = "SELECT %s FROM actor ";
      extFilter.fields = "actor.actor_id, actor.name, actor.art_urls, path.strPath";
      extFilter.AppendField(extraField);
      extFilter.AppendJoin(PrepareSQL("JOIN %s_link ON actor.actor_id = %s_link.actor_id", type, type));
      extFilter.AppendJoin(PrepareSQL("JOIN %s_view ON %s_link.media_id = %s_view.%s AND %s_link.media_type='%s'", view.c_str(), type, view.c_str(), view_id.c_str(), type, media_type.c_str()));
      extFilter.AppendJoin(PrepareSQL("JOIN files ON files.idFile = %s_view.idFile", view.c_str()));
      extFilter.AppendJoin("JOIN path ON path.idPath = files.idPath");
      extFilter.AppendGroup(group);
    }
    else
    {
      std::string view, view_id, media_type, extraField, extraJoin;
      if (idContent == VIDEODB_CONTENT_MOVIES)
      {
        view       = MediaTypeMovie;
        view_id    = "idMovie";
        media_type = MediaTypeMovie;
        extraField = "count(1), count(files.playCount)";
        extraJoin  = PrepareSQL(" JOIN files ON files.idFile=%s_view.idFile", view.c_str());
      }
      else if (idContent == VIDEODB_CONTENT_TVSHOWS)
      {
        view       = MediaTypeTvShow;
        view_id    = "idShow";
        media_type = MediaTypeTvShow;
        extraField = "count(idShow)";
      }
      else if (idContent == VIDEODB_CONTENT_EPISODES)
      {
        view       = MediaTypeEpisode;
        view_id    = "idEpisode";
        media_type = MediaTypeEpisode;
        extraField = "count(1), count(files.playCount)";
        extraJoin  = PrepareSQL("JOIN files ON files.idFile = %s_view.idFile", view.c_str());
      }
      else if (idContent == VIDEODB_CONTENT_MUSICVIDEOS)
      {
        view       = MediaTypeMusicVideo;
        view_id    = "idMVideo";
        media_type = MediaTypeMusicVideo;
        extraField = "count(1), count(files.playCount)";
        extraJoin  = PrepareSQL("JOIN files ON files.idFile = %s_view.idFile", view.c_str());
      }
      else
        return false;

      strSQL ="SELECT %s FROM actor ";
      extFilter.fields = "actor.actor_id, actor.name, actor.art_urls";
      extFilter.AppendField(extraField);
      extFilter.AppendJoin(PrepareSQL("JOIN %s_link on actor.actor_id = %s_link.actor_id", type, type));
      extFilter.AppendJoin(PrepareSQL("JOIN %s_view on %s_link.media_id = %s_view.%s AND %s_link.media_type='%s'", view.c_str(), type, view.c_str(), view_id.c_str(), type, media_type.c_str()));
      extFilter.AppendJoin(extraJoin);
      extFilter.AppendGroup("actor.actor_id");
    }

    if (countOnly)
    {
      extFilter.fields = "COUNT(1)";
      extFilter.group.clear();
      extFilter.order.clear();
    }
    strSQL = StringUtils::Format(strSQL.c_str(), !extFilter.fields.empty() ? extFilter.fields.c_str() : "*");

    CVideoDbUrl videoUrl;
    if (!BuildSQL(strBaseDir, strSQL, extFilter, strSQL, videoUrl))
      return false;

    // run query
    unsigned int time = XbmcThreads::SystemClockMillis();
    if (!m_pDS->query(strSQL)) return false;
    CLog::Log(LOGDEBUG, LOGDATABASE, "%s -  query took %i ms",
              __FUNCTION__, XbmcThreads::SystemClockMillis() - time); time = XbmcThreads::SystemClockMillis();
    int iRowsFound = m_pDS->num_rows();
    if (iRowsFound == 0)
    {
      m_pDS->close();
      return true;
    }

    if (countOnly)
    {
      CFileItemPtr pItem(new CFileItem());
      pItem->SetProperty("total", iRowsFound == 1 ? m_pDS->fv(0).get_asInt() : iRowsFound);
      items.Add(pItem);

      m_pDS->close();
      return true;
    }

    if (m_profileManager.GetMasterProfile().getLockMode() != LOCK_MODE_EVERYONE && !g_passwordManager.bMasterUser)
    {
      std::map<int, CActor> mapActors;

      while (!m_pDS->eof())
      {
        int idActor = m_pDS->fv(0).get_asInt();
        CActor actor;
        actor.name = m_pDS->fv(1).get_asString();
        actor.thumb = m_pDS->fv(2).get_asString();
        if (idContent != VIDEODB_CONTENT_TVSHOWS)
        {
          actor.playcount = m_pDS->fv(3).get_asInt();
          actor.appearances = 1;
        }
        else actor.appearances = m_pDS->fv(4).get_asInt();
        auto it = mapActors.find(idActor);
        // is this actor already known?
        if (it == mapActors.end())
        {
          // check path
          if (g_passwordManager.IsDatabasePathUnlocked(m_pDS->fv("path.strPath").get_asString(),*CMediaSourceSettings::GetInstance().GetSources("video")))
            mapActors.insert(std::pair<int, CActor>(idActor, actor));
        }
        else if (idContent != VIDEODB_CONTENT_TVSHOWS)
            it->second.appearances++;
        m_pDS->next();
      }
      m_pDS->close();

      for (const auto &i : mapActors)
      {
        CFileItemPtr pItem(new CFileItem(i.second.name));

        CVideoDbUrl itemUrl = videoUrl;
        std::string path = StringUtils::Format("%i/", i.first);
        itemUrl.AppendPath(path);
        pItem->SetPath(itemUrl.ToString());

        pItem->m_bIsFolder=true;
        pItem->GetVideoInfoTag()->SetPlayCount(i.second.playcount);
        pItem->GetVideoInfoTag()->m_strPictureURL.ParseString(i.second.thumb);
        pItem->GetVideoInfoTag()->m_iDbId = i.first;
        pItem->GetVideoInfoTag()->m_type = type;
        pItem->GetVideoInfoTag()->m_relevance = i.second.appearances;
        items.Add(pItem);
      }
    }
    else
    {
      while (!m_pDS->eof())
      {
        try
        {
          CFileItemPtr pItem(new CFileItem(m_pDS->fv(1).get_asString()));

          CVideoDbUrl itemUrl = videoUrl;
          std::string path = StringUtils::Format("%i/", m_pDS->fv(0).get_asInt());
          itemUrl.AppendPath(path);
          pItem->SetPath(itemUrl.ToString());

          pItem->m_bIsFolder=true;
          pItem->GetVideoInfoTag()->m_strPictureURL.ParseString(m_pDS->fv(2).get_asString());
          pItem->GetVideoInfoTag()->m_iDbId = m_pDS->fv(0).get_asInt();
          pItem->GetVideoInfoTag()->m_type = type;
          if (idContent != VIDEODB_CONTENT_TVSHOWS)
          {
            // fv(4) is the number of videos watched, fv(3) is the total number.  We set the playcount
            // only if the number of videos watched is equal to the total number (i.e. every video watched)
            pItem->GetVideoInfoTag()->SetPlayCount((m_pDS->fv(4).get_asInt() == m_pDS->fv(3).get_asInt()) ? 1 : 0);
          }
          pItem->GetVideoInfoTag()->m_relevance = m_pDS->fv(3).get_asInt();
          if (idContent == VIDEODB_CONTENT_MUSICVIDEOS)
            pItem->GetVideoInfoTag()->m_artist.emplace_back(pItem->GetLabel());
          items.Add(pItem);
          m_pDS->next();
        }
        catch (...)
        {
          m_pDS->close();
          CLog::Log(LOGERROR, "%s: out of memory - retrieved %i items", __FUNCTION__, items.Size());
          return items.Size() > 0;
        }
      }
      m_pDS->close();
    }
    CLog::Log(LOGDEBUG, LOGDATABASE, "%s item retrieval took %i ms",
              __FUNCTION__, XbmcThreads::SystemClockMillis() - time); time = XbmcThreads::SystemClockMillis();

    return true;
  }
  catch (...)
  {
    m_pDS->close();
    CLog::Log(LOGERROR, "%s failed", __FUNCTION__);
  }
  return false;
}

bool CVideoDatabase::GetYearsNav(const std::string& strBaseDir, CFileItemList& items, int idContent /* = -1 */, const Filter &filter /* = Filter() */)
{
  try
  {
    if (NULL == m_pDB.get()) return false;
    if (NULL == m_pDS.get()) return false;

    std::string strSQL;
    Filter extFilter = filter;
    if (m_profileManager.GetMasterProfile().getLockMode() != LOCK_MODE_EVERYONE && !g_passwordManager.bMasterUser)
    {
      if (idContent == VIDEODB_CONTENT_MOVIES)
      {
        strSQL = "select movie_view.premiered, path.strPath, files.playCount from movie_view ";
        extFilter.AppendJoin("join files on files.idFile = movie_view.idFile join path on files.idPath = path.idPath");
      }
      else if (idContent == VIDEODB_CONTENT_TVSHOWS)
      {
        strSQL = PrepareSQL("select tvshow_view.c%02d, path.strPath from tvshow_view ", VIDEODB_ID_TV_PREMIERED);
        extFilter.AppendJoin("join episode_view on episode_view.idShow = tvshow_view.idShow join files on files.idFile = episode_view.idFile join path on files.idPath = path.idPath");
      }
      else if (idContent == VIDEODB_CONTENT_MUSICVIDEOS)
      {
        strSQL = "select musicvideo_view.premiered, path.strPath, files.playCount from musicvideo_view ";
        extFilter.AppendJoin("join files on files.idFile = musicvideo_view.idFile join path on files.idPath = path.idPath");
      }
      else
        return false;
    }
    else
    {
      std::string group;
      if (idContent == VIDEODB_CONTENT_MOVIES)
      {
        strSQL = "select movie_view.premiered, count(1), count(files.playCount) from movie_view ";
        extFilter.AppendJoin("join files on files.idFile = movie_view.idFile");
        extFilter.AppendGroup("movie_view.premiered");
      }
      else if (idContent == VIDEODB_CONTENT_TVSHOWS)
      {
        strSQL = PrepareSQL("select distinct tvshow_view.c%02d from tvshow_view", VIDEODB_ID_TV_PREMIERED);
        extFilter.AppendGroup(PrepareSQL("tvshow_view.c%02d", VIDEODB_ID_TV_PREMIERED));
      }
      else if (idContent == VIDEODB_CONTENT_MUSICVIDEOS)
      {
        strSQL = "select musicvideo_view.premiered, count(1), count(files.playCount) from musicvideo_view ";
        extFilter.AppendJoin("join files on files.idFile = musicvideo_view.idFile");
        extFilter.AppendGroup("musicvideo_view.premiered");
      }
      else
        return false;
    }

    CVideoDbUrl videoUrl;
    if (!BuildSQL(strBaseDir, strSQL, extFilter, strSQL, videoUrl))
      return false;

    int iRowsFound = RunQuery(strSQL);
    if (iRowsFound <= 0)
      return iRowsFound == 0;

    if (m_profileManager.GetMasterProfile().getLockMode() != LOCK_MODE_EVERYONE && !g_passwordManager.bMasterUser)
    {
      std::map<int, std::pair<std::string,int> > mapYears;
      while (!m_pDS->eof())
      {
        int lYear = 0;
        std::string dateString = m_pDS->fv(0).get_asString();
        if (dateString.size() == 4)
          lYear = m_pDS->fv(0).get_asInt();
        else
        {
          CDateTime time;
          time.SetFromDateString(dateString);
          if (time.IsValid())
            lYear = time.GetYear();
        }
        auto it = mapYears.find(lYear);
        if (it == mapYears.end())
        {
          // check path
          if (g_passwordManager.IsDatabasePathUnlocked(m_pDS->fv("path.strPath").get_asString(),*CMediaSourceSettings::GetInstance().GetSources("video")))
          {
            std::string year = StringUtils::Format("%d", lYear);
            if (idContent == VIDEODB_CONTENT_MOVIES || idContent == VIDEODB_CONTENT_MUSICVIDEOS)
              mapYears.insert(std::pair<int, std::pair<std::string,int> >(lYear, std::pair<std::string,int>(year,m_pDS->fv(2).get_asInt())));
            else
              mapYears.insert(std::pair<int, std::pair<std::string,int> >(lYear, std::pair<std::string,int>(year,0)));
          }
        }
        m_pDS->next();
      }
      m_pDS->close();

      for (const auto &i : mapYears)
      {
        if (i.first == 0)
          continue;
        CFileItemPtr pItem(new CFileItem(i.second.first));

        CVideoDbUrl itemUrl = videoUrl;
        std::string path = StringUtils::Format("%i/", i.first);
        itemUrl.AppendPath(path);
        pItem->SetPath(itemUrl.ToString());

        pItem->m_bIsFolder=true;
        if (idContent == VIDEODB_CONTENT_MOVIES || idContent == VIDEODB_CONTENT_MUSICVIDEOS)
          pItem->GetVideoInfoTag()->SetPlayCount(i.second.second);
        items.Add(pItem);
      }
    }
    else
    {
      while (!m_pDS->eof())
      {
        int lYear = 0;
        std::string strLabel = m_pDS->fv(0).get_asString();
        if (strLabel.size() == 4)
          lYear = m_pDS->fv(0).get_asInt();
        else
        {
          CDateTime time;
          time.SetFromDateString(strLabel);
          if (time.IsValid())
          {
            lYear = time.GetYear();
            strLabel = StringUtils::Format("%i", lYear);
          }
        }
        if (lYear == 0)
        {
          m_pDS->next();
          continue;
        }
        CFileItemPtr pItem(new CFileItem(strLabel));

        CVideoDbUrl itemUrl = videoUrl;
        std::string path = StringUtils::Format("%i/", lYear);
        itemUrl.AppendPath(path);
        pItem->SetPath(itemUrl.ToString());

        pItem->m_bIsFolder=true;
        if (idContent == VIDEODB_CONTENT_MOVIES || idContent == VIDEODB_CONTENT_MUSICVIDEOS)
        {
          // fv(2) is the number of videos watched, fv(1) is the total number.  We set the playcount
          // only if the number of videos watched is equal to the total number (i.e. every video watched)
          pItem->GetVideoInfoTag()->SetPlayCount((m_pDS->fv(2).get_asInt() == m_pDS->fv(1).get_asInt()) ? 1 : 0);
        }

        // take care of dupes ..
        if (!items.Contains(pItem->GetPath()))
          items.Add(pItem);

        m_pDS->next();
      }
      m_pDS->close();
    }

    return true;
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s failed", __FUNCTION__);
  }
  return false;
}

bool CVideoDatabase::GetSortedVideos(const MediaType &mediaType, const std::string& strBaseDir, const SortDescription &sortDescription, CFileItemList& items, const Filter &filter /* = Filter() */)
{
  if (NULL == m_pDB.get() || NULL == m_pDS.get())
    return false;

  if (mediaType != MediaTypeMovie && mediaType != MediaTypeTvShow && mediaType != MediaTypeEpisode && mediaType != MediaTypeMusicVideo)
    return false;

  SortDescription sorting = sortDescription;
  if (sortDescription.sortBy == SortByFile ||
      sortDescription.sortBy == SortByTitle ||
      sortDescription.sortBy == SortBySortTitle ||
      sortDescription.sortBy == SortByLabel ||
      sortDescription.sortBy == SortByDateAdded ||
      sortDescription.sortBy == SortByRating ||
      sortDescription.sortBy == SortByUserRating ||
      sortDescription.sortBy == SortByYear ||
      sortDescription.sortBy == SortByLastPlayed ||
      sortDescription.sortBy == SortByPlaycount)
    sorting.sortAttributes = (SortAttribute)(sortDescription.sortAttributes | SortAttributeIgnoreFolders);

  bool success = false;
  if (mediaType == MediaTypeMovie)
    success = GetMoviesByWhere(strBaseDir, filter, items, sorting);
  else if (mediaType == MediaTypeTvShow)
    success = GetTvShowsByWhere(strBaseDir, filter, items, sorting);
  else if (mediaType == MediaTypeEpisode)
    success = GetEpisodesByWhere(strBaseDir, filter, items, true, sorting);
  else if (mediaType == MediaTypeMusicVideo)
    success = GetMusicVideosByWhere(strBaseDir, filter, items, true, sorting);
  else
    return false;

  items.SetContent(CMediaTypes::ToPlural(mediaType));
  return success;
}

bool CVideoDatabase::GetItems(const std::string &strBaseDir, CFileItemList &items, const Filter &filter /* = Filter() */, const SortDescription &sortDescription /* = SortDescription() */)
{
  CVideoDbUrl videoUrl;
  if (!videoUrl.FromString(strBaseDir))
    return false;

  return GetItems(strBaseDir, videoUrl.GetType(), videoUrl.GetItemType(), items, filter, sortDescription);
}

bool CVideoDatabase::GetItems(const std::string &strBaseDir, const std::string &mediaType, const std::string &itemType, CFileItemList &items, const Filter &filter /* = Filter() */, const SortDescription &sortDescription /* = SortDescription() */)
{
  VIDEODB_CONTENT_TYPE contentType;
  if (StringUtils::EqualsNoCase(mediaType, "movies"))
    contentType = VIDEODB_CONTENT_MOVIES;
  else if (StringUtils::EqualsNoCase(mediaType, "tvshows"))
  {
    if (StringUtils::EqualsNoCase(itemType, "episodes"))
      contentType = VIDEODB_CONTENT_EPISODES;
    else
      contentType = VIDEODB_CONTENT_TVSHOWS;
  }
  else if (StringUtils::EqualsNoCase(mediaType, "musicvideos"))
    contentType = VIDEODB_CONTENT_MUSICVIDEOS;
  else
    return false;

  return GetItems(strBaseDir, contentType, itemType, items, filter, sortDescription);
}

bool CVideoDatabase::GetItems(const std::string &strBaseDir, VIDEODB_CONTENT_TYPE mediaType, const std::string &itemType, CFileItemList &items, const Filter &filter /* = Filter() */, const SortDescription &sortDescription /* = SortDescription() */)
{
  if (StringUtils::EqualsNoCase(itemType, "movies") && (mediaType == VIDEODB_CONTENT_MOVIES || mediaType == VIDEODB_CONTENT_MOVIE_SETS))
    return GetMoviesByWhere(strBaseDir, filter, items, sortDescription);
  else if (StringUtils::EqualsNoCase(itemType, "tvshows") && mediaType == VIDEODB_CONTENT_TVSHOWS)
    return GetTvShowsByWhere(strBaseDir, filter, items, sortDescription);
  else if (StringUtils::EqualsNoCase(itemType, "musicvideos") && mediaType == VIDEODB_CONTENT_MUSICVIDEOS)
    return GetMusicVideosByWhere(strBaseDir, filter, items, true, sortDescription);
  else if (StringUtils::EqualsNoCase(itemType, "episodes") && mediaType == VIDEODB_CONTENT_EPISODES)
    return GetEpisodesByWhere(strBaseDir, filter, items, true, sortDescription);
  else if (StringUtils::EqualsNoCase(itemType, "seasons") && mediaType == VIDEODB_CONTENT_TVSHOWS)
    return GetSeasonsNav(strBaseDir, items);
  else if (StringUtils::EqualsNoCase(itemType, "genres"))
    return GetGenresNav(strBaseDir, items, mediaType, filter);
  else if (StringUtils::EqualsNoCase(itemType, "years"))
    return GetYearsNav(strBaseDir, items, mediaType, filter);
  else if (StringUtils::EqualsNoCase(itemType, "actors"))
    return GetActorsNav(strBaseDir, items, mediaType, filter);
  else if (StringUtils::EqualsNoCase(itemType, "directors"))
    return GetDirectorsNav(strBaseDir, items, mediaType, filter);
  else if (StringUtils::EqualsNoCase(itemType, "writers"))
    return GetWritersNav(strBaseDir, items, mediaType, filter);
  else if (StringUtils::EqualsNoCase(itemType, "studios"))
    return GetStudiosNav(strBaseDir, items, mediaType, filter);
  else if (StringUtils::EqualsNoCase(itemType, "sets"))
    return GetSetsNav(strBaseDir, items, mediaType, filter, !CServiceBroker::GetSettingsComponent()->GetSettings()->GetBool(CSettings::SETTING_VIDEOLIBRARY_GROUPSINGLEITEMSETS));
  else if (StringUtils::EqualsNoCase(itemType, "countries"))
    return GetCountriesNav(strBaseDir, items, mediaType, filter);
  else if (StringUtils::EqualsNoCase(itemType, "tags"))
    return GetTagsNav(strBaseDir, items, mediaType, filter);
  else if (StringUtils::EqualsNoCase(itemType, "artists") && mediaType == VIDEODB_CONTENT_MUSICVIDEOS)
    return GetActorsNav(strBaseDir, items, mediaType, filter);
  else if (StringUtils::EqualsNoCase(itemType, "albums") && mediaType == VIDEODB_CONTENT_MUSICVIDEOS)
    return GetMusicVideoAlbumsNav(strBaseDir, items, -1, filter);

  return false;
}

std::string CVideoDatabase::GetItemById(const std::string &itemType, int id)
{
  if (StringUtils::EqualsNoCase(itemType, "genres"))
    return GetGenreById(id);
  else if (StringUtils::EqualsNoCase(itemType, "years"))
    return StringUtils::Format("%d", id);
  else if (StringUtils::EqualsNoCase(itemType, "actors") ||
           StringUtils::EqualsNoCase(itemType, "directors") ||
           StringUtils::EqualsNoCase(itemType, "artists"))
    return GetPersonById(id);
  else if (StringUtils::EqualsNoCase(itemType, "studios"))
    return GetStudioById(id);
  else if (StringUtils::EqualsNoCase(itemType, "sets"))
    return GetSetById(id);
  else if (StringUtils::EqualsNoCase(itemType, "countries"))
    return GetCountryById(id);
  else if (StringUtils::EqualsNoCase(itemType, "tags"))
    return GetTagById(id);
  else if (StringUtils::EqualsNoCase(itemType, "albums"))
    return GetMusicVideoAlbumById(id);

  return "";
}

bool CVideoDatabase::GetTvShowsNav(const std::string& strBaseDir, CFileItemList& items,
                                  int idGenre /* = -1 */, int idYear /* = -1 */, int idActor /* = -1 */, int idDirector /* = -1 */, int idStudio /* = -1 */, int idTag /* = -1 */,
                                  const SortDescription &sortDescription /* = SortDescription() */, int getDetails /* = VideoDbDetailsNone */)
{
  CVideoDbUrl videoUrl;
  if (!videoUrl.FromString(strBaseDir))
    return false;

  if (idGenre != -1)
    videoUrl.AddOption("genreid", idGenre);
  else if (idStudio != -1)
    videoUrl.AddOption("studioid", idStudio);
  else if (idDirector != -1)
    videoUrl.AddOption("directorid", idDirector);
  else if (idYear != -1)
    videoUrl.AddOption("year", idYear);
  else if (idActor != -1)
    videoUrl.AddOption("actorid", idActor);
  else if (idTag != -1)
    videoUrl.AddOption("tagid", idTag);

  Filter filter;
  if (!CServiceBroker::GetSettingsComponent()->GetSettings()->GetBool(CSettings::SETTING_VIDEOLIBRARY_SHOWEMPTYTVSHOWS))
    filter.AppendWhere("totalCount IS NOT NULL AND totalCount > 0");
  return GetTvShowsByWhere(videoUrl.ToString(), filter, items, sortDescription, getDetails);
}

bool CVideoDatabase::GetTvShowsByWhere(const std::string& strBaseDir, const Filter &filter, CFileItemList& items, const SortDescription &sortDescription /* = SortDescription() */, int getDetails /* = VideoDbDetailsNone */)
{
  try
  {
    movieTime = 0;

    if (NULL == m_pDB.get()) return false;
    if (NULL == m_pDS.get()) return false;

    int total = -1;

    std::string strSQL = "SELECT %s FROM tvshow_view ";
    CVideoDbUrl videoUrl;
    std::string strSQLExtra;
    Filter extFilter = filter;
    SortDescription sorting = sortDescription;
    if (!BuildSQL(strBaseDir, strSQLExtra, extFilter, strSQLExtra, videoUrl, sorting))
      return false;

    // Apply the limiting directly here if there's no special sorting but limiting
    if (extFilter.limit.empty() &&
        sorting.sortBy == SortByNone &&
        (sorting.limitStart > 0 || sorting.limitEnd > 0))
    {
      total = (int)strtol(GetSingleValue(PrepareSQL(strSQL, "COUNT(1)") + strSQLExtra, m_pDS).c_str(), NULL, 10);
      strSQLExtra += DatabaseUtils::BuildLimitClause(sorting.limitEnd, sorting.limitStart);
    }

    strSQL = PrepareSQL(strSQL, !extFilter.fields.empty() ? extFilter.fields.c_str() : "*") + strSQLExtra;

    int iRowsFound = RunQuery(strSQL);
    if (iRowsFound <= 0)
      return iRowsFound == 0;

    // store the total value of items as a property
    if (total < iRowsFound)
      total = iRowsFound;
    items.SetProperty("total", total);

    DatabaseResults results;
    results.reserve(iRowsFound);
    if (!SortUtils::SortFromDataset(sorting, MediaTypeTvShow, m_pDS, results))
      return false;

    // get data from returned rows
    items.Reserve(results.size());
    const query_data &data = m_pDS->get_result_set().records;
    for (const auto &i : results)
    {
      unsigned int targetRow = (unsigned int)i.at(FieldRow).asInteger();
      const dbiplus::sql_record* const record = data.at(targetRow);

      CFileItemPtr pItem(new CFileItem());
      CVideoInfoTag movie = GetDetailsForTvShow(record, getDetails, pItem.get());
      if (m_profileManager.GetMasterProfile().getLockMode() == LOCK_MODE_EVERYONE ||
           g_passwordManager.bMasterUser                                     ||
           g_passwordManager.IsDatabasePathUnlocked(movie.m_strPath, *CMediaSourceSettings::GetInstance().GetSources("video")))
      {
        pItem->SetFromVideoInfoTag(movie);

        CVideoDbUrl itemUrl = videoUrl;
        std::string path = StringUtils::Format("%i/", record->at(0).get_asInt());
        itemUrl.AppendPath(path);
        pItem->SetPath(itemUrl.ToString());

        pItem->SetOverlayImage(CGUIListItem::ICON_OVERLAY_UNWATCHED, (pItem->GetVideoInfoTag()->GetPlayCount() > 0) && (pItem->GetVideoInfoTag()->m_iEpisode > 0));
        items.Add(pItem);
      }
    }

    // cleanup
    m_pDS->close();
    return true;
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s failed", __FUNCTION__);
  }
  return false;
}

bool CVideoDatabase::GetInProgressTvShowsNav(const std::string& strBaseDir, CFileItemList& items, unsigned int limit /* = 0 */, int getDetails /* = VideoDbDetailsNone */)
{
  Filter filter;
  filter.order = PrepareSQL("c%02d", VIDEODB_ID_TV_TITLE);
  filter.where = "watchedCount != 0 AND totalCount != watchedCount";
  return GetTvShowsByWhere(strBaseDir, filter, items, SortDescription(), getDetails);
}

std::string CVideoDatabase::GetGenreById(int id)
{
  return GetSingleValue("genre", "name", PrepareSQL("genre_id=%i", id));
}

std::string CVideoDatabase::GetCountryById(int id)
{
  return GetSingleValue("country", "name", PrepareSQL("country_id=%i", id));
}

std::string CVideoDatabase::GetPersonById(int id)
{
  return GetSingleValue("actor", "name", PrepareSQL("actor_id=%i", id));
}

std::string CVideoDatabase::GetStudioById(int id)
{
  return GetSingleValue("studio", "name", PrepareSQL("studio_id=%i", id));
}

std::string CVideoDatabase::GetTvShowTitleById(int id)
{
  return GetSingleValue("tvshow", PrepareSQL("c%02d", VIDEODB_ID_TV_TITLE), PrepareSQL("idShow=%i", id));
}

int CVideoDatabase::GetTvShowForEpisode(int idEpisode)
{
  try
  {
    if (NULL == m_pDB.get()) return false;
    if (NULL == m_pDS2.get()) return false;

    // make sure we use m_pDS2, as this is called in loops using m_pDS
    std::string strSQL=PrepareSQL("select idShow from episode where idEpisode=%i", idEpisode);
    m_pDS2->query( strSQL );

    int result=-1;
    if (!m_pDS2->eof())
      result=m_pDS2->fv(0).get_asInt();
    m_pDS2->close();

    return result;
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (%i) failed", __FUNCTION__, idEpisode);
  }
  return false;
}

bool CVideoDatabase::HasContent()
{
  return (HasContent(VIDEODB_CONTENT_MOVIES) ||
          HasContent(VIDEODB_CONTENT_TVSHOWS) ||
          HasContent(VIDEODB_CONTENT_MUSICVIDEOS));
}

bool CVideoDatabase::HasContent(VIDEODB_CONTENT_TYPE type)
{
  bool result = false;
  try
  {
    if (NULL == m_pDB.get()) return false;
    if (NULL == m_pDS.get()) return false;

    std::string sql;
    if (type == VIDEODB_CONTENT_MOVIES)
      sql = "select count(1) from movie";
    else if (type == VIDEODB_CONTENT_TVSHOWS)
      sql = "select count(1) from tvshow";
    else if (type == VIDEODB_CONTENT_MUSICVIDEOS)
      sql = "select count(1) from musicvideo";
    m_pDS->query( sql );

    if (!m_pDS->eof())
      result = (m_pDS->fv(0).get_asInt() > 0);

    m_pDS->close();
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s failed", __FUNCTION__);
  }
  return result;
}

void CVideoDatabase::GetTvShowGenresByName(const std::string& strSearch, CFileItemList& items)
{
  std::string strSQL;

  try
  {
    if (NULL == m_pDB.get()) return;
    if (NULL == m_pDS.get()) return;

    if (m_profileManager.GetMasterProfile().getLockMode() != LOCK_MODE_EVERYONE && !g_passwordManager.bMasterUser)
      strSQL=PrepareSQL("SELECT genre.genre_id, genre.name, path.strPath FROM genre INNER JOIN genre_link ON genre_link.genre_id=genre.genre_id INNER JOIN tvshow ON genre_link.media_id=tvshow.idShow INNER JOIN tvshowlinkpath ON tvshowlinkpath.idShow=tvshow.idShow INNER JOIN path ON path.idPath=tvshowlinkpath.idPath WHERE genre_link.media_type='tvshow' AND genre.name LIKE '%%%s%%'", strSearch.c_str());
    else
      strSQL=PrepareSQL("SELECT DISTINCT genre.genre_id, genre.name FROM genre INNER JOIN genre_link ON genre_link.genre_id=genre.genre_id WHERE genre_link.media_type='tvshow' AND name LIKE '%%%s%%'", strSearch.c_str());
    m_pDS->query( strSQL );

    while (!m_pDS->eof())
    {
      if (m_profileManager.GetMasterProfile().getLockMode() != LOCK_MODE_EVERYONE && !g_passwordManager.bMasterUser)
        if (!g_passwordManager.IsDatabasePathUnlocked(m_pDS->fv("path.strPath").get_asString(),*CMediaSourceSettings::GetInstance().GetSources("video")))
        {
          m_pDS->next();
          continue;
        }

      CFileItemPtr pItem(new CFileItem(m_pDS->fv(1).get_asString()));
      std::string strDir = StringUtils::Format("%i/", m_pDS->fv(0).get_asInt());
      pItem->SetPath("videodb://tvshows/genres/"+ strDir);
      pItem->m_bIsFolder=true;
      items.Add(pItem);
      m_pDS->next();
    }
    m_pDS->close();
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (%s) failed", __FUNCTION__, strSQL.c_str());
  }
}

void CVideoDatabase::GetTvShowsActorsByName(const std::string& strSearch, CFileItemList& items)
{
  std::string strSQL;

  try
  {
    if (NULL == m_pDB.get()) return;
    if (NULL == m_pDS.get()) return;

    if (m_profileManager.GetMasterProfile().getLockMode() != LOCK_MODE_EVERYONE && !g_passwordManager.bMasterUser)
      strSQL=PrepareSQL("SELECT actor.actor_id, actor.name, path.strPath FROM actor INNER JOIN actor_link ON actor_link.actor_id=actor.actor_id INNER JOIN tvshow ON actor_link.media_id=tvshow.idShow INNER JOIN tvshowlinkpath ON tvshowlinkpath.idPath=tvshow.idShow INNER JOIN path ON path.idPath=tvshowlinkpath.idPath WHERE actor_link.media_type='tvshow' AND actor.name LIKE '%%%s%%'", strSearch.c_str());
    else
      strSQL=PrepareSQL("SELECT DISTINCT actor.actor_id, actor.name FROM actor INNER JOIN actor_link ON actor_link.actor_id=actor.actor_id INNER JOIN tvshow ON actor_link.media_id=tvshow.idShow WHERE actor_link.media_type='tvshow' AND actor.name LIKE '%%%s%%'",strSearch.c_str());
    m_pDS->query( strSQL );

    while (!m_pDS->eof())
    {
      if (m_profileManager.GetMasterProfile().getLockMode() != LOCK_MODE_EVERYONE && !g_passwordManager.bMasterUser)
        if (!g_passwordManager.IsDatabasePathUnlocked(m_pDS->fv("path.strPath").get_asString(),*CMediaSourceSettings::GetInstance().GetSources("video")))
        {
          m_pDS->next();
          continue;
        }

      CFileItemPtr pItem(new CFileItem(m_pDS->fv(1).get_asString()));
      std::string strDir = StringUtils::Format("%i/", m_pDS->fv(0).get_asInt());
      pItem->SetPath("videodb://tvshows/actors/"+ strDir);
      pItem->m_bIsFolder=true;
      items.Add(pItem);
      m_pDS->next();
    }
    m_pDS->close();
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (%s) failed", __FUNCTION__, strSQL.c_str());
  }
}

void CVideoDatabase::GetTvShowsByName(const std::string& strSearch, CFileItemList& items)
{
  std::string strSQL;

  try
  {
    if (NULL == m_pDB.get()) return;
    if (NULL == m_pDS.get()) return;

    if (m_profileManager.GetMasterProfile().getLockMode() != LOCK_MODE_EVERYONE && !g_passwordManager.bMasterUser)
      strSQL = PrepareSQL("SELECT tvshow.idShow, tvshow.c%02d, path.strPath FROM tvshow INNER JOIN tvshowlinkpath ON tvshowlinkpath.idShow=tvshow.idShow INNER JOIN path ON path.idPath=tvshowlinkpath.idPath WHERE tvshow.c%02d LIKE '%%%s%%'", VIDEODB_ID_TV_TITLE, VIDEODB_ID_TV_TITLE, strSearch.c_str());
    else
      strSQL = PrepareSQL("select tvshow.idShow,tvshow.c%02d from tvshow where tvshow.c%02d like '%%%s%%'",VIDEODB_ID_TV_TITLE,VIDEODB_ID_TV_TITLE,strSearch.c_str());
    m_pDS->query( strSQL );

    while (!m_pDS->eof())
    {
      if (m_profileManager.GetMasterProfile().getLockMode() != LOCK_MODE_EVERYONE && !g_passwordManager.bMasterUser)
        if (!g_passwordManager.IsDatabasePathUnlocked(m_pDS->fv("path.strPath").get_asString(),*CMediaSourceSettings::GetInstance().GetSources("video")))
        {
          m_pDS->next();
          continue;
        }

      CFileItemPtr pItem(new CFileItem(m_pDS->fv(1).get_asString()));
      std::string strDir = StringUtils::Format("tvshows/titles/%i/", m_pDS->fv("tvshow.idShow").get_asInt());

      pItem->SetPath("videodb://"+ strDir);
      pItem->m_bIsFolder=true;
      pItem->GetVideoInfoTag()->m_iDbId = m_pDS->fv("tvshow.idShow").get_asInt();
      items.Add(pItem);
      m_pDS->next();
    }
    m_pDS->close();
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (%s) failed", __FUNCTION__, strSQL.c_str());
  }
}

void CVideoDatabase::GetTvShowsDirectorsByName(const std::string& strSearch, CFileItemList& items)
{
  std::string strSQL;

  try
  {
    if (NULL == m_pDB.get()) return;
    if (NULL == m_pDS.get()) return;

    if (m_profileManager.GetMasterProfile().getLockMode() != LOCK_MODE_EVERYONE && !g_passwordManager.bMasterUser)
      strSQL = PrepareSQL("SELECT DISTINCT director_link.actor_id, actor.name, path.strPath FROM actor INNER JOIN director_link ON director_link.actor_id=actor.actor_id INNER JOIN tvshow ON director_link.media_id=tvshow.idShow INNER JOIN tvshowlinkpath ON tvshowlinkpath.idShow=tvshow.idShow INNER JOIN path ON path.idPath=tvshowlinkpath.idPath WHERE director_link.media_type='tvshow' AND actor.name LIKE '%%%s%%'", strSearch.c_str());
    else
      strSQL = PrepareSQL("SELECT DISTINCT director_link.actor_id, actor.name FROM actor INNER JOIN director_link ON director_link.actor_id=actor.actor_id INNER JOIN tvshow ON director_link.media_id=tvshow.idShow WHERE director_link.media_type='tvshow' AND actor.name LIKE '%%%s%%'", strSearch.c_str());

    m_pDS->query( strSQL );

    while (!m_pDS->eof())
    {
      if (m_profileManager.GetMasterProfile().getLockMode() != LOCK_MODE_EVERYONE && !g_passwordManager.bMasterUser)
        if (!g_passwordManager.IsDatabasePathUnlocked(m_pDS->fv("path.strPath").get_asString(),*CMediaSourceSettings::GetInstance().GetSources("video")))
        {
          m_pDS->next();
          continue;
        }

      std::string strDir = StringUtils::Format("%i/", m_pDS->fv(0).get_asInt());
      CFileItemPtr pItem(new CFileItem(m_pDS->fv(1).get_asString()));

      pItem->SetPath("videodb://tvshows/directors/"+ strDir);
      pItem->m_bIsFolder=true;
      items.Add(pItem);
      m_pDS->next();
    }
    m_pDS->close();
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (%s) failed", __FUNCTION__, strSQL.c_str());
  }
}

void CVideoDatabase::CleanDatabase(CGUIDialogProgressBarHandle* handle, const std::set<int>& paths, bool showProgress)
{
  CGUIDialogProgress *progress=NULL;
  try
  {
    if (NULL == m_pDB.get()) return;
    if (NULL == m_pDS.get()) return;
    if (NULL == m_pDS2.get()) return;

    unsigned int time = XbmcThreads::SystemClockMillis();
    CLog::Log(LOGNOTICE, "%s: Starting videodatabase cleanup ..", __FUNCTION__);
    CServiceBroker::GetAnnouncementManager()->Announce(ANNOUNCEMENT::VideoLibrary, "xbmc", "OnCleanStarted");

    BeginTransaction();

    // find all the files
    std::string sql = "SELECT files.idFile, files.strFileName, path.strPath FROM files INNER JOIN path ON path.idPath=files.idPath";
    if (!paths.empty())
    {
      std::string strPaths;
      for (const auto &i : paths)
        strPaths += StringUtils::Format(",%i", i);
      sql += PrepareSQL(" AND path.idPath IN (%s)", strPaths.substr(1).c_str());
    }

    m_pDS2->query(sql);
    if (m_pDS2->num_rows() == 0) return;

    if (handle)
    {
      handle->SetTitle(g_localizeStrings.Get(700));
      handle->SetText("");
    }
    else if (showProgress)
    {
      progress = CServiceBroker::GetGUI()->GetWindowManager().GetWindow<CGUIDialogProgress>(WINDOW_DIALOG_PROGRESS);
      if (progress)
      {
        progress->SetHeading(CVariant{700});
        progress->SetLine(0, CVariant{""});
        progress->SetLine(1, CVariant{313});
        progress->SetLine(2, CVariant{330});
        progress->SetPercentage(0);
        progress->Open();
        progress->ShowProgressBar(true);
      }
    }

    std::string filesToTestForDelete;
    VECSOURCES videoSources(*CMediaSourceSettings::GetInstance().GetSources("video"));
    g_mediaManager.GetRemovableDrives(videoSources);

    int total = m_pDS2->num_rows();
    int current = 0;

    while (!m_pDS2->eof())
    {
      std::string path = m_pDS2->fv("path.strPath").get_asString();
      std::string fileName = m_pDS2->fv("files.strFileName").get_asString();
      std::string fullPath;
      ConstructPath(fullPath, path, fileName);

      // get the first stacked file
      if (URIUtils::IsStack(fullPath))
        fullPath = CStackDirectory::GetFirstStackedFile(fullPath);

      // get the actual archive path
      if (URIUtils::IsInArchive(fullPath))
        fullPath = CURL(fullPath).GetHostName();

      bool del = true;
      if (URIUtils::IsPlugin(fullPath))
      {
        SScanSettings settings;
        bool foundDirectly = false;
        ScraperPtr scraper = GetScraperForPath(fullPath, settings, foundDirectly);
        if (scraper && CPluginDirectory::CheckExists(TranslateContent(scraper->Content()), fullPath))
          del = false;
      }
      else
      {
        // remove optical, non-existing files, files with no matching source
        bool bIsSource;
        if (!URIUtils::IsOnDVD(fullPath) && CFile::Exists(fullPath, false) &&
            CUtil::GetMatchingSource(fullPath, videoSources, bIsSource) >= 0)
          del = false;
      }
      if (del)
        filesToTestForDelete += m_pDS2->fv("files.idFile").get_asString() + ",";

      if (handle == NULL && progress != NULL)
      {
        int percentage = current * 100 / total;
        if (percentage > progress->GetPercentage())
        {
          progress->SetPercentage(percentage);
          progress->Progress();
        }
        if (progress->IsCanceled())
        {
          progress->Close();
          m_pDS2->close();
          CServiceBroker::GetAnnouncementManager()->Announce(ANNOUNCEMENT::VideoLibrary, "xbmc", "OnCleanFinished");
          return;
        }
      }
      else if (handle != NULL)
        handle->SetPercentage(current * 100 / (float)total);

      m_pDS2->next();
      current++;
    }
    m_pDS2->close();

    std::string filesToDelete;

    // Add any files that don't have a valid idPath entry to the filesToDelete list.
    m_pDS->query("SELECT files.idFile FROM files WHERE NOT EXISTS (SELECT 1 FROM path WHERE path.idPath = files.idPath)");
    while (!m_pDS->eof())
    {
      std::string file = m_pDS->fv("files.idFile").get_asString() + ",";
      filesToTestForDelete += file;
      filesToDelete += file;

      m_pDS->next();
    }
    m_pDS->close();

    std::map<int, bool> pathsDeleteDecisions;
    std::vector<int> movieIDs;
    std::vector<int> tvshowIDs;
    std::vector<int> episodeIDs;
    std::vector<int> musicVideoIDs;

    if (!filesToTestForDelete.empty())
    {
      StringUtils::TrimRight(filesToTestForDelete, ",");

      movieIDs = CleanMediaType(MediaTypeMovie, filesToTestForDelete, pathsDeleteDecisions, filesToDelete, !showProgress);
      episodeIDs = CleanMediaType(MediaTypeEpisode, filesToTestForDelete, pathsDeleteDecisions, filesToDelete, !showProgress);
      musicVideoIDs = CleanMediaType(MediaTypeMusicVideo, filesToTestForDelete, pathsDeleteDecisions, filesToDelete, !showProgress);
    }

    if (progress != NULL)
    {
      progress->SetPercentage(100);
      progress->Progress();
    }

    if (!filesToDelete.empty())
    {
      filesToDelete = "(" + StringUtils::TrimRight(filesToDelete, ",") + ")";

      // Clean hashes of all paths that files are deleted from
      // Otherwise there is a mismatch between the path contents and the hash in the
      // database, leading to potentially missed items on re-scan (if deleted files are
      // later re-added to a source)
      CLog::LogF(LOGDEBUG, LOGDATABASE, "Cleaning path hashes");
      m_pDS->query("SELECT DISTINCT strPath FROM path JOIN files ON files.idPath=path.idPath WHERE files.idFile IN " + filesToDelete);
      int pathHashCount = m_pDS->num_rows();
      while (!m_pDS->eof())
      {
        InvalidatePathHash(m_pDS->fv("strPath").get_asString());
        m_pDS->next();
      }
      CLog::LogF(LOGDEBUG, LOGDATABASE, "Cleaned {} path hashes", pathHashCount);

      CLog::Log(LOGDEBUG, LOGDATABASE, "%s: Cleaning files table", __FUNCTION__);
      sql = "DELETE FROM files WHERE idFile IN " + filesToDelete;
      m_pDS->exec(sql);
    }

    if (!movieIDs.empty())
    {
      std::string moviesToDelete;
      for (const auto &i : movieIDs)
        moviesToDelete += StringUtils::Format("%i,", i);
      moviesToDelete = "(" + StringUtils::TrimRight(moviesToDelete, ",") + ")";

      CLog::Log(LOGDEBUG, LOGDATABASE, "%s: Cleaning movie table", __FUNCTION__);
      sql = "DELETE FROM movie WHERE idMovie IN " + moviesToDelete;
      m_pDS->exec(sql);
    }

    if (!episodeIDs.empty())
    {
      std::string episodesToDelete;
      for (const auto &i : episodeIDs)
        episodesToDelete += StringUtils::Format("%i,", i);
      episodesToDelete = "(" + StringUtils::TrimRight(episodesToDelete, ",") + ")";

      CLog::Log(LOGDEBUG, LOGDATABASE, "%s: Cleaning episode table", __FUNCTION__);
      sql = "DELETE FROM episode WHERE idEpisode IN " + episodesToDelete;
      m_pDS->exec(sql);
    }

    CLog::Log(LOGDEBUG, LOGDATABASE, "%s: Cleaning paths that don't exist and have content set...", __FUNCTION__);
    sql = "SELECT path.idPath, path.strPath, path.idParentPath FROM path "
            "WHERE NOT ((strContent IS NULL OR strContent = '') "
                   "AND (strSettings IS NULL OR strSettings = '') "
                   "AND (strHash IS NULL OR strHash = '') "
                   "AND (exclude IS NULL OR exclude != 1))";
    m_pDS2->query(sql);
    std::string strIds;
    while (!m_pDS2->eof())
    {
      auto pathsDeleteDecision = pathsDeleteDecisions.find(m_pDS2->fv(0).get_asInt());
      // Check if we have a decision for the parent path
      auto pathsDeleteDecisionByParent = pathsDeleteDecisions.find(m_pDS2->fv(2).get_asInt());
      std::string path = m_pDS2->fv(1).get_asString();

      bool exists = false;
      if (URIUtils::IsPlugin(path))
      {
        SScanSettings settings;
        bool foundDirectly = false;
        ScraperPtr scraper = GetScraperForPath(path, settings, foundDirectly);
        if (scraper && CPluginDirectory::CheckExists(TranslateContent(scraper->Content()), path))
          exists = true;
      }
      else
        exists = CDirectory::Exists(path, false);

      if (((pathsDeleteDecision != pathsDeleteDecisions.end() && pathsDeleteDecision->second) ||
           (pathsDeleteDecision == pathsDeleteDecisions.end() && !exists)) &&
          ((pathsDeleteDecisionByParent != pathsDeleteDecisions.end() && pathsDeleteDecisionByParent->second) ||
           (pathsDeleteDecisionByParent == pathsDeleteDecisions.end())))
        strIds += m_pDS2->fv(0).get_asString() + ",";

      m_pDS2->next();
    }
    m_pDS2->close();

    if (!strIds.empty())
    {
      sql = PrepareSQL("DELETE FROM path WHERE idPath IN (%s)", StringUtils::TrimRight(strIds, ",").c_str());
      m_pDS->exec(sql);
      sql = "DELETE FROM tvshowlinkpath WHERE NOT EXISTS (SELECT 1 FROM path WHERE path.idPath = tvshowlinkpath.idPath)";
      m_pDS->exec(sql);
    }

    CLog::Log(LOGDEBUG, LOGDATABASE, "%s: Cleaning tvshow table", __FUNCTION__);

    std::string tvshowsToDelete;
    sql = "SELECT idShow FROM tvshow WHERE NOT EXISTS (SELECT 1 FROM tvshowlinkpath WHERE tvshowlinkpath.idShow = tvshow.idShow)";
    m_pDS->query(sql);
    while (!m_pDS->eof())
    {
      tvshowIDs.push_back(m_pDS->fv(0).get_asInt());
      tvshowsToDelete += m_pDS->fv(0).get_asString() + ",";
      m_pDS->next();
    }
    m_pDS->close();
    if (!tvshowsToDelete.empty())
    {
      sql = "DELETE FROM tvshow WHERE idShow IN (" + StringUtils::TrimRight(tvshowsToDelete, ",") + ")";
      m_pDS->exec(sql);
    }

    if (!musicVideoIDs.empty())
    {
      std::string musicVideosToDelete;
      for (const auto &i : musicVideoIDs)
        musicVideosToDelete += StringUtils::Format("%i,", i);
      musicVideosToDelete = "(" + StringUtils::TrimRight(musicVideosToDelete, ",") + ")";

      CLog::Log(LOGDEBUG, LOGDATABASE, "%s: Cleaning musicvideo table", __FUNCTION__);
      sql = "DELETE FROM musicvideo WHERE idMVideo IN " + musicVideosToDelete;
      m_pDS->exec(sql);
    }

    CLog::Log(LOGDEBUG, LOGDATABASE, "%s: Cleaning path table", __FUNCTION__);
    sql = StringUtils::Format("DELETE FROM path "
                                "WHERE (strContent IS NULL OR strContent = '') "
                                  "AND (strSettings IS NULL OR strSettings = '') "
                                  "AND (strHash IS NULL OR strHash = '') "
                                  "AND (exclude IS NULL OR exclude != 1) "
                                  "AND (idParentPath IS NULL OR NOT EXISTS (SELECT 1 FROM (SELECT idPath FROM path) as parentPath WHERE parentPath.idPath = path.idParentPath)) " // MySQL only fix (#5007)
                                  "AND NOT EXISTS (SELECT 1 FROM files WHERE files.idPath = path.idPath) "
                                  "AND NOT EXISTS (SELECT 1 FROM tvshowlinkpath WHERE tvshowlinkpath.idPath = path.idPath) "
                                  "AND NOT EXISTS (SELECT 1 FROM movie WHERE movie.c%02d = path.idPath) "
                                  "AND NOT EXISTS (SELECT 1 FROM episode WHERE episode.c%02d = path.idPath) "
                                  "AND NOT EXISTS (SELECT 1 FROM musicvideo WHERE musicvideo.c%02d = path.idPath)"
                , VIDEODB_ID_PARENTPATHID, VIDEODB_ID_EPISODE_PARENTPATHID, VIDEODB_ID_MUSICVIDEO_PARENTPATHID );
    m_pDS->exec(sql);

    CLog::Log(LOGDEBUG, LOGDATABASE, "%s: Cleaning genre table", __FUNCTION__);
    sql = "DELETE FROM genre "
            "WHERE NOT EXISTS (SELECT 1 FROM genre_link WHERE genre_link.genre_id = genre.genre_id)";
    m_pDS->exec(sql);

    CLog::Log(LOGDEBUG, LOGDATABASE, "%s: Cleaning country table", __FUNCTION__);
    sql = "DELETE FROM country WHERE NOT EXISTS (SELECT 1 FROM country_link WHERE country_link.country_id = country.country_id)";
    m_pDS->exec(sql);

    CLog::Log(LOGDEBUG, LOGDATABASE, "%s: Cleaning actor table of actors, directors and writers", __FUNCTION__);
    sql = "DELETE FROM actor "
            "WHERE NOT EXISTS (SELECT 1 FROM actor_link WHERE actor_link.actor_id = actor.actor_id) "
              "AND NOT EXISTS (SELECT 1 FROM director_link WHERE director_link.actor_id = actor.actor_id) "
              "AND NOT EXISTS (SELECT 1 FROM writer_link WHERE writer_link.actor_id = actor.actor_id)";
    m_pDS->exec(sql);

    CLog::Log(LOGDEBUG, LOGDATABASE, "%s: Cleaning studio table", __FUNCTION__);
    sql = "DELETE FROM studio "
            "WHERE NOT EXISTS (SELECT 1 FROM studio_link WHERE studio_link.studio_id = studio.studio_id)";
    m_pDS->exec(sql);

    CLog::Log(LOGDEBUG, LOGDATABASE, "%s: Cleaning set table", __FUNCTION__);
    sql = "DELETE FROM sets WHERE NOT EXISTS (SELECT 1 FROM movie WHERE movie.idSet = sets.idSet)";
    m_pDS->exec(sql);

    CommitTransaction();

    if (handle)
      handle->SetTitle(g_localizeStrings.Get(331));

    Compress(false);

    CUtil::DeleteVideoDatabaseDirectoryCache();

    time = XbmcThreads::SystemClockMillis() - time;
    CLog::Log(LOGNOTICE, "%s: Cleaning videodatabase done. Operation took %s", __FUNCTION__, StringUtils::SecondsToTimeString(time / 1000).c_str());

    for (const auto &i : movieIDs)
      AnnounceRemove(MediaTypeMovie, i, true);

    for (const auto &i : episodeIDs)
      AnnounceRemove(MediaTypeEpisode, i, true);

    for (const auto &i : tvshowIDs)
      AnnounceRemove(MediaTypeTvShow, i, true);

    for (const auto &i : musicVideoIDs)
      AnnounceRemove(MediaTypeMusicVideo, i, true);
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s failed", __FUNCTION__);
    RollbackTransaction();
  }
  if (progress)
    progress->Close();

  CServiceBroker::GetAnnouncementManager()->Announce(ANNOUNCEMENT::VideoLibrary, "xbmc", "OnCleanFinished");
}

std::vector<int> CVideoDatabase::CleanMediaType(const std::string &mediaType, const std::string &cleanableFileIDs,
                                                std::map<int, bool> &pathsDeleteDecisions, std::string &deletedFileIDs, bool silent)
{
  std::vector<int> cleanedIDs;
  if (mediaType.empty() || cleanableFileIDs.empty())
    return cleanedIDs;

  std::string table = mediaType;
  std::string idField;
  std::string parentPathIdField;
  bool isEpisode = false;
  if (mediaType == MediaTypeMovie)
  {
    idField = "idMovie";
    parentPathIdField = StringUtils::Format("%s.c%02d", table.c_str(), VIDEODB_ID_PARENTPATHID);
  }
  else if (mediaType == MediaTypeEpisode)
  {
    idField = "idEpisode";
    parentPathIdField = "showPath.idParentPath";
    isEpisode = true;
  }
  else if (mediaType == MediaTypeMusicVideo)
  {
    idField = "idMVideo";
    parentPathIdField = StringUtils::Format("%s.c%02d", table.c_str(), VIDEODB_ID_MUSICVIDEO_PARENTPATHID);
  }
  else
    return cleanedIDs;

  // now grab them media items
  std::string sql = PrepareSQL("SELECT %s.%s, %s.idFile, path.idPath, parentPath.strPath FROM %s "
                                 "JOIN files ON files.idFile = %s.idFile "
                                 "JOIN path ON path.idPath = files.idPath ",
                               table.c_str(), idField.c_str(), table.c_str(), table.c_str(),
                               table.c_str());

  if (isEpisode)
    sql += "JOIN tvshowlinkpath ON tvshowlinkpath.idShow = episode.idShow JOIN path AS showPath ON showPath.idPath=tvshowlinkpath.idPath ";

  sql += PrepareSQL("LEFT JOIN path as parentPath ON parentPath.idPath = %s "
                    "WHERE %s.idFile IN (%s)",
                    parentPathIdField.c_str(),
                    table.c_str(), cleanableFileIDs.c_str());

  VECSOURCES videoSources(*CMediaSourceSettings::GetInstance().GetSources("video"));
  g_mediaManager.GetRemovableDrives(videoSources);

  // map of parent path ID to boolean pair (if not exists and user choice)
  std::map<int, std::pair<bool, bool> > sourcePathsDeleteDecisions;
  m_pDS2->query(sql);
  while (!m_pDS2->eof())
  {
    bool del = true;
    if (m_pDS2->fv(3).get_isNull() == false)
    {
      std::string parentPath = m_pDS2->fv(3).get_asString();

      // try to find the source path the parent path belongs to
      SScanSettings scanSettings;
      std::string sourcePath;
      GetSourcePath(parentPath, sourcePath, scanSettings);

      bool bIsSourceName;
      bool sourceNotFound = (CUtil::GetMatchingSource(parentPath, videoSources, bIsSourceName) < 0);

      if (sourceNotFound && sourcePath.empty())
        sourcePath = parentPath;

      int sourcePathID = GetPathId(sourcePath);
      auto sourcePathsDeleteDecision = sourcePathsDeleteDecisions.find(sourcePathID);
      if (sourcePathsDeleteDecision == sourcePathsDeleteDecisions.end())
      {
        bool sourcePathNotExists = (sourceNotFound || !CDirectory::Exists(sourcePath, false));
        // if the parent path exists, the file will be deleted without asking
        // if the parent path doesn't exist or does not belong to a valid media source,
        // ask the user whether to remove all items it contained
        if (sourcePathNotExists)
        {
          // in silent mode assume that the files are just temporarily missing
          if (silent)
            del = false;
          else
          {
            CGUIDialogYesNo* pDialog = CServiceBroker::GetGUI()->GetWindowManager().GetWindow<CGUIDialogYesNo>(WINDOW_DIALOG_YES_NO);
            if (pDialog != NULL)
            {
              CURL sourceUrl(sourcePath);
              pDialog->SetHeading(CVariant{15012});
              pDialog->SetText(CVariant{StringUtils::Format(g_localizeStrings.Get(15013).c_str(), sourceUrl.GetWithoutUserDetails().c_str())});
              pDialog->SetChoice(0, CVariant{15015});
              pDialog->SetChoice(1, CVariant{15014});
              pDialog->Open();

              del = !pDialog->IsConfirmed();
            }
          }
        }

        sourcePathsDeleteDecisions.insert(std::make_pair(sourcePathID, std::make_pair(sourcePathNotExists, del)));
        pathsDeleteDecisions.insert(std::make_pair(sourcePathID, sourcePathNotExists && del));
      }
      // the only reason not to delete the file is if the parent path doesn't
      // exist and the user decided to delete all the items it contained
      else if (sourcePathsDeleteDecision->second.first &&
               !sourcePathsDeleteDecision->second.second)
        del = false;

      if (scanSettings.parent_name)
        pathsDeleteDecisions.insert(std::make_pair(m_pDS2->fv(2).get_asInt(), del));
    }

    if (del)
    {
      deletedFileIDs += m_pDS2->fv(1).get_asString() + ",";
      cleanedIDs.push_back(m_pDS2->fv(0).get_asInt());
    }

    m_pDS2->next();
  }
  m_pDS2->close();

  return cleanedIDs;
}

void CVideoDatabase::ConstructPath(std::string& strDest, const std::string& strPath, const std::string& strFileName)
{
  if (URIUtils::IsStack(strFileName) ||
      URIUtils::IsInArchive(strFileName) || URIUtils::IsPlugin(strPath))
    strDest = strFileName;
  else
    strDest = URIUtils::AddFileToFolder(strPath, strFileName);
}

void CVideoDatabase::SplitPath(const std::string& strFileNameAndPath, std::string& strPath, std::string& strFileName)
{
  if (URIUtils::IsStack(strFileNameAndPath) || StringUtils::StartsWithNoCase(strFileNameAndPath, "rar://") || StringUtils::StartsWithNoCase(strFileNameAndPath, "zip://"))
  {
    URIUtils::GetParentPath(strFileNameAndPath,strPath);
    strFileName = strFileNameAndPath;
  }
  else if (URIUtils::IsPlugin(strFileNameAndPath))
  {
    CURL url(strFileNameAndPath);
    strPath = url.GetOptions().empty() ? url.GetWithoutFilename() : url.GetWithoutOptions();
    strFileName = strFileNameAndPath;
  }
  else
  {
    URIUtils::Split(strFileNameAndPath, strPath, strFileName);
    // Keep protocol options as part of the path
    if (URIUtils::IsURL(strFileNameAndPath))
    {
      CURL url(strFileNameAndPath);
      if (!url.GetProtocolOptions().empty())
        strPath += "|" + url.GetProtocolOptions();
    }
  }
}

void CVideoDatabase::InvalidatePathHash(const std::string& strPath)
{
  SScanSettings settings;
  bool foundDirectly;
  ScraperPtr info = GetScraperForPath(strPath,settings,foundDirectly);
  SetPathHash(strPath,"");
  if (!info)
    return;
  if (info->Content() == CONTENT_TVSHOWS || (info->Content() == CONTENT_MOVIES && !foundDirectly)) // if we scan by folder name we need to invalidate parent as well
  {
    if (info->Content() == CONTENT_TVSHOWS || settings.parent_name_root)
    {
      std::string strParent;
      if (URIUtils::GetParentPath(strPath, strParent) && (!URIUtils::IsPlugin(strPath) || !CURL(strParent).GetHostName().empty()))
        SetPathHash(strParent, "");
    }
  }
}

bool CVideoDatabase::CommitTransaction()
{
  if (CDatabase::CommitTransaction())
  { // number of items in the db has likely changed, so recalculate
    GUIINFO::CLibraryGUIInfo& guiInfo = CServiceBroker::GetGUI()->GetInfoManager().GetInfoProviders().GetLibraryInfoProvider();
    guiInfo.SetLibraryBool(LIBRARY_HAS_MOVIES, HasContent(VIDEODB_CONTENT_MOVIES));
    guiInfo.SetLibraryBool(LIBRARY_HAS_TVSHOWS, HasContent(VIDEODB_CONTENT_TVSHOWS));
    guiInfo.SetLibraryBool(LIBRARY_HAS_MUSICVIDEOS, HasContent(VIDEODB_CONTENT_MUSICVIDEOS));
    return true;
  }
  return false;
}

bool CVideoDatabase::SetSingleValue(VIDEODB_CONTENT_TYPE type, int dbId, int dbField, const std::string &strValue)
{
  std::string strSQL;
  try
  {
    if (NULL == m_pDB.get() || NULL == m_pDS.get())
      return false;

    std::string strTable, strField;
    if (type == VIDEODB_CONTENT_MOVIES)
    {
      strTable = "movie";
      strField = "idMovie";
    }
    else if (type == VIDEODB_CONTENT_TVSHOWS)
    {
      strTable = "tvshow";
      strField = "idShow";
    }
    else if (type == VIDEODB_CONTENT_EPISODES)
    {
      strTable = "episode";
      strField = "idEpisode";
    }
    else if (type == VIDEODB_CONTENT_MUSICVIDEOS)
    {
      strTable = "musicvideo";
      strField = "idMVideo";
    }

    if (strTable.empty())
      return false;

    return SetSingleValue(strTable, StringUtils::Format("c%02u", dbField), strValue, strField, dbId);
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (%s) failed", __FUNCTION__, strSQL.c_str());
  }
  return false;
}

bool CVideoDatabase::SetSingleValue(VIDEODB_CONTENT_TYPE type, int dbId, Field dbField, const std::string &strValue)
{
  MediaType mediaType = DatabaseUtils::MediaTypeFromVideoContentType(type);
  if (mediaType == MediaTypeNone)
    return false;

  int dbFieldIndex = DatabaseUtils::GetField(dbField, mediaType);
  if (dbFieldIndex < 0)
    return false;

  return SetSingleValue(type, dbId, dbFieldIndex, strValue);
}

bool CVideoDatabase::SetSingleValue(const std::string &table, const std::string &fieldName, const std::string &strValue,
                                    const std::string &conditionName /* = "" */, int conditionValue /* = -1 */)
{
  if (table.empty() || fieldName.empty())
    return false;

  std::string sql;
  try
  {
    if (NULL == m_pDB.get() || NULL == m_pDS.get())
      return false;

    sql = PrepareSQL("UPDATE %s SET %s='%s'", table.c_str(), fieldName.c_str(), strValue.c_str());
    if (!conditionName.empty())
      sql += PrepareSQL(" WHERE %s=%u", conditionName.c_str(), conditionValue);
    if (m_pDS->exec(sql) == 0)
      return true;
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s (%s) failed", __FUNCTION__, sql.c_str());
  }
  return false;
}

std::string CVideoDatabase::GetSafeFile(const std::string &dir, const std::string &name) const
{
  std::string safeThumb(name);
  StringUtils::Replace(safeThumb, ' ', '_');
  return URIUtils::AddFileToFolder(dir, CUtil::MakeLegalFileName(safeThumb));
}

void CVideoDatabase::AnnounceRemove(std::string content, int id, bool scanning /* = false */)
{
  CVariant data;
  data["type"] = content;
  data["id"] = id;
  if (scanning)
    data["transaction"] = true;
  CServiceBroker::GetAnnouncementManager()->Announce(ANNOUNCEMENT::VideoLibrary, "xbmc", "OnRemove", data);
}

void CVideoDatabase::AnnounceUpdate(std::string content, int id)
{
  CVariant data;
  data["type"] = content;
  data["id"] = id;
  CServiceBroker::GetAnnouncementManager()->Announce(ANNOUNCEMENT::VideoLibrary, "xbmc", "OnUpdate", data);
}

bool CVideoDatabase::GetItemsForPath(const std::string &content, const std::string &strPath, CFileItemList &items)
{
  std::string path(strPath);

  if(URIUtils::IsMultiPath(path))
  {
    std::vector<std::string> paths;
    CMultiPathDirectory::GetPaths(path, paths);

    for(unsigned i=0;i<paths.size();i++)
      GetItemsForPath(content, paths[i], items);

    return items.Size() > 0;
  }

  int pathID = GetPathId(path);
  if (pathID < 0)
    return false;

  if (content == "movies")
  {
    Filter filter(PrepareSQL("c%02d=%d", VIDEODB_ID_PARENTPATHID, pathID));
    GetMoviesByWhere("videodb://movies/titles/", filter, items);
  }
  else if (content == "episodes")
  {
    Filter filter(PrepareSQL("c%02d=%d", VIDEODB_ID_EPISODE_PARENTPATHID, pathID));
    GetEpisodesByWhere("videodb://tvshows/titles/", filter, items);
  }
  else if (content == "tvshows")
  {
    Filter filter(PrepareSQL("idParentPath=%d", pathID));
    GetTvShowsByWhere("videodb://tvshows/titles/", filter, items);
  }
  else if (content == "musicvideos")
  {
    Filter filter(PrepareSQL("c%02d=%d", VIDEODB_ID_MUSICVIDEO_PARENTPATHID, pathID));
    GetMusicVideosByWhere("videodb://musicvideos/titles/", filter, items);
  }
  for (int i = 0; i < items.Size(); i++)
    items[i]->SetPath(items[i]->GetVideoInfoTag()->m_basePath);
  return items.Size() > 0;
}

void CVideoDatabase::AppendIdLinkFilter(const char* field, const char *table, const MediaType& mediaType, const char *view, const char *viewKey, const CUrlOptions::UrlOptions& options, Filter &filter)
{
  auto option = options.find((std::string)field + "id");
  if (option == options.end())
    return;

  filter.AppendJoin(PrepareSQL("JOIN %s_link ON %s_link.media_id=%s_view.%s AND %s_link.media_type='%s'", field, field, view, viewKey, field, mediaType.c_str()));
  filter.AppendWhere(PrepareSQL("%s_link.%s_id = %i", field, table, (int)option->second.asInteger()));
}

void CVideoDatabase::AppendLinkFilter(const char* field, const char *table, const MediaType& mediaType, const char *view, const char *viewKey, const CUrlOptions::UrlOptions& options, Filter &filter)
{
  auto option = options.find(field);
  if (option == options.end())
    return;

  filter.AppendJoin(PrepareSQL("JOIN %s_link ON %s_link.media_id=%s_view.%s AND %s_link.media_type='%s'", field, field, view, viewKey, field, mediaType.c_str()));
  filter.AppendJoin(PrepareSQL("JOIN %s ON %s.%s_id=%s_link.%s_id", table, table, field, table, field));
  filter.AppendWhere(PrepareSQL("%s.name like '%s'", table, option->second.asString().c_str()));
}

bool CVideoDatabase::GetFilter(CDbUrl &videoUrl, Filter &filter, SortDescription &sorting)
{
  if (!videoUrl.IsValid())
    return false;

  std::string type = videoUrl.GetType();
  std::string itemType = ((const CVideoDbUrl &)videoUrl).GetItemType();
  const CUrlOptions::UrlOptions& options = videoUrl.GetOptions();

  if (type == "movies")
  {
    AppendIdLinkFilter("genre", "genre", "movie", "movie", "idMovie", options, filter);
    AppendLinkFilter("genre", "genre", "movie", "movie", "idMovie", options, filter);

    AppendIdLinkFilter("country", "country", "movie", "movie", "idMovie", options, filter);
    AppendLinkFilter("country", "country", "movie", "movie", "idMovie", options, filter);

    AppendIdLinkFilter("studio", "studio", "movie", "movie", "idMovie", options, filter);
    AppendLinkFilter("studio", "studio", "movie", "movie", "idMovie", options, filter);

    AppendIdLinkFilter("director", "actor", "movie", "movie", "idMovie", options, filter);
    AppendLinkFilter("director", "actor", "movie", "movie", "idMovie", options, filter);

    auto option = options.find("year");
    if (option != options.end())
      filter.AppendWhere(PrepareSQL("movie_view.premiered like '%i%%'", (int)option->second.asInteger()));

    AppendIdLinkFilter("actor", "actor", "movie", "movie", "idMovie", options, filter);
    AppendLinkFilter("actor", "actor", "movie", "movie", "idMovie", options, filter);

    option = options.find("setid");
    if (option != options.end())
      filter.AppendWhere(PrepareSQL("movie_view.idSet = %i", (int)option->second.asInteger()));

    option = options.find("set");
    if (option != options.end())
      filter.AppendWhere(PrepareSQL("movie_view.strSet LIKE '%s'", option->second.asString().c_str()));

    AppendIdLinkFilter("tag", "tag", "movie", "movie", "idMovie", options, filter);
    AppendLinkFilter("tag", "tag", "movie", "movie", "idMovie", options, filter);
  }
  else if (type == "tvshows")
  {
    if (itemType == "tvshows")
    {
      AppendIdLinkFilter("genre", "genre", "tvshow", "tvshow", "idShow", options, filter);
      AppendLinkFilter("genre", "genre", "tvshow", "tvshow", "idShow", options, filter);

      AppendIdLinkFilter("studio", "studio", "tvshow", "tvshow", "idShow", options, filter);
      AppendLinkFilter("studio", "studio", "tvshow", "tvshow", "idShow", options, filter);

      AppendIdLinkFilter("director", "actor", "tvshow", "tvshow", "idShow", options, filter);

      auto option = options.find("year");
      if (option != options.end())
        filter.AppendWhere(PrepareSQL("tvshow_view.c%02d like '%%%i%%'", VIDEODB_ID_TV_PREMIERED, (int)option->second.asInteger()));

      AppendIdLinkFilter("actor", "actor", "tvshow", "tvshow", "idShow", options, filter);
      AppendLinkFilter("actor", "actor", "tvshow", "tvshow", "idShow", options, filter);

      AppendIdLinkFilter("tag", "tag", "tvshow", "tvshow", "idShow", options, filter);
      AppendLinkFilter("tag", "tag", "tvshow", "tvshow", "idShow", options, filter);
    }
    else if (itemType == "seasons")
    {
      auto option = options.find("tvshowid");
      if (option != options.end())
        filter.AppendWhere(PrepareSQL("season_view.idShow = %i", (int)option->second.asInteger()));

      AppendIdLinkFilter("genre", "genre", "tvshow", "season", "idShow", options, filter);

      AppendIdLinkFilter("director", "actor", "tvshow", "season", "idShow", options, filter);

      option = options.find("year");
      if (option != options.end())
        filter.AppendWhere(PrepareSQL("season_view.premiered like '%%%i%%'", (int)option->second.asInteger()));

      AppendIdLinkFilter("actor", "actor", "tvshow", "season", "idShow", options, filter);
    }
    else if (itemType == "episodes")
    {
      int idShow = -1;
      auto option = options.find("tvshowid");
      if (option != options.end())
        idShow = (int)option->second.asInteger();

      int season = -1;
      option = options.find("season");
      if (option != options.end())
        season = (int)option->second.asInteger();

      if (idShow > -1)
      {
        bool condition = false;

        AppendIdLinkFilter("genre", "genre", "tvshow", "episode", "idShow", options, filter);
        AppendLinkFilter("genre", "genre", "tvshow", "episode", "idShow", options, filter);

        AppendIdLinkFilter("director", "actor", "tvshow", "episode", "idShow", options, filter);
        AppendLinkFilter("director", "actor", "tvshow", "episode", "idShow", options, filter);

        option = options.find("year");
        if (option != options.end())
        {
          condition = true;
          filter.AppendWhere(PrepareSQL("episode_view.idShow = %i and episode_view.premiered like '%%%i%%'", idShow, (int)option->second.asInteger()));
        }

        AppendIdLinkFilter("actor", "actor", "tvshow", "episode", "idShow", options, filter);
        AppendLinkFilter("actor", "actor", "tvshow", "episode", "idShow", options, filter);

        if (!condition)
          filter.AppendWhere(PrepareSQL("episode_view.idShow = %i", idShow));

        if (season > -1)
        {
          if (season == 0) // season = 0 indicates a special - we grab all specials here (see below)
            filter.AppendWhere(PrepareSQL("episode_view.c%02d = %i", VIDEODB_ID_EPISODE_SEASON, season));
          else
            filter.AppendWhere(PrepareSQL("(episode_view.c%02d = %i or (episode_view.c%02d = 0 and (episode_view.c%02d = 0 or episode_view.c%02d = %i)))",
              VIDEODB_ID_EPISODE_SEASON, season, VIDEODB_ID_EPISODE_SEASON, VIDEODB_ID_EPISODE_SORTSEASON, VIDEODB_ID_EPISODE_SORTSEASON, season));
        }
      }
      else
      {
        option = options.find("year");
        if (option != options.end())
          filter.AppendWhere(PrepareSQL("episode_view.premiered like '%%%i%%'", (int)option->second.asInteger()));

        AppendIdLinkFilter("director", "actor", "episode", "episode", "idEpisode", options, filter);
        AppendLinkFilter("director", "actor", "episode", "episode", "idEpisode", options, filter);
      }
    }
  }
  else if (type == "musicvideos")
  {
    AppendIdLinkFilter("genre", "genre", "musicvideo", "musicvideo", "idMVideo", options, filter);
    AppendLinkFilter("genre", "genre", "musicvideo", "musicvideo", "idMVideo", options, filter);

    AppendIdLinkFilter("studio", "studio", "musicvideo", "musicvideo", "idMVideo", options, filter);
    AppendLinkFilter("studio", "studio", "musicvideo", "musicvideo", "idMVideo", options, filter);

    AppendIdLinkFilter("director", "actor", "musicvideo", "musicvideo", "idMVideo", options, filter);
    AppendLinkFilter("director", "actor", "musicvideo", "musicvideo", "idMVideo", options, filter);

    auto option = options.find("year");
    if (option != options.end())
      filter.AppendWhere(PrepareSQL("musicvideo_view.premiered like '%i%%'", (int)option->second.asInteger()));

    option = options.find("artistid");
    if (option != options.end())
    {
      if (itemType != "albums")
        filter.AppendJoin(PrepareSQL("JOIN actor_link ON actor_link.media_id=musicvideo_view.idMVideo AND actor_link.media_type='musicvideo'"));
      filter.AppendWhere(PrepareSQL("actor_link.actor_id = %i", (int)option->second.asInteger()));
    }

    option = options.find("artist");
    if (option != options.end())
    {
      if (itemType != "albums")
      {
        filter.AppendJoin(PrepareSQL("JOIN actor_link ON actor_link.media_id=musicvideo_view.idMVideo AND actor_link.media_type='musicvideo'"));
        filter.AppendJoin(PrepareSQL("JOIN actor ON actor.actor_id=actor_link.actor_id"));
      }
      filter.AppendWhere(PrepareSQL("actor.name LIKE '%s'", option->second.asString().c_str()));
    }

    option = options.find("albumid");
    if (option != options.end())
      filter.AppendWhere(PrepareSQL("musicvideo_view.c%02d = (select c%02d from musicvideo where idMVideo = %i)", VIDEODB_ID_MUSICVIDEO_ALBUM, VIDEODB_ID_MUSICVIDEO_ALBUM, (int)option->second.asInteger()));

    AppendIdLinkFilter("tag", "tag", "musicvideo", "musicvideo", "idMVideo", options, filter);
    AppendLinkFilter("tag", "tag", "musicvideo", "musicvideo", "idMVideo", options, filter);
  }
  else
    return false;

  auto option = options.find("xsp");
  if (option != options.end())
  {
    CSmartPlaylist xsp;
    if (!xsp.LoadFromJson(option->second.asString()))
      return false;

    // check if the filter playlist matches the item type
    if (xsp.GetType() == itemType ||
       (xsp.GetGroup() == itemType && !xsp.IsGroupMixed()) ||
        // handle episode listings with videodb://tvshows/titles/ which get the rest
        // of the path (season and episodeid) appended later
       (xsp.GetType() == "episodes" && itemType == "tvshows"))
    {
      std::set<std::string> playlists;
      filter.AppendWhere(xsp.GetWhereClause(*this, playlists));

      if (xsp.GetLimit() > 0)
        sorting.limitEnd = xsp.GetLimit();
      if (xsp.GetOrder() != SortByNone)
        sorting.sortBy = xsp.GetOrder();
      if (xsp.GetOrderDirection() != SortOrderNone)
        sorting.sortOrder = xsp.GetOrderDirection();
      if (CServiceBroker::GetSettingsComponent()->GetSettings()->GetBool(CSettings::SETTING_FILELISTS_IGNORETHEWHENSORTING))
        sorting.sortAttributes = SortAttributeIgnoreArticle;
    }
  }

  option = options.find("filter");
  if (option != options.end())
  {
    CSmartPlaylist xspFilter;
    if (!xspFilter.LoadFromJson(option->second.asString()))
      return false;

    // check if the filter playlist matches the item type
    if (xspFilter.GetType() == itemType)
    {
      std::set<std::string> playlists;
      filter.AppendWhere(xspFilter.GetWhereClause(*this, playlists));
    }
    // remove the filter if it doesn't match the item type
    else
      videoUrl.RemoveOption("filter");
  }

  return true;
}
