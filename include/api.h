/**
 * @file
 *
 * @brief Api main class definition.
 */
#ifndef API_H_
#define API_H_

#include <memory>
#include <string>

#include "access_listener.h"
#include "add_music_playlist_listener.h"
#include "playlist_listener.h"
#include "search_listener.h"
#include "types.h"

namespace espotifai_api {

class ApiPrivate;
class Authenticator;
class Searcher;
class PlaylistMgr;

/**
 * @class Api.
 *
 * @brief This class implements the main functionalities of espotifai API.
 */
class Api {
 public:
  /**
   * @brief Constructor.
   *
   * @param auth Spotify authenticator instance.
   * @param searcher Spotify music searcher.
   * @param mgr Playlist manager.
   */
  Api(const std::shared_ptr<Authenticator>& auth = nullptr,
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
  void CreatePlaylist(PlaylistListener& listener,
                      const std::string& name) const;

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
   * @brief List the musics of a given playlist.
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
  // TODO: make it a unique_ptr
  std::shared_ptr<ApiPrivate> private_;  //!< API private.
};

}  // namespace espotifai_api

#endif  // API_H_
