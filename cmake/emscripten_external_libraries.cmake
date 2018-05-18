
message(STATUS "Platform is emscripten for project")

DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("bullet"
  "https://www.dropbox.com/s/idv5r5y7zx5gqks/LIBBULLET_1.3.5_emscripten.tar.gz?dl=0"
  "thirdparty/bullet/lib/emscripten/Release")

DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("imgui"
  "https://www.dropbox.com/s/yu2iizjkjx4x5nu/LIBIMGUI_1.5.0_emscripten.tar.gz?dl=0"
  "thirdparty/imgui/lib/emscripten/Release")
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("imguizmo"
  "https://www.dropbox.com/s/hcgb9qf71rz23nq/LIBIMGUIZMO_1.04_emscripten.tar.gz?dl=0"
  "thirdparty/imguizmo/lib/emscripten/Release")
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("jsoncpp"
  "https://www.dropbox.com/s/e7lt7b1jokz99ph/LIBJSONCPP_1.8.0_emscripten.tar.gz?dl=0"
  "thirdparty/jsoncpp/lib/emscripten/Release")
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("nanovg"
  "https://www.dropbox.com/s/pfjqi8wqfgfwjl2/LIBNANOVG_emscripten.tar.gz?dl=0"
  "thirdparty/nanovg/lib/emscripten/Release")
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("ogg"
  "https://www.dropbox.com/s/iq6ekxu3k677th2/LIBOGG_1.3.2_emscripten.tar.gz?dl=0"
  "thirdparty/ogg/lib/emscripten/Release")
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("vorbis"
  "https://www.dropbox.com/s/dpa17v5zs3vhgcp/LIBVORBIS_1.3.5_emscripten.tar.gz?dl=0"
  "thirdparty/vorbis/lib/emscripten/Release")

DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("bullet"
  "https://www.dropbox.com/s/idv5r5y7zx5gqks/LIBBULLET_1.3.5_emscripten.tar.gz?dl=0"
  "thirdparty/bullet/lib/emscripten/Debug")
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("imgui"
  "https://www.dropbox.com/s/yu2iizjkjx4x5nu/LIBIMGUI_1.5.0_emscripten.tar.gz?dl=0"
  "thirdparty/imgui/lib/emscripten/Debug")
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("imguizmo"
  "https://www.dropbox.com/s/hcgb9qf71rz23nq/LIBIMGUIZMO_1.04_emscripten.tar.gz?dl=0"
  "thirdparty/imguizmo/lib/emscripten/Debug")
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("jsoncpp"
  "https://www.dropbox.com/s/e7lt7b1jokz99ph/LIBJSONCPP_1.8.0_emscripten.tar.gz?dl=0"
  "thirdparty/jsoncpp/lib/emscripten/Debug")
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("nanovg"
  "https://www.dropbox.com/s/pfjqi8wqfgfwjl2/LIBNANOVG_emscripten.tar.gz?dl=0"
  "thirdparty/nanovg/lib/emscripten/Debug")
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("ogg"
  "https://www.dropbox.com/s/iq6ekxu3k677th2/LIBOGG_1.3.2_emscripten.tar.gz?dl=0"
  "thirdparty/ogg/lib/emscripten/Debug")
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("vorbis"
  "https://www.dropbox.com/s/dpa17v5zs3vhgcp/LIBVORBIS_1.3.5_emscripten.tar.gz?dl=0"
  "thirdparty/vorbis/lib/emscripten/Debug")

IF( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "fmod" )
  message(STATUS "need to add fmod lib")
ELSEIF( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "openal" )
  message(STATUS "emscripten supports openal automatically")
ELSEIF( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "sdl" )
  message(STATUS "need to add sdl lib")
ENDIF()

