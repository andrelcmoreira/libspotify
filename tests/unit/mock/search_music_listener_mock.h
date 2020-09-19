#ifndef SEARCH_MUSIC_LISTENER_MOCK_H_
#define SEARCH_MUSIC_LISTENER_MOCK_H_

#include <gmock/gmock.h>

#include "search_music_listener.h"

namespace espotifai_api {
namespace test {

class SearchMusicListenerMock : public SearchMusicListener {
   public:
    MOCK_CONST_METHOD1(OnMusicFound, void(const std::vector<MusicInfo> &));
    MOCK_CONST_METHOD1(OnMusicSearchError, void(const std::string &));
};

}  // namespace test
}  // namespace espotifai_api

#endif // SEARCH_MUSIC_LISTENER_MOCK_H_
