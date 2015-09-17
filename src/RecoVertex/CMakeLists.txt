# RAVE CMake build file for src folder
cmake_minimum_required (VERSION 2.6)
project (ravevertex)

set(RAVEVERTEX_CPP 
	VertexTools/src/hsm_3d.cc
	AdaptiveVertexFinder/src/AdaptiveVertexReconstructor.cc
	AdaptiveVertexFit/src/AdaptiveVertexFitter.cc
	ConfigurableVertexReco/src/ConfigurableAdaptiveFitter.cc
	ConfigurableVertexReco/src/ConfigurableAdaptiveReconstructor.cc
	ConfigurableVertexReco/src/ConfigurableAnnealing.cc
	ConfigurableVertexReco/src/ConfigurableKalmanFitter.cc
	ConfigurableVertexReco/src/ConfigurableVertexReconstructor.cc
	ConfigurableVertexReco/src/ConfigurableVertexFitter.cc
	ConfigurableVertexReco/src/ReconstructorFromFitter.cc
	ConfigurableVertexReco/src/VertexRecoManager.cc
	ConfigurableVertexReco/src/VertexFitterManager.cc
	ConfigurableVertexReco/src/AbstractConfFitter.cc
	KalmanVertexFit/src/KalmanSmoothedVertexChi2Estimator.cc
	KalmanVertexFit/src/KalmanTrackToTrackCovCalculator.cc
	KalmanVertexFit/src/KalmanVertexFitter.cc
	KalmanVertexFit/src/KalmanVertexTrackCompatibilityEstimator.cc
	KalmanVertexFit/src/KalmanVertexTrackUpdator.cc
	KalmanVertexFit/src/KalmanVertexSmoother.cc
	KalmanVertexFit/src/KalmanVertexUpdator.cc
	KalmanVertexFit/src/KVFHelper.cc
	LinearizationPointFinders/src/CrossingPtBasedLinearizationPointFinder.cc
	LinearizationPointFinders/src/DefaultLinearizationPointFinder.cc
	LinearizationPointFinders/src/FallbackLinearizationPointFinder.cc
	LinearizationPointFinders/src/FsmwLinearizationPointFinder.cc
	VertexPrimitives/src/BasicSingleVertexState.cc
	VertexPrimitives/src/BasicVertexState.cc
	VertexPrimitives/src/CachingVertex.cc
	VertexPrimitives/src/LinearizedTrackState.cc
	VertexPrimitives/src/TransientVertex.cc
	VertexPrimitives/src/VertexState.cc
	VertexPrimitives/src/VertexTrack.cc
	VertexTools/src/DeterministicAnnealing.cc
	VertexTools/src/DummyTrackToTrackCovCalculator.cc
	VertexTools/src/DummyVertexSmoother.cc
	VertexTools/src/DummyVertexTrackUpdator.cc
	VertexTools/src/FsmwModeFinder3d.cc
	VertexTools/src/GeometricAnnealing.cc
	VertexTools/src/HsmModeFinder3d.cc
	VertexTools/src/LinearizationPointFinder.cc
	VertexTools/src/LinearizedTrackStateFactory.cc
	VertexTools/src/NbSharedTracks.cc
	VertexTools/src/PerigeeLinearizedTrackState.cc
	VertexTools/src/PerigeeRefittedTrackState.cc
	VertexTools/src/SequentialVertexFitter.cc
	VertexTools/src/SequentialVertexSmoother.cc
	VertexTools/src/VertexDistance.cc
	VertexTools/src/VertexDistanceXY.cc
	VertexTools/src/VertexDistance3D.cc 
)

add_library(RaveVertex SHARED
    ${RAVEVERTEX_CPP} )

target_link_libraries(RaveVertex
	RaveCore
	CLHEP
)