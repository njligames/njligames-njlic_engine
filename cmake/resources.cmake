set( GAME_RESOURCES "${GAMEPROJECT_REPO_DIRECTORY}/assets" )
list(APPEND RESOURCE_FILES ${GAME_RESOURCES})

if(EMSCRIPTEN)
  list(APPEND EXTRA_LDFLAGS "--memory-init-file 1")
  list(APPEND EXTRA_LDFLAGS "--embed-file ${GAME_RESOURCES}@/")
endif()

set(LUA_RESOURCE_FILES "${LUA_ETC_LOCAL_INCLUDE_DIRECTORIES}/lua.ico" "${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/lua.rc")
set(LUAC_RESOURCE_FILES "${LUA_ETC_LOCAL_INCLUDE_DIRECTORIES}/lua_lang.ico" "${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/luac.rc")

if(WINDOWS)
  set( LUA_ASSET_CATALOGUE "${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/lua.rc" )
  list(APPEND LUA_RESOURCE_FILES ${LUA_ASSET_CATALOGUE})

  set( LUAC_ASSET_CATALOGUE "${LUA_SRC_LOCAL_INCLUDE_DIRECTORIES}/luac.rc" )
  list(APPEND LUAC_RESOURCE_FILES ${LUAC_ASSET_CATALOGUE})
endif()
