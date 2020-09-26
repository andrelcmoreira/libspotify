#ifndef LIST_PLAYLIST_MUSICS_LISTENER_MOCK_H_
#define LIST_PLAYLIST_MUSICS_LISTENER_MOCK_H_

#include <gmock/gmock.h>

#include "list_playlist_musics_listener.h"
#include "types.h"

namespace espotifai_api {
namespace test {

class ListPlaylistMusicsListenerMock : public ListPlaylistMusicsListener {
   public:
    MOCK_CONST_METHOD1(OnMusicList, void(const std::vector<MusicInfo> &));
    MOCK_CONST_METHOD1(OnMusicListError, void(const std::string &));
};

}  // namespace test
}  // namespace espotifai_api

#endif // LIST_PLAYLIST_MUSICS_LISTENER_MOCK_H_
