macro(REMOVE_PLATFORM_FILES PLATFORM_DIR)

  file(GLOB_RECURSE PLATFORM_SOURCE_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/platform/${PLATFORM_DIR}/*.c
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/platform/${PLATFORM_DIR}/*.cpp
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/platform/${PLATFORM_DIR}/*.cxx
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/platform/${PLATFORM_DIR}/*.m
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/platform/${PLATFORM_DIR}/*.mm
    )

  file(GLOB_RECURSE PLATFORM_INCLUDE_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/platform/${PLATFORM_DIR}/*.h
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/platform/${PLATFORM_DIR}/*.hpp
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/platform/${PLATFORM_DIR}/*.hxx
    )

  if(PLATFORM_SOURCE_FILES)
    list(REMOVE_ITEM SOURCE_FILES ${PLATFORM_SOURCE_FILES})
  endif()
  if(PLATFORM_INCLUDE_FILES)
    list(REMOVE_ITEM INCLUDE_FILES ${PLATFORM_INCLUDE_FILES})
  endif()
  list(REMOVE_ITEM NJLI_INCLUDE_DIRECTORY_LIST ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/platform/${PLATFORM_DIR})

endmacro()

# General source files
file(GLOB_RECURSE SOURCE_FILES
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/*.c
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/*.cpp
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/*.cxx
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/*.m
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/*.mm
  )

file(GLOB MAIN_FILES
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/platform/main.cpp
  )

file(GLOB_RECURSE INCLUDE_FILES
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/*.h
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/*.hpp
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/*.hxx

  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/bullet/*.h
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/bullet/*.hpp
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/bullet/*.hxx

  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/sdl2_test/*.h
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/sdl2_test/*.hpp
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/sdl2_test/*.hxx
  
  # ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/*.h
  # ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/*.hpp
  # ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/*.hxx
  
  )

SUBDIRLIST(SUBDIRS "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli" NJLI_INCLUDE_DIRECTORY_LIST)
SUBDIRLIST(SUBDIRS "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/bullet" BULLET_INCLUDE_DIRECTORY_LIST)
SUBDIRLIST(SUBDIRS "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/sdl2_test" SDL2_INCLUDE_DIRECTORY_LIST)
# SUBDIRLIST(SUBDIRS "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua" LUA_INCLUDE_DIRECTORY_LIST)

set(${CMAKE_PROJECT_NAME}_SOUND_PLATFORM "openal" CACHE STRING "The rendering platform to use")
set(${CMAKE_PROJECT_NAME}_SOUND_PLATFORM_Values "openal;fmod;sdl")

if(EMSCRIPTEN)
  # REMOVE_PLATFORM_FILES("emscripten")
  REMOVE_PLATFORM_FILES("windows")
  REMOVE_PLATFORM_FILES("ios")
  REMOVE_PLATFORM_FILES("appletv")
  REMOVE_PLATFORM_FILES("macOS")
  REMOVE_PLATFORM_FILES("linux")
  REMOVE_PLATFORM_FILES("unix")
  REMOVE_PLATFORM_FILES("android")
  REMOVE_PLATFORM_FILES("applewatchos")
  set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM "opengl_es_2" CACHE STRING "The rendering platform to use")
  set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM_Values "opengl_es_2;opengl_es_3")
elseif(WINDOWS)
  REMOVE_PLATFORM_FILES("emscripten")
  # REMOVE_PLATFORM_FILES("windows")
  REMOVE_PLATFORM_FILES("ios")
  REMOVE_PLATFORM_FILES("appletv")
  REMOVE_PLATFORM_FILES("macOS")
  REMOVE_PLATFORM_FILES("linux")
  REMOVE_PLATFORM_FILES("unix")
  REMOVE_PLATFORM_FILES("android")
  REMOVE_PLATFORM_FILES("applewatchos")
  set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM "opengl_2" CACHE STRING "The rendering platform to use")
  set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM_Values "opengl_2;opengl_3")
elseif(APPLE)
  if(IOS)
    REMOVE_PLATFORM_FILES("emscripten")
    REMOVE_PLATFORM_FILES("windows")
    # REMOVE_PLATFORM_FILES("ios")
    REMOVE_PLATFORM_FILES("appletv")
    REMOVE_PLATFORM_FILES("macOS")
    REMOVE_PLATFORM_FILES("linux")
    REMOVE_PLATFORM_FILES("unix")
    REMOVE_PLATFORM_FILES("android")
    REMOVE_PLATFORM_FILES("applewatchos")
    set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM "opengl_es_2" CACHE STRING "The rendering platform to use")
    set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM_Values "opengl_es_2;opengl_es_3")
  elseif(TVOS)
    REMOVE_PLATFORM_FILES("emscripten")
    REMOVE_PLATFORM_FILES("windows")
    REMOVE_PLATFORM_FILES("ios")
    # REMOVE_PLATFORM_FILES("appletv")
    REMOVE_PLATFORM_FILES("macOS")
    REMOVE_PLATFORM_FILES("linux")
    REMOVE_PLATFORM_FILES("unix")
    REMOVE_PLATFORM_FILES("android")
    REMOVE_PLATFORM_FILES("applewatchos")
    set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM "opengl_es_2" CACHE STRING "The rendering platform to use")
    set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM_Values "opengl_es_2;opengl_es_3")
  else()
    REMOVE_PLATFORM_FILES("emscripten")
    REMOVE_PLATFORM_FILES("windows")
    REMOVE_PLATFORM_FILES("ios")
    REMOVE_PLATFORM_FILES("appletv")
    # REMOVE_PLATFORM_FILES("macOS")
    REMOVE_PLATFORM_FILES("linux")
    REMOVE_PLATFORM_FILES("unix")
    REMOVE_PLATFORM_FILES("android")
    REMOVE_PLATFORM_FILES("applewatchos")
    set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM "opengl_2" CACHE STRING "The rendering platform to use")
    set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM_Values "opengl_2;opengl_3")
  endif()
elseif(UNIX AND NOT APPLE AND NOT ANDROID)
  if(LINUX)
    REMOVE_PLATFORM_FILES("emscripten")
    REMOVE_PLATFORM_FILES("windows")
    REMOVE_PLATFORM_FILES("ios")
    REMOVE_PLATFORM_FILES("appletv")
    REMOVE_PLATFORM_FILES("macOS")
    # REMOVE_PLATFORM_FILES("linux")
    REMOVE_PLATFORM_FILES("unix")
    REMOVE_PLATFORM_FILES("android")
    REMOVE_PLATFORM_FILES("applewatchos")
    set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM "opengl_2" CACHE STRING "The rendering platform to use")
    set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM_Values "opengl_2;opengl_3")
  elseif(UNIX)
    REMOVE_PLATFORM_FILES("emscripten")
    REMOVE_PLATFORM_FILES("windows")
    REMOVE_PLATFORM_FILES("ios")
    REMOVE_PLATFORM_FILES("appletv")
    REMOVE_PLATFORM_FILES("macOS")
    REMOVE_PLATFORM_FILES("linux")
    # REMOVE_PLATFORM_FILES("unix")
    REMOVE_PLATFORM_FILES("android")
    REMOVE_PLATFORM_FILES("applewatchos")
    set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM "opengl_2" CACHE STRING "The rendering platform to use")
    set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM_Values "opengl_2;opengl_3")
  endif()
elseif(ANDROID)
  REMOVE_PLATFORM_FILES("emscripten")
  REMOVE_PLATFORM_FILES("windows")
  REMOVE_PLATFORM_FILES("ios")
  REMOVE_PLATFORM_FILES("appletv")
  REMOVE_PLATFORM_FILES("macOS")
  REMOVE_PLATFORM_FILES("linux")
  REMOVE_PLATFORM_FILES("unix")
  # REMOVE_PLATFORM_FILES("android")
  REMOVE_PLATFORM_FILES("applewatchos")
  set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM "opengl_es_2" CACHE STRING "The rendering platform to use")
  set(${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM_Values "opengl_es_2;opengl_es_3")
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
  ADD_DEFINITIONS(-D__FMOD__)
ELSEIF( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "openal" )
  ADD_DEFINITIONS(-D__OPENAL__)
ELSEIF( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "sdl" )
  ADD_DEFINITIONS(-D__SDL__)
ENDIF()

IF( NOT ${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM} STREQUAL "opengl_es_2" )
  file(GLOB_RECURSE GL_ES_2_SOURCE_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/graphics/opengl_es_2/*.c
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/graphics/opengl_es_2/*.cpp
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/graphics/opengl_es_2/*.cxx

    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/generated/swig/lua/opengl_es_2/*.c
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/generated/swig/lua/opengl_es_2/*.cpp
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/generated/swig/lua/opengl_es_2/*.cxx
    )

  list(REMOVE_ITEM SOURCE_FILES ${GL_ES_2_SOURCE_FILES})
ENDIF()

IF( NOT ${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM} STREQUAL "opengl_es_3" )
  file(GLOB_RECURSE GL_ES_3_SOURCE_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/graphics/opengl_es_3/*.c
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/graphics/opengl_es_3/*.cpp
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/graphics/opengl_es_3/*.cxx

    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/generated/swig/lua/opengl_es_3/*.c
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/generated/swig/lua/opengl_es_3/*.cpp
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/generated/swig/lua/opengl_es_3/*.cxx
    )

  list(REMOVE_ITEM SOURCE_FILES ${GL_ES_3_SOURCE_FILES})
ENDIF()

IF( NOT ${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM} STREQUAL "opengl_2" )
  file(GLOB_RECURSE GL_2_SOURCE_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/graphics/opengl_2/*.c
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/graphics/opengl_2/*.cpp
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/graphics/opengl_2/*.cxx

    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/generated/swig/lua/opengl_2/*.c
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/generated/swig/lua/opengl_2/*.cpp
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/generated/swig/lua/opengl_2/*.cxx
    )

  list(REMOVE_ITEM SOURCE_FILES ${GL_2_SOURCE_FILES})
ENDIF()

IF( NOT ${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM} STREQUAL "opengl_3" )
  file(GLOB_RECURSE GL_3_SOURCE_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/graphics/opengl_3/*.c
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/graphics/opengl_3/*.cpp
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/graphics/opengl_3/*.cxx

    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/generated/swig/lua/opengl_3/*.c
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/generated/swig/lua/opengl_3/*.cpp
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/generated/swig/lua/opengl_3/*.cxx
    )

  list(REMOVE_ITEM SOURCE_FILES ${GL_3_SOURCE_FILES})
ENDIF()


IF( NOT ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "fmod" )
  file(GLOB_RECURSE FMOD_SOURCE_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/sound/fmod/*.c
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/sound/fmod/*.cpp
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/sound/fmod/*.cxx
    )

  list(REMOVE_ITEM SOURCE_FILES ${FMOD_SOURCE_FILES})
ENDIF()

IF( NOT ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "openal" )
  file(GLOB_RECURSE OPENAL_SOURCE_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/sound/openal/*.c
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/sound/openal/*.cpp
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/sound/openal/*.cxx
    )

  list(REMOVE_ITEM SOURCE_FILES ${OPENAL_SOURCE_FILES})
ENDIF()

IF( NOT ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "sdl" )
  file(GLOB_RECURSE SDL_SOURCE_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/sound/sdl/*.c
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/sound/sdl/*.cpp
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/sound/sdl/*.cxx
    )

  list(REMOVE_ITEM SOURCE_FILES ${SDL_SOURCE_FILES})
ENDIF()

# MUST BE AT THE END
# General includes
include_directories(
  ${${CMAKE_PROJECT_NAME}_BINARY_DIR}/include 
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli ${NJLI_INCLUDE_DIRECTORY_LIST} 
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/bullet ${BULLET_INCLUDE_DIRECTORY_LIST} 
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/sdl2_test ${SDL2_INCLUDE_DIRECTORY_LIST}
  # ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/exts ${LUA_INCLUDE_DIRECTORY_LIST}
  )
