/**
 * \file
 * \brief Api test class implementation.
 */
#include <gtest/gtest.h>

#include <memory>

#include "mock/access_listener_mock.h"
#include "mock/curl_wrapper_mock.h"

#include "api.h"
#include "private/curl_wrapper.h"
#include "private/spotify_auth.h"
#include "private/utils.h"

class EspotifaiApiTest : public testing::Test {
    public:
     EspotifaiApiTest()
          : curl_{std::make_shared<espotifai_api::test::CurlWrapperMock>()},
            auth_{std::make_shared<espotifai_api::SpotifyAuth>(curl_)},
            api_{auth_}
     {
     }

    protected:
     std::shared_ptr<espotifai_api::test::CurlWrapperMock> curl_; //!< Curl wrapper mock instance.
     std::shared_ptr<espotifai_api::SpotifyAuth> auth_; //!< Spotify auth instance.
     espotifai_api::Api api_; //!< Api instance.
};

/**
 * \brief This tests validates the scenario when the user try to log into the spotify API
 * with a valid client_id and client_credentials. When this occurs, the espotifai_api must
 * return the access token through the listener.
 */
TEST_F(EspotifaiApiTest, W_UserRequestAuthWithValidCredentials_S_LogWithSuccess)
{
    /* test constants */
    const std::string kLoginUri{"https://accounts.spotify.com/api/token"};
    const std::string kClientId{"good_id"};
    const std::string kClientSecret{"good_secret"};
    const std::vector<std::string> kReqHeaders{
        "Authorization: Basic " +
        espotifai_api::utils::GetBase64Code(kClientId + ":" + kClientSecret)
    };
    const std::vector<std::string> kReqData{
        "grant_type=client_credentials"
    };
    const std::map<std::string, std::string> kExpectedReturn{
        { "access_token", "BQDGLtwpiJbNGiJejVpzV6xvFFwlaDCysDW41sPWJgVBL0XBWXj7wMm7Es0C" },
        { "token_type", "Bearer" },
        { "expires_in", "3600" },
        { "scope", "" }
    };

    auto listener = std::make_shared<espotifai_api::test::AccessListenerMock>();

    /* set default behavior for Post method */
    ON_CALL(*curl_, Post(kLoginUri, kReqHeaders, kReqData))
        .WillByDefault(testing::Return(kExpectedReturn));

    EXPECT_CALL(*curl_, Post(kLoginUri, kReqHeaders, kReqData)).Times(1);
    EXPECT_CALL(*listener, OnAccessDeny(testing::_)).Times(0);
    EXPECT_CALL(*listener, OnAccessGuaranteed(kExpectedReturn.at("access_token")))
        .Times(1);

    api_.RequestAccess(*listener, kClientId, kClientSecret);
}

/**
 * \brief This tests validates the scenario when the user try to log into the spotify API
 * with an invalid client_id and client_credentials. When this occurs, the espotifai_api must
 * return the the suitable error message through the listener.
 */
TEST_F(EspotifaiApiTest, W_UserRequestAuthWithBadCredentials_S_ReturnFailure)
{
    /* test constants */
    const std::string kLoginUri{"https://accounts.spotify.com/api/token"};
    const std::string kClientId{"bad_id"};
    const std::string kClientSecret{"bad_secret"};
    const std::vector<std::string> kReqHeaders{
        "Authorization: Basic " +
        espotifai_api::utils::GetBase64Code(kClientId + ":" + kClientSecret)
    };
    const std::vector<std::string> kReqData{
        "grant_type=client_credentials"
    };

    /* set default behavior for Post method */
    ON_CALL(*curl_, Post(kLoginUri, kReqHeaders, kReqData))
        .WillByDefault(testing::Throw(std::runtime_error("")));

    auto listener = std::make_shared<espotifai_api::test::AccessListenerMock>();

    EXPECT_CALL(*curl_, Post(kLoginUri, kReqHeaders, kReqData))
        .Times(1)
        .WillOnce(testing::Throw(std::runtime_error("")));
    EXPECT_CALL(*listener, OnAccessGuaranteed(testing::_)).Times(0);
    EXPECT_CALL(*listener, OnAccessDeny(testing::_))
        .Times(1);

    api_.RequestAccess(*listener, kClientId, kClientSecret);
}
