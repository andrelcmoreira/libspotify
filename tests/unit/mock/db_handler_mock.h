#ifndef DB_HANDLER_MOCK_H_
#define DB_HANDLER_MOCK_H_

#include <gmock/gmock.h>

#include "private/db_handler.h"

namespace espotifai_api {
namespace test {

class DbHandlerMock : public DbHandler {
   public:
    MOCK_CONST_METHOD1(FindPlaylist, bool(const std::string &));
    MOCK_CONST_METHOD1(CreatePlaylist, void(const std::string &));
    MOCK_CONST_METHOD2(FindMusicInPlaylist, bool(const std::string &, const std::string &));
    MOCK_CONST_METHOD2(AddMusic, void(const MusicInfo &, const std::string &));
    MOCK_CONST_METHOD1(GetMusics, std::vector<MusicInfo>(const std::string &));
};

}  // namespace test
}  // namespace espotifai_api

#endif // DB_HANDLER_MOCK_H_
