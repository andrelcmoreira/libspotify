/**
 * @file
 *
 * @brief Music searcher test class implementation.
 */
#include "private/searcher.h"

#include <gtest/gtest.h>

#include <fstream>
#include <memory>

#include "spotify.h"
#include "mock/curl_wrapper_mock.h"
#include "mock/search_listener_mock.h"
#include "private/curl_wrapper.h"
#include "types.h"

using std::ifstream;
using std::make_shared;
using std::runtime_error;
using std::shared_ptr;
using std::string;
using std::vector;

using spotify_lib::Spotify;
using spotify_lib::MusicInfo;
using spotify_lib::Searcher;
using spotify_lib::test::CurlWrapperMock;
using spotify_lib::test::SearchListenerMock;

using Json::Value;

using testing::_;
using testing::Return;
using testing::Test;
using testing::Throw;

class MusicSearcherTest : public Test {
 public:
  MusicSearcherTest()
      : curl_{make_shared<CurlWrapperMock>()},
        searcher_{make_shared<Searcher>(curl_)},
        lib_{nullptr, searcher_, nullptr} {}

 protected:
  shared_ptr<CurlWrapperMock> curl_;    //!< Curl wrapper mock instance.
  shared_ptr<Searcher> searcher_;  //!< Spotify music searcher instance.
  Spotify lib_;                             //!< Spotify instance.
  const string kMusicSearchBaseUri_{
      "https://lib.spotify.com/v1/search?q="};  //!< URI used for music
                                                //!< searching.
};

/**
 * @brief This tests validates the scenario when the user try to search a valid
 * music in the spotify API and the result will contain several matches. When
 * this occurs, the spotify_lib must return the list of found musics through
 * the listener.
 */
TEST_F(MusicSearcherTest,
       W_UserSearchForAnExistentMusic_S_ReturnTheListOfMatches) {
  /* test constants */
  const string kSearchName{"umbrella"};
  const string kUri{kMusicSearchBaseUri_ + kSearchName +
                    "&type=track&limit=10"};
  const string kAccessToken{"ASUUHnbvBbHASddBSd87asdSA=DDDAa=UUl-=y"};
  const vector<string> kReqHeaders{"Authorization: Bearer " + kAccessToken};
  const vector<MusicInfo> kExpectedReturn{
      {.name = "Umbrella",
       .artist = "Rihanna",
       .uri = "spotify:track:49FYlytm3dAAraYgpoJZux",
       .duration = 275986},
      {.name = "Umbrella",
       .artist = "Laffey",
       .uri = "spotify:track:0ORfekOSAhkcYgdTS4YK8f",
       .duration = 122718},
      {.name = "Umbrella",
       .artist = "All Time Low",
       .uri = "spotify:track:6ZUQhRkFJqiPsOucrXZwS6",
       .duration = 229853}};

  /* build request reply */
  Value reply;
  {
    ifstream json_file{
        "tests/unit/mock/jsons/search_result_multiple.json",
    };

    json_file >> reply;
  }

  auto listener = make_shared<SearchListenerMock>();

  /* set default behavior for Get method */
  ON_CALL(*curl_, Get(kUri, kReqHeaders)).WillByDefault(Return(reply));

  EXPECT_CALL(*curl_, Get(kUri, kReqHeaders)).Times(1);
  EXPECT_CALL(*listener, OnSearchError(_)).Times(0);
  EXPECT_CALL(*listener, OnPatternFound(kExpectedReturn)).Times(1);

  lib_.Search(*listener, kAccessToken, kSearchName);
}

/**
 * @brief This tests validates the scenario when the user try to search a valid
 * music in the spotify API and the result contain just one music. When this
 * occurs, the spotify_lib must return the list of found musics through the
 * listener.
 */
TEST_F(MusicSearcherTest,
       W_UserSearchForASingleExistentMusic_S_ReturnTheListWithOneMatch) {
  /* test constants */
  const string kSearchName{"staayyyle"};
  const string kUri{kMusicSearchBaseUri_ + kSearchName +
                    "&type=track&limit=10"};
  const string kAccessToken{"ASUUHnbvBbHASddBSd87asdSA=DDDAa=UUl-=y"};
  const vector<string> kReqHeaders{"Authorization: Bearer " + kAccessToken};
  const vector<MusicInfo> kExpectedReturn{
      {.name = "Staayyyle",
       .artist = "Spazz",
       .uri = "spotify:track:6jaY08cdgxbkVYMSSLR9kK",
       .duration = 26146}};

  /* build request reply */
  Value reply;
  {
    ifstream json_file{
        "tests/unit/mock/jsons/search_result_single_without_spaces.json",
    };

    json_file >> reply;
  }

  auto listener = make_shared<SearchListenerMock>();

  /* set default behavior for Get method */
  ON_CALL(*curl_, Get(kUri, kReqHeaders)).WillByDefault(Return(reply));

  EXPECT_CALL(*curl_, Get(kUri, kReqHeaders)).Times(1);
  EXPECT_CALL(*listener, OnSearchError(_)).Times(0);
  EXPECT_CALL(*listener, OnPatternFound(kExpectedReturn)).Times(1);

  lib_.Search(*listener, kAccessToken, kSearchName);
}

/**
 * @brief This tests validates the scenario when the user try to search a valid
 * music which contain several words in the spotify API and the result contain
 * the list of matches. When this occurs, the spotify_lib must return the list
 * of found musics through the listener.
 */
TEST_F(MusicSearcherTest,
       W_UserSearchForAnExistentMusicWithSpaces_S_ReturnTheListWithMatches) {
  /* test constants */
  const string kSearchName{"protocols of anti sound"};
  const string kSearchNameUrl{"protocols+of+anti+sound"};
  const string kUri{kMusicSearchBaseUri_ + kSearchNameUrl +
                    "&type=track&limit=10"};
  const string kAccessToken{"ASUUHnbvBbHASddBSd87asdSA=DDDAa=UUl-=y"};
  const vector<string> kReqHeaders{"Authorization: Bearer " + kAccessToken};
  const vector<MusicInfo> kExpectedReturn{
      {.name = "The Protocols Of Anti-Sound",
       .artist = "Magrudergrind",
       .uri = "spotify:track:2UNCakVkFNo9ClIHbnSBTx",
       .duration = 107813},
      {.name = "Protocols of Anti-Sound",
       .artist = "Mommy's lil Monsterz",
       .uri = "spotify:track:65ypeYc66Mikf6Hx061XqM",
       .duration = 77000}};

  /* build request reply */
  Value reply;
  {
    ifstream json_file{
        "tests/unit/mock/jsons/search_result_multiple_with_spaces.json",
    };

    json_file >> reply;
  }

  auto listener = make_shared<SearchListenerMock>();

  /* set default behavior for Get method */
  ON_CALL(*curl_, Get(kUri, kReqHeaders)).WillByDefault(Return(reply));

  EXPECT_CALL(*curl_, Get(kUri, kReqHeaders)).Times(1);
  EXPECT_CALL(*listener, OnSearchError(_)).Times(0);
  EXPECT_CALL(*listener, OnPatternFound(kExpectedReturn)).Times(1);

  lib_.Search(*listener, kAccessToken, kSearchName);
}

/**
 * @brief This tests validates the scenario when the user try to search a non
 * existent music in the spotify API. When this occurs, the spotify_lib must
 * return an empty list through the listener.
 */
TEST_F(MusicSearcherTest, W_UserSearchForANonExistentMusic_S_ReturnEmptyList) {
  const string kSearchName{"asidjhisuadhfoisduhfaisoduhfaoisudfhaisoudfh"};
  const string kUri{kMusicSearchBaseUri_ + kSearchName +
                    "&type=track&limit=10"};
  const string kAccessToken{"ASUUHnbvBbHASddBSd87asdSA=DDDAa=UUl-=y"};
  const vector<string> kReqHeaders{"Authorization: Bearer " + kAccessToken};
  const vector<MusicInfo> kExpectedReturn;

  /* build request reply */
  Value reply;
  {
    ifstream json_file{
        "tests/unit/mock/jsons/search_result_with_no_musics.json",
    };

    json_file >> reply;
  }

  auto listener = make_shared<SearchListenerMock>();

  /* set default behavior for Get method */
  ON_CALL(*curl_, Get(kUri, kReqHeaders)).WillByDefault(Return(reply));

  EXPECT_CALL(*curl_, Get(kUri, kReqHeaders)).Times(1);
  EXPECT_CALL(*listener, OnSearchError(_)).Times(0);
  EXPECT_CALL(*listener, OnPatternFound(kExpectedReturn)).Times(1);

  lib_.Search(*listener, kAccessToken, kSearchName);
}

/**
 * @brief This tests validates the scenario when the user try to search an
 * existent music in the spotify API with a network error. When this occurs, the
 * spotify_lib must return the suitable error message through the listener.
 */
TEST_F(MusicSearcherTest,
       W_UserSearchForAnExistentMusicWithError_S_ReturnErrorMessage) {
  const string kSearchName{"umbrella"};
  const string kErrorMessage{"some cool error message"};
  const string kUri{kMusicSearchBaseUri_ + kSearchName +
                    "&type=track&limit=10"};
  const string kAccessToken{"ASUUHnbvBbHASddBSd87asdSA=DDDAa=UUl-=y"};
  const vector<string> kReqHeaders{"Authorization: Bearer " + kAccessToken};

  auto listener = make_shared<SearchListenerMock>();

  /* set default behavior for Get method */
  ON_CALL(*curl_, Get(kUri, kReqHeaders))
      .WillByDefault(Throw(runtime_error(kErrorMessage)));

  EXPECT_CALL(*curl_, Get(kUri, kReqHeaders))
      .Times(1)
      .WillOnce(Throw(runtime_error(kErrorMessage)));
  EXPECT_CALL(*listener, OnSearchError(kErrorMessage)).Times(1);
  EXPECT_CALL(*listener, OnPatternFound(testing::_)).Times(0);

  lib_.Search(*listener, kAccessToken, kSearchName);
}
