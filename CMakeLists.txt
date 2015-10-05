# RAVE CMake build file for topmost folder
cmake_minimum_required (VERSION 2.6)
project (rave)


set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set (COMMON_COMPILE_FLAGS "")

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang") 
	# Descent compile configuratin
	set (COMMON_COMPILE_FLAGS "${COMMON_COMPILE_FLAGS} -DUSE_THREADING_NULL=1 -DDESCENT_LOG_ENABLED=1 -DUSE_SDL=1")
	# common gcc settings
	# -pedantic is not working because of usage of non-standard #warning in root config.h include ...
	#set (COMMON_COMPILE_FLAGS "${COMMON_COMPILE_FLAGS} -Wno-unused-local-typedef -Wno-pedantic -Werror -Wfatal-errors -Wall -Wno-unused-function -Wno-deprecated-declarations -Wno-strict-aliasing -Wno-int-to-pointer-cast -Wno-unused-private-field -Wno-reorder -Wno-unused-variable -Wno-overloaded-virtual -std=c++11")
	# less strict, to get it compiling first
	set (COMMON_COMPILE_FLAGS "${COMMON_COMPILE_FLAGS} -Wno-unused-local-typedef -Wno-pedantic -Wno-unused-function -Wno-deprecated-declarations -Wno-strict-aliasing -Wno-int-to-pointer-cast -Wno-unused-private-field -Wno-reorder -Wno-unused-variable -Wno-overloaded-virtual -std=c++11")
	
endif()

# add some gcc specific options
if (CMAKE_COMPILER_IS_GNUCXX) 
	set (COMMON_COMPILE_FLAGS "${COMMON_COMPILE_FLAGS} -Wno-maybe-uninitialized")
endif()

include(FindROOT)
include_directories(${ROOT_INCLUDE_DIR})

# no dll export statement for Linux compile
set (COMMON_COMPILE_FLAGS "${COMMON_COMPILE_FLAGS} -DRaveDllExport=''")
add_definitions(-DPACKAGE_VERSION="0.6.25")

# important so some conversion code gets compiled for the kinematic fits
add_definitions(-DWITH_KINEMATICS=1)

include_directories(${rave_SOURCE_DIR}/src
					${rave_SOURCE_DIR}/src/RaveBase/RaveInterface )


set (GENERAL_COMPILE_FLAGS " ${GENERAL_COMPILE_FLAGS} ${COMMON_COMPILE_FLAGS}")

set(CMAKE_CXX_FLAGS "-O3 -g -ggdb ${GENERAL_COMPILE_FLAGS}" )

# options

option (HAS_TTF "option for TertiaryTracksVertexFinder" OFF)
if(HAS_TTF) 
message("COMPILING WITH OPTION HAS_TTF")
endif(HAS_TTF)

option (HAS_MVF "option for MultiVertexFit" OFF)
if(HAS_MVF) 
message("COMPILING WITH OPTION HAS_MVF")
endif(HAS_MVF)

option (HAS_TKVF "option for TrimmedKalmanVertexFinder" OFF)
if(HAS_TKVF) 
message("COMPILING WITH OPTION HAS_TKVF")
endif(HAS_TKVF)

option (HAS_GSF "option for GaussianSumVertexFit [deprecated]" OFF)
if(HAS_GSF) 
message("COMPILING WITH OPTION HAS_GSF")
endif(HAS_GSF)

option (HAS_ZVRES "option for ZvresReco" OFF)
if(HAS_ZVRES) 
message("COMPILING WITH OPTION HAS_ZVRES")
endif(HAS_ZVRES)

option (HAS_DEVELOPERS "option for developement" OFF)
if(HAS_DEVELOPERS) 
message("COMPILING WITH OPTION HAS_DEVELOPERS")
endif(HAS_DEVELOPERS)

option (HAS_KINEMATICS "option for kinematics" OFF)
if(HAS_KINEMATICS) 
message("COMPILING WITH OPTION HAS_KINEMATICS")
endif(HAS_KINEMATICS)


add_subdirectory(src)
add_subdirectory(src/RaveBase)
add_subdirectory(src/RecoVertex)

# only if has_kinematic fit
if(HAS_KINEMATICS)
	add_subdirectory(src/RecoVertex/KinematicFit)
	add_subdirectory(src/RecoBTag)
	add_subdirectory(UnitTests)
	add_subdirectory(tests)
endif(HAS_KINEMATICS)

