OPTION(THIRDPARTY_BULLET3_ENABLED "Use bullet3 library" ON)
mark_as_advanced(${THIRDPARTY_BULLET3_ENABLED})

OPTION(THIRDPARTY_DEBUGDRAW_ENABLED "Use DebugDraw library" ON)
mark_as_advanced(${THIRDPARTY_DEBUGDRAW_ENABLED})

OPTION(THIRDPARTY_GLM_ENABLED "Use GLM library" ON)
mark_as_advanced(${THIRDPARTY_GLM_ENABLED})

OPTION(THIRDPARTY_IMGUI_ENABLED "Use ImGui library" ON)
mark_as_advanced(${THIRDPARTY_IMGUI_ENABLED})

OPTION(THIRDPARTY_IMGUIZMO_ENABLED "Use ImGuizmo library" ON)
mark_as_advanced(${THIRDPARTY_IMGUIZMO_ENABLED})

OPTION(THIRDPARTY_JSONCPP_ENABLED "Use JsonCPP library" ON)
mark_as_advanced(${THIRDPARTY_JSONCPP_ENABLED})

OPTION(THIRDPARTY_NANOVG_ENABLED "Use Nanovg library" ON)
mark_as_advanced(${THIRDPARTY_NANOVG_ENABLED})

list(APPEND CMAKE_MODULE_PATH "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake")

IF(THIRDPARTY_BULLET3_ENABLED)
  add_definitions(-DUSE_BULLET3_LIBRARY)
  include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadBullet3.cmake")
  list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${BULLET3_INCLUDE_DIRS}")

  find_package(Bullet3 REQUIRED)
  list(APPEND EXTRA_LIBS ${BULLET3_TARGETS})
endif()

IF(THIRDPARTY_DEBUGDRAW_ENABLED)
  add_definitions(-DUSE_DEBUGDRAW_LIBRARY)
  include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadDebug-Draw.cmake")
  list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${DEBUG-DRAW_INCLUDE_DIRS}")

  find_package(Debug-Draw REQUIRED)
  list(APPEND EXTRA_LIBS ${DEBUG-DRAW_TARGETS})
  list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${DEBUG-DRAW_INCLUDE_DIR}")
endif()

IF(THIRDPARTY_GLM_ENABLED)
  add_definitions(-DUSE_GLM_LIBRARY)
  include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadGLM.cmake")
  list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${GLM_INCLUDE_DIRS}")

  find_package(GLM REQUIRED)
  list(APPEND EXTRA_LIBS ${GLM_TARGETS})
  list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${GLM_INCLUDE_DIR}")
endif()

IF(THIRDPARTY_IMGUI_ENABLED)
  add_definitions(-DUSE_IMGUI_LIBRARY)
  include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadImgui.cmake")
  list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${IMGUI_INCLUDE_DIRS}")

  find_package(ImGui REQUIRED)
  list(APPEND EXTRA_LIBS ${IMGUI_TARGETS})
endif()

IF(THIRDPARTY_IMGUIZMO_ENABLED)
  add_definitions(-DUSE_IMGUIZMO_LIBRARY)
  include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadImGuizmo.cmake")
  list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${IMGUIZMO_INCLUDE_DIRS}")

  find_package(ImGuizmo REQUIRED)
  list(APPEND EXTRA_LIBS ${IMGUIZMO_TARGETS})
endif()

IF(THIRDPARTY_JSONCPP_ENABLED)
  add_definitions(-DUSE_JSONCPP_LIBRARY)
  include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadJsonCPP.cmake")
  list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${JSONCPP_INCLUDE_DIRS}")

  find_package(JsonCPP REQUIRED)
  list(APPEND EXTRA_LIBS ${JSONCPP_TARGETS})
endif()

IF(THIRDPARTY_NANOVG_ENABLED)
  add_definitions(-DUSE_NANOVG_LIBRARY)
  include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadNanoVG.cmake")
  list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${NANOVG_INCLUDE_DIRS}")

  find_package(NanoVG REQUIRED)
  list(APPEND EXTRA_LIBS ${NANOVG_TARGETS})
endif()

if( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "fmod" )
  message(STATUS "need to add fmod lib")
elseif( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "openal" )

  add_definitions(-DUSE_OGG_LIBRARY)
  include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadOGG.cmake")
  list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${OGG_INCLUDE_DIRS}")

  find_package(OGG REQUIRED)
  list(APPEND EXTRA_LIBS ${OGG_TARGETS})


  add_definitions(-DUSE_VORBIS_LIBRARY)
  include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadVorbis.cmake")
  list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${VORBIS_INCLUDE_DIRS}")

  find_package(Vorbis REQUIRED)
  list(APPEND EXTRA_LIBS ${VORBIS_TARGETS})


  add_definitions(-DUSE_OPENAL_LIBRARY)
  include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadOpenAL.cmake")
  list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${OPENAL_INCLUDE_DIRS}")

  find_package(OpenAL REQUIRED)
  list(APPEND EXTRA_LIBS ${OPENAL_TARGETS})

elseif( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "sdl" )
  message(STATUS "need to add sdl lib")
endif()

if(EMSCRIPTEN)
  include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/emscripten_external_libraries.cmake")
elseif(WINDOWS)
  if(ARCH_64)
    if(OCULUS)
      include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/oculus_windows64_external_libraries.cmake")
    else()
      include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/windows64_external_libraries.cmake")
    endif()
  else()
    if(OCULUS)
      include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/oculus_windows32_external_libraries.cmake")
    else()
      include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/windows32_external_libraries.cmake")
    endif()
  endif()
elseif(APPLE)
  if(IOS)
    if(VR)
      include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/vr_ios_external_libraries.cmake")
    else()
      include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/ios_external_libraries.cmake")
    endif()
  elseif(TVOS)
    include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/appletv_external_libraries.cmake")
  else()
    if(OCULUS)
      include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/oculus_macos_external_libraries.cmake")
    else()
      include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/macos_external_libraries.cmake")
    endif()
  endif()
elseif(UNIX AND NOT APPLE AND NOT ANDROID)
  if(LINUX)
    if(OCULUS)
      include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/oculus_linux_external_libraries.cmake")
    else()
      include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/linux_external_libraries.cmake")
    endif()
  elseif(UNIX)
    include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/unix_external_libraries.cmake")
  endif()
elseif(ANDROID)
  if(VR)
    include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/vr_android_external_libraries.cmake")
  else()
    include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/android_external_libraries.cmake")
  endif()
endif()
