#include "SimEvaluator_hp.h"

//_____________________________________________________________________
void SimEvaluator_hp::Container::Reset()
{
  _events.clear();
  _vertex_list.clear();
  _particle_list.clear();
  _g4hits.clear();
}
