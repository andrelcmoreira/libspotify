/**
 * \file
 * \brief Curl wrapper class implementation.
 */
#include "private/curl_wrapper.h"

#include <cstring>
#include <stdexcept>

#include <boost/algorithm/string.hpp>

namespace espotifai_api {

struct CurlFetch {
    char *payload;
    size_t size;
};

CurlWrapper::CurlWrapper()
    : curl_handle_{static_cast<CURL *>(curl_easy_init())}
{
    if (!curl_handle_) {
        throw std::runtime_error(
            "failed to start the authentication process!"
        );
    }
}

CurlWrapper::~CurlWrapper()
{
    curl_easy_cleanup(curl_handle_);
}

std::map<std::string, std::string> CurlWrapper::Post(
    const std::string &uri,
    const std::vector<std::string> &req_headers,
    const std::vector<std::string> &req_data) const
{
    std::map<std::string, std::string> response;
    struct curl_slist *headers = nullptr;
    struct CurlFetch curl_fetch;
    struct CurlFetch *cf = &curl_fetch;

    for (auto &h : req_headers) {
        headers = curl_slist_append(headers, h.c_str());
    }

    curl_easy_setopt(curl_handle_, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(curl_handle_, CURLOPT_HTTPHEADER, headers);

    for (auto &d : req_data) {
        headers = curl_slist_append(headers, d.c_str());
        curl_easy_setopt(curl_handle_, CURLOPT_POSTFIELDS, d.c_str());
    }

    auto ret = FetchUri(uri.c_str(), cf);

    curl_slist_free_all(headers);

    if (ret != CURLE_OK) {
        throw std::runtime_error(
            "failed to establish the connection with remote server!"
        );
    }

    if (cf->payload) {
        response = JsonStrToMap(cf->payload);
    }

    free(cf->payload);

    return response;
}

CURLcode CurlWrapper::FetchUri(const std::string &uri, struct CurlFetch *fetch) const
{
    fetch->size = 0;
    fetch->payload = (char *)calloc(1, sizeof(fetch->payload));

    if (!fetch->payload) {
        return CURLE_FAILED_INIT;
    }

    curl_easy_setopt(curl_handle_, CURLOPT_URL, uri.c_str());
    curl_easy_setopt(curl_handle_, CURLOPT_WRITEFUNCTION, CurlCallback);
    curl_easy_setopt(curl_handle_, CURLOPT_WRITEDATA, (void *)fetch);
    curl_easy_setopt(curl_handle_, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    curl_easy_setopt(curl_handle_, CURLOPT_TIMEOUT, 15);
    curl_easy_setopt(curl_handle_, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl_handle_, CURLOPT_MAXREDIRS, 1);

    return curl_easy_perform(curl_handle_);
}

size_t CurlWrapper::CurlCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct CurlFetch *p = (struct CurlFetch *)userp;

    p->payload = (char *)realloc(p->payload, p->size + realsize + 1);
    if (!p->payload) {
        free(p->payload);
        return 1;
    }

    std::memcpy(&(p->payload[p->size]), contents, realsize);

    p->size += realsize;
    p->payload[p->size] = 0;

    return realsize;
}


std::map<std::string, std::string> CurlWrapper::JsonStrToMap(
    char *json_str) const
{
    std::string str{json_str};

    /* removing non interesting chars. */
    boost::erase_all(str, "{");
    boost::erase_all(str, "}");
    boost::erase_all(str, "\"");

    /* filling the vector with the key-value entries */
    std::vector<std::string> key_val_pairs;
    boost::split(key_val_pairs, str, boost::is_any_of(","));

    std::map<std::string, std::string> parsed_json;
    for (auto &entry : key_val_pairs) {
        std::vector<std::string> map_entry;

        boost::split(map_entry, entry, boost::is_any_of(":"));
        parsed_json.insert({map_entry[0], map_entry[1]});
    }

    return parsed_json;
}

}  // espotifai_api
