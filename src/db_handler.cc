/**
 * \file
 * \brief Database handler class implementation.
 */
#include "private/db_handler.h"

#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

namespace espotifai_api {

DbHandler::DbHandler(const std::string &uri)
    : uri_{uri}
{
}

bool DbHandler::FindPlaylist(const std::string &name) const
{
    mongocxx::instance db_inst;
    mongocxx::client db_conn{mongocxx::uri{uri_}};

    auto playlists = db_conn["espotifai-db"]["playlists"];
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
    mongocxx::instance db_inst;
    mongocxx::client db_conn{mongocxx::uri{uri_}};

    auto playlists = db_conn["espotifai-db"]["playlists"];
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
