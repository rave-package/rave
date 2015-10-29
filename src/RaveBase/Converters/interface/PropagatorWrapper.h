#ifndef _PropagatorWrapper_H_
#define _PropagatorWrapper_H_

#include "TrackingTools/GeomPropagators/interface/Propagator.h"
#include "rave/Propagator.h"
#include "rave/Track.h"

class PropagatorWrapper : public Propagator
{
  public:
    PropagatorWrapper ( const rave::Propagator &  );
    PropagatorWrapper ( const PropagatorWrapper & );
    ~PropagatorWrapper();
    
    virtual std::pair< TrajectoryStateOnSurface, double> 
    propagateWithPath (const FreeTrajectoryState&, const Plane&) const;

    virtual std::pair < TrajectoryStateOnSurface, double >
    propagateWithPath ( const rave::Track&, const Plane& ) const;

    TrajectoryStateOnSurface propagate (
        const FreeTrajectoryState&, const Plane & ) const;

    TrajectoryStateOnSurface propagate (
            const rave::Track&, const Plane & ) const;

    std::pair< TrajectoryStateOnSurface, double> 
    propagateWithPath (const FreeTrajectoryState&, const Cylinder&) const;
    
    std::pair < TrajectoryStateOnSurface, double >
    propagateWithPath ( const rave::Track&, const Cylinder& ) const;

    TrajectoryStateOnSurface propagate (
        const FreeTrajectoryState&, const Cylinder & ) const;

    TrajectoryStateOnSurface propagate (
        const rave::Track&, const Cylinder & ) const;

    const rave::MagneticField* magneticField() const;
    PropagatorWrapper * clone() const;


  private:
    rave::Propagator * theRavePropagator;
};

#endif
