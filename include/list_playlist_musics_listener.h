/**
 * \file
 * \brief List playlist musics listener class definition.
 */
#ifndef LIST_PLAYLIST_MUSICS_LISTENER_H_
#define LIST_PLAYLIST_MUSICS_LISTENER_H_

#include <string>
#include <vector>

#include "types.h"

namespace espotifai_api {

/**
 * \interface ListPlaylistMusicsListener.
 *
 * \brief This class defines a interface for music listing of playlists.
 */
class ListPlaylistMusicsListener {
   public:
    /**
     * \brief Report the list of musics associated to the playlist.
     * \param musics List of musics.
     */
    virtual void OnMusicList(const std::vector<MusicInfo> &musics) const = 0;

    /**
     * \brief Indicates a failure during the operation.
     * \param msg The suitable error message.
     */
    virtual void OnMusicListError(const std::string &msg) const = 0;
};

}  // namespace espotifai_api

#endif  // LIST_PLAYLIST_MUSICS_LISTENER_H_
