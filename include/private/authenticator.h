/**
 * @file
 *
 * @brief Spotify authenticator class definition.
 */
#ifndef SPOTIFY_AUTH_H_
#define SPOTIFY_AUTH_H_

#include <string>
#include <memory>

#include "private/curl_wrapper.h"

namespace espotifai_api {

/**
 * @class Authenticator.
 *
 * @brief This class implements the authentication mechanism to Spotify API.
 */
class Authenticator {
   public:
    /**
     * @brief Constructor.
     *
     * @param curl Lib curl handler.
     */
    explicit Authenticator(const std::shared_ptr<CurlWrapper> &curl = nullptr);

    /**
     * @brief Authenticate an user into the Spotify API using the client credentials flow
     * (https://developer.spotify.com/documentation/general/guides/authorization-guide/#client-credentials-flow).
     *
     * @param client_id Client ID.
     * @param client_secret Client secret.
     *
     * @return The access token.
     */
    std::string AuthUser(const std::string &cli_id, const std::string &cli_secret) const;

   private:
    const std::string kUri_; //!< Uri for authentication.
    std::shared_ptr<CurlWrapper> curl_; //!< Lib curl handler.
};

}  // namespace espotifai_api

#endif  // SPOTIFY_AUTH_H_
