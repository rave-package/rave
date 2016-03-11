#ifndef _RavePlane_H_
#define _RavePlane_H_

#include <rave/Point3D.h>
#include <rave/Vector3D.h>
#include "RaveBase/Converters/interface/RaveToCmsObjects.h"
#include "DataFormats/GeometrySurface/interface/Surface.h"
//#include "DataFormats/GeometrySurface/interface/GloballyPositioned.h"
//#include "DataFormats/GeometrySurface/interface/MediumProperties.h"



namespace ravesurf {

/** 
 * @brief a class implementing a physical "detector" plane
 * @ingroup ravesurf
 *
 */

class Plane: public Surface
{
  public:
    Plane ( const rave::Point3D & pos, const rave::Vector3D & normal );

    rave::Point3D positionRave() const;
    rave::Vector3D normalVectorRave() const;

    Plane( const PositionType& pos, const RotationType& rot);
    Plane( const PositionType& pos, const RotationType& rot, MediumProperties* mp);

    ~Plane(){};

    // new cms functions

    // extension of Surface interface for planes

      GlobalVector normalVector() const {
    	std::cout << "rotation: " << rotation() << std::endl;
    	return GlobalVector( rotation().zx(), rotation().zy(), rotation().zz());
      }
      /** Fast access to distance from plane for a point.
       */
      float localZ (const GlobalPoint& gp) const {
        return normalVector().dot(gp - position());
      }
      /** Fast access to component perpendicular to plane for a vector.
       */
      float localZ (const GlobalVector& gv) const {
        return normalVector().dot(gv);
      }



    SurfaceOrientation::Side side( const LocalPoint& p, Scalar toler) const {
      return (std::abs(p.z())<toler) ? SurfaceOrientation::onSurface :
  	(p.z()>0 ? SurfaceOrientation::positiveSide : SurfaceOrientation::negativeSide);
    }

    SurfaceOrientation::Side side( const GlobalPoint& p, Scalar toler=0) const {
      Scalar lz = localZ(p);
      return (std::abs(lz)<toler ? SurfaceOrientation::onSurface :
  	    (lz>0 ? SurfaceOrientation::positiveSide : SurfaceOrientation::negativeSide));
    }


    /// tangent plane to surface from global point
    ReferenceCountingPointer<TangentPlane> tangentPlane (const GlobalPoint&) const;

    /// tangent plane to surface from local point
    ReferenceCountingPointer<TangentPlane> tangentPlane (const LocalPoint&) const;

  private:
    //const PositionType post_;
    rave::Point3D pos_;
    rave::Vector3D norm_;

};

} // namespace ravesurf



#endif
