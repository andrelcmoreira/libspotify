/**
 * \file
 * \brief Api main class implementation.
 */
#include "api.h"

#include "access_listener.h"
#include "search_music_listener.h"
#include "private/spotify_auth.h"

namespace espotifai_api {

Api::Api(const std::shared_ptr<SpotifyAuth> &auth,
         const std::shared_ptr<MusicSearcher> &searcher)
    : sptf_auth_{auth ? auth : std::make_shared<SpotifyAuth>()},
      sptf_searcher_{searcher ? searcher : std::make_shared<MusicSearcher>()}
{
}

void Api::RequestAccess(AccessListener &listener, const std::string &client_id,
    const std::string &client_secret) const
{
    // TODO: make it async?

    try {
        auto token = sptf_auth_->AuthUser(client_id, client_secret);

        listener.OnAccessGuaranteed(token);
    } catch(const std::exception &e) {
        listener.OnAccessDenied(e.what());
    }
}

void Api::SearchMusic(SearchMusicListener &listener, const std::string &token,
    const std::string &name) const
{
    // TODO: make it async?

    try {
        auto musics = sptf_searcher_->Search(token, name);

        listener.OnMusicFound(musics);
    } catch(const std::exception &e) {
        listener.OnMusicSearchError(e.what());
    }
}

}  // espotifai_api
