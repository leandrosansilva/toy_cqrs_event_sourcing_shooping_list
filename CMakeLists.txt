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
set(DEPS_INSTALL_DIR "${CMAKE_BINARY_DIR}/deps" CACHE STRING "")

ExternalProject_Add(
  served
  DEPENDS re2
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/served
  CMAKE_ARGS 
    -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_DIR}
    -DSERVED_BUILD_STATIC=ON -DSERVED_BUILD_SHARED=OFF 
    -DSERVED_INCLUDE_DIR=${SERVED_INCLUDE_DIR} 
    -DSERVED_LIB_DIR=${SERVED_LIB_DIR}
    -DSERVED_BUILD_EXAMPLES=OFF
    -DSERVED_BUILD_TESTS=OFF
)

include_directories(${DEPS_INSTALL_DIR}/include)
link_directories(${DEPS_INSTALL_DIR}/lib ${SERVED_LIB_DIR})

add_subdirectory(tests)

add_subdirectory(src)

