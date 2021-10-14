include_guard()

include(FetchContent)

function(cppcon_find_fmt)
    FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt.git
        GIT_TAG         8.0.1
    )
    FetchContent_GetProperties(fmt)
    if (NOT fmt_POPULATED)
        FetchContent_Populate(fmt)
        add_library(fmt INTERFACE)
        add_library(fmt::fmt ALIAS fmt)
        target_compile_definitions(fmt INTERFACE FMT_HEADER_ONLY=1)
        target_include_directories(fmt INTERFACE ${fmt_SOURCE_DIR}/include)
    endif()
endfunction()

function(cppcon_find_nlohmann_json)
    FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY  https://github.com/nlohmann/json.git
        GIT_TAG         v3.10.3
    )
    FetchContent_GetProperties(nlohmann_json)
    if (NOT nlohmann_json_POPULATED)
        FetchContent_Populate(nlohmann_json)
        add_library(nlohmann_json INTERFACE)
        add_library(nlohmann_json::nlohmann_json ALIAS nlohmann_json)
        target_include_directories(nlohmann_json INTERFACE ${nlohmann_json_SOURCE_DIR}/include)
    endif()
endfunction()
