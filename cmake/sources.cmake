macro(PLATFORM_FILES PLATFORM_DIR SOURCE_FILES INCLUDE_FILES)
  file(GLOB_RECURSE ${SOURCE_FILES}
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/platform/${PLATFORM_DIR}/*.c
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/platform/${PLATFORM_DIR}/*.cpp
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/platform/${PLATFORM_DIR}/*.cxx
    )

  file(GLOB_RECURSE ${INCLUDE_FILES}
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/platform/${PLATFORM_DIR}/*.h
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/platform/${PLATFORM_DIR}/*.hpp
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/platform/${PLATFORM_DIR}/*.hxx
    )
endmacro(PLATFORM_FILES SOURCE_FILES INCLUDE_FILES)

# General source files
file(GLOB_RECURSE SOURCE_FILES
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/*.c
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/*.cpp
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/*.cxx
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

  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/sdl2/*.h
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/sdl2/*.hpp
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/sdl2/*.hxx
  )

SUBDIRLIST(SUBDIRS "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli" NJLI_INCLUDE_DIRECTORY_LIST)
SUBDIRLIST(SUBDIRS "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/bullet" BULLET_INCLUDE_DIRECTORY_LIST)
SUBDIRLIST(SUBDIRS "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/sdl2" SDL2_INCLUDE_DIRECTORY_LIST)

if(NOT EMSCRIPTEN)
  # remove emscripten platform files
  PLATFORM_FILES("emscripten" PLATFORM_SOURCE_FILES PLATFORM_INCLUDE_FILES)

  if(PLATFORM_SOURCE_FILES)
    list(REMOVE_ITEM SOURCE_FILES ${PLATFORM_SOURCE_FILES})
  endif()

  if(PLATFORM_INCLUDE_FILES)
    list(REMOVE_ITEM INCLUDE_FILES ${PLATFORM_INCLUDE_FILES})
  endif()

  list(REMOVE_ITEM NJLI_INCLUDE_DIRECTORY_LIST ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/platform/emscripten)
endif()

if(NOT WINDOWS)
  # remove windows platform files
  PLATFORM_FILES("windows" PLATFORM_SOURCE_FILES PLATFORM_INCLUDE_FILES)

  if(PLATFORM_SOURCE_FILES)
    list(REMOVE_ITEM SOURCE_FILES ${PLATFORM_SOURCE_FILES})
  endif()

  if(PLATFORM_INCLUDE_FILES)
    list(REMOVE_ITEM INCLUDE_FILES ${PLATFORM_INCLUDE_FILES})
  endif()

  list(REMOVE_ITEM NJLI_INCLUDE_DIRECTORY_LIST ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/platform/windows)
endif()

if(APPLE)
  if(NOT IOS)
    # remove ios platform files
    PLATFORM_FILES("ios" PLATFORM_SOURCE_FILES PLATFORM_INCLUDE_FILES)

    if(PLATFORM_SOURCE_FILES)
      list(REMOVE_ITEM SOURCE_FILES ${PLATFORM_SOURCE_FILES})
    endif()

    if(PLATFORM_INCLUDE_FILES)
      list(REMOVE_ITEM INCLUDE_FILES ${PLATFORM_INCLUDE_FILES})
    endif()

    list(REMOVE_ITEM NJLI_INCLUDE_DIRECTORY_LIST ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/platform/ios)
  endif()

  if(NOT TVOS)
    # remove tvos platform files
    PLATFORM_FILES("appletv" PLATFORM_SOURCE_FILES PLATFORM_INCLUDE_FILES)

    if(PLATFORM_SOURCE_FILES)
      list(REMOVE_ITEM SOURCE_FILES ${PLATFORM_SOURCE_FILES})
    endif()

    if(PLATFORM_INCLUDE_FILES)
      list(REMOVE_ITEM INCLUDE_FILES ${PLATFORM_INCLUDE_FILES})
    endif()

    list(REMOVE_ITEM NJLI_INCLUDE_DIRECTORY_LIST ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/platform/appletv)
  endif()

  if(TVOS OR IOS)
    # remove macos platform files
    PLATFORM_FILES("macOS" PLATFORM_SOURCE_FILES PLATFORM_INCLUDE_FILES)

    if(PLATFORM_SOURCE_FILES)
      list(REMOVE_ITEM SOURCE_FILES ${PLATFORM_SOURCE_FILES})
    endif()

    if(PLATFORM_INCLUDE_FILES)
      list(REMOVE_ITEM INCLUDE_FILES ${PLATFORM_INCLUDE_FILES})
    endif()

    list(REMOVE_ITEM NJLI_INCLUDE_DIRECTORY_LIST ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/platform/macOS)
  endif()
endif()

if(UNIX AND NOT APPLE AND NOT ANDROID)
  if(NOT LINUX)
    # remove linux platform files
    PLATFORM_FILES("linux" PLATFORM_SOURCE_FILES PLATFORM_INCLUDE_FILES)

    if(PLATFORM_SOURCE_FILES)
      list(REMOVE_ITEM SOURCE_FILES ${PLATFORM_SOURCE_FILES})
    endif()

    if(PLATFORM_INCLUDE_FILES)
      list(REMOVE_ITEM INCLUDE_FILES ${PLATFORM_INCLUDE_FILES})
    endif()

    list(REMOVE_ITEM NJLI_INCLUDE_DIRECTORY_LIST ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/platform/linux)
  endif()

  if(NOT UNIX)
    # remove unix platform files
    PLATFORM_FILES("unix" PLATFORM_SOURCE_FILES PLATFORM_INCLUDE_FILES)

    if(PLATFORM_SOURCE_FILES)
      list(REMOVE_ITEM SOURCE_FILES ${PLATFORM_SOURCE_FILES})
    endif()

    if(PLATFORM_INCLUDE_FILES)
      list(REMOVE_ITEM INCLUDE_FILES ${PLATFORM_INCLUDE_FILES})
    endif()

    list(REMOVE_ITEM NJLI_INCLUDE_DIRECTORY_LIST ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/platform/unix)
  endif()

endif()

if(NOT ANDROID)
  # remove android platform files
  PLATFORM_FILES("android" PLATFORM_SOURCE_FILES PLATFORM_INCLUDE_FILES)

  if(PLATFORM_SOURCE_FILES)
    list(REMOVE_ITEM SOURCE_FILES ${PLATFORM_SOURCE_FILES})
  endif()

  if(PLATFORM_INCLUDE_FILES)
    list(REMOVE_ITEM INCLUDE_FILES ${PLATFORM_INCLUDE_FILES})
  endif()

  list(REMOVE_ITEM NJLI_INCLUDE_DIRECTORY_LIST ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/platform/android)
endif()

# General includes
include_directories(
  ${${CMAKE_PROJECT_NAME}_BINARY_DIR}/include 
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli ${NJLI_INCLUDE_DIRECTORY_LIST} 
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/bullet ${BULLET_INCLUDE_DIRECTORY_LIST} 
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/sdl2 ${SDL2_INCLUDE_DIRECTORY_LIST}
  )

