#ifndef DB_HANDLER_MOCK_H_
#define DB_HANDLER_MOCK_H_

#include <gmock/gmock.h>

#include "private/db_handler.h"

namespace espotifai_api {
namespace test {

class DbHandlerMock : public DbHandler {
   public:
    DbHandlerMock() : DbHandler("mongodb://db:27017/espotifai-db")
    {
    }

    MOCK_CONST_METHOD1(FindPlaylist, bool(const std::string &));
    MOCK_CONST_METHOD1(CreatePlaylist, void(const std::string &));
};

}  // namespace test
}  // namespace espotifai_api

#endif // DB_HANDLER_MOCK_H_
