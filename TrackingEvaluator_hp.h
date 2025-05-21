#ifndef G4EVAL_TRACKINGEVALUATOR_HP_H
#define G4EVAL_TRACKINGEVALUATOR_HP_H

#include <TObject.h>

#include <array>
#include <map>
#include <set>
#include <string>
#include <vector>

class TrackingEvaluator_hp
{

  public:

  //! constructor
  TrackingEvaluator_hp() = default;

  // event information
  class EventStruct
  {

    public:
    using List = std::vector<EventStruct>;
    static constexpr size_t max_layer = 57;

    // constructor
    EventStruct()
    {
      for( size_t i = 0; i < max_layer; ++i )
      {
        _nhits[i] = 0;
        _nhits_raw[i] = 0;
        _nclusters[i] = 0;

      }
    }

    //! number of hits per layer / event
    /* for TPC hits, the charge is compared to threshold */
    unsigned int _nhits[max_layer];

    //! number of hits per layer / event
    unsigned int _nhits_raw[max_layer];

    //! number of clusters per layer / event
    unsigned int _nclusters[max_layer];

    //! number of micromegas raw hits
    unsigned int _nrawhits_micromegas = 0;

    //! number of clusters in the mvtx
    unsigned int _nclusters_mvtx = 0;

    //! number of clusters in the intt
    unsigned int _nclusters_intt = 0;

    //! number of clusters in the TPC
    unsigned int _nclusters_tpc = 0;

    //! number of clusters in the Micromegas
    unsigned int _nclusters_micromegas = 0;

    //! number of g4hits in the mvtx
    unsigned int _ng4hits_mvtx = 0;

    //! number of g4hits in the intt
    unsigned int _ng4hits_intt = 0;

    //! number of g4hits in the TPC
    unsigned int _ng4hits_tpc = 0;

    //! number of g4hits in the Micromegas
    unsigned int _ng4hits_micromegas = 0;

    //! number of central membrane clusters
    unsigned int _ncmclusters = 0;

    //! gtm bco (real data only)
    uint64_t _gtm_bco = 0;

  };

  // cluster information to be stored in tree
  class ClusterStruct
  {
    public:

    using List = std::vector<ClusterStruct>;

    //! cluster layer
    unsigned int _layer = 0;

    //! number of hits belonging to the cluster
    unsigned int _size = 0;

    //! number of g4hits associated to this cluster
    unsigned int _truth_size = 0;

    //! number of particles associated to this cluster
    unsigned int _ncontributors = 0;

    //! number of hits along phi and along z
    unsigned int _phi_size = 0;
    unsigned int _z_size = 0;

    //!@name cluster position
    //@{
    float _x = 0;
    float _y = 0;
    float _z = 0;
    float _r = 0;
    float _phi = 0;
    float _phi_error = 0;
    float _z_error = 0;
    //@}

    //!@name track position at cluster
    //@{
    float _trk_x = 0;
    float _trk_y = 0;
    float _trk_z = 0;
    float _trk_r = 0;
    float _trk_phi = 0;

    //! track errors
    float _trk_phi_error = 0;
    float _trk_z_error = 0;

    // extrapolation distance
    float _trk_dr = 0;

    //! track inclination at cluster in r,phi plane
    float _trk_alpha = 0;

    //! track inclination at cluster in r,z plane
    float _trk_beta = 0;

    //@}

    //!@name truth position
    //@{
    float _truth_x = 0;
    float _truth_y = 0;
    float _truth_z = 0;
    float _truth_r = 0;
    float _truth_phi = 0;

    //! track inclination at cluster in r,phi plane
    float _truth_alpha = 0;

    //! track inclination at cluster in r,z plane
    float _truth_beta = 0;
    //@}

    //!@name charges
    //@{

    //* maximum charge on strip
    float _energy_max = 0;

    //* sum of strip charges
    float _energy_sum = 0;

    //@}

    //!@name track local momentum information
    //!TODO: in principle trk_alpha and trk_beta can be calculated from those. There should be no need to store them
    //@{
    float _trk_px = 0;
    float _trk_py = 0;
    float _trk_pz = 0;
    //@}

    //!@name truth local momentum information
    //!TODO: in principle truth_alpha and truth_beta can be calculated from those. There should be no need to store them
    //@{
    float _truth_px = 0;
    float _truth_py = 0;
    float _truth_pz = 0;
    //@}

    //! micromegas tile id
    int _tileid = 0;

  };

  // tower information
  class TowerStruct
  {
    public:

    using List = std::vector<TowerStruct>;

    int _ieta = 0;
    int _iphi = 0;
    float _e = 0;
  };

  // cluster information to be stored in tree
  class CaloClusterStruct
  {
    public:

    using List = std::vector<CaloClusterStruct>;

    //! cluster layer
    int _layer = 0;

    //! number of hits belonging to the cluster
    unsigned int _size = 0;

    //!@name cluster position and energy
    //@{
    float _x = 0;
    float _y = 0;
    float _z = 0;
    float _r = 0;
    float _phi = 0;
    float _e = 0;
    float _chisquare = 0;
    //@}

    //!@name matching track position
    //@{
    float _trk_x = 0;
    float _trk_y = 0;
    float _trk_z = 0;
    float _trk_r = 0;
    float _trk_phi = 0;
    float _trk_dr = 0;
    //@}

    //! towers
    TowerStruct::List _towers;
  };

  // cluster information to be stored in tree
  class CMClusterStruct
  {
    public:

    using List = std::vector<CMClusterStruct>;

    //! number of participating clusters
    unsigned int _nclusters = 0;

    //!@name cluster position
    //@{
    float _x = 0;
    float _y = 0;
    float _z = 0;
    float _r = 0;
    float _phi = 0;
    //@}
  };

  // track information to be stored in tree
  class TrackStruct
  {
    public:

    // constructor
    explicit TrackStruct()
    {
      // allocate enough size for the clusters
      static constexpr int max_layers = 60;
      _clusters.reserve( max_layers );
    }

    using List = std::vector<TrackStruct>;

    int _charge = 0;
    unsigned int _nclusters = 0;

    /// crossing
    short int _crossing = 0;

    /// mask of layers for which there is a cluster in the track
    int64_t _mask = 0LL;

    /// mask of layers for which there is a cluster in the track, with correct associated g4hit
    int64_t _correct_mask = 0LL;

    /// mask of layers for which there is a cluster in the track, with correct associated g4hit
    int64_t _correct_mask_strict = 0LL;

    /// maks of layers for which there is a g4hit in the track
    int64_t _truth_mask = 0LL;

    unsigned int _nclusters_mvtx = 0;
    unsigned int _nclusters_intt = 0;
    unsigned int _nclusters_tpc = 0;
    unsigned int _nclusters_micromegas = 0;

    /// number of track states on track
    unsigned int _nstates = 0;
    unsigned int _nstates_mvtx = 0;
    unsigned int _nstates_intt = 0;
    unsigned int _nstates_tpc = 0;
    unsigned int _nstates_micromegas = 0;

    float _chisquare = 0;
    int _ndf = 0;

    //!@name position
    //@{
    float _x = 0;
    float _y = 0;
    float _z = 0;
    float _r = 0;
    float _phi = 0;
    //@}

    //!@name momentum
    //@{
    float _px = 0;
    float _py = 0;
    float _pz = 0;
    float _pt = 0;
    float _p = 0;
    float _eta = 0;
    //@}

    //! dedx in TPC using cluster information only
    float _dedx = 0;

    //!@name truth momentum
    //@{
    int _pid = 0;
    int _embed = 0;
    bool _is_primary = false;

    // number of g4hits from this MC track that match
    unsigned int _contributors = 0;

    float _truth_px = 0;
    float _truth_py = 0;
    float _truth_pz = 0;
    float _truth_pt = 0;
    float _truth_p = 0;
    float _truth_eta = 0;

    // dedx in TPC using truth information (not sure how to calculate)
    float _truth_dedx = 0;

    //@}

    // associate clusters
    ClusterStruct::List _clusters;

    // associate calorimater clusters
    CaloClusterStruct::List _calo_clusters;

  };


  // track information to be stored in tree
  class TrackStruct_small
  {
    public:

    // constructor
    explicit TrackStruct_small() = default;

    int _charge = 0;
    unsigned int _nclusters = 0;

    /// mask of layers for which there is a cluster in the track
    int64_t _mask = 0LL;

    unsigned int _nclusters_mvtx = 0;
    unsigned int _nclusters_intt = 0;
    unsigned int _nclusters_tpc = 0;
    unsigned int _nclusters_micromegas = 0;

    /// number of track states on track
    unsigned int _nstates = 0;
    unsigned int _nstates_mvtx = 0;
    unsigned int _nstates_intt = 0;
    unsigned int _nstates_tpc = 0;
    unsigned int _nstates_micromegas = 0;

    float _chisquare = 0;
    int _ndf = 0;

    float _px = 0;
    float _py = 0;
    float _pz = 0;
    float _pt = 0;
    float _p = 0;
    float _eta = 0;

  };

  // pair information to be stored in tree
  class TrackPairStruct
  {
    public:

    using List = std::vector<TrackPairStruct>;

    int _charge = 0;

    //!@name momentum
    //@{
    float _px = 0;
    float _py = 0;
    float _pz = 0;
    float _pt = 0;
    float _p = 0;
    float _e = 0;
    float _m = 0;
    float _eta = 0;

    std::array<TrackStruct_small,2> _tracks;

    //@}
  };

  //! track container
  class Container: public TObject
  {

    public:

    //! constructor
    explicit Container() = default;

    //! copy constructor
    explicit Container(const Container &) = delete;

    //! assignment operator
    Container& operator = ( const Container& ) = delete;

    //! reset
    // void Reset() override;
    void Reset();

    //!@name accessors
    //@{

    const EventStruct::List& events() const
    { return _events; }

    const ClusterStruct::List& clusters() const
    { return _clusters; }

    const CaloClusterStruct::List& calo_clusters() const
    { return _calo_clusters; }

    const CMClusterStruct::List& cm_clusters() const
    { return _cm_clusters; }

    const TrackStruct::List& tracks() const
    { return _tracks; }

    const TrackPairStruct::List& trackPairs() const
    { return _track_pairs; }

    //@}

    //!@name modifiers
    //@{

    void addEvent( const EventStruct& event )
    { _events.push_back( event ); }

    void addCluster( const ClusterStruct& cluster )
    { _clusters.push_back( cluster ); }

    void addCaloCluster( const CaloClusterStruct& cluster )
    { _calo_clusters.push_back( cluster ); }

    void addCMCluster( const CMClusterStruct& cluster )
    { _cm_clusters.push_back( cluster ); }

    void addTrack( const TrackStruct& track )
    { _tracks.push_back( track ); }

    void addTrackPair( const TrackPairStruct& pair )
    { _track_pairs.push_back( pair ); }

    void clearEvents()
    { _events.clear(); }

    void clearClusters()
    { _clusters.clear(); }

    void clearCaloClusters()
    { _calo_clusters.clear(); }

    void clearCMClusters()
    { _cm_clusters.clear(); }

    void clearTracks()
    { _tracks.clear(); }

    void clearTrackPairs()
    { _track_pairs.clear(); }

    //@}

    private:

    //! event struct
    EventStruct::List _events;

    //! clusters array
    ClusterStruct::List _clusters;

    //! calo clusters array
    CaloClusterStruct::List _calo_clusters;

    //! central membrane clustsrs
    CMClusterStruct::List _cm_clusters;

    //! tracks array
    TrackStruct::List _tracks;

    //! track pairs array
    TrackPairStruct::List _track_pairs;

    ClassDefOverride(Container,1)

  };

};

#endif  // G4EVAL_TRACKINGEVALUATOR_HP_H
