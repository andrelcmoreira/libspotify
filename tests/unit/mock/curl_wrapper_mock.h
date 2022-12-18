#ifndef CURL_WRAPPER_MOCK_H_
#define CURL_WRAPPER_MOCK_H_

#include <gmock/gmock.h>

#include "private/curl_wrapper.h"

namespace spotify_lib {
namespace test {

class CurlWrapperMock : public CurlWrapper {
 public:
  MOCK_CONST_METHOD3(Post, Json::Value(const std::string &,
                                       const std::vector<std::string> &,
                                       const std::vector<std::string> &));

  MOCK_CONST_METHOD2(Get, Json::Value(const std::string &,
                                      const std::vector<std::string> &));
};

}  // namespace test
}  // namespace spotify_lib

#endif  // CURL_WRAPPER_MOCK_H_
