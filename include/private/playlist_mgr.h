/**
 * \file
 * \brief Playlist manager class definition.
 */
#ifndef PLAYLIST_MGR_H_
#define PLAYLIST_MGR_H_

#include <memory>
#include <string>

#include "db_handler.h"
#include "types.h"

namespace espotifai_api {

/**
 * \class PlaylistMgr.
 *
 * \brief This class implements the management of user playlists.
 */
class PlaylistMgr {
   public:
    /**
     * \brief Constructor.
     */
    explicit PlaylistMgr(const std::shared_ptr<DbHandler> &db_handler = nullptr);

    /**
     * \brief Create a new playlist.
     * \param name Name of playlist.
     * \param owner Owner of playlist.
     */
    void Create(const std::string &name, const std::string &owner) const;

    /**
     * \brief Add a music into an existent playlist.
     * \param music Informations of the music.
     * \param playlist Name of the playlist.
     */
    void AddMusic(const MusicInfo &music, const std::string &playlist) const;

    /**
     * \brief List the musics of a playlist.
     * \param playlist Name of the playlist.
     */
    std::vector<MusicInfo> ListMusics(const std::string &playlist) const;

   private:
    std::shared_ptr<DbHandler> db_handler_; //!< Database handler.
};

}  // namespace espotifai_api

#endif  // PLAYLIST_MGR_H_
