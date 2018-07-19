
message(STATUS "Platform is windows32 for project")

find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
  MESSAGE(STATUS "OPENGL_INCLUDE_DIR ${OPENGL_INCLUDE_DIR}")
  MESSAGE(STATUS "OPENGL_LIBRARIES ${OPENGL_LIBRARIES}")
  list(APPEND EXTRA_LIBS "${OPENGL_LIBRARIES}")
  list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRECTORES "${OPENGL_INCLUDE_DIR}")
endif()

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
  MESSAGE(STATUS "GLEW_INCLUDE_DIR ${GLEW_INCLUDE_DIR}")
  MESSAGE(STATUS "GLEW_LIBRARY ${GLEW_LIBRARY}")

  # get_cmake_property(_variableNames VARIABLES)
  # list (SORT _variableNames)
  # foreach (_variableName ${_variableNames})
  #   message(STATUS "${_variableName}=${${_variableName}}")
  # endforeach()

  # if(NOT TARGET GLEW)
  #   MESSAGE(FATAL_ERROR "GLEW isn't a target ${GLEW_LIBRARY}")
  # endif()
  list(APPEND EXTRA_LIBS ${GLEW_LIBRARY})
  list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRECTORES "${GLEW_INCLUDE_DIR}")
endif()

