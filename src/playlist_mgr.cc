/**
 * \file
 * \brief Playlist manager class implementation.
 */
#include "private/playlist_mgr.h"

#include <stdexcept>

namespace espotifai_api {

using std::make_shared;
using std::runtime_error;
using std::shared_ptr;
using std::string;
using std::vector;

PlaylistMgr::PlaylistMgr(const shared_ptr<DbHandler> &db)
    : db_handler_{db ? db : std::make_shared<DbHandler>("mongodb://localhost:27017/espotifai-db")}
{
}

void PlaylistMgr::Create(const string &name, const string &owner) const
{
    if (db_handler_->FindPlaylist(name)) {
        throw runtime_error("the playlist already exist!");
    }

    db_handler_->CreatePlaylist(name);
}

void PlaylistMgr::AddMusic(const MusicInfo &music, const string &playlist) const
{
    if (!db_handler_->FindPlaylist(playlist)) {
        throw runtime_error("the playlist doesn't exist!");
    }

    if (db_handler_->FindMusicInPlaylist(music.uri, playlist)) {
        throw runtime_error("the music already exist in playlist!");
    }

    db_handler_->AddMusic(music, playlist);
}

vector<MusicInfo> PlaylistMgr::ListMusics(const string &playlist) const
{
    if (!db_handler_->FindPlaylist(playlist)) {
        throw runtime_error("the playlist doesn't exist!");
    }

    return db_handler_->GetMusics(playlist);
}

vector<string> PlaylistMgr::GetPlaylists() const
{
    return db_handler_->GetPlaylists();
}

}  // namespace espotifai_api
