
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

OPTION(${CMAKE_PROJECT_NAME}_USE_NANOVG_LIBRARY "Use nanovg library" ON)
IF(${CMAKE_PROJECT_NAME}_USE_NANOVG_LIBRARY)
  ADD_DEFINITIONS(-DUSE_NANOVG_LIBRARY=1)
endif()

if(EMSCRIPTEN)
  include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/emscripten_external_libraries.cmake")
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
elseif(APPLE)
  if(IOS)
    if(VR)
      include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/vr_ios_external_libraries.cmake")
    else()
      include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/ios_external_libraries.cmake")
    endif()
  elseif(TVOS)
    include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/appletv_external_libraries.cmake")
  else()
    if(OCULUS)
      include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/oculus_macos_external_libraries.cmake")
    else()
      include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/macos_external_libraries.cmake")
    endif()
  endif()
elseif(UNIX AND NOT APPLE AND NOT ANDROID)
  if(LINUX)
    if(OCULUS)
      include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/oculus_linux_external_libraries.cmake")
    else()
      include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/linux_external_libraries.cmake")
    endif()
  elseif(UNIX)
    include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/unix_external_libraries.cmake")
  endif()
elseif(ANDROID)
  if(VR)
    include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/vr_android_external_libraries.cmake")
  else()
    include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/android_external_libraries.cmake")
  endif()
endif()

