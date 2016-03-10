#include "RaveBase/RaveInterface/rave/Track.h"
#include "RaveBase/RaveEngine/interface/RaveId.h"


using namespace rave;
using namespace std;


Track::Track( int id, const GlobalTrajectoryParameters & gtp, const CartesianTrajectoryError & cte,
		      float chi2, float ndof, void * originaltrack, std::string tag):
				FreeTrajectoryState(gtp, cte),
				theChi2(chi2),
				theNdof(ndof),
				thePointer(originaltrack),
				theTag(tag),
				theIsValid(true)
{theTrackId=id;}


Track::Track( const GlobalTrajectoryParameters & gtp, const CartesianTrajectoryError & cte,
		      float chi2, float ndof, void * originaltrack, std::string tag):
				FreeTrajectoryState(gtp, cte),
				theChi2(chi2),
				theNdof(ndof),
				thePointer(originaltrack),
				theTag(tag),
				theIsValid(true)
{theTrackId=RaveId::uniqueId();}


Track::Track( int id, const GlobalTrajectoryParameters & gtp, const CurvilinearTrajectoryError & cte,
		      float chi2, float ndof, void * originaltrack, std::string tag ):
				FreeTrajectoryState(gtp, cte),
				theChi2(chi2),
				theNdof(ndof),
				thePointer(originaltrack),
				theTag(tag),
				theIsValid(true)
{theTrackId=id;}


Track::Track( int id, const GlobalTrajectoryParameters & gtp,
		      float chi2, float ndof, int originaltrack,  std::string tag ):
				FreeTrajectoryState(gtp),
				theChi2(chi2),
				theNdof(ndof),
				thePointer(&originaltrack),
				theTag(tag),
				theIsValid(true)
{theTrackId=id;}


Track::Track ( const vector < pair < float, Track > > & components ) :
			  theComponents ( components ),
              FreeTrajectoryState(),
              theChi2(-1),
              theNdof(-1),
              thePointer(0),
              theIsValid(true)
{theTrackId=RaveId::uniqueId();}


Track::Track ( int id, const vector < pair < float, Track > > & components ) :
		      theComponents ( components ),
			  FreeTrajectoryState(),
			  theChi2(-1),
			  theNdof(-1),
			  thePointer(0),
			  theIsValid(true)
{theTrackId=id;}



Track::Track():
				FreeTrajectoryState(),
				theChi2(-1),
				theNdof(-1),
				thePointer(0),
				theIsValid(false)
{theTrackId=-1;}


string Track::tag() const
{
  return theTag;
}

int Track::id() const
{
  return theTrackId;
}

void * Track::originalObject() const
{
	return thePointer;
}

const rave::MagneticField * Track::getMagneticField() const
{
	return & theGlobalParameters.magneticField();
}

const ::GlobalTrajectoryParameters & Track::state() const
{
	return theGlobalParameters;
}


const CartesianTrajectoryError & Track::CartesianError() const
{
    return theCartesianError;
}

const CartesianTrajectoryError & Track::error() const
{
    return theCartesianError;
}

const CurvilinearTrajectoryError & Track::CurvilinearError() const
{
    return theCurvilinearError;
}


bool Track::isValid() const
{
  return theIsValid;
}

vector < pair < float, Track > > Track::components() const
{
  return theComponents;
}

void Track::setComponents ( const vector < pair < float, Track > > & components )
{
  theComponents=components;
}


bool Track::operator< ( const Track & o ) const
{
    return ( id() < o.id() );
}


bool Track::operator== ( const Track & o ) const
{
  return ( id() == o.id() );
}


float Track::chi2() const
{
  return theChi2;
}


float Track::ndof() const
{
  return theNdof;
}

Track collapse ( const vector < pair < float, Track > > & orig )
{
  #ifdef HAS_GSF // not working
  if ( orig.size()==0 ) return Track();
  //RaveToCmsObjects converter;
  GlobalPoint pos = orig[0].second.state().position() ;
  GlobalVector mom = orig[0].second.state().momentum(); //toVector ?
  const BoundPlane *bp_mom = PerpendicularBoundPlaneBuilder()( pos, mom );

  vector < TrajectoryStateOnSurface > comps;
  MultiTrajectoryStateAssembler assembler;
  for ( vector< pair < float, BasicTrack > >::const_iterator i=orig.begin(); i!=orig.end() ; ++i )
  {
    TrajectoryStateOnSurface tsos_mom(  i->second  , *bp_mom  );
    // comps.push_back (  TrajectoryStateOnSurface ( fts, *bp_mom, SurfaceSideDefinition::afterSurface, i->first ) );
    // assembler.addState (  TrajectoryStateOnSurface ( fts, *bp_mom, SurfaceSideDefinition::afterSurface, i->first ) );
    // FIXME the weight is not be supplied in the interface!!!!!
    assembler.addState (  TrajectoryStateOnSurface (  i->second, *bp_mom, SurfaceSideDefinition::afterSurface ) );
  }
  // MultiTrajectoryStateCombiner combiner;
  // TrajectoryStateOnSurface collapsed = combiner.combine ( comps );
  TrajectoryStateOnSurface collapsed = assembler.combinedState();
  /*
  cout << "[BasicTrack]      collapsed is: " << collapsed.globalPosition() << ", " << collapsed.globalMomentum() << endl;
  cout << "                         error: " << collapsed.cartesianError().matrix() << endl;
   */
  CmsToRaveObjects backconversion;
  BasicTrack ret = backconversion.toBasicTrack ( collapsed ); // should be a Track
  ret.setComponents ( orig );
  return ret;
	#else
  return Track();
  #endif
}

