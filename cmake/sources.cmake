include(${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/macros.cmake)

set(NJLIC_INCLUDE_DIRECTORIES "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli")
set(BULLET_LOCAL_INCLUDE_DIRECTORIES "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/bullet")
set(SDL2_LOCAL_INCLUDE_DIRECTORIES "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/sdl2_test")
set(LUA_SRC_LOCAL_INCLUDE_DIRECTORIES "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/src")
set(LUAEXTS_LOCAL_INCLUDE_DIRECTORIES "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/exts")



# General source files
file(GLOB_RECURSE SOURCE_FILES
  ${NJLIC_INCLUDE_DIRECTORIES}/*.c
  ${NJLIC_INCLUDE_DIRECTORIES}/*.cpp
  ${NJLIC_INCLUDE_DIRECTORIES}/*.cxx
  ${NJLIC_INCLUDE_DIRECTORIES}/*.m
  ${NJLIC_INCLUDE_DIRECTORIES}/*.mm

  ${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/*.c
  ${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/*.cpp
  ${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/*.cxx
  ${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/*.m
  ${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/*.mm

  ${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES}/*.c
  ${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES}/*.cpp
  ${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES}/*.cxx
  ${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES}/*.m
  ${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES}/*.mm
  )

file(GLOB MAIN_FILES
  ${NJLIC_INCLUDE_DIRECTORIES}/platform/main.cpp
  )

file(GLOB_RECURSE INCLUDE_FILES
  ${NJLIC_INCLUDE_DIRECTORIES}/*.h
  ${NJLIC_INCLUDE_DIRECTORIES}/*.hpp
  ${NJLIC_INCLUDE_DIRECTORIES}/*.hxx

  ${BULLET_LOCAL_INCLUDE_DIRECTORIES}/*.h
  ${BULLET_LOCAL_INCLUDE_DIRECTORIES}/*.hpp
  ${BULLET_LOCAL_INCLUDE_DIRECTORIES}/*.hxx

  ${SDL2_LOCAL_INCLUDE_DIRECTORIES}/*.h
  ${SDL2_LOCAL_INCLUDE_DIRECTORIES}/*.hpp
  ${SDL2_LOCAL_INCLUDE_DIRECTORIES}/*.hxx
  
  ${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/*.h
  ${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/*.hpp
  ${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/*.hxx
  
  ${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES}/*.h
  ${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES}/*.hpp
  ${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES}/*.hxx
  
  )

SUBDIRLIST(SUBDIRS "${NJLIC_INCLUDE_DIRECTORIES}" NJLIC_INCLUDE_DIRECTORY_LIST)
SUBDIRLIST(SUBDIRS "${BULLET_LOCAL_INCLUDE_DIRECTORIES}" BULLET_LOCAL_INCLUDE_DIRECTORY_LIST)
SUBDIRLIST(SUBDIRS "${SDL2_LOCAL_INCLUDE_DIRECTORIES}" SDL2_LOCAL_INCLUDE_DIRECTORY_LIST)
SUBDIRLIST(SUBDIRS "${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}" LUA_SRC_LOCAL_INCLUDE_DIRECTORY_LIST)
SUBDIRLIST(SUBDIRS "${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES}" LUAEXTS_LOCAL_INCLUDE_DIRECTORY_LIST)

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
  add_definitions(-D__GL_ES2__)
ELSEIF( "${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM}" STREQUAL "opengl_es_3" )
  set(GL_ES3 ON)
  add_definitions(-D__GL_ES3__)
ELSEIF( "${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM}" STREQUAL "opengl_2" )
  set(GL_2 ON)
  add_definitions(-D__GL_2__)
ELSEIF( "${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM}" STREQUAL "opengl_3" )
  set(GL_3 ON)
  add_definitions(-D__GL_3__)
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
  add_definitions(-D__FMOD__)
  set(FMOD ON)
ELSEIF( "${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM}" STREQUAL "openal" )
  add_definitions(-D__OPENAL__)
  set(OPENAL ON)
ELSEIF( "${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM}" STREQUAL "sdl" )
  add_definitions(-D__SDL__)
  set(SDL ON)
ENDIF()

option(__FMOD__ "fmod include" ${FMOD})
option(__OPENAL__ "OpenAL include" ${OPENAL})
option(__SDL__ "SDL2 sound include" ${SDL})

IF( NOT ${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM} STREQUAL "opengl_es_2" )
  file(GLOB_RECURSE GL_ES_2_SOURCE_FILES
    ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_es_2/*.c
    ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_es_2/*.cpp
    ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_es_2/*.cxx

    ${NJLIC_INCLUDE_DIRECTORIES}/generated/swig/lua/opengl_es_2/*.c
    ${NJLIC_INCLUDE_DIRECTORIES}/generated/swig/lua/opengl_es_2/*.cpp
    ${NJLIC_INCLUDE_DIRECTORIES}/generated/swig/lua/opengl_es_2/*.cxx
    )

  list(REMOVE_ITEM SOURCE_FILES ${GL_ES_2_SOURCE_FILES})
ENDIF()

IF( NOT ${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM} STREQUAL "opengl_es_3" )
  file(GLOB_RECURSE GL_ES_3_SOURCE_FILES
    ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_es_3/*.c
    ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_es_3/*.cpp
    ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_es_3/*.cxx

    ${NJLIC_INCLUDE_DIRECTORIES}/generated/swig/lua/opengl_es_3/*.c
    ${NJLIC_INCLUDE_DIRECTORIES}/generated/swig/lua/opengl_es_3/*.cpp
    ${NJLIC_INCLUDE_DIRECTORIES}/generated/swig/lua/opengl_es_3/*.cxx
    )

  list(REMOVE_ITEM SOURCE_FILES ${GL_ES_3_SOURCE_FILES})
ENDIF()

IF( NOT ${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM} STREQUAL "opengl_2" )
  file(GLOB_RECURSE GL_2_SOURCE_FILES
    ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_2/*.c
    ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_2/*.cpp
    ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_2/*.cxx

    ${NJLIC_INCLUDE_DIRECTORIES}/generated/swig/lua/opengl_2/*.c
    ${NJLIC_INCLUDE_DIRECTORIES}/generated/swig/lua/opengl_2/*.cpp
    ${NJLIC_INCLUDE_DIRECTORIES}/generated/swig/lua/opengl_2/*.cxx
    )

  list(REMOVE_ITEM SOURCE_FILES ${GL_2_SOURCE_FILES})
ENDIF()

IF( NOT ${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM} STREQUAL "opengl_3" )
  file(GLOB_RECURSE GL_3_SOURCE_FILES
    ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_3/*.c
    ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_3/*.cpp
    ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_3/*.cxx

    ${NJLIC_INCLUDE_DIRECTORIES}/generated/swig/lua/opengl_3/*.c
    ${NJLIC_INCLUDE_DIRECTORIES}/generated/swig/lua/opengl_3/*.cpp
    ${NJLIC_INCLUDE_DIRECTORIES}/generated/swig/lua/opengl_3/*.cxx
    )

  list(REMOVE_ITEM SOURCE_FILES ${GL_3_SOURCE_FILES})
ENDIF()

IF( NOT ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "fmod" )
  file(GLOB_RECURSE FMOD_SOURCE_FILES
    ${NJLIC_INCLUDE_DIRECTORIES}/sound/fmod/*.c
    ${NJLIC_INCLUDE_DIRECTORIES}/sound/fmod/*.cpp
    ${NJLIC_INCLUDE_DIRECTORIES}/sound/fmod/*.cxx
    )

  list(REMOVE_ITEM SOURCE_FILES ${FMOD_SOURCE_FILES})
ENDIF()

IF( NOT ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "openal" )
  file(GLOB_RECURSE OPENAL_SOURCE_FILES
    ${NJLIC_INCLUDE_DIRECTORIES}/sound/openal/*.c
    ${NJLIC_INCLUDE_DIRECTORIES}/sound/openal/*.cpp
    ${NJLIC_INCLUDE_DIRECTORIES}/sound/openal/*.cxx
    )

  list(REMOVE_ITEM SOURCE_FILES ${OPENAL_SOURCE_FILES})
ENDIF()

IF( NOT ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "sdl" )
  file(GLOB_RECURSE SDL_SOURCE_FILES
    ${NJLIC_INCLUDE_DIRECTORIES}/sound/sdl/*.c
    ${NJLIC_INCLUDE_DIRECTORIES}/sound/sdl/*.cpp
    ${NJLIC_INCLUDE_DIRECTORIES}/sound/sdl/*.cxx
    )

  list(REMOVE_ITEM SOURCE_FILES ${SDL_SOURCE_FILES})
ENDIF()

LIST(REMOVE_ITEM INCLUDE_FILES
  "${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES}/luasocket/compat.h"
  "${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES}/luasocket/wsocket.h"
  )

LIST(REMOVE_ITEM SOURCE_FILES
  "${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/loadlib_rel.c"
  "${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/lua.c"
  "${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/lua.rc"
  "${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/luac.c"
  "${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/luac.rc"
  "${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/luaconf.h.in"
  "${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/wmain.c"

  "${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES}/luasocket/compat.c"
  "${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES}/luasocket/wsocket.c"
)

# MUST BE AT THE END
# General includes

# include_directories(
#   ${${CMAKE_PROJECT_NAME}_BINARY_DIR}/include 
#   ${NJLIC_INCLUDE_DIRECTORIES} ${NJLIC_INCLUDE_DIRECTORY_LIST} 
#   ${BULLET_LOCAL_INCLUDE_DIRECTORIES} #${BULLET_LOCL_INCLUDE_DIRECTORY_LIST} 
#   ${SDL2_LOCAL_INCLUDE_DIRECTORIES} #${SDL2_LOCAL_INCLUDE_DIRECTORY_LIST}
#   ${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES} #${LUA_SRC_LOCAL_INCLUDE_DIRECTORY_LIST}
#   ${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES} ${LUAEXTS_LOCAL_INCLUDE_DIRECTORY_LIST}
#   )



list(APPEND ${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES "${${CMAKE_PROJECT_NAME}_BINARY_DIR}/include")

list(APPEND ${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES "${NJLIC_INCLUDE_DIRECTORIES}")
list(APPEND ${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES "${NJLIC_INCLUDE_DIRECTORY_LIST}")

list(APPEND ${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES "${BULLET_LOCAL_INCLUDE_DIRECTORIES}")
list(APPEND ${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES "${BULLET_LOCAL_INCLUDE_DIRECTORY_LIST}")

list(APPEND ${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES "${SDL2_LOCAL_INCLUDE_DIRECTORIES}")
list(APPEND ${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES "${SDL2_LOCAL_INCLUDE_DIRECTORY_LIST}")

list(APPEND ${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES "${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}")
list(APPEND ${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES "${LUA_SRC_LOCAL_INCLUDE_DIRECTORY_LIST}")

list(APPEND ${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES "${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES}")
list(APPEND ${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES "${LUAEXTS_LOCAL_INCLUDE_DIRECTORY_LIST}")

if(EMSCRIPTEN)
  list(APPEND ${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES
    $ENV{EMSCRIPTEN_LOCATION}/system/include
    $ENV{EMSCRIPTEN_LOCATION}/system/include/emscripten
  )
endif()

foreach(SOURCE_FILE ${SOURCE_FILES})
  # SET_SOURCE_FILES_PROPERTIES( ${SOURCE_FILE} PROPERTIES LANGUAGE "-x c++" )
  # SET_SOURCE_FILES_PROPERTIES( ${SOURCE_FILE} PROPERTIES LANGUAGE CXX )
   # MESSAGE(STATUS "SOURCE_FILE ${SOURCE_FILE}")
endforeach()
