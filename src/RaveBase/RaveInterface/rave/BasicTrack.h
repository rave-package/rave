#ifndef _RaveBasicTrack_H_
#define _RaveBasicTrack_H_

#include <rave/Vector6D.h>
#include <rave/Covariance6D.h>
#include <rave/Charge.h>
#include <rave/ReferenceCounted.h>
#include <rave/CopyUsingNew.h>
#include <rave/ProxyBase.h>
#include <rave/AbstractTrack.h>
#include <rave/AbstractPerigeeAccess.h>
#include <string>
#include <vector>
#include <utility>

#include "TrackingTools/TrajectoryParametrization/interface/GlobalTrajectoryParameters.h"
#include "TrackingTools/TrajectoryParametrization/interface/CartesianTrajectoryError.h"
#include "TrackingTools/TrajectoryParametrization/interface/CurvilinearTrajectoryError.h"
#include "RaveBase/Converters/interface/RaveToAlgebraicObjects.h"
#include "TrackingTools/TrajectoryParametrization/interface/TrajectoryStateExceptions.h"
namespace rave
{
/** \class BasicRaveBasicTrack defines the input to the rave library.
 * Fixme, it's more something like a RaveTrajectoryState,
 * than a BasicRaveBasicTrack.
 */

class BasicTrack :
	public RaveReferenceCounted, 
	public AbstractTrack,
        public AbstractPerigeeAccess
{
  public:
    typedef RaveProxyBase< BasicTrack, CopyUsingNew<BasicTrack> > Proxy;

    /**
     *  Create a BasicRaveBasicTrack from a 6-dimensional euclidean trajectory state
     *  plus covariance matrix, plus charge, plus an optional
     *  pointer to the "original track", whatever that means
     */
    BasicTrack( const Vector6D &, const Covariance6D &, Charge,
           float chi2, float ndof,
           void * originaltrack = 0, std::string tag="" );
    BasicTrack( int id, const Vector6D &, const Covariance6D &, Charge,
           float chi2, float ndof,
           void * originaltrack = 0, std::string tag="" );
    BasicTrack ( const std::vector < std::pair < float, rave::BasicTrack > > & );
    BasicTrack ( int id, const std::vector < std::pair < float, rave::BasicTrack > > & );

    void setComponents ( const std::vector < std::pair < float, rave::BasicTrack > > & );

    BasicTrack();

    Charge charge() const;
    const Vector6D & state() const;
    const Vector3D & momentum() const;
    const Point3D & position() const;
    const Covariance6D & error() const;
    void * originalObject() const;
    std::string tag() const;
    int id() const;
    float chi2() const;
    float ndof() const;

    const PerigeeParameters5D & perigeeParameters() const;
    const PerigeeCovariance5D & perigeeCovariance() const;

    bool isValid() const;

    BasicTrack * clone () const;

    std::vector < std::pair < float, rave::BasicTrack > > components() const;

    bool operator< ( const rave::BasicTrack & ) const;


    // additional CMS functions
    int trackId() const { return theTrackId; }

    void setTrackId( int id ) { theTrackId=id; }
    // access
    // propagate access to parameters
    GlobalPoint position2() const { return theGlobalParameters.position(); }
    GlobalVector momentum2() const { return theGlobalParameters.momentum(); }
    TrackCharge charge2() const { return theGlobalParameters.charge(); }
    double signedInverseMomentum() const {return theGlobalParameters.signedInverseMomentum(); }
    double transverseCurvature() const { return theGlobalParameters.transverseCurvature(); }

    // direct access
    bool hasCartesianError() const {return theCartesianErrorValid;}
    bool hasCurvilinearError() const {return theCurvilinearErrorValid;}
    bool hasError() const { return theCurvilinearErrorValid || theCartesianErrorValid; }
    const GlobalTrajectoryParameters& parameters() const { return theGlobalParameters; }
    const CartesianTrajectoryError& cartesianError() const {
        if (!hasError()) throw TrajectoryStateException(
          "FreeTrajectoryState: attempt to access errors when none available");
        if (!theCartesianErrorValid)
          createCartesianError();
        return theCartesianError;
    }
    const CurvilinearTrajectoryError& curvilinearError() const {
        if (!hasError()) throw TrajectoryStateException(
          "FreeTrajectoryState: attempt to access errors when none available");
        if (!theCurvilinearErrorValid)
        	createCurvilinearError();
        return theCurvilinearError;
    }
    void rescaleError(double factor) {
        bool zeroField = parameters().magneticFieldInInverseGeV(GlobalPoint(0,0,0)).mag2()==0;
        if (zeroField) {
          if (theCartesianErrorValid){
    	if (!theCurvilinearErrorValid) createCurvilinearError();
    	theCurvilinearError.zeroFieldScaling(factor*factor);
    	createCartesianError();
          }else
    	if (theCurvilinearErrorValid) theCurvilinearError.zeroFieldScaling(factor*factor);
        } else{
          if (theCartesianErrorValid){
    	theCartesianError *= (factor*factor);
          }
          if (theCurvilinearErrorValid){
    	theCurvilinearError *= (factor*factor);
          }
        }
    }

    void setCartesianError(const CartesianTrajectoryError &err) {
            theCartesianError = err; theCartesianErrorValid = true;
    }
    void setCartesianError(const AlgebraicSymMatrix66 &err) {
            theCartesianError = CartesianTrajectoryError(err); theCartesianErrorValid = true;
    }
    void setCurvilinearError(const CurvilinearTrajectoryError &err) {
            theCurvilinearError = err; theCurvilinearErrorValid = true;
    }
    void setCurvilinearError(const AlgebraicSymMatrix55 &err) {
            theCurvilinearError = CurvilinearTrajectoryError(err); theCurvilinearErrorValid = true;
    }

    // properties
    bool canReach(double radius) const;



  private:
    void createMomPos();
    
    Vector6D theState;
    Vector3D theMomentum;
    Point3D thePosition;
    Covariance6D theError;
    Charge theCharge;
    void * thePointer;
    std::string theTag;
    int theId;
    bool theIsValid;
    float theChi2;
    float theNdof;
    std::vector < std::pair < float, BasicTrack > > theComponents;


    // additional cms format
    GlobalTrajectoryParameters  theGlobalParameters;
    CartesianTrajectoryError    theCartesianError;
    CurvilinearTrajectoryError  theCurvilinearError;
    bool                        theCartesianErrorValid;
    bool                        theCurvilinearErrorValid;
    int                         theTrackId; // which track does this belong to

    // convert curvilinear errors to cartesian
    void createCartesianError() const;
    // convert cartesian errors to curvilinear
    void createCurvilinearError() const;

  private:
    void calculateCachedPerigeeRepresentation() const;
    mutable bool hasCachedPerigeeRepresentation;
    mutable PerigeeParameters5D cachedPerigeeParameters;
    mutable PerigeeCovariance5D cachedPerigeeCovariance;
};

}

#endif
