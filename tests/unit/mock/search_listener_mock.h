#ifndef SEARCH_LISTENER_MOCK_H_
#define SEARCH_LISTENER_MOCK_H_

#include <gmock/gmock.h>

#include "search_listener.h"

namespace spotify_lib {
namespace test {

class SearchListenerMock : public SearchListener {
 public:
  MOCK_CONST_METHOD1(OnPatternFound, void(const std::vector<MusicInfo> &));
  MOCK_CONST_METHOD1(OnSearchError, void(const std::string &));
};

}  // namespace test
}  // namespace spotify_lib

#endif  // SEARCH_LISTENER_MOCK_H_
