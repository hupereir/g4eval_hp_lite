#ifndef G4EVAL_SIMEVALUATOR_HP_H
#define G4EVAL_SIMEVALUATOR_HP_H

#include <TObject.h>

#include <map>
#include <set>
#include <vector>

class SimEvaluator_hp
{
  public:

  //! constructor
  SimEvaluator_hp() = default;


  // event information
  class EventStruct
  {

    public:

    using List = std::vector<EventStruct>;

    //! impact parameter, when relevant
    float _bimp = 0;

    //! reaction plane angle, when relevant
    float _rplane = 0;

    //!@name used keep track of the number of pileup events
    //@{
    int _nevt = 0;
    int _nevt_active = 0;
    int _nevt_bg = 0;
    //@}

    // number of primary g4 particles with pt > 0.5 GeV
    int _nparticles = 0;

    // id of the main (== primary) vertex
    int _main_vertex_id = 0;

  };

  // vertex information
  class VertexStruct
  {
    public:
    using List = std::vector<VertexStruct>;
    int _embed = 0;

    //! vertex id
    int _id = 0;

    //!@name vertex position
    //@{
    float _x = 0;
    float _y = 0;
    float _z = 0;
    float _t = 0;
    //@}

    //! true if this is the main (primary) vertex
    bool _is_main_vertex = false;
  };

  // particle information
  class ParticleStruct
  {
    public:
    using List = std::vector<ParticleStruct>;

    int _charge = 0;

    //! particle id
    int _pid = 0;

    //! embeding id
    int _embed = 0;

    //! track id
    int _trkid = 0;

    //! track id of the parent particle
    int _parent_id = 0;

    //! track id of the primary particle
    int _primary_id = 0;

    //! vertex id
    int _vtx_id = 0;

    //! true if particle is a primary particle
    bool _is_primary = false;

    //! detector mask
    int64_t _mask = 0;

    //!@name origin
    //@{
    float _x = 0;
    float _y = 0;
    float _z = 0;
    float _t = 0;
    //@}

    //!@name momentum and energy
    //@{
    float _px = 0;
    float _py = 0;
    float _pz = 0;
    float _pt = 0;
    float _p = 0;
    float _e = 0;
    float _eta = 0;
    //@}

    //! pid of the parent particle
    int _parent_pid = 0;

    //! pid of the parent primary particle
    int _primary_pid = 0;
  };

  // particle information
  class G4HitStruct
  {
    public:
    using List = std::vector<G4HitStruct>;

    //! embeded index
    int16_t _embed = 0;

    //! detector id
    int16_t _detid = -1;

    //! calorimeter id
    int16_t _caloid = -1;

    //! layer
    int16_t _layer = 0;

    //! associated PHG4Particle
    int _trkid = 0;

    //! associated particle type
    int _pid = 0;

    //! position
    float _x = 0;
    float _y = 0;
    float _z = 0;
    float _r = 0;
    float _phi = 0;

    //! time
    float _t = 0;

    //! g4hit path length
    float _length = 0;
  };

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

    const EventStruct::List& events() const
    { return _events; }

    const VertexStruct::List& vertexList() const
    { return _vertex_list; }

    const ParticleStruct::List& particleList() const
    { return _particle_list; }

    const G4HitStruct::List& g4hits() const
    { return _g4hits; }

    //@}

    //!@name modifiers
    //@{

    void addEvent( const EventStruct& event )
    { _events.push_back( event ); }

    void addVertex( const VertexStruct& vertex )
    { _vertex_list.push_back( vertex ); }

    void addParticle( const ParticleStruct& particle )
    { _particle_list.push_back( particle ); }

    void addG4Hit( const G4HitStruct& hit )
    { _g4hits.push_back( hit ); }

    void clearEventList()
    { _events.clear(); }

    void clearVertexList()
    { _vertex_list.clear(); }

    void clearParticleList()
    { _particle_list.clear(); }

    void clearG4Hits()
    { _g4hits.clear(); }

    //@}

    private:

    //! event struct
    EventStruct::List _events;

    //* vertex list
    VertexStruct::List _vertex_list;

    //* particles
    ParticleStruct::List _particle_list;

    //* hits
    G4HitStruct::List _g4hits;

    //! pid of the parent particle
    int _parent_pid = 0;

    //! pid of the parent primary particle
    int _primary_pid = 0;

    ClassDef(Container,1)

  };

};

#endif  // G4EVAL_SIMEVALUATOR_HP_H
