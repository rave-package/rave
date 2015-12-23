#include "RaveBase/Converters/interface/HelperFunctions.h"
#include "DataFormats/CLHEP/interface/Migration.h"

/*
 * HelperFunctions.cc
 *
 *  Created on: Dec 2015
 *      Author: Moritz Gelb
 */


CartesianTrajectoryError   HelperFunctions::convertFloatToCartesianTrajcetoryError ( float dxx, float dxy, float dxz,
           						                                    float dyy, float dyz, float dzz,
                                                                    float dxpx, float dxpy, float dxpz,
                                                                    float dypx, float dypy, float dypz,
                                                                    float dzpx, float dzpy, float dzpz,
                                                                    float dpxpx, float dpxpy, float dpxpz,
                                                                    float dpypy, float dpypz, float dpzpz )
	{
	  AlgebraicSymMatrix66 s;
	  s(0,0) = dxx;
	  s(0,1) = dxy;
	  s(0,2) = dxz;
	  s(0,3) = dxpx;
	  s(0,4) = dxpy;
	  s(0,5) = dxpz;
	  s(1,1) = dyy;
	  s(1,2) = dyz;
	  s(1,3) = dypx;
	  s(1,4) = dypy;
	  s(1,5) = dypz;
	  s(2,2) = dzz;
	  s(2,3) = dzpx;
	  s(2,4) = dzpy;
	  s(2,5) = dzpz;
	  s(3,3) = dpxpx;
	  s(3,4) = dpxpy;
	  s(3,5) = dpxpz;
	  s(4,4) = dpypy;
	  s(4,5) = dpypz;
	  s(5,5) = dpzpz;
	  return CartesianTrajectoryError ( s );
	}





