cmake_minimum_required(VERSION 3.1)

project(espotifai_api)

set(espotifai_api_dir "${CMAKE_CURRENT_LIST_DIR}")
set(PROJECT_NAME "espotifai_api")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Werror -O0")

option(UNIT_TESTS "Compile the library unit tests" OFF)
option(EXAMPLES "Compile the library examples" OFF)

if(UNIT_TESTS)
    add_subdirectory(tests/unit)
endif()

if(EXAMPLES)
    add_subdirectory(examples)
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(
    ${PROJECT_NAME} SHARED
    src/api.cc
    src/api_private.cc
    src/authenticator.cc
    src/curl_wrapper.cc
    src/searcher.cc
    src/playlist_mgr.cc
    src/utils.cc
)

target_link_libraries(
    ${PROJECT_NAME}
    curl
    jsoncpp
)
