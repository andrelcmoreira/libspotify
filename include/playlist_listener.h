/**
 * @file
 *
 * @brief Playlist listener class definition.
 */
#ifndef PLAYLIST_LISTENER_H_
#define PLAYLIST_LISTENER_H_

#include <string>
#include <vector>

#include "types.h"

namespace espotifai_api {

/**
 * @interface PlaylistListener.
 *
 * @brief This class defines a interface for playlist events.
 */
class PlaylistListener {
 public:
  /**
   * @brief Indicates that the playlist was created with success.
   */
  virtual void OnPlaylistCreated() const = 0;

  /**
   * @brief Indicates that the attempt to create a playlist has failed.
   *
   * @param msg The suitable error message.
   */
  virtual void OnPlaylistCreationError(const std::string& msg) const = 0;

  /**
   * @brief Report the list of musics associated to the playlist.
   *
   * @param musics List of musics.
   */
  virtual void OnMusicList(const std::vector<MusicInfo>& musics) const = 0;

  /**
   * @brief Indicates a failure during the operation.
   *
   * @param msg The suitable error message.
   */
  virtual void OnMusicListError(const std::string& msg) const = 0;

  /**
   * @brief Report the list of registered playlists.
   *
   * @param playlists The list of playlists.
   */
  virtual void OnPlaylistsFound(
      const std::vector<std::string>& playlists) const = 0;

  /**
   * @brief Indicates an error during the operation for retrieve the playlists.
   *
   * @param msg The suitable error message.
   */
  virtual void OnPlaylistsFoundError(const std::string& msg) const = 0;
};

}  // namespace espotifai_api

#endif  // PLAYLIST_LISTENER_H_
