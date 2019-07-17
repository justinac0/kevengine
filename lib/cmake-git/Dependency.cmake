# [[ This code provided free of charge by Izzy Muerte :) ]]
include_guard(GLOBAL)
include(FetchContent)

function (_get_targets _var _path)
  get_property(_subdirs DIRECTORY ${_path} PROPERTY SUBDIRECTORIES)
  foreach (_subdir IN LISTS _subdirs)
    _get_targets(${_var} ${_subdir})
  endforeach()
  get_property(_targets DIRECTORY ${_path} PROPERTY BUILDSYSTEM_TARGETS)
  foreach (_target IN LISTS _targets)
    get_target_property(_type ${_target} TYPE)
    if(_type STREQUAL STATIC_LIBRARY OR _type STREQUAL INTERFACE_LIBRARY)
      list(APPEND ${_var} ${_target})
    endif()
  endforeach()
  set(${_var} ${${_var}} PARENT_SCOPE)
endfunction()

function (cache _var _value _type)
  set(${_var} ${_value} CACHE ${_type} "" FORCE)
endfunction()

function (git _name _repository _tag)
  fetch(${_name}
    GIT_REPOSITORY ${_repository}
    GIT_TAG ${_tag}
    GIT_SHALLOW OFF
    ${ARGN})
  set(${_name}_SOURCE_DIR ${${_name}_SOURCE_DIR} PARENT_SCOPE)
endfunction ()

function (fetch _name)
  FetchContent_Declare(${_name} ${ARGN})
  FetchContent_GetProperties(${_name})
  string(TOLOWER ${_name} _lcname)
  if (NOT ${_lcname}_POPULATED)
    FetchContent_Populate(${_name})
    set(_srcdir ${${_lcname}_SOURCE_DIR})
    set(_bindir ${${_lcname}_BINARY_DIR})
    add_subdirectory(${_srcdir} ${_bindir} EXCLUDE_FROM_ALL)
  endif ()
  add_library(${_name}::${_name} INTERFACE IMPORTED GLOBAL)
  _get_targets(_deps ${_srcdir})
  target_link_libraries(${_name}::${_name} INTERFACE ${_deps})
  target_include_directories(${_name}::${_name}
    INTERFACE ${_srcdir}/include)
  foreach(_dep IN LISTS _deps)
    target_include_directories(${_name}::${_name} INTERFACE
      $<TARGET_PROPERTY:${_dep},INTERFACE_INCLUDE_DIRECTORIES>)
  endforeach()
  set(${_name}_SOURCE_DIR ${_srcdir} PARENT_SCOPE)
endfunction ()
