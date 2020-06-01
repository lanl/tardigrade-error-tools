add_library (${CMAKE_PROJECT_NAME} "${CMAKE_PROJECT_NAME}.cpp" "${CMAKE_PROJECT_NAME}.h")

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC .)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES CXX_STANDARD 11)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC
                       -Wall -ansi -pedantic -O3 -fmax-errors=5 -ggdb)
