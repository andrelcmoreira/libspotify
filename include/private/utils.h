/**
 * @file
 *
 * @brief Utils methods.
 */
#ifndef UTILS_H_
#define UTILS_H_

#include <string>

namespace spotify_lib {
namespace utils {

/**
 * @brief Generate a base64 string according to a given parameter.
 *
 * @param str Target string.
 *
 * @return Generated base64 string.
 */
std::string GetBase64Code(const std::string &str);

}  // namespace utils
}  // namespace spotify_lib

#endif  // UTILS_H_
