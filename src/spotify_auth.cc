/**
 * \file
 * \brief Spotify authenticator class implementation.
 */
#include "private/spotify_auth.h"

#include <stdexcept>
#include <vector>

#include "private/utils.h"

namespace espotifai_api {

SpotifyAuth::SpotifyAuth(const std::shared_ptr<CurlWrapper> &curl)
    : kUri_{"https://accounts.spotify.com/api/token"},
      curl_{curl ? curl : std::make_shared<CurlWrapper>()}
{
}

std::string SpotifyAuth::AuthUser(
    const std::string &cli_id,
    const std::string &cli_secret) const
{
    std::vector<std::string> req_headers{
        "Authorization: Basic " +
        utils::GetBase64Code(cli_id + ":" + cli_secret)
    };
    std::vector<std::string> req_data{
        "grant_type=client_credentials"
    };

    auto reply = curl_->Post(kUri_, req_headers, req_data);

    /* check if the access token isn't present into the message. */
    if (!reply["access_token"]) {
        throw std::runtime_error(
            "fail to authenticate the user with the provided credentials!"
        );
    }

    return reply["access_token"].asString();
}

}  // espotifai_api
