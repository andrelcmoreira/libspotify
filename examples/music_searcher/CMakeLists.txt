cmake_minimum_required(VERSION 3.1)

project(music_searcher)

set(CMAKE_CXX_STANDARD 14)
set(PROJECT_NAME "music_searcher")
set(sources_dir "${CMAKE_CURRENT_LIST_DIR}")

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/../../include
)

link_directories(${CMAKE_CURRENT_LIST_DIR}/../../build)

set(
    SOURCES
    ${sources_dir}/music_searcher.cc
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(
    ${PROJECT_NAME}
    espotifai_api
)
