set(LIBRARY_NAME "zlib")

set(INCLUDE_URL "https://www.dropbox.com/s/9r6ej0lupnzkkpe/libzlib_include.tar.gz?dl=0")

set(EMSCRIPTEN_DEBUG_URL "https://www.dropbox.com/s/b6qzjqwm4gniew1/libzlib_emscripten_Debug.tar.gz?dl=0")
set(EMSCRIPTEN_MINSIZEREL_URL "https://www.dropbox.com/s/u5o7sxbkw3nfi0m/libzlib_emscripten_MinSizeRel.tar.gz?dl=0")
set(EMSCRIPTEN_RELEASE_URL "https://www.dropbox.com/s/nhqvlwrbug69fz3/libzlib_emscripten_Release.tar.gz?dl=0")
set(EMSCRIPTEN_RELWITHDEBINFO_URL "https://www.dropbox.com/s/nlu8mdh7r9qys1q/libzlib_emscripten_RelWithDebugInfo.tar.gz?dl=0")

set(WINDOWS32_DEBUG_URL "")
set(WINDOWS32_MINSIZEREL_URL "")
set(WINDOWS32_RELEASE_URL "")
set(WINDOWS32_RELWITHDEBINFO_URL "")

set(WINDOWS64_DEBUG_URL "")
set(WINDOWS64_MINSIZEREL_URL "")
set(WINDOWS64_RELEASE_URL "")
set(WINDOWS64_RELWITHDEBINFO_URL "")

set(IOS_DEVICE_DEBUG_URL "https://www.dropbox.com/s/8vh63tmjdx6tf23/libzlib_ios_Debug-iphoneos.tar.gz?dl=0")
set(IOS_SIMULATOR_DEBUG_URL "https://www.dropbox.com/s/s6xnlturft5xe34/libzlib_ios_Debug-iphonesimulator.tar.gz?dl=0")
set(IOS_DEVICE_MINSIZEREL_URL "https://www.dropbox.com/s/lpu9c53kc59ksbw/libzlib_ios_MinsizeRel-iphoneos.tar.gz?dl=0")
set(IOS_SIMULATOR_MINSIZEREL_URL "https://www.dropbox.com/s/zz29l58b60ll5en/libzlib_ios_MinsizeRel-iphonesimulator.tar.gz?dl=0")
set(IOS_DEVICE_RELEASE_URL "https://www.dropbox.com/s/m3dslw3kdxwgk59/libzlib_ios_Release-iphoneos.tar.gz?dl=0")
set(IOS_SIMULATOR_RELEASE_URL "https://www.dropbox.com/s/ckv2j5twccfgnic/libzlib_ios_Release-iphonesimulator.tar.gz?dl=0")
set(IOS_DEVICE_RELWITHDEBINFO_URL "https://www.dropbox.com/s/we8c0cwez6b41m3/libzlib_ios_RelWithDebugInfo-iphoneos.tar.gz?dl=0")
set(IOS_SIMULATOR_RELWITHDEBINFO_URL "https://www.dropbox.com/s/5q5z1nb4i60zmug/libzlib_ios_RelWithDebugInfo-iphonesimulator.tar.gz?dl=0")

set(APPLETV_DEVICE_DEBUG_URL "")
set(APPLETV_SIMULATOR_DEBUG_URL "")
set(APPLETV_DEVICE_MINSIZEREL_URL "")
set(APPLETV_SIMULATOR_MINSIZEREL_URL "")
set(APPLETV_DEVICE_RELEASE_URL "")
set(APPLETV_SIMULATOR_RELEASE_URL "")
set(APPLETV_DEVICE_RELWITHDEBINFO_URL "")
set(APPLETV_SIMULATOR_RELWITHDEBINFO_URL "")

set(MACOS_DEBUG_URL "https://www.dropbox.com/s/w2jv4tph75yswbu/libzlib_macos_Debug.tar.gz?dl=0")
set(MACOS_RELEASE_URL "https://www.dropbox.com/s/fkosgk3g7cfvjof/libzlib_macos_Release.tar.gz?dl=0")
set(MACOS_MINSIZEREL_URL "https://www.dropbox.com/s/gbfugy14cj6qs30/libzlib_macos_MinsizeRel.tar.gz?dl=0")
set(MACOS_RELWITHDEBINFO_URL "https://www.dropbox.com/s/x542mfp9xyet0ju/libzlib_macos_RelWithDebugInfo.tar.gz?dl=0")

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

set(ANDROID_arm64-v8a_DEBUG_URL     "https://www.dropbox.com/s/pvlugafuhmns73x/libzlib_android_Debug-arm64-v8a.tar.gz?dl=0")
set(ANDROID_armeabi-v7a_DEBUG_URL   "https://www.dropbox.com/s/ygg005e6unw9uvx/libzlib_android_Debug-armeabi-v7a.tar.gz?dl=0")
set(ANDROID_x86_64_DEBUG_URL        "https://www.dropbox.com/s/30o2sqa00i77roz/libzlib_android_Debug-x86_64.tar.gz?dl=0")
set(ANDROID_x86_DEBUG_URL           "https://www.dropbox.com/s/3iembua3jsyzmdt/libzlib_android_Debug-x86.tar.gz?dl=0")

set(ANDROID_arm64-v8a_RELEASE_URL   "https://www.dropbox.com/s/cqmm1k2rem70pzs/libzlib_android_Release-arm64-v8a.tar.gz?dl=0")
set(ANDROID_armeabi-v7a_RELEASE_URL "https://www.dropbox.com/s/umqskhehtv1inab/libzlib_android_Release-armeabi-v7a.tar.gz?dl=0")
set(ANDROID_x86_64_RELEASE_URL      "https://www.dropbox.com/s/1cergox3zyy2r46/libzlib_android_Release-x86_64.tar.gz?dl=0")
set(ANDROID_x86_RELEASE_URL         "https://www.dropbox.com/s/x22ex2mze9niggs/libzlib_android_Release-x86.tar.gz?dl=0")

###########################################################################################################################

include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadLibrary.cmake")
