/**
 * @file
 *
 * @brief Api private class implementation.
 */
#include "private/api_private.h"

#include "private/authenticator.h"
#include "private/playlist_mgr.h"
#include "private/searcher.h"

namespace espotifai_api {

using std::exception;
using std::make_shared;
using std::shared_ptr;
using std::string;

ApiPrivate::ApiPrivate(const shared_ptr<Authenticator>& auth,
                       const shared_ptr<Searcher>& searcher,
                       const shared_ptr<PlaylistMgr>& mgr)
    : auth_{auth ? auth : make_shared<Authenticator>()},
      searcher_{searcher ? searcher : make_shared<Searcher>()},
      playlist_mgr_{mgr ? mgr : make_shared<PlaylistMgr>()} {}

void ApiPrivate::Auth(AccessListener& listener, const string& client_id,
                      const string& client_secret) const {
  try {
    auto token = auth_->AuthUser(client_id, client_secret);

    listener.OnAccessGuaranteed(token);
  } catch (const exception& e) {
    listener.OnAccessDenied(e.what());
  }
}

void ApiPrivate::Search(SearchListener& listener, const string& token,
                        const string& name) const {
  try {
    auto musics = searcher_->Search(token, name);

    listener.OnPatternFound(musics);
  } catch (const exception& e) {
    listener.OnSearchError(e.what());
  }
}

void ApiPrivate::CreatePlaylist(PlaylistListener& listener,
                                const string& name) const {
  try {
    playlist_mgr_->Create(name);

    listener.OnPlaylistCreated();
  } catch (const exception& e) {
    listener.OnPlaylistCreationError(e.what());
  }
}

void ApiPrivate::AddMusicToPlaylist(AddMusicPlaylistListener& listener,
                                    const MusicInfo& music,
                                    const string& playlist) const {
  try {
    playlist_mgr_->AddMusic(music, playlist);

    listener.OnMusicAdded();
  } catch (const exception& e) {
    listener.OnMusicAdditionError(e.what());
  }
}

void ApiPrivate::ListPlaylistMusics(PlaylistListener& listener,
                                    const string& playlist_name) const {
  try {
    auto musics = playlist_mgr_->ListMusics(playlist_name);

    listener.OnMusicList(musics);
  } catch (const exception& e) {
    listener.OnMusicListError(e.what());
  }
}

void ApiPrivate::GetPlaylists(PlaylistListener& listener) const {
  try {
    auto playlists = playlist_mgr_->GetPlaylists();

    listener.OnPlaylistsFound(playlists);
  } catch (const exception& e) {
    listener.OnPlaylistsFoundError(e.what());
  }
}

}  // namespace espotifai_api
