
message(STATUS "Platform is android for project")

FIND_LIBRARY(log-lib log)
list(APPEND EXTRA_LIBS "${log-lib}")

FIND_LIBRARY(dl-lib dl)
list(APPEND EXTRA_LIBS "${dl-lib}")

# IF( GL_ES2 )
   FIND_LIBRARY(GLESv2-lib GLESv2)
   list(APPEND EXTRA_LIBS "${GLESv2-lib}")
# ELSEIF( GL_ES3 )
#   FIND_LIBRARY(GLESv3-lib GLESv3)
#   list(APPEND EXTRA_LIBS "${GLESv3-lib}")
# ELSE()
#   MESSAGE(FATAL_ERROR "opengl isn't defined for android")
# ENDIF()

FIND_LIBRARY(m-lib m)
list(APPEND EXTRA_LIBS "${m-lib}")

FIND_LIBRARY(c-lib c)
list(APPEND EXTRA_LIBS "${c-lib}")

FIND_LIBRARY(EGL-lib EGL)
list(APPEND EXTRA_LIBS "${EGL-lib}")

FIND_LIBRARY(stdc++-lib stdc++)
list(APPEND EXTRA_LIBS "${stdc++-lib}")

FIND_LIBRARY(android-lib android)
list(APPEND EXTRA_LIBS "${android-lib}")

