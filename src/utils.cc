/**
 * \file
 * \brief Utils class implementation.
 */
#include "private/utils.h"

#include <boost/beast/core/detail/base64.hpp>

namespace espotifai_api {
namespace utils {

namespace base64 = ::boost::beast::detail::base64;

std::string GetBase64Code(const std::string &str)
{
    const char *auth = str.c_str();
    std::size_t max_size = base64::encoded_size(str.size()) + 1;
    char result[max_size];

    std::memset(result, 0, max_size);

    base64::encode(result, auth, std::strlen(auth));

    return std::string{result};
}

}  // namespace utils
}  // namespace espotifai_api
