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

Externalproject_Get_Property(re2 install_dir)
include_directories(${install_dir}/include)

ExternalProject_Add(
  served
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/served
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/served -DSERVED_BUILD_STATIC=ON -DSERVED_BUILD_SHARED=OFF 
)

Externalproject_Get_Property(served install_dir)
include_directories(${install_dir}/include)

add_subdirectory(tests)

add_subdirectory(src)

