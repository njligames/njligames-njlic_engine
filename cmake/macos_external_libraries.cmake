
message(STATUS "Platform is macOS for project")

macro(DOWNLOAD_LIBRARY_INCLUDE_FILES LIBNAME LIBRARY_INCLUDE_URL LIBRARY_DIRECTORY)

  set(${LIBNAME}_URL_INCLUDE 
    "${LIBRARY_INCLUDE_URL}" 
    CACHE STRING "The URL for the include files for ${LIBRARY_DIRECTORY}")

  RETRIEVE_TAR(
    "${${LIBNAME}_URL_INCLUDE}"
    "${LIBRARY_DIRECTORY}"
    "SKIP"
    )

  SET(SUBDIRS "")
  SUBDIRLIST(SUBDIRS "${CMAKE_BINARY_DIR}/${LIBRARY_DIRECTORY}" ${LIBNAME}_INCLUDE_DIRECTORY_LIST)

  include_directories("${CMAKE_BINARY_DIR}/${LIBRARY_DIRECTORY}" ${${LIBNAME}_INCLUDE_DIRECTORY_LIST})

endmacro()

DOWNLOAD_LIBRARY_INCLUDE_FILES("bullet" "https://www.dropbox.com/s/bvtxtpqa925godz/BULLET-1.85_include.tar.gz?dl=0" "thirdparty/bullet/include")
DOWNLOAD_LIBRARY_INCLUDE_FILES("lua" "https://www.dropbox.com/s/ff3rvbdtfr1k56i/LIBLUA-5.3.2_include.tar.gz?dl=0" "thirdparty/lua/include")
DOWNLOAD_LIBRARY_INCLUDE_FILES("vorbis" "https://www.dropbox.com/s/f6l6iyq6o7fo72e/LIBVORBIS_1.3.5_include.tar.gz?dl=0" "thirdparty/vorbis/include")
DOWNLOAD_LIBRARY_INCLUDE_FILES("ogg" "https://www.dropbox.com/s/wm29ek4iifpkta2/LIBOGG_1.3.2_include.tar.gz?dl=0" "thirdparty/ogg/include")
DOWNLOAD_LIBRARY_INCLUDE_FILES("nanovg" "https://www.dropbox.com/s/e04zo6h8buc3ydo/LIBNANOVG_macOS.tar.gz?dl=0" "thirdparty/nanovg/include")



macro(DOWNLOAD_LIBRARY_BINARY_FILES LIBNAME LIBRARY_BINARY_URL LIBRARY_DIRECTORY)

  set(${LIBNAME}_URL_BINARY 
    "${LIBRARY_BINARY_URL}" 
    CACHE STRING "The URL for the include files for ${LIBRARY_DIRECTORY}")

  RETRIEVE_TAR(
    "${${LIBNAME}_URL_BINARY}"
    "${LIBRARY_DIRECTORY}"
    "SKIP"
    )

  MESSAGE(STATUS "library directory ${CMAKE_BINARY_DIR}/${LIBRARY_DIRECTORY}/Release/")
  file(GLOB_RECURSE ${LIBNAME}_RELEASE_BINARY_FILES
    ${CMAKE_BINARY_DIR}/${LIBRARY_DIRECTORY}/Release/*.a
    )

  MESSAGE(STATUS "_RELEASE_BINARY_FILES ${${LIBNAME}_RELEASE_BINARY_FILES}")

  foreach(BINARY_FILE ${${LIBNAME}_RELEASE_BINARY_FILES})
    string(FIND ${BINARY_FILE} "/" _IDXSLASH_ REVERSE)
    string(FIND ${BINARY_FILE} "." _IDXDOT_ REVERSE)

    MATH(EXPR _BEGIN_ "${_IDXSLASH_}+1")
    MATH(EXPR _LENGTH_ "${_IDXDOT_}-${_IDXSLASH_}-1")

    string(SUBSTRING ${BINARY_FILE} ${_BEGIN_} ${_LENGTH_} _LIB_NAME_)

    MESSAGE(STATUS "BINARY_FILE ${BINARY_FILE} - _LIB_NAME_ ${_LIB_NAME_}")

    add_library(${_LIB_NAME_}_LIBRARY STATIC IMPORTED )
    set_target_properties(${_LIB_NAME_}_LIBRARY PROPERTIES IMPORTED_LOCATION "${BINARY_FILE}")
    list(APPEND EXTRA_LIBS ${_LIB_NAME_}_LIBRARY)
  endforeach()

endmacro()

DOWNLOAD_LIBRARY_BINARY_FILES("bullet" "https://www.dropbox.com/s/cbmdirabylueukr/LIBBULLET_1.3.5_macOS.tar.gz?dl=0" "thirdparty/bullet/lib/macOS")
DOWNLOAD_LIBRARY_BINARY_FILES("lua" "https://www.dropbox.com/s/5wfx8rk9be4apni/LIBLUA-5.3.2_macOS.tar.gz?dl=0" "thirdparty/lua/lib/macOS")
DOWNLOAD_LIBRARY_BINARY_FILES("imgui" "https://www.dropbox.com/s/s6ombjjnb6or9xn/LIBIMGUI_1.5.0_macOS.tar.gz?dl=0" "thirdparty/imgui/lib/macOS")
DOWNLOAD_LIBRARY_BINARY_FILES("imguizmo" "https://www.dropbox.com/s/hppgmykw25k0xys/LIBIMGUIZMO_1.04_macOS.tar.gz?dl=0" "thirdparty/imguizmo/lib/macOS")
DOWNLOAD_LIBRARY_BINARY_FILES("jsoncpp" "https://www.dropbox.com/s/skh3zs3ps4lq797/LIBJSONCPP_1.8.0_macOS.tar.gz?dl=0" "thirdparty/jsoncpp/lib/macOS")
DOWNLOAD_LIBRARY_BINARY_FILES("nanovg" "https://www.dropbox.com/s/e04zo6h8buc3ydo/LIBNANOVG_macOS.tar.gz?dl=0" "thirdparty/nanovg/lib/macOS")
DOWNLOAD_LIBRARY_BINARY_FILES("ogg" "https://www.dropbox.com/s/59t9nblaagk1aid/LIBOGG_1.3.2_macOS.tar.gz?dl=0" "thirdparty/ogg/lib/macOS")


IF( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "fmod" )
  message(STATUS "need to add fmod lib")
ELSEIF( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "openal" )
  list(APPEND EXTRA_LIBS "-framework OpenAL")
ELSEIF( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "sdl" )
  message(STATUS "need to add sdl lib")
ENDIF()

list(APPEND EXTRA_LIBS "-framework OpenGL")
