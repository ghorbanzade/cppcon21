# Copyright 2021 Touca, Inc. Subject to Apache-2.0 License.

include(GenerateExportHeader)

cppcon_find_fmt()
cppcon_find_nlohmann_json()

add_library(${CPPCON_TARGET_MAIN} "")

target_sources(
        ${CPPCON_TARGET_MAIN}
    PRIVATE
        date.cpp
)

target_link_libraries(
        ${CPPCON_TARGET_MAIN}
    PRIVATE
        cppcon_project_options
    PUBLIC
        fmt::fmt
        nlohmann_json::nlohmann_json
)

target_include_directories(
        ${CPPCON_TARGET_MAIN}
    PUBLIC
        $<BUILD_INTERFACE:${CPPCON_ROOT_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/generated>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_definitions(
        ${CPPCON_TARGET_MAIN}
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:NOMINMAX>
        $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>
)

target_compile_options(
        ${CPPCON_TARGET_MAIN}
    PRIVATE
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wno-unused-parameter>
)

set_target_properties(
        ${CPPCON_TARGET_MAIN}
    PROPERTIES
        SOVERSION ${CPACK_PACKAGE_VERSION_MAJOR}
        VERSION ${CPPCON_VERSION}
        POSITION_INDEPENDENT_CODE ON
        DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
)

generate_export_header(
    ${CPPCON_TARGET_MAIN}
    EXPORT_MACRO_NAME "CPPCON_API"
    EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/generated/cppcon/lib_api.hpp"
)

source_group(
    TREE
        ${CMAKE_CURRENT_LIST_DIR}
    FILES
        $<TARGET_PROPERTY:${CPPCON_TARGET_MAIN},SOURCES>
)
