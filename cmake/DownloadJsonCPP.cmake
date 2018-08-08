set(LIBRARY_NAME "jsoncpp")

set(INCLUDE_URL "https://www.dropbox.com/s/7tqgfvuygusxlbd/libjsoncpp_includes.tar.gz?dl=0")

set(EMSCRIPTEN_DEBUG_URL "https://www.dropbox.com/s/nketminya5lj7j3/libjsoncpp_emscripten_Debug.tar.gz?dl=0")
set(EMSCRIPTEN_RELEASE_URL "https://www.dropbox.com/s/dl9c9kgesdg7zil/libjsoncpp_emscripten_Release.tar.gz?dl=0")

set(WINDOWS32_DEBUG_URL "https://www.dropbox.com/s/zllvsm3esdte1ej/libjsoncpp_windows32_Debug.tar.gz?dl=0")
set(WINDOWS32_RELEASE_URL "https://www.dropbox.com/s/bje4gfkt1av5lyc/libjsoncpp_windows32_Release.tar.gz?dl=0")

set(WINDOWS64_DEBUG_URL "")
set(WINDOWS64_RELEASE_URL "")

set(IOS_DEVICE_DEBUG_URL "https://www.dropbox.com/s/4ne9v1vew6yan2k/libjsoncpp_ios_Debug-iphoneos.tar.gz?dl=0")
set(IOS_SIMULATOR_DEBUG_URL "https://www.dropbox.com/s/n2rnwjazs8jh4um/libjsoncpp_ios_Debug-iphonesimulator.tar.gz?dl=0")
set(IOS_DEVICE_RELEASE_URL "https://www.dropbox.com/s/7m9i9zp77zzuz4m/libjsoncpp_ios_Release-iphoneos.tar.gz?dl=0")
set(IOS_SIMULATOR_RELEASE_URL "https://www.dropbox.com/s/c5vu7gnrlw6spw7/libjsoncpp_ios_Release-iphonesimulator.tar.gz?dl=0")

set(APPLETV_DEVICE_DEBUG_URL "https://www.dropbox.com/s/rk8iszobjo7n9fb/libjsoncpp_appletv_Debug-appletvos.tar.gz?dl=0")
set(APPLETV_SIMULATOR_DEBUG_URL "https://www.dropbox.com/s/3sd1unj8b4fd6wp/libjsoncpp_appletv_Debug-appletvsimulator.tar.gz?dl=0")
set(APPLETV_DEVICE_RELEASE_URL "https://www.dropbox.com/s/7bxo0j1cmxdz2pv/libjsoncpp_appletv_Release-appletvos.tar.gz?dl=0")
set(APPLETV_SIMULATOR_RELEASE_URL "https://www.dropbox.com/s/xoiplxcr4my2yqn/libjsoncpp_appletv_Release-appletvsimulator.tar.gz?dl=0")

set(MACOS_DEBUG_URL "https://www.dropbox.com/s/4ho6qfymeuxor2r/libjsoncpp_macos_Debug.tar.gz?dl=0")
set(MACOS_RELEASE_URL "https://www.dropbox.com/s/clvfj12666rtd7q/libjsoncpp_macos_Release.tar.gz?dl=0")

set(LINUX_DEBUG_URL "https://www.dropbox.com/s/57vn3yu9bx3acvm/libjsoncpp_linux_Debug.tar.gz?dl=0")
set(LINUX_RELEASE_URL "https://www.dropbox.com/s/mesfvmvrmz3hcqc/libjsoncpp_linux_Release.tar.gz?dl=0")

set(UNIX_DEBUG_URL "")
set(UNIX_RELEASE_URL "")

set(ANDROID_arm64-v8a_DEBUG_URL     "https://www.dropbox.com/s/wcohdjkkj0zflp8/libjsoncpp_android_Debug-arm64-v8a.tar.gz?dl=0")
set(ANDROID_armeabi-v7a_DEBUG_URL   "https://www.dropbox.com/s/1dld6ttli04qtlm/libjsoncpp_android_Debug-armeabi-v7a.tar.gz?dl=0")
set(ANDROID_x86_64_DEBUG_URL        "https://www.dropbox.com/s/emq385dchc4za4q/libjsoncpp_android_Debug-x86_64.tar.gz?dl=0")
set(ANDROID_x86_DEBUG_URL           "https://www.dropbox.com/s/yk6w4sp0qwbpv6p/libjsoncpp_android_Debug-x86.tar.gz?dl=0")

set(ANDROID_arm64-v8a_RELEASE_URL   "https://www.dropbox.com/s/7vmgcezs6o1v80m/libjsoncpp_android_Release-arm64-v8a.tar.gz?dl=0")
set(ANDROID_armeabi-v7a_RELEASE_URL "https://www.dropbox.com/s/ysn0qz74fki0t7i/libjsoncpp_android_Release-armeabi-v7a.tar.gz?dl=0")
set(ANDROID_x86_64_RELEASE_URL      "https://www.dropbox.com/s/g8o1l7gu4qnionu/libjsoncpp_android_Release-x86_64.tar.gz?dl=0")
set(ANDROID_x86_RELEASE_URL         "https://www.dropbox.com/s/tezdiji1ol2jxnx/libjsoncpp_android_Release-x86.tar.gz?dl=0")

###########################################################################################################################

set(PLATFORM_PATH_SUFFIX_RELEASE "Release")
set(PLATFORM_PATH_SUFFIX_DEBUG "Debug")

###########################################################################################################################

string(TOUPPER ${LIBRARY_NAME} LIBRARY_NAME_UPPER)
set(${LIBRARY_NAME_UPPER}_BASE_PATH "thirdparty/${LIBRARY_NAME}")

set(THIRDPARTY_${LIBRARY_NAME_UPPER}_INCLUDE_URL "${INCLUDE_URL}" CACHE STRING "The URL for include Bullet3")
mark_as_advanced(${THIRDPARTY_${LIBRARY_NAME_UPPER}_INCLUDE_URL})

unset(THIRDPARTY_${LIBRARY_NAME_UPPER}_DEBUG_URL CACHE)
unset(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELEASE_URL CACHE)

if(EMSCRIPTEN)
  set(${LIBRARY_NAME_UPPER}_BASE_PATH "${${LIBRARY_NAME_UPPER}_BASE_PATH}/lib/emscripten")
  if(EMSCRIPTEN_DEBUG_URL)
    set(THIRDPARTY_${LIBRARY_NAME_UPPER}_DEBUG_URL "${EMSCRIPTEN_DEBUG_URL}" CACHE STRING "The URL for Debug Bullet3")
  endif()
  if(EMSCRIPTEN_RELEASE_URL)
    set(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELEASE_URL "${EMSCRIPTEN_RELEASE_URL}" CACHE STRING "The URL for Release Bullet3")
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
  else()
    set(${LIBRARY_NAME_UPPER}_BASE_PATH "${${LIBRARY_NAME_UPPER}_BASE_PATH}/lib/windows32")
    if(WINDOWS32_DEBUG_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_DEBUG_URL "${WINDOWS32_DEBUG_URL}" CACHE STRING "The URL for Debug Bullet3")
    endif()
    if(WINDOWS32_RELEASE_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELEASE_URL "${WINDOWS32_RELEASE_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()
  endif()
elseif(APPLE)
  if(IOS)
    set(PLATFORM_PATH_SUFFIX_RELEASE "Release-iphoneos")
    set(PLATFORM_PATH_SUFFIX_DEBUG "Debug-iphoneos")

    set(PLATFORM_SIMULATOR_PATH_SUFFIX_RELEASE "Release-iphonesimulator")
    set(PLATFORM_SIMULATOR_PATH_SUFFIX_DEBUG "Debug-iphonesimulator")

    set(${LIBRARY_NAME_UPPER}_BASE_PATH "${${LIBRARY_NAME_UPPER}_BASE_PATH}/lib/ios")
    if(IOS_DEVICE_DEBUG_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_DEBUG_URL "${IOS_DEVICE_DEBUG_URL}" CACHE STRING "The URL for Debug Bullet3")
    endif()
    if(IOS_DEVICE_RELEASE_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELEASE_URL "${IOS_DEVICE_RELEASE_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()
    if(IOS_SIMULATOR_DEBUG_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_DEBUG_URL "${IOS_SIMULATOR_DEBUG_URL}" CACHE STRING "The URL for Debug Bullet3 in the Simulator")
    endif()
    if(IOS_SIMULATOR_RELEASE_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_RELEASE_URL "${IOS_SIMULATOR_RELEASE_URL}" CACHE STRING "The URL for Release Bullet3 in the Simulator")
    endif()

  elseif(TVOS)
    set(PLATFORM_PATH_SUFFIX_RELEASE "Release-appletvos")
    set(PLATFORM_PATH_SUFFIX_DEBUG "Debug-appletvos")

    set(PLATFORM_SIMULATOR_PATH_SUFFIX_RELEASE "Release-appletvsimulator")
    set(PLATFORM_SIMULATOR_PATH_SUFFIX_DEBUG "Debug-appletvsimulator")

    set(${LIBRARY_NAME_UPPER}_BASE_PATH "${${LIBRARY_NAME_UPPER}_BASE_PATH}/lib/appletv")
    if(APPLETV_DEVICE_DEBUG_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_DEBUG_URL "${APPLETV_DEVICE_DEBUG_URL}" CACHE STRING "The URL for Debug Bullet3")
    endif()
    if(APPLETV_DEVICE_RELEASE_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELEASE_URL "${APPLETV_DEVICE_RELEASE_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()
    if(APPLETV_SIMULATOR_DEBUG_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_DEBUG_URL "${APPLETV_SIMULATOR_DEBUG_URL}" CACHE STRING "The URL for Debug Bullet3")
    endif()
    if(APPLETV_SIMULATOR_RELEASE_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_SIMULATOR_RELEASE_URL "${APPLETV_SIMULATOR_RELEASE_URL}" CACHE STRING "The URL for Release Bullet3")
    endif()

  else()
    set(${LIBRARY_NAME_UPPER}_BASE_PATH "${${LIBRARY_NAME_UPPER}_BASE_PATH}/lib/macos")
    if(MACOS_DEBUG_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_DEBUG_URL "${MACOS_DEBUG_URL}" CACHE STRING "The URL for Debug Bullet3")
    endif()
    if(MACOS_RELEASE_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELEASE_URL "${MACOS_RELEASE_URL}" CACHE STRING "The URL for Release Bullet3")
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
  elseif(UNIX)
    set(${LIBRARY_NAME_UPPER}_BASE_PATH "${${LIBRARY_NAME_UPPER}_BASE_PATH}/lib/unix")
    if(UNIX_DEBUG_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_DEBUG_URL "${UNIX_DEBUG_URL}" CACHE STRING "The URL for Debug Bullet3")
    endif()
    if(UNIX_RELEASE_URL)
      set(THIRDPARTY_${LIBRARY_NAME_UPPER}_RELEASE_URL "${UNIX_RELEASE_URL}" CACHE STRING "The URL for Release Bullet3")
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
  endif()

  #         if(ANDROID_ARMEABI_DEBUG_URL)
  #           set(THIRDPARTY_${LIBRARY_NAME_UPPER}_ARMEABI_DEBUG_URL ${ANDROID_ARMEABI_DEBUG_URL} CACHE STRING "The URL for Bullet3")
  #           mark_as_advanced(${THIRDPARTY_${LIBRARY_NAME_UPPER}_ARMEABI_DEBUG_URL})
  #           DOWNLOAD_LIBRARY_TAR(
  #             "${LIBRARY_NAME}"
  #             "${THIRDPARTY_${LIBRARY_NAME_UPPER}_ARMEABI_DEBUG_URL}"
  #             "${${LIBRARY_NAME_UPPER}_BASE_PATH}/${ANDROID_ABI}/Debug"
  #             )
  #         endif()

  #         if(ANDROID_X86_64_DEBUG_URL)
  #           set(THIRDPARTY_${LIBRARY_NAME_UPPER}_X86_64_DEBUG_URL ${ANDROID_X86_64_DEBUG_URL} CACHE STRING "The URL for Bullet3")
  #           mark_as_advanced(${THIRDPARTY_${LIBRARY_NAME_UPPER}_X86_64_DEBUG_URL})
  #           DOWNLOAD_LIBRARY_TAR(
  #             "${LIBRARY_NAME}"
  #             "${THIRDPARTY_${LIBRARY_NAME_UPPER}_X86_64_DEBUG_URL}"
  #             "${${LIBRARY_NAME_UPPER}_BASE_PATH}/${ANDROID_ABI}/Debug"
  #             )
  #         endif()

  #         if(ANDROID_X86_DEBUG_URL)
  #           set(THIRDPARTY_${LIBRARY_NAME_UPPER}_X86_DEBUG_URL ${ANDROID_X86_DEBUG_URL} CACHE STRING "The URL for Bullet3")
  #           mark_as_advanced(${THIRDPARTY_${LIBRARY_NAME_UPPER}_X86_DEBUG_URL})
  #           DOWNLOAD_LIBRARY_TAR(
  #             "${LIBRARY_NAME}"
  #             "${THIRDPARTY_${LIBRARY_NAME_UPPER}_X86_DEBUG_URL}"
  #             "${${LIBRARY_NAME_UPPER}_BASE_PATH}/${ANDROID_ABI}/Debug"
  #             )
  #         endif()

  # 

  if(ANDROID_${ANDROID_ABI}_RELEASE_URL)
    set(THIRDPARTY_${LIBRARY_NAME_UPPER}_${ANDROID_ABI}_RELEASE_URL ${ANDROID_${ANDROID_ABI}_RELEASE_URL} CACHE STRING "The URL for Bullet3")
    mark_as_advanced(${THIRDPARTY_${LIBRARY_NAME_UPPER}_${ANDROID_ABI}_RELEASE_URL})
    DOWNLOAD_LIBRARY_TAR(
      "${LIBRARY_NAME}"
      "${THIRDPARTY_${LIBRARY_NAME_UPPER}_${ANDROID_ABI}_RELEASE_URL}"
      "${${LIBRARY_NAME_UPPER}_BASE_PATH}/${ANDROID_ABI}/Release"
      )
  endif()

  #              if(ANDROID_ARMEABI_RELEASE_URL)
  #                set(THIRDPARTY_${LIBRARY_NAME_UPPER}_ARMEABI_RELEASE_URL ${ANDROID_ARMEABI_RELEASE_URL} CACHE STRING "The URL for Bullet3")
  #                mark_as_advanced(${THIRDPARTY_${LIBRARY_NAME_UPPER}_ARMEABI_RELEASE_URL})
  #                DOWNLOAD_LIBRARY_TAR(
  #                  "${LIBRARY_NAME}"
  #                  "${THIRDPARTY_${LIBRARY_NAME_UPPER}_ARMEABI_RELEASE_URL}"
  #                  "${${LIBRARY_NAME_UPPER}_BASE_PATH}/${ANDROID_ABI}/Release"
  #                  )
  #              endif()

  #              if(ANDROID_X86_64_RELEASE_URL)
  #                set(THIRDPARTY_${LIBRARY_NAME_UPPER}_X86_64_RELEASE_URL ${ANDROID_X86_64_RELEASE_URL} CACHE STRING "The URL for Bullet3")
  #                mark_as_advanced(${THIRDPARTY_${LIBRARY_NAME_UPPER}_X86_64_RELEASE_URL})
  #                DOWNLOAD_LIBRARY_TAR(
  #                  "${LIBRARY_NAME}"
  #                  "${THIRDPARTY_${LIBRARY_NAME_UPPER}_X86_64_RELEASE_URL}"
  #                  "${${LIBRARY_NAME_UPPER}_BASE_PATH}/${ANDROID_ABI}/Release"
  #                  )
  #              endif()

  #              if(ANDROID_X86_RELEASE_URL)
  #                set(THIRDPARTY_${LIBRARY_NAME_UPPER}_X86_RELEASE_URL ${ANDROID_X86_RELEASE_URL} CACHE STRING "The URL for Bullet3")
  #                mark_as_advanced(${THIRDPARTY_${LIBRARY_NAME_UPPER}_X86_RELEASE_URL})
  #                DOWNLOAD_LIBRARY_TAR(
  #                  "${LIBRARY_NAME}"
  #                  "${THIRDPARTY_${LIBRARY_NAME_UPPER}_X86_RELEASE_URL}"
  #                  "${${LIBRARY_NAME_UPPER}_BASE_PATH}/${ANDROID_ABI}/Release"
  #                  )
  #              endif()

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

if(THIRDPARTY_${LIBRARY_NAME_UPPER}_INCLUDE_URL)
  DOWNLOAD_LIBRARY_INCLUDE_FILES(
    "${LIBRARY_NAME}"
    "${THIRDPARTY_${LIBRARY_NAME_UPPER}_INCLUDE_URL}"
    "${${LIBRARY_NAME_UPPER}_BASE_PATH}/include"
    )

  SUBDIRLIST(SUBDIRS "${CMAKE_BINARY_DIR}/${${LIBRARY_NAME_UPPER}_BASE_PATH}/include" ${LIBRARY_NAME_UPPER}_INCLUDE_DIRS)
  list(APPEND ${LIBRARY_NAME_UPPER}_INCLUDE_DIRS "${CMAKE_BINARY_DIR}/${${LIBRARY_NAME_UPPER}_BASE_PATH}/include")
endif()

