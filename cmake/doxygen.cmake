# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build ${CMAKE_PROJECT_NAME} documentation" ON)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
  # set input and output files
  set(DOXYGEN_PROJECT_DIR "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}")
  set(DOXYGEN_IN ${CMAKEIN_REPO_DIRECTORY}/Doxyfile.in)
  set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/Doxyfile)

  # request to configure the file
  configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
  message(STATUS "Doxygen build started")

  # note the option ALL which allows to build the docs together with the application
  add_custom_target( ${CMAKE_PROJECT_NAME}-documentation ALL
    SOURCES ${CMAKE_BINARY_DIR}/Doxyfile
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM 
    )

  # add_custom_command(
  #   OUTPUT
  #   ${CMAKE_BINARY_DIR}/doc/html/index.html
  #   SOURCES
  #   ${CMAKE_BINARY_DIR}/doc/html/index.html
  #   COMMAND
  #   ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
  #   WORKING_DIRECTORY
  #   ${CMAKE_BINARY_DIR}
  #   COMMENT
  #   "Generating API documentation with Doxygen"
  #   VERBATIM
  #   )
  # 
  # add_custom_target(${CMAKE_PROJECT_NAME}-documentation ALL
  #   DEPENDS
  #   ${CMAKE_BINARY_DIR}/doc/html/index.html
  #   SOURCES
  #   ${CMAKE_BINARY_DIR}/doc/html/index.html
  #   )
  
  file(GLOB_RECURSE LUA_DOXYGEN_GENERATED_FILES
    "${CMAKE_BINARY_DIR}/doc/html/*.*"
    )
  set_property(DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${LUA_DOXYGEN_GENERATED_FILES})
  set_source_files_properties( ${LUA_DOXYGEN_GENERATED_FILES} PROPERTIES GENERATED TRUE )

  INSTALL(DIRECTORY ${CMAKE_BINARY_DIR}/doc/html DESTINATION doc)

else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

INSTALL(DIRECTORY ${CMAKE_BINARY_DIR}/doc/html DESTINATION doc)

