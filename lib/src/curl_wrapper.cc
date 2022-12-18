/**
 * @file
 *
 * @brief Curl wrapper class implementation.
 */
#include "private/curl_wrapper.h"

#include <cstring>
#include <stdexcept>

namespace spotify_lib {

using Json::Value;
using std::memcpy;
using std::runtime_error;
using std::size_t;
using std::string;
using std::vector;

struct CurlFetch {
  char* payload;
  size_t size;
};

CurlWrapper::CurlWrapper()
    : curl_handle_{static_cast<CURL*>(curl_easy_init())} {
  if (!curl_handle_) {
    throw runtime_error("failed to start the authentication process!");
  }
}

CurlWrapper::~CurlWrapper() { curl_easy_cleanup(curl_handle_); }

Value CurlWrapper::Post(const string& uri, const vector<string>& req_headers,
                        const vector<string>& req_data) const {
  Value response;
  struct curl_slist* headers = nullptr;
  struct CurlFetch curl_fetch;
  struct CurlFetch* cf = &curl_fetch;

  for (auto& h : req_headers) {
    headers = curl_slist_append(headers, h.c_str());
  }

  curl_easy_setopt(curl_handle_, CURLOPT_CUSTOMREQUEST, "POST");
  curl_easy_setopt(curl_handle_, CURLOPT_HTTPHEADER, headers);

  for (auto& d : req_data) {
    headers = curl_slist_append(headers, d.c_str());
    curl_easy_setopt(curl_handle_, CURLOPT_POSTFIELDS, d.c_str());
  }

  auto ret = FetchUri(uri.c_str(), cf);

  curl_slist_free_all(headers);

  if (ret != CURLE_OK) {
    throw runtime_error(
        "failed to establish the connection with remote server!");
  }

  if (cf->payload) {
    string errors; /* unused */
    auto json_reader = builder_.newCharReader();

    bool parse_ok = json_reader->parse(cf->payload, cf->payload + cf->size,
                                       &response, &errors);

    free(cf->payload);

    if (!parse_ok) {
      throw runtime_error("failed to parse the response from server!");
    }
  }

  return response;
}

Value CurlWrapper::Get(const string& uri,
                       const vector<string>& req_headers) const {
  Value response;
  struct curl_slist* headers = nullptr;
  struct CurlFetch curl_fetch;
  struct CurlFetch* cf = &curl_fetch;

  for (auto& h : req_headers) {
    headers = curl_slist_append(headers, h.c_str());
  }

  curl_easy_setopt(curl_handle_, CURLOPT_CUSTOMREQUEST, "GET");
  curl_easy_setopt(curl_handle_, CURLOPT_HTTPHEADER, headers);

  auto ret = FetchUri(uri.c_str(), cf);

  curl_slist_free_all(headers);

  if (ret != CURLE_OK) {
    throw runtime_error(
        "failed to establish the connection with remote server!");
  }

  if (cf->payload) {
    string errors; /* unused */
    auto json_reader = builder_.newCharReader();

    bool parse_ok = json_reader->parse(cf->payload, cf->payload + cf->size,
                                       &response, &errors);

    free(cf->payload);

    if (!parse_ok) {
      throw runtime_error("failed to parse the response from server!");
    }
  }

  return response;
}

CURLcode CurlWrapper::FetchUri(const string& uri,
                               struct CurlFetch* fetch) const {
  fetch->size = 0;
  fetch->payload = (char*)calloc(1, sizeof(fetch->payload));

  if (!fetch->payload) {
    return CURLE_FAILED_INIT;
  }

  curl_easy_setopt(curl_handle_, CURLOPT_URL, uri.c_str());
  curl_easy_setopt(curl_handle_, CURLOPT_WRITEFUNCTION, CurlCallback);
  curl_easy_setopt(curl_handle_, CURLOPT_WRITEDATA, (void*)fetch);
  curl_easy_setopt(curl_handle_, CURLOPT_USERAGENT, "libcurl-agent/1.0");
  curl_easy_setopt(curl_handle_, CURLOPT_TIMEOUT, 15);
  curl_easy_setopt(curl_handle_, CURLOPT_FOLLOWLOCATION, 1);
  curl_easy_setopt(curl_handle_, CURLOPT_MAXREDIRS, 1);

  return curl_easy_perform(curl_handle_);
}

size_t CurlWrapper::CurlCallback(void* contents, size_t size, size_t nmemb,
                                 void* userp) {
  size_t realsize = size * nmemb;
  struct CurlFetch* p = (struct CurlFetch*)userp;

  p->payload = (char*)realloc(p->payload, p->size + realsize + 1);
  if (!p->payload) {
    free(p->payload);
    return 1;
  }

  memcpy(&(p->payload[p->size]), contents, realsize);

  p->size += realsize;
  p->payload[p->size] = 0;

  return realsize;
}

}  // namespace spotify_lib
