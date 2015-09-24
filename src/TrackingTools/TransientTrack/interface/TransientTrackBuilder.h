#ifndef TRACKINGTOOLS_TRANSIENTRACKBUILDER_H
#define TRACKINGTOOLS_TRANSIENTRACKBUILDER_H

#include "DataFormats/TrackReco/interface/Track.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
//#include "MagneticField/Engine/interface/MagneticField.h"
#include "Geometry/CommonDetUnit/interface/GlobalTrackingGeometry.h"
#include "DataFormats/Common/interface/Handle.h"
#include <rave/MagneticField.h>

  /**
   * Helper class to build TransientTrack from the persistent Track.
   * (Note, the reco::Track is dummy in Rave)
   */

class TransientTrackBuilder {
 public:
    TransientTrackBuilder(const rave::MagneticField * field, const edm::ESHandle<GlobalTrackingGeometry> & );
    reco::TransientTrack build ( const reco::TransientTrack * p ) const;

    // reco::TransientTrack build ( const reco::Track * p ) const;

    const rave::MagneticField* field() const;

  private:
    const rave::MagneticField* theField;
};

#endif
