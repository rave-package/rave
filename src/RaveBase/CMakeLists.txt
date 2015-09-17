# RAVE CMake build file for src folder
cmake_minimum_required (VERSION 2.6)
project (ravebase)

set(RAVEBASE_CPP 
	Converters/src/CmsToRaveObjects.cc 
	Converters/src/MagneticFieldWrapper.cc 
	Converters/src/PerigeeToRaveObjects.cc 
	Converters/src/PropagatorWrapper.cc 
	Converters/src/RaveStreamers.cc 
	Converters/src/RaveToAlgebraicObjects.cc 
	Converters/src/RaveToCmsObjects.cc 
	Converters/src/RaveToPerigeeObjects.cc 
	RaveEngine/src/RaveId.cc 
	RaveEngine/src/RaveVertexReconstructor.cc 
	RaveEngine/src/RaveParameterSetBuilder.cc 
	RaveEngine/src/RaveBeamSpotSingleton.cc 
	RaveInterface/src/BasicTrack.cc 
	RaveInterface/src/BasicVertex.cc 
	RaveInterface/src/CheckedFloat.cc 
	RaveInterface/src/ConstantMagneticField.cc 
	RaveInterface/src/Covariance3D.cc 
	RaveInterface/src/Covariance33D.cc 
	RaveInterface/src/Covariance6D.cc 
	RaveInterface/src/Ellipsoid3D.cc 
	RaveInterface/src/Exception.cc 
	RaveInterface/src/PerigeeParameters3D.cc 
	RaveInterface/src/PerigeeParameters5D.cc 
	RaveInterface/src/PerigeeCovariance3D.cc 
	RaveInterface/src/PerigeeCovariance5D.cc 
	RaveInterface/src/Point3D.cc 
	RaveInterface/src/Track.cc 
	RaveInterface/src/VacuumPropagator.cc 
	RaveInterface/src/Vector6D.cc 
	RaveInterface/src/Version.cc 
	RaveInterface/src/Vertex.cc 
	RaveInterface/src/VertexFactory.cc 
	Utilities/src/StringTools.cc

# if has_kinematics
  RaveEngine/src/TaggedTransientTrackKinematicParticle.cc
  RaveInterface/src/Vector4D.cc
  RaveInterface/src/Vector7D.cc
  RaveInterface/src/Covariance4D.cc
  RaveInterface/src/Covariance7D.cc
  RaveInterface/src/PerigeeParameters6D.cc
  RaveInterface/src/PerigeeCovariance6D.cc
  RaveInterface/src/BasicKinematicConstraint.cc
  RaveInterface/src/BasicKinematicParticle.cc
  RaveInterface/src/BasicKinematicTree.cc
  RaveInterface/src/BasicKinematicVertex.cc
  RaveInterface/src/BasicMultipleKinematicConstraint.cc
  RaveInterface/src/BasicTransientTrackKinematicParticle.cc
  RaveInterface/src/BasicVirtualKinematicParticle.cc
  RaveInterface/src/KinematicConstraint.cc
  RaveInterface/src/KinematicParticle.cc
  RaveInterface/src/KinematicTree.cc
  RaveInterface/src/Logger.cc
  RaveInterface/src/KinematicVertex.cc
  RaveInterface/src/MultipleKinematicConstraint.cc
  RaveInterface/src/TransientTrackKinematicParticle.cc
  RaveInterface/src/VirtualKinematicParticle.cc
  RaveInterface/src/Plane.cc
  RaveInterface/src/Cylinder.cc
  RaveInterface/src/KinematicConstraintBuilder.cc
  RaveInterface/src/KinematicTreeFactory.cc
)

add_library(RaveBase SHARED
    ${RAVEBASE_CPP} )

target_link_libraries(RaveBase
	RaveCore
	# only if has_kinematics, but it is weird this has to be
	# linked into the RaveBase library
	#RaveVertexKinematics
	CLHEP
)
