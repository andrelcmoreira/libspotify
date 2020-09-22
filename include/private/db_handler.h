/**
 * \file
 * \brief Database handler class definition.
 */
#ifndef DB_HANDLER_H_
#define DB_HANDLER_H_

#include <string>

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

   private:
    std::string uri_; //!< Database uri.
};

}  // namespace espotifai_api

#endif  // DB_HANDLER_H_
