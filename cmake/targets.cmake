include(${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/macros.cmake)

set(${CMAKE_PROJECT_NAME}_SWIG_ENABLED_BY_DEFAULT ON)
set(${CMAKE_PROJECT_NAME}_SWIG ${${CMAKE_PROJECT_NAME}_SWIG_ENABLED_BY_DEFAULT} CACHE BOOL "Build the swig module for ${CMAKE_PROJECT_NAME}")

list(APPEND CMAKE_MODULE_PATH "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake")

if(${CMAKE_PROJECT_NAME}_SWIG)
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

      # file(GLOB_RECURSE SWIG_SOURCE_FILES
      #   ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/*.i
      #   )
      # foreach(_SWIG_SOURCE_FILE ${SWIG_SOURCE_FILES})
      #   MESSAGE(STATUS "_SWIG_SOURCE_FILE ${_SWIG_SOURCE_FILE}")
      # endforeach()

      # set(SWIG_LIBRARY_FILES "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njli/_LuaEntry.i")
      # file(APPEND SWIG_LIBRARY_FILES ${SOURCE_FILES})
      # set(SWIG_LIBRARY_FILES ${SOURCE_FILES})
      # file(APPEND SWIG_LIBRARY_FILES  "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njli/_LuaEntry.i")

      # set_property(SOURCE "${SWIG_LIBRARY_FILES}" PROPERTY CPLUSPLUS ON)
      # foreach(_SWIG_LIBRARY_FILE ${SWIG_LIBRARY_FILES})
      #   MESSAGE(STATUS "_SWIG_LIBRARY_FILE ${_SWIG_LIBRARY_FILE}")
      # endforeach()
      
      set_source_files_properties( "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njli/_LuaEntry.i" PROPERTIES SWIG_FLAGS "-fcompact")
      set_source_files_properties( "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njli/_LuaEntry.i" PROPERTIES SWIG_FLAGS "-fvirtual")
      set_source_files_properties( "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njli/_LuaEntry.i" PROPERTIES SWIG_FLAGS "-v")
      set_source_files_properties( "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njli/_LuaEntry.i" PROPERTIES SWIG_FLAGS "-w201")
      set_source_files_properties( "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njli/_LuaEntry.i" PROPERTIES SWIG_FLAGS "-w312")
      set_source_files_properties( "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njli/_LuaEntry.i" PROPERTIES SWIG_FLAGS "-c++")
      set_source_files_properties( "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njli/_LuaEntry.i" PROPERTIES SWIG_FLAGS "-includeall")
      set_source_files_properties( "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njli/_LuaEntry.i" PROPERTIES SWIG_FLAGS "-ignoremissing")
      # set_source_files_properties( "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njli/_LuaEntry.i" PROPERTIES SWIG_FLAGS "-features directors,autodoc=1")

      swig_add_library(
        ${CMAKE_PROJECT_NAME}-lua-static
        TYPE SHARED
        LANGUAGE lua
        SOURCES "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njli/_LuaEntry.i"
        OUTPUT_DIR ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua
        OUTFILE_DIR ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig/lua
      )
      ADD_DEFINITIONS(-DNJLIC_SWIG)

      SUBDIRLIST(SUBDIRS "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script" SWIGIN_SCRIPTS_INCLUDE_DIRECTORY_LIST)
      include_directories("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script" ${SWIGIN_SCRIPTS_INCLUDE_DIRECTORY_LIST})

      TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME}-lua-static ${CMAKE_PROJECT_NAME}-static)

    endif()
  endif()
endif()
