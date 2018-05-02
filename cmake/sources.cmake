include(${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/macros.cmake)

# General source files
file(GLOB_RECURSE SOURCE_FILES
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/*.c
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/*.cpp
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/*.cxx
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/*.m
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/*.mm

  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/src/*.c
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/src/*.cpp
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/src/*.cxx
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/src/*.m
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/src/*.mm

  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/exts/*.c
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/exts/*.cpp
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/exts/*.cxx
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/exts/*.m
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/exts/*.mm
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
  
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/src/*.h
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/src/*.hpp
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/src/*.hxx
  
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/exts/*.h
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/exts/*.hpp
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/exts/*.hxx
  
  )

SUBDIRLIST(SUBDIRS "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli" NJLI_INCLUDE_DIRECTORY_LIST)
SUBDIRLIST(SUBDIRS "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/bullet" BULLET_INCLUDE_DIRECTORY_LIST)
SUBDIRLIST(SUBDIRS "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/sdl2_test" SDL2_INCLUDE_DIRECTORY_LIST)
SUBDIRLIST(SUBDIRS "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/src" LUA_SRC_INCLUDE_DIRECTORY_LIST)
SUBDIRLIST(SUBDIRS "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/exts" LUA_EXTS_INCLUDE_DIRECTORY_LIST)

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


set(GL_ES2 OFF)
set(GL_ES3 OFF)
set(GL_2 OFF)
set(GL_3 OFF)

IF( "${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM}" STREQUAL "opengl_es_2" )
  set(GL_ES2 ON)
  list(APPEND ${CMAKE_PROJECT_NAME}_DEFINITIONS __GL_ES2__=1)
ELSEIF( "${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM}" STREQUAL "opengl_es_3" )
  set(GL_ES3 ON)
  list(APPEND ${CMAKE_PROJECT_NAME}_DEFINITIONS __GL_ES3__=1)
ELSEIF( "${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM}" STREQUAL "opengl_2" )
  set(GL_2 ON)
  list(APPEND ${CMAKE_PROJECT_NAME}_DEFINITIONS __GL_2__=1)
ELSEIF( "${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM}" STREQUAL "opengl_3" )
  set(GL_3 ON)
  list(APPEND ${CMAKE_PROJECT_NAME}_DEFINITIONS __GL_3__=1)
ENDIF()

option(__GL_ES2__ "GLES2 include" ${GL_ES2})
option(__GL_ES3__ "GLES3 include" ${GL_ES3})
option(__GL_2__ "GL2 include" ${GL_2})
option(__GL_3__ "GL3 include" ${GL_3})

set_property(CACHE ${CMAKE_PROJECT_NAME}_SOUND_PLATFORM PROPERTY STRINGS ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM_Values})


set(FMOD OFF)
set(OPENAL OFF)
set(SDL OFF)

IF( "${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM}" STREQUAL "fmod" )
  list(APPEND ${CMAKE_PROJECT_NAME}_DEFINITIONS __FMOD__=1)
  set(FMOD ON)
ELSEIF( "${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM}" STREQUAL "openal" )
  list(APPEND ${CMAKE_PROJECT_NAME}_DEFINITIONS __OPENAL__=1)
  set(OPENAL ON)
ELSEIF( "${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM}" STREQUAL "sdl" )
  list(APPEND ${CMAKE_PROJECT_NAME}_DEFINITIONS __SDL__=1)
  set(SDL ON)
ENDIF()

option(__FMOD__ "fmod include" ${FMOD})
option(__OPENAL__ "OpenAL include" ${OPENAL})
option(__SDL__ "SDL2 sound include" ${SDL})

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

LIST(REMOVE_ITEM INCLUDE_FILES
  "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/exts/luasocket/compat.h"
  "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/exts/luasocket/wsocket.h"
  )

LIST(REMOVE_ITEM SOURCE_FILES
  "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/exts/luasocket/compat.c"
  "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/exts/luasocket/wsocket.c"
  "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/src/loadlib_rel.c"
  "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/src/lua.c"
  "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/src/lua.rc"
  "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/src/luac.c"
  "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/src/luac.rc"
  "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/src/luaconf.h.in"
  "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/src/wmain.c"
)

# MUST BE AT THE END
# General includes
include_directories(
  ${${CMAKE_PROJECT_NAME}_BINARY_DIR}/include 
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli ${NJLI_INCLUDE_DIRECTORY_LIST} 
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/bullet ${BULLET_INCLUDE_DIRECTORY_LIST} 
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/sdl2_test ${SDL2_INCLUDE_DIRECTORY_LIST}
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/src ${LUA_SRC_INCLUDE_DIRECTORY_LIST}
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/exts ${LUA_EXTS_INCLUDE_DIRECTORY_LIST}
  )

