
set(LIBRARY_NAME "GLEW")
set(SUB_LIBRARY_NAMES
        "glew32d"
        "glew32sd"
        "glew32"
        "glew32s"
        )

set(INCLUDE_FILE "GL/glew.h")

include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/FindLibrary.cmake")
