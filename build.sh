#!/usr/bin/env bash

# configure bash environment
set -o errexit -o pipefail -o noclobber -o nounset

# declare project structure

CPPCON_ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

is_command_installed () {
    if [ $# -eq 0 ]; then return 1; fi
    for cmd in "$@"; do
        if ! hash "$cmd" 2>/dev/null; then
            return 1
        fi
    done
    return 0
}

build_build () {

    local dir_source="${CPPCON_ROOT_DIR}"
    local dir_build="${dir_source}/build"
    mkdir -p "${dir_build}"

    if case $OSTYPE in linux* | darwin*) false;; *) true;; esac; then
        printf "recipe not implemented for windows."
        return 1;
    fi

    local buildtype="Release"

    local cmake_generator="Unix Makefiles"
    if is_command_installed "ninja"; then
        cmake_generator="Ninja"
    fi

    local cmake_config_optional_args=()
    if is_command_installed "ccache"; then
        cmake_config_optional_args+=(
            -DCMAKE_C_COMPILER_LAUNCHER=ccache
            -DCMAKE_CXX_COMPILER_LAUNCHER=ccache
        )
    fi

    local cmake_config_general_args=(
        -B"${dir_build}"
        -H"${dir_source}"
        -G"${cmake_generator}"
        -DCMAKE_BUILD_TYPE="${buildtype}"
        "${cmake_config_optional_args[@]}"
    )

    cmake "${cmake_config_general_args[@]}"
    cmake --build "${dir_build}" --parallel
}

build_build
