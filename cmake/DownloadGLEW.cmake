set(LIBRARY_NAME "glew")

set(INCLUDE_URL "https://www.dropbox.com/s/6y4hx7aqfyenlpp/libglew_include.tar.gz?dl=0")

set(EMSCRIPTEN_DEBUG_URL "")
set(EMSCRIPTEN_RELEASE_URL "")

set(WINDOWS32_DEBUG_URL "https://www.dropbox.com/s/a9gj19jqrjc488p/libglew_windows32_Release.tar.gz?dl=0")
set(WINDOWS32_RELEASE_URL "https://www.dropbox.com/s/a9gj19jqrjc488p/libglew_windows32_Release.tar.gz?dl=0")

set(WINDOWS64_DEBUG_URL "https://www.dropbox.com/s/r5jadyd7tshw23f/libglew_windows64_Release.tar.gz?dl=0")
set(WINDOWS64_RELEASE_URL "https://www.dropbox.com/s/r5jadyd7tshw23f/libglew_windows64_Release.tar.gz?dl=0")

set(IOS_DEVICE_DEBUG_URL "")
set(IOS_SIMULATOR_DEBUG_URL "")
set(IOS_DEVICE_RELEASE_URL "")
set(IOS_SIMULATOR_RELEASE_URL "")

set(APPLETV_DEVICE_DEBUG_URL "")
set(APPLETV_SIMULATOR_DEBUG_URL "")
set(APPLETV_DEVICE_RELEASE_URL "")
set(APPLETV_SIMULATOR_RELEASE_URL "")

set(MACOS_DEBUG_URL "")
set(MACOS_RELEASE_URL "")
set(MACOS_MINSIZEREL_URL "")
set(MACOS_RELWITHDEBUGINFO_URL "")

set(LINUX_DEBUG_URL "")
set(LINUX_RELEASE_URL "")

set(UNIX_DEBUG_URL "")
set(UNIX_RELEASE_URL "")

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
