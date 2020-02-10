cmake_minimum_required (VERSION 2.8)

project (error_tools)

add_subdirectory ("src/cpp")
add_subdirectory ("docs")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-std=gnu++11 -Wall -ansi -pedantic -O3 -I. -fmax-errors=5")
