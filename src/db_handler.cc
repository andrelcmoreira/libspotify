/**
 * \file
 * \brief Database handler class implementation.
 */
#include "private/db_handler.h"

#include <bsoncxx/builder/stream/document.hpp>

namespace espotifai_api {

DbHandler::DbHandler(const std::string &uri)
    : db_inst_{std::make_unique<mongocxx::instance>()},
      db_conn_{mongocxx::uri{uri}}
{
}

bool DbHandler::FindPlaylist(const std::string &name) const
{
    auto playlists = db_conn_["espotifai-db"]["playlists"];
    auto found = playlists.find_one(
        bsoncxx::builder::stream::document{} <<
        "name" <<
        name <<
        bsoncxx::builder::stream::finalize
    );

    return found ? true : false;
}

void DbHandler::CreatePlaylist(const std::string &name) const
{
    auto playlists = db_conn_["espotifai-db"]["playlists"];
    auto builder = bsoncxx::builder::stream::document{};

    bsoncxx::document::value doc = builder
        << "name" << name
        << "owner" << ""
        << "musics" << bsoncxx::builder::stream::open_array
        << bsoncxx::builder::stream::close_array
        << bsoncxx::builder::stream::finalize;

    if (!playlists.insert_one(doc.view())) {
        throw std::runtime_error(
            "failed to create the playlist!"
        );
    }
}

} // namespace espotifai_api
