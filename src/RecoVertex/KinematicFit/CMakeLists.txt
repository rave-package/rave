# RAVE CMake build file for src folder
cmake_minimum_required (VERSION 2.6)
project (ravevertexkinematics)

set(RAVEVERTEXKINEMATICS_CPP 
	src/BackToBackKinematicConstraint.cc
	src/ConstrainedTreeBuilder.cc
	src/FinalTreeBuilder.cc
	src/FourMomentumKinematicConstraint.cc
	src/EqualMassKinematicConstraint.cc
	src/InputSort.cc
	src/KinematicConstrainedVertexFitter.cc
	src/KinematicConstrainedVertexUpdator.cc
	src/KinematicParticleFitter.cc
	src/KinematicParticleVertexFitter.cc
	src/LagrangeChildUpdator.cc
	src/LagrangeParentParticleFitter.cc
	src/LagrangeEnergyParentParticleFitter.cc
	src/MassKinematicConstraint.cc
	src/MomentumKinematicConstraint.cc
	src/PointingKinematicConstraint.cc
	src/SimplePointingConstraint.cc
	src/SmartPointingConstraint.cc
	src/TwoTrackMassKinematicConstraint.cc
	src/VertexKinematicConstraint.cc
	src/MultiTrackMassKinematicConstraint.cc
	src/MultiTrackVertexLinkKinematicConstraint.cc
	src/MultiTrackPointingKinematicConstraint.cc
	../KinematicFitPrimitives/src/KinematicParameters.cc
	../KinematicFitPrimitives/src/KinematicParametersError.cc
	../KinematicFitPrimitives/src/KinematicParticle.cc
	../KinematicFitPrimitives/src/KinematicParticleFactoryFromTransientTrack.cc
	../KinematicFitPrimitives/src/KinematicPerigeeConversions.cc
	../KinematicFitPrimitives/src/KinematicRefittedTrackState.cc
	../KinematicFitPrimitives/src/KinematicState.cc
	../KinematicFitPrimitives/src/KinematicTree.cc
	../KinematicFitPrimitives/src/KinematicVertex.cc
	../KinematicFitPrimitives/src/KinematicVertexFactory.cc
	../KinematicFitPrimitives/src/MultipleKinematicConstraint.cc
	../KinematicFitPrimitives/src/ParticleKinematicLinearizedTrackState.cc
	../KinematicFitPrimitives/src/ParticleKinematicLinearizedTrackStateFactory.cc
	../KinematicFitPrimitives/src/PerigeeKinematicState.cc
	../KinematicFitPrimitives/src/TrackKinematicStatePropagator.cc
	../KinematicFitPrimitives/src/TransientTrackKinematicParticle.cc
	../KinematicFitPrimitives/src/TransientTrackKinematicStateBuilder.cc
	../KinematicFitPrimitives/src/VirtualKinematicParticle.cc
	../KinematicFitPrimitives/src/VirtualKinematicParticleFactory.cc
)

add_library(RaveVertexKinematics SHARED
    ${RAVEVERTEXKINEMATICS_CPP} )
    
target_link_libraries(RaveVertexKinematics
	RaveCore
	RaveVertex
	)

