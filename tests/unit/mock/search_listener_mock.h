#ifndef SEARCH_LISTENER_MOCK_H_
#define SEARCH_LISTENER_MOCK_H_

#include <gmock/gmock.h>

#include "search_listener.h"

namespace espotifai_api {
namespace test {

class SearchListenerMock : public SearchListener {
 public:
  MOCK_CONST_METHOD1(OnPatternFound, void(const std::vector<MusicInfo> &));
  MOCK_CONST_METHOD1(OnSearchError, void(const std::string &));
};

}  // namespace test
}  // namespace espotifai_api

#endif  // SEARCH_LISTENER_MOCK_H_
