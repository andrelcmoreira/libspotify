/**
 * \file
 * \brief Access listener class definition.
 */
#ifndef ACCESS_LISTENER_H_
#define ACCESS_LISTENER_H_

#include <string>

namespace espotifai_api {

/**
 * \interface AccessListener.
 *
 * \brief This class defines a interface for login events.
 */
class AccessListener {
 public:
  /**
   * \brief Indicates that the login attempt was a success.
   * \param token User's auth token.
   */
  virtual void OnAccessGuaranteed(const std::string& token) const = 0;

  /**
   * \brief Indicates that the login attempt has failed.
   * \param msg The suitable error message.
   */
  virtual void OnAccessDenied(const std::string& msg) const = 0;
};

}  // namespace espotifai_api

#endif  // ACCESS_LISTENER_H_
