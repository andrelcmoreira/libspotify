#ifndef PLAYLIST_MGR_MOCK_H_
#define PLAYLIST_MGR_MOCK_H_

#include <gmock/gmock.h>

#include "private/playlist_mgr.h"

namespace spotify_lib {
namespace test {

class PlaylistMgrMock : public PlaylistMgr {};

}  // namespace test
}  // namespace spotify_lib

#endif  // PLAYLIST_MGR_MOCK_H_
