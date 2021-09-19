/**
 * @file
 *
 * @brief Api private class definition.
 */
#ifndef API_PRIVATE_H_
#define API_PRIVATE_H_

#include <memory>
#include <string>

#include "access_listener.h"
#include "add_music_playlist_listener.h"
#include "playlist_listener.h"
#include "search_listener.h"
#include "types.h"

namespace espotifai_api {

class Authenticator;
class PlaylistMgr;
class Searcher;

/**
 * @class ApiPrivate.
 *
 * @brief This class implements the main functionalities of espotifai API.
 */
class ApiPrivate {
 public:
  /**
   * @brief Constructor.
   *
   * @param auth Spotify authenticator instance.
   * @param searcher Spotify music searcher.
   * @param mgr Playlist manager.
   */
  ApiPrivate(const std::shared_ptr<Authenticator>& auth = nullptr,
             const std::shared_ptr<Searcher>& searcher = nullptr,
             const std::shared_ptr<PlaylistMgr>& mgr = nullptr);

  /**
   * @brief Authenticate a user within the spotify API.
   *
   * @param listener Event listener.
   * @param client_id Client's ID.
   * @param client_secret Client's secret.
   */
  void Auth(AccessListener& listener, const std::string& client_id,
            const std::string& client_secret) const;

  /**
   * @brief Search for a string in the spotify platform.
   *
   * @param listener Event listener.
   * @param token Access token.
   * @param name String to be queried.
   */
  void Search(SearchListener& listener, const std::string& token,
              const std::string& name) const;

  /**
   * @brief Create a spotify playlist.
   *
   * @param listener Event listener.
   * @param name Name of the playlist.
   */
  void CreatePlaylist(PlaylistListener& listener, const std::string& name) const;

  /**
   * @brief Add a music into an existent playlist.
   *
   * @param listener Event listener.
   * @param music Informations of the music.
   * @param playlist Name of the playlist.
   */
  void AddMusicToPlaylist(AddMusicPlaylistListener& listener,
                          const MusicInfo& music,
                          const std::string& playlist) const;

  /**
   * @brief List the musics for a given playlist.
   *
   * @param listener Event listener.
   * @param playlist_name Name of the playlist.
   */
  void ListPlaylistMusics(PlaylistListener& listener,
                          const std::string& playlist_name) const;

  /**
   * @brief Get all playlists of the authenticated user.
   *
   * @param listener Event listener.
   */
  void GetPlaylists(PlaylistListener& listener) const;

 private:
  std::shared_ptr<Authenticator> auth_;        //!< Spotify authenticator.
  std::shared_ptr<Searcher> searcher_;  //!< Spotify music searcher.
  std::shared_ptr<PlaylistMgr> playlist_mgr_;     //!< Playlist manager.
};

}  // namespace espotifai_api

#endif  // API_PRIVATE_H_
