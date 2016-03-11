//
//  Author M. Gelb KIT (2015)
//
//  Boost-based unit tests, see www.boost.org for details
#include <boost/test/unit_test.hpp>
#include <cstdio>
#include <iostream>

#include <rave/Version.h>
#include <rave/Plane.h> 
#include <rave/Point3D.h>
#include <rave/Vector3D.h> 


BOOST_AUTO_TEST_CASE(RavePlane)
{
   std::cout << "[ravesurftest] ravesurf::Plane test"<<std::endl;

	const rave::Point3D pos(0., 0., 0.);
	const rave::Vector3D normal(1., 0., 0.);
	ravesurf::Plane Plane(pos, normal); 

	
	std::cout << "...Checking initialization" << std::endl;
	BOOST_CHECK(Plane.positionRave().x() == pos.x());
	BOOST_CHECK(Plane.positionRave().y() == pos.y());
	BOOST_CHECK(Plane.positionRave().z() == pos.z());
	BOOST_CHECK(Plane.normalVectorRave().x() == normal.x());
	BOOST_CHECK(Plane.normalVectorRave().y() == normal.y());
	BOOST_CHECK(Plane.normalVectorRave().z() == normal.z());


}
