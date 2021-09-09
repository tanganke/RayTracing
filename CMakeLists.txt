project(RayTracing)
cmake_minimum_required(VERSION 3.10)

find_package(PkgConfig REQUIRED)
pkg_check_modules(OPENCV REQUIRED opencv4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(CREATE_LINK ${CMAKE_CURRENT_LIST_DIR}/data ${CMAKE_BINARY_DIR}/data SYMBOLIC)

add_subdirectory(libRayTracing)

# These tests can use the Catch2-provided main
file(GLOB SOURCES ${CMAKE_CURRENT_LIST_DIR}/test/*.cpp)
add_executable(test ${SOURCES})
target_link_libraries(test PUBLIC RayTracing)

