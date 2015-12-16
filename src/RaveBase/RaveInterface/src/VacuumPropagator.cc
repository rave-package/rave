#include "RaveBase/RaveInterface/rave/VacuumPropagator.h"
#include "TrackingTools/PatternTools/interface/TransverseImpactPointExtrapolator.h"
#include "RaveTools/Converters/interface/MagneticFieldSingleton.h"
#include "TrackingTools/TrajectoryState/interface/PerigeeConversions.h"
#include "TrackingTools/GeomPropagators/interface/AnalyticalPropagator.h"
#include "DataFormats/GeometrySurface/interface/Plane.h"
#include "DataFormats/GeometrySurface/interface/Cylinder.h"
#include "DataFormats/GeometrySurface/interface/GloballyPositioned.h"
#include "rave/Plane.h"
#include "rave/Cylinder.h"

#include "RaveBase/Converters/interface/RaveStreamers.h"
#include <iostream>

using namespace std;

namespace {
  // FIXME really really ugly work around for reference counting probs!
  std::vector < const TrajectoryStateOnSurface * > tsoses;
  void clearTsoses()
  {
    /*
    cout << "[VacuumPropagator] clearing!" << endl;
    for ( vector< const TrajectoryStateOnSurface * >::const_iterator 
          i=tsoses.begin(); i!=tsoses.end() ; ++i )
      delete (*i);
    tsoses.clear();
    */
  }
}
  
rave::VacuumPropagator * rave::VacuumPropagator::copy() const
{
  return new rave::VacuumPropagator ( * this );
}
    

pair < rave::Track, double > rave::VacuumPropagator::to ( const rave::Track & orig,
                          const ravesurf::Cylinder & rcyl ) const
{
  clearTsoses();
  typedef GloballyPositioned<float>::PositionType PositionType;
  typedef GloballyPositioned<float>::RotationType RotationType;
  AnalyticalPropagator prop ( MagneticFieldSingleton::Instance(), anyDirection );
  pair < rave::Track, double > ot = prop.propagateWithPathRave ( orig, rcyl );
  return ot;
}

rave::VacuumPropagator::~VacuumPropagator()
{
  clearTsoses();
}


pair < rave::Track, double > rave::VacuumPropagator::to ( const rave::Track & orig,
                          const ravesurf::Plane & rplane ) const
{
  tsoses.clear();
  typedef GloballyPositioned<float>::PositionType PositionType;

  AnalyticalPropagator prop ( MagneticFieldSingleton::Instance(), anyDirection );
  pair < rave::Track, double > to = prop.propagateWithPathRave ( orig, rplane );
  return to;
}

/*
rave::Track rave::VacuumPropagator::closestTo ( const rave::Track & orig,
    const rave::Point3D & pt, bool transverse ) const
{
  RaveToCmsObjects forward;
  CmsToRaveObjects backward;
  GlobalPoint pos = forward.convert ( pt );

  if ( transverse )
  {
    //FreeTrajectoryState fts = forward.convertTrackToFTS ( orig );
    TransverseImpactPointExtrapolator tipe( MagneticFieldSingleton::Instance() );
    TrajectoryStateOnSurface tsos = tipe.extrapolate( orig, pos );
    rave::Track ret = backward.convert ( orig.id(), tsos, orig.chi2(), orig.ndof(),
       orig.originalObject(), orig.tag() );
    return ret;
  }
  
  PerigeeConversions conv;
  AlgebraicVector3 momentum = forward.toAlgebraicVector3 ( orig.state().momentum() );
  AlgebraicSymMatrix66 error = forward.convert ( orig.error() ).matrix();
  TrajectoryStateClosestToPoint tscp = conv.trajectoryStateClosestToPoint
    ( momentum, pos, orig.chargeRave(), error , MagneticFieldSingleton::Instance()  );
  rave::Track ret = backward.convert ( orig.id(), tscp.theState(), orig.chi2(), 
      orig.ndof(), orig.originalObject(), orig.tag() );
  return ret;
}
*/

rave::VacuumPropagator::VacuumPropagator() {}
