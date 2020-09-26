/**
 * \file
 * \brief Database handler class definition.
 */
#ifndef DB_HANDLER_H_
#define DB_HANDLER_H_

#include <memory>
#include <string>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include "types.h"

namespace espotifai_api {

/**
 * \class DbHandler.
 *
 * \brief This class defines a database handler.
 */
class DbHandler {
   public:
    /**
     * \brief Constructor.
     */
    DbHandler() = default;

    /**
     * \brief Constructor.
     * \param uri Database URI.
     */
    explicit DbHandler(const std::string &uri);

    /**
     * \brief Find a playlist in the database.
     * \param name Playlist name.
     * \return True if the playlist already exist; otherwise false.
     */
    virtual bool FindPlaylist(const std::string &name) const;

    /**
     * \brief Create a new playlist in the database.
     * \param name Playlist name.
     */
    virtual void CreatePlaylist(const std::string &name) const;

    /**
     * \brief Add a music into an existent playlist.
     * \param music Informations of the music.
     * \param playlist Name of the playlist.
     */
    virtual void AddMusic(const MusicInfo &music, const std::string &playlist) const;

    /**
     * \brief Look for a music in the playlist.
     * \param uri URI of the music.
     * \param playlist Name of the playlist.
     * \return True if the music is already present on playlist; otherwise False.
     */
    virtual bool FindMusicInPlaylist(const std::string &uri, const std::string &playlist) const;

    /**
     * \brief Get the musics of a given playlist.
     * \param playlist Name of the playlist.
     */
    virtual std::vector<MusicInfo> GetMusics(const std::string &playlist) const;

   private:
    std::unique_ptr<mongocxx::instance> db_inst_;
    mongocxx::client db_conn_;
};

}  // namespace espotifai_api

#endif  // DB_HANDLER_H_
