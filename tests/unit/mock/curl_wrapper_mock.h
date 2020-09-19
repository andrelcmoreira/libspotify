#ifndef CURL_WRAPPER_MOCK_H_
#define CURL_WRAPPER_MOCK_H_

#include <gmock/gmock.h>

#include "private/curl_wrapper.h"

namespace espotifai_api {
namespace test {

class CurlWrapperMock : public espotifai_api::CurlWrapper {
   public:
    MOCK_CONST_METHOD3(
        Post,
        Json::Value(
            const std::string &,
            const std::vector<std::string> &,
            const std::vector<std::string> &
        )
    );

    MOCK_CONST_METHOD2(
        Get,
        Json::Value(
            const std::string &,
            const std::vector<std::string> &
        )
    );
};

}  // namespace test
}  // namespace espotifai_api

#endif // CURL_WRAPPER_MOCK_H_
