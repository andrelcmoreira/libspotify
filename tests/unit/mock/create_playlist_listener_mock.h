#ifndef CREATE_PLAYLIST_LISTENER_MOCK_H_
#define CREATE_PLAYLIST_LISTENER_MOCK_H_

#include <gmock/gmock.h>

#include "create_playlist_listener.h"

namespace espotifai_api {
namespace test {

class CreatePlaylistListenerMock : public CreatePlaylistListener {
   public:
    MOCK_CONST_METHOD0(OnPlaylistCreated, void());
    MOCK_CONST_METHOD1(OnPlaylistCreationError, void(const std::string &));
};

}  // namespace test
}  // namespace espotifai_api

#endif // CREATE_PLAYLIST_LISTENER_MOCK_H_
