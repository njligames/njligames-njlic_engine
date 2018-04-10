# General source files
file(GLOB SOURCE_FILES
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/src/*.c
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/src/*.cpp
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/src/*.cxx
  )

if(OCULUS)
  file(GLOB MAIN_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/src/main/oculus_rift_sdl2_opengl_demo.cpp
    )
elseif(VR)
  file(GLOB MAIN_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/src/main/vr_main.cpp
    )
else()
  file(GLOB MAIN_FILES
    ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/src/main/main.cpp
    )
endif()

file(GLOB INCLUDE_FILES
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/include/*.h
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/include/*.hpp
  ${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/include/*.hxx
  )
