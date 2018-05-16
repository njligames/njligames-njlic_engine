# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build ${CMAKE_PROJECT_NAME} documentation" ON)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
  # set input and output files
  set(DOXYGEN_PROJECT_DIR "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}")
  set(DOXYGEN_IN ${CMAKEIN_REPO_DIRECTORY}/Doxyfile.in)
  set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

  # request to configure the file
  configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
  message(STATUS "Doxygen build started")

  # note the option ALL which allows to build the docs together with the application
  # add_custom_target( ${CMAKE_PROJECT_NAME}-documentation ALL
  #     COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
  #     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  #     COMMENT "Generating API documentation with Doxygen"
  #     VERBATIM )

  add_custom_command(
    OUTPUT
    ${CMAKE_CURRENT_BINARY_DIR}/doc/html/index.html
    COMMAND
    ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT
    "Generating API documentation with Doxygen"
    VERBATIM
    )
  
  add_custom_target(${CMAKE_PROJECT_NAME}-documentation ALL
    DEPENDS
    ${CMAKE_CURRENT_BINARY_DIR}/doc/html/index.html
    SOURCES
    ${CMAKE_CURRENT_BINARY_DIR}/doc/html/index.html
    )
  
  set_source_files_properties( ${CMAKE_CURRENT_BINARY_DIR}/doc/html/index.html PROPERTIES GENERATED TRUE )

else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

