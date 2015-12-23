//
//  Author M. Gelb KIT (2015)
//
//  Boost-based unit tests, see www.boost.org for details
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <cstdio>
#include <iostream>

#include <rave/Version.h>
#include <rave/Covariance6D.h>

#include "RaveBase/Converters/interface/RaveToCmsObjects.h"
#include "RaveBase/Converters/interface/CmsToRaveObjects.h"
#include "RaveBase/Converters/interface/HelperFunctions.h"



BOOST_AUTO_TEST_CASE(HelperFunctionsTest)
{
   std::cout << "[helperfunctionstest] HelperFunctions::convertFloatToCartesianTrajcetoryError test"<<std::endl;

   RaveToCmsObjects forward;
   CmsToRaveObjects backward;
   HelperFunctions helper;

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

   CartesianTrajectoryError cte1 = forward.convert(cov1);



   CartesianTrajectoryError cte2 = helper.convertFloatToCartesianTrajcetoryError(
			1.5e-7,    3.6e-7,    4.0e-14,
                      8.5e-7,    9.6e-14,
                                  1.7e-6,
                                       -1.4e-16,  -3.4e-16,   1.8e-24,
                                       -3.3e-16,  -8.1e-16,   4.3e-24,
                                       -3.9e-9,   -9.4e-9,    5.0e-17,
                                        4.9e-3,   -2.0e-3,   -4.4e-3,
                                                   9.2e-4,    1.8e-3,
                                                              4.1e-3 );

   rave::Covariance6D cov2 = backward.convert ( cte2 );

   BOOST_CHECK( cte1.matrix() == cte2.matrix() );
   BOOST_CHECK( cov1 == cov2 );
 }



