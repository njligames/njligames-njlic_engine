
message(STATUS "Platform is ios for project")

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
# 
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
