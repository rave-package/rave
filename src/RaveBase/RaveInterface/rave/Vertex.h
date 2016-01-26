#ifndef _RaveVertex_H_
#define _RaveVertex_H_

#include <rave/Track.h>
#include <rave/Point3D.h>
#include <rave/Covariance3D.h>
#include <rave/Covariance33D.h>
#include <rave/BasicVertex.h>
#include <utility>
#include <vector>

namespace rave 
{

class Vertex : public rave::BasicVertex
{
    //typedef rave::BasicVertex::Proxy Base;
  /**
   *  The output of the rave library: a reconstructed vertex.
   *  A position in 3d space, plus its error.
   *  Along with the (refitted!!) tracks and
   *  the association probabilities of tracks belonging to this vertex.
   *  also a (fractional) number of degrees of freedom (ndf)
   *  and chi-squared.
   */
  public:
    Vertex(); //< default constructor, creating invalid vertex. 
    Vertex( const rave::BasicVertex & );
    
    void addTrackToVertexCovariance ( const rave::Track & t,
        const rave::Covariance33D & cov );

    void addTrackToTrackCovariance ( const rave::Track & t1,
        const rave::Track & t2, const rave::Covariance3D & cov );

    bool operator< ( const rave::Vertex & ) const;
    bool operator== ( const rave::Vertex & ) const;

    /**
     *  The vertex components - only used in the Gaussian
     *  algorithm.
     */
    std::vector < std::pair < float, rave::Vertex > > components() const;

    Vertex( const rave::Point3D &, const rave::Covariance3D &,
            const std::vector < std::pair < float, rave::Track > > & tracks, float ndf, float chi2,
            const std::vector < std::pair < float, rave::Vertex > > & components );
    Vertex( const rave::Point3D &, const rave::Covariance3D &,
            const std::vector < rave::Track > & tracks, float ndf, float chi2,
            const std::vector < std::pair < float, rave::Vertex > > & components );
    Vertex( const rave::Point3D &, const rave::Covariance3D &,
            const std::vector < std::pair < float, rave::Track > > & tracks, 
            const std::vector < std::pair < float, rave::Track > > & smoothedtracks, float ndf, float chi2,
            const std::vector < std::pair < float, rave::Vertex > > & components );
    Vertex( const rave::Point3D &, const rave::Covariance3D &,
            const std::vector < rave::Track > & tracks,
            const std::vector < rave::Track > & smoothedtracks, float ndf, float chi2,
            const std::vector < std::pair < float, rave::Vertex > > & components );
  private:
    std::vector < std::pair < float, rave::Vertex > > theComponents;

};

}

#endif
