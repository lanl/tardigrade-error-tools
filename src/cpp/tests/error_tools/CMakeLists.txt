add_executable (test_${CMAKE_PROJECT_NAME} "test_${CMAKE_PROJECT_NAME}.cpp")
add_test(NAME test_${CMAKE_PROJECT_NAME} COMMAND test_${CMAKE_PROJECT_NAME})

set_target_properties(test_${CMAKE_PROJECT_NAME} PROPERTIES CXX_STANDARD 11)

target_link_libraries(test_${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_PROJECT_NAME})
