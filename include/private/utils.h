/**
 * \file
 * \brief Utils methods.
 */
#ifndef UTILS_H_
#define UTILS_H_

#include <string>

namespace espotifai_api {
namespace utils {

/**
 * \brief Generate a base64 string according to a given parameter.
 * \param str Target string.
 * \return Generated base64 string.
 */
std::string GetBase64Code(const std::string &str);

} // utils
} // namespace espotifai_api

#endif  // UTILS_H_
