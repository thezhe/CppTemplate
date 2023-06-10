# ############################################################################################################
# Helper Functions
# ############################################################################################################

include(FetchContent)

#[[
Shallow clone and add a CMake project from GitHub.

Options:
``OWNER_REPO_TAG_STRING``
  A string in the form of owner/repo@tag (e.g., "thezhe/CppTemplate@v1.0.0").
]]
function(fetch_github OWNER_REPO_TAG_STRING)
    string(REGEX REPLACE "[/@]" ";" OWNER_REPO_TAG_LIST ${OWNER_REPO_TAG_STRING})
    list(POP_FRONT OWNER_REPO_TAG_LIST OWNER REPO TAG)

    FetchContent_Declare(
        ${REPO}
        GIT_REPOSITORY "https://github.com/${OWNER}/${REPO}.git"
        GIT_TAG ${TAG}
        GIT_SHALLOW ON
    )
    FetchContent_MakeAvailable(${REPO})
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

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install)
endif()

cmake_minimum_required(VERSION 3.15)

project(CppTemplate)

# ############################################################################################################
# Deps
# ############################################################################################################

fetch_github("thezhe/cppConfigs@v0.9") # Adds opinionated linter/formatter/IDE/CI files to source directory.

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
