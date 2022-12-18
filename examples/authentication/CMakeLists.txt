cmake_minimum_required(VERSION 3.16.1)

project(authentication)

set(CMAKE_CXX_STANDARD 14)
set(PROJECT_NAME "authentication")
set(sources_dir "${CMAKE_CURRENT_LIST_DIR}")

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/../../include
)

link_directories(${CMAKE_CURRENT_LIST_DIR}/../../build)

set(
    SOURCES
    ${sources_dir}/auth.cc
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(
    ${PROJECT_NAME}
    spotify_lib
)
