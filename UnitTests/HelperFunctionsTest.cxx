//
//  Author M. Gelb KIT (2015)
//
//  Boost-based unit tests, see www.boost.org for details
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <cstdio>
#include <iostream>

#include <rave/Version.h>
#include <rave/Vector6D.h>
#include <rave/Covariance6D.h>
#include <rave/Charge.h>

#include "RaveBase/Converters/interface/RaveToCmsObjects.h"
#include "RaveBase/Converters/interface/CmsToRaveObjects.h"
#include "RaveBase/Converters/interface/HelperFunctions.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/GeometryVector/interface/GlobalVector.h"



BOOST_AUTO_TEST_CASE(HelperFunctionsTest)
{
   std::cout << "[helperfunctionstest] Testing HelperFunctions::convertFloatToCartesianTrajcetoryError"<<std::endl;

   RaveToCmsObjects forward;
   CmsToRaveObjects backward;
   HelperFunctions helper;

   rave::Covariance6D cov1 (
		   1.0, 2.0, 3.0,
           4.0, 5.0, 6.0,
           7.0,  8.0, 9.0,
           10.0,  11.0, 12.0,
           13.0,  14.0, 15.0,
           16.0,  17.0, 18.0,
           19.0,  20.0, 21.0);

   CartesianTrajectoryError cte1 = forward.convert(cov1);



   CartesianTrajectoryError cte2 = helper.convertFloatToCartesianTrajcetoryError(
			1.0, 2.0, 3.0,
            4.0, 5.0, 6.0,
            7.0,  8.0, 9.0,
            10.0,  11.0, 12.0,
            13.0,  14.0, 15.0,
            16.0,  17.0, 18.0,
            19.0,  20.0, 21.0);

   rave::Covariance6D cov2 = backward.convert ( cte2 );

   BOOST_CHECK( cte1.dxx() == cte2.dxx() );
   std::cout << "FIRST: " << cte1.dxx() << " SECOND: " << cte2.dxx() << std::endl;
   BOOST_CHECK( cte1.dxy() == cte2.dxy() );
   BOOST_CHECK( cte1.dxz() == cte2.dxz() );
   BOOST_CHECK( cte1.dxpx() == cte2.dxpx() );
   BOOST_CHECK( cte1.dxpy() == cte2.dxpy() );
   BOOST_CHECK( cte1.dxpz() == cte2.dxpz() );
   BOOST_CHECK( cte1.dyy() == cte2.dyy() );
   BOOST_CHECK( cte1.dyz() == cte2.dyz() );
   BOOST_CHECK( cte1.dypx() == cte2.dypx() );
   BOOST_CHECK( cte1.dypy() == cte2.dypy() );
   BOOST_CHECK( cte1.dypz() == cte2.dypz() );
   BOOST_CHECK( cte1.dzz() == cte2.dzz() );
   BOOST_CHECK( cte1.dzpx() == cte2.dzpx() );
   BOOST_CHECK( cte1.dzpy() == cte2.dzpy() );
   BOOST_CHECK( cte1.dzpz() == cte2.dzpz() );
   BOOST_CHECK( cte1.dpxpx() == cte2.dpxpx() );
   BOOST_CHECK( cte1.dpxpy() == cte2.dpxpy() );
   BOOST_CHECK( cte1.dpxpz() == cte2.dpxpz() );
   BOOST_CHECK( cte1.dpypy() == cte2.dpypy() );
   BOOST_CHECK( cte1.dpypz() == cte2.dpypz() );
   BOOST_CHECK( cte1.dpzpz() == cte2.dpzpz() );


   BOOST_CHECK( cov1.dxx() == cov2.dxx() );
   BOOST_CHECK( cov1.dxy() == cov2.dxy() );
   BOOST_CHECK( cov1.dxz() == cov2.dxz() );
   BOOST_CHECK( cov1.dxpx() == cov2.dxpx() );
   BOOST_CHECK( cov1.dxpy() == cov2.dxpy() );
   BOOST_CHECK( cov1.dxpz() == cov2.dxpz() );
   BOOST_CHECK( cov1.dyy() == cov2.dyy() );
   BOOST_CHECK( cov1.dyz() == cov2.dyz() );
   BOOST_CHECK( cov1.dypx() == cov2.dypx() );
   BOOST_CHECK( cov1.dypy() == cov2.dypy() );
   BOOST_CHECK( cov1.dypz() == cov2.dypz() );
   BOOST_CHECK( cov1.dzz() == cov2.dzz() );
   BOOST_CHECK( cov1.dzpx() == cov2.dzpx() );
   BOOST_CHECK( cov1.dzpy() == cov2.dzpy() );
   BOOST_CHECK( cov1.dzpz() == cov2.dzpz() );
   BOOST_CHECK( cov1.dpxpx() == cov2.dpxpx() );
   BOOST_CHECK( cov1.dpxpy() == cov2.dpxpy() );
   BOOST_CHECK( cov1.dpxpz() == cov2.dpxpz() );
   BOOST_CHECK( cov1.dpypy() == cov2.dpypy() );
   BOOST_CHECK( cov1.dpypz() == cov2.dpypz() );
   BOOST_CHECK( cov1.dpzpz() == cov2.dpzpz() );



 }

