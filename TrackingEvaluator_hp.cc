#include "TrackingEvaluator_hp.h"

//_____________________________________________________________________
void TrackingEvaluator_hp::Container::Reset()
{
  _events.clear();
  _clusters.clear();
  _calo_clusters.clear();
  _cm_clusters.clear();
  _tracks.clear();
  _track_pairs.clear();
}
