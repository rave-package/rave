//
//  Author M. Gelb KIT (2015)
//
//  Boost-based unit tests, see www.boost.org for details
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ravesurftest

#include <boost/test/unit_test.hpp>
#include <cstdio>
#include <iostream>

#include <rave/Version.h>
#include <rave/Cylinder.h> 
#include <rave/Point3D.h>
#include <rave/Vector3D.h> 

#include "RaveBase/Converters/interface/RaveToCmsObjects.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/GeometrySurface/interface/TkRotation.h"



BOOST_AUTO_TEST_CASE(RaveCylinder)
{
   std::cout << "[ravesurftest] ravesurf::Cylinder test"<<std::endl;

	const rave::Point3D pos(0., 0., 0.);
	const rave::Point3D axis(1., 0., 0.);
	float radius(2.0);
	ravesurf::Cylinder Cyl(pos, axis, radius); 

	
	std::cout << "...Checking initialization" << std::endl;
	BOOST_CHECK(Cyl.positionRave() == pos);
	BOOST_CHECK(Cyl.axisRave() == axis);

	std::cout << "Radius is: " << Cyl.radiusRave() << std::endl;

	// in ravesurf constructor no initilization of radius_???
	// should be fixed!
	BOOST_CHECK(Cyl.radiusRave() == radius);

	RaveToCmsObjects forward;
	GlobalPoint pt = forward.convert ( Cyl.positionRave() );
	TkRotation<float> rot;
	::Cylinder cmsCyl ( pt, rot, Cyl.radiusRave() );
        std::cout << "cmsCyl radius " << cmsCyl.radius() << std::endl;

	
	// now testing the conversion 
	// it has new functions which we want to check 
	BOOST_CHECK(Cyl.radius() == radius);
	// is there more ??


// required test cases: Do conversion before conversion 
// should be the same like after
}
