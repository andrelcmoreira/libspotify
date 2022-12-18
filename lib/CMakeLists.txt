cmake_minimum_required(VERSION 3.16.1)

project(spotify_lib)

set(spotify_lib_dir "${CMAKE_CURRENT_LIST_DIR}")
set(PROJECT_NAME "spotify_lib")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_CFLAGS "-Wall -Werror -Wextra -O3")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

add_library(
    ${PROJECT_NAME}
    SHARED
    src/spotify.cc
    src/spotify_private.cc
    src/authenticator.cc
    src/curl_wrapper.cc
    src/searcher.cc
    src/playlist_mgr.cc
    src/utils.cc
)

target_link_libraries(
    ${PROJECT_NAME}
    libcurl
    jsoncpp
)
