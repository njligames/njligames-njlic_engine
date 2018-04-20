
message(STATUS "Platform is macOS for project")

DOWNLOAD_LIBRARY_BINARY_FILES("bullet" "https://www.dropbox.com/s/cbmdirabylueukr/LIBBULLET_1.3.5_macOS.tar.gz?dl=0" "thirdparty/bullet/lib/macOS")
DOWNLOAD_LIBRARY_BINARY_FILES("imgui" "https://www.dropbox.com/s/s6ombjjnb6or9xn/LIBIMGUI_1.5.0_macOS.tar.gz?dl=0" "thirdparty/imgui/lib/macOS")
DOWNLOAD_LIBRARY_BINARY_FILES("imguizmo" "https://www.dropbox.com/s/hppgmykw25k0xys/LIBIMGUIZMO_1.04_macOS.tar.gz?dl=0" "thirdparty/imguizmo/lib/macOS")
DOWNLOAD_LIBRARY_BINARY_FILES("jsoncpp" "https://www.dropbox.com/s/skh3zs3ps4lq797/LIBJSONCPP_1.8.0_macOS.tar.gz?dl=0" "thirdparty/jsoncpp/lib/macOS")
DOWNLOAD_LIBRARY_BINARY_FILES("nanovg" "https://www.dropbox.com/s/e04zo6h8buc3ydo/LIBNANOVG_macOS.tar.gz?dl=0" "thirdparty/nanovg/lib/macOS")
DOWNLOAD_LIBRARY_BINARY_FILES("ogg" "https://www.dropbox.com/s/59t9nblaagk1aid/LIBOGG_1.3.2_macOS.tar.gz?dl=0" "thirdparty/ogg/lib/macOS")
DOWNLOAD_LIBRARY_BINARY_FILES("vorbis" "https://www.dropbox.com/s/l4hy6vb8a3apwxh/LIBVORBIS_1.3.5_macOS.tar.gz?dl=0" "thirdparty/vorbis/lib/macOS")

IF( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "fmod" )
  message(STATUS "need to add fmod lib")
ELSEIF( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "openal" )
  list(APPEND EXTRA_LIBS "-framework OpenAL")
ELSEIF( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "sdl" )
  message(STATUS "need to add sdl lib")
ENDIF()

list(APPEND EXTRA_LIBS "-framework OpenGL")
