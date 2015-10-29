#include "DataFormats/GeometrySurface/interface/Plane.h"
#include "DataFormats/GeometrySurface/interface/TangentPlane.h"
#include "rave/Plane.h"
#include <iostream>

namespace ravesurf {



Plane::Plane ( const rave::Point3D & pos, const rave::Point3D & normal )
  :
		  pos_ ( pos ),
		  norm_ ( normal ),
		  //post_ (forward_.convert(pos)),
		  Surface(RaveToCmsObjects().convert(pos), TkRotation<float>())
{

	// Surface( const PositionType& pos, const RotationType& rot) :
std::cout << "pos_  " << pos_.x() << " " << pos_.y() << " " << pos_.z() << std::endl;
std::cout << "norm_ " << norm_.x() << " "<< norm_.y() << " " << norm_.z() << std::endl;
//std::cout << "post_" << post_ << std::endl;
//std::cout << "rot_" << rot_ << std::endl;

};

Plane::Plane( const PositionType& pt, const RotationType& rot) :
    Surface( pt, rot)//,
	//pos_ (0.,0.,0.), //
	//norm_ (0.,0.,0.)
{
};

Plane::Plane( const PositionType& pt, const RotationType& rot, MediumProperties* mp) :
    Surface( pt, rot, mp)//,
	//pos_ (0.,0.,0.),
	//norm_ (0.,0.,0.)
{
};

rave::Point3D Plane::positionRave() const
{
  return pos_;
}

rave::Vector3D Plane::normalVectorRave() const
{
  return norm_;
}

ReferenceCountingPointer<TangentPlane>
Plane::tangentPlane (const GlobalPoint&) const
{
  return ReferenceCountingPointer<TangentPlane>(new TangentPlane(position(),
								 rotation(),
								 this));
}

ReferenceCountingPointer<TangentPlane>
Plane::tangentPlane (const LocalPoint&) const
{
  return ReferenceCountingPointer<TangentPlane>(new TangentPlane(position(),
								 rotation(),
								 this));
}

} // ravesurf
