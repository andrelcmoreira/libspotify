/**
 * @file
 *
 * @brief Spotify main class implementation.
 */
#include "spotify.h"

#include "private/spotify_private.h"

namespace spotify_lib {

using std::exception;
using std::make_shared;
using std::shared_ptr;
using std::string;

Spotify::Spotify(const shared_ptr<Authenticator>& auth,
                 const shared_ptr<Searcher>& searcher,
                 const shared_ptr<PlaylistMgr>& mgr)
    : private_{make_shared<SpotifyPrivate>(auth, searcher, mgr)} {}

void Spotify::Auth(AccessListener& listener, const string& client_id,
               const string& client_secret) const {
  private_->Auth(listener, client_id, client_secret);
}

void Spotify::Search(SearchListener& listener, const string& token,
                 const string& name) const {
  private_->Search(listener, token, name);
}

void Spotify::CreatePlaylist(PlaylistListener& listener, const string& name) const {
  private_->CreatePlaylist(listener, name);
}

void Spotify::AddMusicToPlaylist(AddMusicPlaylistListener& listener,
                             const MusicInfo& music,
                             const string& playlist) const {
  private_->AddMusicToPlaylist(listener, music, playlist);
}

void Spotify::ListPlaylistMusics(PlaylistListener& listener,
                             const string& playlist_name) const {
  private_->ListPlaylistMusics(listener, playlist_name);
}

void Spotify::GetPlaylists(PlaylistListener& listener) const {
  private_->GetPlaylists(listener);
}

}  // namespace spotify_lib
