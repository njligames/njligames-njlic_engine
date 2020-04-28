set(LIBRARY_NAME "tinyxml2")

set(INCLUDE_URL "https://www.dropbox.com/s/qa58up3igx3citn/libtinyxml2_includes.tar.gz?dl=0")

set(EMSCRIPTEN_DEBUG_URL "")
set(EMSCRIPTEN_RELEASE_URL "")
set(EMSCRIPTEN_MINSIZEREL_URL "")
set(EMSCRIPTEN_RELWITHDEBINFO_URL "")

set(WINDOWS32_DEBUG_URL "")
set(WINDOWS32_MINSIZEREL_URL "")
set(WINDOWS32_RELEASE_URL "")
set(WINDOWS32_RELWITHDEBINFO_URL "")

set(WINDOWS64_DEBUG_URL "")
set(WINDOWS64_MINSIZEREL_URL "")
set(WINDOWS64_RELEASE_URL "")
set(WINDOWS64_RELWITHDEBINFO_URL "")

set(IOS_DEVICE_DEBUG_URL "")
set(IOS_SIMULATOR_DEBUG_URL "")
set(IOS_DEVICE_MINSIZEREL_URL "")
set(IOS_SIMULATOR_MINSIZEREL_URL "")
set(IOS_DEVICE_RELEASE_URL "")
set(IOS_SIMULATOR_RELEASE_URL "")
set(IOS_DEVICE_RELWITHDEBINFO_URL "")
set(IOS_SIMULATOR_RELWITHDEBINFO_URL "")

set(APPLETV_DEVICE_DEBUG_URL "")
set(APPLETV_SIMULATOR_DEBUG_URL "")
set(APPLETV_DEVICE_MINSIZEREL_URL "")
set(APPLETV_SIMULATOR_MINSIZEREL_URL "")
set(APPLETV_DEVICE_RELEASE_URL "")
set(APPLETV_SIMULATOR_RELEASE_URL "")
set(APPLETV_DEVICE_RELWITHDEBINFO_URL "")
set(APPLETV_SIMULATOR_RELWITHDEBINFO_URL "")

set(MACOS_DEBUG_URL "https://www.dropbox.com/s/s61ju7reo831oja/libtinyxml2_macos_Debug.tar.gz?dl=0")
set(MACOS_RELEASE_URL "https://www.dropbox.com/s/h351ioiza5c92s0/libtinyxml2_macos_Release.tar.gz?dl=0")
set(MACOS_MINSIZEREL_URL "https://www.dropbox.com/s/ly6rioegrim7dqr/libtinyxml2_macos_MinsizeRel.tar.gz?dl=0")
set(MACOS_RELWITHDEBINFO_URL "https://www.dropbox.com/s/38myt9zkr9q48y5/libtinyxml2_macos_RelWithDebugInfo.tar.gz?dl=0")

set(LINUX_DEBUG_URL "")
set(LINUX_MINSIZEREL_URL "")
set(LINUX_RELEASE_URL "")
set(LINUX_RELWITHDEBINFO_URL "")

set(RASPBERRY_DEBUG_URL "")
set(RASPBERRY_MINSIZEREL_URL "")
set(RASPBERRY_RELEASE_URL "")
set(RASPBERRY_RELWITHDEBINFO_URL "")

set(UNIX_DEBUG_URL "")
set(UNIX_MINSIZEREL_URL "")
set(UNIX_RELEASE_URL "")
set(UNIX_RELWITHDEBINFO_URL "")

set(ANDROID_arm64-v8a_DEBUG_URL     "")
set(ANDROID_armeabi-v7a_DEBUG_URL   "")
set(ANDROID_x86_64_DEBUG_URL        "")
set(ANDROID_x86_DEBUG_URL           "")

set(ANDROID_arm64-v8a_RELEASE_URL   "")
set(ANDROID_armeabi-v7a_RELEASE_URL "")
set(ANDROID_x86_64_RELEASE_URL      "")
set(ANDROID_x86_RELEASE_URL         "")

###########################################################################################################################

include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadLibrary.cmake")