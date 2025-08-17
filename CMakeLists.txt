cmake_minimum_required(VERSION 4.0)

project(RegisterC C)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)

set(CMAKE_C_STANDARD 17)

set(CMAKE_C_FLAGS "-D_GNU-SOURCE -Wall -std=c99")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

add_executable(registerC "")
target_sources(registerC
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src/main.c
    )
target_include_directories(registerC
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
    )