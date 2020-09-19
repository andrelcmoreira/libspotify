/**
 * \file
 * \brief Music searcher listener class definition.
 */
#ifndef SEARCH_MUSIC_LISTENER_H_
#define SEARCH_MUSIC_LISTENER_H_

#include <string>
#include <vector>

namespace espotifai_api {

struct MusicInfo;

/**
 * \interface SearchMusicListener.
 *
 * \brief This class defines a interface for music searching events.
 */
class SearchMusicListener {
   public:
    /**
     * \brief Report the musics found.
     * \param musics List of found musics.
     */
    virtual void OnMusicFound(const std::vector<MusicInfo> &musics) const = 0;

    /**
     * \brief Indicates a error during the operation.
     * \param msg The suitable error message.
     */
    virtual void OnMusicSearchError(const std::string &msg) const = 0;
};

}  // espotifai_api

#endif  // SEARCH_MUSIC_LISTENER_H_
