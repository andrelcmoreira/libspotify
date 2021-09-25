cmake_minimum_required(VERSION 3.16.1)

project(espotifai_api)

set(espotifai_api_dir "${CMAKE_CURRENT_LIST_DIR}")
set(PROJECT_NAME "espotifai_api")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILET g++)
set(CMAKE_CXX_FLAGS "-Wall -Werror -O0")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

add_library(
    ${PROJECT_NAME}
    SHARED
    api.cc
    api_private.cc
    authenticator.cc
    curl_wrapper.cc
    searcher.cc
    playlist_mgr.cc
    utils.cc
)

target_link_libraries(
    ${PROJECT_NAME}
    libcurl
    jsoncpp
)
