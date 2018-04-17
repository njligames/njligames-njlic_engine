
message(STATUS "Platform is ios for project")

macro(DOWNLOAD_LIBRARY_INCLUDE_FILES LIBNAME LIBRARY_INCLUDE_URL LIBRARY_DIRECTORY)

  set(${LIBNAME}_URL_INCLUDE 
    "${LIBRARY_INCLUDE_URL}" 
    CACHE STRING "The URL for the include files for ${LIBRARY_DIRECTORY}")

  RETRIEVE_TAR(
    "${${LIBNAME}_URL_INCLUDE}"
    "${LIBRARY_DIRECTORY}"
    "SKIP"
    )

  SUBDIRLIST(SUBDIRS "${CMAKE_BINARY_DIR}/${LIBRARY_DIRECTORY}" INCLUDE_DIRECTORY_LIST)

  include_directories("${CMAKE_BINARY_DIR}/${LIBRARY_DIRECTORY}" ${INCLUDE_DIRECTORY_LIST})

endmacro()

DOWNLOAD_LIBRARY_INCLUDE_FILES("bullet" "https://www.dropbox.com/s/bvtxtpqa925godz/BULLET-1.85_include.tar.gz?dl=0" "thirdparty/bullet-1.85/include")
DOWNLOAD_LIBRARY_INCLUDE_FILES("lua" "https://www.dropbox.com/s/4djlrt4x4ej2k8t/LUA-5.3.2_include.tar.gz?dl=0" "thirdparty/lua-5.3.2/include")

# set(${CMAKE_PROJECT_NAME}_URL_SDL2_INCLUDE 
#   "https://www.dropbox.com/s/g0qrc1xkz2qcb9y/SDL2-2.0.7_include.tar.gz?dl=0" 
#   CACHE STRING "The URL for the include files for SDL2")
# 
# set(${CMAKE_PROJECT_NAME}_URL_SDL2_LIB_IOS_RELEASE 
#   "https://www.dropbox.com/s/xsvgzfp2h4lk965/SDL2-2.0.7_ios.tar.gz?dl=0" 
#   CACHE STRING "The URL for the iOS version of SDL2"
#   )
# 
# set(SDL2_INCLUDE_DIR "thirdparty/SDL2-2.0.7/include")
# set(LIBSDL_INCLUDE_URL "${${CMAKE_PROJECT_NAME}_URL_SDL2_INCLUDE}")
# 
# RETRIEVE_TAR(
#   "${LIBSDL_INCLUDE_URL}"
#   "${SDL2_INCLUDE_DIR}"
#   "SKIP"
#   )
# 
# include_directories("${CMAKE_BINARY_DIR}/${SDL2_INCLUDE_DIR}")








# set(LIBSDL_LIBRARY_URL "${${CMAKE_PROJECT_NAME}_URL_SDL2_LIB_IOS_RELEASE}")
# set(LIBSDL_LIBRARY_TARGET_DIRECTORY "thirdparty/SDL2-2.0.7/lib/ios")
# 
# RETRIEVE_TAR(
#   "${LIBSDL_LIBRARY_URL}"
#   "${LIBSDL_LIBRARY_TARGET_DIRECTORY}"
#   "SKIP"
#   )
# 
# set(SDL_IMPORT_LOCATION "${CMAKE_BINARY_DIR}/${LIBSDL_LIBRARY_TARGET_DIRECTORY}/Release\$(EFFECTIVE_PLATFORM_NAME)/libSDL2.${STATIC_LIBRARY_EXTENSION}")
# 
# add_library(SDL2_LIBRARY STATIC IMPORTED )
# set_target_properties(SDL2_LIBRARY PROPERTIES IMPORTED_LOCATION "${SDL_IMPORT_LOCATION}")
# list(APPEND EXTRA_LIBS SDL2_LIBRARY)
