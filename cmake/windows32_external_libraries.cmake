
message(STATUS "Platform is windows32 for project")

set(THIRDPARTY_BULLET3_DEBUG_WINDOWS32_URL    "https://www.dropbox.com/s/b5vk1nlvrep7trz/libbullet3_windows32_Debug.tar.gz?dl=0" CACHE STRING "The URL for library")
set(THIRDPARTY_BULLET3_RELEASE_WINDOWS32_URL  "https://www.dropbox.com/s/c4czumv892vvyp0/libbullet3_windows32_Release.tar.gz?dl=0"        CACHE STRING "The URL for library")

set(THIRDPARTY_IMGUI_DEBUG_WINDOWS32_URL      "https://www.dropbox.com/s/7cwy84q8yod6trr/libimgui_windows32_Debug.tar.gz?dl=0" CACHE STRING "The URL for library")
set(THIRDPARTY_IMGUI_RELEASE_WINDOWS32_URL    "https://www.dropbox.com/s/7tveus8vnqf3hbd/libimgui_windows32_Release.tar.gz?dl=0" CACHE STRING "The URL for library")

set(THIRDPARTY_IMGUIZMO_DEBUG_WINDOWS32_URL   "https://www.dropbox.com/s/6cl359lyi6a2g08/libImGuizmo_windows32_Debug.tar.gz?dl=0" CACHE STRING "The URL for library")
set(THIRDPARTY_IMGUIZMO_RELEASE_WINDOWS32_URL "https://www.dropbox.com/s/tbkqhseagh0yd7r/libImGuizmo_windows32_Release.tar.gz?dl=0" CACHE STRING "The URL for library")

set(THIRDPARTY_JSONCPP_DEBUG_WINDOWS32_URL    "https://www.dropbox.com/s/wedvjq1xy2gvyfq/libjsoncpp_windows32_Debug.tar.gz?dl=0" CACHE STRING "The URL for library")
set(THIRDPARTY_JSONCPP_RELEASE_WINDOWS32_URL  "https://www.dropbox.com/s/86top8muu8z6rb3/libjsoncpp_windows32_Release.tar.gz?dl=0" CACHE STRING "The URL for library")

set(THIRDPARTY_NANOVG_DEBUG_WINDOWS32_URL     "https://www.dropbox.com/s/u759rflaonqk320/libnanovg_windows32_Debug.tar.gz?dl=0" CACHE STRING "The URL for library")
set(THIRDPARTY_NANOVG_RELEASE_WINDOWS32_URL   "https://www.dropbox.com/s/652bxs9ic394e4t/libnanovg_windows32_Release.tar.gz?dl=0" CACHE STRING "The URL for library")

set(THIRDPARTY_OGG_DEBUG_WINDOWS32_URL        "https://www.dropbox.com/s/652bxs9ic394e4t/libnanovg_windows32_Release.tar.gz?dl=0" CACHE STRING "The URL for library")
set(THIRDPARTY_OGG_RELEASE_WINDOWS32_URL      "https://www.dropbox.com/s/0p7srknrepbltiq/libogg_windows32_Release.tar.gz?dl=0" CACHE STRING "The URL for library")

set(THIRDPARTY_VORBIS_DEBUG_WINDOWS32_URL     "https://www.dropbox.com/s/d4ksrmreonrwei9/libvorbis_windows32_Debug.tar.gz?dl=0" CACHE STRING "The URL for library")
set(THIRDPARTY_VORBIS_RELEASE_WINDOWS32_URL   "https://www.dropbox.com/s/sxh1v9z8sbcd15o/libvorbis_windows32_Release.tar.gz?dl=0" CACHE STRING "The URL for library")

# Bullet3 #########################################################################

DOWNLOAD_LIBRARY_TAR(
  "bullet3"
  "${THIRDPARTY_BULLET3_RELEASE_WINDOWS32_URL}"
  "thirdparty/bullet3/lib/windows32/Release"
  )
DOWNLOAD_LIBRARY_TAR(
  "bullet3"
  "${THIRDPARTY_BULLET3_DEBUG_WINDOWS32_URL}"
  "thirdparty/bullet3/lib/windows32/Debug"
  )

# ImGui #########################################################################

DOWNLOAD_LIBRARY_TAR(
  "imgui"
  "${THIRDPARTY_IMGUI_RELEASE_WINDOWS32_URL}"
  "thirdparty/imgui/lib/windows32/Release"
  )
DOWNLOAD_LIBRARY_TAR(
  "imgui"
  "${THIRDPARTY_IMGUI_DEBUG_WINDOWS32_URL}"
  "thirdparty/imgui/lib/windows32/Debug"
  )

# ImGuizmo #########################################################################

DOWNLOAD_LIBRARY_TAR(
  "imguizmo"
  "${THIRDPARTY_IMGUIZMO_RELEASE_WINDOWS32_URL}"
  "thirdparty/imguizmo/lib/windows32/Release"
  )
DOWNLOAD_LIBRARY_TAR(
  "imguizmo"
  "${THIRDPARTY_IMGUIZMO_DEBUG_WINDOWS32_URL}"
  "thirdparty/imguizmo/lib/windows32/Debug"
  )

# JsonCPP #########################################################################

DOWNLOAD_LIBRARY_TAR(
  "jsoncpp"
  "${THIRDPARTY_JSONCPP_RELEASE_WINDOWS32_URL}"
  "thirdparty/jsoncpp/lib/windows32/Release"
  )
DOWNLOAD_LIBRARY_TAR(
  "jsoncpp"
  "${THIRDPARTY_JSONCPP_DEBUG_WINDOWS32_URL}"
  "thirdparty/jsoncpp/lib/windows32/Debug"
  )

# NanoVG #########################################################################

DOWNLOAD_LIBRARY_TAR(
  "nanovg"
  "${THIRDPARTY_NANOVG_RELEASE_WINDOWS32_URL}"
  "thirdparty/nanovg/lib/windows32/Release"
  )
DOWNLOAD_LIBRARY_TAR(
  "nanovg"
  "${THIRDPARTY_NANOVG_DEBUG_WINDOWS32_URL}"
  "thirdparty/nanovg/lib/windows32/Debug"
  )

# OGG #########################################################################

DOWNLOAD_LIBRARY_TAR(
  "ogg"
  "${THIRDPARTY_OGG_RELEASE_WINDOWS32_URL}"
  "thirdparty/ogg/lib/windows32/Release"
  )
DOWNLOAD_LIBRARY_TAR(
  "ogg"
  "${THIRDPARTY_OGG_DEBUG_WINDOWS32_URL}"
  "thirdparty/ogg/lib/windows32/Debug"
  )

# Vorbis #########################################################################

DOWNLOAD_LIBRARY_TAR(
  "vorbis"
  "${THIRDPARTY_VORBIS_RELEASE_WINDOWS32_URL}"
  "thirdparty/vorbis/lib/windows32/Release"
  )
DOWNLOAD_LIBRARY_TAR(
  "vorbis"
  "${THIRDPARTY_VORBIS_DEBUG_WINDOWS32_URL}"
  "thirdparty/vorbis/lib/windows32/Debug"
  )

ADD_LIBRARIES(
  "${BULLET3_BINARY_FILENAMES}"
  "thirdparty/bullet3/lib/windows32/Release" 
  # "thirdparty/bullet3/lib/windows32/Debug\$(EFFECTIVE_PLATFORM_NAME)" 
  # "thirdparty/bullet3/lib/windows32/MinSizeRel\$(EFFECTIVE_PLATFORM_NAME)" 
  # "thirdparty/bullet3/lib/windows32/RelWithDebugInfo\$(EFFECTIVE_PLATFORM_NAME)" 
  )
foreach(LIBRARY_TARGET_NAME ${LIBRARY_TARGET_NAMES})
  list(APPEND EXTRA_LIBS ${LIBRARY_TARGET_NAME})
endforeach()

ADD_LIBRARIES(
  "${IMGUI_BINARY_FILENAMES}"
  "thirdparty/imgui/lib/windows32/Release" 
  # "thirdparty/imgui/lib/windows32/Debug\$(EFFECTIVE_PLATFORM_NAME)" 
  # "thirdparty/imgui/lib/windows32/MinSizeRel\$(EFFECTIVE_PLATFORM_NAME)" 
  # "thirdparty/imgui/lib/windows32/RelWithDebugInfo\$(EFFECTIVE_PLATFORM_NAME)" 
  )
foreach(LIBRARY_TARGET_NAME ${LIBRARY_TARGET_NAMES})
  list(APPEND EXTRA_LIBS ${LIBRARY_TARGET_NAME})
endforeach()

ADD_LIBRARIES(
  "${IMGUIZMO_BINARY_FILENAMES}"
  "thirdparty/imguizmo/lib/windows32/Release" 
  # "thirdparty/imguizmo/lib/windows32/Debug\$(EFFECTIVE_PLATFORM_NAME)" 
  # "thirdparty/imguizmo/lib/windows32/MinSizeRel\$(EFFECTIVE_PLATFORM_NAME)" 
  # "thirdparty/imguizmo/lib/windows32/RelWithDebugInfo\$(EFFECTIVE_PLATFORM_NAME)" 
  )
foreach(LIBRARY_TARGET_NAME ${LIBRARY_TARGET_NAMES})
  list(APPEND EXTRA_LIBS ${LIBRARY_TARGET_NAME})
endforeach()

ADD_LIBRARIES(
  "${JSONCPP_BINARY_FILENAMES}"
  "thirdparty/jsoncpp/lib/windows32/Release" 
  # "thirdparty/jsoncpp/lib/windows32/Debug\$(EFFECTIVE_PLATFORM_NAME)" 
  # "thirdparty/jsoncpp/lib/windows32/MinSizeRel\$(EFFECTIVE_PLATFORM_NAME)" 
  # "thirdparty/jsoncpp/lib/windows32/RelWithDebugInfo\$(EFFECTIVE_PLATFORM_NAME)" 
  )
foreach(LIBRARY_TARGET_NAME ${LIBRARY_TARGET_NAMES})
  list(APPEND EXTRA_LIBS ${LIBRARY_TARGET_NAME})
endforeach()

ADD_LIBRARIES(
  "${NANOVG_BINARY_FILENAMES}"
  "thirdparty/nanovg/lib/windows32/Release" 
  # "thirdparty/nanovg/lib/windows32/Debug\$(EFFECTIVE_PLATFORM_NAME)" 
  # "thirdparty/nanovg/lib/windows32/MinSizeRel\$(EFFECTIVE_PLATFORM_NAME)" 
  # "thirdparty/nanovg/lib/windows32/RelWithDebugInfo\$(EFFECTIVE_PLATFORM_NAME)" 
  )
foreach(LIBRARY_TARGET_NAME ${LIBRARY_TARGET_NAMES})
  list(APPEND EXTRA_LIBS ${LIBRARY_TARGET_NAME})
endforeach()

ADD_LIBRARIES(
  "${OGG_BINARY_FILENAMES}"
  "thirdparty/ogg/lib/windows32/Release" 
  # "thirdparty/ogg/lib/windows32/Debug\$(EFFECTIVE_PLATFORM_NAME)" 
  # "thirdparty/ogg/lib/windows32/MinSizeRel\$(EFFECTIVE_PLATFORM_NAME)" 
  # "thirdparty/ogg/lib/windows32/RelWithDebugInfo\$(EFFECTIVE_PLATFORM_NAME)" 
  )
foreach(LIBRARY_TARGET_NAME ${LIBRARY_TARGET_NAMES})
  list(APPEND EXTRA_LIBS ${LIBRARY_TARGET_NAME})
endforeach()

ADD_LIBRARIES(
  "${VORBIS_BINARY_FILENAMES}"
  "thirdparty/vorbis/lib/windows32/Release" 
  # "thirdparty/vorbis/lib/windows32/Debug\$(EFFECTIVE_PLATFORM_NAME)" 
  # "thirdparty/vorbis/lib/windows32/MinSizeRel\$(EFFECTIVE_PLATFORM_NAME)" 
  # "thirdparty/vorbis/lib/windows32/RelWithDebugInfo\$(EFFECTIVE_PLATFORM_NAME)" 
  )
foreach(LIBRARY_TARGET_NAME ${LIBRARY_TARGET_NAMES})
  list(APPEND EXTRA_LIBS ${LIBRARY_TARGET_NAME})
endforeach()

if( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "fmod" )
  message(STATUS "need to add fmod lib")
elseif( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "openal" )
  set(THIRDPARTY_OPENAL_WINDOWS32_URL "https://www.dropbox.com/s/rcnf3j6nw3s9gjd/libopenal_win32.tar.gz?dl=0" CACHE STRING "The URL for library")
  set(THIRDPARTY_OPENAL_INCLUDE_URL "https://www.dropbox.com/s/ykhm0omt23ocevh/libopenal_include.tar.gz?dl=0" CACHE STRING "The URL for library")

  set(OPENAL_INCLUDE_DIRECTORY "thirdparty/openal/include")

  DOWNLOAD_LIBRARY_INCLUDE_FILES("openal" "${THIRDPARTY_OPENAL_INCLUDE_URL}" ${OPENAL_INCLUDE_DIRECTORY})

  DOWNLOAD_LIBRARY_TAR(
    "openal"
    "${THIRDPARTY_OPENAL_WINDOWS32_URL}"
    "thirdparty/openal/lib/openal"
    )
  ADD_LIBRARIES(
    "${OPENAL_BINARY_FILENAMES}"
    "thirdparty/openal/lib/windows32" 
    )
  foreach(LIBRARY_TARGET_NAME ${LIBRARY_TARGET_NAMES})
    list(APPEND EXTRA_LIBS ${LIBRARY_TARGET_NAME})
  endforeach()

elseif( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "sdl" )
  message(STATUS "need to add sdl lib")
endif()

find_package(OpenGL REQUIRED)
list(APPEND EXTRA_LIBS ${OPENGL_LIBRARIES})
include_directories(${OPENGL_INCLUDE_DIR})


