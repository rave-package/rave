#include "RaveBase/RaveInterface/rave/ConstantMagneticField.h"
#include <iostream>

rave::MagneticField * rave::ConstantMagneticField::copy() const
{
  return new rave::ConstantMagneticField ( *this );
}

GlobalVector rave::ConstantMagneticField::inTesla ( const GlobalPoint & ) const
{
  // std::cout << "[rave::ConstantMagneticField] ::inTesla called." << std::endl;
  return GlobalVector ( x_, y_, z_ );
}

rave::ConstantMagneticField::ConstantMagneticField() : x_(0.), y_(0.), z_(0.) {}
rave::ConstantMagneticField::ConstantMagneticField( float x, float y, float z ) : 
  x_(x), y_(y), z_(z) {}
rave::ConstantMagneticField::ConstantMagneticField( float z ) : 
  x_(0.), y_(0.), z_(z) {}
