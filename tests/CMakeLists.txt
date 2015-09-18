# RAVE CMake build file for src folder
cmake_minimum_required (VERSION 2.6)
project (ravetests)

set(RAVETESTS_LIBS 
	RaveCore
	RaveBase
	RaveVertex
	RaveVertexKinematics
)

add_executable(kinematics02
	kinematics02.cc
)

target_link_libraries(kinematics02
	${RAVETESTS_LIBS}
)

add_executable(kinematics01
	kinematics01.cc
)

target_link_libraries(kinematics01
	${RAVETESTS_LIBS}
)

add_executable(kinematics03
	kinematics03.cc
)

target_link_libraries(kinematics03
	${RAVETESTS_LIBS}
)

# needs the MultiVertexReconstructor to be compiled in
# therefore deactivated atm.
#add_executable(memorytests
#	memorytests.cc
#)

#target_link_libraries(memorytests
#	${RAVETESTS_LIBS}
#)

add_executable(rave_version
	rave_version.cc
)

target_link_libraries(rave_version
	${RAVETESTS_LIBS}
)

add_executable(propagatortests
	propagatortests.cc
)

target_link_libraries(propagatortests
	${RAVETESTS_LIBS}
)


