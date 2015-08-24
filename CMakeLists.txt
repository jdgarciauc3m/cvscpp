cmake_minimum_required (VERSION 2.8)
project(cvscpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
include_directories(
  "${PROJECT_SOURCE_DIR}/include"
)

list(APPEND CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wextra -Wno-deprecated -Werror -pedantic-errors -pthread")

add_subdirectory(gennum)
