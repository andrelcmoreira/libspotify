/**
 * @file
 *
 * @brief Spotify authenticator test class implementation.
 */
#include "private/authenticator.h"

#include <gtest/gtest.h>

#include <memory>

#include "api.h"
#include "mock/access_listener_mock.h"
#include "mock/curl_wrapper_mock.h"
#include "private/curl_wrapper.h"
#include "private/utils.h"

using std::make_shared;
using std::shared_ptr;
using std::string;
using std::vector;

using espotifai_api::Api;
using espotifai_api::Authenticator;
using espotifai_api::test::AccessListenerMock;
using espotifai_api::test::CurlWrapperMock;

using testing::_;
using testing::Return;
using testing::Test;
using testing::Throw;

using Json::Value;

class AuthTest : public Test {
 public:
  AuthTest()
      : curl_{make_shared<CurlWrapperMock>()},
        auth_{make_shared<Authenticator>(curl_)},
        api_{auth_, nullptr, nullptr} {}

 protected:
  shared_ptr<CurlWrapperMock> curl_;  //!< Curl wrapper mock instance.
  shared_ptr<Authenticator> auth_;      //!< Spotify auth instance.
  Api api_;                           //!< Api instance.
  const string KLoginUri_{
      "https://accounts.spotify.com/api/token"};  //!< URI used for
                                                  //!< authentication.
};

/**
 * @brief This tests validates the scenario when the user try to log into the
 * spotify API with a valid client_id and client_credentials. When this occurs,
 * the espotifai_api must return the access token through the listener.
 */
TEST_F(AuthTest,
       W_UserRequestAuthWithValidCredentials_S_LogWithSuccess) {
  /* test constants */
  const string kClientId{"good_id"};
  const string kClientSecret{"good_secret"};
  const vector<string> kReqHeaders{
      "Authorization: Basic " +
      espotifai_api::utils::GetBase64Code(kClientId + ":" + kClientSecret)};
  const vector<string> kReqData{"grant_type=client_credentials"};
  Value expected_return;

  /* build the expected return */
  expected_return["access_token"] =
      "BQDGLtwpiJbNGiJejVpzV6xvFFwlaDCysDW41sPWJgVBL0XBWXj7wMm7";
  expected_return["token_type"] = "Bearer";
  expected_return["expires_in"] = "3600";
  expected_return["scope"] = "";

  auto listener = make_shared<AccessListenerMock>();

  /* set default behavior for Post method */
  ON_CALL(*curl_, Post(KLoginUri_, kReqHeaders, kReqData))
      .WillByDefault(Return(expected_return));

  EXPECT_CALL(*curl_, Post(KLoginUri_, kReqHeaders, kReqData)).Times(1);
  EXPECT_CALL(*listener, OnAccessDenied(_)).Times(0);
  EXPECT_CALL(*listener,
              OnAccessGuaranteed(expected_return["access_token"].asString()))
      .Times(1);

  api_.Auth(*listener, kClientId, kClientSecret);
}

/**
 * @brief This tests validates the scenario when the user try to log into the
 * spotify API with an invalid client_id and client_credentials. When this
 * occurs, the espotifai_api must return the suitable error message through the
 * listener.
 */
TEST_F(AuthTest, W_UserRequestAuthWithBadCredentials_S_ReturnFailure) {
  /* test constants */
  const string kClientId{"bad_id"};
  const string kClientSecret{"bad_secret"};
  const string kExpectedMsg{
      "fail to authenticate the user with the provided credentials!"};
  const vector<string> kReqHeaders{
      "Authorization: Basic " +
      espotifai_api::utils::GetBase64Code(kClientId + ":" + kClientSecret)};
  const vector<string> kReqData{"grant_type=client_credentials"};
  Value expected_return;

  /* build the expected return */
  expected_return["error"] = "invalid_client";
  expected_return["error_description"] = "Invalid client secret";

  auto listener = make_shared<AccessListenerMock>();

  /* set default behavior for Post method */
  ON_CALL(*curl_, Post(KLoginUri_, kReqHeaders, kReqData))
      .WillByDefault(Return(expected_return));

  EXPECT_CALL(*curl_, Post(KLoginUri_, kReqHeaders, kReqData)).Times(1);
  EXPECT_CALL(*listener, OnAccessDenied(kExpectedMsg)).Times(1);
  EXPECT_CALL(*listener, OnAccessGuaranteed(_)).Times(0);

  api_.Auth(*listener, kClientId, kClientSecret);
}

/**
 * @brief This tests validates the scenario when the user try to log into the
 * spotify API offline. When this occurs, the espotifai_api must return the
 * suitable error message through the listener.
 */
TEST_F(AuthTest, W_UserRequestAuthOffline_S_ReturnFailure) {
  /* test constants */
  const string kClientId{"good_id"};
  const string kClientSecret{"good_secret"};
  const string kErrorMessage{"some cool error message"};
  const vector<string> kReqHeaders{
      "Authorization: Basic " +
      espotifai_api::utils::GetBase64Code(kClientId + ":" + kClientSecret)};
  const vector<string> kReqData{"grant_type=client_credentials"};

  /* set default behavior for Post method */
  ON_CALL(*curl_, Post(KLoginUri_, kReqHeaders, kReqData))
      .WillByDefault(Throw(std::runtime_error(kErrorMessage)));

  auto listener = make_shared<AccessListenerMock>();

  EXPECT_CALL(*curl_, Post(KLoginUri_, kReqHeaders, kReqData))
      .Times(1)
      .WillOnce(Throw(std::runtime_error(kErrorMessage)));
  EXPECT_CALL(*listener, OnAccessGuaranteed(_)).Times(0);
  EXPECT_CALL(*listener, OnAccessDenied(kErrorMessage)).Times(1);

  api_.Auth(*listener, kClientId, kClientSecret);
}
