/**
 * \file
 * \brief Add music to playlist listener class definition.
 */
#ifndef ADD_MUSIC_PLAYLIST_LISTENER_H_
#define ADD_MUSIC_PLAYLIST_LISTENER_H_

#include <string>

namespace espotifai_api {

/**
 * \interface AddMusicPlaylistListener.
 *
 * \brief This class defines a interface for events related to the addition of
 * a music into playlist.
 */
class AddMusicPlaylistListener {
 public:
  /**
   * \brief Report the music addition.
   */
  virtual void OnMusicAdded() const = 0;

  /**
   * \brief Indicates an error during the operation.
   * \param msg The suitable error message.
   */
  virtual void OnMusicAdditionError(const std::string& msg) const = 0;
};

}  // namespace espotifai_api

#endif  // ADD_MUSIC_PLAYLIST_LISTENER_H_
