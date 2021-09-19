/**
 * @file
 *
 * @brief Searcher listener class definition.
 */
#ifndef SEARCH_LISTENER_H_
#define SEARCH_LISTENER_H_

#include <string>
#include <vector>

namespace espotifai_api {

struct MusicInfo;

/**
 * @interface SearchListener.
 *
 * @brief This class defines a interface for searching events.
 */
class SearchListener {
 public:
  /**
   * @brief Report the musics found.
   *
   * @param result List of matching results.
   */
  virtual void OnPatternFound(const std::vector<MusicInfo>& result) const = 0;

  /**
   * @brief Indicates a error during the operation.
   *
   * @param msg The suitable error message.
   */
  virtual void OnSearchError(const std::string& msg) const = 0;
};

}  // namespace espotifai_api

#endif  // SEARCH_LISTENER_H_
