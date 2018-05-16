
message(STATUS "Platform is ios for project")

DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("bullet"
  "https://www.dropbox.com/s/4j68y5239qdydve/LIBBULLET_1.3.5_ios.tar.gz?dl=0"
  "thirdparty/bullet/lib/ios")

IF( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "fmod" )
  message(STATUS "need to add fmod lib")
ELSEIF( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "openal" )
  list(APPEND EXTRA_LIBS "-framework OpenAL")
ELSEIF( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "sdl" )
  message(STATUS "need to add sdl lib")
ENDIF()

list(APPEND EXTRA_LIBS "-framework OpenGLES")

