# RAVE CMake build file for src folder
cmake_minimum_required (VERSION 2.6)
project (ravebase)

set(RAVEBASE_CPP 
	Converters/src/CmsToRaveObjects.cc 
	#	Converters/src/MagneticFieldWrapper.cc 
	Converters/src/PerigeeToRaveObjects.cc 
	#	Converters/src/PropagatorWrapper.cc 
	Converters/src/HelperFunctions.cc
	Converters/src/RaveStreamers.cc 
	Converters/src/RaveToAlgebraicObjects.cc 
	Converters/src/RaveToCmsObjects.cc 
	Converters/src/RaveToPerigeeObjects.cc 
	RaveEngine/src/RaveId.cc 
	RaveEngine/src/RaveVertexReconstructor.cc 
	RaveEngine/src/RaveParameterSetBuilder.cc 
	RaveEngine/src/RaveBeamSpotSingleton.cc 
	#	RaveInterface/src/BasicTrack.cc 
	RaveInterface/src/BasicVertex.cc 
	RaveInterface/src/CheckedFloat.cc 
	RaveInterface/src/ConstantMagneticField.cc 
	RaveInterface/src/Covariance3D.cc 
	RaveInterface/src/Covariance33D.cc 
	# 	RaveInterface/src/Covariance6D.cc 
	RaveInterface/src/Ellipsoid3D.cc 
	RaveInterface/src/Exception.cc 
	RaveInterface/src/PerigeeParameters3D.cc 
	RaveInterface/src/PerigeeParameters5D.cc 
	RaveInterface/src/PerigeeCovariance3D.cc 
	RaveInterface/src/PerigeeCovariance5D.cc 
	#	RaveInterface/src/Point3D.cc 
	RaveInterface/src/Track.cc 
	RaveInterface/src/VacuumPropagator.cc 
	#	RaveInterface/src/Vector6D.cc 
	RaveInterface/src/Version.cc 
	RaveInterface/src/Vertex.cc 
	RaveInterface/src/VertexFactory.cc 
	Utilities/src/StringTools.cc
)

set(RAVEBASE_HEADERS
         RaveInterface/rave/AbstractPerigeeAccess.h
         RaveInterface/rave/AbstractTrack.h
         RaveInterface/rave/AbstractVertex.h
         RaveInterface/rave/BasicKinematicConstraint.h
         RaveInterface/rave/BasicKinematicParticle.h
         RaveInterface/rave/BasicKinematicTree.h
         RaveInterface/rave/BasicKinematicVertex.h
         RaveInterface/rave/BasicMultipleKinematicConstraint.h
         RaveInterface/rave/BasicTrack.h
         RaveInterface/rave/BasicTransientTrackKinematicParticle.h
         RaveInterface/rave/BasicVertex.h
         RaveInterface/rave/BasicVirtualKinematicParticle.h
         RaveInterface/rave/Charge.h
         RaveInterface/rave/CheckedFloat.h
         RaveInterface/rave/ConstantMagneticField.h
         RaveInterface/rave/CopyUsingNew.h
         RaveInterface/rave/Covariance33D.h
         RaveInterface/rave/Covariance3D.h
         RaveInterface/rave/Covariance4D.h
	 #	 RaveInterface/rave/Covariance6D.h
         RaveInterface/rave/Covariance7D.h
         RaveInterface/rave/Cylinder.h
         RaveInterface/rave/Ellipsoid3D.h
         RaveInterface/rave/Exception.h
         RaveInterface/rave/FlavorTagFactory.h
         RaveInterface/rave/KinematicConstraintBuilder.h
         RaveInterface/rave/KinematicConstraint.h
         RaveInterface/rave/KinematicParticle.h
         RaveInterface/rave/KinematicTreeFactory.h
         RaveInterface/rave/KinematicTree.h
         RaveInterface/rave/KinematicVertex.h
         RaveInterface/rave/Logger.h
         RaveInterface/rave/MagneticField.h
         RaveInterface/rave/MultipleKinematicConstraint.h
         RaveInterface/rave/PerigeeCovariance3D.h
         RaveInterface/rave/PerigeeCovariance5D.h
         RaveInterface/rave/PerigeeCovariance6D.h
         RaveInterface/rave/PerigeeParameters3D.h
         RaveInterface/rave/PerigeeParameters5D.h
         RaveInterface/rave/PerigeeParameters6D.h
         RaveInterface/rave/Plane.h
         RaveInterface/rave/Point3D.h
         RaveInterface/rave/Propagator.h
         RaveInterface/rave/ProxyBase.h
         RaveInterface/rave/ReferenceCounted.h
         RaveInterface/rave/Track.h
         RaveInterface/rave/TransientTrackKinematicParticle.h
         RaveInterface/rave/Units.h
         RaveInterface/rave/VacuumPropagator.h
         RaveInterface/rave/Vector3D.h
         RaveInterface/rave/Vector4D.h
         RaveInterface/rave/Vector6D.h
         RaveInterface/rave/Vector7D.h
         RaveInterface/rave/Version.h
         RaveInterface/rave/VertexFactory.h
         RaveInterface/rave/Vertex.h
         RaveInterface/rave/VirtualKinematicParticle.h
)



if(HAS_KINEMATICS)
  	set(RAVEBASE_CPP
		${RAVEBASE_CPP}
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
endif(HAS_KINEMATICS)



add_library(RaveBase SHARED
    ${RAVEBASE_CPP} )

target_link_libraries(RaveBase
	RaveCore
	# only if has_kinematics, but it is weird this has to be
	# linked into the RaveBase library
	#RaveVertexKinematics
	RaveVertex
	CLHEP
)

install(TARGETS RaveBase LIBRARY DESTINATION lib)
install(FILES ${RAVEBASE_HEADERS} DESTINATION include/rave)
