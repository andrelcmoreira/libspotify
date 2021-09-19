/**
 * @file
 *
 * @brief Spotify music searcher class implementation.
 */
#include "private/searcher.h"

#include <algorithm>
#include <stdexcept>
#include <vector>

namespace espotifai_api {

using std::make_shared;
using std::replace;
using std::shared_ptr;
using std::string;
using std::vector;

Searcher::Searcher(const shared_ptr<CurlWrapper>& curl)
    : kBaseUri_{"https://api.spotify.com/v1/search?q="},
      curl_{curl ? curl : make_shared<CurlWrapper>()} {}

vector<MusicInfo> Searcher::Search(const string& token,
                                   const string& name) const {
  vector<MusicInfo> ret;
  string uri{kBaseUri_ + name + "&type=track&limit=10"};
  vector<string> req_headers{"Authorization: Bearer " + token};

  replace(uri.begin(), uri.end(), ' ', '+');

  auto reply = curl_->Get(uri, req_headers);

  for (auto& item : reply["tracks"]["items"]) {
    MusicInfo info = {.name = item["name"].asString(),
                      .artist = item["album"]["artists"][0]["name"].asString(),
                      .uri = item["uri"].asString(),
                      .duration = item["duration_ms"].asInt()};

    ret.emplace_back(info);
  }

  return ret;
}

}  // namespace espotifai_api
