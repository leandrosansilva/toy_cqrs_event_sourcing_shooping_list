project(shoppinglist_cqrs)

include(ExternalProject)

cmake_minimum_required(VERSION 2.6)

add_definitions(-std=c++14 -Wall -Wextra)

include_directories(${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR})

execute_process(COMMAND git submodule update --init --recursive)

include_directories(${CMAKE_SOURCE_DIR}/bandit/)
enable_testing()
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/bandit/cmake/cotire/CMake/")
include(cotire)

ExternalProject_Add(
  re2
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/re2
  INSTALL_COMMAND true
)

set(SERVED_LIB_DIR "${CMAKE_BINARY_DIR}/re2-prefix/src/re2-build/" CACHE STRING "")
set(SERVED_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/re2" CACHE STRING "")

message(${SERVED_LIB_DIR})
message(${SERVED_INCLUDE_DIR})

ExternalProject_Add(
  served
  DEPENDS re2
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/served
  CMAKE_ARGS -DSERVED_BUILD_STATIC=ON -DSERVED_BUILD_SHARED=OFF -DSERVED_INCLUDE_DIR=${SERVED_INCLUDE_DIR} -DSERVED_LIB_DIR=${SERVED_LIB_DIR}
)

ExternalProject_Get_Property(served install_dir)
include_directories(${install_dir}/include)

add_subdirectory(tests)

add_subdirectory(src)

