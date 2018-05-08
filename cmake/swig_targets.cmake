set(${CMAKE_PROJECT_NAME}_LUA_SWIG_ENABLED_BY_DEFAULT ON)
set(${CMAKE_PROJECT_NAME}_LUA_SWIG ${${CMAKE_PROJECT_NAME}_LUA_SWIG_ENABLED_BY_DEFAULT} CACHE BOOL "Build the swig module for ${CMAKE_PROJECT_NAME}")

list(APPEND CMAKE_MODULE_PATH "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake")

#                macro(LUA_BULLET_SWIG)
#                  set(CMAKE_SWIG_FLAGS "")
#                
#                  file(GLOB_RECURSE LUA_SWIG_SOURCE_FILES
#                    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/thirdparty/bullet3/*.swg
#                    )
#                
#                  list(APPEND LUA_SWIG_SOURCE_FILES
#                    "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/thirdparty/bullet3/bullet3.i" 
#                  )
#                
#                  file(GLOB_RECURSE NJLIC_INCLUDE_SWIG_SOURCE_FILES
#                    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njlic/include/*.swg
#                    )
#                  list(APPEND LUA_SWIG_SOURCE_FILES
#                    "${NJLIC_INCLUDE_SWIG_SOURCE_FILES}" 
#                  )
#                
#                  SUBDIRLIST(SUBDIRS "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/thirdparty/bullet3" SWIGIN_SCRIPTS_INCLUDE_DIRECTORY_LIST)
#                
#                  set(${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-includeall")
#                  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-fcompact")
#                  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-fvirtual")
#                  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-v")
#                  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-w201")
#                  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-w312")
#                  list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-ignoremissing")
#                  # list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-cpperraswarn")
#                  # list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "BT_INFINITY")
#                  # list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-DSWIG_TYPE_TABLE=myprojectname")
#                  # list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-isystem")
#                
#                  list(APPEND ${CMAKE_PROJECT_NAME}_DEFINITIONS "BT_INFINITY")
#                  # IF( ${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM} STREQUAL "opengl_es_2" )
#                  #   list(APPEND ${CMAKE_PROJECT_NAME}_DEFINITIONS __GL_ES2__=1)
#                  # ELSEIF( ${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM} STREQUAL "opengl_es_3" )
#                  #   list(APPEND ${CMAKE_PROJECT_NAME}_DEFINITIONS __GL_ES3__=1)
#                  # ELSEIF( ${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM} STREQUAL "opengl_2" )
#                  #   list(APPEND ${CMAKE_PROJECT_NAME}_DEFINITIONS __GL_2__=1)
#                  # ELSEIF( ${${CMAKE_PROJECT_NAME}_GRAPHICS_PLATFORM} STREQUAL "opengl_3" )
#                  #   list(APPEND ${CMAKE_PROJECT_NAME}_DEFINITIONS __GL_3__=1)
#                  # ENDIF()
#                
#                  foreach(_SWIG_SOURCE_FILE ${LUA_SWIG_SOURCE_FILES})
#                    set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY SWIG_FLAGS ${${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS})
#                    set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY CPLUSPLUS ON)
#                    set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY SWIG_INCLUDE_DIRECTORIES "${SWIGIN_SCRIPTS_INCLUDE_DIRECTORY_LIST}")
#                  endforeach()
#                
#                  SUBDIRLIST(SUBDIRS "${CMAKE_BINARY_DIR}/${BULLET_INCLUDE_DIRECTORY}" BULLET_INCLUDE_DIRECTORY_LIST)
#                
#                  include_directories("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/thirdparty/bullet3" ${SWIGIN_SCRIPTS_INCLUDE_DIRECTORY_LIST} ${BULLET_INCLUDE_DIRECTORY_LIST})
#                
#                  swig_add_library(
#                    ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static
#                    TYPE STATIC
#                    LANGUAGE lua
#                    SOURCES "${LUA_SWIG_SOURCE_FILES}"
#                    OUTPUT_DIR ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua
#                    OUTFILE_DIR ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua
#                    )
#                  # set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua)
#                
#                  list(APPEND ${CMAKE_PROJECT_NAME}_DEFINITIONS BULLET_SWIG=1)
#                  target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})
#                
#                  target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static ${CMAKE_PROJECT_NAME}-static)
#                
#                  list(APPEND EXTRA_LIBS ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static)
#                  list(APPEND INTERFACE_FILES ${LUA_SWIG_SOURCE_FILES})
#                endmacro()

macro(LUA_NJLI_SWIG)
  set(CMAKE_SWIG_FLAGS "")

  SUBDIRLIST(SUBDIRS "${CMAKE_BINARY_DIR}/${BULLET_INCLUDE_DIRECTORY}" BULLET_INCLUDE_DIRECTORY_LIST)
  SUBDIRLIST(SUBDIRS "${CMAKE_BINARY_DIR}/${JSONCPP_INCLUDE_DIRECTORY}" JSONCPP_INCLUDE_DIRECTORY_LIST)

  configure_file("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njlic/_Defines.swg.in"
    "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njlic/_Defines.swg")

  file(GLOB_RECURSE LUA_SWIG_SOURCE_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njlic/*.swg
    "${CMAKE_BINARY_DIR}/${BULLET_INCLUDE_DIRECTORY}" 
    ${BULLET_INCLUDE_DIRECTORY_LIST}
    "${CMAKE_BINARY_DIR}/${JSONCPP_INCLUDE_DIRECTORY}" 
    ${JSONCPP_INCLUDE_DIRECTORY_LIST}
    "${CMAKE_BINARY_DIR}/${DEBUGDRAW_INCLUDE_DIRECTORY}" 
    # "${CMAKE_BINARY_DIR}/${GLM_INCLUDE_DIRECTORY}" 
    "${CMAKE_BINARY_DIR}/${NANOVG_INCLUDE_DIRECTORY}" 
    )

  list(APPEND LUA_SWIG_SOURCE_FILES
    "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njlic/njlic.i" 
  )

  SUBDIRLIST(SUBDIRS "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njlic" SWIGIN_SCRIPTS_INCLUDE_DIRECTORY_LIST)

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
  # list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-isystem")

  foreach(_SWIG_SOURCE_FILE ${LUA_SWIG_SOURCE_FILES})
    set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY SWIG_FLAGS ${${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS})
    set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY CPLUSPLUS ON)
    set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY SWIG_INCLUDE_DIRECTORIES "${SWIGIN_SCRIPTS_INCLUDE_DIRECTORY_LIST}")
  endforeach()


  include_directories("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njlic" 
    ${SWIGIN_SCRIPTS_INCLUDE_DIRECTORY_LIST} 

    "${CMAKE_BINARY_DIR}/${BULLET_INCLUDE_DIRECTORY}" 
    ${BULLET_INCLUDE_DIRECTORY_LIST}

    "${CMAKE_BINARY_DIR}/${JSONCPP_INCLUDE_DIRECTORY}" 
    # ${JSONCPP_INCLUDE_DIRECTORY_LIST}

    "${CMAKE_BINARY_DIR}/${DEBUGDRAW_INCLUDE_DIRECTORY}" 

    # "${CMAKE_BINARY_DIR}/${GLM_INCLUDE_DIRECTORY}" 

    "${CMAKE_BINARY_DIR}/${NANOVG_INCLUDE_DIRECTORY}" 

    ${NJLIC_INCLUDE_DIRECTORIES} ${NJLIC_INCLUDE_DIRECTORY_LIST} 
    ${BULLET_LOCAL_INCLUDE_DIRECTORIES} #${BULLET_LOCL_INCLUDE_DIRECTORY_LIST} 
    # ${SDL2_LOCAL_INCLUDE_DIRECTORIES} #${SDL2_LOCAL_INCLUDE_DIRECTORY_LIST}
    ${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES} #${LUA_SRC_LOCAL_INCLUDE_DIRECTORY_LIST}
    ${LUAEXTS_LOCAL_INCLUDE_DIRECTORIES} ${LUAEXTS_LOCAL_INCLUDE_DIRECTORY_LIST}
    )

  get_property(_INCLUDE_DIRECTORIES DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
  foreach(_INCLUDE_DIRECTORY ${_INCLUDE_DIRECTORIES})
    MESSAGE(STATUS "SWIG_INCLUDE_DIRECTORY ${_INCLUDE_DIRECTORY}")
  endforeach()

  swig_add_library(
    ${CMAKE_PROJECT_NAME}-lua-swig-njlic-static
    TYPE STATIC
    LANGUAGE lua
    SOURCES "${LUA_SWIG_SOURCE_FILES}"
    OUTPUT_DIR ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua
    OUTFILE_DIR ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua
    )
  #set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua)
  #set_property(DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua/njlicLUA_wrap.cxx")
 # set_property(DIRECTORY PROPERTY GENERATED "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua")

 SET_SOURCE_FILES_PROPERTIES( "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua/njlicLUA_wrap.cxx" PROPERTIES GENERATED TRUE )
 # SET_SOURCE_FILES_PROPERTIES( "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua/njlicLUA_wrap.cxx" PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES TRUE )
 SET_DIRECTORY_PROPERTIES(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "njlicLUA_wrap.cxx")

 #set_property(DIRECTORY APPEND PROPERTY GENERATED ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua)


  list(APPEND ${CMAKE_PROJECT_NAME}_DEFINITIONS NJLIC_SWIG=1 BT_INFINITY)
  target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-njlic-static PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})

  target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-njlic-static ${CMAKE_PROJECT_NAME}-static)

  list(APPEND EXTRA_LIBS ${CMAKE_PROJECT_NAME}-lua-swig-njlic-static)
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
      # LUA_BULLET_SWIG()

    endif()
  endif()
endif()
