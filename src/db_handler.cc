/**
 * \file
 * \brief Database handler class implementation.
 */
#include "private/db_handler.h"

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/json.hpp>

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

bool DbHandler::FindMusicInPlaylist(const std::string &uri, const std::string &playlist) const
{
    // TODO: improve this method.
    auto playlists = db_conn_["espotifai-db"]["playlists"];
    auto found = playlists.find_one(
        bsoncxx::builder::stream::document{} <<
        "name" << playlist <<
        bsoncxx::builder::stream::finalize
    );

    auto doc = bsoncxx::to_json(*found);

    return (doc.find("\"uri\" : \"" + uri + "\"") != std::string::npos);
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

void DbHandler::AddMusic(const MusicInfo &music, const std::string &playlist) const
{
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::open_document;
    using bsoncxx::builder::stream::close_document;
    using bsoncxx::builder::stream::finalize;

    auto playlists = db_conn_["espotifai-db"]["playlists"];

    playlists.update_one(
        make_document(kvp("name", playlist)),
        make_document(kvp("$addToSet",
            document{}
                << "musics" << open_document
                    << "name" << music.name
                    << "artist" << music.artist
                    << "uri" << music.uri
                    << "duration" << std::to_string(music.duration)
                    << close_document
                    << finalize
            )
        )
    );
}

} // namespace espotifai_api