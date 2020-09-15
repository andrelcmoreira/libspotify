/**
 * \file
 * \brief Curl wrapper class definition.
 */
#ifndef CURL_WRAPPER_H_
#define CURL_WRAPPER_H_

#include <map>
#include <vector>

#include <curl/curl.h>

namespace espotifai_api {

/**
 * \class CurlWrapper.
 *
 * \brief This class wraps some of functionalities of libcurl.
 */
class CurlWrapper {
   public:
    /**
     * \brief Constructor.
     */
    CurlWrapper();

    /**
     * \brief Destructor.
     */
    ~CurlWrapper();

    /**
     * \brief Performs a POST request.
     * \param uri The requested uri.
     * \param req_headers Headers associated to request.
     * \param req_data Data associated to request.
     */
    virtual std::map<std::string, std::string> Post(
        const std::string &uri,
        const std::vector<std::string> &req_headers,
        const std::vector<std::string> &req_data) const;

   private:
    /**
     * \brief Fetch a given uri.
     * \param uri Requested uri.
     * \param fetch Libcurl's fetch structure.
     * \return CURL_OK in success; otherwise the suitable error code.
     */
    CURLcode FetchUri(const std::string &uri, struct CurlFetch *fetch) const;

    /**
     * \brief Libcurl callback.
     */
    static size_t CurlCallback(void *contents, size_t size, size_t nmemb, void *userp);

    /**
     * \brief Convert a json string into a map.
     * \param json_str The string in json format.
     * \return A map containing the json data.
     */
    std::map<std::string, std::string> JsonStrToMap(char *json_str) const;

    CURL *curl_handle_; //!< Handle for libcurl.
};

}  // espotifai_api

#endif  // CURL_WRAPPER_H_
