cmake_minimum_required(VERSION 3.1)

project(espotifai_api_tests)

set(PROJECT_NAME "espotifai_api_tests")
set(test_main_source ${CMAKE_CURRENT_LIST_DIR}/src/main.cc)
set(sources_dir "${CMAKE_CURRENT_LIST_DIR}")

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/../../include
    ${CMAKE_CURRENT_LIST_DIR}
)

link_directories(${CMAKE_SOURCE_DIR}/../../build /usr/local/lib64)

set(
    SOURCES
    ${sources_dir}/src/spotify_auth_test.cc
    ${sources_dir}/src/music_searcher_test.cc
    ${sources_dir}/src/playlist_mgr_test.cc
    ${test_main_source}
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(
    ${PROJECT_NAME}
    gtest
    gtest_main
    gmock
    pthread
    espotifai_api
)
