#ifndef ACCESS_LISTENER_MOCK_H_
#define ACCESS_LISTENER_MOCK_H_

#include <gmock/gmock.h>

#include "access_listener.h"

namespace espotifai_api {
namespace test {

class AccessListenerMock : public AccessListener {
   public:
    MOCK_CONST_METHOD1(OnAccessGuaranteed, void(const std::string &));
    MOCK_CONST_METHOD1(OnAccessDeny, void(const std::string &));
};

}  // namespace test
}  // namespace espotifai_api

#endif // ACCESS_LISTENER_MOCK_H_
