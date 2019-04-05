include(${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/macros.cmake)
include(${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/swig_targets.cmake)

if(NOT ANDROID AND NOT EMSCRIPTEN)
  include(${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/doxygen.cmake)
  set(CPPCHECK_FORMAT_BIN "/usr/local/bin/cppcheck" CACHE STRING "use: `brew install cppcheck` to install")
  # http://releases.llvm.org/3.8.0/tools/clang/docs/ClangFormatStyleOptions.html
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
    ${LUA_SWIG_GENERATED_FILES}
    "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njlic/njlic.i"
  )

  add_custom_target(
    clang-format
    COMMAND ${CLANG_FORMAT_BIN} -style=file -i ${SOURCE_FILES} ${LUA_SWIG_GENERATED_FILES} "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njlic/njlic.i" -verbose
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
    include(${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/ZerobraneAPI.cmake)

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

if(${CMAKE_PROJECT_NAME}_EXE)
  if(NOT EMSCRIPTEN AND NOT IOS AND NOT TVOS AND NOT ANDROID)

    # LUA

    if(APPLE)
      add_executable( lua 
        MACOSX_BUNDLE 
        ${SOURCE_FILES} ${LUA_MAIN_FILES} ${LUA_RESOURCE_FILES} ${INCLUDE_FILES}
        )
    elseif(LINUX OR MSVC)
      add_executable( lua 
        ${SOURCE_FILES} ${LUA_MAIN_FILES} ${INCLUDE_FILES}
        )
    endif()

    if(NOT LINUX AND NOT MSVC)
      SET_TARGET_PROPERTIES(
          lua PROPERTIES
          RESOURCE "${LUA_RESOURCE_FILES}"
        )
    endif()
    
    if(MSVC)
      set_property(TARGET lua PROPERTY FOLDER "executables")
      install (TARGETS lua RUNTIME DESTINATION bin)
    elseif(NOT EMSCRIPTEN)
      INSTALL(TARGETS lua
        RUNTIME DESTINATION bin
        BUNDLE DESTINATION bin
        )
    else()
      file(GLOB_RECURSE EMSCRIPTEN_LUA_BINARY_FILES ${CMAKE_BINARY_DIR}/lua.*)
      list(REMOVE_DUPLICATES EMSCRIPTEN_LUA_BINARY_FILES)
      install(FILES ${EMSCRIPTEN_LUA_BINARY_FILES} DESTINATION bin)
    endif()

    if(MSVC AND NOT LIBC)

      list(APPEND EXTRA_LIBS "msvcrt.lib")
      # Don't try to link with the default set of libraries.
      set_target_properties(lua PROPERTIES LINK_FLAGS_RELEASE "/NODEFAULTLIB:LIBCMT")
      set_target_properties(lua PROPERTIES LINK_FLAGS_DEBUG "/NODEFAULTLIB:LIBCMT")
      target_link_libraries(lua ${EXTRA_LDFLAGS} debug "msvcrtd.lib")
    endif()

    target_include_directories(lua
      PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS}>
      PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES}>
      )

    target_link_libraries(lua ${EXTRA_LDFLAGS} optimized ${EXTRA_LIBS})

    # LUAC

    if(APPLE)
      add_executable( luac
        MACOSX_BUNDLE 
        ${SOURCE_FILES} ${LUAC_MAIN_FILES} ${LUAC_RESOURCE_FILES} ${INCLUDE_FILES}
        )
    elseif(LINUX OR MSVC)
      add_executable( luac
        ${SOURCE_FILES} ${LUAC_MAIN_FILES} ${INCLUDE_FILES}
        )
    endif()

    if(NOT LINUX AND NOT MSVC)
      SET_TARGET_PROPERTIES(
          luac PROPERTIES
          RESOURCE "${LUAC_RESOURCE_FILES}"
        )
    endif()

    if(MSVC)
      set_property(TARGET luac PROPERTY FOLDER "executables")
      install (TARGETS luac RUNTIME DESTINATION bin)
    elseif(NOT EMSCRIPTEN)
      INSTALL(TARGETS luac
        RUNTIME DESTINATION bin
        BUNDLE DESTINATION bin
        )
    else()
      file(GLOB_RECURSE EMSCRIPTEN_LUA_BINARY_FILES ${CMAKE_BINARY_DIR}/luac.*)
      list(REMOVE_DUPLICATES EMSCRIPTEN_LUA_BINARY_FILES)
      install(FILES ${EMSCRIPTEN_LUA_BINARY_FILES} DESTINATION bin)
    endif()

    if(MSVC AND NOT LIBC)

      list(APPEND EXTRA_LIBS "msvcrt.lib")
      # Don't try to link with the default set of libraries.
      set_target_properties(luac PROPERTIES LINK_FLAGS_RELEASE "/NODEFAULTLIB:LIBCMT")
      set_target_properties(luac PROPERTIES LINK_FLAGS_DEBUG "/NODEFAULTLIB:LIBCMT")
      target_link_libraries(luac ${EXTRA_LDFLAGS} debug "msvcrtd.lib")
    endif()

    target_include_directories(luac
      PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS}>
      PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES}>
      )

    target_link_libraries(luac ${EXTRA_LDFLAGS} optimized ${EXTRA_LIBS})
  endif()

endif(${CMAKE_PROJECT_NAME}_EXE)

