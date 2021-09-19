#ifndef ADD_MUSIC_PLAYLIST_LISTENER_MOCK_H_
#define ADD_MUSIC_PLAYLIST_LISTENER_MOCK_H_

#include <gmock/gmock.h>

#include "add_music_playlist_listener.h"

namespace espotifai_api {
namespace test {

class AddMusicPlaylistListenerMock : public AddMusicPlaylistListener {
 public:
  MOCK_CONST_METHOD0(OnMusicAdded, void());
  MOCK_CONST_METHOD1(OnMusicAdditionError, void(const std::string &));
};

}  // namespace test
}  // namespace espotifai_api

#endif  // ADD_MUSIC_PLAYLIST_LISTENER_MOCK_H_
