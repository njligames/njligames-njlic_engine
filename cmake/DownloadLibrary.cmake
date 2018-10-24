
set(PLATFORM_PATH_SUFFIX_DEBUG "Debug")
set(PLATFORM_PATH_SUFFIX_RELEASE "Release")
set(PLATFORM_PATH_SUFFIX_MINSIZEREL "MinsizeRel")
set(PLATFORM_PATH_SUFFIX_RELWITHDEBINFO "RelWithDebInfo")

###########################################################################################################################

string(TOUPPER ${LIBRARY_NAME} LIBRARY_NAME_UPPER)
set(${LIBRARY_NAME_UPPER}_BASE_PATH "thirdparty/${LIBRARY_NAME}")

set(THIRDPARTY_${LIBRARY_NAME_UPPER}_INCLUDE_URL "${INCLUDE_URL}" CACHE STRING "The URL for include Bullet3")
mark_as_advanced(${THIRDPARTY_${LIBRARY_NAME_UPPER}_INCLUDE_URL})

unset(THIRDPARTY_${LIBRARY_NAME_UPPER}_DEBUG_URL CACHE)
unset(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELEASE_URL CACHE)
unset(THIRDPARTY_${LIBRARY_NAME_UPPER}_MINSIZEREL_URL CACHE)
unset(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELWITHDEBINFO_URL CACHE)

if(EMSCRIPTEN)
  set(${LIBRARY_NAME_UPPER}_BASE_PATH "${${LIBRARY_NAME_UPPER}_BASE_PATH}/lib/emscripten")
  if(EMSCRIPTEN_DEBUG_URL)
    set(THIRDPARTY_${LIBRARY_NAME_UPPER}_DEBUG_URL "${EMSCRIPTEN_DEBUG_URL}" CACHE STRING "The URL for Debug Bullet3")
  endif()
  if(EMSCRIPTEN_RELEASE_URL)
    set(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELEASE_URL "${EMSCRIPTEN_RELEASE_URL}" CACHE STRING "The URL for Release Bullet3")
  endif()
  if(EMSCRIPTEN_MINSIZEREL_URL)
    set(THIRDPARTY_${LIBRARY_NAME_UPPER}_MINSIZEREL_URL "${EMSCRIPTEN_MINSIZEREL_URL}" CACHE STRING "The URL for Release Bullet3")
  endif()
  if(EMSCRIPTEN_RELWITHDEBINFO_URL)
    set(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELWITHDEBINFO_URL "${EMSCRIPTEN_RELWITHDEBINFO_URL}" CACHE STRING "The URL for Release Bullet3")
  endif()
elseif(WINDOWS)
  if(ARCH_64)
    set(${LIBRARY_NAME_UPPER}_BASE_PATH "${${LIBRARY_NAME_UPPER}_BASE_PATH}/lib/windows64")
    if(WINDOWS64_DEBUG_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_DEBUG_URL "${WINDOWS64_DEBUG_URL}" CACHE STRING "The URL for Debug Bullet3")
    endif()
    if(WINDOWS64_RELEASE_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELEASE_URL "${WINDOWS64_RELEASE_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()
    if(WINDOWS64_MINSIZEREL_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_MINSIZEREL_URL "${WINDOWS64_MINSIZEREL_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()
    if(WINDOWS64_RELWITHDEBINFO_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELWITHDEBINFO_URL "${WINDOWS64_RELWITHDEBINFO_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()
  else()
    set(${LIBRARY_NAME_UPPER}_BASE_PATH "${${LIBRARY_NAME_UPPER}_BASE_PATH}/lib/windows32")
    if(WINDOWS32_DEBUG_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_DEBUG_URL "${WINDOWS32_DEBUG_URL}" CACHE STRING "The URL for Debug Bullet3")
    endif()
    if(WINDOWS32_RELEASE_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELEASE_URL "${WINDOWS32_RELEASE_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()
    if(WINDOWS32_MINSIZEREL_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_MINSIZEREL_URL "${WINDOWS32_MINSIZEREL_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()
    if(WINDOWS32_RELWITHDEBINFO_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELWITHDEBINFO_URL "${WINDOWS32_RELWITHDEBINFO_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()
  endif()
elseif(APPLE)
  if(IOS)
    set(PLATFORM_PATH_SUFFIX_DEBUG "Debug-iphoneos")
    set(PLATFORM_SIMULATOR_PATH_SUFFIX_DEBUG "Debug-iphonesimulator")

    set(PLATFORM_PATH_SUFFIX_RELEASE "Release-iphoneos")
    set(PLATFORM_SIMULATOR_PATH_SUFFIX_RELEASE "Release-iphonesimulator")

    set(PLATFORM_PATH_SUFFIX_MINSIZEREL "MinsizeRel-iphoneos")
    set(PLATFORM_SIMULATOR_PATH_SUFFIX_MINSIZEREL "MinsizeRel-iphonesimulator")

    set(PLATFORM_PATH_SUFFIX_RELWITHDEBINFO "RelWithDebInfo-iphoneos")
    set(PLATFORM_SIMULATOR_PATH_SUFFIX_RELWITHDEBINFO "RelWithDebInfo-iphonesimulator")

    set(${LIBRARY_NAME_UPPER}_BASE_PATH "${${LIBRARY_NAME_UPPER}_BASE_PATH}/lib/ios")

    if(IOS_DEVICE_DEBUG_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_DEBUG_URL "${IOS_DEVICE_DEBUG_URL}" CACHE STRING "The URL for Debug Bullet3")
    endif()
    if(IOS_SIMULATOR_DEBUG_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_DEBUG_URL "${IOS_SIMULATOR_DEBUG_URL}" CACHE STRING "The URL for Debug Bullet3 in the Simulator")
    endif()

   if(IOS_DEVICE_MINSIZEREL_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_MINSIZEREL_URL "${IOS_DEVICE_MINSIZEREL_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()
    if(IOS_SIMULATOR_MINSIZEREL_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_MINSIZEREL_URL "${IOS_SIMULATOR_MINSIZEREL_URL}" CACHE STRING "The URL for Release Bullet3 in the Simulator")
    endif()

    if(IOS_DEVICE_RELEASE_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELEASE_URL "${IOS_DEVICE_RELEASE_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()
    if(IOS_SIMULATOR_RELEASE_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_RELEASE_URL "${IOS_SIMULATOR_RELEASE_URL}" CACHE STRING "The URL for Release Bullet3 in the Simulator")
    endif()

    if(IOS_DEVICE_RELWITHDEBINFO_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELWITHDEBINFO_URL "${IOS_DEVICE_RELWITHDEBINFO_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()
    if(IOS_SIMULATOR_RELWITHDEBINFO_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_RELWITHDEBINFO_URL "${IOS_SIMULATOR_RELWITHDEBINFO_URL}" CACHE STRING "The URL for Release Bullet3 in the Simulator")
    endif()

  elseif(TVOS)
    set(PLATFORM_PATH_SUFFIX_RELEASE "Release-appletvos")
    set(PLATFORM_SIMULATOR_PATH_SUFFIX_RELEASE "Release-appletvsimulator")

    set(PLATFORM_PATH_SUFFIX_DEBUG "Debug-appletvos")
    set(PLATFORM_SIMULATOR_PATH_SUFFIX_DEBUG "Debug-appletvsimulator")

    set(PLATFORM_PATH_SUFFIX_MINSIZEREL "MinsizeRel-appletvos")
    set(PLATFORM_SIMULATOR_PATH_SUFFIX_MINSIZEREL "MinsizeRel-appletvsimulator")

    set(PLATFORM_PATH_SUFFIX_RELWITHDEBINFO "RelWithDebInfo-appletvos")
    set(PLATFORM_SIMULATOR_PATH_SUFFIX_RELWITHDEBINFO "RelWithDebInfo-appletvsimulator")

    set(${LIBRARY_NAME_UPPER}_BASE_PATH "${${LIBRARY_NAME_UPPER}_BASE_PATH}/lib/appletv")
    if(APPLETV_DEVICE_DEBUG_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_DEBUG_URL "${APPLETV_DEVICE_DEBUG_URL}" CACHE STRING "The URL for Debug Bullet3")
    endif()
    if(APPLETV_DEVICE_RELEASE_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELEASE_URL "${APPLETV_DEVICE_RELEASE_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()

    if(APPLETV_DEVICE_MINSIZEREL_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_MINSIZEREL_URL "${APPLETV_DEVICE_MINSIZEREL_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()
    if(APPLETV_SIMULATOR_MINSIZEREL_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_MINSIZEREL_URL "${APPLETV_SIMULATOR_MINSIZEREL_URL}" CACHE STRING "The URL for Release Bullet3 in the Simulator")
    endif()

    if(APPLETV_SIMULATOR_DEBUG_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_DEBUG_URL "${APPLETV_SIMULATOR_DEBUG_URL}" CACHE STRING "The URL for Debug Bullet3")
    endif()
    if(APPLETV_SIMULATOR_RELEASE_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_RELEASE_URL "${APPLETV_SIMULATOR_RELEASE_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()

    if(APPLETV_DEVICE_RELWITHDEBINFO_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELWITHDEBINFO_URL "${APPLETV_DEVICE_RELWITHDEBINFO_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()
    if(APPLETV_SIMULATOR_RELWITHDEBINFO_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_RELWITHDEBINFO_URL "${APPLETV_SIMULATOR_RELWITHDEBINFO_URL}" CACHE STRING "The URL for Release Bullet3 in the Simulator")
    endif()
  else()
    set(${LIBRARY_NAME_UPPER}_BASE_PATH "${${LIBRARY_NAME_UPPER}_BASE_PATH}/lib/macos")
    if(MACOS_DEBUG_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_DEBUG_URL "${MACOS_DEBUG_URL}" CACHE STRING "The URL for Debug Bullet3")
    endif()
    if(MACOS_RELEASE_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELEASE_URL "${MACOS_RELEASE_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()
    if(MACOS_MINSIZEREL_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_MINSIZEREL_URL "${MACOS_MINSIZEREL_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()
    if(MACOS_RELWITHDEBINFO_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELWITHDEBINFO_URL "${MACOS_RELWITHDEBINFO_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()
  endif()
elseif(UNIX AND NOT APPLE AND NOT ANDROID)
  if(LINUX)
    set(${LIBRARY_NAME_UPPER}_BASE_PATH "${${LIBRARY_NAME_UPPER}_BASE_PATH}/lib/linux")
    if(LINUX_DEBUG_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_DEBUG_URL "${LINUX_DEBUG_URL}" CACHE STRING "The URL for Debug Bullet3")
    endif()
    if(LINUX_RELEASE_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELEASE_URL "${LINUX_RELEASE_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()
    if(LINUX_MINSIZEREL_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_MINSIZEREL_URL "${LINUX_MINSIZEREL_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()
    if(LINUX_RELWITHDEBINFO_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELWITHDEBINFO_URL "${LINUX_RELWITHDEBINFO_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()
  elseif(UNIX)
    set(${LIBRARY_NAME_UPPER}_BASE_PATH "${${LIBRARY_NAME_UPPER}_BASE_PATH}/lib/unix")
    if(UNIX_DEBUG_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_DEBUG_URL "${UNIX_DEBUG_URL}" CACHE STRING "The URL for Debug Bullet3")
    endif()
    if(UNIX_RELEASE_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELEASE_URL "${UNIX_RELEASE_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()
    if(UNIX_MINSIZEREL_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_MINSIZEREL_URL "${UNIX_MINSIZEREL_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()
    if(UNIX_RELWITHDEBINFO_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELWITHDEBINFO_URL "${UNIX_RELWITHDEBINFO_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()
  endif()
elseif(ANDROID)

  set(${LIBRARY_NAME_UPPER}_BASE_PATH "${${LIBRARY_NAME_UPPER}_BASE_PATH}/lib/android")

  if(ANDROID_${ANDROID_ABI}_DEBUG_URL)
    set(THIRDPARTY_${LIBRARY_NAME_UPPER}_${ANDROID_ABI}_DEBUG_URL ${ANDROID_${ANDROID_ABI}_DEBUG_URL} CACHE STRING "The URL for Bullet3")
    mark_as_advanced(${THIRDPARTY_${LIBRARY_NAME_UPPER}_${ANDROID_ABI}_DEBUG_URL})
    DOWNLOAD_LIBRARY_TAR(
      "${LIBRARY_NAME}"
      "${THIRDPARTY_${LIBRARY_NAME_UPPER}_${ANDROID_ABI}_DEBUG_URL}"
      "${${LIBRARY_NAME_UPPER}_BASE_PATH}/${ANDROID_ABI}/Debug"
      )
    file(GLOB DL_LIBRARIES "${CMAKE_BINARY_DIR}/${${LIBRARY_NAME_UPPER}_BASE_PATH}/${ANDROID_ABI}/Debug/*.so")
    list(APPEND ${ANDROID_ABI}_LIBRARIES ${DL_LIBRARIES})
  endif()

  if(ANDROID_${ANDROID_ABI}_RELEASE_URL)
    set(THIRDPARTY_${LIBRARY_NAME_UPPER}_${ANDROID_ABI}_RELEASE_URL ${ANDROID_${ANDROID_ABI}_RELEASE_URL} CACHE STRING "The URL for Bullet3")
    mark_as_advanced(${THIRDPARTY_${LIBRARY_NAME_UPPER}_${ANDROID_ABI}_RELEASE_URL})
    DOWNLOAD_LIBRARY_TAR(
      "${LIBRARY_NAME}"
      "${THIRDPARTY_${LIBRARY_NAME_UPPER}_${ANDROID_ABI}_RELEASE_URL}"
      "${${LIBRARY_NAME_UPPER}_BASE_PATH}/${ANDROID_ABI}/Release"
      )
    file(GLOB DL_LIBRARIES "${CMAKE_BINARY_DIR}/${${LIBRARY_NAME_UPPER}_BASE_PATH}/${ANDROID_ABI}/Release/*.so")
    list(APPEND ${ANDROID_ABI}_LIBRARIES ${DL_LIBRARIES})
  endif()

endif()

if(THIRDPARTY_${LIBRARY_NAME_UPPER}_DEBUG_URL)
  mark_as_advanced(${THIRDPARTY_${LIBRARY_NAME_UPPER}_DEBUG_URL})
  if(THIRDPARTY_${LIBRARY_NAME_UPPER}_DEBUG_URL)
    DOWNLOAD_LIBRARY_TAR(
      "${LIBRARY_NAME}"
      "${THIRDPARTY_${LIBRARY_NAME_UPPER}_DEBUG_URL}"
      "${${LIBRARY_NAME_UPPER}_BASE_PATH}/${PLATFORM_PATH_SUFFIX_DEBUG}"
      )
  endif()
endif()

if(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELEASE_URL)
  mark_as_advanced(${THIRDPARTY_${LIBRARY_NAME_UPPER}_RELEASE_URL})
  if(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELEASE_URL)
    DOWNLOAD_LIBRARY_TAR(
      "${LIBRARY_NAME}"
      "${THIRDPARTY_${LIBRARY_NAME_UPPER}_RELEASE_URL}"
      "${${LIBRARY_NAME_UPPER}_BASE_PATH}/${PLATFORM_PATH_SUFFIX_RELEASE}"
      )
  endif()
endif()

if(THIRDPARTY_${LIBRARY_NAME_UPPER}_MINSIZEREL_URL)
  mark_as_advanced(${THIRDPARTY_${LIBRARY_NAME_UPPER}_MINSIZEREL_URL})
  if(THIRDPARTY_${LIBRARY_NAME_UPPER}_MINSIZEREL_URL)
    DOWNLOAD_LIBRARY_TAR(
      "${LIBRARY_NAME}"
      "${THIRDPARTY_${LIBRARY_NAME_UPPER}_MINSIZEREL_URL}"
      "${${LIBRARY_NAME_UPPER}_BASE_PATH}/${PLATFORM_PATH_SUFFIX_MINSIZEREL}"
      )
  endif()
endif()

if(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELWITHDEBINFO_URL)
  mark_as_advanced(${THIRDPARTY_${LIBRARY_NAME_UPPER}_RELWITHDEBINFO_URL})
  if(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELWITHDEBINFO_URL)
    DOWNLOAD_LIBRARY_TAR(
      "${LIBRARY_NAME}"
      "${THIRDPARTY_${LIBRARY_NAME_UPPER}_RELWITHDEBINFO_URL}"
      "${${LIBRARY_NAME_UPPER}_BASE_PATH}/${PLATFORM_PATH_SUFFIX_RELWITHDEBINFO}"
      )
  endif()
endif()

if(THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_DEBUG_URL)
  mark_as_advanced(${THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_DEBUG_URL})
  if(THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_DEBUG_URL)
    DOWNLOAD_LIBRARY_TAR(
      "${LIBRARY_NAME}"
      "${THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_DEBUG_URL}"
      "${${LIBRARY_NAME_UPPER}_BASE_PATH}/${PLATFORM_SIMULATOR_PATH_SUFFIX_DEBUG}"
      )
  endif()
endif()

if(THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_RELEASE_URL)
  mark_as_advanced(${THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_RELEASE_URL})
  if(THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_RELEASE_URL)
    DOWNLOAD_LIBRARY_TAR(
      "${LIBRARY_NAME}"
      "${THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_RELEASE_URL}"
      "${${LIBRARY_NAME_UPPER}_BASE_PATH}/${PLATFORM_SIMULATOR_PATH_SUFFIX_RELEASE}"
      )
  endif()
endif()

if(THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_MINSIZEREL_URL)
  mark_as_advanced(${THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_MINSIZEREL_URL})
  if(THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_MINSIZEREL_URL)
    DOWNLOAD_LIBRARY_TAR(
      "${LIBRARY_NAME}"
      "${THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_MINSIZEREL_URL}"
      "${${LIBRARY_NAME_UPPER}_BASE_PATH}/${PLATFORM_SIMULATOR_PATH_SUFFIX_MINSIZEREL}"
      )
  endif()
endif()

if(THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_RELWITHDEBINFO_URL)
  mark_as_advanced(${THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_RELWITHDEBINFO_URL})
  if(THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_RELWITHDEBINFO_URL)
    DOWNLOAD_LIBRARY_TAR(
      "${LIBRARY_NAME}"
      "${THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_RELWITHDEBINFO_URL}"
      "${${LIBRARY_NAME_UPPER}_BASE_PATH}/${PLATFORM_SIMULATOR_PATH_SUFFIX_RELWITHDEBINFO}"
      )
  endif()
endif()

if(THIRDPARTY_${LIBRARY_NAME_UPPER}_INCLUDE_URL)
  DOWNLOAD_LIBRARY_INCLUDE_FILES(
    "${LIBRARY_NAME}"
    "${THIRDPARTY_${LIBRARY_NAME_UPPER}_INCLUDE_URL}"
    "${${LIBRARY_NAME_UPPER}_BASE_PATH}/include"
    )

  SUBDIRLIST(SUBDIRS "${CMAKE_BINARY_DIR}/${${LIBRARY_NAME_UPPER}_BASE_PATH}/include" ${LIBRARY_NAME_UPPER}_INCLUDE_DIRS)
  list(APPEND ${LIBRARY_NAME_UPPER}_INCLUDE_DIRS "${CMAKE_BINARY_DIR}/${${LIBRARY_NAME_UPPER}_BASE_PATH}/include")
endif()
