/**
 * \file
 * \brief Playlist manager class implementation.
 */
#include "private/playlist_mgr.h"

#include <stdexcept>

namespace espotifai_api {

PlaylistMgr::PlaylistMgr(const std::shared_ptr<DbHandler> &db)
    : db_handler_{db ? db : std::make_shared<DbHandler>("mongodb://localhost:27017/espotifai-db")}
{
}

void PlaylistMgr::Create(const std::string &name, const std::string &owner) const
{
    if (db_handler_->FindPlaylist(name)) {
        throw std::runtime_error(
            "the playlist already exist!"
        );
    }

    db_handler_->CreatePlaylist(name);
}

}  // namespace espotifai_api
