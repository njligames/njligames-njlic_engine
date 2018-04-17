

set(${CMAKE_PROJECT_NAME}_SOUND_PLATFORM "openal" CACHE STRING "The rendering platform to use")
set(${CMAKE_PROJECT_NAME}_SOUND_PLATFORM_Values "openal;fmod;sdl")

if(EMSCRIPTEN)
  include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/emscripten_external_libraries.cmake")
  set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM "opengl_es_2" CACHE STRING "The rendering platform to use")
  set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM_Values "opengl_es_2;opengl_es_3")
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
  set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM "opengl_2" CACHE STRING "The rendering platform to use")
  set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM_Values "opengl_2;opengl_3")
elseif(APPLE)
  if(IOS)
    set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM "opengl_es_2" CACHE STRING "The rendering platform to use")
    set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM_Values "opengl_es_2;opengl_es_3")
    if(VR)
      include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/vr_ios_external_libraries.cmake")
    else()
      include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/ios_external_libraries.cmake")
    endif()
  elseif(TVOS)
    include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/appletv_external_libraries.cmake")
    set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM "opengl_es_2" CACHE STRING "The rendering platform to use")
    set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM_Values "opengl_es_2;opengl_es_3")
  else()
    set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM "opengl_2" CACHE STRING "The rendering platform to use")
    set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM_Values "opengl_2;opengl_3")
    if(OCULUS)
      include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/oculus_macos_external_libraries.cmake")
    else()
      include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/macos_external_libraries.cmake")
    endif()
  endif()
elseif(UNIX AND NOT APPLE AND NOT ANDROID)
  if(LINUX)
    set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM "opengl_2" CACHE STRING "The rendering platform to use")
    set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM_Values "opengl_2;opengl_3")
    if(OCULUS)
      include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/oculus_linux_external_libraries.cmake")
    else()
      include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/linux_external_libraries.cmake")
    endif()
  elseif(UNIX)
    include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/unix_external_libraries.cmake")
    set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM "opengl_2" CACHE STRING "The rendering platform to use")
    set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM_Values "opengl_2;opengl_3")
  endif()
elseif(ANDROID)
  set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM "opengl_es_2" CACHE STRING "The rendering platform to use")
  set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM_Values "opengl_es_2;opengl_es_3")
  if(VR)
    include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/vr_android_external_libraries.cmake")
  else()
    include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/android_external_libraries.cmake")
  endif()
endif()

set_property(CACHE ${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM PROPERTY STRINGS ${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM_Values})

IF( ${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM} STREQUAL "opengl_es_2" )
  ADD_DEFINITIONS(-D__GL_ES2__)
ELSEIF( ${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM} STREQUAL "opengl_es_3" )
  ADD_DEFINITIONS(-D__GL_ES3__)
ELSEIF( ${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM} STREQUAL "opengl_2" )
  ADD_DEFINITIONS(-D__GL_2__)
ELSEIF( ${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM} STREQUAL "opengl_3" )
  ADD_DEFINITIONS(-D__GL_3__)
ENDIF()

set_property(CACHE ${CMAKE_PROJECT_NAME}_SOUND_PLATFORM PROPERTY STRINGS ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM_Values})

IF( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "fmod" )
  ADD_DEFINITIONS(-DNJLI_SOUND_FMOD)
ELSEIF( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "openal" )
  ADD_DEFINITIONS(-DNJLI_SOUND_OPENAL)
ELSEIF( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "sdl" )
  ADD_DEFINITIONS(-DNJLI_SOUND_SDL)
ENDIF()

MESSAGE(STATUS "GRAPHICS_PLATFORM ${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM}")

IF( NOT ${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM} STREQUAL "opengl_es_2" )
  file(GLOB_RECURSE GL_SOURCE_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/graphics/opengl_es_2/${PLATFORM_DIR}/*.c
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/graphics/opengl_es_2/${PLATFORM_DIR}/*.cpp
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/graphics/opengl_es_2/${PLATFORM_DIR}/*.cxx
    )

  list(REMOVE_ITEM SOURCE_FILES ${GL_SOURCE_FILES})
  list(REMOVE_ITEM SOURCE_FILES ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/generated/swig/lua/opengl_es_2/lgl_es_2.cpp)
ENDIF()

IF( NOT ${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM} STREQUAL "opengl_es_3" )
  file(GLOB_RECURSE GL_SOURCE_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/graphics/opengl_es_3/${PLATFORM_DIR}/*.c
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/graphics/opengl_es_3/${PLATFORM_DIR}/*.cpp
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/graphics/opengl_es_3/${PLATFORM_DIR}/*.cxx
    )

  list(REMOVE_ITEM SOURCE_FILES ${GL_SOURCE_FILES})
  list(REMOVE_ITEM SOURCE_FILES ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/generated/swig/lua/opengl_es_3/lgl_es_3.cpp)
ENDIF()

IF( NOT ${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM} STREQUAL "opengl_2" )
  file(GLOB_RECURSE GL_SOURCE_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/graphics/opengl_2/${PLATFORM_DIR}/*.c
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/graphics/opengl_2/${PLATFORM_DIR}/*.cpp
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/graphics/opengl_2/${PLATFORM_DIR}/*.cxx
    )

  list(REMOVE_ITEM SOURCE_FILES ${GL_SOURCE_FILES})
  list(REMOVE_ITEM SOURCE_FILES ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/generated/swig/lua/opengl_2/lgl_2.cpp)
ENDIF()

IF( NOT ${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM} STREQUAL "opengl_3" )
  file(GLOB_RECURSE GL_SOURCE_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/graphics/opengl_3/${PLATFORM_DIR}/*.c
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/graphics/opengl_3/${PLATFORM_DIR}/*.cpp
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/graphics/opengl_3/${PLATFORM_DIR}/*.cxx
    )

  list(REMOVE_ITEM SOURCE_FILES ${GL_SOURCE_FILES})
  list(REMOVE_ITEM SOURCE_FILES ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/generated/swig/lua/opengl_3/lgl_3.cpp)
ENDIF()

include_directories(
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/generated/swig/lua
  )

OPTION(${CMAKE_PROJECT_NAME}_USE_NANOVG_LIBRARY "Use nanovg library" ON)
IF(${CMAKE_PROJECT_NAME}_USE_NANOVG_LIBRARY)
  ADD_DEFINITIONS(-DUSE_NANOVG_LIBRARY=1)
endif()

