#include "TrackingTools/TrajectoryParametrization/interface/CartesianTrajectoryError.h"
#include "TrackingTools/TrajectoryParametrization/interface/GlobalTrajectoryParameters.h"
#include "DataFormats/TrajectoryState/interface/TrackCharge.h"

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

	GlobalTrajectoryParameters   convertToGlobalTrajecetoryState( float x, float y, float z,
								                                  float px, float py, float pz,
																  TrackCharge charge);


};


#endif /* SRC_RAVEBASE_CONVERTERS_INTERFACE_HELPERFUNCTIONS_H_ */
