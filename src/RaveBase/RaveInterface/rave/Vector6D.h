#ifndef _RAVEVECTOR6D_H_
#define _RAVEVECTOR6D_H_

//#include <rave/Vector3D.h>
//#include <rave/Point3D.h>

//#include "boost/operators.hpp"

#include "TrackingTools/TrajectoryParametrization/interface/GlobalTrajectoryParameters.h"

namespace rave
{
typedef GlobalTrajectoryParameters Vector6D;
}
/** \class RaveVector6D a 6-dimensional state
 *  Lengths are given in cm, momenta in GeV/c.
 */

/**
class  Vector6D :
    boost::equality_comparable<Vector6D>
{
  public:

    Vector6D();

    Vector6D( float x, float y, float z,
              float px, float py, float pz );

    Vector6D( const Point3D & position,
              const Vector3D & momentum );

    virtual ~Vector6D() {};

    float x() const;
    float y() const;
    float z() const;

    float px() const;
    float py() const;
    float pz() const;

    Vector3D momentum() const;
    Point3D position() const;

    void addMomentum ( const Vector3D & other );

    virtual bool equal(const Vector6D & other) const;

  private:
    CheckedFloat thex;
    CheckedFloat they;
    CheckedFloat thez;
    CheckedFloat thepx;
    CheckedFloat thepy;
    CheckedFloat thepz;
};

 bool operator==(const Vector6D & lhs, const Vector6D & rhs);

} // namespace rave
**/
#endif

