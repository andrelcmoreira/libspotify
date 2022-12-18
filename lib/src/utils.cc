/**
 * @file
 *
 * @brief Utils class implementation.
 */
#include "private/utils.h"

#include <boost/beast/core/detail/base64.hpp>
#include <vector>

namespace spotify_lib {
namespace utils {

using boost::beast::detail::base64::encode;
using boost::beast::detail::base64::encoded_size;
using std::memset;
using std::size_t;
using std::string;
using std::strlen;

std::string GetBase64Code(const string& str) {
  const char* auth = str.c_str();
  size_t max_size = encoded_size(str.size()) + 1;
  char result[max_size];

  memset(result, 0, max_size);

  encode(result, auth, strlen(auth));

  return string{result};
}

}  // namespace utils
}  // namespace spotify_lib
