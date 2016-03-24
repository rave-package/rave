#include "RaveTools/Converters/interface/MagneticFieldSingleton.h"
#include "RaveBase/RaveInterface/rave/Vector3D.h"

#include <boost/assert.hpp>

using namespace std;

GlobalVector rave::MagneticFieldSingleton::inTesla ( const GlobalPoint & gp ) const
{
  /*
  if ( !theField )
  {
    cout << "[MagneticFieldSingleton] Arrg! No field registered!" << endl;
    exit(0);
  }
  */

  BOOST_ASSERT( hasField() );

  /*
  rave::Vector3D rv = theField->inTesla( rave::Point3D( gp.x(), gp.y(), gp.z() ) );
  return GlobalVector( rv.x(), rv.y(), rv.z() );
  */
  return theField->inTesla ( gp );
}

void rave::MagneticFieldSingleton::release() {
	if (theField){
		delete theField;
		theField = NULL;
	}
}

bool rave::MagneticFieldSingleton::hasField() const
{
  return ( theField != 0 );
}

rave::MagneticFieldSingleton::MagneticFieldSingleton() : theField(0)
{}

rave::MagneticFieldSingleton::MagneticFieldSingleton( const MagneticFieldSingleton & o )
{
  cout << "[MagneticFieldSingleton] Arrgh! Fatal!" << endl;
}

rave::MagneticFieldSingleton * rave::MagneticFieldSingleton::Instance()
{
  static MagneticFieldSingleton singleton;
  return &singleton;
}

const rave::MagneticField * rave::MagneticFieldSingleton::field() const
{
  return theField;
}

void rave::MagneticFieldSingleton::registry ( MagneticField * field )
{
  /*
  cout << "[MagneticFieldSingleton] registering field Bz="  << flush;
  cout << field->inTesla ( GlobalPoint ( 0.,0.,0. ) ).z() << flush;
  cout << " field=" << (void *) field << ", singleton=" << (void *) this << endl;
  */
//	std::cout << "&&& rave::MagneticFieldSingleton::::registry inputMagnetic field" << field << std::endl;
//	std::cout << "&&& rave::MagneticFieldSingleton::::registry before setting theField" << theField << std::endl;

	release();

//	std::cout << "&&& rave::MagneticFieldSingleton::::registry after setting NULLPTR" << theField << std::endl;

	theField = field;

//	std::cout << "&&& rave::MagneticFieldSingleton::::registry after setting theField" << theField << std::endl;
}

// dummy function
rave::MagneticField * rave::MagneticFieldSingleton::copy() const
{
	return nullptr;
}
