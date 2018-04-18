
message(STATUS "Platform is macOS for project")


DOWNLOAD_LIBRARY_INCLUDE_FILES("bullet" "https://www.dropbox.com/s/bvtxtpqa925godz/BULLET-1.85_include.tar.gz?dl=0" "thirdparty/bullet/include")
DOWNLOAD_LIBRARY_INCLUDE_FILES("debug-draw" "https://www.dropbox.com/s/isuefnerr26na7p/LIBDEBUGDRAW_include.tar.gz?dl=0" "thirdparty/debug-draw/include")
DOWNLOAD_LIBRARY_INCLUDE_FILES("glm" "https://www.dropbox.com/s/2sr0kts3054ojvw/LIBGLM_include.tar.gz?dl=0" "thirdparty/glm/include")
DOWNLOAD_LIBRARY_INCLUDE_FILES("imgui" "https://www.dropbox.com/s/govijzlvvvyp7gy/LIBIMGUI_1.5.0_include.tar.gz?dl=0" "thirdparty/imgui/include")
DOWNLOAD_LIBRARY_INCLUDE_FILES("imguizmo" "https://www.dropbox.com/s/1z8lar75aidhcjx/LIBIMGUIZMO_1.04_include.tar.gz?dl=0" "thirdparty/imguizmo/include")
DOWNLOAD_LIBRARY_INCLUDE_FILES("jsoncpp" "https://www.dropbox.com/s/v8dt6qpgp389ham/LIBJSONCPP_1.8.0_include.tar.gz?dl=0" "thirdparty/jsoncpp/include")
DOWNLOAD_LIBRARY_INCLUDE_FILES("lua" "https://www.dropbox.com/s/ff3rvbdtfr1k56i/LIBLUA-5.3.2_include.tar.gz?dl=0" "thirdparty/lua/include")
DOWNLOAD_LIBRARY_INCLUDE_FILES("nanovg" "https://www.dropbox.com/s/e04zo6h8buc3ydo/LIBNANOVG_macOS.tar.gz?dl=0" "thirdparty/nanovg/include")
DOWNLOAD_LIBRARY_INCLUDE_FILES("ogg" "https://www.dropbox.com/s/wm29ek4iifpkta2/LIBOGG_1.3.2_include.tar.gz?dl=0" "thirdparty/ogg/include")
DOWNLOAD_LIBRARY_INCLUDE_FILES("vorbis" "https://www.dropbox.com/s/f6l6iyq6o7fo72e/LIBVORBIS_1.3.5_include.tar.gz?dl=0" "thirdparty/vorbis/include")




DOWNLOAD_LIBRARY_BINARY_FILES("bullet" "https://www.dropbox.com/s/cbmdirabylueukr/LIBBULLET_1.3.5_macOS.tar.gz?dl=0" "thirdparty/bullet/lib/macOS")
DOWNLOAD_LIBRARY_BINARY_FILES("imgui" "https://www.dropbox.com/s/s6ombjjnb6or9xn/LIBIMGUI_1.5.0_macOS.tar.gz?dl=0" "thirdparty/imgui/lib/macOS")
DOWNLOAD_LIBRARY_BINARY_FILES("imguizmo" "https://www.dropbox.com/s/hppgmykw25k0xys/LIBIMGUIZMO_1.04_macOS.tar.gz?dl=0" "thirdparty/imguizmo/lib/macOS")
DOWNLOAD_LIBRARY_BINARY_FILES("jsoncpp" "https://www.dropbox.com/s/skh3zs3ps4lq797/LIBJSONCPP_1.8.0_macOS.tar.gz?dl=0" "thirdparty/jsoncpp/lib/macOS")
DOWNLOAD_LIBRARY_BINARY_FILES("lua" "https://www.dropbox.com/s/5wfx8rk9be4apni/LIBLUA-5.3.2_macOS.tar.gz?dl=0" "thirdparty/lua/lib/macOS")
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
