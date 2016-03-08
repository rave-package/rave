#ifndef _TRACKER_CARTESIANTRAJECTORYERROR_H_
#define _TRACKER_CARTESIANTRAJECTORYERROR_H_

#include "DataFormats/CLHEP/interface/AlgebraicObjects.h"
#include "DataFormats/GeometryCommonDetAlgo/interface/GlobalError.h"

/** Class containing (6x6) error matrix of a track in the global, Cartesian frame.
 *  This error matrix should be used with care and in particular not as an
 *  intermediate frame when transforming between different, 5-dimensional
 *  track parameter frames. The order of the quantities inside the error matrix
 *  is the same as for the corresponding parameter vector provided by the
 *  GlobalTrajectoryParameters class.
 */

class CartesianTrajectoryError {
public:
// construct
  CartesianTrajectoryError() {}

  CartesianTrajectoryError ( double dxx, double dxy, double dxz,
             				double dyy, double dyz, double dzz,
                          double dxpx, double dxpy, double dxpz,
                          double dypx, double dypy, double dypz,
                          double dzpx, double dzpy, double dzpz,
                          double dpxpx, double dpxpy, double dpxpz,
                          double dpypy, double dpypz, double dpzpz )
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
  	theCovarianceMatrix = s; }

  double dxx() const{
	  return theCovarianceMatrix(0,0);
  }

  double dxy() const{
  	  return theCovarianceMatrix(0,1);
    }

  double dxz() const{
  	  return theCovarianceMatrix(0,2);
    }

  double dxpx() const{
  	  return theCovarianceMatrix(0,3);
    }

  double dxpy() const{
  	  return theCovarianceMatrix(0,4);
    }

  double dxpz() const{
  	  return theCovarianceMatrix(0,5);
    }

  double dyy() const{
  	  return theCovarianceMatrix(1,1);
    }

  double dyz() const{
  	  return theCovarianceMatrix(1,2);
    }

  double dypx() const{
  	  return theCovarianceMatrix(1,3);
    }

  double dypy() const{
      return theCovarianceMatrix(1,4);
    }

  double dypz() const{
      return theCovarianceMatrix(1,5);
    }

  double dzz() const{
      return theCovarianceMatrix(2,2);
    }

  double dzpx() const{
      return theCovarianceMatrix(2,3);
    }

  double dzpy() const{
      return theCovarianceMatrix(2,4);
    }

  double dzpz() const{
      return theCovarianceMatrix(2,5);
    }

   double dpxpx() const{
       return theCovarianceMatrix(3,3);
      }

   double dpxpy() const{
       return theCovarianceMatrix(3,4);
      }

   double dpxpz() const{
        return theCovarianceMatrix(3,5);
      }

   double dpypy() const{
        return theCovarianceMatrix(4,4);
      }

  double dpypz() const{
         return theCovarianceMatrix(4,5);
     	      }

  double dpzpz() const{
  	       return theCovarianceMatrix(5,5);
     	      }



  /** Constructing class from error matrix.
   */

  CartesianTrajectoryError(const AlgebraicSymMatrix66& aCovarianceMatrix) :
    theCovarianceMatrix(aCovarianceMatrix) { }

  /** Constructing class from error matrix.
   */

  CartesianTrajectoryError(const AlgebraicSymMatrix& aCovarianceMatrix) :
    theCovarianceMatrix(asSMatrix<6>(aCovarianceMatrix)) {}
// access

  /** Returning error matrix.
   */
  const AlgebraicSymMatrix matrix_old() const {
    return asHepMatrix(theCovarianceMatrix);
  }


  const AlgebraicSymMatrix66 &matrix() const {
    return theCovarianceMatrix;
  }

  /** Enables the multiplication of the error matrix with a scalar "factor".
   */

  void operator *= (double factor) {
    theCovarianceMatrix *= factor;
  }

  /// Position error submatrix

  /** Returning (3x3) submatrix of error matrix containing information about the errors
   *  and correlations between the different position coordinates. 
   */

  GlobalError position() const;

private:
  AlgebraicSymMatrix66 theCovarianceMatrix;
};

#endif
