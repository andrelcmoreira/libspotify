#include <iostream>
#include <string>
#include <vector>

#include "spotify.h"
#include "search_listener.h"
#include "types.h"

using spotify_lib::Spotify;
using spotify_lib::MusicInfo;
using spotify_lib::SearchListener;

class EventHandler : public SearchListener {
 public:
  void OnPatternFound(const std::vector<MusicInfo>& musics) const override {
    std::cout << musics.size() << " results found" << std::endl;

    for (auto& music : musics) {
      std::cout << "artist: " << music.artist << ", music: " << music.name
                << ", uri: " << music.uri << ", duration: " << music.duration
                << " ms" << std::endl;
    }
  }

  void OnSearchError(const std::string& msg) const override {
    std::cerr << msg << std::endl;
  }
};

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << "usage: " << argv[0] << " <token> <search_string>"
              << std::endl;
    std::exit(1);
  }

  const std::string kToken{argv[1]};
  const std::string kSearchString{argv[2]};

  Spotify lib;
  EventHandler ev;

  lib.Search(ev, kToken, kSearchString);

  std::exit(0);
}
