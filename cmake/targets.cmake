include(${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/macros.cmake)
include(${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/swig_targets.cmake)
include(${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/doxygen.cmake)

set(CPPCHECK_FORMAT_BIN "/usr/local/bin/cppcheck" CACHE STRING "use: `brew install cppcheck` to install")
set(CLANG_FORMAT_BIN "/usr/local/bin/clang-format" CACHE STRING "use: `brew install clang-format` to install")

add_custom_target(
  cppcheck
  COMMAND ${CPPCHECK_FORMAT_BIN}
  --enable=warning,performance,portability,information,missingInclude
  --std=c++11
  --library=qt.cfg
  --template="{file},{line},{message},{callstack},{severity},{id}"
  --verbose
  ${SOURCE_FILES}
)

add_custom_target(
  clang-format
  COMMAND ${CLANG_FORMAT_BIN} -style=file -i ${SOURCE_FILES} -verbose
  SOURCES
  "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/.clang-format"
)


