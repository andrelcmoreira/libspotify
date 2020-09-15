cmake_minimum_required(VERSION 2.8)

set(espotifai_api_dir "${CMAKE_CURRENT_LIST_DIR}")
set(PROJECT_NAME "espotifai_api")

project(espotifai_api)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(${PROJECT_NAME} SHARED
    src/api.cc
    src/spotify_auth.cc
    src/curl_wrapper.cc
    src/utils.cc
)
target_link_libraries(${PROJECT_NAME} curl)
