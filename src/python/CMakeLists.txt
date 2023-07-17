set(CYTHON_SOURCE_FILES
    tardigrade_error_tools_python.pxd
    tardigrade_error_tools_python.pyx
    setup.py
    settings.py.in
    conftest.py
)
configure_file(settings.py.in settings.py)
add_custom_target(${PROJECT_NAME}_CYTHON ALL
                  DEPENDS ${PROJECT_NAME})
add_custom_command(TARGET ${PROJECT_NAME}_CYTHON PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   "${PROJECT_SOURCE_DIR}/${PYTHON_SRC_PATH}" "${PROJECT_BINARY_DIR}/${PYTHON_SRC_PATH}"
                   COMMAND python setup.py build_ext --inplace
                   DEPENDS ${CYTHON_SOURCE_FILES}
                  )
install(FILES 
            "${PROJECT_SOURCE_DIR}/${PYTHON_SRC_PATH}/${PROJECT_NAME}_python.pyx"
            "${PROJECT_SOURCE_DIR}/${PYTHON_SRC_PATH}/${PROJECT_NAME}_python.pxd"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# Add pytests as a ctest function for automated testing under unified CMake/CTest tools
add_test(NAME pytest
         COMMAND pytest --cov-report=xml:$(pwd)/cobertura.xml --cov=$(pwd)/. --cov-report=html:$(pwd)/htmlcov
         WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/${PYTHON_SRC_PATH}
        )
