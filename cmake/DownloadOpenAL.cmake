set(LIBRARY_NAME "openal")

set(INCLUDE_URL "https://www.dropbox.com/s/ykhm0omt23ocevh/libopenal_include.tar.gz?dl=0")

set(EMSCRIPTEN_DEBUG_URL "")
set(EMSCRIPTEN_RELEASE_URL "")
set(EMSCRIPTEN_MINSIZEREL_URL "")
set(EMSCRIPTEN_RELWITHDEBINFO_URL "")

set(WINDOWS32_DEBUG_URL "https://www.dropbox.com/s/hrsjgmc7nxh0iaz/libopenal_windows32_Release.tar.gz?dl=0")
set(WINDOWS32_RELEASE_URL "https://www.dropbox.com/s/hrsjgmc7nxh0iaz/libopenal_windows32_Release.tar.gz?dl=0")

set(WINDOWS64_DEBUG_URL "https://www.dropbox.com/s/esl9ch6nw0v71uw/libopenal_windows64_Release.tar.gz?dl=0")
set(WINDOWS64_RELEASE_URL "https://www.dropbox.com/s/esl9ch6nw0v71uw/libopenal_windows64_Release.tar.gz?dl=0")

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

set(MACOS_DEBUG_URL "")
set(MACOS_RELEASE_URL "")
set(MACOS_MINSIZEREL_URL "")
set(MACOS_RELWITHDEBINFO_URL "")

set(LINUX_DEBUG_URL "")
set(LINUX_RELEASE_URL "")

set(UNIX_DEBUG_URL "")
set(UNIX_RELEASE_URL "")

set(ANDROID_arm64-v8a_DEBUG_URL     "https://www.dropbox.com/s/vhl9iay1611yf62/libopenal_android_Release-arm64-v8a.tar.gz?dl=0")
set(ANDROID_armeabi-v7a_DEBUG_URL   "https://www.dropbox.com/s/kpemdgz24fyei9y/libopenal_android_Release-armeabi-v7a.tar.gz?dl=0")
set(ANDROID_x86_64_DEBUG_URL        "https://www.dropbox.com/s/llgvis7g9hhms7x/libopenal_android_Release-x86_64.tar.gz?dl=0")
set(ANDROID_x86_DEBUG_URL           "https://www.dropbox.com/s/87j34y0apm005k0/libopenal_android_Release-x86.tar.gz?dl=0")

set(ANDROID_arm64-v8a_RELEASE_URL   "https://www.dropbox.com/s/vhl9iay1611yf62/libopenal_android_Release-arm64-v8a.tar.gz?dl=0")
set(ANDROID_armeabi-v7a_RELEASE_URL "https://www.dropbox.com/s/kpemdgz24fyei9y/libopenal_android_Release-armeabi-v7a.tar.gz?dl=0")
set(ANDROID_x86_64_RELEASE_URL      "https://www.dropbox.com/s/llgvis7g9hhms7x/libopenal_android_Release-x86_64.tar.gz?dl=0")
set(ANDROID_x86_RELEASE_URL         "https://www.dropbox.com/s/87j34y0apm005k0/libopenal_android_Release-x86.tar.gz?dl=0")

###########################################################################################################################

include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadLibrary.cmake")
