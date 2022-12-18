#ifndef ACCESS_LISTENER_MOCK_H_
#define ACCESS_LISTENER_MOCK_H_

#include <gmock/gmock.h>

#include "access_listener.h"

namespace spotify_lib {
namespace test {

class AccessListenerMock : public AccessListener {
 public:
  MOCK_CONST_METHOD1(OnAccessGuaranteed, void(const std::string &));
  MOCK_CONST_METHOD1(OnAccessDenied, void(const std::string &));
};

}  // namespace test
}  // namespace spotify_lib

#endif  // ACCESS_LISTENER_MOCK_H_
