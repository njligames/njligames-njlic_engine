
message(STATUS "Platform is windows64 for project")

find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
  MESSAGE(STATUS "OPENGL_INCLUDE_DIR ${OPENGL_INCLUDE_DIR}")
  MESSAGE(STATUS "OPENGL_LIBRARIES ${OPENGL_LIBRARIES}")
  list(APPEND EXTRA_LIBS "${OPENGL_LIBRARIES}")
  list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRECTORES "${OPENGL_INCLUDE_DIR}")
endif()

add_definitions(-DUSE_GLEW_LIBRARY)
include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadGLEW.cmake")
list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${GLEW_INCLUDE_DIRS}")
find_package(GLEW_NJLIC REQUIRED)
list(APPEND EXTRA_LIBS ${GLEW_TARGETS})
