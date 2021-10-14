# Copyright 2021 Touca, Inc. Subject to Apache-2.0 License.

add_executable(cppcon_app "")

target_sources(
        cppcon_app
    PRIVATE
        main.cpp
)

target_link_libraries(
        cppcon_app
    PRIVATE
        cppcon
)
