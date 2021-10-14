# Copyright 2021 CppCon, Inc. Subject to Apache-2.0 License.

cmake_minimum_required(VERSION 3.14...3.21 FATAL_ERROR)

set(CPPCON_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
set(CPPCON_TARGET_MAIN cppcon)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(CONAN_CMAKE_SILENT_OUTPUT ON)

project(CppCon VERSION 2021.0.0 LANGUAGES CXX)

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

if (NOT DEFINED CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release)
endif()

if (NOT DEFINED CMAKE_DEBUG_POSTFIX)
    set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "Default postfix for libraries with debug build type")
endif()

if (NOT DEFINED CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif()

if (NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif()

if (NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

add_library(cppcon_project_options INTERFACE)

if(CMAKE_GENERATOR STREQUAL "Ninja")
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
        target_compile_options(cppcon_project_options INTERFACE -fcolor-diagnostics)
    endif()
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(cppcon_project_options INTERFACE -fdiagnostics-color=always)
    endif()
endif()

if (cppcon_BUILD_TESTS)
    if (MSVC)
        target_compile_options(cppcon_project_options INTERFACE /W4 /wd4251)
    else()
        target_compile_options(cppcon_project_options INTERFACE -Wextra -Werror -Wfatal-errors)
        target_compile_options(cppcon_project_options INTERFACE -Wall -pedantic)
    endif()
endif()

message(DEBUG "CppCon: building version: ${cppcon_VERSION}")
message(DEBUG "CppCon: using cxx standard: ${CMAKE_CXX_STANDARD}")
message(DEBUG "CppCon: using build type: ${CMAKE_BUILD_TYPE}")

include(external.cmake)

add_subdirectory(src)
add_subdirectory(app)
