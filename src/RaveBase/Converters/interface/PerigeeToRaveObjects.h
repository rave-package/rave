#ifndef _PerigeeToRaveObjects_H_
#define _PerigeeToRaveObjects_H_

#include "RaveBase/RaveInterface/rave/Charge.h"
#include "RaveBase/RaveInterface/rave/Vector3D.h"
#include "RaveBase/RaveInterface/rave/Vector6D.h"
#include "RaveBase/RaveInterface/rave/Covariance6D.h"
#include "RaveBase/RaveInterface/rave/PerigeeParameters3D.h"
#include "RaveBase/RaveInterface/rave/PerigeeParameters5D.h"
#include "RaveBase/RaveInterface/rave/PerigeeCovariance5D.h"

#include <rave/MagneticField.h>
#include "TrackingTools/TrajectoryParametrization/interface/GlobalTrajectoryParameters.h"

#ifdef WITH_KINEMATICS
#include "RaveBase/RaveInterface/rave/Vector7D.h"
#include "RaveBase/RaveInterface/rave/Covariance7D.h"
#include "RaveBase/RaveInterface/rave/PerigeeParameters6D.h"
#include "RaveBase/RaveInterface/rave/PerigeeCovariance6D.h"
#endif

namespace rave
{

/**
 * @class PerigeeToRaveObjects converts from perigee coords to euclidian space.
 *
 * This conversion class is used internally by several data classes to provide
 * their data in perigee parametrization also.
 */
class PerigeeToRaveObjects
{
  public:
    Vector3D convert(const PerigeeParameters3D &) const;
    //Vector6D convert(const PerigeeParameters5D &, const Charge, const Point3D & referencePoint) const;
    Covariance6D convert(const PerigeeCovariance5D & error, const GlobalTrajectoryParameters & gtp) const;

  #ifdef WITH_KINEMATICS
  public:
    Vector7D convert(
        const PerigeeParameters6D &, const Charge, const Point3D & referencePoint) const;
    Covariance7D convert(
        const PerigeeCovariance6D &, const Vector7D & parameters, 
        const Charge charge, const Point3D & referencePoint) const;
  #endif
};

} // namespace rave

#endif
