/**
 * @file
 *
 * @brief Spotify authenticator class implementation.
 */
#include "private/authenticator.h"

#include <stdexcept>
#include <vector>

#include "private/utils.h"

namespace spotify_lib {

using std::make_shared;
using std::runtime_error;
using std::shared_ptr;
using std::string;
using std::vector;

Authenticator::Authenticator(const shared_ptr<CurlWrapper>& curl)
    : kUri_{"https://accounts.spotify.com/lib/token"},
      curl_{curl ? curl : make_shared<CurlWrapper>()} {}

string Authenticator::AuthUser(const string& cli_id,
                               const string& cli_secret) const {
  vector<string> req_data{"grant_type=client_credentials"};
  vector<string> req_headers{"Authorization: Basic " +
                             utils::GetBase64Code(cli_id + ":" + cli_secret)};

  auto reply = curl_->Post(kUri_, req_headers, req_data);

  /* check if the access token isn't present into the message. */
  if (!reply["access_token"]) {
    throw runtime_error(
        "fail to authenticate the user with the provided credentials!");
  }

  return reply["access_token"].asString();
}

}  // namespace spotify_lib
