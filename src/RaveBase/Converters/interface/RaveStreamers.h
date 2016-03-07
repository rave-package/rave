#ifndef _RaveStreamers_H_
#define _RaveStreamers_H_

#include <rave/Point3D.h>
#include <rave/Vector3D.h>


#include <rave/Covariance7D.h>
#include <rave/PerigeeParameters6D.h>
#include <rave/PerigeeCovariance6D.h>
#include <rave/KinematicParticle.h>
#include <rave/KinematicTree.h>
#include <rave/Vector6D.h>
#include <rave/Track.h>
#include <rave/Vertex.h>
#include <rave/Ellipsoid3D.h>
#include <rave/Covariance3D.h>
#include <rave/Covariance33D.h>
#include <rave/Covariance6D.h>

#include <ostream>

 std::ostream& operator<< (std::ostream& os, const rave::Point3D & );
 std::ostream& operator<< (std::ostream& os, const rave::Covariance3D & );
 std::ostream& operator<< (std::ostream& os, const rave::Covariance33D & );
 std::ostream& operator<< (std::ostream& os, const rave::Covariance6D & );
 std::ostream& operator<< (std::ostream& os, const rave::Ellipsoid3D & );
 std::ostream& operator<< (std::ostream& os, const rave::Vector6D & );
 std::ostream& operator<< (std::ostream& os, const rave::Track & );
 std::ostream& operator<< (std::ostream& os, const rave::Vertex & );

 #ifdef WITH_KINEMATICS
#include <rave/Vector4D.h>
#include <rave/Vector7D.h>
 std::ostream& operator<< (std::ostream& os, const rave::Vector7D & );
 std::ostream& operator<< (std::ostream& os, const rave::Covariance7D & );
 std::ostream& operator<< (std::ostream& os, const rave::Vector4D & );
 std::ostream& operator<< (std::ostream& os, const rave::KinematicParticle & );
 std::ostream& operator<< (std::ostream& os, const rave::KinematicVertex & );
 std::ostream& operator<< (std::ostream& os, const rave::KinematicTree & );
 std::ostream& operator<< (std::ostream& os, const rave::PerigeeParameters6D & p );
 std::ostream& operator<< (std::ostream& os, const rave::PerigeeCovariance6D & p );
 #endif

#endif
