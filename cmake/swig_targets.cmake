set(${CMAKE_PROJECT_NAME}_LUA_SWIG_ENABLED_BY_DEFAULT ON)
set(${CMAKE_PROJECT_NAME}_LUA_SWIG ${${CMAKE_PROJECT_NAME}_LUA_SWIG_ENABLED_BY_DEFAULT} CACHE BOOL "Build the swig module for ${CMAKE_PROJECT_NAME}")

list(APPEND CMAKE_MODULE_PATH "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake")































#                                          macro(LUA_GLM_SWIG)
#                                            if(NOT CMAKE_PROJECT_NAME)
#                                              MESSAGE(FATAL_ERROR "CMAKE_PROJECT_NAME variable is empty.")
#                                            endif()
#                                            if(NOT ${CMAKE_PROJECT_NAME}_REPO_DIRECTORY)
#                                              MESSAGE(FATAL_ERROR "${CMAKE_PROJECT_NAME}_REPO_DIRECTORY variable is empty.")
#                                            endif()
#                                          
#                                            set(GLM_SWIG_DIRECTORY "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/thirdparty/glm")
#                                          
#                                            if(NOT GLM_SWIG_DIRECTORY)
#                                                MESSAGE(FATAL_ERROR "GLM_SWIG_DIRECTORY variable is empty.")
#                                            endif()
#                                            if(NOT GLM_INCLUDE_DIR)
#                                                MESSAGE(FATAL_ERROR "GLM_INCLUDE_DIR variable is empty.")
#                                            endif()
#                                          
#                                            if(NOT EXISTS "${GLM_SWIG_DIRECTORY}")
#                                                MESSAGE(FATAL_ERROR "Path doesn't exist: ${GLM_SWIG_DIRECTORY}")
#                                            endif()
#                                            if(NOT EXISTS "${GLM_INCLUDE_DIR}")
#                                                MESSAGE(FATAL_ERROR "Path doesn't exist: ${GLM_INCLUDE_DIR}")
#                                            endif()
#                                            if(NOT EXISTS "${GLM_SWIG_DIRECTORY}/glm.i")
#                                                MESSAGE(FATAL_ERROR "Path doesn't exist: ${GLM_SWIG_DIRECTORY}/glm.i")
#                                            endif()
#                                          
#                                            set(CMAKE_SWIG_FLAGS "")
#                                          
#                                            file(GLOB_RECURSE LUA_SWIG_SOURCE_FILES
#                                                "${GLM_SWIG_DIRECTORY}/*.swg"
#                                                "${GLM_INCLUDE_DIR}" 
#                                              )
#                                          
#                                            list(APPEND LUA_SWIG_SOURCE_FILES
#                                                "${GLM_SWIG_DIRECTORY}/glm.i" 
#                                            )
#                                          
#                                            SUBDIRLIST(SUBDIRS "${GLM_SWIG_DIRECTORY}" SWIGIN_SCRIPTS_INCLUDE_DIRS)
#                                          
#                                            set(${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-includeall")
#                                            # list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-fcompact")
#                                            list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-fvirtual")
#                                            list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-v")
#                                            list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-w201")
#                                            list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-w312")
#                                            list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-ignoremissing")
#                                            # list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-cpperraswarn")
#                                            list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-DBT_INFINITY")
#                                            list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-DSWIG_TYPE_TABLE=myprojectname")
#                                            if(GL_ES2)
#                                              list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-D__GL_ES2__")
#                                            elseif(GL_ES3)
#                                              list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-D__GL_ES3__")
#                                            elseif(GL_2)
#                                              list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-D__GL_2__")
#                                            elseif(GL_3)
#                                              list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-D__GL_3__")
#                                            endif()
#                                          
#                                            foreach(_SWIG_SOURCE_FILE ${LUA_SWIG_SOURCE_FILES})
#                                              set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY SWIG_FLAGS ${${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS})
#                                              set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY CPLUSPLUS ON)
#                                              set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY SWIG_INCLUDE_DIRECTORIES "${SWIGIN_SCRIPTS_INCLUDE_DIRS}")
#                                            endforeach()
#                                          
#                                          
#                                            # include_directories("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njlic" 
#                                            #   ${SWIGIN_SCRIPTS_INCLUDE_DIRS} 
#                                            #   ${GLM_INCLUDE_DIR} 
#                                            #   ${GLM_INCLUDE_DIRS}
#                                            #   )
#                                            include_directories("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njlic" 
#                                              ${SWIGIN_SCRIPTS_INCLUDE_DIRS} 
#                                              )
#                                          
#                                            get_property(_INCLUDE_DIRECTORIES DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
#                                            #  foreach(_INCLUDE_DIRECTORY ${_INCLUDE_DIRECTORIES})
#                                            #    MESSAGE(STATUS "BULLET_SWIG_INCLUDE_DIRECTORY ${_INCLUDE_DIRECTORY}")
#                                            #  endforeach()
#                                            list(REMOVE_ITEM _INCLUDE_DIRECTORIES "/usr/include")
#                                            set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES ${_INCLUDE_DIRECTORIES} )
#                                          
#                                            list(APPEND ${CMAKE_PROJECT_NAME}_DEFINITIONS GLM_SWIG=1 BT_INFINITY)
#                                          
#                                          
#                                          
#                                            if(${CMAKE_VERSION} VERSION_LESS "3.8")
#                                              swig_add_module(
#                                                ${CMAKE_PROJECT_NAME}-lua-swig-glm-static
#                                                lua
#                                                "${LUA_SWIG_SOURCE_FILES}"
#                                                )
#                                            else()
#                                              swig_add_library(
#                                                ${CMAKE_PROJECT_NAME}-lua-swig-glm-static
#                                                TYPE STATIC
#                                                LANGUAGE lua
#                                                SOURCES "${LUA_SWIG_SOURCE_FILES}"
#                                                )
#                                            endif()
#                                          
#                                            if(ANDROID)
#                                              if(TARGET main)
#                                                add_dependencies(main ${CMAKE_PROJECT_NAME}-lua-swig-glm-static)
#                                              endif()
#                                            else()
#                                              if(TARGET ${CMAKE_PROJECT_NAME}-exe)
#                                                add_dependencies(${CMAKE_PROJECT_NAME}-exe ${CMAKE_PROJECT_NAME}-lua-swig-glm-static)
#                                              endif()
#                                            endif()
#                                          
#                                            if(TARGET ${CMAKE_PROJECT_NAME}-static)
#                                              add_dependencies(${CMAKE_PROJECT_NAME}-static ${CMAKE_PROJECT_NAME}-lua-swig-glm-static)
#                                            endif()
#                                            if(TARGET ${CMAKE_PROJECT_NAME})
#                                              add_dependencies(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}-lua-swig-glm-static)
#                                            endif()
#                                          
#                                            target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-glm-static PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})
#                                          
#                                            if(APPLE)
#                                              if(IOS OR TVOS)
#                                                SET_TARGET_PROPERTIES (
#                                                  ${CMAKE_PROJECT_NAME}-lua-swig-glm-static PROPERTIES
#                                                  XCODE_PRODUCT_TYPE "com.apple.product-type.library.static"
#                                                  )
#                                              endif(IOS OR TVOS)
#                                            endif()
#                                          
#                                            target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-glm-static ${CMAKE_PROJECT_NAME}-static)
#                                            foreach(EXTRA_LIB ${EXTRA_LIBS})
#                                              target_link_libraries( ${CMAKE_PROJECT_NAME}-lua-swig-glm-static optimized ${EXTRA_LIB})
#                                            endforeach()
#                                            target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-glm-static ${EXTRA_LDFLAGS})
#                                            foreach(EXTRA_DEBUG_LIB ${EXTRA_DEBUG_LIBS})
#                                              target_link_libraries( ${CMAKE_PROJECT_NAME}-lua-swig-glm-static debug ${EXTRA_DEBUG_LIB})
#                                            endforeach()
#                                          
#                                            if(ANDROID)
#                                              # target_link_libraries( main ${CMAKE_PROJECT_NAME}-lua-swig-glm-static)
#                                              # target_compile_definitions(main PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})
#                                            endif()
#                                          
#                                            list(APPEND EXTRA_LIBS ${CMAKE_PROJECT_NAME}-lua-swig-glm-static)
#                                            list(APPEND INTERFACE_FILES ${LUA_SWIG_SOURCE_FILES})
#                                          
#                                            set(_INSTALL_LIBS "${CMAKE_PROJECT_NAME}-lua-swig-glm-static" ${_INSTALL_LIBS})
#                                            target_include_directories(${CMAKE_PROJECT_NAME}-lua-swig-glm-static
#                                              PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS}>
#                                              PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES}>
#                                              )
#                                            target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-glm-static PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})
#                                          
#                                            #                  if(NOT LINUX AND NOT EMSCRIPTEN AND NOT IOS AND NOT TVOS AND NOT ANDROID)
#                                          
#                                            #                    if(${CMAKE_VERSION} VERSION_LESS "3.8")
#                                            #                      swig_add_module(
#                                            #                        ${CMAKE_PROJECT_NAME}-lua-swig-glm
#                                            #                        lua
#                                            #                        "${LUA_SWIG_SOURCE_FILES}"
#                                            #                        )
#                                            #                    else()
#                                            #                      swig_add_library(
#                                            #                        ${CMAKE_PROJECT_NAME}-lua-swig-glm
#                                            #                        TYPE SHARED
#                                            #                        LANGUAGE lua
#                                            #                        SOURCES "${LUA_SWIG_SOURCE_FILES}"
#                                            #                        )
#                                            #                    endif()
#                                          
#                                            #                    # if(APPLE)
#                                            #                    #   if(IOS OR TVOS)
#                                            #                    #     SET_TARGET_PROPERTIES (
#                                            #                    #       ${CMAKE_PROJECT_NAME}-lua-swig-glm PROPERTIES
#                                            #                    #       XCODE_PRODUCT_TYPE "com.apple.product-type.library.dynamic"
#                                            #                    #       )
#                                            #                    #   endif(IOS OR TVOS)
#                                            #                    # endif()
#                                            #                    target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-glm PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})
#                                          
#                                            #                    if(MSVC AND NOT LIBC)
#                                            #                      list(APPEND EXTRA_LIBS "msvcrt.lib")
#                                            #                      # Don't try to link with the default set of libraries.
#                                            #                      set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-glm PROPERTIES LINK_FLAGS_RELEASE "/NODEFAULTLIB:LIBCMT")
#                                            #                      set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-glm PROPERTIES LINK_FLAGS_DEBUG "/NODEFAULTLIB:LIBCMT")
#                                            #                      target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-glm ${EXTRA_LDFLAGS} debug "msvcrtd.lib")
#                                            #                    endif()
#                                          
#                                            #                    target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-glm ${CMAKE_PROJECT_NAME}-static )
#                                            #                    foreach(EXTRA_LIB ${EXTRA_LIBS})
#                                            #                      target_link_libraries( ${CMAKE_PROJECT_NAME}-lua-swig-glm optimized ${EXTRA_LIB})
#                                            #                    endforeach()
#                                            #                    target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-glm ${EXTRA_LDFLAGS})
#                                            #                    foreach(EXTRA_DEBUG_LIB ${EXTRA_DEBUG_LIBS})
#                                            #                      target_link_libraries( ${CMAKE_PROJECT_NAME}-lua-swig-glm debug ${EXTRA_DEBUG_LIB})
#                                            #                    endforeach()
#                                            #                  endif()
#                                          
#                                            #                  if(NOT EMSCRIPTEN AND NOT IOS AND NOT TVOS AND NOT ANDROID AND NOT LINUX)
#                                            #                    #So... non-mobile (WINDOWS, LINUX, MAC
#                                          
#                                            #                    if(${CMAKE_VERSION} VERSION_LESS "3.8")
#                                            #                      MESSAGE(FATAL_ERROR "Cannot make a swig module with a version less than 3.8")
#                                            #                    else()
#                                            #                      swig_add_library(
#                                            #                        ${CMAKE_PROJECT_NAME}-lua-swig-glm-module
#                                            #                        TYPE MODULE
#                                            #                        LANGUAGE lua
#                                            #                        SOURCES "${LUA_SWIG_SOURCE_FILES}"
#                                            #                        )
#                                            #                    endif()
#                                          
#                                            #                    target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-glm-module PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})
#                                          
#                                            #                    if(MSVC AND NOT LIBC)
#                                            #                      list(APPEND EXTRA_LIBS "msvcrt.lib")
#                                            #                      # Don't try to link with the default set of libraries.
#                                            #                      set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-glm-module PROPERTIES LINK_FLAGS_RELEASE "/NODEFAULTLIB:LIBCMT")
#                                            #                      set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-glm-module PROPERTIES LINK_FLAGS_DEBUG "/NODEFAULTLIB:LIBCMT")
#                                            #                      target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-glm-module ${EXTRA_LDFLAGS} debug "msvcrtd.lib")
#                                            #                    endif()
#                                          
#                                            #                    target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-glm-module ${CMAKE_PROJECT_NAME}-static )
#                                            #                    foreach(EXTRA_LIB ${EXTRA_LIBS})
#                                            #                      target_link_libraries( ${CMAKE_PROJECT_NAME}-lua-swig-glm-module optimized ${EXTRA_LIB})
#                                            #                    endforeach()
#                                            #                    target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-glm-module ${EXTRA_LDFLAGS})
#                                            #                    foreach(EXTRA_DEBUG_LIB ${EXTRA_DEBUG_LIBS})
#                                            #                      target_link_libraries( ${CMAKE_PROJECT_NAME}-lua-swig-glm-module debug ${EXTRA_DEBUG_LIB})
#                                            #                    endforeach()
#                                            #                  endif()
#                                          
#                                          endmacro()
#                                          
#                                          macro(LUA_BULLET3_SWIG)
#                                            if(NOT CMAKE_PROJECT_NAME)
#                                              MESSAGE(FATAL_ERROR "CMAKE_PROJECT_NAME variable is empty.")
#                                            endif()
#                                            if(NOT ${CMAKE_PROJECT_NAME}_REPO_DIRECTORY)
#                                              MESSAGE(FATAL_ERROR "${CMAKE_PROJECT_NAME}_REPO_DIRECTORY variable is empty.")
#                                            endif()
#                                          
#                                            set(BULLET3_SWIG_DIRECTORY "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/thirdparty/bullet3")
#                                          
#                                            if(NOT BULLET3_SWIG_DIRECTORY)
#                                              MESSAGE(FATAL_ERROR "BULLET3_SWIG_DIRECTORY variable is empty.")
#                                            endif()
#                                            if(NOT BULLET3_INCLUDE_DIR)
#                                              MESSAGE(FATAL_ERROR "BULLET3_INCLUDE_DIR variable is empty.")
#                                            endif()
#                                          
#                                            if(NOT EXISTS "${BULLET3_SWIG_DIRECTORY}")
#                                              MESSAGE(FATAL_ERROR "Path doesn't exist: ${BULLET3_SWIG_DIRECTORY}")
#                                            endif()
#                                            if(NOT EXISTS "${BULLET3_INCLUDE_DIR}")
#                                              MESSAGE(FATAL_ERROR "Path doesn't exist: ${BULLET3_INCLUDE_DIR}")
#                                            endif()
#                                            if(NOT EXISTS "${BULLET3_SWIG_DIRECTORY}/bullet3.i")
#                                              MESSAGE(FATAL_ERROR "Path doesn't exist: ${BULLET3_SWIG_DIRECTORY}/bullet3.i")
#                                            endif()
#                                          
#                                            set(CMAKE_SWIG_FLAGS "")
#                                          
#                                            file(GLOB_RECURSE LUA_SWIG_SOURCE_FILES
#                                              "${BULLET3_SWIG_DIRECTORY}/*.swg"
#                                              "${BULLET3_INCLUDE_DIR}" 
#                                              )
#                                          
#                                            list(APPEND LUA_SWIG_SOURCE_FILES
#                                              "${BULLET3_SWIG_DIRECTORY}/bullet3.i" 
#                                            )
#                                          
#                                            SUBDIRLIST(SUBDIRS "${BULLET3_SWIG_DIRECTORY}" SWIGIN_SCRIPTS_INCLUDE_DIRS)
#                                          
#                                            set(${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-includeall")
#                                            # list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-fcompact")
#                                            list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-fvirtual")
#                                            list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-v")
#                                            list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-w201")
#                                            list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-w312")
#                                            list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-ignoremissing")
#                                            # list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-cpperraswarn")
#                                            list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-DBT_INFINITY")
#                                            list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-DSWIG_TYPE_TABLE=myprojectname")
#                                            if(GL_ES2)
#                                              list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-D__GL_ES2__")
#                                            elseif(GL_ES3)
#                                              list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-D__GL_ES3__")
#                                            elseif(GL_2)
#                                              list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-D__GL_2__")
#                                            elseif(GL_3)
#                                              list(APPEND ${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS "-D__GL_3__")
#                                            endif()
#                                          
#                                            foreach(_SWIG_SOURCE_FILE ${LUA_SWIG_SOURCE_FILES})
#                                              set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY SWIG_FLAGS ${${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS})
#                                              set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY CPLUSPLUS ON)
#                                              set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY SWIG_INCLUDE_DIRECTORIES "${SWIGIN_SCRIPTS_INCLUDE_DIRS}")
#                                            endforeach()
#                                          
#                                          
#                                            # include_directories("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njlic" 
#                                            #   ${SWIGIN_SCRIPTS_INCLUDE_DIRS} 
#                                            #   ${BULLET3_INCLUDE_DIR} 
#                                            #   ${BULLET3_INCLUDE_DIRS}
#                                            #   )
#                                            include_directories("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njlic" 
#                                              ${SWIGIN_SCRIPTS_INCLUDE_DIRS} 
#                                              )
#                                          
#                                            get_property(_INCLUDE_DIRECTORIES DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
#                                            #  foreach(_INCLUDE_DIRECTORY ${_INCLUDE_DIRECTORIES})
#                                            #    MESSAGE(STATUS "BULLET_SWIG_INCLUDE_DIRECTORY ${_INCLUDE_DIRECTORY}")
#                                            #  endforeach()
#                                            list(REMOVE_ITEM _INCLUDE_DIRECTORIES "/usr/include")
#                                            set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES ${_INCLUDE_DIRECTORIES} )
#                                          
#                                            list(APPEND ${CMAKE_PROJECT_NAME}_DEFINITIONS BULLET3_SWIG=1 BT_INFINITY)
#                                          
#                                          
#                                          
#                                            if(${CMAKE_VERSION} VERSION_LESS "3.8")
#                                              swig_add_module(
#                                                ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static
#                                                lua
#                                                "${LUA_SWIG_SOURCE_FILES}"
#                                                )
#                                            else()
#                                              swig_add_library(
#                                                ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static
#                                                TYPE STATIC
#                                                LANGUAGE lua
#                                                SOURCES "${LUA_SWIG_SOURCE_FILES}"
#                                                )
#                                            endif()
#                                          
#                                            if(ANDROID)
#                                              if(TARGET main)
#                                                add_dependencies(main ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static)
#                                              endif()
#                                            else()
#                                              if(TARGET ${CMAKE_PROJECT_NAME}-exe)
#                                                add_dependencies(${CMAKE_PROJECT_NAME}-exe ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static)
#                                              endif()
#                                            endif()
#                                          
#                                            if(TARGET ${CMAKE_PROJECT_NAME}-static)
#                                              add_dependencies(${CMAKE_PROJECT_NAME}-static ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static)
#                                            endif()
#                                            if(TARGET ${CMAKE_PROJECT_NAME})
#                                              add_dependencies(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static)
#                                            endif()
#                                          
#                                            target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})
#                                          
#                                            if(APPLE)
#                                              if(IOS OR TVOS)
#                                                SET_TARGET_PROPERTIES (
#                                                  ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static PROPERTIES
#                                                  XCODE_PRODUCT_TYPE "com.apple.product-type.library.static"
#                                                  )
#                                              endif(IOS OR TVOS)
#                                            endif()
#                                          
#                                            target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static ${CMAKE_PROJECT_NAME}-static)
#                                            foreach(EXTRA_LIB ${EXTRA_LIBS})
#                                              target_link_libraries( ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static optimized ${EXTRA_LIB})
#                                            endforeach()
#                                            target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static ${EXTRA_LDFLAGS})
#                                            foreach(EXTRA_DEBUG_LIB ${EXTRA_DEBUG_LIBS})
#                                              target_link_libraries( ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static debug ${EXTRA_DEBUG_LIB})
#                                            endforeach()
#                                          
#                                            if(ANDROID)
#                                              # target_link_libraries( main ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static)
#                                              # target_compile_definitions(main PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})
#                                            endif()
#                                          
#                                            list(APPEND EXTRA_LIBS ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static)
#                                            list(APPEND INTERFACE_FILES ${LUA_SWIG_SOURCE_FILES})
#                                          
#                                            set(_INSTALL_LIBS "${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static" ${_INSTALL_LIBS})
#                                            target_include_directories(${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static
#                                              PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS}>
#                                              PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES}>
#                                              )
#                                            target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-bullet3-static PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})
#                                          
#                                            #                 if(NOT LINUX AND NOT EMSCRIPTEN AND NOT IOS AND NOT TVOS AND NOT ANDROID)
#                                          
#                                            #                   if(${CMAKE_VERSION} VERSION_LESS "3.8")
#                                            #                     swig_add_module(
#                                            #                       ${CMAKE_PROJECT_NAME}-lua-swig-bullet3
#                                            #                       lua
#                                            #                       "${LUA_SWIG_SOURCE_FILES}"
#                                            #                       )
#                                            #                   else()
#                                            #                     swig_add_library(
#                                            #                       ${CMAKE_PROJECT_NAME}-lua-swig-bullet3
#                                            #                       TYPE SHARED
#                                            #                       LANGUAGE lua
#                                            #                       SOURCES "${LUA_SWIG_SOURCE_FILES}"
#                                            #                       )
#                                            #                   endif()
#                                          
#                                            #                   # if(APPLE)
#                                            #                   #   if(IOS OR TVOS)
#                                            #                   #     SET_TARGET_PROPERTIES (
#                                            #                   #       ${CMAKE_PROJECT_NAME}-lua-swig-bullet3 PROPERTIES
#                                            #                   #       XCODE_PRODUCT_TYPE "com.apple.product-type.library.dynamic"
#                                            #                   #       )
#                                            #                   #   endif(IOS OR TVOS)
#                                            #                   # endif()
#                                            #                   target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-bullet3 PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})
#                                          
#                                            #                   if(MSVC AND NOT LIBC)
#                                            #                     list(APPEND EXTRA_LIBS "msvcrt.lib")
#                                            #                     # Don't try to link with the default set of libraries.
#                                            #                     set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-bullet3 PROPERTIES LINK_FLAGS_RELEASE "/NODEFAULTLIB:LIBCMT")
#                                            #                     set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-bullet3 PROPERTIES LINK_FLAGS_DEBUG "/NODEFAULTLIB:LIBCMT")
#                                            #                     target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-bullet3 ${EXTRA_LDFLAGS} debug "msvcrtd.lib")
#                                            #                   endif()
#                                          
#                                            #                   target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-bullet3 ${CMAKE_PROJECT_NAME}-static )
#                                            #                   foreach(EXTRA_LIB ${EXTRA_LIBS})
#                                            #                     target_link_libraries( ${CMAKE_PROJECT_NAME}-lua-swig-bullet3 optimized ${EXTRA_LIB})
#                                            #                   endforeach()
#                                            #                   target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-bullet3 ${EXTRA_LDFLAGS})
#                                            #                   foreach(EXTRA_DEBUG_LIB ${EXTRA_DEBUG_LIBS})
#                                            #                     target_link_libraries( ${CMAKE_PROJECT_NAME}-lua-swig-bullet3 debug ${EXTRA_DEBUG_LIB})
#                                            #                   endforeach()
#                                            #                 endif()
#                                          
#                                            #                 if(NOT EMSCRIPTEN AND NOT IOS AND NOT TVOS AND NOT ANDROID AND NOT LINUX)
#                                            #                   #So... non-mobile (WINDOWS, LINUX, MAC
#                                          
#                                            #                   if(${CMAKE_VERSION} VERSION_LESS "3.8")
#                                            #                     MESSAGE(FATAL_ERROR "Cannot make a swig module with a version less than 3.8")
#                                            #                   else()
#                                            #                     swig_add_library(
#                                            #                       ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-module
#                                            #                       TYPE MODULE
#                                            #                       LANGUAGE lua
#                                            #                       SOURCES "${LUA_SWIG_SOURCE_FILES}"
#                                            #                       )
#                                            #                   endif()
#                                          
#                                            #                   target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-bullet3-module PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})
#                                          
#                                            #                   if(MSVC AND NOT LIBC)
#                                            #                     list(APPEND EXTRA_LIBS "msvcrt.lib")
#                                            #                     # Don't try to link with the default set of libraries.
#                                            #                     set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-bullet3-module PROPERTIES LINK_FLAGS_RELEASE "/NODEFAULTLIB:LIBCMT")
#                                            #                     set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-bullet3-module PROPERTIES LINK_FLAGS_DEBUG "/NODEFAULTLIB:LIBCMT")
#                                            #                     target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-bullet3-module ${EXTRA_LDFLAGS} debug "msvcrtd.lib")
#                                            #                   endif()
#                                          
#                                            #                   target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-bullet3-module ${CMAKE_PROJECT_NAME}-static )
#                                            #                   foreach(EXTRA_LIB ${EXTRA_LIBS})
#                                            #                     target_link_libraries( ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-module optimized ${EXTRA_LIB})
#                                            #                   endforeach()
#                                            #                   target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-bullet3-module ${EXTRA_LDFLAGS})
#                                            #                   foreach(EXTRA_DEBUG_LIB ${EXTRA_DEBUG_LIBS})
#                                            #                     target_link_libraries( ${CMAKE_PROJECT_NAME}-lua-swig-bullet3-module debug ${EXTRA_DEBUG_LIB})
#                                            #                   endforeach()
#                                            #                 endif()
#                                          
#                                          endmacro()
#                                          
#                                          macro(LUA_NJLIC_SWIG)
#                                          
#                                            if(NOT CMAKE_PROJECT_NAME)
#                                              MESSAGE(FATAL_ERROR "CMAKE_PROJECT_NAME variable is empty.")
#                                            endif()
#                                          
#                                            if(NOT ${CMAKE_PROJECT_NAME}_REPO_DIRECTORY)
#                                              MESSAGE(FATAL_ERROR "${CMAKE_PROJECT_NAME}_REPO_DIRECTORY variable is empty.")
#                                            endif()
#                                          
#                                            set(NJLIC_SWIG_INCLUDE_DIR "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njlic")
#                                          
#                                            if(NOT NJLIC_SWIG_INCLUDE_DIR)
#                                              MESSAGE(FATAL_ERROR "NJLIC_SWIG_INCLUDE_DIR variable is empty.")
#                                            endif()
#                                          
#                                            if(NOT NJLIC_INCLUDE_DIR)
#                                              MESSAGE(FATAL_ERROR "NJLIC_INCLUDE_DIR variable is empty.")
#                                            endif()
#                                          
#                                            if(NOT EXISTS "${NJLIC_SWIG_INCLUDE_DIR}")
#                                              MESSAGE(FATAL_ERROR "Path doesn't exist: ${NJLIC_SWIG_INCLUDE_DIR}")
#                                            endif()
#                                            if(NOT EXISTS "${NJLIC_INCLUDE_DIR}")
#                                              MESSAGE(FATAL_ERROR "Path doesn't exist: ${NJLIC_INCLUDE_DIR}")
#                                            endif()
#                                          
#                                            if(NOT EXISTS "${NJLIC_SWIG_INCLUDE_DIR}/njlic.i")
#                                              MESSAGE(FATAL_ERROR "Path doesn't exist: ${NJLIC_SWIG_INCLUDE_DIR}/njlic.i")
#                                            endif()
#                                          
#                                            configure_file("${NJLIC_SWIG_INCLUDE_DIR}/_Defines.swg.in"
#                                              "${NJLIC_SWIG_INCLUDE_DIR}/_Defines.swg")
#                                          
#                                            file(GLOB_RECURSE LUA_SWIG_SOURCE_FILES
#                                              ${NJLIC_SWIG_INCLUDE_DIR}/*.swg
#                                              )
#                                          
#                                            list(APPEND LUA_SWIG_SOURCE_FILES
#                                              "${NJLIC_SWIG_INCLUDE_DIR}/njlic.i" 
#                                              "${NJLIC_SWIG_INCLUDE_DIR}/_Defines.swg"
#                                            )
#                                          
#                                            SUBDIRLIST(SUBDIRS "${NJLIC_SWIG_INCLUDE_DIR}" NJLIC_SWIG_INCLUDE_DIRS)
#                                            list(APPEND NJLIC_SWIG_INCLUDE_DIRS ${NJLIC_INCLUDE_DIRS})
#                                          
#                                            set(CMAKE_SWIG_FLAGS "-includeall")
#                                            # list(APPEND CMAKE_SWIG_FLAGS "-fcompact")
#                                            list(APPEND CMAKE_SWIG_FLAGS "-fvirtual")
#                                            list(APPEND CMAKE_SWIG_FLAGS "-v")
#                                            list(APPEND CMAKE_SWIG_FLAGS "-w201")
#                                            list(APPEND CMAKE_SWIG_FLAGS "-w312")
#                                            list(APPEND CMAKE_SWIG_FLAGS "-ignoremissing")
#                                            # list(APPEND CMAKE_SWIG_FLAGS "-cpperraswarn")
#                                            list(APPEND CMAKE_SWIG_FLAGS "-DBT_INFINITY")
#                                            list(APPEND CMAKE_SWIG_FLAGS "-DSWIG_TYPE_TABLE=myprojectname")
#                                            list(APPEND CMAKE_SWIG_FLAGS "-D__GL_2__")
#                                            if(GL_ES2)
#                                              list(APPEND CMAKE_SWIG_FLAGS "-D__GL_ES2__")
#                                            elseif(GL_ES3)
#                                              list(APPEND CMAKE_SWIG_FLAGS "-D__GL_ES3__")
#                                            elseif(GL_2)
#                                              list(APPEND CMAKE_SWIG_FLAGS "-D__GL_2__")
#                                            elseif(GL_3)
#                                              list(APPEND CMAKE_SWIG_FLAGS "-D__GL_3__")
#                                            endif()
#                                          
#                                            foreach(_SWIG_SOURCE_FILE ${LUA_SWIG_SOURCE_FILES})
#                                              # set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY SWIG_FLAGS ${${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS})
#                                              set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY CPLUSPLUS ON)
#                                              set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY SWIG_INCLUDE_DIRECTORIES "${NJLIC_SWIG_INCLUDE_DIRS}")
#                                            endforeach()
#                                          
#                                            include_directories(
#                                              ${NJLIC_SWIG_INCLUDE_DIRS}
#                                              ${BULLET3_INCLUDE_DIRS}
#                                              )
#                                          
#                                            get_property(_INCLUDE_DIRECTORIES DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
#                                            # foreach(_INCLUDE_DIRECTORY ${_INCLUDE_DIRECTORIES})
#                                            #   MESSAGE(STATUS "BULLET_SWIG_INCLUDE_DIRECTORY ${_INCLUDE_DIRECTORY}")
#                                            # endforeach()
#                                            list(REMOVE_ITEM _INCLUDE_DIRECTORIES "/usr/include")
#                                            set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES ${_INCLUDE_DIRECTORIES} )
#                                          
#                                            list(APPEND ${CMAKE_PROJECT_NAME}_DEFINITIONS NJLIC_SWIG=1 BT_INFINITY)
#                                          
#                                            if(${CMAKE_VERSION} VERSION_LESS "3.8")
#                                              swig_add_module(
#                                                ${CMAKE_PROJECT_NAME}-lua-swig-njlic-static
#                                                lua
#                                                "${LUA_SWIG_SOURCE_FILES}"
#                                                )
#                                            else()
#                                              swig_add_library(
#                                                ${CMAKE_PROJECT_NAME}-lua-swig-njlic-static
#                                                TYPE STATIC
#                                                LANGUAGE lua
#                                                SOURCES "${LUA_SWIG_SOURCE_FILES}"
#                                                )
#                                            endif()
#                                          
#                                            if(ANDROID)
#                                              if(TARGET main)
#                                                add_dependencies(main ${CMAKE_PROJECT_NAME}-lua-swig-njlic-static)
#                                              endif()
#                                            else()
#                                              if(TARGET ${CMAKE_PROJECT_NAME}-exe)
#                                                add_dependencies(${CMAKE_PROJECT_NAME}-exe ${CMAKE_PROJECT_NAME}-lua-swig-njlic-static)
#                                              endif()
#                                            endif()
#                                          
#                                            if(TARGET ${CMAKE_PROJECT_NAME}-static)
#                                              add_dependencies(${CMAKE_PROJECT_NAME}-static ${CMAKE_PROJECT_NAME}-lua-swig-njlic-static)
#                                            endif()
#                                            if(TARGET ${CMAKE_PROJECT_NAME})
#                                              add_dependencies(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}-lua-swig-njlic-static)
#                                            endif()
#                                          
#                                            if(APPLE)
#                                              if(IOS OR TVOS)
#                                                SET_TARGET_PROPERTIES (
#                                                  ${CMAKE_PROJECT_NAME}-lua-swig-njlic-static PROPERTIES
#                                                  XCODE_PRODUCT_TYPE "com.apple.product-type.library.static"
#                                                  )
#                                              endif(IOS OR TVOS)
#                                            endif()
#                                          
#                                            target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-njlic-static PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})
#                                            # Had to comment this out for windows... 
#                                            # target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-njlic-static ${CMAKE_PROJECT_NAME}-static)
#                                            if(ANDROID)
#                                              # target_link_libraries( main ${CMAKE_PROJECT_NAME}-lua-swig-njlic-static)
#                                              # target_compile_definitions(main PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})
#                                            endif()
#                                            list(APPEND EXTRA_LIBS ${CMAKE_PROJECT_NAME}-lua-swig-njlic-static)
#                                            list(APPEND INTERFACE_FILES ${LUA_SWIG_SOURCE_FILES})
#                                          
#                                          
#                                          
#                                          
#                                          
#                                          
#                                          
#                                            set(_INSTALL_LIBS "${CMAKE_PROJECT_NAME}-lua-swig-njlic-static" ${_INSTALL_LIBS})
#                                            target_include_directories(${CMAKE_PROJECT_NAME}-lua-swig-njlic-static
#                                              PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS}>
#                                              PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES}>
#                                              )
#                                            target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-njlic-static PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})
#                                          
#                                            #                    if(NOT LINUX AND NOT EMSCRIPTEN AND NOT IOS AND NOT TVOS AND NOT ANDROID)
#                                          
#                                            #                      if(${CMAKE_VERSION} VERSION_LESS "3.8")
#                                            #                        swig_add_module(
#                                            #                          ${CMAKE_PROJECT_NAME}-lua-swig-njlic
#                                            #                          lua
#                                            #                          "${LUA_SWIG_SOURCE_FILES}"
#                                            #                          )
#                                            #                      else()
#                                            #                        swig_add_library(
#                                            #                          ${CMAKE_PROJECT_NAME}-lua-swig-njlic
#                                            #                          TYPE SHARED
#                                            #                          LANGUAGE lua
#                                            #                          SOURCES "${LUA_SWIG_SOURCE_FILES}"
#                                            #                          )
#                                            #                      endif()
#                                            #                      target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-njlic PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})
#                                          
#                                            #                      if(APPLE)
#                                            #                        set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-njlic PROPERTIES MACOSX_RPATH 1)
#                                            #                        # if(IOS OR TVOS)
#                                            #                        #   SET_TARGET_PROPERTIES (
#                                            #                        #     ${CMAKE_PROJECT_NAME}-lua-swig-njlic PROPERTIES
#                                            #                        #     XCODE_ATTRIBUTE_ENABLE_BITCODE "NO"
#                                            #                        #     XCODE_PRODUCT_TYPE "com.apple.product-type.library.dynamic"
#                                            #                        #     )
#                                            #                        # endif()
#                                            #                      elseif(UNIX AND NOT ANDROID)
#                                            #                        set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-njlic PROPERTIES
#                                            #                          VERSION ${LT_VERSION}
#                                            #                          SOVERSION ${LT_REVISION}
#                                            #                          OUTPUT_NAME "${CMAKE_PROJECT_NAME}-lua-swig-njlic-${LT_RELEASE}")
#                                            #                      else()
#                                            #                        # set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-njlic PROPERTIES
#                                            #                        #   VERSION ${${CMAKE_PROJECT_NAME}-lua-swig-njlic_VERSION}
#                                            #                        #   SOVERSION ${LT_REVISION}
#                                            #                        #   OUTPUT_NAME "${CMAKE_PROJECT_NAME}-lua-swig-njlic")
#                                            #                      endif()
#                                            #                      if(MSVC AND NOT LIBC)
#                                            #                        list(APPEND EXTRA_LIBS "msvcrt.lib")
#                                            #                        # Don't try to link with the default set of libraries.
#                                            #                        set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-njlic PROPERTIES LINK_FLAGS_RELEASE "/NODEFAULTLIB:LIBCMT")
#                                            #                        set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-njlic PROPERTIES LINK_FLAGS_DEBUG "/NODEFAULTLIB:LIBCMT")
#                                            #                        target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-njlic ${EXTRA_LDFLAGS} debug "msvcrtd.lib")
#                                            #                      endif()
#                                            #                      target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-njlic ${CMAKE_PROJECT_NAME}-static)
#                                          
#                                            #                      set(_INSTALL_LIBS "${CMAKE_PROJECT_NAME}-lua-swig-njlic" ${_INSTALL_LIBS})
#                                            #                      target_include_directories(${CMAKE_PROJECT_NAME}-lua-swig-njlic
#                                            #                        PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS}>
#                                            #                        PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES}>
#                                            #                        )
#                                            #                      target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-njlic PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})
#                                            #                    endif()
#                                          
#                                            #                    if(NOT EMSCRIPTEN AND NOT IOS AND NOT TVOS AND NOT ANDROID AND NOT LINUX)
#                                            #                      #So... non-mobile (WINDOWS, LINUX, MAC
#                                          
#                                            #                      if(${CMAKE_VERSION} VERSION_LESS "3.8")
#                                            #                        MESSAGE(FATAL_ERROR "Cannot make a swig module with a version less than 3.8")
#                                            #                      else()
#                                            #                        swig_add_library(
#                                            #                          ${CMAKE_PROJECT_NAME}-lua-swig-njlic-module
#                                            #                          TYPE MODULE
#                                            #                          LANGUAGE lua
#                                            #                          SOURCES "${LUA_SWIG_SOURCE_FILES}"
#                                            #                          )
#                                            #                      endif()
#                                            #                      target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-njlic-module PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})
#                                          
#                                            #                      if(APPLE)
#                                            #                        set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-njlic-module PROPERTIES MACOSX_RPATH 1)
#                                            #                        # if(IOS OR TVOS)
#                                            #                        #   SET_TARGET_PROPERTIES (
#                                            #                        #     ${CMAKE_PROJECT_NAME}-lua-swig-njlic-module PROPERTIES
#                                            #                        #     XCODE_ATTRIBUTE_ENABLE_BITCODE "NO"
#                                            #                        #     XCODE_PRODUCT_TYPE "com.apple.product-type.library.dynamic"
#                                            #                        #     )
#                                            #                        # endif()
#                                            #                      elseif(UNIX AND NOT ANDROID)
#                                            #                        set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-njlic-module PROPERTIES
#                                            #                          VERSION ${LT_VERSION}
#                                            #                          SOVERSION ${LT_REVISION}
#                                            #                          OUTPUT_NAME "${CMAKE_PROJECT_NAME}-lua-swig-njlic-module-${LT_RELEASE}")
#                                            #                      else()
#                                            #                        # set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-njlic-module PROPERTIES
#                                            #                        #   VERSION ${${CMAKE_PROJECT_NAME}-lua-swig-njlic_VERSION}
#                                            #                        #   SOVERSION ${LT_REVISION}
#                                            #                        #   OUTPUT_NAME "${CMAKE_PROJECT_NAME}-lua-swig-njlic-module")
#                                            #                      endif()
#                                            #                      if(MSVC AND NOT LIBC)
#                                            #                        list(APPEND EXTRA_LIBS "msvcrt.lib")
#                                            #                        # Don't try to link with the default set of libraries.
#                                            #                        set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-njlic-module PROPERTIES LINK_FLAGS_RELEASE "/NODEFAULTLIB:LIBCMT")
#                                            #                        set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-njlic-module PROPERTIES LINK_FLAGS_DEBUG "/NODEFAULTLIB:LIBCMT")
#                                            #                        target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-njlic-module ${EXTRA_LDFLAGS} debug "msvcrtd.lib")
#                                            #                      endif()
#                                            #                      target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-njlic-module ${CMAKE_PROJECT_NAME}-static)
#                                          
#                                            #                      set(_INSTALL_LIBS "${CMAKE_PROJECT_NAME}-lua-swig-njlic-module" ${_INSTALL_LIBS})
#                                            #                      target_include_directories(${CMAKE_PROJECT_NAME}-lua-swig-njlic-module
#                                            #                        PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS}>
#                                            #                        PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES}>
#                                            #                        )
#                                            #                      target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-njlic-module PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})
#                                            #                    endif()
#                                          
#                                          endmacro()


























macro(LUA_SWIG INTERFACE_NAME )

    set (extra_macro_args ${ARGN})
    # Did we get any optional args?
    list(LENGTH extra_macro_args num_extra_args)
    if (${num_extra_args} GREATER 0)
        list(GET extra_macro_args 0 IS_SHARED )
    endif ()

    if (${num_extra_args} GREATER 1)
        list(GET extra_macro_args 1 BASE_PATH)
    endif ()

    set(TARGET_EXTENSION "-static")
    if(IS_SHARED)
        set(TARGET_EXTENSION "")
    endif()

    string(TOLOWER ${INTERFACE_NAME} INTERFACE_NAME_LOWER)

  if(NOT CMAKE_PROJECT_NAME)
    MESSAGE(FATAL_ERROR "CMAKE_PROJECT_NAME variable is empty.")
  endif()

  if(NOT ${CMAKE_PROJECT_NAME}_REPO_DIRECTORY)
    MESSAGE(FATAL_ERROR "${CMAKE_PROJECT_NAME}_REPO_DIRECTORY variable is empty.")
  endif()

  set(${INTERFACE_NAME}_SWIG_INCLUDE_DIR "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/${BASE_PATH}/${INTERFACE_NAME_LOWER}")
  MESSAGE(STATUS "${INTERFACE_NAME}_SWIG_INCLUDE_DIR ${${INTERFACE_NAME}_SWIG_INCLUDE_DIR}") 
  if(NOT ${INTERFACE_NAME}_SWIG_INCLUDE_DIR)
      MESSAGE(FATAL_ERROR "${INTERFACE_NAME}_SWIG_INCLUDE_DIR variable is empty.")
  endif()

  if(NOT ${INTERFACE_NAME}_INCLUDE_DIR)
      MESSAGE(FATAL_ERROR "${INTERFACE_NAME}_INCLUDE_DIR variable is empty.")
  endif()

  if(NOT EXISTS "${${INTERFACE_NAME}_SWIG_INCLUDE_DIR}")
      MESSAGE(FATAL_ERROR "Path doesn't exist: ${${INTERFACE_NAME}_SWIG_INCLUDE_DIR}")
  endif()
  if(NOT EXISTS "${${INTERFACE_NAME}_INCLUDE_DIR}")
      MESSAGE(FATAL_ERROR "Path doesn't exist: ${${INTERFACE_NAME}_INCLUDE_DIR}")
  endif()

  if(NOT EXISTS "${${INTERFACE_NAME}_SWIG_INCLUDE_DIR}/${INTERFACE_NAME_LOWER}.i")
      MESSAGE(FATAL_ERROR "Path doesn't exist: ${${INTERFACE_NAME}_SWIG_INCLUDE_DIR}/${INTERFACE_NAME_LOWER}.i")
  endif()

  file(GLOB_RECURSE LUA_SWIG_SOURCE_FILES
      ${${INTERFACE_NAME}_SWIG_INCLUDE_DIR}/*.swg
    )

  list(APPEND LUA_SWIG_SOURCE_FILES
      "${${INTERFACE_NAME}_SWIG_INCLUDE_DIR}/${INTERFACE_NAME_LOWER}.i" 
  )

  SUBDIRLIST(SUBDIRS "${${INTERFACE_NAME}_SWIG_INCLUDE_DIR}" ${INTERFACE_NAME}_SWIG_INCLUDE_DIRS)
  list(APPEND ${INTERFACE_NAME}_SWIG_INCLUDE_DIRS ${${INTERFACE_NAME}_INCLUDE_DIRS})

  set(CMAKE_SWIG_FLAGS "-includeall")
  # list(APPEND CMAKE_SWIG_FLAGS "-fcompact")
  list(APPEND CMAKE_SWIG_FLAGS "-fvirtual")
  list(APPEND CMAKE_SWIG_FLAGS "-v")
  list(APPEND CMAKE_SWIG_FLAGS "-w201")
  list(APPEND CMAKE_SWIG_FLAGS "-w312")
  list(APPEND CMAKE_SWIG_FLAGS "-ignoremissing")
  # list(APPEND CMAKE_SWIG_FLAGS "-cpperraswarn")
  list(APPEND CMAKE_SWIG_FLAGS "-DBT_INFINITY")
  list(APPEND CMAKE_SWIG_FLAGS "-DSWIG_TYPE_TABLE=myprojectname")
  list(APPEND CMAKE_SWIG_FLAGS "-D__GL_2__")
  if(GL_ES2)
    list(APPEND CMAKE_SWIG_FLAGS "-D__GL_ES2__")
  elseif(GL_ES3)
    list(APPEND CMAKE_SWIG_FLAGS "-D__GL_ES3__")
  elseif(GL_2)
    list(APPEND CMAKE_SWIG_FLAGS "-D__GL_2__")
  elseif(GL_3)
    list(APPEND CMAKE_SWIG_FLAGS "-D__GL_3__")
  endif()

  foreach(_SWIG_SOURCE_FILE ${LUA_SWIG_SOURCE_FILES})
    # set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY SWIG_FLAGS ${${CMAKE_PROJECT_NAME}_LUA_SWIG_FLAGS})
    set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY CPLUSPLUS ON)
    set_property(SOURCE ${_SWIG_SOURCE_FILE} PROPERTY SWIG_INCLUDE_DIRECTORIES "${${INTERFACE_NAME}_SWIG_INCLUDE_DIRS}")
  endforeach()

  include_directories(
      ${${INTERFACE_NAME}_SWIG_INCLUDE_DIRS}
    ${BULLET3_INCLUDE_DIRS}
    )

  get_property(_INCLUDE_DIRECTORIES DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
  # foreach(_INCLUDE_DIRECTORY ${_INCLUDE_DIRECTORIES})
  #   MESSAGE(STATUS "BULLET_SWIG_INCLUDE_DIRECTORY ${_INCLUDE_DIRECTORY}")
  # endforeach()
  list(REMOVE_ITEM _INCLUDE_DIRECTORIES "/usr/include")
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES ${_INCLUDE_DIRECTORIES} )

  list(APPEND ${CMAKE_PROJECT_NAME}_DEFINITIONS ${INTERFACE_NAME}_SWIG=1 BT_INFINITY)
  
  if(${CMAKE_VERSION} VERSION_LESS "3.8")
    swig_add_module(
        ${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}${TARGET_EXTENSION}
      lua
      "${LUA_SWIG_SOURCE_FILES}"
      )
  else()
      if(IS_SHARED)
          swig_add_library(
              ${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}${TARGET_EXTENSION}
              TYPE SHARED
              LANGUAGE lua
              SOURCES "${LUA_SWIG_SOURCE_FILES}"
              )
      else()
          swig_add_library(
              ${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}${TARGET_EXTENSION}
              TYPE STATIC
              LANGUAGE lua
              SOURCES "${LUA_SWIG_SOURCE_FILES}"
              )
      endif()
  endif()

  if(ANDROID)
    if(TARGET main)
        add_dependencies(main ${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}${TARGET_EXTENSION})
    endif()
  else()
    if(TARGET ${CMAKE_PROJECT_NAME}-exe)
        add_dependencies(${CMAKE_PROJECT_NAME}-exe ${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}${TARGET_EXTENSION})
    endif()
  endif()

  if(TARGET ${CMAKE_PROJECT_NAME}-static)
      add_dependencies(${CMAKE_PROJECT_NAME}-static ${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}${TARGET_EXTENSION})
  endif()
  if(TARGET ${CMAKE_PROJECT_NAME})
      add_dependencies(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}${TARGET_EXTENSION})
  endif()

  if(APPLE)
    if(IOS OR TVOS)
      SET_TARGET_PROPERTIES (
          ${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}${TARGET_EXTENSION} PROPERTIES
          XCODE_PRODUCT_TYPE "com.apple.product-type.library.static"
          )
    endif()
  endif()
  if(ANDROID)
      if(IS_SHARED)
          # target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}${TARGET_EXTENSION} ${CMAKE_PROJECT_NAME})
          SET_TARGET_PROPERTIES (
              ${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}${TARGET_EXTENSION} PROPERTIES
              POSITION_INDEPENDENT_CODE ON
              )
      endif()
  endif()

  target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}${TARGET_EXTENSION} PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})
  # Had to comment this out for windows... 
  # target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}${TARGET_EXTENSION} ${CMAKE_PROJECT_NAME}-static)
  if(ANDROID)
      # target_link_libraries( main ${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}${TARGET_EXTENSION})
    # target_compile_definitions(main PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})
  endif()
  list(APPEND EXTRA_LIBS ${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}${TARGET_EXTENSION})
  list(APPEND INTERFACE_FILES ${LUA_SWIG_SOURCE_FILES})







  set(_INSTALL_LIBS "${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}${TARGET_EXTENSION}" ${_INSTALL_LIBS})
  target_include_directories(${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}${TARGET_EXTENSION}
    PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS}>
    PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES}>
    )
target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}${TARGET_EXTENSION} PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})

  #                    if(NOT LINUX AND NOT EMSCRIPTEN AND NOT IOS AND NOT TVOS AND NOT ANDROID)

  #                      if(${CMAKE_VERSION} VERSION_LESS "3.8")
  #                        swig_add_module(
  #                          ${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}
  #                          lua
  #                          "${LUA_SWIG_SOURCE_FILES}"
  #                          )
  #                      else()
  #                        swig_add_library(
  #                          ${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}
  #                          TYPE SHARED
  #                          LANGUAGE lua
  #                          SOURCES "${LUA_SWIG_SOURCE_FILES}"
  #                          )
  #                      endif()
  #                      target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER} PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})

  #                      if(APPLE)
  #                        set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER} PROPERTIES MACOSX_RPATH 1)
  #                        # if(IOS OR TVOS)
  #                        #   SET_TARGET_PROPERTIES (
  #                        #     ${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER} PROPERTIES
  #                        #     XCODE_ATTRIBUTE_ENABLE_BITCODE "NO"
  #                        #     XCODE_PRODUCT_TYPE "com.apple.product-type.library.dynamic"
  #                        #     )
  #                        # endif()
  #                      elseif(UNIX AND NOT ANDROID)
  #                        set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER} PROPERTIES
  #                          VERSION ${LT_VERSION}
  #                          SOVERSION ${LT_REVISION}
  #                          OUTPUT_NAME "${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}-${LT_RELEASE}")
  #                      else()
  #                        # set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER} PROPERTIES
  #                        #   VERSION ${${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}}
  #                        #   SOVERSION ${LT_REVISION}
  #                        #   OUTPUT_NAME "${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}")
  #                      endif()
  #                      if(MSVC AND NOT LIBC)
  #                        list(APPEND EXTRA_LIBS "msvcrt.lib")
  #                        # Don't try to link with the default set of libraries.
  #                        set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER} PROPERTIES LINK_FLAGS_RELEASE "/NODEFAULTLIB:LIBCMT")
  #                        set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER} PROPERTIES LINK_FLAGS_DEBUG "/NODEFAULTLIB:LIBCMT")
  #                        target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER} ${EXTRA_LDFLAGS} debug "msvcrtd.lib")
  #                      endif()
  #                      target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER} ${CMAKE_PROJECT_NAME}-static)

  #                      set(_INSTALL_LIBS "${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}" ${_INSTALL_LIBS})
  #                      target_include_directories(${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}
  #                        PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS}>
  #                        PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES}>
  #                        )
  #                      target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER} PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})
  #                    endif()

  #                    if(NOT EMSCRIPTEN AND NOT IOS AND NOT TVOS AND NOT ANDROID AND NOT LINUX)
  #                      #So... non-mobile (WINDOWS, LINUX, MAC

  #                      if(${CMAKE_VERSION} VERSION_LESS "3.8")
  #                        MESSAGE(FATAL_ERROR "Cannot make a swig module with a version less than 3.8")
  #                      else()
  #                        swig_add_library(
  #                          ${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}-module
  #                          TYPE MODULE
  #                          LANGUAGE lua
  #                          SOURCES "${LUA_SWIG_SOURCE_FILES}"
  #                          )
  #                      endif()
  #                      target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}-module PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})

  #                      if(APPLE)
  #                        set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}-module PROPERTIES MACOSX_RPATH 1)
  #                        # if(IOS OR TVOS)
  #                        #   SET_TARGET_PROPERTIES (
  #                        #     ${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}-module PROPERTIES
  #                        #     XCODE_ATTRIBUTE_ENABLE_BITCODE "NO"
  #                        #     XCODE_PRODUCT_TYPE "com.apple.product-type.library.dynamic"
  #                        #     )
  #                        # endif()
  #                      elseif(UNIX AND NOT ANDROID)
  #                        set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}-module PROPERTIES
  #                          VERSION ${LT_VERSION}
  #                          SOVERSION ${LT_REVISION}
  #                          OUTPUT_NAME "${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}-module-${LT_RELEASE}")
  #                      else()
  #                        # set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}-module PROPERTIES
  #                        #   VERSION ${${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}}
  #                        #   SOVERSION ${LT_REVISION}
  #                        #   OUTPUT_NAME "${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}-module")
  #                      endif()
  #                      if(MSVC AND NOT LIBC)
  #                        list(APPEND EXTRA_LIBS "msvcrt.lib")
  #                        # Don't try to link with the default set of libraries.
  #                        set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}-module PROPERTIES LINK_FLAGS_RELEASE "/NODEFAULTLIB:LIBCMT")
  #                        set_target_properties(${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}-module PROPERTIES LINK_FLAGS_DEBUG "/NODEFAULTLIB:LIBCMT")
  #                        target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}-module ${EXTRA_LDFLAGS} debug "msvcrtd.lib")
  #                      endif()
  #                      target_link_libraries(${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}-module ${CMAKE_PROJECT_NAME}-static)

  #                      set(_INSTALL_LIBS "${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}-module" ${_INSTALL_LIBS})
  #                      target_include_directories(${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}-module
  #                        PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS}>
  #                        PRIVATE $<BUILD_INTERFACE:${${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES}>
  #                        )
  #                      target_compile_definitions(${CMAKE_PROJECT_NAME}-lua-swig-${INTERFACE_NAME_LOWER}-module PUBLIC ${${CMAKE_PROJECT_NAME}_DEFINITIONS})
  #                    endif()

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

      if(RASPBERRYPI)
	      set(CMAKE_SWIG_OUTDIR "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/.swig/lua/raspberrypi")
	      set(SWIG_OUTFILE_DIR "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/.swig/lua/raspberrypi")
      else()
	      set(CMAKE_SWIG_OUTDIR "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/.swig/lua/${CMAKE_SYSTEM_NAME}")
	      set(SWIG_OUTFILE_DIR "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/.swig/lua/${CMAKE_SYSTEM_NAME}")
      endif()

      if(ANDROID)
        if(${ANDROID_ABI} STREQUAL "armeabi-v7a" OR ${ANDROID_ABI} STREQUAL "x86")
          list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS ${ANDROID_SYSROOT}/usr/include/arm-linux-androideabi)
        elseif(${ANDROID_ABI} STREQUAL "arm64-v8a" OR ${ANDROID_ABI} STREQUAL "x86_64")
          list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS ${ANDROID_SYSROOT}/usr/include/aarch64-linux-android)
        elseif(${ANDROID_ABI} STREQUAL "x86")
          list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS ${ANDROID_SYSROOT}/usr/include/i686-linux-android)
        elseif(${ANDROID_ABI} STREQUAL "x86_64")
          list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS ${ANDROID_SYSROOT}/usr/include/x86_64-linux-android)
        endif()

        # include_directories(${${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS})
        # include_directories(${${CMAKE_PROJECT_NAME}_PROJECT_INCLUDE_DIRECTORES})
      endif()

      if(MSVC AND NOT LIBC)
        add_definitions(-DSTATIC_LINKED)
      endif()

      configure_file("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njlic/_Defines.swg.in"
          "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njlic/_Defines.swg")

      # LUA_NJLIC_SWIG()
      # LUA_BULLET3_SWIG()
      # LUA_GLM_SWIG()

      LUA_SWIG(NJLIC TRUE)
      LUA_SWIG(BULLET3 TRUE "thirdparty")
      # LUA_SWIG(GLM "thirdparty")

      file(GLOB_RECURSE LUA_SWIG_GENERATED_FILES
        "${SWIG_OUTFILE_DIR}/*.c*"
        )

      set_property(DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${LUA_SWIG_GENERATED_FILES})
      set_source_files_properties( ${LUA_SWIG_GENERATED_FILES} PROPERTIES GENERATED TRUE )
    endif()
  endif()
endif()
