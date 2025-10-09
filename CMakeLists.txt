cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)
project(RootUtil CXX)

######
# ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})

######################
# module path
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include( RootMacros )

######################
# include directories
include_directories(SYSTEM ${PROJECT_SOURCE_DIR} ${ROOT_INCLUDE_DIR} )

######################
# base
set( libg4eval_hp_lite_SOURCES
  SimEvaluator_hp.cc
  TrackingEvaluator_hp.cc
  TrackingEvaluatorLight_hp.cc
)

######################
# base
set( libg4eval_hp_lite_HEADERS
  SimEvaluator_hp.h
  TrackingEvaluator_hp.h
  TrackingEvaluatorLight_hp.h
)

add_root_dictionaries( libg4eval_hp_lite_SOURCES
  SimEvaluator_hpLinkDef.h
  TrackingEvaluator_hpLinkDef.h
  TrackingEvaluatorLight_hpLinkDef.h
 )

add_library( g4eval_hp_lite SHARED ${libg4eval_hp_lite_SOURCES} )
target_link_libraries( g4eval_hp_lite ${ROOT_LIBRARIES})
install( TARGETS g4eval_hp_lite DESTINATION ${CMAKE_INSTALL_PREFIX}/lib )
install( FILES ${libg4eval_hp_lite_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/RootUtil )

