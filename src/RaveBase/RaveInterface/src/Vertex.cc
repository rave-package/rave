#include "RaveBase/RaveInterface/rave/Vertex.h"
#include "RaveBase/RaveEngine/interface/RaveId.h"
#include <iostream>

using namespace rave;
using namespace std;

Vertex::Vertex( const Point3D & p, const Covariance3D & e,
      const vector < pair < float, Track > > & tracks, float ndf, float chi2,
      const vector < pair < float, Vertex > > & components ) :
  BasicVertex ( p, e, tracks, ndf, chi2 ),
  theComponents ( components )
{}

Vertex::Vertex( const Point3D & p, const Covariance3D & e,
      const vector < Track > & tracks, float ndf, float chi2,
      const vector < pair < float, Vertex > > & components ) :
  BasicVertex ( p, e, tracks, ndf, chi2 ),
  theComponents ( components )
{}

Vertex::Vertex( const Point3D & p, const Covariance3D & e,
      const vector < pair < float, Track > > & tracks,
      const vector < pair < float, Track > > & ftracks, float ndf, float chi2,
      const vector < pair < float, Vertex > > & components ) :
  BasicVertex ( p, e, tracks, ftracks, ndf, chi2 ),
  theComponents ( components )
{}

Vertex::Vertex( const Point3D & p, const Covariance3D & e,
      const vector < Track > & tracks, 
      const vector < Track > & ftracks, float ndf, float chi2,
      const vector < pair < float, Vertex > > & components ) :
  BasicVertex ( p, e, tracks, ftracks, ndf, chi2 ),
  theComponents ( components )
{}


void Vertex::addTrackToTrackCovariance(
    const rave::Track & i, const rave::Track & j,
    const rave::Covariance3D & cov ) 
{
  BasicVertex::addTrackToTrackCovariance ( i.id(), j.id(), cov );
}

void Vertex::addTrackToVertexCovariance(
    const rave::Track & i, const rave::Covariance33D & cov ) 
{
  BasicVertex::addTrackToVertexCovariance ( i.id(), cov ); // fixme
}

bool Vertex::operator< ( const Vertex & o ) const
{
    return ( id() < o.id() );
}

bool Vertex::operator== ( const Vertex & o ) const
{
  return ( id() == o.id() );
}

Vertex::Vertex () : BasicVertex()
{}

Vertex::Vertex ( const BasicVertex & o ) : BasicVertex ( o )
{}

std::vector < std::pair < float, Vertex > > Vertex::components() const
{
  return theComponents;
}
