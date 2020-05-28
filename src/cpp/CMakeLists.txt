add_library (error_tools "error_tools.cpp" "error_tools.h")

target_include_directories(error_tools PUBLIC .)
set_target_properties(error_tools PROPERTIES CXX_STANDARD 11)
target_compile_options(error_tools PUBLIC
                       -Wall -ansi -pedantic -O3 -fmax-errors=5 -ggdb)
