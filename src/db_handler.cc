/**
 * \file
 * \brief Database handler class implementation.
 */
#include "private/db_handler.h"

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/document/element.hpp>
#include <bsoncxx/document/view.hpp>
#include <bsoncxx/json.hpp>

namespace espotifai_api {

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::document::element;
using bsoncxx::document::value;
using bsoncxx::array::view;
using bsoncxx::to_json;

using mongocxx::instance;
using mongocxx::uri;

using std::make_unique;
using std::runtime_error;
using std::string;
using std::to_string;
using std::vector;

DbHandler::DbHandler(const string &db_uri)
    : db_inst_{make_unique<instance>()},
      db_conn_{uri{db_uri}}
{
}

bool DbHandler::FindPlaylist(const string &name) const
{
    auto playlists = db_conn_["espotifai-db"]["playlists"];
    auto found = playlists.find_one(
        document{} << "name" << name << finalize
    );

    return found ? true : false;
}

bool DbHandler::FindMusicInPlaylist(const string &uri, const string &playlist) const
{
    // TODO: improve this method.
    auto playlists = db_conn_["espotifai-db"]["playlists"];
    auto found = playlists.find_one(
        document{} << "name" << playlist << finalize
    );

    auto doc = to_json(*found);

    return (doc.find("\"uri\" : \"" + uri + "\"") != string::npos);
}

void DbHandler::CreatePlaylist(const string &name) const
{
    auto playlists = db_conn_["espotifai-db"]["playlists"];
    auto builder = document{};

    value doc = builder
        << "name" << name
        << "owner" << ""
        << "musics" << open_array
        << close_array
        << finalize;

    if (!playlists.insert_one(doc.view())) {
        throw runtime_error("failed to create the playlist!");
    }
}

void DbHandler::AddMusic(const MusicInfo &music, const std::string &playlist) const
{
    auto playlists = db_conn_["espotifai-db"]["playlists"];

    playlists.update_one(
        make_document(kvp("name", playlist)),
        make_document(kvp("$addToSet",
            document{}
                << "musics" << open_document
                    << "name" << music.name
                    << "artist" << music.artist
                    << "uri" << music.uri
                    << "duration" << to_string(music.duration)
                    << close_document
                    << finalize
            )
        )
    );
}

vector<MusicInfo> DbHandler::GetMusics(const string &playlist) const
{
    vector<MusicInfo> musics;

    auto playlists = db_conn_["espotifai-db"]["playlists"];
    auto found = playlists.find_one(
        document{} << "name" << playlist << finalize
    );

    if (!found) {
        throw runtime_error("the playlist doesn't exist!");
    }

    {
        auto found_view = found->view();

        element musics_ele{found_view["musics"]};
        view music_list{musics_ele.get_array().value};

        for (auto &music : music_list) {
            auto music_doc = music.get_document().value;
            MusicInfo info = {
                .name = music_doc["name"].get_utf8().value.data(),
                .artist = music_doc["artist"].get_utf8().value.data(),
                .uri = music_doc["uri"].get_utf8().value.data(),
                .duration = std::atoi(
                    music_doc["duration"].get_utf8().value.data()
                )
            };

            musics.emplace_back(info);
        }
    }

    return musics;
}

vector<string> DbHandler::GetPlaylists() const
{
    vector<string> list_playlists;
    auto playlists = db_conn_["espotifai-db"]["playlists"];

    for (auto &playlist : playlists.find({})) {
        list_playlists.emplace_back(
            playlist["name"].get_utf8().value.data()
        );
    }

    return list_playlists;
}

} // namespace espotifai_api
