add_executable (test_error_tools "test_error_tools.cpp")

target_include_directories(test_error_tools PUBLIC .)
set_target_properties(test_error_tools PROPERTIES CXX_STANDARD 11)

target_link_libraries(test_error_tools error_tools.o)
target_include_directories(test_error_tools PUBLIC "${PROJECT_SOURCE_DIR}/src/cpp")
