/**
 * \file
 * \brief Music searcher test class implementation.
 */
#include <gtest/gtest.h>

#include <fstream>
#include <memory>

#include "mock/search_music_listener_mock.h"
#include "mock/curl_wrapper_mock.h"
#include "mock/db_handler_mock.h"


#include "api.h"
#include "private/curl_wrapper.h"
#include "private/music_searcher.h"
#include "private/playlist_mgr.h"
#include "types.h"

class MusicSearcherTest : public testing::Test {
    public:
     MusicSearcherTest()
          : curl_{std::make_shared<espotifai_api::test::CurlWrapperMock>()},
            searcher_{std::make_shared<espotifai_api::MusicSearcher>(curl_)},
            db_mock_{std::make_shared<espotifai_api::test::DbHandlerMock>()},
            playlist_mgr_{std::make_shared<espotifai_api::PlaylistMgr>(db_mock_)},
            api_{nullptr, searcher_, playlist_mgr_}
     {
     }

    protected:
     std::shared_ptr<espotifai_api::test::CurlWrapperMock> curl_; //!< Curl wrapper mock instance.
     std::shared_ptr<espotifai_api::MusicSearcher> searcher_; //!< Spotify music searcher instance.
     /* The playlist mgr must be supplied with a mocked database handler due mongodb instance. */
     /* TODO: fix this behavior */
     std::shared_ptr<espotifai_api::test::DbHandlerMock> db_mock_; //!< Database mock.
     std::shared_ptr<espotifai_api::PlaylistMgr> playlist_mgr_; //!< Playlist manager.
     espotifai_api::Api api_; //!< Api instance.
     const std::string kMusicSearchBaseUri_{"https://api.spotify.com/v1/search?q="}; //!< URI used for music searching.
};

/**
 * \brief This tests validates the scenario when the user try to search a valid music
 * in the spotify API and the result will contain several matches. When this occurs, the
 * espotifai_api must return the list of found musics through the listener.
 */
TEST_F(MusicSearcherTest, W_UserSearchForAnExistentMusic_S_ReturnTheListOfMatches)
{
    /* test constants */
    const std::string kSearchName{"umbrella"};
    const std::string kUri{kMusicSearchBaseUri_ + kSearchName + "&type=track&limit=10"};
    const std::string kAccessToken{"ASUUHnbvBbHASddBSd87asdSA=DDDAa=UUl-=y"};
    const std::vector<std::string> kReqHeaders{
        "Authorization: Bearer " + kAccessToken
    };
    const std::vector<espotifai_api::MusicInfo> kExpectedReturn{
        {
            .name = "Umbrella",
            .artist = "Rihanna",
            .uri = "spotify:track:49FYlytm3dAAraYgpoJZux",
            .duration = 275986
        },
        {
            .name = "Umbrella",
            .artist = "Laffey",
            .uri = "spotify:track:0ORfekOSAhkcYgdTS4YK8f",
            .duration = 122718
        },
        {
            .name = "Umbrella",
            .artist = "All Time Low",
            .uri = "spotify:track:6ZUQhRkFJqiPsOucrXZwS6",
            .duration = 229853
        }
    };

    /* build request reply */
    Json::Value reply;
    {
        std::ifstream json_file{
            "../unit/jsons/search_result_multiple.json",
        };

        json_file >> reply;
    }

    auto listener = std::make_shared<espotifai_api::test::SearchMusicListenerMock>();

    /* set default behavior for Get method */
    ON_CALL(*curl_, Get(kUri, kReqHeaders))
        .WillByDefault(testing::Return(reply));

    EXPECT_CALL(*curl_, Get(kUri, kReqHeaders)).Times(1);
    EXPECT_CALL(*listener, OnMusicSearchError(testing::_)).Times(0);
    EXPECT_CALL(*listener, OnMusicFound(kExpectedReturn)).Times(1);

    api_.SearchMusic(*listener, kAccessToken, kSearchName);
}

/**
 * \brief This tests validates the scenario when the user try to search a valid music
 * in the spotify API and the result contain just one music. When this occurs, the espotifai_api
 * must return the list of found musics through the listener.
 */
TEST_F(MusicSearcherTest, W_UserSearchForASingleExistentMusic_S_ReturnTheListWithOneMatch)
{
    /* test constants */
    const std::string kSearchName{"staayyyle"};
    const std::string kUri{kMusicSearchBaseUri_ + kSearchName + "&type=track&limit=10"};
    const std::string kAccessToken{"ASUUHnbvBbHASddBSd87asdSA=DDDAa=UUl-=y"};
    const std::vector<std::string> kReqHeaders{
        "Authorization: Bearer " + kAccessToken
    };
    const std::vector<espotifai_api::MusicInfo> kExpectedReturn{
        {
            .name = "Staayyyle",
            .artist = "Spazz",
            .uri = "spotify:track:6jaY08cdgxbkVYMSSLR9kK",
            .duration = 26146
        }
    };

    /* build request reply */
    Json::Value reply;
    {
        std::ifstream json_file{
            "../unit/jsons/search_result_single_without_spaces.json",
        };

        json_file >> reply;
    }

    auto listener = std::make_shared<espotifai_api::test::SearchMusicListenerMock>();

    /* set default behavior for Get method */
    ON_CALL(*curl_, Get(kUri, kReqHeaders))
        .WillByDefault(testing::Return(reply));

    EXPECT_CALL(*curl_, Get(kUri, kReqHeaders)).Times(1);
    EXPECT_CALL(*listener, OnMusicSearchError(testing::_)).Times(0);
    EXPECT_CALL(*listener, OnMusicFound(kExpectedReturn)).Times(1);

    api_.SearchMusic(*listener, kAccessToken, kSearchName);
}

/**
 * \brief This tests validates the scenario when the user try to search a valid music which
 * contain several words in the spotify API and the result contain the list of matches.
 * When this occurs, the espotifai_api must return the list of found musics through the listener.
 */
TEST_F(MusicSearcherTest, W_UserSearchForAnExistentMusicWithSpaces_S_ReturnTheListWithMatches)
{
    /* test constants */
    const std::string kSearchName{"protocols of anti sound"};
    const std::string kSearchNameUrl{"protocols+of+anti+sound"};
    const std::string kUri{kMusicSearchBaseUri_ + kSearchNameUrl + "&type=track&limit=10"};
    const std::string kAccessToken{"ASUUHnbvBbHASddBSd87asdSA=DDDAa=UUl-=y"};
    const std::vector<std::string> kReqHeaders{
        "Authorization: Bearer " + kAccessToken
    };
    const std::vector<espotifai_api::MusicInfo> kExpectedReturn{
        {
            .name = "The Protocols Of Anti-Sound",
            .artist = "Magrudergrind",
            .uri = "spotify:track:2UNCakVkFNo9ClIHbnSBTx",
            .duration = 107813
        },
        {
            .name = "Protocols of Anti-Sound",
            .artist = "Mommy's lil Monsterz",
            .uri = "spotify:track:65ypeYc66Mikf6Hx061XqM",
            .duration = 77000
        }
    };

    /* build request reply */
    Json::Value reply;
    {
        std::ifstream json_file{
            "../unit/jsons/search_result_multiple_with_spaces.json",
        };

        json_file >> reply;
    }

    auto listener = std::make_shared<espotifai_api::test::SearchMusicListenerMock>();

    /* set default behavior for Get method */
    ON_CALL(*curl_, Get(kUri, kReqHeaders))
        .WillByDefault(testing::Return(reply));

    EXPECT_CALL(*curl_, Get(kUri, kReqHeaders)).Times(1);
    EXPECT_CALL(*listener, OnMusicSearchError(testing::_)).Times(0);
    EXPECT_CALL(*listener, OnMusicFound(kExpectedReturn)).Times(1);

    api_.SearchMusic(*listener, kAccessToken, kSearchName);
}

/**
 * \brief This tests validates the scenario when the user try to search a non existent
 * music in the spotify API. When this occurs, the espotifai_api must return an empty
 * list through the listener.
 */
TEST_F(MusicSearcherTest, W_UserSearchForANonExistentMusic_S_ReturnEmptyList)
{
    const std::string kSearchName{"asidjhisuadhfoisduhfaisoduhfaoisudfhaisoudfh"};
    const std::string kUri{kMusicSearchBaseUri_ + kSearchName + "&type=track&limit=10"};
    const std::string kAccessToken{"ASUUHnbvBbHASddBSd87asdSA=DDDAa=UUl-=y"};
    const std::vector<std::string> kReqHeaders{
        "Authorization: Bearer " + kAccessToken
    };
    const std::vector<espotifai_api::MusicInfo> kExpectedReturn;

    /* build request reply */
    Json::Value reply;
    {
        std::ifstream json_file{
            "../unit/jsons/search_result_with_no_musics.json",
        };

        json_file >> reply;
    }

    auto listener = std::make_shared<espotifai_api::test::SearchMusicListenerMock>();

    /* set default behavior for Get method */
    ON_CALL(*curl_, Get(kUri, kReqHeaders))
        .WillByDefault(testing::Return(reply));

    EXPECT_CALL(*curl_, Get(kUri, kReqHeaders)).Times(1);
    EXPECT_CALL(*listener, OnMusicSearchError(testing::_)).Times(0);
    EXPECT_CALL(*listener, OnMusicFound(kExpectedReturn)).Times(1);

    api_.SearchMusic(*listener, kAccessToken, kSearchName);
}

/**
 * \brief This tests validates the scenario when the user try to search an existent music
 * in the spotify API with a network error. When this occurs, the espotifai_api must
 * return the suitable error message through the listener.
 */
TEST_F(MusicSearcherTest, W_UserSearchForAnExistentMusicWithError_S_ReturnErrorMessage)
{
    const std::string kSearchName{"umbrella"};
    const std::string kErrorMessage{"some cool error message"};
    const std::string kUri{kMusicSearchBaseUri_ + kSearchName + "&type=track&limit=10"};
    const std::string kAccessToken{"ASUUHnbvBbHASddBSd87asdSA=DDDAa=UUl-=y"};
    const std::vector<std::string> kReqHeaders{
        "Authorization: Bearer " + kAccessToken
    };

    auto listener = std::make_shared<espotifai_api::test::SearchMusicListenerMock>();

    /* set default behavior for Get method */
    ON_CALL(*curl_, Get(kUri, kReqHeaders))
        .WillByDefault(testing::Throw(std::runtime_error(kErrorMessage)));

    EXPECT_CALL(*curl_, Get(kUri, kReqHeaders))
        .Times(1)
        .WillOnce(testing::Throw(std::runtime_error(kErrorMessage)));
    EXPECT_CALL(*listener, OnMusicSearchError(kErrorMessage)).Times(1);
    EXPECT_CALL(*listener, OnMusicFound(testing::_)).Times(0);

    api_.SearchMusic(*listener, kAccessToken, kSearchName);
}
