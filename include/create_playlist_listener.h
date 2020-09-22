/**
 * \file
 * \brief Create playlist listener class definition.
 */
#ifndef CREATE_PLAYLIST_LISTENER_H_
#define CREATE_PLAYLIST_LISTENER_H_

#include <string>

namespace espotifai_api {

/**
 * \interface CreatePlaylistListener.
 *
 * \brief This class defines a interface for playlist creation events.
 */
class CreatePlaylistListener {
   public:
    /**
     * \brief Indicates that the playlist was created with success.
     */
    virtual void OnPlaylistCreated() const = 0;

    /**
     * \brief Indicates that the attempt to create a playlist has failed.
     * \param msg The suitable error message.
     */
    virtual void OnPlaylistCreationError(const std::string &msg) const = 0;
};

}  // namespace espotifai_api

#endif  // CREATE_PLAYLIST_LISTENER_H_
