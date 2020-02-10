find_package(Doxygen REQUIRED)

# Find all the public headers
get_target_property(ERROR_TOOLS_PUBLIC_HEADER_DIR src/cpp INTERFACE_INCLUDE_DIRECTORIES)
file(GLOB_RECURSE ERROR_TOOLS_PUBLIC_HEADERS ${ERROR_TOOLS_PUBLIC_HEADER_DIR}/*.h)

# Set some variables
set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR}/src/cpp)
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/docs/doxygen)
set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.html)
set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

#Replace variables inside @@ with the current values
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})
add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
                   DEPENDS ${ERROR_TOOLS_PUBLIC_HEADERS}
                   COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   MAIN_DEPENDENCY Doxyfile
                   COMMENT "Generating error_tools docs")

add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})
