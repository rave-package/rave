#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"

TransientTrackBuilder::TransientTrackBuilder ( const rave::MagneticField * field,
    const edm::ESHandle<GlobalTrackingGeometry> & ) :
  theField ( field )
{}

const rave::MagneticField * TransientTrackBuilder::field() const
{
  return theField;
}

/*
reco::TransientTrack TransientTrackBuilder::build ( const reco::Track * p ) const
{
  return static_cast < reco::TransientTrack > ((*p));
}*/

reco::TransientTrack TransientTrackBuilder::build ( const reco::TransientTrack * p ) const
{
  return (*p);
}
