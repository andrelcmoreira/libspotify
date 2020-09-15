#ifndef SPOTIFY_WRAPPER_MOCK_H_
#define SPOTIFY_WRAPPER_MOCK_H_

#include <gmock/gmock.h>

#include <memory>

#include "curl_wrapper_mock.h"
#include "private/spotify_auth.h"

namespace espotifai_api {
namespace test {

class SpotifyAuthMock : public SpotifyAuth {
   public:
    explicit SpotifyAuthMock(std::shared_ptr<CurlWrapperMock> curl_mock)
        : SpotifyAuth(curl_mock)
    {
    }

    MOCK_CONST_METHOD2(
        AuthUser,
        std::string(const std::string &, const std::string &)
    );
};

} // test
} // espotifai_api

#endif // SPOTIFY_WRAPPER_MOCK_H_
