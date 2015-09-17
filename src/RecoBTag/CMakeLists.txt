# RAVE CMake build file for src folder
cmake_minimum_required (VERSION 2.6)
project (ravebtag)

set(RAVEFLAVOURTAG_CPP 
SecondaryVertex/src/ParticleMasses.cc
SecondaryVertex/src/SecondaryVertex.cc
SecondaryVertex/src/V0Filter.cc
SecondaryVertex/src/VertexSorting.cc
SecondaryVertex/src/VertexFilter.cc
SecondaryVertex/src/TrackKinematics.cc
SecondaryVertex/src/TrackSorting.cc
SecondaryVertex/src/TrackSelector.cc
SecondaryVertex/src/SimpleVertexBasedTagger.cc
SecondaryVertex/src/SVBuilder.cc
SecondaryVertex/src/SVFilter.cc
../DataFormats/BTauReco/src/SecondaryVertexTagInfo.cc
../DataFormats/BTauReco/src/JetTag.cc
../DataFormats/BTauReco/src/TaggingVariable.cc 
)

add_library(RaveFlavorTag SHARED
    ${RAVEFLAVOURTAG_CPP} )

