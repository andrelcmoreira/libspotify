cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "espotifai_api_tests")
project(espotifai_api_tests)

set(test_main_source ${CMAKE_CURRENT_LIST_DIR}/unit/main.cc)
set(sources_dir "${CMAKE_CURRENT_LIST_DIR}")

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/../include
    /usr/local/include/mongocxx/v_noabi
    /usr/local/include/bsoncxx/v_noabi
)

link_directories(${CMAKE_SOURCE_DIR}/../build /usr/local/lib64)

set(
    SOURCES
    ${sources_dir}/unit/spotify_auth_test.cc
    ${sources_dir}/unit/music_searcher_test.cc
    ${sources_dir}/unit/playlist_mgr_test.cc
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
    mongocxx
    bsoncxx
)
