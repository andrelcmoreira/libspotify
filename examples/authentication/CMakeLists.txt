cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "authentication")
project(authentication)

set(sources_dir "${CMAKE_CURRENT_LIST_DIR}")
set(CMAKE_CXX_STANDARD 14)

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/../../include
)

link_directories(${CMAKE_SOURCE_DIR}/../../build)

set(
    SOURCES
    ${sources_dir}/auth.cc
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(
    ${PROJECT_NAME}
    espotifai_api
)
