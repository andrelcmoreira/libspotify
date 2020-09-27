#ifndef PLAYLIST_LISTENER_MOCK_H_
#define PLAYLIST_LISTENER_MOCK_H_

#include <gmock/gmock.h>

#include "playlist_listener.h"

namespace espotifai_api {
namespace test {

class PlaylistListenerMock : public PlaylistListener {
   public:
    MOCK_CONST_METHOD0(OnPlaylistCreated, void());
    MOCK_CONST_METHOD1(OnPlaylistCreationError, void(const std::string &));
    MOCK_CONST_METHOD1(OnMusicList, void(const std::vector<MusicInfo> &));
    MOCK_CONST_METHOD1(OnMusicListError, void(const std::string &));
    MOCK_CONST_METHOD1(OnPlaylistsFound, void(const std::vector<std::string> &playlists));
    MOCK_CONST_METHOD1(OnPlaylistsFoundError, void(const std::string &));
};

}  // namespace test
}  // namespace espotifai_api

#endif // PLAYLIST_LISTENER_MOCK_H_
