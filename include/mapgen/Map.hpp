#ifndef MAP_H_
#define MAP_H_
#include "City.hpp"
#include "Region.hpp"
#include "River.hpp"
#include "Road.hpp"
#include "micropather.h"
#include <cstring>

class Map : public micropather::Graph {
public:
  ~Map();

  std::vector<std::shared_ptr<MegaCluster>> megaClusters;
  std::vector<std::shared_ptr<Cluster>> clusters;
  std::vector<std::shared_ptr<Cluster>> stateClusters;

  std::vector<State *> states;
  RegionList regions;
  std::vector<std::shared_ptr<River>> rivers;
  std::vector<std::shared_ptr<City>> cities;
  std::vector<std::shared_ptr<Location>> locations;
  std::vector<Road *> roads;
  std::map<std::pair<std::shared_ptr<Location>, std::shared_ptr<Location>>, Road*> roadMap;

  std::string status = "";

  float getRegionDistance(std::shared_ptr<Region>r, std::shared_ptr<Region>r2);
  float LeastCostEstimate(void *stateStart, void *stateEnd);
  void AdjacentCost(void *state, MP_VECTOR<micropather::StateCost> *adjacent);
  void PrintStateInfo(void *state);

};

#endif
