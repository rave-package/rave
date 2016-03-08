#ifndef _RaveTrack_H_
#define _RaveTrack_H_

#include <rave/Vector6D.h>
#include <rave/Covariance6D.h>
#include <rave/Charge.h>
//#include <rave/BasicTrack.h>
#include <rave/ProxyBase.h>
#include <string>

#include "TrackingTools/TrajectoryState/interface/FreeTrajectoryState.h"
#include "TrackingTools/TrajectoryParametrization/interface/GlobalTrajectoryParameters.h"

namespace rave
{

/**
 * RaveTrack defines the input to the rave library.
 *
 */
/*
typedef GlobalVector Vector3D;
typedef GlobalTrajectoryParameters Vector6D;
typedef CartesianTrajectoryError Covariance6D;
*/
class Track:  public ::FreeTrajectoryState
{
  public:

    /**
     *
     *  Create a RaveTrack from GlobalTrajectoryParameters, Cartesian TrajectoryError,
     *  chi2, ndof and optional pointer to the "original track" and a tag.
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

    Track( const std::vector < std::pair < float, Track > > & components );

    Track( int id, const std::vector < std::pair < float, Track > > & components );

    Track();

    const GlobalTrajectoryParameters & state() const;
    const CartesianTrajectoryError & CartesianError() const;
    const CartesianTrajectoryError & error() const;
    const CurvilinearTrajectoryError & CurvilinearError() const;

    int id() const;
    void * originalObject() const;


    float chi2() const;
    float ndof() const;
    std::string tag() const;

    bool isValid() const;
    std::vector < std::pair < float, rave::Track > > components() const;
    void setComponents ( const std::vector < std::pair < float, rave::Track > > & );
    bool operator< ( const rave::Track & ) const;
    bool operator== ( const rave::Track & ) const;


private:

    void * thePointer;
    std::string theTag;
    bool theIsValid;
    float theChi2;
    float theNdof;
    std::vector < std::pair < float, Track > > theComponents;


};

}

#endif
