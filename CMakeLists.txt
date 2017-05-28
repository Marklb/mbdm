cmake_minimum_required(VERSION 2.6)
project (mbdm)

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

macro(increment_version)
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/version.txt)
    file(READ ${CMAKE_CURRENT_SOURCE_DIR}/version.txt MBDM_VERSION)
  else()
    set(MBDM_VERSION "0.0.0.1")
  endif()

  string(REPLACE "." ";" VERSION_LIST ${MBDM_VERSION})

  list(GET VERSION_LIST 0 MBDM_VERSION_MAJOR)
  list(GET VERSION_LIST 1 MBDM_VERSION_MINOR)
  list(GET VERSION_LIST 2 MBDM_VERSION_PATCH)
  list(GET VERSION_LIST 3 MBDM_VERSION_TWEAK)

  math(EXPR MBDM_VERSION_TWEAK_NEW "${MBDM_VERSION_TWEAK} + 1")

  set(MBDM_VERSION "${MBDM_VERSION_MAJOR}.${MBDM_VERSION_MINOR}.${MBDM_VERSION_PATCH}.${MBDM_VERSION_TWEAK_NEW}")

  file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/version.txt "${MBDM_VERSION}")
endmacro()



#
increment_version()

configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)


set(MBDM_SRCS
  ${PROJECT_SOURCE_DIR}/base_components/base_panel.cpp
  ${PROJECT_SOURCE_DIR}/base_components/base_window.cpp
  ${PROJECT_SOURCE_DIR}/core/core.cpp
  ${PROJECT_SOURCE_DIR}/core/global_kb_handler.cpp
  ${PROJECT_SOURCE_DIR}/core/simulated_desktop.cpp
  ${PROJECT_SOURCE_DIR}/core/simulated_desktops_manager.cpp
  ${PROJECT_SOURCE_DIR}/utils/paint_utils.cpp
  ${PROJECT_SOURCE_DIR}/window_components/button.cpp
  ${PROJECT_SOURCE_DIR}/window_components/panel.cpp
  ${PROJECT_SOURCE_DIR}/window_components/scrollable_panel.cpp
  ${PROJECT_SOURCE_DIR}/window_components/scrollbar.cpp
  ${PROJECT_SOURCE_DIR}/windows/current_simulated_desktop_window.cpp
  ${PROJECT_SOURCE_DIR}/windows/settings_window.cpp
  ${PROJECT_SOURCE_DIR}/mbdm.cpp
  ${PROJECT_SOURCE_DIR}/custom.cpp
)



include_directories("${PROJECT_BINARY_DIR}")
add_executable(${PROJECT_NAME} WIN32 ${MBDM_SRCS} ${MBDM_SRCS})
include_directories("${PROJECT_INCLUDE_DIR}")
