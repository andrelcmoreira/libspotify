/**
 * \file
 * \brief Api main class implementation.
 */
#include "api.h"

#include "access_listener.h"
#include "add_music_playlist_listener.h"
#include "playlist_listener.h"
#include "search_music_listener.h"

namespace espotifai_api {

using std::exception;
using std::make_shared;
using std::shared_ptr;
using std::string;

Api::Api(const shared_ptr<SpotifyAuth>& auth,
         const shared_ptr<MusicSearcher>& searcher,
         const shared_ptr<PlaylistMgr>& mgr)
    : sptf_auth_{auth ? auth : make_shared<SpotifyAuth>()},
      sptf_searcher_{searcher ? searcher : make_shared<MusicSearcher>()},
      playlist_mgr_{mgr ? mgr : make_shared<PlaylistMgr>()} {}

void Api::RequestAccess(AccessListener& listener, const string& client_id,
                        const string& client_secret) const {
  // TODO: make it async?

  try {
    auto token = sptf_auth_->AuthUser(client_id, client_secret);

    listener.OnAccessGuaranteed(token);
  } catch (const exception& e) {
    listener.OnAccessDenied(e.what());
  }
}

void Api::SearchMusic(SearchMusicListener& listener, const string& token,
                      const string& name) const {
  // TODO: make it async?

  try {
    auto musics = sptf_searcher_->Search(token, name);

    listener.OnMusicFound(musics);
  } catch (const exception& e) {
    listener.OnMusicSearchError(e.what());
  }
}

void Api::CreatePlaylist(PlaylistListener& listener, const string& name,
                         const string& owner) const {
  // TODO: make it async?

  try {
    playlist_mgr_->Create(name, owner);

    listener.OnPlaylistCreated();
  } catch (const exception& e) {
    listener.OnPlaylistCreationError(e.what());
  }
}

void Api::AddMusicToPlaylist(AddMusicPlaylistListener& listener,
                             const MusicInfo& music,
                             const string& playlist) const {
  // TODO: make it async?

  try {
    playlist_mgr_->AddMusic(music, playlist);

    listener.OnMusicAdded();
  } catch (const exception& e) {
    listener.OnMusicAdditionError(e.what());
  }
}

void Api::ListPlaylistMusics(PlaylistListener& listener,
                             const string& playlist_name) const {
  // TODO: make it async?

  try {
    auto musics = playlist_mgr_->ListMusics(playlist_name);

    listener.OnMusicList(musics);
  } catch (const exception& e) {
    listener.OnMusicListError(e.what());
  }
}

void Api::GetPlaylists(PlaylistListener& listener) const {
  // TODO: make it async?

  try {
    auto playlists = playlist_mgr_->GetPlaylists();

    listener.OnPlaylistsFound(playlists);
  } catch (const exception& e) {
    listener.OnPlaylistsFoundError(e.what());
  }
}

}  // namespace espotifai_api
