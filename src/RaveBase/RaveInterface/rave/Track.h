#ifndef _RaveTrack_H_
#define _RaveTrack_H_

#include <rave/Vector6D.h>
#include <rave/Covariance6D.h>
#include <rave/Charge.h>
#include <rave/BasicTrack.h>
#include <rave/ProxyBase.h>
#include <string>

#include "TrackingTools/TrajectoryState/interface/FreeTrajectoryState.h"
#include "TrackingTools/TrajectoryParametrization/interface/GlobalTrajectoryParameters.h"

namespace rave
{

/** \class RaveTrack defines the input to the rave library.
 *  The class is reference counted, so dont worry about memory management.
 */

class Track:  public ::FreeTrajectoryState
{
  public:

    /**
     *  to be updated!
     *
     *  Create a RaveTrack from a 6-dimensional euclidean trajectory state
     *  plus covariance matrix, plus charge, plus an optional
     *  pointer to the "original track", whatever that means.
     *
     *       Lengths are given in cm, momenta in GeV/c.
     */

    Track( int id, const GlobalTrajectoryParameters &, const CartesianTrajectoryError &,
             float chi2, float ndof, void * originaltrack = 0, std::string tag="" );

    Track( const GlobalTrajectoryParameters &, const CartesianTrajectoryError &,
                 float chi2, float ndof, void * originaltrack = 0, std::string tag="" );

    Track( int id, const GlobalTrajectoryParameters &, const CurvilinearTrajectoryError &,
                 float chi2, float ndof, void * originaltrack = 0, std::string tag="" );

    Track( int id, const GlobalTrajectoryParameters &,
                     float chi2, float ndof, int originaltrack = 0, std::string tag="" );

    Track();

    Charge raveCharge() const;
    const GlobalTrajectoryParameters & state() const;
    const CartesianTrajectoryError & CartesianError() const;
    const CurvilinearTrajectoryError & CurvilinearError() const;

    int id() const;
    void * originalObject() const;


    float chi2() const;
    float ndof() const;
    std::string tag() const;

    bool isValid() const;
    bool operator< ( const rave::Track & ) const;
    bool operator== ( const rave::Track & ) const;


private:

    int theId; // rave interface id, there is also an internal (cms) theTrackId
    Charge theRaveCharge;
    void * thePointer;
    std::string theTag;
    bool theIsValid;
    float theChi2;
    float theNdof;


};

}

#endif
