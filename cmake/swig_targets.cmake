set(${CMAKE_PROJECT_NAME}_LUA_SWIG_ENABLED_BY_DEFAULT ON)
set(${CMAKE_PROJECT_NAME}_LUA_SWIG ${${CMAKE_PROJECT_NAME}_LUA_SWIG_ENABLED_BY_DEFAULT} CACHE BOOL "Build the swig module for ${CMAKE_PROJECT_NAME}")

list(APPEND CMAKE_MODULE_PATH "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake")

macro(LUA_BULLET_SWIG)
  set(CMAKE_SWIG_FLAGS "")

  file(GLOB_RECURSE LUA_SWIG_SOURCE_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/thirdparty/bullet3/*.swg
    )

  list(APPEND LUA_SWIG_SOURCE_FILES
    "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/thirdparty/bullet3/bullet3.i" 
  )

  SUBDIRLIST(SUBDIRS "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/thirdparty/bullet3" SWIGIN_SCRIPTS_INCLUDE_DIRECTORY_LIST)

  set(${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-includeall")
  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-fcompact")
  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-fvirtual")
  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-v")
  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-w201")
  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-w312")
  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-c++")

  foreach(_SWIG_SOURCE_FILE ${LUA_SWIG_SOURCE_FILES})
    MESSAGE(STATUS "_SWIG_SOURCE_FILE ${_SWIG_SOURCE_FILE}")
    set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY SWIG_FLAGS ${${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS})
    set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY CPLUSPLUS ON)
    set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY SWIG_INCLUDE_DIRECTORIES "${SWIGIN_SCRIPTS_INCLUDE_DIRECTORY_LIST}")
  endforeach()

  include_directories("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/thirdparty/bullet3" ${SWIGIN_SCRIPTS_INCLUDE_DIRECTORY_LIST})

  foreach(_SWIGIN_SCRIPTS_INCLUDE_DIRECTORY ${SWIGIN_SCRIPTS_INCLUDE_DIRECTORY_LIST})
    MESSAGE(STATUS "_SWIGIN_SCRIPTS_INCLUDE_DIRECTORY ${_SWIGIN_SCRIPTS_INCLUDE_DIRECTORY}")
  endforeach()

  swig_add_library(
    ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static
    TYPE STATIC
    LANGUAGE lua
    SOURCES "${LUA_SWIG_SOURCE_FILES}"
    OUTPUT_DIR ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua
    OUTFILE_DIR ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua
    )

  target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static PUBLIC BULLET3_SWIG=1 SWIG_TYPE_TABLE=myprojectname)

  TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static ${CMAKE_PROJECT_NAME}-static)

  list(APPEND EXTRA_LIBS ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static)
  list(APPEND INTERFACE_FILES ${LUA_SWIG_SOURCE_FILES})
endmacro()

macro(LUA_NJLI_SWIG)
  set(CMAKE_SWIG_FLAGS "")

  file(GLOB_RECURSE LUA_SWIG_SOURCE_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njli/*.swg
    )

  list(APPEND LUA_SWIG_SOURCE_FILES
    "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njli/njlic.i" 
  )

  SUBDIRLIST(SUBDIRS "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njli" SWIGIN_SCRIPTS_INCLUDE_DIRECTORY_LIST)

  set(${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-includeall")
  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-fcompact")
  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-fvirtual")
  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-v")
  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-w201")
  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-w312")
  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-c++")

  foreach(_SWIG_SOURCE_FILE ${LUA_SWIG_SOURCE_FILES})
    MESSAGE(STATUS "_SWIG_SOURCE_FILE ${_SWIG_SOURCE_FILE}")
    set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY SWIG_FLAGS ${${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS})
    set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY CPLUSPLUS ON)
    set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY SWIG_INCLUDE_DIRECTORIES "${SWIGIN_SCRIPTS_INCLUDE_DIRECTORY_LIST}")
  endforeach()

  include_directories("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njli" ${SWIGIN_SCRIPTS_INCLUDE_DIRECTORY_LIST})

  foreach(_SWIGIN_SCRIPTS_INCLUDE_DIRECTORY ${SWIGIN_SCRIPTS_INCLUDE_DIRECTORY_LIST})
    MESSAGE(STATUS "_SWIGIN_SCRIPTS_INCLUDE_DIRECTORY ${_SWIGIN_SCRIPTS_INCLUDE_DIRECTORY}")
  endforeach()

  swig_add_library(
    ${CMAKE_PROJECT_NAME}-lua-swig-njli-static
    TYPE STATIC
    LANGUAGE lua
    SOURCES "${LUA_SWIG_SOURCE_FILES}"
    OUTPUT_DIR ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua
    OUTFILE_DIR ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua
    )

  target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-njli-static PUBLIC NJLIC_SWIG=1 SWIG_TYPE_TABLE=myprojectname)

  TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME}-lua-swig-njli-static ${CMAKE_PROJECT_NAME}-static)

  list(APPEND EXTRA_LIBS ${CMAKE_PROJECT_NAME}-lua-swig-njli-static)
  list(APPEND INTERFACE_FILES ${LUA_SWIG_SOURCE_FILES})
endmacro()

if(${CMAKE_PROJECT_NAME}_LUA_SWIG)
  if(${CMAKE_VERSION} VERSION_LESS "3.11")
    message("Please consider to switch to CMake 3.11 in order to use SWIG")
  else()
    find_package(SWIG REQUIRED)

    if(${SWIG_FOUND})
      MESSAGE(STATUS "SWIG_FOUND ${SWIG_FOUND}")
      MESSAGE(STATUS "SWIG_DIR ${SWIG_DIR}")
      MESSAGE(STATUS "SWIG_EXECUTABLE ${SWIG_EXECUTABLE}")
      MESSAGE(STATUS "SWIG_VERSION ${SWIG_VERSION}")

      include(${SWIG_USE_FILE})

      LUA_NJLI_SWIG()
      LUA_BULLET_SWIG()

    endif()
  endif()
endif()
