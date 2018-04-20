
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

macro(DOWNLOAD_LIBRARY_INCLUDE_FILES LIBNAME LIBRARY_INCLUDE_URL LIBRARY_DIRECTORY)

  set(${LIBNAME}_URL_INCLUDE 
    "${LIBRARY_INCLUDE_URL}" 
    CACHE STRING "The URL for the include files for ${LIBRARY_DIRECTORY}")

  RETRIEVE_TAR(
    "${${LIBNAME}_URL_INCLUDE}"
    "${LIBRARY_DIRECTORY}"
    "SKIP"
    )

  SET(SUBDIRS "")
  SUBDIRLIST(SUBDIRS "${CMAKE_BINARY_DIR}/${LIBRARY_DIRECTORY}" ${LIBNAME}_INCLUDE_DIRECTORY_LIST)

  include_directories("${CMAKE_BINARY_DIR}/${LIBRARY_DIRECTORY}" ${${LIBNAME}_INCLUDE_DIRECTORY_LIST})

endmacro()


macro(DOWNLOAD_LIBRARY_BINARY_FILES LIBNAME LIBRARY_BINARY_URL LIBRARY_DIRECTORY)

  set(${LIBNAME}_URL_BINARY 
    "${LIBRARY_BINARY_URL}" 
    CACHE STRING "The URL for the include files for ${LIBRARY_DIRECTORY}")

  RETRIEVE_TAR(
    "${${LIBNAME}_URL_BINARY}"
    "${LIBRARY_DIRECTORY}"
    "SKIP"
    )

  MESSAGE(STATUS "library directory ${CMAKE_BINARY_DIR}/${LIBRARY_DIRECTORY}/Release/")
  file(GLOB_RECURSE ${LIBNAME}_RELEASE_BINARY_FILES
    ${CMAKE_BINARY_DIR}/${LIBRARY_DIRECTORY}/Release/*.a
    )

  MESSAGE(STATUS "_RELEASE_BINARY_FILES ${${LIBNAME}_RELEASE_BINARY_FILES}")

  foreach(BINARY_FILE ${${LIBNAME}_RELEASE_BINARY_FILES})
    string(FIND ${BINARY_FILE} "/" _IDXSLASH_ REVERSE)
    string(FIND ${BINARY_FILE} "." _IDXDOT_ REVERSE)

    MATH(EXPR _BEGIN_ "${_IDXSLASH_}+1")
    MATH(EXPR _LENGTH_ "${_IDXDOT_}-${_IDXSLASH_}-1")

    string(SUBSTRING ${BINARY_FILE} ${_BEGIN_} ${_LENGTH_} _LIB_NAME_)

    MESSAGE(STATUS "BINARY_FILE ${BINARY_FILE} - _LIB_NAME_ ${_LIB_NAME_}")

    add_library(${_LIB_NAME_}_LIBRARY STATIC IMPORTED )
    set_target_properties(${_LIB_NAME_}_LIBRARY PROPERTIES IMPORTED_LOCATION "${BINARY_FILE}")
    list(APPEND EXTRA_LIBS ${_LIB_NAME_}_LIBRARY)
  endforeach()

endmacro()
