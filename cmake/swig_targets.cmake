set(${CMAKE_PROJECT_NAME}_LUA_SWIG_ENABLED_BY_DEFAULT ON)
set(${CMAKE_PROJECT_NAME}_LUA_SWIG ${${CMAKE_PROJECT_NAME}_LUA_SWIG_ENABLED_BY_DEFAULT} CACHE BOOL "Build the swig module for ${CMAKE_PROJECT_NAME}")

list(APPEND CMAKE_MODULE_PATH "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake")

macro(LUA_BULLET3_SWIG)
  if(NOT CMAKE_PROJECT_NAME)
    MESSAGE(FATAL_ERROR "CMAKE_PROJECT_NAME variable is empty.")
  endif()
  if(NOT ${CMAKE_PROJECT_NAME}_REPO_DIRECTORY)
    MESSAGE(FATAL_ERROR "${CMAKE_PROJECT_NAME}_REPO_DIRECTORY variable is empty.")
  endif()

  set(BULLET3_SWIG_DIRECTORY "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/thirdparty/bullet3")

  if(NOT BULLET3_SWIG_DIRECTORY)
    MESSAGE(FATAL_ERROR "BULLET3_SWIG_DIRECTORY variable is empty.")
  endif()
  if(NOT BULLET3_INCLUDE_DIR)
    MESSAGE(FATAL_ERROR "BULLET3_INCLUDE_DIR variable is empty.")
  endif()

  if(NOT EXISTS "${BULLET3_SWIG_DIRECTORY}")
    MESSAGE(FATAL_ERROR "Path doesn't exist: ${BULLET3_SWIG_DIRECTORY}")
  endif()
  if(NOT EXISTS "${BULLET3_INCLUDE_DIR}")
    MESSAGE(FATAL_ERROR "Path doesn't exist: ${BULLET3_INCLUDE_DIR}")
  endif()
  if(NOT EXISTS "${BULLET3_SWIG_DIRECTORY}/bullet3.i")
    MESSAGE(FATAL_ERROR "Path doesn't exist: ${BULLET3_SWIG_DIRECTORY}/bullet3.i")
  endif()

  set(CMAKE_SWIG_FLAGS "")

  file(GLOB_RECURSE LUA_SWIG_SOURCE_FILES
    "${BULLET3_SWIG_DIRECTORY}/*.swg"
    "${BULLET3_INCLUDE_DIR}" 
    )

  list(APPEND LUA_SWIG_SOURCE_FILES
    "${BULLET3_SWIG_DIRECTORY}/bullet3.i" 
  )

  SUBDIRLIST(SUBDIRS "${BULLET3_SWIG_DIRECTORY}" SWIGIN_SCRIPTS_INCLUDE_DIRS)

  set(${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-includeall")
  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-fcompact")
  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-fvirtual")
  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-v")
  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-w201")
  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-w312")
  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-ignoremissing")
  # list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-cpperraswarn")
  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-DBT_INFINITY")
  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-DSWIG_TYPE_TABLE=myprojectname")

  foreach(_SWIG_SOURCE_FILE ${LUA_SWIG_SOURCE_FILES})
    set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY SWIG_FLAGS ${${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS})
    set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY CPLUSPLUS ON)
    set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY SWIG_INCLUDE_DIRECTORIES "${SWIGIN_SCRIPTS_INCLUDE_DIRS}")
  endforeach()


  # include_directories("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njlic" 
  #   ${SWIGIN_SCRIPTS_INCLUDE_DIRS} 
  #   ${BULLET3_INCLUDE_DIR} 
  #   ${BULLET3_INCLUDE_DIRS}
  #   )
  include_directories("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njlic" 
    ${SWIGIN_SCRIPTS_INCLUDE_DIRS} 
    )

  # get_property(_INCLUDE_DIRECTORIES DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
  # foreach(_INCLUDE_DIRECTORY ${_INCLUDE_DIRECTORIES})
  #   MESSAGE(STATUS "BULLET_SWIG_INCLUDE_DIRECTORY ${_INCLUDE_DIRECTORY}")
  # endforeach()

  list(APPEND ${CMAKE_PROJECT_NAME}_DEFINITIONS BULLET3_SWIG=1 BT_INFINITY)


  #    ``CMAKE_SWIG_FLAGS``
  #    Add flags to all swig calls.
  #  
  #  ``CMAKE_SWIG_OUTDIR``
  #    Specify where to write the language specific files (swig ``-outdir`` option).
  #  
  #  ``SWIG_OUTFILE_DIR``
  #    Specify an output directory name where the generated source file will be
  #    placed.  If not specified, ``CMAKE_SWIG_OUTDIR`` is used.
  #  
  #  ``SWIG_MODULE_<name>_EXTRA_DEPS``
  #    Specify extra dependencies for the generated module for ``<name>``.

  set(CMAKE_SWIG_OUTDIR "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua")
  set(SWIG_OUTFILE_DIR "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua")

  if(${CMAKE_VERSION} VERSION_LESS "3.8")
    swig_add_module(
      ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static
      lua
      "${LUA_SWIG_SOURCE_FILES}"
      )
  else()
    swig_add_library(
      ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static
      TYPE STATIC
      LANGUAGE lua
      SOURCES "${LUA_SWIG_SOURCE_FILES}"
      )
  endif()

  if(ANDROID)
    if(TARGET main)
      add_dependencies(main ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static)
    endif()
  else()
    if(TARGET ${CMAKE_PROJECT_NAME}-exe)
      add_dependencies(${CMAKE_PROJECT_NAME}-exe ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static)
    endif()
  endif()

  target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})

  if(APPLE)
    if(IOS OR TVOS)
      SET_TARGET_PROPERTIES (
        ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static PROPERTIES
        XCODE_PRODUCT_TYPE "com.apple.product-type.library.static"
        )
    endif(IOS OR TVOS)
  endif()

  target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static ${CMAKE_PROJECT_NAME}-static)
  foreach(EXTRA_LIB ${EXTRA_LIBS})
    target_link_libraries( ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static optimized ${EXTRA_LIB})
  endforeach()
  target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static ${EXTRA_LDFLAGS})
  foreach(EXTRA_DEBUG_LIB ${EXTRA_DEBUG_LIBS})
    target_link_libraries( ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static debug ${EXTRA_DEBUG_LIB})
  endforeach()

  if(ANDROID)
    target_link_libraries( main ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static)
    target_compile_definitions(main PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})
  endif()

  list(APPEND EXTRA_LIBS ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static)
  list(APPEND INTERFACE_FILES ${LUA_SWIG_SOURCE_FILES})

  target_include_directories(${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static
    PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS}>
    PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES}>
    )
  if(NOT LINUX AND NOT EMSCRIPTEN AND NOT IOS AND NOT TVOS AND NOT ANDROID)
    set(CMAKE_SWIG_OUTDIR "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua")
    set(SWIG_OUTFILE_DIR "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua")

    if(${CMAKE_VERSION} VERSION_LESS "3.8")
      swig_add_module(
        ${CMAKE_PROJECT_NAME}-lua-swig-bullet3
        lua
        "${LUA_SWIG_SOURCE_FILES}"
        )
    else()
      swig_add_library(
        ${CMAKE_PROJECT_NAME}-lua-swig-bullet3
        TYPE MODULE
        LANGUAGE lua
        SOURCES "${LUA_SWIG_SOURCE_FILES}"
        )
    endif()

    # if(APPLE)
    #   if(IOS OR TVOS)
    #     SET_TARGET_PROPERTIES (
    #       ${CMAKE_PROJECT_NAME}-lua-swig-bullet3 PROPERTIES
    #       XCODE_PRODUCT_TYPE "com.apple.product-type.library.dynamic"
    #       )
    #   endif(IOS OR TVOS)
    # endif()
    target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-bullet3 PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})

    if(MSVC AND NOT LIBC)
      list(APPEND EXTRA_LIBS "msvcrt.lib")
      # Don't try to link with the default set of libraries.
      set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-bullet3 PROPERTIES LINK_FLAGS_RELEASE "/NODEFAULTLIB:LIBCMT")
      set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-bullet3 PROPERTIES LINK_FLAGS_DEBUG "/NODEFAULTLIB:LIBCMT")
      target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-bullet3 ${EXTRA_LDFLAGS} debug "msvcrtd.lib")
    endif()

    target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-bullet3 ${CMAKE_PROJECT_NAME}-static )
    foreach(EXTRA_LIB ${EXTRA_LIBS})
      target_link_libraries( ${CMAKE_PROJECT_NAME}-lua-swig-bullet3 optimized ${EXTRA_LIB})
    endforeach()
    target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-bullet3 ${EXTRA_LDFLAGS})
    foreach(EXTRA_DEBUG_LIB ${EXTRA_DEBUG_LIBS})
      target_link_libraries( ${CMAKE_PROJECT_NAME}-lua-swig-bullet3 debug ${EXTRA_DEBUG_LIB})
    endforeach()
  endif()

endmacro()

macro(LUA_NJLIC_SWIG)

  if(NOT CMAKE_PROJECT_NAME)
    MESSAGE(FATAL_ERROR "CMAKE_PROJECT_NAME variable is empty.")
  endif()

  if(NOT ${CMAKE_PROJECT_NAME}_REPO_DIRECTORY)
    MESSAGE(FATAL_ERROR "${CMAKE_PROJECT_NAME}_REPO_DIRECTORY variable is empty.")
  endif()

  set(NJLIC_SWIG_INCLUDE_DIR "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njlic")

  if(NOT NJLIC_SWIG_INCLUDE_DIR)
    MESSAGE(FATAL_ERROR "NJLIC_SWIG_INCLUDE_DIR variable is empty.")
  endif()

  if(NOT NJLIC_INCLUDE_DIR)
    MESSAGE(FATAL_ERROR "NJLIC_INCLUDE_DIR variable is empty.")
  endif()

  if(NOT EXISTS "${NJLIC_SWIG_INCLUDE_DIR}")
    MESSAGE(FATAL_ERROR "Path doesn't exist: ${NJLIC_SWIG_INCLUDE_DIR}")
  endif()
  if(NOT EXISTS "${NJLIC_INCLUDE_DIR}")
    MESSAGE(FATAL_ERROR "Path doesn't exist: ${NJLIC_INCLUDE_DIR}")
  endif()

  if(NOT EXISTS "${NJLIC_SWIG_INCLUDE_DIR}/njlic.i")
    MESSAGE(FATAL_ERROR "Path doesn't exist: ${NJLIC_SWIG_INCLUDE_DIR}/njlic.i")
  endif()

  configure_file("${NJLIC_SWIG_INCLUDE_DIR}/_Defines.swg.in"
    "${NJLIC_SWIG_INCLUDE_DIR}/_Defines.swg")

  file(GLOB_RECURSE LUA_SWIG_SOURCE_FILES
    ${NJLIC_SWIG_INCLUDE_DIR}/*.swg
    )

  list(APPEND LUA_SWIG_SOURCE_FILES
    "${NJLIC_SWIG_INCLUDE_DIR}/njlic.i" 
  )

  SUBDIRLIST(SUBDIRS "${NJLIC_SWIG_INCLUDE_DIR}" NJLIC_SWIG_INCLUDE_DIRS)
  list(APPEND NJLIC_SWIG_INCLUDE_DIRS ${NJLIC_INCLUDE_DIRS})

  set(CMAKE_SWIG_FLAGS "-includeall")
  list(APPEND CMAKE_SWIG_FLAGS "-fcompact")
  list(APPEND CMAKE_SWIG_FLAGS "-fvirtual")
  list(APPEND CMAKE_SWIG_FLAGS "-v")
  list(APPEND CMAKE_SWIG_FLAGS "-w201")
  list(APPEND CMAKE_SWIG_FLAGS "-w312")
  list(APPEND CMAKE_SWIG_FLAGS "-ignoremissing")
  # list(APPEND CMAKE_SWIG_FLAGS "-cpperraswarn")
  list(APPEND CMAKE_SWIG_FLAGS "-DBT_INFINITY")
  list(APPEND CMAKE_SWIG_FLAGS "-DSWIG_TYPE_TABLE=myprojectname")

  foreach(_SWIG_SOURCE_FILE ${LUA_SWIG_SOURCE_FILES})
    # set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY SWIG_FLAGS ${${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS})
    set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY CPLUSPLUS ON)
    set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY SWIG_INCLUDE_DIRECTORIES "${NJLIC_SWIG_INCLUDE_DIRS}")
  endforeach()

  include_directories(
    ${NJLIC_SWIG_INCLUDE_DIRS}
    ${BULLET3_INCLUDE_DIRS}
    )

  list(APPEND ${CMAKE_PROJECT_NAME}_DEFINITIONS NJLIC_SWIG=1 BT_INFINITY)

  set(CMAKE_SWIG_OUTDIR "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua")
  set(SWIG_OUTFILE_DIR "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua")

  if(${CMAKE_VERSION} VERSION_LESS "3.8")
    swig_add_module(
      ${CMAKE_PROJECT_NAME}-lua-swig-njlic-static
      lua
      "${LUA_SWIG_SOURCE_FILES}"
      )
  else()
    swig_add_library(
      ${CMAKE_PROJECT_NAME}-lua-swig-njlic-static
      TYPE STATIC
      LANGUAGE lua
      SOURCES "${LUA_SWIG_SOURCE_FILES}"
      )
  endif()

  if(ANDROID)
    if(TARGET main)
      add_dependencies(main ${CMAKE_PROJECT_NAME}-lua-swig-njlic-static)
    endif()
  else()
    if(TARGET ${CMAKE_PROJECT_NAME}-exe)
      add_dependencies(${CMAKE_PROJECT_NAME}-exe ${CMAKE_PROJECT_NAME}-lua-swig-njlic-static)
    endif()
  endif()

  if(APPLE)
    if(IOS OR TVOS)
      SET_TARGET_PROPERTIES (
        ${CMAKE_PROJECT_NAME}-lua-swig-njlic-static PROPERTIES
        XCODE_PRODUCT_TYPE "com.apple.product-type.library.static"
        )
    endif(IOS OR TVOS)
  endif()

  # target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-njlic-static PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})
  target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-njlic-static ${CMAKE_PROJECT_NAME}-static)
  if(ANDROID)
    target_link_libraries( main ${CMAKE_PROJECT_NAME}-lua-swig-njlic-static)
    target_compile_definitions(main PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})
  endif()
  list(APPEND EXTRA_LIBS ${CMAKE_PROJECT_NAME}-lua-swig-njlic-static)
  list(APPEND INTERFACE_FILES ${LUA_SWIG_SOURCE_FILES})

  target_include_directories(${CMAKE_PROJECT_NAME}-lua-swig-njlic-static
    PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS}>
    PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES}>
    )

  if(NOT LINUX AND NOT EMSCRIPTEN AND NOT IOS AND NOT TVOS AND NOT ANDROID)
    set(CMAKE_SWIG_OUTDIR "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua")
    set(SWIG_OUTFILE_DIR "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua")

    if(${CMAKE_VERSION} VERSION_LESS "3.8")
      swig_add_module(
        ${CMAKE_PROJECT_NAME}-lua-swig-njlic
        lua
        "${LUA_SWIG_SOURCE_FILES}"
        )
    else()
      swig_add_library(
        ${CMAKE_PROJECT_NAME}-lua-swig-njlic
        TYPE MODULE
        LANGUAGE lua
        SOURCES "${LUA_SWIG_SOURCE_FILES}"
        )
    endif()
    # target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-njlic PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})

    if(APPLE)
      set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-njlic PROPERTIES MACOSX_RPATH 1)
      # if(IOS OR TVOS)
      #   SET_TARGET_PROPERTIES (
      #     ${CMAKE_PROJECT_NAME}-lua-swig-njlic PROPERTIES
      #     XCODE_ATTRIBUTE_ENABLE_BITCODE "NO"
      #     XCODE_PRODUCT_TYPE "com.apple.product-type.library.dynamic"
      #     )
      # endif()
    elseif(UNIX AND NOT ANDROID)
      set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-njlic PROPERTIES
        VERSION ${LT_VERSION}
        SOVERSION ${LT_REVISION}
        OUTPUT_NAME "${CMAKE_PROJECT_NAME}-lua-swig-njlic-${LT_RELEASE}")
    else()
      # set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-njlic PROPERTIES
      #   VERSION ${${CMAKE_PROJECT_NAME}-lua-swig-njlic_VERSION}
      #   SOVERSION ${LT_REVISION}
      #   OUTPUT_NAME "${CMAKE_PROJECT_NAME}-lua-swig-njlic")
    endif()
    if(MSVC AND NOT LIBC)
      list(APPEND EXTRA_LIBS "msvcrt.lib")
      # Don't try to link with the default set of libraries.
      set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-njlic PROPERTIES LINK_FLAGS_RELEASE "/NODEFAULTLIB:LIBCMT")
      set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-njlic PROPERTIES LINK_FLAGS_DEBUG "/NODEFAULTLIB:LIBCMT")
      target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-njlic ${EXTRA_LDFLAGS} debug "msvcrtd.lib")
    endif()
    target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-njlic ${CMAKE_PROJECT_NAME}-static)

    target_include_directories(${CMAKE_PROJECT_NAME}-lua-swig-njlic
      PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS}>
      PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES}>
      )
  endif()

endmacro()

if(${CMAKE_PROJECT_NAME}_LUA_SWIG)
  if(${CMAKE_VERSION} VERSION_LESS "3.6")
    message("Please consider to switch to CMake 3.6 in order to use SWIG")
  else()
    find_package(SWIG REQUIRED)

    if(${SWIG_FOUND})
      MESSAGE(STATUS "SWIG_FOUND ${SWIG_FOUND}")
      MESSAGE(STATUS "SWIG_DIR ${SWIG_DIR}")
      MESSAGE(STATUS "SWIG_EXECUTABLE ${SWIG_EXECUTABLE}")
      MESSAGE(STATUS "SWIG_VERSION ${SWIG_VERSION}")

      include(${SWIG_USE_FILE})

      if(ANDROID)
        if(${ANDROID_ABI} STREQUAL "armeabi-v7a" OR ${ANDROID_ABI} STREQUAL "x86")
          include_directories(${ANDROID_SYSROOT}/usr/include/arm-linux-androideabi)
        elseif(${ANDROID_ABI} STREQUAL "arm64-v8a" OR ${ANDROID_ABI} STREQUAL "x86_64")
          include_directories(${ANDROID_SYSROOT}/usr/include/aarch64-linux-android)
        elseif(${ANDROID_ABI} STREQUAL "x86")
          include_directories(${ANDROID_SYSROOT}/usr/include/i686-linux-android)
        elseif(${ANDROID_ABI} STREQUAL "x86_64")
          include_directories(${ANDROID_SYSROOT}/usr/include/x86_64-linux-android)
        endif()

        include_directories(${${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS})
        include_directories(${${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES})
      endif()

      LUA_NJLIC_SWIG()
      LUA_BULLET3_SWIG()

      file(GLOB_RECURSE LUA_SWIG_GENERATED_FILES
        "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua/*.c*"
        )

      set_property(DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${LUA_SWIG_GENERATED_FILES})
      set_source_files_properties( ${LUA_SWIG_GENERATED_FILES} PROPERTIES GENERATED TRUE )
    endif()
  endif()
endif()
