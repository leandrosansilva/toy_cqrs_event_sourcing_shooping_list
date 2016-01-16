project(shoppinglist_cqrs)

cmake_minimum_required(VERSION 2.6)

add_definitions(-std=c++11 -Wall -Wextra)

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})

execute_process(COMMAND git submodule update --init --recursive)

include_directories(${CMAKE_SOURCE_DIR}/bandit/)
enable_testing()
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/bandit/cmake/cotire/CMake/")
include(cotire)

add_subdirectory(tests)

add_subdirectory(src)
