cmake_minimum_required(VERSION 3.28)

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
    ${CMAKE_CURRENT_LIST_DIR}/src/domain/model/person.c
    ${CMAKE_CURRENT_LIST_DIR}/src/domain/services/person_service.c
    ${CMAKE_CURRENT_LIST_DIR}/src/adapters/repositories/person_repository_factory.c
    ${CMAKE_CURRENT_LIST_DIR}/src/adapters/repositories/file/person_repository_file.c
    ${CMAKE_CURRENT_LIST_DIR}/src/adapters/repositories/sqlite/person_repository_sqlite.c
    ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/person_controller_factory.c
    ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/cli_controller/person_controller_cli.c
    ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/cli_controller/cli/cli.c
    ${CMAKE_CURRENT_LIST_DIR}/src/domain/ports
    )

target_include_directories(registerC
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/src/domain/model
    ${CMAKE_CURRENT_LIST_DIR}/src/domain/ports
    ${CMAKE_CURRENT_LIST_DIR}/src/domain/services
    ${CMAKE_CURRENT_LIST_DIR}/src/adapters/repositories
    ${CMAKE_CURRENT_LIST_DIR}/src/adapters/repositories/file
    ${CMAKE_CURRENT_LIST_DIR}/src/adapters/repositories/sqlite
    ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers
    ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/cli_controller
    ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/cli_controller/cli
    )