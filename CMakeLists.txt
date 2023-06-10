# ############################################################################################################
# Helper Functions
# ############################################################################################################

include(FetchContent)

#[[
Shallow clone and add a CMake project from GitHub.

Options:
``REPO_TAG_STRING``
  A string in the form of owner/repo@tag (e.g., "thezhe/CppTemplate@v1.0.0").
]]
function(fetch_github REPO_TAG_STRING)
    string(REPLACE "@" ";" REPO_TAG_LIST ${REPO_TAG_STRING})
    list(GET REPO_TAG_LIST 0 REPO)
    list(GET REPO_TAG_LIST 1 TAG)

    FetchContent_Declare(
        content
        GIT_REPOSITORY "https://github.com/${REPO}.git"
        GIT_TAG ${TAG}
        GIT_SHALLOW ON
    )
    FetchContent_MakeAvailable(content)
endfunction()

#[[
Add a header-only library.

Options:
``name``
Interface name -- camelBack naming convention.
]]
function(add_interface name)
    add_library(${name} INTERFACE)
    add_library(${PROJECT_NAME}::${name} ALIAS ${name})
endfunction()

# ############################################################################################################
# Project
# ############################################################################################################
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED $CACHE{CMAKE_INSTALL_PREFIX} AND NOT DEFINED $ENV{CMAKE_INSTALL_PREFIX})
    set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install)
endif()

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install)

cmake_minimum_required(VERSION 3.15)

project(CppTemplate)

# ############################################################################################################
# Deps
# ############################################################################################################

# fetch_github("thezhe/cppConfigs@v0.9") # Adds opinionated linter/formatter/IDE/CI files to source directory.

# ############################################################################################################
# Src
# ############################################################################################################

# CppTemplate::cppTemplate
add_library(libCppTemplate STATIC)
add_library(CppTemplate::libCppTemplate ALIAS libCppTemplate)

target_include_directories(libCppTemplate PUBLIC include)
target_sources(libCppTemplate PRIVATE src/CppTemplate/CppTemplate.cpp)

# CppTemplate
add_executable(CppTemplate)
target_link_libraries(CppTemplate PRIVATE CppTemplate::libCppTemplate)

target_sources(CppTemplate PRIVATE src/main.cpp)

# ############################################################################################################
# Test
# ############################################################################################################

enable_testing()

# CppTemplateTest
add_executable(CppTemplateTest)
add_test(CppTemplateTest CppTemplateTest)
target_link_libraries(CppTemplateTest PRIVATE CppTemplate::libCppTemplate)

target_sources(CppTemplateTest PRIVATE test/CppTemplate/CppTemplateTest.cpp)

# ############################################################################################################
# Install
# ############################################################################################################

install(TARGETS CppTemplate)
# TODO: clearer naming
