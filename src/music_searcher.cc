/**
 * \file
 * \brief Spotify music searcher class implementation.
 */
#include "private/music_searcher.h"

#include <algorithm>
#include <stdexcept>
#include <vector>

namespace espotifai_api {

MusicSearcher::MusicSearcher(const std::shared_ptr<CurlWrapper> &curl)
    : kBaseUri_{"https://api.spotify.com/v1/search?q="},
      curl_{curl ? curl : std::make_shared<CurlWrapper>()}
{
}

std::vector<MusicInfo> MusicSearcher::Search(const std::string &token,
    const std::string &name) const
{
    std::vector<MusicInfo> ret;
    std::string uri{kBaseUri_ + name + "&type=track&limit=3"};
    std::vector<std::string> req_headers{
        "Authorization: Bearer " + token
    };

    std::replace(uri.begin(), uri.end(), ' ', '+');

    auto reply = curl_->Get(uri, req_headers);

    for (auto &item : reply["tracks"]["items"]) {
        MusicInfo info = {
            .name = item["name"].asString(),
            .artist = item["album"]["artists"][0]["name"].asString(),
            .uri = item["uri"].asString(),
            .duration = item["duration_ms"].asInt()
        };

        ret.emplace_back(info);
    }

    return ret;
}

}  // espotifai_api
