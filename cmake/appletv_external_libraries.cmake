
message(STATUS "Platform is appletv for project")

# Release-appletvos #########################################################################

DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("bullet"
  "https://www.dropbox.com/s/hwfc0a7cee6idz9/libbullet3_appletv_Release-appletvos.tar.gz?dl=0"
  "thirdparty/bullet/lib/appletv/Release-appletvos"
  "thirdparty/bullet/lib/appletv/Release\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("imgui"
  "https://www.dropbox.com/s/2m9h4mrnu9ukgbf/libimgui_appletv_Release-appletvos.tar.gz?dl=0"
  "thirdparty/imgui/lib/appletv/Release-appletvos"
  "thirdparty/imgui/lib/appletv/Release\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("imguizmo"
  "https://www.dropbox.com/s/362jzsl66uneecr/libImGuizmo_appletv_Release-appletvos.tar.gz?dl=0"
  "thirdparty/imguizmo/lib/appletv/Release-appletvos"
  "thirdparty/imguizmo/lib/appletv/Release\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("jsoncpp"
  "https://www.dropbox.com/s/fggaq1wy6qtkdty/libjsoncpp_appletv_Release-appletvos.tar.gz?dl=0"
  "thirdparty/jsoncpp/lib/appletv/Release-appletvos"
  "thirdparty/jsoncpp/lib/appletv/Release\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("nanovg"
  "https://www.dropbox.com/s/092u84cy8qar4cx/libnanovg_appletv_Release-appletvos.tar.gz?dl=0"
  "thirdparty/nanovg/lib/appletv/Release-appletvos"
  "thirdparty/nanovg/lib/appletv/Release\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("ogg"
  "https://www.dropbox.com/s/u9bvv22ver6a20o/libogg_appletv_Release-appletvos.tar.gz?dl=0"
  "thirdparty/ogg/lib/appletv/Release-appletvos"
  "thirdparty/ogg/lib/appletv/Release\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("vorbis"
  "https://www.dropbox.com/s/xtyncx0xhqn7jj8/libvorbis_appletv_Release-appletvos.tar.gz?dl=0"
  "thirdparty/vorbis/lib/appletv/Release-appletvos"
  "thirdparty/vorbis/lib/appletv/Release\$(EFFECTIVE_PLATFORM_NAME)"
  )

# Release-appletvsimulator #########################################################################

DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("bullet"
  "https://www.dropbox.com/s/4j8ged3kocx4qmn/libbullet3_appletv_Release-appletvsimulator.tar.gz?dl=0"
  "thirdparty/bullet/lib/appletv/Release-appletvsimulator"
  "thirdparty/bullet/lib/appletv/Release\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("imgui"
  "https://www.dropbox.com/s/1tr1gmopy9b3ofh/libimgui_appletv_Release-appletvsimulator.tar.gz?dl=0"
  "thirdparty/imgui/lib/appletv/Release-appletvsimulator"
  "thirdparty/imgui/lib/appletv/Release\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("imguizmo"
  "https://www.dropbox.com/s/y69wapozj1ivin6/libImGuizmo_appletv_Release-appletvsimulator.tar.gz?dl=0"
  "thirdparty/imguizmo/lib/appletv/Release-appletvsimulator"
  "thirdparty/imguizmo/lib/appletv/Release\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("jsoncpp"
  "https://www.dropbox.com/s/cjlzyzp5ebhwy67/libjsoncpp_appletv_Release-appletvsimulator.tar.gz?dl=0"
  "thirdparty/jsoncpp/lib/appletv/Release-appletvsimulator"
  "thirdparty/jsoncpp/lib/appletv/Release\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("nanovg"
  "https://www.dropbox.com/s/sntbq384g0h7joy/libnanovg_appletv_Release-appletvsimulator.tar.gz?dl=0"
  "thirdparty/nanovg/lib/appletv/Release-appletvsimulator"
  "thirdparty/nanovg/lib/appletv/Release\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("ogg"
  "https://www.dropbox.com/s/b6uuo4c0qpe0ecr/libogg_appletv_Release-appletvsimulator.tar.gz?dl=0"
  "thirdparty/ogg/lib/appletv/Release-appletvsimulator"
  "thirdparty/ogg/lib/appletv/Release\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("vorbis"
  "https://www.dropbox.com/s/hx9bc7jcp4dj486/libvorbis_appletv_Release-appletvsimulator.tar.gz?dl=0"
  "thirdparty/vorbis/lib/appletv/Release-appletvsimulator"
  "thirdparty/vorbis/lib/appletv/Release\$(EFFECTIVE_PLATFORM_NAME)"
  )

# Debug-appletvos #########################################################################

DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("bullet"
  "https://www.dropbox.com/s/9z4h979t8hp6xdc/libbullet3_appletv_Debug-appletvos.tar.gz?dl=0"
  "thirdparty/bullet/lib/appletv/Debug-appletvos"
  "thirdparty/bullet/lib/appletv/Debug\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("imgui"
  "https://www.dropbox.com/s/rrmq4y7o2z25pw8/libimgui_appletv_Debug-appletvos.tar.gz?dl=0"
  "thirdparty/imgui/lib/appletv/Debug-appletvos"
  "thirdparty/imgui/lib/appletv/Debug\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("imguizmo"
  "https://www.dropbox.com/s/mj1l7mzd0wb5g8y/libImGuizmo_appletv_Debug-appletvos.tar.gz?dl=0"
  "thirdparty/imguizmo/lib/appletv/Debug-appletvos"
  "thirdparty/imguizmo/lib/appletv/Debug\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("jsoncpp"
  "https://www.dropbox.com/s/1bh0cgbtcr1mlws/libjsoncpp_appletv_Debug-appletvos.tar.gz?dl=0"
  "thirdparty/jsoncpp/lib/appletv/Debug-appletvos"
  "thirdparty/jsoncpp/lib/appletv/Debug\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("nanovg"
  "https://www.dropbox.com/s/balo9843hky9cjl/libnanovg_appletv_Debug-appletvos.tar.gz?dl=0"
  "thirdparty/nanovg/lib/appletv/Debug-appletvos"
  "thirdparty/nanovg/lib/appletv/Debug\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("ogg"
  "https://www.dropbox.com/s/pci0wdqxywuo9yg/libogg_appletv_Debug-appletvos.tar.gz?dl=0"
  "thirdparty/ogg/lib/appletv/Debug-appletvos"
  "thirdparty/ogg/lib/appletv/Debug\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("vorbis"
  "https://www.dropbox.com/s/jm7x9bk0c0y2232/libvorbis_appletv_Debug-appletvos.tar.gz?dl=0"
  "thirdparty/vorbis/lib/appletv/Debug-appletvos"
  "thirdparty/vorbis/lib/appletv/Debug\$(EFFECTIVE_PLATFORM_NAME)"
  )

# Debug-appletvsimulator #########################################################################

DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("bullet"
  "https://www.dropbox.com/s/w70pog01zfuy14c/libbullet3_appletv_Debug-appletvsimulator.tar.gz?dl=0"
  "thirdparty/bullet/lib/appletv/Debug-appletvsimulator"
  "thirdparty/bullet/lib/appletv/Debug\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("imgui"
  "https://www.dropbox.com/s/nx8o9y0loi5oyn6/libimgui_appletv_Debug-appletvsimulator.tar.gz?dl=0"
  "thirdparty/imgui/lib/appletv/Debug-appletvsimulator"
  "thirdparty/imgui/lib/appletv/Debug\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("imguizmo"
  "https://www.dropbox.com/s/7uhi5n0x8shdesb/libImGuizmo_appletv_Debug-appletvsimulator.tar.gz?dl=0"
  "thirdparty/imguizmo/lib/appletv/Debug-appletvsimulator"
  "thirdparty/imguizmo/lib/appletv/Debug\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("jsoncpp"
  "https://www.dropbox.com/s/rndoiypkqquwi0e/libjsoncpp_appletv_Debug-appletvsimulator.tar.gz?dl=0"
  "thirdparty/jsoncpp/lib/appletv/Debug-appletvsimulator"
  "thirdparty/jsoncpp/lib/appletv/Debug\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("nanovg"
  "https://www.dropbox.com/s/lvtz1vs2hx7rk4m/libnanovg_appletv_Debug-appletvsimulator.tar.gz?dl=0"
  "thirdparty/nanovg/lib/appletv/Debug-appletvsimulator"
  "thirdparty/nanovg/lib/appletv/Debug\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("ogg"
  "https://www.dropbox.com/s/d47y8ktjs5gfy64/libogg_appletv_Debug-appletvsimulator.tar.gz?dl=0"
  "thirdparty/ogg/lib/appletv/Debug-appletvsimulator"
  "thirdparty/ogg/lib/appletv/Debug\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("vorbis"
  "https://www.dropbox.com/s/5cbh1pl8ewey9p7/libvorbis_appletv_Debug-appletvsimulator.tar.gz?dl=0"
  "thirdparty/vorbis/lib/appletv/Debug-appletvsimulator"
  "thirdparty/vorbis/lib/appletv/Debug\$(EFFECTIVE_PLATFORM_NAME)"
  )

# MinsizeRel-appletvos #########################################################################

DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("bullet"
  "https://www.dropbox.com/s/hm15flmpyve0gle/libbullet3_appletv_MinsizeRel-appletvos.tar.gz?dl=0"
  "thirdparty/bullet/lib/appletv/MinsizeRel-appletvos"
  "thirdparty/bullet/lib/appletv/MinsizeRel\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("imgui"
  "https://www.dropbox.com/s/37mdyvhhhh2iac8/libimgui_appletv_MinsizeRel-appletvos.tar.gz?dl=0"
  "thirdparty/imgui/lib/appletv/MinsizeRel-appletvos"
  "thirdparty/imgui/lib/appletv/MinsizeRel\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("imguizmo"
  "https://www.dropbox.com/s/z49sj1opd621acx/libImGuizmo_appletv_MinsizeRel-appletvos.tar.gz?dl=0"
  "thirdparty/imguizmo/lib/appletv/MinsizeRel-appletvos"
  "thirdparty/imguizmo/lib/appletv/MinsizeRel\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("jsoncpp"
  "https://www.dropbox.com/s/vvrpsasg2nuprcu/libjsoncpp_appletv_MinsizeRel-appletvos.tar.gz?dl=0"
  "thirdparty/jsoncpp/lib/appletv/MinsizeRel-appletvos"
  "thirdparty/jsoncpp/lib/appletv/MinsizeRel\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("nanovg"
  "https://www.dropbox.com/s/uleivtha22nabyq/libnanovg_appletv_MinsizeRel-appletvos.tar.gz?dl=0"
  "thirdparty/nanovg/lib/appletv/MinsizeRel-appletvos"
  "thirdparty/nanovg/lib/appletv/MinsizeRel\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("ogg"
  "https://www.dropbox.com/s/jmfikyyqnumhkoi/libogg_appletv_RelWithDebugInfo-appletvos.tar.gz?dl=0"
  "thirdparty/ogg/lib/appletv/MinsizeRel-appletvos"
  "thirdparty/ogg/lib/appletv/MinsizeRel\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("vorbis"
  "https://www.dropbox.com/s/1ke1cvxnfchwsf6/libvorbis_appletv_MinsizeRel-appletvos.tar.gz?dl=0"
  "thirdparty/vorbis/lib/appletv/MinsizeRel-appletvos"
  "thirdparty/vorbis/lib/appletv/MinsizeRel\$(EFFECTIVE_PLATFORM_NAME)"
  )

# MinsizeRel-appletvsimulator #########################################################################

DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("bullet"
  "https://www.dropbox.com/s/97u5n4u1p2x2wf3/libbullet3_appletv_MinsizeRel-appletvsimulator.tar.gz?dl=0"
  "thirdparty/bullet/lib/appletv/MinsizeRel-appletvsimulator"
  "thirdparty/bullet/lib/appletv/MinsizeRel\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("imgui"
  "https://www.dropbox.com/s/yeg7hcq9683pwmn/libimgui_appletv_MinsizeRel-appletvsimulator.tar.gz?dl=0"
  "thirdparty/imgui/lib/appletv/MinsizeRel-appletvsimulator"
  "thirdparty/imgui/lib/appletv/MinsizeRel\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("imguizmo"
  "https://www.dropbox.com/s/lytzmpuap7rpfbu/libImGuizmo_appletv_MinsizeRel-appletvsimulator.tar.gz?dl=0"
  "thirdparty/imguizmo/lib/appletv/MinsizeRel-appletvsimulator"
  "thirdparty/imguizmo/lib/appletv/MinsizeRel\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("jsoncpp"
  "https://www.dropbox.com/s/sl91r54ctxyjyc7/libjsoncpp_appletv_MinsizeRel-appletvsimulator.tar.gz?dl=0"
  "thirdparty/jsoncpp/lib/appletv/MinsizeRel-appletvsimulator"
  "thirdparty/jsoncpp/lib/appletv/MinsizeRel\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("nanovg"
  "https://www.dropbox.com/s/zvxsv4ihaucr2rt/libnanovg_appletv_MinsizeRel-appletvsimulator.tar.gz?dl=0"
  "thirdparty/nanovg/lib/appletv/MinsizeRel-appletvsimulator"
  "thirdparty/nanovg/lib/appletv/MinsizeRel\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("ogg"
  "https://www.dropbox.com/s/ov5iba4vm0znnjt/libogg_appletv_MinsizeRel-appletvsimulator.tar.gz?dl=0"
  "thirdparty/ogg/lib/appletv/MinsizeRel-appletvsimulator"
  "thirdparty/ogg/lib/appletv/MinsizeRel\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_RELEASE_LIBRARY_BINARY_FILES("vorbis"
  "https://www.dropbox.com/s/cpxt32bldw9a2xe/libvorbis_appletv_MinsizeRel-appletvsimulator.tar.gz?dl=0"
  "thirdparty/vorbis/lib/appletv/MinsizeRel-appletvsimulator"
  "thirdparty/vorbis/lib/appletv/MinsizeRel\$(EFFECTIVE_PLATFORM_NAME)"
  )

# RelWithDebugInfo-appletvos #########################################################################

DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("bullet"
  "https://www.dropbox.com/s/uyh0b2na40tleis/libbullet3_appletv_RelWithDebugInfo-appletvos.tar.gz?dl=0"
  "thirdparty/bullet/lib/appletv/RelWithDebugInfo-appletvos"
  "thirdparty/bullet/lib/appletv/RelWithDebugInfo\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("imgui"
  "https://www.dropbox.com/s/qvl2k4droc3mt0p/libimgui_appletv_RelWithDebugInfo-appletvos.tar.gz?dl=0"
  "thirdparty/imgui/lib/appletv/RelWithDebugInfo-appletvos"
  "thirdparty/imgui/lib/appletv/RelWithDebugInfo\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("imguizmo"
  "https://www.dropbox.com/s/e08r61jgxae35pn/libImGuizmo_appletv_RelWithDebugInfo-appletvos.tar.gz?dl=0"
  "thirdparty/imguizmo/lib/appletv/RelWithDebugInfo-appletvos"
  "thirdparty/imguizmo/lib/appletv/RelWithDebugInfo\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("jsoncpp"
  "https://www.dropbox.com/s/udfvsy8u856rc64/libjsoncpp_appletv_RelWithDebugInfo-appletvos.tar.gz?dl=0"
  "thirdparty/jsoncpp/lib/appletv/RelWithDebugInfo-appletvos"
  "thirdparty/jsoncpp/lib/appletv/RelWithDebugInfo\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("nanovg"
  "https://www.dropbox.com/s/2jvt1nffnnee96p/libnanovg_appletv_RelWithDebugInfo-appletvos.tar.gz?dl=0"
  "thirdparty/nanovg/lib/appletv/RelWithDebugInfo-appletvos"
  "thirdparty/nanovg/lib/appletv/RelWithDebugInfo\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("ogg"
  "https://www.dropbox.com/s/jmfikyyqnumhkoi/libogg_appletv_RelWithDebugInfo-appletvos.tar.gz?dl=0"
  "thirdparty/ogg/lib/appletv/RelWithDebugInfo-appletvos"
  "thirdparty/ogg/lib/appletv/RelWithDebugInfo\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("vorbis"
  "https://www.dropbox.com/s/vqgl3290c7cib5f/libvorbis_appletv_RelWithDebugInfo-appletvos.tar.gz?dl=0"
  "thirdparty/vorbis/lib/appletv/RelWithDebugInfo-appletvos"
  "thirdparty/vorbis/lib/appletv/RelWithDebugInfo\$(EFFECTIVE_PLATFORM_NAME)"
  )

# RelWithDebugInfo-appletvsimulator #########################################################################

DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("bullet"
  "https://www.dropbox.com/s/h1dintok8rvwsiz/libbullet3_appletv_RelWithDebugInfo-appletvsimulator.tar.gz?dl=0"
  "thirdparty/bullet/lib/appletv/RelWithDebugInfo-appletvsimulator"
  "thirdparty/bullet/lib/appletv/RelWithDebugInfo\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("imgui"
  "https://www.dropbox.com/s/ofa3dx0248b4vve/libimgui_appletv_RelWithDebugInfo-appletvsimulator.tar.gz?dl=0"
  "thirdparty/imgui/lib/appletv/RelWithDebugInfo-appletvsimulator"
  "thirdparty/imgui/lib/appletv/RelWithDebugInfo\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("imguizmo"
  "https://www.dropbox.com/s/y7r7wtz6y18pnjd/libImGuizmo_appletv_RelWithDebugInfo-appletvsimulator.tar.gz?dl=0"
  "thirdparty/imguizmo/lib/appletv/RelWithDebugInfo-appletvsimulator"
  "thirdparty/imguizmo/lib/appletv/RelWithDebugInfo\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("jsoncpp"
  "https://www.dropbox.com/s/09uvzu96gm8dpbd/libjsoncpp_appletv_RelWithDebugInfo-appletvsimulator.tar.gz?dl=0"
  "thirdparty/jsoncpp/lib/appletv/RelWithDebugInfo-appletvsimulator"
  "thirdparty/jsoncpp/lib/appletv/RelWithDebugInfo\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("nanovg"
  "https://www.dropbox.com/s/sqsb9lp4mkra41z/libnanovg_appletv_RelWithDebugInfo-appletvsimulator.tar.gz?dl=0"
  "thirdparty/nanovg/lib/appletv/RelWithDebugInfo-appletvsimulator"
  "thirdparty/nanovg/lib/appletv/RelWithDebugInfo\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("ogg"
  "https://www.dropbox.com/s/6prri803u6sqibv/libogg_appletv_RelWithDebugInfo-appletvsimulator.tar.gz?dl=0"
  "thirdparty/ogg/lib/appletv/RelWithDebugInfo-appletvsimulator"
  "thirdparty/ogg/lib/appletv/RelWithDebugInfo\$(EFFECTIVE_PLATFORM_NAME)"
  )
DOWNLOAD_STATIC_DEBUG_LIBRARY_BINARY_FILES("vorbis"
  "https://www.dropbox.com/s/rcvgiufaiql280o/libvorbis_appletv_RelWithDebugInfo-appletvsimulator.tar.gz?dl=0"
  "thirdparty/vorbis/lib/appletv/RelWithDebugInfo-appletvsimulator"
  "thirdparty/vorbis/lib/appletv/RelWithDebugInfo\$(EFFECTIVE_PLATFORM_NAME)"
  )

IF( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "fmod" )
  message(STATUS "need to add fmod lib")
ELSEIF( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "openal" )
  list(APPEND EXTRA_LIBS "-framework OpenAL")
ELSEIF( ${${CMAKE_PROJECT_NAME}_SOUND_PLATFORM} STREQUAL "sdl" )
  message(STATUS "need to add sdl lib")
ENDIF()

list(APPEND EXTRA_LIBS "-framework OpenGLES")

