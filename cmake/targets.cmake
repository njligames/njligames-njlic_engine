include(${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/macros.cmake)
include(${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/swig_targets.cmake)

if(NOT ANDROID AND NOT EMSCRIPTEN)
  include(${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/doxygen.cmake)
  set(CPPCHECK_FORMAT_BIN "/usr/local/bin/cppcheck" CACHE STRING "use: `brew install cppcheck` to install")
  set(CLANG_FORMAT_BIN "/usr/local/bin/clang-format" CACHE STRING "use: `brew install clang-format` to install")

  add_custom_target(
    cppcheck
    COMMAND ${CPPCHECK_FORMAT_BIN}
    --enable=warning,performance,portability,information,missingInclude
    --std=c++11
    --library=qt.cfg
    --template="{file},{line},{message},{callstack},{severity},{id}"
    --verbose
    ${SOURCE_FILES}
  )

  add_custom_target(
    clang-format
    COMMAND ${CLANG_FORMAT_BIN} -style=file -i ${SOURCE_FILES} -verbose
    SOURCES
    "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/.clang-format"
  )
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

  if(IOS)
    configure_file("${CMAKEIN_REPO_DIRECTORY}/platform.in/ios/FrameworkInfo.plist.in"
      "${CMAKE_BINARY_DIR}/Info.plist")
  elseif(TVOS)
    configure_file("${CMAKEIN_REPO_DIRECTORY}/platform.in/appletv/FrameworkInfo.plist.in"
      "${CMAKE_BINARY_DIR}/Info.plist")
  else()
    configure_file("${CMAKEIN_REPO_DIRECTORY}/platform.in/macOS/FrameworkInfo.plist.in"
      "${CMAKE_BINARY_DIR}/Info.plist")
  endif()

  add_library( ${CMAKE_PROJECT_NAME}Framework SHARED ${SOURCE_FILES} ${VERSION_SOURCES} ${INCLUDE_FILES})

  set_target_properties(${CMAKE_PROJECT_NAME}Framework PROPERTIES
    FRAMEWORK TRUE
    FRAMEWORK_VERSION C
    MACOSX_FRAMEWORK_IDENTIFIER com.njligames.${CMAKE_PROJECT_NAME}Framework.framework
    MACOSX_FRAMEWORK_INFO_PLIST ${CMAKE_BINARY_DIR}/Info.plist
    # "current version" in semantic format in Mach-O binary file
    VERSION 16.4.0
    # "compatibility version" in semantic format in Mach-O binary file
    SOVERSION ${${CMAKE_PROJECT_NAME}_VERSION}
    PUBLIC_HEADER ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/njli/platform/Engine.h
    XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
    )
  
  set(_INSTALL_LIBS "${CMAKE_PROJECT_NAME}Framework" ${_INSTALL_LIBS})
  target_include_directories(${CMAKE_PROJECT_NAME}Framework
    PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS}>
    PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES}>
    )

  target_link_libraries( ${CMAKE_PROJECT_NAME}Framework ${EXTRA_LDFLAGS} ${EXTRA_LIBS} )
endif()
