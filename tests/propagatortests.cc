#include <iostream>
#include <rave/Propagator.h>
#include <rave/VacuumPropagator.h>
#include <rave/VertexFactory.h>
#include <rave/ConstantMagneticField.h>
#include "RaveBase/Converters/interface/RaveStreamers.h"

// #include "RaveBase/Converters/interface/RaveToCmsObjects.h"

using namespace std;

namespace {
  rave::Track track1()
  {
	RaveToCmsObjects forward;

    rave::Vector6D state1 ( 0.0001, 0.0001, 0.0001, -31.2685, 13.0785, 28.7524 );
    //GlobalTrajectoryParameters gtp1 = forward.convert(state1, 1.0);
    rave::Covariance6D cov1 (
        1.5e-7,    3.6e-7,    4.0e-14,
                   8.5e-7,    9.6e-14,
                              1.7e-6,
                                      -1.4e-16,  -3.4e-16,   1.8e-24,
                                      -3.3e-16,  -8.1e-16,   4.3e-24,
                                      -3.9e-9,   -9.4e-9,    5.0e-17,
                                       4.9e-3,   -2.0e-3,   -4.4e-3,
                                                  9.2e-4,    1.8e-3,
                                                             4.1e-3 );
    //CartesianTrajectoryError cte1 = forward.convert(cov1);

    //return rave::Track ( state1, cov1, 1, 0., 0. ) ;
    return rave::Track ( state1, cov1, 0., 0. );
  }
  
  rave::Track track2()
  {
	RaveToCmsObjects forward;

    rave::Vector6D state1 ( 0.0001, 0.0001, 0.0001, -31.2685, 13.0785, 28.7524 );
   // GlobalTrajectoryParameters gtp1 = forward.convert(state1, -1.0);
    rave::Covariance6D cov1 (
        1.5e-7,    3.6e-7,    4.0e-14,
                   8.5e-7,    9.6e-14,
                              1.7e-6,
                                      -1.4e-16,  -3.4e-16,   1.8e-24,
                                      -3.3e-16,  -8.1e-16,   4.3e-24,
                                      -3.9e-9,   -9.4e-9,    5.0e-17,
                                       4.9e-3,   -2.0e-3,   -4.4e-3,
                                                  9.2e-4,    1.8e-3,
                                                             4.1e-3 );
    //CartesianTrajectoryError cte1 = forward.convert(cov1);

    return rave::Track ( state1, cov1, 0., 0. ) ;
    // return rave::Track ( gtp1, cte1, 0., 0. );
  }
}

class MyPropagator : public rave::Propagator
{
  public:
//	virtual std::shared_ptr < Propagator > copy() const override;
  virtual std::shared_ptr < Propagator > copy() const override {
  //return new MyPropagator ( *this );
  return make_shared < MyPropagator > ( * this );
  }
  rave::Track closestTo ( const rave::Track & orig,
                          const rave::Point3D &, bool transverse ) const 
  {
    rave::Track ret ( orig );
    return ret;
  }
  
  std::pair < rave::Track, double > to ( const rave::Track & orig,
                   const ravesurf::Plane & ) const 
  {
    rave::Track ret ( orig );
    return pair < rave::Track, double > ( ret, 0. );
  }
  
  std::pair < rave::Track, double > to ( const rave::Track & orig,
                   const ravesurf::Cylinder & ) const 
  {
    rave::Track ret ( orig );
    return pair < rave::Track, double > ( ret, 0. );
  }
};



int main(void)
{
  /*
  rave::VertexFactory f ( rave::ConstantMagneticField ( 3.8 ) );
  cout << "propagatortests" << endl;
  rave::VacuumPropagator vacuumpropagator;
  rave::Track  t1 = track1();
  cout << "original track at " << t1 << endl;
  rave::Point3D pivot ( 0., 0., 0. );
  rave::Track vacuumed = vacuumpropagator.closestTo ( t1, pivot,true  );
  cout << "vacuumed at " << vacuumed << endl;
  */
  rave::Point3D pivot ( 0., 0., 0. );


  // added Test 
  rave::VertexFactory f2 ( rave::ConstantMagneticField ( 3.2 ) );
  cout << " Own Propagator " << endl;
  MyPropagator mypropagator;
  rave::Track t2 = track1();
  cout << "original track at " << t2 << endl;
  rave::Point3D pivot2(0.,0.,0.);
  rave::Track newtr = mypropagator.closestTo (t2, pivot, true );
  cout << "track prop with own prop " << newtr << endl;

  // additional tests for cms swicht - first some track tests
  rave::Track t3 = track1();
  cout << "Track charge: old " << t3.charge() << " new " << t3.charge() << endl;
  cout << "Track momentum: old " << t3.momentum() << " new " << t3.momentum() << endl;
  cout << "Track position: old " << t3.position() << " new " << t3.position() << endl;
  cout << "Track trackId: old " << t3.id() << " new " << t3.trackId() << endl;
  cout << "Track signInvMom " << t3.signedInverseMomentum() << endl;
  cout << "Track transCurv " << t3.transverseCurvature() << endl;
  cout << "Track hasCartErr " << t3.hasCartesianError() <<  endl;
  cout << "Track hasCurvlError " << t3.hasCurvilinearError() << endl;
  cout << "Track hasErr " << t3.hasError() <<  endl;
  //cout << "Track trackId: old " << t3.parameters() << endl;
  //
 
 // add Test for to fucntion of vacuum prop
 //    Cylinder ( const rave::Point3D & pos, const rave::Point3D & axis, float radius );
  /*
  const rave::Point3D pos3D ( 0.00, 0.00, 0.0025 );
  const  rave::Point3D axis3D ( 0.0001, 0.0001, 1.000 );
  float radius =1000.25 ; 
  ravesurf::Cylinder cyl( pos3D, axis3D, radius);
  rave::VacuumPropagator vacPro;
  pair < rave::Track, double > result = vacPro.to(t3, cyl);
  std::cout << "VacPro Test first element " << result.first << " second element " << result.second << std::endl;
  */ 

  cout << "Test the new plane: " << endl;
  const rave::Point3D pos(0.0, 1.0, 0.0);
  const rave::Vector3D nor(42.0, 42.0, 42.0);
  const ravesurf::Plane plane (pos, nor); 
  cout << " ** Checkpoint 1 **" << endl;
  cout << " function postionRave       " << plane.positionRave() << endl;
  cout << " function normalVectorRave  " << plane.normalVectorRave() << endl;
  cout << " function normalVector (cms)" << plane.normalVector() << endl;
//  cout << " function normalVector (cms)" << plane.normalVector() << endl;
//  cout << " function normalVector (cms)" << plane.normalVector() << endl;

}

