cmake_minimum_required(VERSION 3.15)
project(
    CppTemplate
    VERSION 1.0.0
    LANGUAGES CXX
)

# ############################################################################################################
# Helper Functions
# ############################################################################################################

include(FetchContent)

#[[
Fetch a commit from a GitHub via a shallow clone.

Options:
``REPO``
  A path in the form of owner/repo (e.g., juce-framework/JUCE).
``TAG``
  A GitHub tag (e.g., v1.0.0).
]]
function(fetch_github REPO TAG)
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
    target_compile_features(${name} INTERFACE cxx_std_20)
endfunction()

# ############################################################################################################
# Deps
# ############################################################################################################

# fetch_github(thezhe/cppConfigs v0.9) # Adds opinionated linter/formatter/IDE/CI files to source directory.

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

# TODO: install
