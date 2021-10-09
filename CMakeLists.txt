cmake_minimum_required(VERSION 3.16.1)

project(espotifai_api)

option(UNIT_TESTS "Compile the library unit tests" OFF)
option(EXAMPLES "Compile the library examples" OFF)
option(INSTALL_DEPENDENCIES "Install the library dependencies" ON)

add_subdirectory(lib)

if(UNIT_TESTS)
    add_subdirectory(tests/unit)
endif(UNIT_TESTS)

if(EXAMPLES)
    add_subdirectory(examples)
endif(EXAMPLES)

if(INSTALL_DEPENDENCIES)
    include(scripts/cmake/fetch_dependencies.cmake)
endif(INSTALL_DEPENDENCIES)
