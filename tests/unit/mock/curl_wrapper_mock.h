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
        std::map<std::string, std::string>(const std::string &,
                                           const std::vector<std::string> &,
                                           const std::vector<std::string> &)
    );
};

}  // namespace test
}  // namespace espotifai_api
    //virtual std::map<std::string, std::string> Post(
    //    const std::string &uri,
    //    const std::vector<std::string> &req_headers,
    //    const std::vector<std::string> &req_data) const;
#endif // CURL_WRAPPER_MOCK_H_
