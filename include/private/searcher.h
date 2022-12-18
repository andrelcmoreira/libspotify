/**
 * @file
 *
 * @brief Spotify music searcher class definition.
 */
#ifndef MUSIC_SEARCHER_H_
#define MUSIC_SEARCHER_H_

#include <memory>
#include <string>
#include <vector>

#include "types.h"
#include "private/curl_wrapper.h"

namespace spotify_lib {

/**
 * @class Searcher.
 *
 * @brief This class implements the mechanism for music searching in the
 * Spotify platform.
 */
class Searcher {
   public:
    /**
     * @brief Constructor.
     *
     * @param curl Lib curl handler.
     */
    explicit Searcher(const std::shared_ptr<CurlWrapper> &curl = nullptr);

    /**
     * @brief Search a music in the Spotify platform.
     *
     * @param token Access token.
     * @param name Name of the music.
     *
     * @return The search result.
     */
    std::vector<MusicInfo> Search(
        const std::string &token,
        const std::string &name) const;

   private:
    std::string kBaseUri_; //!< Base uri for music searching.
    std::shared_ptr<CurlWrapper> curl_; //!< Lib curl handler.
};

}  // namespace spotify_lib

#endif  // MUSIC_SEARCHER_H_
