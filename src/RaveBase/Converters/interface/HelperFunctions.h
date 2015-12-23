#include "TrackingTools/TrajectoryParametrization/interface/CartesianTrajectoryError.h"
/*
 * HelperFunctions.h
 *
 *  Created on: Dec 2015
 *      Author: Moritz Gelb
 */

#ifndef SRC_RAVEBASE_CONVERTERS_INTERFACE_HELPERFUNCTIONS_H_
#define SRC_RAVEBASE_CONVERTERS_INTERFACE_HELPERFUNCTIONS_H_



class HelperFunctions
{
public:

	/*
	 * helper function to build CartesianTrajectoryError matrix with only 21 entries.
	 */
	CartesianTrajectoryError   convertFloatToCartesianTrajcetoryError( float dxx, float dxy, float dxz,
            						                                   float dyy, float dyz, float dzz,
                                                                       float dxpx, float dxpy, float dxpz,
                                                                       float dypx, float dypy, float dypz,
                                                                       float dzpx, float dzpy, float dzpz,
                                                                       float dpxpx, float dpxpy, float dpxpz,
                                                                       float dpypy, float dpypz, float dpzpz );
};


#endif /* SRC_RAVEBASE_CONVERTERS_INTERFACE_HELPERFUNCTIONS_H_ */
