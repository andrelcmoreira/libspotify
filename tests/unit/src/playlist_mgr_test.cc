/**
 * @file
 *
 * @brief Playlist manager test class implementation.
 */
#include "private/playlist_mgr.h"

#include <gtest/gtest.h>

#include <memory>

#include "api.h"
#include "mock/add_music_playlist_listener_mock.h"
#include "mock/playlist_listener_mock.h"

using std::make_shared;
using std::runtime_error;
using std::shared_ptr;
using std::string;
using std::vector;

using espotifai_api::Api;
using espotifai_api::MusicInfo;
using espotifai_api::PlaylistMgr;
using espotifai_api::Authenticator;
using espotifai_api::test::AddMusicPlaylistListenerMock;
using espotifai_api::test::PlaylistListenerMock;

using testing::_;
using testing::Return;
using testing::Test;
using testing::Throw;

class PlaylistMgrTest : public Test {
 public:
  PlaylistMgrTest()
      : playlist_mgr_{make_shared<PlaylistMgr>()},
        api_{nullptr, nullptr, playlist_mgr_} {}

 protected:
  shared_ptr<PlaylistMgr> playlist_mgr_;  //!< Playlist manager.
  Api api_;                               //!< Api instance.
};

/**
 * @brief This tests validates the scenario when the user try create a new
 * playlist. When this occurs, the espotifai_api must create it and return
 * notify the user through the listener.
 */
TEST_F(PlaylistMgrTest,
       W_UserRequestTheCreationOfANewPlaylist_S_CreatePlaylist) {
  //    /* test constants */
  //    const string kPlaylistName{"my cool playlist"};
  //    const string kPlaylistOwner{"foo"};
  //
  //    auto listener = make_shared<PlaylistListenerMock>();
  //
  //    /* set default behavior for FindPlaylist method */
  //    ON_CALL(*db_mock_, FindPlaylist(kPlaylistName))
  //        .WillByDefault(Return(false));
  //
  //    EXPECT_CALL(*db_mock_, FindPlaylist(kPlaylistName)).Times(1);
  //    EXPECT_CALL(*db_mock_, CreatePlaylist(kPlaylistName)).Times(1);
  //    EXPECT_CALL(*listener, OnPlaylistCreated()).Times(1);
  //    EXPECT_CALL(*listener, OnPlaylistCreationError(_)).Times(0);
  //
  //    api_.CreatePlaylist(*listener, kPlaylistName, kPlaylistOwner);
}

/**
 * @brief This tests validates the scenario when the user try create a playlist
 * which already exist on database. When this occurs, the espotifai_api must
 * return the suitable error message through the listener.
 */
TEST_F(PlaylistMgrTest,
       W_UserRequestTheCreationOfAPlaylistThatAlreadyExist_S_ReturnFailure) {
  //    /* test constants */
  //    const string kPlaylistName{"my cool playlist"};
  //    const string kErrorMessage{"the playlist already exist!"};
  //    const string kPlaylistOwner{"foo"};
  //
  //    auto listener = make_shared<PlaylistListenerMock>();
  //
  //    /* set default behavior for FindPlaylist method */
  //    ON_CALL(*db_mock_, FindPlaylist(kPlaylistName))
  //        .WillByDefault(Return(true));
  //
  //    EXPECT_CALL(*db_mock_, FindPlaylist(kPlaylistName)).Times(1);
  //    EXPECT_CALL(*db_mock_, CreatePlaylist(kPlaylistName)).Times(0);
  //    EXPECT_CALL(*listener, OnPlaylistCreated()).Times(0);
  //    EXPECT_CALL(*listener, OnPlaylistCreationError(kErrorMessage)).Times(1);
  //
  //    api_.CreatePlaylist(*listener, kPlaylistName, kPlaylistOwner);
}

/**
 * @brief This tests validates the scenario when the user try to create a
 * playlist, but an error occurs at database level. When this occurs, the
 * espotifai_api must return the the suitable error message through the
 * listener.
 */
TEST_F(PlaylistMgrTest,
       W_UserRequestTheCreationOfAPlaylistWithDatabaseError_S_ReturnFailure) {
  //    /* test constants */
  //    const string kPlaylistName{"my cool playlist"};
  //    const string kErrorMsg{"something went wrong!"};
  //    const string kPlaylistOwner{"foo"};
  //
  //    auto listener = make_shared<PlaylistListenerMock>();
  //
  //    /* set default behavior for CreatePlaylist method */
  //    ON_CALL(*db_mock_, FindPlaylist(kPlaylistName))
  //        .WillByDefault(Return(false));
  //    ON_CALL(*db_mock_, CreatePlaylist(kPlaylistName))
  //        .WillByDefault(Throw(runtime_error(kErrorMsg)));
  //
  //    EXPECT_CALL(*db_mock_, FindPlaylist(kPlaylistName)).Times(1);
  //    EXPECT_CALL(*db_mock_, CreatePlaylist(kPlaylistName))
  //        .Times(1)
  //        .WillOnce(Throw(runtime_error(kErrorMsg)));
  //    EXPECT_CALL(*listener, OnPlaylistCreated()).Times(0);
  //    EXPECT_CALL(*listener, OnPlaylistCreationError(kErrorMsg))
  //        .Times(1);
  //
  //    api_.CreatePlaylist(*listener, kPlaylistName, kPlaylistOwner);
}

/**
 * @brief This tests validates the scenario when the user try to add a music to
 * an existent playlist. When this occurs, the espotifai_api must add the music
 * to the given playlist and return success through the listener.
 */
TEST_F(PlaylistMgrTest, W_UserAddMusicToExistentPlaylist_S_MusicBeAdded) {
  //    /* test constants */
  //    const string kPlaylistName{"my cool playlist"};
  //    const string kPlaylistOwner{"foo"};
  //    const MusicInfo kMusic{
  //        .name = "cool music",
  //        .artist = "cool artist",
  //        .uri = "cool uri",
  //        .duration = 1234
  //    };
  //
  //    auto listener = make_shared<AddMusicPlaylistListenerMock>();
  //
  //    /* set default behavior for FindPlaylist method */
  //    ON_CALL(*db_mock_, FindPlaylist(kPlaylistName))
  //        .WillByDefault(Return(true));
  //    ON_CALL(*db_mock_, FindMusicInPlaylist(kMusic.uri, kPlaylistName))
  //        .WillByDefault(Return(false));
  //
  //    EXPECT_CALL(*db_mock_, FindPlaylist(kPlaylistName)).Times(1);
  //    EXPECT_CALL(*db_mock_, FindMusicInPlaylist(kMusic.uri,
  //    kPlaylistName)).Times(1); EXPECT_CALL(*db_mock_, AddMusic(kMusic,
  //    kPlaylistName)).Times(1); EXPECT_CALL(*listener,
  //    OnMusicAdded()).Times(1); EXPECT_CALL(*listener,
  //    OnMusicAdditionError(_)).Times(0);
  //
  //    api_.AddMusicToPlaylist(*listener, kMusic, kPlaylistName);
}

/**
 * @brief This tests validates the scenario when the user try to add a music to
 * a non existent playlist. When this occurs, the espotifai_api must return the
 * suitable error message through the listener.
 */
TEST_F(PlaylistMgrTest, W_UserAddMusicToNonExistentPlaylist_S_ReturnFailure) {
  //    /* test constants */
  //    const string kPlaylistName{"non existent playlist"};
  //    const string kPlaylistOwner{"foo"};
  //    const string kErrorMsg{"the playlist doesn't exist!"};
  //    const MusicInfo kMusic{
  //        .name = "cool music",
  //        .artist = "cool artist",
  //        .uri = "cool uri",
  //        .duration = 1234
  //    };
  //
  //    auto listener = make_shared<AddMusicPlaylistListenerMock>();
  //
  //    /* set default behavior for FindPlaylist method */
  //    ON_CALL(*db_mock_, FindPlaylist(kPlaylistName))
  //        .WillByDefault(Return(false));
  //
  //    EXPECT_CALL(*db_mock_, FindPlaylist(kPlaylistName)).Times(1);
  //    EXPECT_CALL(*db_mock_, FindMusicInPlaylist(kMusic.uri,
  //    kPlaylistName)).Times(0); EXPECT_CALL(*db_mock_, AddMusic(kMusic,
  //    kPlaylistName)).Times(0); EXPECT_CALL(*listener,
  //    OnMusicAdded()).Times(0); EXPECT_CALL(*listener,
  //    OnMusicAdditionError(kErrorMsg)).Times(1);
  //
  //    api_.AddMusicToPlaylist(*listener, kMusic, kPlaylistName);
}

/**
 * @brief This tests validates the scenario when the user try to add an existent
 * music to a playlist. When this occurs, the espotifai_api must return the
 * suitable error message through the listener.
 */
TEST_F(PlaylistMgrTest,
       W_UserAddMusicWichAlreadyExistInPlaylist_S_ReturnFailure) {
  //    /* test constants */
  //    const string kPlaylistName{"existent playlist"};
  //    const string kPlaylistOwner{"foo"};
  //    const string kErrorMsg{"the music already exist in playlist!"};
  //    const MusicInfo kMusic{
  //        .name = "cool music",
  //        .artist = "cool artist",
  //        .uri = "cool uri",
  //        .duration = 1234
  //    };
  //
  //    auto listener = make_shared<AddMusicPlaylistListenerMock>();
  //
  //    /* set default behavior for FindPlaylist method */
  //    ON_CALL(*db_mock_, FindPlaylist(kPlaylistName))
  //        .WillByDefault(Return(true));
  //    ON_CALL(*db_mock_, FindMusicInPlaylist(kMusic.uri, kPlaylistName))
  //        .WillByDefault(Return(true));
  //
  //    EXPECT_CALL(*db_mock_, FindPlaylist(kPlaylistName)).Times(1);
  //    EXPECT_CALL(*db_mock_, FindMusicInPlaylist(kMusic.uri,
  //    kPlaylistName)).Times(1); EXPECT_CALL(*db_mock_, AddMusic(kMusic,
  //    kPlaylistName)).Times(0); EXPECT_CALL(*listener,
  //    OnMusicAdded()).Times(0); EXPECT_CALL(*listener,
  //    OnMusicAdditionError(kErrorMsg)).Times(1);
  //
  //    api_.AddMusicToPlaylist(*listener, kMusic, kPlaylistName);
}

/**
 * @brief This tests validates the scenario when the user try list the musics of
 * an existent playlist. When this occurs, the API must return the list of
 * musics related to the playlist through the listener.
 */
TEST_F(PlaylistMgrTest,
       W_UserTryToListMusicsOfExistentPlaylist_S_ReturnTheMusicList) {
  //    /* test constants */
  //    const string kPlaylistName{"existent playlist"};
  //    const string kPlaylistOwner{"foo"};
  //    const vector<MusicInfo> kMusicList{
  //        {
  //            .name = "music 1",
  //            .artist = "artist 1",
  //            .uri = "uri 1",
  //            .duration = 1234
  //        },
  //        {
  //            .name = "music 2",
  //            .artist = "artist 2",
  //            .uri = "uri 2",
  //            .duration = 4567
  //        }
  //
  //    };
  //
  //    auto listener = make_shared<PlaylistListenerMock>();
  //
  //    /* set default behavior for methods */
  //    ON_CALL(*db_mock_, FindPlaylist(kPlaylistName))
  //        .WillByDefault(Return(true));
  //    ON_CALL(*db_mock_, GetMusics(kPlaylistName))
  //        .WillByDefault(Return(kMusicList));
  //
  //    EXPECT_CALL(*db_mock_, FindPlaylist(kPlaylistName)).Times(1);
  //    EXPECT_CALL(*db_mock_, GetMusics(kPlaylistName)).Times(1);
  //    EXPECT_CALL(*listener, OnMusicList(kMusicList)).Times(1);
  //    EXPECT_CALL(*listener, OnMusicListError(_)).Times(0);
  //
  //    api_.ListPlaylistMusics(*listener, kPlaylistName);
}

/**
 * @brief This tests validates the scenario when the user try list the musics of
 * a non existent playlist. When this occurs, the API must return the suitable
 * error through the listener.
 */
TEST_F(PlaylistMgrTest,
       W_UserTryToListMusicsOfNonExistentPlaylist_S_ReturnFailure) {
  //    /* test constants */
  //    const string kPlaylistName{"non existent playlist"};
  //    const string kPlaylistOwner{"foo"};
  //    const string kErrorMsg{"the playlist doesn't exist"};
  //
  //    auto listener = make_shared<PlaylistListenerMock>();
  //
  //    /* set default behavior for FindPlaylist method */
  //    ON_CALL(*db_mock_, FindPlaylist(kPlaylistName))
  //        .WillByDefault(Return(false));
  //
  //    EXPECT_CALL(*db_mock_, FindPlaylist(kPlaylistName)).Times(1);
  //    EXPECT_CALL(*db_mock_, GetMusics(kPlaylistName)).Times(0);
  //    EXPECT_CALL(*listener, OnMusicList(_)).Times(0);
  //    EXPECT_CALL(*listener, OnMusicListError(_)).Times(1);
  //
  //    api_.ListPlaylistMusics(*listener, kPlaylistName);
}

/**
 * @brief This tests validates the scenario when the user try list the musics of
 * an empty playlist. When this occurs, the API must return an empty list
 * through the listener.
 */
TEST_F(PlaylistMgrTest,
       W_UserTryToListMusicsOfEmptyPlaylist_S_ReturnEmptyList) {
  //    /* test constants */
  //    const string kPlaylistName{"empty playlist"};
  //    const string kPlaylistOwner{"foo"};
  //    const vector<MusicInfo> kMusicList;
  //
  //    auto listener = make_shared<PlaylistListenerMock>();
  //
  //    /* set default behavior for methods */
  //    ON_CALL(*db_mock_, FindPlaylist(kPlaylistName))
  //        .WillByDefault(Return(true));
  //    ON_CALL(*db_mock_, GetMusics(kPlaylistName))
  //        .WillByDefault(Return(kMusicList));
  //
  //    EXPECT_CALL(*db_mock_, FindPlaylist(kPlaylistName)).Times(1);
  //    EXPECT_CALL(*db_mock_, GetMusics(kPlaylistName)).Times(1);
  //    EXPECT_CALL(*listener, OnMusicList(kMusicList)).Times(1);
  //    EXPECT_CALL(*listener, OnMusicListError(_)).Times(0);
  //
  //    api_.ListPlaylistMusics(*listener, kPlaylistName);
}

/**
 * @brief This tests validates the scenario when the user try to retrieve all
 * registered playlists. When this occurs, the API must return a list of the
 * registered playlists through the listener.
 */
TEST_F(PlaylistMgrTest, W_UserTryToObtainAllPlaylists_S_ReturnPlaylists) {
  //    /* test constants */
  //    const vector<string> kPlaylists{
  //        "playlist 1",
  //        "playlist 2",
  //        "playlist 3",
  //        "playlist 4"
  //    };
  //
  //    auto listener = make_shared<PlaylistListenerMock>();
  //
  //    /* set default behavior for GetPlaylists method */
  //    ON_CALL(*db_mock_, GetPlaylists())
  //        .WillByDefault(Return(kPlaylists));
  //
  //    EXPECT_CALL(*db_mock_, GetPlaylists()).Times(1);
  //    EXPECT_CALL(*listener, OnPlaylistsFound(kPlaylists)).Times(1);
  //    EXPECT_CALL(*listener, OnPlaylistsFoundError(_)).Times(0);
  //
  //    api_.GetPlaylists(*listener);
}

/**
 * @brief This tests validates the scenario when the user try to retrieve all
 * registered playlists, but the database is empty. When this occurs, the API
 * must return an empty list through the listener.
 */
TEST_F(PlaylistMgrTest,
       W_UserTryToObtainAllPlaylistsButDbIsEmpty_S_ReturnEmptyList) {
  //    /* test constants */
  //    const vector<string> kPlaylists;
  //
  //    auto listener = make_shared<PlaylistListenerMock>();
  //
  //    /* set default behavior for GetPlaylists method */
  //    ON_CALL(*db_mock_, GetPlaylists())
  //        .WillByDefault(Return(kPlaylists));
  //
  //    EXPECT_CALL(*db_mock_, GetPlaylists()).Times(1);
  //    EXPECT_CALL(*listener, OnPlaylistsFound(kPlaylists)).Times(1);
  //    EXPECT_CALL(*listener, OnPlaylistsFoundError(_)).Times(0);
  //
  //    api_.GetPlaylists(*listener);
}
