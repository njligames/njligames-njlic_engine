
set(LIBRARY_NAME "vorbis")
set(SUB_LIBRARY_NAMES
        "vorbisfile"
        "vorbis"
        "vorbisenc"
        )

set(PACKAGE_PATHS
        "/usr/lib/arm-linux-gnueabihf/"
        "/usr/lib/x86_64-linux-gnu/"
        )

set(PACKAGE_INCLUDE_PATH
        "/usr/include/vorbis/"
        )

set(INCLUDE_FILE "vorbis/codec.h")

include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/FindLibrary.cmake")
