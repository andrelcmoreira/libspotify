cmake_minimum_required(VERSION 3.16.1)

include(FetchContent)

message(STATUS "Fetching dependencies")

### jsoncpp ######################################################
message(STATUS "Fetching jsoncpp")

FetchContent_Declare(
    libjsoncpp
    GIT_REPOSITORY  git@github.com:open-source-parsers/jsoncpp.git
    GIT_TAG         1.9.3
)

FetchContent_MakeAvailable(libjsoncpp)
#################################################################

### libcurl #####################################################
message(STATUS "Fetching libcurl")

FetchContent_Declare(
    libcurl
    GIT_REPOSITORY  git@github.com:curl/curl.git
    GIT_TAG         curl-7_79_1
)

FetchContent_MakeAvailable(libcurl)

set_target_properties(
    libcurl
    PROPERTIES
    COMPILE_FLAGS "-fPIC"
)
#################################################################

### gtest #######################################################
if(UNIT_TESTS)
    message(STATUS "Fetching gtest")

    FetchContent_Declare(
        google_test
        GIT_REPOSITORY  git@github.com:google/googletest.git
        GIT_TAG         release-1.11.0
    )

    FetchContent_MakeAvailable(google_test)
endif(UNIT_TESTS)
#################################################################
