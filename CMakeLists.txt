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
        ${REPO}_${TAG}
        GIT_REPOSITORY "https://github.com/${OWNER}/${REPO}.git"
        GIT_TAG ${TAG}
        GIT_SHALLOW ON
    )
    FetchContent_MakeAvailable(${REPO}_${TAG})
endfunction()

#[[
Add a header-only library.

Options:
``INTERFACE_NAME``
The name of the library.

Note:
Also adds "${PROJECT_NAME}::${INTERFACE_NAME}" as a valid library name.
]]
function(add_interface INTERFACE_NAME)
    add_library(${INTERFACE_NAME} INTERFACE)
    add_library(${PROJECT_NAME}::${INTERFACE_NAME} ALIAS ${INTERFACE_NAME})
endfunction()

#[[
Install a file to ${CMAKE_INSTALL_PREFIX}.

Options:
``FILE_PATH``
File path relative to ${CMAKE_SOURCE_DIR}.
]]
function(install_file_to_prefix FILE_PATH)
    install(FILES ${FILE_PATH} DESTINATION ${CMAKE_INSTALL_PREFIX})
endfunction()

#[[
Install a target to ${CMAKE_INSTALL_PREFIX}.

Options:
``TARGET_NAME``
]]
function(install_target_to_prefix TARGET_NAME)
    install(TARGETS ${TARGET_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
endfunction()

# ############################################################################################################
# Deps
# ############################################################################################################

# fetch_github("thezhe/CppConfigs@v0.9") # Adds opinionated linter/formatter/IDE/CI files to source directory.

# ############################################################################################################
# Src
# ############################################################################################################

# CppTemplate::libCppTemplate
add_library(libCppTemplate STATIC)
add_library(CppTemplate::libCppTemplate ALIAS libCppTemplate)

target_include_directories(libCppTemplate PUBLIC include)
target_sources(libCppTemplate PRIVATE src/CppTemplate/CppTemplate.cpp)

# CppTemplate
add_executable(CppTemplate)
target_link_libraries(CppTemplate PRIVATE libCppTemplate)

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

install_file_to_prefix(CHANGELOG.md)
install_target_to_prefix(CppTemplate)
