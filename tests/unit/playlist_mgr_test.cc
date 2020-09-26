/**
 * \file
 * \brief Playlist manager test class implementation.
 */
#include <gtest/gtest.h>

#include <memory>

#include "mock/add_music_playlist_listener_mock.h"
#include "mock/create_playlist_listener_mock.h"
#include "mock/list_playlist_musics_listener_mock.h"
#include "mock/db_handler_mock.h"

#include "api.h"
#include "private/playlist_mgr.h"

class PlaylistMgrTest : public testing::Test {
    public:
     PlaylistMgrTest()
          : db_mock_{std::make_shared<espotifai_api::test::DbHandlerMock>()},
            playlist_mgr_{std::make_shared<espotifai_api::PlaylistMgr>(db_mock_)},
            api_{nullptr, nullptr, playlist_mgr_}
     {
     }

    protected:
     std::shared_ptr<espotifai_api::test::DbHandlerMock> db_mock_; //!< Database mock.
     std::shared_ptr<espotifai_api::PlaylistMgr> playlist_mgr_; //!< Playlist manager.
     espotifai_api::Api api_; //!< Api instance.
};

/**
 * \brief This tests validates the scenario when the user try create a new playlist. When
 * this occurs, the espotifai_api must create it and return notify the user through the
 * listener.
 */
TEST_F(PlaylistMgrTest, W_UserRequestTheCreationOfANewPlaylist_S_CreatePlaylist)
{
    /* test constants */
    const std::string kPlaylistName{"my cool playlist"};
    const std::string kPlaylistOwner{"foo"};

    auto listener = std::make_shared<espotifai_api::test::CreatePlaylistListenerMock>();

    /* set default behavior for FindPlaylist method */
    ON_CALL(*db_mock_, FindPlaylist(kPlaylistName))
        .WillByDefault(testing::Return(false));

    EXPECT_CALL(*db_mock_, FindPlaylist(kPlaylistName)).Times(1);
    EXPECT_CALL(*db_mock_, CreatePlaylist(kPlaylistName)).Times(1);
    EXPECT_CALL(*listener, OnPlaylistCreated()).Times(1);
    EXPECT_CALL(*listener, OnPlaylistCreationError(testing::_))
        .Times(0);

    api_.CreatePlaylist(*listener, kPlaylistName, kPlaylistOwner);
}

/**
 * \brief This tests validates the scenario when the user try create a playlist which
 * already exist on database. When this occurs, the espotifai_api must return the suitable
 * error message through the listener.
 */
TEST_F(PlaylistMgrTest, W_UserRequestTheCreationOfAPlaylistThatAlreadyExist_S_ReturnFailure)
{
    /* test constants */
    const std::string kPlaylistName{"my cool playlist"};
    const std::string kErrorMessage{"the playlist already exist!"};
    const std::string kPlaylistOwner{"foo"};

    auto listener = std::make_shared<espotifai_api::test::CreatePlaylistListenerMock>();

    /* set default behavior for FindPlaylist method */
    ON_CALL(*db_mock_, FindPlaylist(kPlaylistName))
        .WillByDefault(testing::Return(true));

    EXPECT_CALL(*db_mock_, FindPlaylist(kPlaylistName)).Times(1);
    EXPECT_CALL(*db_mock_, CreatePlaylist(kPlaylistName)).Times(0);
    EXPECT_CALL(*listener, OnPlaylistCreated()).Times(0);
    EXPECT_CALL(*listener, OnPlaylistCreationError(kErrorMessage))
        .Times(1);

    api_.CreatePlaylist(*listener, kPlaylistName, kPlaylistOwner);
}

/**
 * \brief This tests validates the scenario when the user try to create a playlist, but an
 * error occurs at database level. When this occurs, the espotifai_api must return the the
 * suitable error message through the listener.
 */
TEST_F(PlaylistMgrTest, W_UserRequestTheCreationOfAPlaylistWithDatabaseError_S_ReturnFailure)
{
    /* test constants */
    const std::string kPlaylistName{"my cool playlist"};
    const std::string kErrorMsg{"something went wrong!"};
    const std::string kPlaylistOwner{"foo"};

    auto listener = std::make_shared<espotifai_api::test::CreatePlaylistListenerMock>();

    /* set default behavior for CreatePlaylist method */
    ON_CALL(*db_mock_, FindPlaylist(kPlaylistName))
        .WillByDefault(testing::Return(false));
    ON_CALL(*db_mock_, CreatePlaylist(kPlaylistName))
        .WillByDefault(testing::Throw(std::runtime_error(kErrorMsg)));

    EXPECT_CALL(*db_mock_, FindPlaylist(kPlaylistName)).Times(1);
    EXPECT_CALL(*db_mock_, CreatePlaylist(kPlaylistName))
        .Times(1)
        .WillOnce(testing::Throw(std::runtime_error(kErrorMsg)));
    EXPECT_CALL(*listener, OnPlaylistCreated()).Times(0);
    EXPECT_CALL(*listener, OnPlaylistCreationError(kErrorMsg))
        .Times(1);

    api_.CreatePlaylist(*listener, kPlaylistName, kPlaylistOwner);
}

/**
 * \brief This tests validates the scenario when the user try to add a music to an
 * existent playlist. When this occurs, the espotifai_api must add the music to the
 * given playlist and return success through the listener.
 */
TEST_F(PlaylistMgrTest, W_UserAddMusicToExistentPlaylist_S_MusicBeAdded)
{
    /* test constants */
    const std::string kPlaylistName{"my cool playlist"};
    const std::string kPlaylistOwner{"foo"};
    const espotifai_api::MusicInfo kMusic{
        .name = "cool music",
        .artist = "cool artist",
        .uri = "cool uri",
        .duration = 1234
    };

    auto listener = std::make_shared<espotifai_api::test::AddMusicPlaylistListenerMock>();

    /* set default behavior for FindPlaylist method */
    ON_CALL(*db_mock_, FindPlaylist(kPlaylistName))
        .WillByDefault(testing::Return(true));
    ON_CALL(*db_mock_, FindMusicInPlaylist(kMusic.uri, kPlaylistName))
        .WillByDefault(testing::Return(false));

    EXPECT_CALL(*db_mock_, FindPlaylist(kPlaylistName)).Times(1);
    EXPECT_CALL(*db_mock_, FindMusicInPlaylist(kMusic.uri, kPlaylistName)).Times(1);
    EXPECT_CALL(*db_mock_, AddMusic(kMusic, kPlaylistName)).Times(1);
    EXPECT_CALL(*listener, OnMusicAdded()).Times(1);
    EXPECT_CALL(*listener, OnMusicAdditionError(testing::_))
        .Times(0);

    api_.AddMusicToPlaylist(*listener, kMusic, kPlaylistName);
}

/**
 * \brief This tests validates the scenario when the user try to add a music to a
 * non existent playlist. When this occurs, the espotifai_api must return the suitable
 * error message through the listener.
 */
TEST_F(PlaylistMgrTest, W_UserAddMusicToNonExistentPlaylist_S_ReturnFailure)
{
    /* test constants */
    const std::string kPlaylistName{"non existent playlist"};
    const std::string kPlaylistOwner{"foo"};
    const std::string kErrorMsg{"the playlist doesn't exist!"};
    const espotifai_api::MusicInfo kMusic{
        .name = "cool music",
        .artist = "cool artist",
        .uri = "cool uri",
        .duration = 1234
    };

    auto listener = std::make_shared<espotifai_api::test::AddMusicPlaylistListenerMock>();

    /* set default behavior for FindPlaylist method */
    ON_CALL(*db_mock_, FindPlaylist(kPlaylistName))
        .WillByDefault(testing::Return(false));

    EXPECT_CALL(*db_mock_, FindPlaylist(kPlaylistName)).Times(1);
    EXPECT_CALL(*db_mock_, FindMusicInPlaylist(kMusic.uri, kPlaylistName)).Times(0);
    EXPECT_CALL(*db_mock_, AddMusic(kMusic, kPlaylistName)).Times(0);
    EXPECT_CALL(*listener, OnMusicAdded()).Times(0);
    EXPECT_CALL(*listener, OnMusicAdditionError(kErrorMsg))
        .Times(1);

    api_.AddMusicToPlaylist(*listener, kMusic, kPlaylistName);
}

/**
 * \brief This tests validates the scenario when the user try to add an existent music to a
 * playlist. When this occurs, the espotifai_api must return the suitable error message
 * through the listener.
 */
TEST_F(PlaylistMgrTest, W_UserAddMusicWichAlreadyExistInPlaylist_S_ReturnFailure)
{
    /* test constants */
    const std::string kPlaylistName{"existent playlist"};
    const std::string kPlaylistOwner{"foo"};
    const std::string kErrorMsg{"the music already exist in playlist!"};
    const espotifai_api::MusicInfo kMusic{
        .name = "cool music",
        .artist = "cool artist",
        .uri = "cool uri",
        .duration = 1234
    };

    auto listener = std::make_shared<espotifai_api::test::AddMusicPlaylistListenerMock>();

    /* set default behavior for FindPlaylist method */
    ON_CALL(*db_mock_, FindPlaylist(kPlaylistName))
        .WillByDefault(testing::Return(true));
    ON_CALL(*db_mock_, FindMusicInPlaylist(kMusic.uri, kPlaylistName))
        .WillByDefault(testing::Return(true));

    EXPECT_CALL(*db_mock_, FindPlaylist(kPlaylistName)).Times(1);
    EXPECT_CALL(*db_mock_, FindMusicInPlaylist(kMusic.uri, kPlaylistName)).Times(1);
    EXPECT_CALL(*db_mock_, AddMusic(kMusic, kPlaylistName)).Times(0);
    EXPECT_CALL(*listener, OnMusicAdded()).Times(0);
    EXPECT_CALL(*listener, OnMusicAdditionError(kErrorMsg))
        .Times(1);

    api_.AddMusicToPlaylist(*listener, kMusic, kPlaylistName);
}

/**
 * \brief This tests validates the scenario when the user try list the musics of an
 * existent playlist. When this occurs, the API must return the list of musics related
 * to the playlist through the listener.
 */
TEST_F(PlaylistMgrTest, W_UserTryToListMusicsOfExistentPlaylist_S_ReturnTheMusicList)
{
    /* test constants */
    const std::string kPlaylistName{"existent playlist"};
    const std::string kPlaylistOwner{"foo"};
    const std::vector<espotifai_api::MusicInfo> kMusicList{
        {
            .name = "music 1",
            .artist = "artist 1",
            .uri = "uri 1",
            .duration = 1234
        },
        {
            .name = "music 2",
            .artist = "artist 2",
            .uri = "uri 2",
            .duration = 4567
        }

    };

    auto listener = std::make_shared<espotifai_api::test::ListPlaylistMusicsListenerMock>();

    /* set default behavior for FindPlaylist method */
    ON_CALL(*db_mock_, FindPlaylist(kPlaylistName))
        .WillByDefault(testing::Return(true));
    ON_CALL(*db_mock_, GetMusics(kPlaylistName))
        .WillByDefault(testing::Return(kMusicList));

    EXPECT_CALL(*db_mock_, FindPlaylist(kPlaylistName)).Times(1);
    EXPECT_CALL(*db_mock_, GetMusics(kPlaylistName)).Times(1);
    EXPECT_CALL(*listener, OnMusicList(kMusicList)).Times(1);
    EXPECT_CALL(*listener, OnMusicListError(testing::_))
        .Times(0);

    api_.ListPlaylistMusics(*listener, kPlaylistName);
}

/**
 * \brief This tests validates the scenario when the user try list the musics of a non
 * existent playlist. When this occurs, the API must return the suitable error through
 * the listener.
 */
TEST_F(PlaylistMgrTest, W_UserTryToListMusicsOfNonExistentPlaylist_S_ReturnFailure)
{
    /* test constants */
    const std::string kPlaylistName{"non existent playlist"};
    const std::string kPlaylistOwner{"foo"};
    const std::string kErrorMsg{"the playlist doesn't exist"};

    auto listener = std::make_shared<espotifai_api::test::ListPlaylistMusicsListenerMock>();

    /* set default behavior for FindPlaylist method */
    ON_CALL(*db_mock_, FindPlaylist(kPlaylistName))
        .WillByDefault(testing::Return(false));

    EXPECT_CALL(*db_mock_, FindPlaylist(kPlaylistName)).Times(1);
    EXPECT_CALL(*db_mock_, GetMusics(kPlaylistName)).Times(0);
    EXPECT_CALL(*listener, OnMusicList(testing::_)).Times(0);
    EXPECT_CALL(*listener, OnMusicListError(testing::_))
        .Times(1);

    api_.ListPlaylistMusics(*listener, kPlaylistName);
}

/**
 * \brief This tests validates the scenario when the user try list the musics of an empty
 * playlist. When this occurs, the API must return an empty list through the listener.
 */
TEST_F(PlaylistMgrTest, W_UserTryToListMusicsOfEmptyPlaylist_S_ReturnEmptyList)
{
    /* test constants */
    const std::string kPlaylistName{"empty playlist"};
    const std::string kPlaylistOwner{"foo"};
    const std::vector<espotifai_api::MusicInfo> kMusicList;

    auto listener = std::make_shared<espotifai_api::test::ListPlaylistMusicsListenerMock>();

    /* set default behavior for FindPlaylist method */
    ON_CALL(*db_mock_, FindPlaylist(kPlaylistName))
        .WillByDefault(testing::Return(true));
    ON_CALL(*db_mock_, GetMusics(kPlaylistName))
        .WillByDefault(testing::Return(kMusicList));

    EXPECT_CALL(*db_mock_, FindPlaylist(kPlaylistName)).Times(1);
    EXPECT_CALL(*db_mock_, GetMusics(kPlaylistName)).Times(1);
    EXPECT_CALL(*listener, OnMusicList(kMusicList)).Times(1);
    EXPECT_CALL(*listener, OnMusicListError(testing::_))
        .Times(0);

    api_.ListPlaylistMusics(*listener, kPlaylistName);
}
