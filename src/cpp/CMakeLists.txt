add_library (${PROJECT_NAME} "${PROJECT_NAME}.cpp" "${PROJECT_NAME}.h")
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11
                                                 PUBLIC_HEADER ${PROJECT_NAME}.h)
target_compile_options(${PROJECT_NAME} PUBLIC
                       -Wall -ansi -pedantic -O3 -fmax-errors=5 -ggdb)
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}_Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
