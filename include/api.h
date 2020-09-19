/**
 * \file
 * \brief Api main class definition.
 */
#ifndef API_H_
#define API_H_

#include <memory>
#include <string>

#include "private/music_searcher.h"
#include "private/spotify_auth.h"

namespace espotifai_api {

class AccessListener;
class SearchMusicListener;

/**
 * \class Api.
 *
 * \brief This class implements the main functionalities of espotifai API.
 */
class Api {
   public:
    /**
     * \brief Constructor.
     * \param auth Spotify authenticator instance.
     */
    Api(
        const std::shared_ptr<SpotifyAuth> &auth = nullptr,
        const std::shared_ptr<MusicSearcher> &searcher = nullptr
    );

    /**
     * \brief Authenticate a user using the spotify API.
     * \param listener Event listener.
     * \param client_id Client's ID.
     * \param client_secret Client's secret.
     */
    void RequestAccess(
        AccessListener &listener,
        const std::string &client_id,
        const std::string &client_secret
    ) const;

    /**
     * \brief Search for a music in the spotify platform.
     * \param listener Event listener.
     * \param token Access token.
     * \param name Name of the music.
     */
    void SearchMusic(
        SearchMusicListener &listener,
        const std::string &token,
        const std::string &name
    ) const;

   private:
    std::shared_ptr<SpotifyAuth> sptf_auth_; //!< Spotify authenticator.
    std::shared_ptr<MusicSearcher> sptf_searcher_; //!< Spotify music searcher.
};

}  // espotifai_api

#endif  // API_H_
