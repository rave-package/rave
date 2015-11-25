# RAVE CMake build file for src folder
cmake_minimum_required (VERSION 2.6)
project (raveunittests)

set(RAVEUNITTESTS_CPP 
#	LowMomentumScale.cxx
	RaveTest.cxx
	unittest.cxx
	PropertyHandler.cxx
	TinyBField.cxx
	ZeroBField.cxx
)

add_executable(raveunittests
    ${RAVEUNITTESTS_CPP} 
)

target_link_libraries(raveunittests
	RaveCore
	RaveBase
	RaveVertex
	RaveVertexKinematics
	boost_unit_test_framework
)
	
# refactor tests
add_executable(refactortests
        RaveCylinder
	RavePlane
)

target_link_libraries(refactortests
	RaveCore
	RaveBase
	RaveVertex
	RaveVertexKinematics
	boost_unit_test_framework
)
