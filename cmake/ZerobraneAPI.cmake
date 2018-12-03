
# MESSAGE(FATAL_ERROR ${LUA_SWIG_SOURCE_FILES})



# add_custom_command(
#   OUTPUT ${swig_custom_output}
#   ${swig_custom_products}
#   # Let's create the ${swig_outdir} at execution time, in case dir contains $(OutDir)
#   COMMAND ${CMAKE_COMMAND} -E make_directory ${swig_outdir}
#   ${swig_timestamp_command}
#   COMMAND "${SWIG_EXECUTABLE}"
#   ARGS "-${SWIG_MODULE_${name}_SWIG_LANGUAGE_FLAG}"
#   ${swig_source_file_flags}
#   ${CMAKE_SWIG_FLAGS}
#   -outdir ${swig_outdir}
#   ${swig_special_flags}
#   ${swig_extra_flags}
#   ${swig_include_dirs}
#   -o "${swig_generated_file_fullname}"
#   "${swig_source_file_fullname}"
#   MAIN_DEPENDENCY "${swig_source_file_fullname}"
#   DEPENDS ${SWIG_MODULE_${name}_EXTRA_DEPS}
#   IMPLICIT_DEPENDS CXX "${swig_source_file_fullname}"
#   COMMENT "Swig source")

# set(SWIG_ZBZ_EXECUTABLE "/Users/jamesfolk/Desktop/Documents_4.18.18/NJLI/External/tools/swig/swig")
# set(SWIG_ZBZ_LIB "/Users/jamesfolk/Desktop/Documents_4.18.18/NJLI/External/tools/swig/Lib")

set(swig_outdir ${CMAKE_BINARY_DIR})


foreach(it ${SWIGIN_SCRIPTS_INCLUDE_DIRS})
  set(swig_include_dirs ${swig_include_dirs} "-I${it}")
endforeach()
foreach(it ${NJLIC_SWIG_INCLUDE_DIRS})
  set(swig_include_dirs ${swig_include_dirs} "-I${it}")
endforeach()
foreach(it ${BULLET3_INCLUDE_DIRS})
  set(swig_include_dirs ${swig_include_dirs} "-I${it}")
endforeach()

set(NJLIC_SWIG_INCLUDE_DIR "${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/swig.in/script/njlic")

set(swig_include_dirs ${swig_include_dirs} "-I${NJLIC_SWIG_INCLUDE_DIR}")
set(swig_include_dirs ${swig_include_dirs} "-I${SWIG_ZBZ_LIB}")
set(swig_include_dirs ${swig_include_dirs} "-I${SWIG_ZBZ_LIB}/zbz")

 
set(swig_source_file_fullname ${NJLIC_SWIG_INCLUDE_DIR}/njlic.i)
set(swig_generated_file_fullname "${CMAKE_BINARY_DIR}/njlic_wrap.json")

if(CMAKE_GENERATOR MATCHES "Make")
  get_filename_component(swig_generated_timestamp
    "${swig_generated_file_fullname}" NAME_WE)
  set(swig_gen_target gen_njlic_${swig_generated_timestamp})
  set(swig_generated_timestamp
    "${swig_outdir}/${swig_generated_timestamp}.stamp")
  set(swig_custom_output ${swig_generated_timestamp})
  set(swig_custom_products
    BYPRODUCTS "${swig_generated_file_fullname}" ${swig_extra_generated_files})
  set(swig_timestamp_command
    COMMAND ${CMAKE_COMMAND} -E touch ${swig_generated_timestamp})
else()
  set(swig_custom_output
    "${swig_generated_file_fullname}" ${swig_extra_generated_files})
  set(swig_custom_products)
  set(swig_timestamp_command)
endif()

if(GL_ES2)
  list(APPEND CMAKE_SWIG_FLAGS "-D__GL_ES2__")
elseif(GL_ES3)
  list(APPEND CMAKE_SWIG_FLAGS "-D__GL_ES3__")
elseif(GL_2)
  list(APPEND CMAKE_SWIG_FLAGS "-D__GL_2__")
elseif(GL_3)
  list(APPEND CMAKE_SWIG_FLAGS "-D__GL_3__")
  endif()

add_custom_command(
  OUTPUT ${swig_custom_output}
  ${swig_custom_products}
  ${swig_generated_file_fullname}
  COMMAND ${CMAKE_COMMAND} -E make_directory ${swig_outdir}
  ${swig_timestamp_command}
  COMMAND "${SWIG_ZBZ_EXECUTABLE}"
  ARGS "-c++" "-zbz" "-includeall" "-fvirtual" "-v" "-w201" "-w312" "-ignoremissing" "-D__GL_2__"
  ${CMAKE_SWIG_FLAGS}
  -outdir ${swig_outdir}
  ${swig_include_dirs}
  -o "${swig_generated_file_fullname}"
  "${swig_source_file_fullname}"
  MAIN_DEPENDENCY "${swig_source_file_fullname}"
  IMPLICIT_DEPENDS CXX "${swig_source_file_fullname}"
  COMMENT "Swig ZBZ source")

# if(CMAKE_GENERATOR MATCHES "Make")
  add_custom_target(ZeroBrane-njlic-api DEPENDS ${swig_generated_file_fullname})
  # endif()


















# swig -c++ -zbz  -o example_wrap.cxx example.i

# add_custom_target( ${CMAKE_PROJECT_NAME}-documentation ALL
#   SOURCES ${CMAKE_BINARY_DIR}/Doxyfile
#   COMMAND ${SWIG_ZBZ_EXECUTABLE} ${DOXYGEN_OUT}
#   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#   COMMENT "Generating API documentation with Doxygen"
#   VERBATIM
#   )

