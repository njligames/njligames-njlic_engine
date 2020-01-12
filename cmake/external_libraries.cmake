
OPTION(THIRDPARTY_BULLET3_ENABLED "Use bullet3 library" ON)
mark_as_advanced(${THIRDPARTY_BULLET3_ENABLED})
OPTION(USE_BULLET3_LIBRARY "bullet3 typedef" ${THIRDPARTY_BULLET3_ENABLED})

OPTION(THIRDPARTY_BULLET3_DOWNLOAD "Use bullet3 library" ON)
mark_as_advanced(${THIRDPARTY_BULLET3_DOWNLOAD})
OPTION(DOWNLOAD_BULLET3_LIBRARY "bullet3 typedef" ${THIRDPARTY_BULLET3_DOWNLOAD})


OPTION(THIRDPARTY_DEBUGDRAW_ENABLED "Use DebugDraw library" ON)
mark_as_advanced(${THIRDPARTY_DEBUGDRAW_ENABLED})
OPTION(USE_DEBUGDRAW_LIBRARY "debugdraw typedef" ${THIRDPARTY_DEBUGDRAW_ENABLED})

OPTION(THIRDPARTY_DEBUGDRAW_ENABLED "Use DebugDraw library" ON)
mark_as_advanced(${THIRDPARTY_DEBUGDRAW_ENABLED})
OPTION(DOWNLOAD_DEBUGDRAW_ENABLED "debugdraw typedef" ${THIRDPARTY_DEBUGDRAW_ENABLED})


OPTION(THIRDPARTY_GLM_ENABLED "Use GLM library" ON)
mark_as_advanced(${THIRDPARTY_GLM_ENABLED})
OPTION(USE_GLM_LIBRARY "glm typedef" ${THIRDPARTY_GLM_ENABLED})

OPTION(THIRDPARTY_GLM_ENABLED "Use GLM library" ON)
mark_as_advanced(${THIRDPARTY_GLM_ENABLED})
OPTION(DOWNLOAD_GLM_ENABLED "glm typedef" ${THIRDPARTY_GLM_ENABLED})


OPTION(THIRDPARTY_IMGUI_ENABLED "Use ImGui library" ON)
mark_as_advanced(${THIRDPARTY_IMGUI_ENABLED})
OPTION(USE_IMGUI_LIBRARY "imgui typedef" ${THIRDPARTY_IMGUI_ENABLED})

OPTION(THIRDPARTY_IMGUI_ENABLED "Use ImGui library" ON)
mark_as_advanced(${THIRDPARTY_IMGUI_ENABLED})
OPTION(DOWNLOAD_IMGUI_ENABLED "imgui typedef" ${THIRDPARTY_IMGUI_ENABLED})


OPTION(THIRDPARTY_IMGUIZMO_ENABLED "Use ImGuizmo library" ON)
mark_as_advanced(${THIRDPARTY_IMGUIZMO_ENABLED})
OPTION(USE_IMGUIZMO_LIBRARY "imguizmo typedef" ${THIRDPARTY_IMGUIZMO_ENABLED})

OPTION(THIRDPARTY_IMGUIZMO_ENABLED "Use ImGuizmo library" ON)
mark_as_advanced(${THIRDPARTY_IMGUIZMO_ENABLED})
OPTION(DOWNLOAD_IMGUIZMO_ENABLED "imguizmo typedef" ${THIRDPARTY_IMGUIZMO_ENABLED})


OPTION(THIRDPARTY_JSONCPP_ENABLED "Use JsonCPP library" OFF)
mark_as_advanced(${THIRDPARTY_JSONCPP_ENABLED})
OPTION(USE_JSONCPP_LIBRARY "jsoncpp typedef" ${THIRDPARTY_JSONCPP_ENABLED})

OPTION(THIRDPARTY_JSONCPP_ENABLED "Use JsonCPP library" OFF)
mark_as_advanced(${THIRDPARTY_JSONCPP_ENABLED})
OPTION(DOWNLOAD_JSONCPP_ENABLED "jsoncpp typedef" ${THIRDPARTY_JSONCPP_ENABLED})


OPTION(THIRDPARTY_NANOVG_ENABLED "Use Nanovg library" OFF)
mark_as_advanced(${THIRDPARTY_NANOVG_ENABLED})
OPTION(USE_NANOVG_LIBRARY "nanovg typedef" ${THIRDPARTY_NANOVG_ENABLED})

OPTION(THIRDPARTY_NANOVG_ENABLED "Use Nanovg library" OFF)
mark_as_advanced(${THIRDPARTY_NANOVG_ENABLED})
OPTION(DOWNLOAD_NANOVG_ENABLED "nanovg typedef" ${THIRDPARTY_NANOVG_ENABLED})


OPTION(THIRDPARTY_OPENCV_ENABLED "Use OpenCV library" OFF)
mark_as_advanced(${THIRDPARTY_OPENCV_ENABLED})
OPTION(USE_OPENCV_LIBRARY "opencv typedef" ${THIRDPARTY_OPENCV_ENABLED})

OPTION(THIRDPARTY_OPENCV_DOWNLOAD "Use OpenCV library" OFF)
mark_as_advanced(${THIRDPARTY_OPENCV_DOWNLOAD})
OPTION(DOWNLOAD_OPENCV_LIBRARY "opencv typedef" ${THIRDPARTY_OPENCV_DOWNLOAD})


OPTION(THIRDPARTY_TINYXML2_ENABLED "Use TinyXml library" OFF)
mark_as_advanced(${THIRDPARTY_TINYXML2_ENABLED})
OPTION(USE_TINYXML2_LIBRARY "opencv typedef" ${THIRDPARTY_TINYXML2_ENABLED})

OPTION(THIRDPARTY_TINYXML2_DOWNLOAD "Use OpenCV library" OFF)
mark_as_advanced(${THIRDPARTY_TINYXML2_DOWNLOAD})
OPTION(DOWNLOAD_TINYXML2_LIBRARY "opencv typedef" ${THIRDPARTY_TINYXML2_DOWNLOAD})


OPTION(THIRDPARTY_ZLIB_ENABLED "Use zlib library" ON)
mark_as_advanced(${THIRDPARTY_ZLIB_ENABLED})
OPTION(USE_ZLIB_LIBRARY "zlib typedef" ${THIRDPARTY_ZLIB_ENABLED})

OPTION(THIRDPARTY_ZLIB_DOWNLOAD "Use ZLib library" ON)
mark_as_advanced(${THIRDPARTY_ZLIB_DOWNLOAD})
OPTION(DOWNLOAD_ZLIB_LIBRARY "zlib typedef" ${THIRDPARTY_ZLIB_DOWNLOAD})


set(${CMAKE_PROJECT_NAME}_SOUND_PLATFORM "openal" CACHE STRING "The rendering platform to use")
set(${CMAKE_PROJECT_NAME}_SOUND_PLATFORM_Values "openal;fmod;sdl")
set_property(CACHE ${CMAKE_PROJECT_NAME}_SOUND_PLATFORM PROPERTY STRINGS ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM_Values})

set(FMOD OFF)
set(OPENAL OFF)
set(SDL_SOUND OFF)

IF ("${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM}" STREQUAL "fmod")
    set(FMOD ON)
    add_definitions(-D__FMOD__)
ELSEIF ("${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM}" STREQUAL "openal")

    OPTION(THIRDPARTY_OGG_DOWNLOAD "Download OGG library" ON)
    mark_as_advanced(${THIRDPARTY_OGG_DOWNLOAD})
    OPTION(DOWNLOAD_OGG_LIBRARY "ogg typedef" ${THIRDPARTY_OGG_DOWNLOAD})

    OPTION(THIRDPARTY_VORBIS_DOWNLOAD "Download Vorbis library" ON)
    mark_as_advanced(${THIRDPARTY_VORBIS_DOWNLOAD})
    OPTION(DOWNLOAD_VORBIS_LIBRARY "vorbis typedef" ${THIRDPARTY_VORBIS_DOWNLOAD})


    set(OPENAL ON)
    add_definitions(-D__OPENAL__)
ELSEIF ("${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM}" STREQUAL "sdl")
    set(SDL_SOUND ON)
    add_definitions(-D__SDL_SOUND__)
ENDIF ()

OPTION(__FMOD__ "fmod include" ${FMOD})
OPTION(__OPENAL__ "OpenAL include" ${OPENAL})
OPTION(__SDL__ "SDL2 sound include" ${SDL_SOUND})

list(APPEND CMAKE_MODULE_PATH "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake")

IF (USE_BULLET3_LIBRARY)
    if (DOWNLOAD_BULLET3_LIBRARY)
        include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadBullet3.cmake")
        list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${BULLET3_INCLUDE_DIRS}")
    endif ()

    find_package(Bullet3 REQUIRED)
    list(APPEND EXTRA_LIBS ${BULLET3_TARGETS})

    list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${BULLET3_INCLUDE_DIR}")
endif ()

IF (USE_DEBUGDRAW_LIBRARY)
    include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadDebug-Draw.cmake")
    list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${DEBUG-DRAW_INCLUDE_DIRS}")

    find_package(Debug-Draw REQUIRED)
    list(APPEND EXTRA_LIBS ${DEBUG-DRAW_TARGETS})

    list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${DEBUG-DRAW_INCLUDE_DIR}")
endif ()

IF (USE_GLM_LIBRARY)
    include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadGLM.cmake")
    list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${GLM_INCLUDE_DIRS}")

    find_package(GLM REQUIRED)
    list(APPEND EXTRA_LIBS ${GLM_TARGETS})

    list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${GLM_INCLUDE_DIR}")
endif ()

IF (USE_IMGUI_LIBRARY)
    include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadImGui.cmake")
    list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${IMGUI_INCLUDE_DIRS}")

    find_package(ImGui REQUIRED)
    list(APPEND EXTRA_LIBS ${IMGUI_TARGETS})

    list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${IMGUI_INCLUDE_DIR}")
endif ()

IF (USE_IMGUIZMO_LIBRARY)
    include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadImGuizmo.cmake")
    list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${IMGUIZMO_INCLUDE_DIRS}")

    find_package(ImGuizmo REQUIRED)
    list(APPEND EXTRA_LIBS ${IMGUIZMO_TARGETS})

    list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${IMGUIZMO_INCLUDE_DIR}")
endif ()

IF (USE_JSONCPP_LIBRARY)
    include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadJsonCPP.cmake")
    list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${JSONCPP_INCLUDE_DIRS}")

    find_package(JsonCPP REQUIRED)
    list(APPEND EXTRA_LIBS ${JSONCPP_TARGETS})

    list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${JSONCPP_INCLUDE_DIR}")
endif ()

IF (USE_NANOVG_LIBRARY)
    include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadNanoVG.cmake")
    list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${NANOVG_INCLUDE_DIRS}")

    find_package(NanoVG REQUIRED)
    list(APPEND EXTRA_LIBS ${NANOVG_TARGETS})

    list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${NANOVG_INCLUDE_DIR}")
endif ()

IF (USE_OPENCV_LIBRARY)
    if (DOWNLOAD_OPENCV_LIBRARY)
        include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadOpenCV.cmake")
        list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${OPENCV_INCLUDE_DIRS}")
    endif ()

    find_package(OpenCV REQUIRED)
    list(APPEND EXTRA_LIBS ${OPENCV_TARGETS})

    list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${OPENCV_INCLUDE_DIR}")
endif ()


IF (USE_TINYXML2_LIBRARY)
    if (DOWNLOAD_TINYXML2_LIBRARY)
        include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadTinyXml2.cmake")
        list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${TINYXML2_INCLUDE_DIRS}")
    endif ()

    find_package(TinyXml2 REQUIRED)
    list(APPEND EXTRA_LIBS ${TINYXML2_TARGETS})

    list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${TINYXML2_INCLUDE_DIR}")
endif ()


IF (USE_ZLIB_LIBRARY)
    if (DOWNLOAD_ZLIB_LIBRARY)
        include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadZLib.cmake")
        list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${ZLIB_INCLUDE_DIRS}")
    endif ()

    find_package(ZLib REQUIRED)
    list(APPEND EXTRA_LIBS ${ZLIB_TARGETS})

    list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${ZLIB_INCLUDE_DIR}")
endif ()


if (FMOD)
    message(STATUS "need to add fmod lib")
elseif (OPENAL)

    OPTION(USE_OGG_LIBRARY "ogg include" ON)
    OPTION(USE_VORBIS_LIBRARY "vorbis include" ON)


    if (DOWNLOAD_VORBIS_LIBRARY)
        include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadVorbis.cmake")
        list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${VORBIS_INCLUDE_DIRS}")
    endif ()
    find_package(Vorbis REQUIRED)
    list(APPEND EXTRA_LIBS ${VORBIS_TARGETS})


    if (DOWNLOAD_OGG_LIBRARY)
        include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadOGG.cmake")
        list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${OGG_INCLUDE_DIRS}")
    endif ()
    find_package(OGG REQUIRED)
    list(APPEND EXTRA_LIBS ${OGG_TARGETS})


    if (EMSCRIPTEN)
        MESSAGE(STATUS "No need to include openal")
    elseif (WINDOWS)
        if (ARCH_64)
            include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadOpenAL.cmake")
            list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${OPENAL_INCLUDE_DIRS}")
            find_package(OpenAL_NJLIC REQUIRED)
            list(APPEND EXTRA_LIBS ${OPENAL_TARGETS})
        else ()
            include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadOpenAL.cmake")
            list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${OPENAL_INCLUDE_DIRS}")
            find_package(OpenAL_NJLIC REQUIRED)
            list(APPEND EXTRA_LIBS ${OPENAL_TARGETS})
        endif ()
    elseif (APPLE)
        if (IOS)
            list(APPEND EXTRA_LIBS "-framework OpenAL")
        elseif (TVOS)
            list(APPEND EXTRA_LIBS "-framework OpenAL")
        else ()
            list(APPEND EXTRA_LIBS "-framework OpenAL")
        endif ()
    elseif (UNIX AND NOT APPLE AND NOT ANDROID)
        if (LINUX)
            find_package(OpenAL REQUIRED)
            if (OPENAL_FOUND)
                MESSAGE(STATUS "OPENAL_INCLUDE_DIR ${OPENAL_INCLUDE_DIR}")
                MESSAGE(STATUS "OPENAL_LIBRARY ${OPENAL_LIBRARY}")
                list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRECTORES "${OPENAL_INCLUDE_DIR}")
                list(APPEND EXTRA_LIBS "${OPENAL_LIBRARY}")
            endif ()
        elseif (UNIX)
            MESSAGE(STATUS "No need to include openal")
        endif ()
    elseif (ANDROID)
        include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadOpenAL.cmake")
        list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${OPENAL_INCLUDE_DIRS}")
        find_package(OpenAL_NJLIC REQUIRED)
        list(APPEND EXTRA_LIBS ${OPENAL_TARGETS})

        FIND_LIBRARY(OpenSLES-lib OpenSLES)
        list(APPEND EXTRA_LIBS "${OpenSLES-lib}")
    endif ()

elseif (SDL_SOUND)
    message(STATUS "need to add sdl lib")
endif ()

include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/DownloadSTBImages.cmake")
list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS "${STBIMAGES_INCLUDE_DIRS}")
# MESSAGE(FATAL_ERROR "STBIMAGES_INCLUDE_DIRS ${STBIMAGES_INCLUDE_DIRS}         ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS ${${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS}")

find_package(STBImages REQUIRED)
list(APPEND EXTRA_LIBS ${STBIMAGES_TARGETS})
add_definitions(-DSTB_IMAGE_IMPLEMENTATION=1)


########################################################################################

if (EMSCRIPTEN)
    include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/emscripten_external_libraries.cmake")
elseif (WINDOWS)
    if (ARCH_64)
        if (OCULUS)
            include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/oculus_windows64_external_libraries.cmake")
        else ()
            include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/windows64_external_libraries.cmake")
        endif ()
    else ()
        if (OCULUS)
            include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/oculus_windows32_external_libraries.cmake")
        else ()
            include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/windows32_external_libraries.cmake")
        endif ()
    endif ()
elseif (APPLE)
    if (IOS)
        if (VR)
            include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/vr_ios_external_libraries.cmake")
        else ()
            include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/ios_external_libraries.cmake")
        endif ()
    elseif (TVOS)
        include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/appletv_external_libraries.cmake")
    else ()
        if (OCULUS)
            include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/oculus_macos_external_libraries.cmake")
        else ()
            include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/macos_external_libraries.cmake")
        endif ()
    endif ()
elseif (UNIX AND NOT APPLE AND NOT ANDROID)
    if (LINUX)
        if (OCULUS)
            include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/oculus_linux_external_libraries.cmake")
        else ()
            include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/linux_external_libraries.cmake")
        endif ()
    elseif (UNIX)
        include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/unix_external_libraries.cmake")
    endif ()
elseif (ANDROID)
    if (VR)
        include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/vr_android_external_libraries.cmake")
    else ()
        include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/android_external_libraries.cmake")
    endif ()
endif ()
