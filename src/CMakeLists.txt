cmake_minimum_required(VERSION 3.15)

project(BASIC_APP VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)
include(cmake/cpm.cmake)

CPMAddPackage(
    NAME JUCE
    GITHUB_REPOSITORY juce-framework/JUCE
    GIT_TAG 7.0.9
    VERSION v7.0.9
    SOURCE_DIR ${LIB_DIR}/juce
)

# CPMAddPackage(
#     NAME JUCE
#     GITHUB_REPOSITORY juce-framework/JUCE
#     GIT_TAG 7.0.9
#     VERSION v7.0.9
#     SOURCE_DIR ${LIB_DIR}/juce
#     GIT_SHALLOW TRUE
#     GIT_USE_SSH TRUE
# )

if(MSVC)
    #add_compile_options(/Wall /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

add_subdirectory(Source)