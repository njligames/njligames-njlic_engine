
set(LIBRARY_NAME "vorbis")
set(SUB_LIBRARY_NAMES
  "vorbis"
  "vorbisenc"
  "vorbisfile"
  )

set(INCLUDE_FILE "vorbis/codec.h")

include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/FindLibrary.cmake")
