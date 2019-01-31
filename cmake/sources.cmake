# include(${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/macros.cmake)

set(NJLIC_INCLUDE_DIR "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}")
SUBDIRLIST(SUBDIRS "${NJLIC_INCLUDE_DIR}" NJLIC_INCLUDE_DIRS)

set(NJLIC_INCLUDE_DIRECTORIES "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli")
set(BULLET3_LOCAL_INCLUDE_DIRECTORIES "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/bullet3")
set(SDL2_LOCAL_INCLUDE_DIRECTORIES "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/sdl2_test")
set(LUA_ETC_LOCAL_INCLUDE_DIRECTORIES "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/lua/etc")
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
  )

file(GLOB_RECURSE EXTRA_SOURCE_FILES
  ${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES}/*.c
  ${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES}/*.cpp
  ${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES}/*.cxx
  ${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES}/*.m
  ${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES}/*.mm
  )

if(NOT WINDOWS)
  list(APPEND SOURCE_FILES ${EXTRA_SOURCE_FILES})
endif()

file(GLOB MAIN_FILES
  ${NJLIC_INCLUDE_DIRECTORIES}/platform/main.cpp
  )

list(REMOVE_ITEM SOURCE_FILES ${NJLIC_INCLUDE_DIRECTORIES}/platform/main.cpp)

file(GLOB_RECURSE INCLUDE_FILES
  ${NJLIC_INCLUDE_DIRECTORIES}/*.h
  ${NJLIC_INCLUDE_DIRECTORIES}/*.hpp
  ${NJLIC_INCLUDE_DIRECTORIES}/*.hxx

  ${BULLET3_LOCAL_INCLUDE_DIRECTORIES}/*.h
  ${BULLET3_LOCAL_INCLUDE_DIRECTORIES}/*.hpp
  ${BULLET3_LOCAL_INCLUDE_DIRECTORIES}/*.hxx

  ${SDL2_LOCAL_INCLUDE_DIRECTORIES}/*.h
  ${SDL2_LOCAL_INCLUDE_DIRECTORIES}/*.hpp
  ${SDL2_LOCAL_INCLUDE_DIRECTORIES}/*.hxx
  
  ${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/*.h
  ${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/*.hpp
  ${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/*.hxx
  
  
  )

file(GLOB_RECURSE EXTRA_INCLUDE_FILES
  ${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES}/*.h
  ${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES}/*.hpp
  ${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES}/*.hxx
  )

if(NOT WINDOWS)
  list(APPEND INCLUDE_FILES ${EXTRA_INCLUDE_FILES})
endif()

SUBDIRLIST(SUBDIRS "${NJLIC_INCLUDE_DIRECTORIES}" NJLIC_INCLUDE_DIRS)
SUBDIRLIST(SUBDIRS "${BULLET3_LOCAL_INCLUDE_DIRECTORIES}" BULLET3_LOCAL_INCLUDE_DIRECTORY_LIST)
SUBDIRLIST(SUBDIRS "${SDL2_LOCAL_INCLUDE_DIRECTORIES}" SDL2_LOCAL_INCLUDE_DIRECTORY_LIST)
SUBDIRLIST(SUBDIRS "${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}" LUA_SRC_LOCAL_INCLUDE_DIRECTORY_LIST)
if(NOT WINDOWS)
  SUBDIRLIST(SUBDIRS "${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES}" LUAEXTS_LOCAL_INCLUDE_DIRECTORY_LIST)
endif()






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

OPTION(__GL_ES2__ "GLES2 include" ${GL_ES2})
OPTION(__GL_ES3__ "GLES3 include" ${GL_ES3})
OPTION(__GL_2__ "GL2 include" ${GL_2})
OPTION(__GL_3__ "GL3 include" ${GL_3})

if(NOT THIRDPARTY_NANOVG_ENABLED)
  file(GLOB_RECURSE GL_NANOVG_INCLUDE_FILES
  ${NJLIC_INCLUDE_DIRECTORIES}/graphics/*HUD.h
  )

  list(REMOVE_ITEM INCLUDE_FILES ${GL_NANOVG_INCLUDE_FILES})
endif()

IF( NOT GL_ES2 )
  file(GLOB_RECURSE GL_ES_2_SOURCE_FILES
    ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_es_2/*.c
    ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_es_2/*.cpp
    ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_es_2/*.cxx

    ${NJLIC_INCLUDE_DIRECTORIES}/generated/swig/lua/opengl_es_2/*.c
    ${NJLIC_INCLUDE_DIRECTORIES}/generated/swig/lua/opengl_es_2/*.cpp
    ${NJLIC_INCLUDE_DIRECTORIES}/generated/swig/lua/opengl_es_2/*.cxx
    )

  list(REMOVE_ITEM SOURCE_FILES ${GL_ES_2_SOURCE_FILES})

ELSE()

  if(NOT THIRDPARTY_NANOVG_ENABLED)
    file(GLOB_RECURSE GL_ES_2_NANOVG_SOURCE_FILES
      ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_es_2/*HUD.cpp
      )

    list(REMOVE_ITEM SOURCE_FILES ${GL_ES_2_NANOVG_SOURCE_FILES})
  endif()

ENDIF()

IF( NOT GL_ES3 )
  file(GLOB_RECURSE GL_ES_3_SOURCE_FILES
    ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_es_3/*.c
    ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_es_3/*.cpp
    ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_es_3/*.cxx

    ${NJLIC_INCLUDE_DIRECTORIES}/generated/swig/lua/opengl_es_3/*.c
    ${NJLIC_INCLUDE_DIRECTORIES}/generated/swig/lua/opengl_es_3/*.cpp
    ${NJLIC_INCLUDE_DIRECTORIES}/generated/swig/lua/opengl_es_3/*.cxx
    )

  list(REMOVE_ITEM SOURCE_FILES ${GL_ES_3_SOURCE_FILES})

ELSE()

  if(NOT THIRDPARTY_NANOVG_ENABLED)
    file(GLOB_RECURSE GL_ES_3_NANOVG_SOURCE_FILES
      ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_es_3/*HUD.cpp
      )
    list(REMOVE_ITEM SOURCE_FILES ${GL_ES_3_NANOVG_SOURCE_FILES})
  endif()

ENDIF()

IF( NOT GL_2 )
  file(GLOB_RECURSE GL_2_SOURCE_FILES
    ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_2/*.c
    ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_2/*.cpp
    ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_2/*.cxx

    ${NJLIC_INCLUDE_DIRECTORIES}/generated/swig/lua/opengl_2/*.c
    ${NJLIC_INCLUDE_DIRECTORIES}/generated/swig/lua/opengl_2/*.cpp
    ${NJLIC_INCLUDE_DIRECTORIES}/generated/swig/lua/opengl_2/*.cxx
    )

  list(REMOVE_ITEM SOURCE_FILES ${GL_2_SOURCE_FILES})

ELSE()

  if(NOT THIRDPARTY_NANOVG_ENABLED)
    file(GLOB_RECURSE GL_2_NANOVG_SOURCE_FILES
      ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_2/*HUD.cpp
      )

    list(REMOVE_ITEM SOURCE_FILES ${GL_2_NANOVG_SOURCE_FILES})
  endif()
ENDIF()

IF( NOT GL_3 )
  file(GLOB_RECURSE GL_3_SOURCE_FILES
    ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_3/*.c
    ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_3/*.cpp
    ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_3/*.cxx

    ${NJLIC_INCLUDE_DIRECTORIES}/generated/swig/lua/opengl_3/*.c
    ${NJLIC_INCLUDE_DIRECTORIES}/generated/swig/lua/opengl_3/*.cpp
    ${NJLIC_INCLUDE_DIRECTORIES}/generated/swig/lua/opengl_3/*.cxx
    )

  list(REMOVE_ITEM SOURCE_FILES ${GL_3_SOURCE_FILES})

ELSE()

  if(NOT THIRDPARTY_NANOVG_ENABLED)
    file(GLOB_RECURSE GL_3_NANOVG_SOURCE_FILES
      ${NJLIC_INCLUDE_DIRECTORIES}/graphics/opengl_3/*HUD.cpp
      )

    list(REMOVE_ITEM SOURCE_FILES ${GL_3_NANOVG_SOURCE_FILES})
  endif()
ENDIF()

IF( NOT FMOD )
  file(GLOB_RECURSE FMOD_SOURCE_FILES
    ${NJLIC_INCLUDE_DIRECTORIES}/sound/fmod/*.c
    ${NJLIC_INCLUDE_DIRECTORIES}/sound/fmod/*.cpp
    ${NJLIC_INCLUDE_DIRECTORIES}/sound/fmod/*.cxx
    )

  list(REMOVE_ITEM SOURCE_FILES ${FMOD_SOURCE_FILES})
ENDIF()

IF( NOT OPENAL )
  file(GLOB_RECURSE OPENAL_SOURCE_FILES
    ${NJLIC_INCLUDE_DIRECTORIES}/sound/openal/*.c
    ${NJLIC_INCLUDE_DIRECTORIES}/sound/openal/*.cpp
    ${NJLIC_INCLUDE_DIRECTORIES}/sound/openal/*.cxx
    )

  list(REMOVE_ITEM SOURCE_FILES ${OPENAL_SOURCE_FILES})
ENDIF()

IF( NOT SDL_SOUND )
  file(GLOB_RECURSE SDL_SOUND_SOURCE_FILES
    ${NJLIC_INCLUDE_DIRECTORIES}/sound/sdl/*.c
    ${NJLIC_INCLUDE_DIRECTORIES}/sound/sdl/*.cpp
    ${NJLIC_INCLUDE_DIRECTORIES}/sound/sdl/*.cxx
    )

  list(REMOVE_ITEM SOURCE_FILES ${SDL_SOUND_SOURCE_FILES})
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

file(GLOB LUA_MAIN_FILES
  "${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/lua.c"
  )

file(GLOB LUAC_MAIN_FILES
  "${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/luac.c"
  )











## CONFIGURATION
# Default configuration (we assume POSIX by default)
set ( LUA_PATH "LUA_PATH" CACHE STRING "Environment variable to use as package.path." )
set ( LUA_CPATH "LUA_CPATH" CACHE STRING "Environment variable to use as package.cpath." )
set ( LUA_INIT "LUA_INIT" CACHE STRING "Environment variable for initial script." )

option ( LUA_BUILD_LUA "Build lua interpretter." ON )
option ( LUA_BUILD_LUAC "Build luac compiler." ON )

option ( LUA_USE_C89 "Use only C89 features." ON )
option ( LUA_USE_RELATIVE_LOADLIB "Use modified loadlib.c with support for relative paths on posix systems." ON )

option ( LUA_COMPAT_5_1 "Enable backwards compatibility options with lua-5.1." ON )
option ( LUA_COMPAT_5_2 "Enable backwards compatibility options with lua-5.2." ON )

#2DO: LUAI_* and LUAL_* settings, for now defaults are used.
set ( LUA_DIRSEP "/" )
set ( LUA_MODULE_SUFFIX ${CMAKE_SHARED_MODULE_SUFFIX} )
set ( LUA_LDIR ${INSTALL_LMOD} )
set ( LUA_CDIR ${INSTALL_CMOD} )

if ( LUA_USE_RELATIVE_LOADLIB )
  # This will set up relative paths to lib
  string ( REGEX REPLACE "[^!/]+" ".." LUA_DIR "!/${INSTALL_BIN}/" )
else ( )
  # Direct path to installation
  set ( LUA_DIR ${CMAKE_INSTALL_PREFIX} CACHE STRING "Destination from which modules will be resolved. See INSTALL_LMOD and INSTALL_CMOD." )
endif ( )

set ( LUA_PATH_DEFAULT "./?.lua;${LUA_DIR}${LUA_LDIR}/?.lua;${LUA_DIR}${LUA_LDIR}/?/init.lua" )
set ( LUA_CPATH_DEFAULT "./?${LUA_MODULE_SUFFIX};${LUA_DIR}${LUA_CDIR}/?${LUA_MODULE_SUFFIX};${LUA_DIR}${LUA_CDIR}/loadall${LUA_MODULE_SUFFIX}" )

if ( WIN32 AND NOT CYGWIN )
  # Windows systems
  option ( LUA_USE_WINDOWS "Windows specific build." ON )
  option ( LUA_BUILD_WLUA "Build wLua interpretter without console output." ON )
  option ( LUA_BUILD_AS_DLL "Build Lua library as Dll." ${BUILD_SHARED_LIBS} )

  # Paths (Double escapes needed)
  set ( LUA_DIRSEP "\\\\" )
  string ( REPLACE " /" ${LUA_DIRSEP} LUA_DIR "${LUA_DIR}" )
  string ( REPLACE "/" ${LUA_DIRSEP} LUA_LDIR "${LUA_LDIR}" )
  string ( REPLACE "/" ${LUA_DIRSEP} LUA_CDIR "${LUA_CDIR}" )
  string ( REPLACE "/" ${LUA_DIRSEP} LUA_PATH_DEFAULT "${LUA_PATH_DEFAULT}" )
  string ( REPLACE "/" ${LUA_DIRSEP} LUA_CPATH_DEFAULT "${LUA_CPATH_DEFAULT}" )
else ( )
  # Posix systems (incl. Cygwin)
  option ( LUA_USE_POSIX "Use POSIX features." ON )
  option ( LUA_USE_DLOPEN "Use dynamic linker to load modules." ON )
  # Apple and Linux specific
  if ( LINUX OR APPLE )
    option ( LUA_USE_AFORMAT "Assume 'printf' handles 'aA' specifiers" ON )
  endif ( )
endif ( )

configure_file("${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/luaconf.h.in"
  "${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/luaconf.h")


list(APPEND ${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES "${${CMAKE_PROJECT_NAME}_BINARY_DIR}/include")

list(APPEND ${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES "${NJLIC_INCLUDE_DIRECTORIES}")
list(APPEND ${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES "${NJLIC_INCLUDE_DIRS}")

list(APPEND ${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES "${BULLET3_LOCAL_INCLUDE_DIRECTORIES}")
list(APPEND ${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES "${BULLET3_LOCAL_INCLUDE_DIRECTORY_LIST}")

list(APPEND ${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES "${SDL2_LOCAL_INCLUDE_DIRECTORIES}")
list(APPEND ${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES "${SDL2_LOCAL_INCLUDE_DIRECTORY_LIST}")

list(APPEND ${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES "${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}")
list(APPEND ${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES "${LUA_SRC_LOCAL_INCLUDE_DIRECTORY_LIST}")

if(NOT WINDOWS)
  list(APPEND ${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES "${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES}")
  list(APPEND ${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES "${LUAEXTS_LOCAL_INCLUDE_DIRECTORY_LIST}")
endif()

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
