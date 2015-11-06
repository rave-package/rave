#include "TrackingTools/GeomPropagators/interface/AnalyticalPropagator.h"

#include "DataFormats/GeometrySurface/interface/Cylinder.h"
#include "DataFormats/GeometrySurface/interface/TangentPlane.h"
#include "DataFormats/GeometrySurface/interface/Plane.h"

//#include "MagneticField/Engine/interface/MagneticField.h"

#include "TrackingTools/GeomPropagators/interface/PropagationExceptions.h"
#include "TrackingTools/GeomPropagators/interface/StraightLinePlaneCrossing.h"
#include "TrackingTools/GeomPropagators/interface/StraightLineBarrelCylinderCrossing.h"
#include "TrackingTools/GeomPropagators/interface/HelixBarrelPlaneCrossingByCircle.h"
#include "TrackingTools/GeomPropagators/interface/HelixForwardPlaneCrossing.h"
#include "TrackingTools/GeomPropagators/interface/HelixArbitraryPlaneCrossing.h"
#include "TrackingTools/GeomPropagators/interface/HelixBarrelCylinderCrossing.h"
#include "TrackingTools/AnalyticalJacobians/interface/AnalyticalCurvilinearJacobian.h"
#include "TrackingTools/GeomPropagators/interface/PropagationDirectionFromPath.h"
#include "TrackingTools/TrajectoryState/interface/SurfaceSideDefinition.h"
#include "TrackingTools/GeomPropagators/interface/PropagationExceptions.h"

// Moritz
#include "RaveBase/Converters/interface/RaveToCmsObjects.h"
#include "RaveBase/Converters/interface/CmsToRaveObjects.h"


#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include <cmath>

using namespace SurfaceSideDefinition;

std::pair<TrajectoryStateOnSurface,double>
AnalyticalPropagator::propagateWithPath(const FreeTrajectoryState& fts, 
					const Plane& plane) const
{
  // check curvature
  double rho = fts.transverseCurvature();
  
  // propagate parameters
  GlobalPoint x;
  GlobalVector p;
  double s;
  
  // check if already on plane
  const float maxDistToPlane(0.1e-4);
  const float numericalPrecision(5.e-7);
  float maxDz = numericalPrecision*plane.position().mag();
  if ( fabs(plane.localZ(fts.position()))>(maxDistToPlane>maxDz?maxDistToPlane:maxDz) ) {
    // propagate
    bool parametersOK = this->propagateParametersOnPlane(fts, plane, x, p, s);
    // check status and deltaPhi limit
    float dphi2 = s*rho;
    dphi2 = dphi2*dphi2*fts.momentum().perp2()/fts.momentum().mag2();
    if ( !parametersOK || dphi2>theMaxDPhi2 )
    {
      return TsosWP(TrajectoryStateOnSurface(),0.);
    }
  }
  else {
    /*
    LogDebug("AnalyticalPropagator")<<"not going anywhere. Already on surface.\n"
				    <<"plane.localZ(fts.position()): "<<plane.localZ(fts.position())<<"\n"
				    <<"maxDistToPlane: "<<maxDistToPlane<<"\n"
				    <<"maxDz: "<<maxDz<<"\n"
				    <<"plane.position().mag(): "<<plane.position().mag();
                                    */
    x = fts.position();
    p = fts.momentum();
    s = 0.;
  }
  //
  // Compute propagated state and check change in curvature
  //
  GlobalTrajectoryParameters gtp(x,p,fts.charge(),theField);
  if ( fabs(rho)>1.e-10 && fabs((gtp.transverseCurvature()-rho)/rho)>theMaxDBzRatio ) 
    return TsosWP(TrajectoryStateOnSurface(),0.);
  //
  // construct TrajectoryStateOnSurface
  //
  return propagatedStateWithPath(fts,plane,gtp,s);
}


/// propagation to plane with path length  -- using rave::Track and CMS Plane
// using ravetrack instead of cms fts --> TEMPORARY charge, position, momentum

std::pair<TrajectoryStateOnSurface,double> AnalyticalPropagator::propagateWithPath(const rave::Track& raveTrack, const Plane& plane) const
{
  // check curvature
  double rho = raveTrack.transverseCurvature();

  // propagate parameters
  GlobalPoint x;
  GlobalVector p;
  double s;

  // check if already on plane
  const float maxDistToPlane(0.1e-4);
  const float numericalPrecision(5.e-7);
  float maxDz = numericalPrecision*plane.position().mag();
  if ( fabs(plane.localZ(raveTrack.position()))>(maxDistToPlane>maxDz?maxDistToPlane:maxDz) ) {
    // propagate
    bool parametersOK = this->propagateParametersOnPlane(raveTrack, plane, x, p, s);
    // check status and deltaPhi limit
    float dphi2 = s*rho;
    dphi2 = dphi2*dphi2*raveTrack.momentum().perp2()/raveTrack.momentum().mag2();
    if ( !parametersOK || dphi2>theMaxDPhi2 )
    {
      return TsosWP(TrajectoryStateOnSurface(),0.);
    }
  }
  else {
    x = raveTrack.position();
    p = raveTrack.momentum();
    s = 0.;
  }
  //
  // Compute propagated state and check change in curvature
  //
  GlobalTrajectoryParameters gtp(x,p,raveTrack.charge(),theField);
  if ( fabs(rho)>1.e-10 && fabs((gtp.transverseCurvature()-rho)/rho)>theMaxDBzRatio )
    return TsosWP(TrajectoryStateOnSurface(),0.);
  //
  // construct TrajectoryStateOnSurface
  //
  return propagatedStateWithPath(raveTrack,plane,gtp,s);
}

/// propagation to plane with path length  -- using rave::Track and ravesurf::Plane
// using ravetrack instead of cms fts --> TEMPORARY charge, position, momentum

std::pair<TrajectoryStateOnSurface,double> AnalyticalPropagator::propagateWithPath(const rave::Track& raveTrack, const ravesurf::Plane& raveplane) const
{
  // check curvature
  double rho = raveTrack.transverseCurvature();

  // propagate parameters
  GlobalPoint x;
  GlobalVector p;
  double s;

  // check if already on plane
  const float maxDistToPlane(0.1e-4);
  const float numericalPrecision(5.e-7);
  float maxDz = numericalPrecision*raveplane.position().mag();
  if ( fabs(raveplane.localZ(raveTrack.position()))>(maxDistToPlane>maxDz?maxDistToPlane:maxDz) ) {
    // propagate
    bool parametersOK = this->propagateParametersOnPlane(raveTrack, raveplane, x, p, s);
    // check status and deltaPhi limit
    float dphi2 = s*rho;
    dphi2 = dphi2*dphi2*raveTrack.momentum().perp2()/raveTrack.momentum().mag2();
    if ( !parametersOK || dphi2>theMaxDPhi2 )
    {
      return TsosWP(TrajectoryStateOnSurface(),0.);
    }
  }
  else {
    x = raveTrack.position();
    p = raveTrack.momentum();
    s = 0.;
  }
  //
  // Compute propagated state and check change in curvature
  //
  GlobalTrajectoryParameters gtp(x,p,raveTrack.charge(),theField);
  if ( fabs(rho)>1.e-10 && fabs((gtp.transverseCurvature()-rho)/rho)>theMaxDBzRatio )
    return TsosWP(TrajectoryStateOnSurface(),0.);
  //
  // construct TrajectoryStateOnSurface
  //
  return propagatedStateWithPath(raveTrack,raveplane,gtp,s);
}



std::pair<TrajectoryStateOnSurface,double>
AnalyticalPropagator::propagateWithPath(const FreeTrajectoryState& fts, 
					const Cylinder& cylinder) const
{
  // check curvature
  double rho = fts.transverseCurvature();

  // propagate parameters
  GlobalPoint x;
  GlobalVector p;
  double s = 0;

  bool parametersOK = this->propagateParametersOnCylinder(fts, cylinder, x, p, s);
  // check status and deltaPhi limit
  float dphi2 = s*rho;
  dphi2 = dphi2*dphi2*fts.momentum().perp2()/fts.momentum().mag2();
  if ( !parametersOK || dphi2>theMaxDPhi2 )  return TsosWP(TrajectoryStateOnSurface(),0.);
  //
  // Compute propagated state and check change in curvature
  //
  GlobalTrajectoryParameters gtp(x,p,fts.charge(),theField);
  if ( fabs(rho)>1.e-10 && fabs((gtp.transverseCurvature()-rho)/rho)>theMaxDBzRatio ) 
    return TsosWP(TrajectoryStateOnSurface(),0.);
  //
  // create result on TangentPlane (local parameters & errors are better defined)
  //
  ReferenceCountingPointer<TangentPlane> plane(cylinder.tangentPlane(x));
  return propagatedStateWithPath(fts,*plane,gtp,s);
}


std::pair<TrajectoryStateOnSurface,double> AnalyticalPropagator::propagateWithPath(const rave::Track& raveTrack, const Cylinder & cylinder) const
{
  // check curvature
  double rho = raveTrack.transverseCurvature();

  // propagate parameters
  GlobalPoint x;
  GlobalVector p;
  double s = 0;

  bool parametersOK = this->propagateParametersOnCylinder(raveTrack, cylinder, x, p, s);
  // check status and deltaPhi limit
  float dphi2 = s*rho;
  dphi2 = dphi2*dphi2*raveTrack.momentum().perp2()/raveTrack.momentum().mag2();
  if ( !parametersOK || dphi2>theMaxDPhi2 )
  {
	  return TsosWP(TrajectoryStateOnSurface(),0.);
  }
  //
  // Compute propagated state and check change in curvature
  //
  GlobalTrajectoryParameters gtp(x,p,raveTrack.charge(),theField);
  if ( fabs(rho)>1.e-10 && fabs((gtp.transverseCurvature()-rho)/rho)>theMaxDBzRatio )
    return TsosWP(TrajectoryStateOnSurface(),0.);
  //
  // create result on TangentPlane (local parameters & errors are better defined)
  //
  ReferenceCountingPointer<TangentPlane> plane(cylinder.tangentPlane(x));
  return propagatedStateWithPath(raveTrack,*plane,gtp,s);
}

std::pair<TrajectoryStateOnSurface,double> AnalyticalPropagator::propagateWithPath(const rave::Track& raveTrack, const ravesurf::Cylinder & raveCylinder) const
{
  // check curvature
  double rho = raveTrack.transverseCurvature();

  // propagate parameters
  GlobalPoint x;
  GlobalVector p;
  double s = 0;

  bool parametersOK = this->propagateParametersOnCylinder(raveTrack, raveCylinder, x, p, s);
  // check status and deltaPhi limit
  float dphi2 = s*rho;
  dphi2 = dphi2*dphi2*raveTrack.momentum().perp2()/raveTrack.momentum().mag2();
  if ( !parametersOK || dphi2>theMaxDPhi2 )
  {
	  return TsosWP(TrajectoryStateOnSurface(),0.);
  }
  //
  // Compute propagated state and check change in curvature
  //
  GlobalTrajectoryParameters gtp(x,p,raveTrack.charge(),theField);
  if ( fabs(rho)>1.e-10 && fabs((gtp.transverseCurvature()-rho)/rho)>theMaxDBzRatio )
    return TsosWP(TrajectoryStateOnSurface(),0.);
  //
  // create result on TangentPlane (local parameters & errors are better defined)
  //
  ReferenceCountingPointer<TangentPlane> plane(raveCylinder.tangentPlane(x));
  return propagatedStateWithPath(raveTrack,*plane,gtp,s);
}



std::pair<TrajectoryStateOnSurface,double>
AnalyticalPropagator::propagatedStateWithPath (const FreeTrajectoryState& fts, 
					       const Surface& surface, 
					       const GlobalTrajectoryParameters& gtp, 
					       const double& s) const
{
  //
  // for forward propagation: state is before surface,
  // for backward propagation: state is after surface
  //
  SurfaceSide side = PropagationDirectionFromPath()(s,propagationDirection())==alongMomentum 
    ? beforeSurface : afterSurface;
  // 
  //
  // error propagation (if needed) and conversion to a TrajectoryStateOnSurface
  //
  if (fts.hasError()) {
    //
    // compute jacobian
    //
    AnalyticalCurvilinearJacobian analyticalJacobian(fts.parameters(), gtp.position(), gtp.momentum(), s);
    const AlgebraicMatrix55 &jacobian = analyticalJacobian.jacobian();
    CurvilinearTrajectoryError cte(ROOT::Math::Similarity(jacobian, fts.curvilinearError().matrix()));
    TrajectoryStateOnSurface tsos (gtp,cte,surface,side);
    tsos.freeState()->setTrackId ( fts.trackId() );
    return TsosWP(tsos,s);
  }
  else {
    //
    // return state without errors
    //
    TrajectoryStateOnSurface tsos (gtp,surface,side);
    tsos.freeState()->setTrackId ( fts.trackId() );
    return TsosWP(tsos,s);
  }
}

// cms
std::pair<TrajectoryStateOnSurface,double>
AnalyticalPropagator::propagatedStateWithPath (const rave::Track& raveTrack,
					       const Surface& surface,
					       const GlobalTrajectoryParameters& gtp,
					       const double& s) const
{
  //
  // for forward propagation: state is before surface,
  // for backward propagation: state is after surface
  //
  SurfaceSide side = PropagationDirectionFromPath()(s,propagationDirection())==alongMomentum
    ? beforeSurface : afterSurface;
  //
  //
  // error propagation (if needed) and conversion to a TrajectoryStateOnSurface
  //
  if (raveTrack.hasError()) {
    //
    // compute jacobian
    //
    AnalyticalCurvilinearJacobian analyticalJacobian(raveTrack.parameters(), gtp.position(), gtp.momentum(), s);
    const AlgebraicMatrix55 &jacobian = analyticalJacobian.jacobian();
    CurvilinearTrajectoryError cte(ROOT::Math::Similarity(jacobian, raveTrack.curvilinearError().matrix()));
    TrajectoryStateOnSurface tsos (gtp,cte,surface,side);
    tsos.freeState()->setTrackId ( raveTrack.trackId() );
    return TsosWP(tsos,s);
  }
  else {
    //
    // return state without errors
    //
    TrajectoryStateOnSurface tsos (gtp,surface,side);
    tsos.freeState()->setTrackId ( raveTrack.trackId() );
    return TsosWP(tsos,s);
  }
}


bool AnalyticalPropagator::propagateParametersOnCylinder(
  const FreeTrajectoryState& fts, const Cylinder& cylinder, 
  GlobalPoint& x, GlobalVector& p, double& s) const
{

  GlobalPoint sp = cylinder.toGlobal(LocalPoint(0.,0.));
  if (sp.x()!=0. || sp.y()!=0.) {
    throw PropagationException("Cannot propagate to an arbitrary cylinder");
  }
  // preset output
  x = fts.position();
  p = fts.momentum();
  s = 0;
  // (transverse) curvature
  double rho = fts.transverseCurvature();
  //
  // Straight line approximation? |rho|<1.e-10 equivalent to ~ 1um 
  // difference in transversal position at 10m.
  //
  if( fabs(rho)<1.e-10 )
    return propagateWithLineCrossing(fts.position(),p,cylinder,x,s);
  //
  // Helix case
  //
  // check for possible intersection
  const double tolerance = 1.e-4; // 1 micron distance
  double rdiff = x.perp() - cylinder.radius();
  if ( fabs(rdiff) < tolerance )  return true;
  //
  // Instantiate HelixBarrelCylinderCrossing and get solutions
  //
  HelixBarrelCylinderCrossing cylinderCrossing(fts.position(),fts.momentum(),rho,
					       propagationDirection(),cylinder);
  if ( !cylinderCrossing.hasSolution() )  return false;
  // path length
  s = cylinderCrossing.pathLength();
  // point
  x = cylinderCrossing.position();
  // direction (renormalised)
  p = cylinderCrossing.direction().unit()*fts.momentum().mag();
  return true;
}

bool AnalyticalPropagator::propagateParametersOnCylinder(
  const rave::Track& raveTrack, const Cylinder& cylinder,
  GlobalPoint& x, GlobalVector& p, double& s) const
{
  GlobalPoint sp = cylinder.toGlobal(LocalPoint(0.,0.));
  if (sp.x()!=0. || sp.y()!=0.) {
	  throw PropagationException("Cannot propagate to an arbitrary cylinder");
  }
  // preset output
  x = raveTrack.position();
  p = raveTrack.momentum();
  s = 0;
  // (transverse) curvature
  double rho = raveTrack.transverseCurvature();
  //
  // Straight line approximation? |rho|<1.e-10 equivalent to ~ 1um
  // difference in transversal position at 10m.
  //
  std::cout << "	rho " << rho << std::endl;
  if( fabs(rho)<1.e-10 )
    return propagateWithLineCrossing(raveTrack.position(),p,cylinder,x,s);
  //
  // Helix case
  //
  // check for possible intersection
  std::cout << "	rho " << rho << std::endl;
  const double tolerance = 1.e-4; // 1 micron distance
  double rdiff = x.perp() - cylinder.radius();
  std::cout << "	rdiff " << rdiff << std::endl;
  std::cout << "	tolerance " << tolerance << std::endl;
  if ( fabs(rdiff) < tolerance )  return true;
  //
  // Instantiate HelixBarrelCylinderCrossing and get solutions
  //
  HelixBarrelCylinderCrossing cylinderCrossing(raveTrack.position(),raveTrack.momentum(),rho,
					       propagationDirection(),cylinder);
  std::cout << "	!cylinderCrossing.hasSolution() " << !cylinderCrossing.hasSolution() << std::endl;
  if ( !cylinderCrossing.hasSolution() )  return false;
  // path length
  s = cylinderCrossing.pathLength();
  // point
  x = cylinderCrossing.position();
  // direction (renormalised)
  p = cylinderCrossing.direction().unit()*raveTrack.momentum().mag();
  std::cout << "	dd" <<  std::endl;
  return true;
}

bool AnalyticalPropagator::propagateParametersOnCylinder(
  const rave::Track& raveTrack, const ravesurf::Cylinder& raveCylinder,
  GlobalPoint& x, GlobalVector& p, double& s) const
{
  GlobalPoint sp = raveCylinder.toGlobal(LocalPoint(0.,0.));
  if (sp.x()!=0. || sp.y()!=0.) {
	  throw PropagationException("Cannot propagate to an arbitrary cylinder");
  }
  // preset output
  x = raveTrack.position();
  p = raveTrack.momentum();
  s = 0;
  // (transverse) curvature
  double rho = raveTrack.transverseCurvature();
  //
  // Straight line approximation? |rho|<1.e-10 equivalent to ~ 1um
  // difference in transversal position at 10m.
  //
  std::cout << "	rho " << rho << std::endl;
  if( fabs(rho)<1.e-10 )
    return propagateWithLineCrossing(raveTrack.position(),p,raveCylinder,x,s);
  //
  // Helix case
  //
  // check for possible intersection
  std::cout << "	rho " << rho << std::endl;
  const double tolerance = 1.e-4; // 1 micron distance
  double rdiff = x.perp() - raveCylinder.radius();
  std::cout << "	rdiff " << rdiff << std::endl;
  std::cout << "	tolerance " << tolerance << std::endl;
  if ( fabs(rdiff) < tolerance )  return true;
  //
  // Instantiate HelixBarrelCylinderCrossing and get solutions
  //
  HelixBarrelCylinderCrossing cylinderCrossing(raveTrack.position(),raveTrack.momentum(),rho,
					       propagationDirection(),raveCylinder);
  std::cout << "	!cylinderCrossing.hasSolution() " << !cylinderCrossing.hasSolution() << std::endl;
  if ( !cylinderCrossing.hasSolution() )  return false;
  // path length
  s = cylinderCrossing.pathLength();
  // point
  x = cylinderCrossing.position();
  // direction (renormalised)
  p = cylinderCrossing.direction().unit()*raveTrack.momentum().mag();
  std::cout << "	dd" <<  std::endl;
  return true;
}

bool 
AnalyticalPropagator::propagateParametersOnPlane(const FreeTrajectoryState& fts, 
						 const Plane& plane, 
						 GlobalPoint& x, 
						 GlobalVector& p, 
						 double& s) const
{
  // initialisation of position, momentum and path length
  x = fts.position();
  p = fts.momentum();
  s = 0;
  // (transverse) curvature
  double rho = fts.transverseCurvature();
  //
  // Straight line approximation? |rho|<1.e-10 equivalent to ~ 1um 
  // difference in transversal position at 10m.
  //
  if( fabs(rho)<1.e-10 )
    return propagateWithLineCrossing(fts.position(),p,plane,x,s);
  //
  // Helix case 
  //
  GlobalVector u = plane.normalVector();
  const double small = 1.e-6; // for orientation of planes
  //
  // Frame-independant point and vector are created explicitely to 
  // avoid confusing gcc (refuses to compile with temporary objects
  // in the constructor).
  //
  HelixPlaneCrossing::PositionType helixPos(x);
  HelixPlaneCrossing::DirectionType helixDir(p);
  if (fabs(u.z()) < small) {
    // barrel plane:
    // instantiate HelixBarrelPlaneCrossing, get vector of solutions and check for existance
    HelixBarrelPlaneCrossingByCircle planeCrossing(helixPos,helixDir,rho,propagationDirection());
    return propagateWithHelixCrossing(planeCrossing,plane,fts.momentum().mag(),x,p,s);
  }
  if (fabs(u.x()) < small && fabs(u.y()) < small) {
    // forward plane:
    // instantiate HelixForwardPlaneCrossing, get vector of solutions and check for existance
    HelixForwardPlaneCrossing planeCrossing(helixPos,helixDir,rho,propagationDirection());
    return propagateWithHelixCrossing(planeCrossing,plane,fts.momentum().mag(),x,p,s);
  }
  else {
    // arbitrary plane:
    // instantiate HelixArbitraryPlaneCrossing, get vector of solutions and check for existance
    HelixArbitraryPlaneCrossing planeCrossing(helixPos,helixDir,rho,propagationDirection());
    return propagateWithHelixCrossing(planeCrossing,plane,fts.momentum().mag(),x,p,s);
  }
}

bool
AnalyticalPropagator::propagateParametersOnPlane(const rave::Track& raveTrack,
						 const Plane& plane,
						 GlobalPoint& x,
						 GlobalVector& p,
						 double& s) const
{
  // initialisation of position, momentum and path length
  x = raveTrack.position();
  p = raveTrack.momentum();
  s = 0;
  // (transverse) curvature
  double rho = raveTrack.transverseCurvature();
  //
  // Straight line approximation? |rho|<1.e-10 equivalent to ~ 1um
  // difference in transversal position at 10m.
  //
  if( fabs(rho)<1.e-10 )
    return propagateWithLineCrossing(raveTrack.position(),p,plane,x,s);
  //
  // Helix case
  //
  GlobalVector u = plane.normalVector();
  const double small = 1.e-6; // for orientation of planes
  //
  // Frame-independant point and vector are created explicitely to
  // avoid confusing gcc (refuses to compile with temporary objects
  // in the constructor).
  //
  HelixPlaneCrossing::PositionType helixPos(x);
  HelixPlaneCrossing::DirectionType helixDir(p);
  if (fabs(u.z()) < small) {
    // barrel plane:
    // instantiate HelixBarrelPlaneCrossing, get vector of solutions and check for existance
    HelixBarrelPlaneCrossingByCircle planeCrossing(helixPos,helixDir,rho,propagationDirection());
    return propagateWithHelixCrossing(planeCrossing,plane,raveTrack.momentum().mag(),x,p,s);
  }
  if (fabs(u.x()) < small && fabs(u.y()) < small) {
    // forward plane:
    // instantiate HelixForwardPlaneCrossing, get vector of solutions and check for existance
    HelixForwardPlaneCrossing planeCrossing(helixPos,helixDir,rho,propagationDirection());
    return propagateWithHelixCrossing(planeCrossing,plane,raveTrack.momentum().mag(),x,p,s);
  }
  else {
    // arbitrary plane:
    // instantiate HelixArbitraryPlaneCrossing, get vector of solutions and check for existance
    HelixArbitraryPlaneCrossing planeCrossing(helixPos,helixDir,rho,propagationDirection());
    return propagateWithHelixCrossing(planeCrossing,plane,raveTrack.momentum().mag(),x,p,s);
  }
}

bool
AnalyticalPropagator::propagateParametersOnPlane(const rave::Track& raveTrack,
						 const ravesurf::Plane& ravePlane,
						 GlobalPoint& x,
						 GlobalVector& p,
						 double& s) const
{
  // initialisation of position, momentum and path length
  x = raveTrack.position();
  p = raveTrack.momentum();
  s = 0;
  // (transverse) curvature
  double rho = raveTrack.transverseCurvature();
  //
  // Straight line approximation? |rho|<1.e-10 equivalent to ~ 1um
  // difference in transversal position at 10m.
  //
  if( fabs(rho)<1.e-10 )
    return propagateWithLineCrossing(raveTrack.position(),p,ravePlane,x,s);
  //
  // Helix case
  //
  GlobalVector u = ravePlane.normalVector();
  const double small = 1.e-6; // for orientation of planes
  //
  // Frame-independant point and vector are created explicitely to
  // avoid confusing gcc (refuses to compile with temporary objects
  // in the constructor).
  //
  HelixPlaneCrossing::PositionType helixPos(x);
  HelixPlaneCrossing::DirectionType helixDir(p);
  if (fabs(u.z()) < small) {
    // barrel plane:
    // instantiate HelixBarrelPlaneCrossing, get vector of solutions and check for existance
    HelixBarrelPlaneCrossingByCircle planeCrossing(helixPos,helixDir,rho,propagationDirection());
    return propagateWithHelixCrossing(planeCrossing,ravePlane,raveTrack.momentum().mag(),x,p,s);
  }
  if (fabs(u.x()) < small && fabs(u.y()) < small) {
    // forward plane:
    // instantiate HelixForwardPlaneCrossing, get vector of solutions and check for existance
    HelixForwardPlaneCrossing planeCrossing(helixPos,helixDir,rho,propagationDirection());
    return propagateWithHelixCrossing(planeCrossing,ravePlane,raveTrack.momentum().mag(),x,p,s);
  }
  else {
    // arbitrary plane:
    // instantiate HelixArbitraryPlaneCrossing, get vector of solutions and check for existance
    HelixArbitraryPlaneCrossing planeCrossing(helixPos,helixDir,rho,propagationDirection());
    return propagateWithHelixCrossing(planeCrossing,ravePlane,raveTrack.momentum().mag(),x,p,s);
  }
}

bool
AnalyticalPropagator::propagateWithLineCrossing (const GlobalPoint& x0, 
						 const GlobalVector& p0,
						 const Plane& plane,
						 GlobalPoint& x, double& s) const {
  //
  // Instantiate auxiliary object for finding intersection.
  // Frame-independant point and vector are created explicitely to 
  // avoid confusing gcc (refuses to compile with temporary objects
  // in the constructor).
  //
  StraightLinePlaneCrossing::PositionType pos(x0);
  StraightLinePlaneCrossing::DirectionType dir(p0);
  StraightLinePlaneCrossing planeCrossing(pos,dir,propagationDirection());
  //
  // get solution
  //
  std::pair<bool,double> propResult = planeCrossing.pathLength(plane);
  if ( !propResult.first )  return false;
  s = propResult.second;
  // point (reconverted to GlobalPoint)
  x = GlobalPoint(planeCrossing.position(s));
  //
  return true;
}

bool
AnalyticalPropagator::propagateWithLineCrossing (const GlobalPoint& x0,
						 const GlobalVector& p0,
						 const ravesurf::Plane& ravePlane,
						 GlobalPoint& x, double& s) const {
  //
  // Instantiate auxiliary object for finding intersection.
  // Frame-independant point and vector are created explicitely to
  // avoid confusing gcc (refuses to compile with temporary objects
  // in the constructor).
  //
  StraightLinePlaneCrossing::PositionType pos(x0);
  StraightLinePlaneCrossing::DirectionType dir(p0);
  StraightLinePlaneCrossing planeCrossing(pos,dir,propagationDirection());
  //
  // get solution
  //
  std::pair<bool,double> propResult = planeCrossing.pathLength(ravePlane);
  if ( !propResult.first )  return false;
  s = propResult.second;
  // point (reconverted to GlobalPoint)
  x = GlobalPoint(planeCrossing.position(s));
  //
  return true;
}

bool
AnalyticalPropagator::propagateWithLineCrossing (const GlobalPoint& x0,
						 const GlobalVector& p0,
						 const ravesurf::Cylinder& raveCylinder,
						 GlobalPoint& x, double& s) const {
  //
  // Instantiate auxiliary object for finding intersection.
  // Frame-independant point and vector are created explicitely to
  // avoid confusing gcc (refuses to compile with temporary objects
  // in the constructor).
  //
  StraightLineBarrelCylinderCrossing cylCrossing(x0,p0,propagationDirection());
  //
  // get solution
  //
  std::pair<bool,double> propResult = cylCrossing.pathLength(raveCylinder);
  if ( !propResult.first )  return false;
  s = propResult.second;
  // point (reconverted to GlobalPoint)
  x = cylCrossing.position(s);
  //
  return true;
}

bool
AnalyticalPropagator::propagateWithLineCrossing (const GlobalPoint& x0,
						 const GlobalVector& p0,
						 const Cylinder& cylinder,
						 GlobalPoint& x, double& s) const {
  //
  // Instantiate auxiliary object for finding intersection.
  // Frame-independant point and vector are created explicitely to 
  // avoid confusing gcc (refuses to compile with temporary objects
  // in the constructor).
  //
  StraightLineBarrelCylinderCrossing cylCrossing(x0,p0,propagationDirection());
  //
  // get solution
  //
  std::pair<bool,double> propResult = cylCrossing.pathLength(cylinder);
  if ( !propResult.first )  return false;
  s = propResult.second;
  // point (reconverted to GlobalPoint)
  x = cylCrossing.position(s);
  //
  return true;
}

bool
AnalyticalPropagator::propagateWithHelixCrossing (HelixPlaneCrossing& planeCrossing,
						  const Plane& plane,
						  const float pmag,
						  GlobalPoint& x,
						  GlobalVector& p,
						  double& s) const {
  // get solution
  std::pair<bool,double> propResult = planeCrossing.pathLength(plane);
  if ( !propResult.first )  return false;
  s = propResult.second;
  // point (reconverted to GlobalPoint)
  HelixPlaneCrossing::PositionType xGen = planeCrossing.position(s);
  x = GlobalPoint(xGen);
  // direction (reconverted to GlobalVector, renormalised)
  HelixPlaneCrossing::DirectionType pGen = planeCrossing.direction(s);
  pGen *= pmag/pGen.mag();
  p = GlobalVector(pGen);
  //
  return true;
}


bool
AnalyticalPropagator::propagateWithHelixCrossing (HelixPlaneCrossing& planeCrossing,
						  const ravesurf::Plane& ravePlane,
						  const float pmag,
						  GlobalPoint& x,
						  GlobalVector& p,
						  double& s) const {
  // get solution
  std::pair<bool,double> propResult = planeCrossing.pathLength(ravePlane);
  if ( !propResult.first )  return false;
  s = propResult.second;
  // point (reconverted to GlobalPoint)
  HelixPlaneCrossing::PositionType xGen = planeCrossing.position(s);
  x = GlobalPoint(xGen);
  // direction (reconverted to GlobalVector, renormalised)
  HelixPlaneCrossing::DirectionType pGen = planeCrossing.direction(s);
  pGen *= pmag/pGen.mag();
  p = GlobalVector(pGen);
  //
  return true;
}
