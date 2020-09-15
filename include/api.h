/**
 * \file
 * \brief Api main class definition.
 */
#ifndef API_H_
#define API_H_

#include <memory>
#include <string>

#include "private/spotify_auth.h"

namespace espotifai_api {

class AccessListener;

/**
 * \class Api.
 *
 * \brief This class implements the main functionalities of espotifai API.
 */
class Api {
   public:
    /**
     * \brief Constructor.
     * \param auth Spotify authenticator instance.
     */
    explicit Api(const std::shared_ptr<SpotifyAuth> &auth = nullptr);

    /**
     * \brief Authenticate a user using the spotify API.
     * \param listener Event listener.
     * \param client_id Client's ID.
     * \param client_secret Client's secret.
     */
    void RequestAccess(
        AccessListener &listener,
        const std::string &client_id,
        const std::string &client_secret) const;

   private:
    std::shared_ptr<SpotifyAuth> sptf_auth_; //!< Spotify authenticator.
};

}  // espotifai_api

#endif  // API_H_
