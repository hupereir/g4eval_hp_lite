#ifndef G4EVAL_TrackingEvaluatorLight_hp_H
#define G4EVAL_TrackingEvaluatorLight_hp_H

#include <TObject.h>

#include <vector>


class TrackingEvaluatorLight_hp
{
  public:

  //! constructor
  TrackingEvaluatorLight_hp() = default;

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

    // geometrical phi and eta
    float _phi = 0;
    float _eta = 0;

    // energy
    float _e = 0;
    float _chisquare = 0;
    //@}

    //!@name matching track position
    //@{
    float _trk_x = 0;
    float _trk_y = 0;
    float _trk_z = 0;
    float _trk_r = 0;

    // geometrical phi and eta
    float _trk_phi = 0;
    float _trk_eta = 0;

    // extrapolation length
    float _trk_dr = 0;
    //@}

    //! towers
    TowerStruct::List _towers;
  };

  // track information to be stored in tree
  class TrackStruct
  {
    public:

    // constructor
    explicit TrackStruct() = default;

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
    unsigned int _nclusters_micromegas_phi = 0;
    unsigned int _nclusters_micromegas_z = 0;

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

    CaloClusterStruct _calo_cluster_emcal;
    CaloClusterStruct _calo_cluster_ihcal;
    CaloClusterStruct _calo_cluster_ohcal;
    CaloClusterStruct _calo_cluster_topo;
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
    void Reset();

    //!@name accessors
    //@{

    const TrackStruct::List& tracks() const
    { return _tracks; }

    //@}

    //!@name modifiers
    //@{

    void addTrack( const TrackStruct& track )
    { _tracks.push_back( track ); }

    void clearTracks()
    { _tracks.clear(); }
    //@}

    private:

    //! tracks array
    TrackStruct::List _tracks;

    ClassDefOverride(Container,1)

  };

};

#endif  // G4EVAL_TrackingEvaluatorLight_hp_H
