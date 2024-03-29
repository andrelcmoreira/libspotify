cmake_minimum_required(VERSION 3.16.1)

project(spotify_lib_tests)

set(PROJECT_NAME "spotify_lib_tests")
set(test_main_source ${CMAKE_CURRENT_LIST_DIR}/src/main.cc)
set(sources_dir "${CMAKE_CURRENT_LIST_DIR}")

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/../../include
    ${CMAKE_CURRENT_LIST_DIR}
)

link_directories(${CMAKE_SOURCE_DIR}/../../build /usr/local/lib64)

set(
    SOURCES
    ${sources_dir}/src/auth_test.cc
    ${sources_dir}/src/searcher_test.cc
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
    spotify_lib
)
