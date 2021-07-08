
set(LIBRARY_NAME "ogg")
set(SUB_LIBRARY_NAMES
  "ogg"
  )

set(PACKAGE_PATHS
    "/usr/lib/arm-linux-gnueabihf/"
    )

set(PACKAGE_INCLUDE_PATH
    "/usr/include/ogg/"
    )

set(INCLUDE_FILE "ogg/ogg.h")

include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/FindLibrary.cmake")
