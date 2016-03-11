#ifndef _RaveCylinder_H_
#define _RaveCylinder_H_

#include <rave/Point3D.h>
#include <rave/Vector3D.h>
//#include "RaveBase/Converters/interface/RaveToCmsObjects.h"
#include "DataFormats/GeometrySurface/interface/Surface.h"

namespace ravesurf {

/** 
 * @brief a class implementing a cylindric "detector" plane
 * @ingroup ravesurf
 *
 */

class Cylinder: public Surface
{
  public:
    Cylinder ( const rave::Point3D & pos, const rave::Vector3D & axis, float radius );

    rave::Point3D positionRave() const;
    rave::Vector3D axisRave() const;
    float radiusRave() const;

    // cms constructors
    Cylinder( const PositionType& pos, const RotationType& rot, Scalar radius) :
    	Surface( pos, rot), theRadius(radius) {}

    Cylinder( const PositionType& pos, const RotationType& rot, Scalar radius, MediumProperties* mp) :
         Surface( pos, rot, mp), theRadius(radius) {}

    Scalar radius() const {return theRadius;}
    using Surface::side;
    virtual Side side( const LocalPoint& p, Scalar toler) const;

    // tangent plane to surface from global point
    virtual ReferenceCountingPointer<TangentPlane> tangentPlane (const GlobalPoint&) const;
    // tangent plane to surface from local point
    virtual ReferenceCountingPointer<TangentPlane> tangentPlane (const LocalPoint&) const;

  private:
    rave::Point3D pos_;
    rave::Vector3D norm_;
    float radius_;

    // cms like
    Scalar theRadius;

};

} // namespace ravesurf

#endif


/**

  Cylinder( const PositionType& pos, const RotationType& rot, Scalar radius) :
    Surface( pos, rot), theRadius(radius) {}

  Cylinder( const PositionType& pos, const RotationType& rot, Scalar radius,
	 MediumProperties* mp) :
    Surface( pos, rot, mp), theRadius(radius) {}

// extension of Surface interface for cylinder

  Scalar radius() const {return theRadius;}

// implementation of Surface interface

  using Surface::side;
  virtual Side side( const LocalPoint& p, Scalar toler) const;

  /// tangent plane to surface from global point
  virtual ReferenceCountingPointer<TangentPlane> tangentPlane (const GlobalPoint&) const;
  /// tangent plane to surface from local point
  virtual ReferenceCountingPointer<TangentPlane> tangentPlane (const LocalPoint&) const;
 */
