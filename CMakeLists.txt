cmake_minimum_required(VERSION 4.0)

project(RegisterC C)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)

set(CMAKE_C_STANDARD 17)

set(CMAKE_C_FLAGS "-D_GNU-SOURCE -Wall -std=c99")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_BUILD_TYPE Debug)

add_executable(registerC "")
target_link_libraries(registerC sqlite3)

target_sources(registerC
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src/main.c
    ${CMAKE_CURRENT_LIST_DIR}/src/person.c
    ${CMAKE_CURRENT_LIST_DIR}/src/menu.c
    ${CMAKE_CURRENT_LIST_DIR}/src/use_cases/person_add.c
    ${CMAKE_CURRENT_LIST_DIR}/src/use_cases/person_delete.c
    ${CMAKE_CURRENT_LIST_DIR}/src/use_cases/person_update.c
    ${CMAKE_CURRENT_LIST_DIR}/src/use_cases/person_find.c
    ${CMAKE_CURRENT_LIST_DIR}/src/use_cases/person_list.c
    ${CMAKE_CURRENT_LIST_DIR}/src/use_cases/person_quit.c
    ${CMAKE_CURRENT_LIST_DIR}/src/repository/file/file_database.c
    ${CMAKE_CURRENT_LIST_DIR}/src/repository/sqlite/sqlite_database.c
    ${CMAKE_CURRENT_LIST_DIR}/src/repository/repository.c
    ${CMAKE_CURRENT_LIST_DIR}/src/repository/repository_factory.c
    )

target_include_directories(registerC
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/src/repository/file
    ${CMAKE_CURRENT_LIST_DIR}/src/repository/sqlite
    )