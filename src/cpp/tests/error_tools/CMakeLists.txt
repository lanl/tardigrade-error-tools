add_executable (test_${CMAKE_PROJECT_NAME} "test_${CMAKE_PROJECT_NAME}.cpp")

target_include_directories(test_${CMAKE_PROJECT_NAME} PUBLIC .)
set_target_properties(test_${CMAKE_PROJECT_NAME} PROPERTIES CXX_STANDARD 11)

target_link_libraries(test_${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_PROJECT_NAME}.o)
target_include_directories(test_${CMAKE_PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/src/cpp")
