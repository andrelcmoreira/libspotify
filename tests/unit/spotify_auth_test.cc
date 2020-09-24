/**
 * \file
 * \brief Spotify authenticator test class implementation.
 */
#include <gtest/gtest.h>

#include <memory>

#include "mock/access_listener_mock.h"
#include "mock/curl_wrapper_mock.h"
#include "mock/db_handler_mock.h"

#include "api.h"
#include "private/curl_wrapper.h"
#include "private/spotify_auth.h"
#include "private/playlist_mgr.h"
#include "private/utils.h"

class SpotifyAuthTest : public testing::Test {
    public:
     SpotifyAuthTest()
          : curl_{std::make_shared<espotifai_api::test::CurlWrapperMock>()},
            auth_{std::make_shared<espotifai_api::SpotifyAuth>(curl_)},
            db_mock_{std::make_shared<espotifai_api::test::DbHandlerMock>()},
            playlist_mgr_{std::make_shared<espotifai_api::PlaylistMgr>(db_mock_)},
            api_{auth_, nullptr, playlist_mgr_}
     {
     }

    protected:
     std::shared_ptr<espotifai_api::test::CurlWrapperMock> curl_; //!< Curl wrapper mock instance.
     std::shared_ptr<espotifai_api::SpotifyAuth> auth_; //!< Spotify auth instance.
     /* The playlist mgr must be supplied with a mocked database handler due mongodb instance. */
     /* TODO: fix this behavior */
     std::shared_ptr<espotifai_api::test::DbHandlerMock> db_mock_; //!< Database mock.
     std::shared_ptr<espotifai_api::PlaylistMgr> playlist_mgr_; //!< Playlist manager.
     espotifai_api::Api api_; //!< Api instance.
     const std::string KLoginUri_{"https://accounts.spotify.com/api/token"}; //!< URI used for authentication.
};

/**
 * \brief This tests validates the scenario when the user try to log into the spotify API
 * with a valid client_id and client_credentials. When this occurs, the espotifai_api must
 * return the access token through the listener.
 */
TEST_F(SpotifyAuthTest, W_UserRequestAuthWithValidCredentials_S_LogWithSuccess)
{
    /* test constants */
    const std::string kClientId{"good_id"};
    const std::string kClientSecret{"good_secret"};
    const std::vector<std::string> kReqHeaders{
        "Authorization: Basic " +
        espotifai_api::utils::GetBase64Code(kClientId + ":" + kClientSecret)
    };
    const std::vector<std::string> kReqData{
        "grant_type=client_credentials"
    };
    Json::Value expected_return;

    /* build the expected return */
    expected_return["access_token"] = "BQDGLtwpiJbNGiJejVpzV6xvFFwlaDCysDW41sPWJgVBL0XBWXj7wMm7";
    expected_return["token_type"] = "Bearer";
    expected_return["expires_in"] = "3600";
    expected_return["scope"] = "";

    auto listener = std::make_shared<espotifai_api::test::AccessListenerMock>();

    /* set default behavior for Post method */
    ON_CALL(*curl_, Post(KLoginUri_, kReqHeaders, kReqData))
        .WillByDefault(testing::Return(expected_return));

    EXPECT_CALL(*curl_, Post(KLoginUri_, kReqHeaders, kReqData)).Times(1);
    EXPECT_CALL(*listener, OnAccessDenied(testing::_)).Times(0);
    EXPECT_CALL(*listener, OnAccessGuaranteed(expected_return["access_token"].asString()))
        .Times(1);

    api_.RequestAccess(*listener, kClientId, kClientSecret);
}

/**
 * \brief This tests validates the scenario when the user try to log into the spotify API
 * with an invalid client_id and client_credentials. When this occurs, the espotifai_api must
 * return the suitable error message through the listener.
 */
TEST_F(SpotifyAuthTest, W_UserRequestAuthWithBadCredentials_S_ReturnFailure)
{
    /* test constants */
    const std::string kClientId{"bad_id"};
    const std::string kClientSecret{"bad_secret"};
    const std::string kExpectedMsg{
        "fail to authenticate the user with the provided credentials!"
    };
    const std::vector<std::string> kReqHeaders{
        "Authorization: Basic " +
        espotifai_api::utils::GetBase64Code(kClientId + ":" + kClientSecret)
    };
    const std::vector<std::string> kReqData{
        "grant_type=client_credentials"
    };
    Json::Value expected_return;

    /* build the expected return */
    expected_return["error"] = "invalid_client";
    expected_return["error_description"] = "Invalid client secret";

    auto listener = std::make_shared<espotifai_api::test::AccessListenerMock>();

    /* set default behavior for Post method */
    ON_CALL(*curl_, Post(KLoginUri_, kReqHeaders, kReqData))
        .WillByDefault(testing::Return(expected_return));

    EXPECT_CALL(*curl_, Post(KLoginUri_, kReqHeaders, kReqData)).Times(1);
    EXPECT_CALL(*listener, OnAccessDenied(kExpectedMsg)).Times(1);
    EXPECT_CALL(*listener, OnAccessGuaranteed(testing::_)).Times(0);

    api_.RequestAccess(*listener, kClientId, kClientSecret);
}

/**
 * \brief This tests validates the scenario when the user try to log into the spotify API
 * offline. When this occurs, the espotifai_api must return the suitable error message
 * through the listener.
 */
TEST_F(SpotifyAuthTest, W_UserRequestAuthOffline_S_ReturnFailure)
{
    /* test constants */
    const std::string kClientId{"good_id"};
    const std::string kClientSecret{"good_secret"};
    const std::string kErrorMessage{"some cool error message"};
    const std::vector<std::string> kReqHeaders{
        "Authorization: Basic " +
        espotifai_api::utils::GetBase64Code(kClientId + ":" + kClientSecret)
    };
    const std::vector<std::string> kReqData{
        "grant_type=client_credentials"
    };

    /* set default behavior for Post method */
    ON_CALL(*curl_, Post(KLoginUri_, kReqHeaders, kReqData))
        .WillByDefault(testing::Throw(std::runtime_error(kErrorMessage)));

    auto listener = std::make_shared<espotifai_api::test::AccessListenerMock>();

    EXPECT_CALL(*curl_, Post(KLoginUri_, kReqHeaders, kReqData))
        .Times(1)
        .WillOnce(testing::Throw(std::runtime_error(kErrorMessage)));
    EXPECT_CALL(*listener, OnAccessGuaranteed(testing::_)).Times(0);
    EXPECT_CALL(*listener, OnAccessDenied(kErrorMessage))
        .Times(1);

    api_.RequestAccess(*listener, kClientId, kClientSecret);
}
