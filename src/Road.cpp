#include "mapgen/Road.hpp"
#include "mapgen/Region.hpp"
#include "micropather.h"

Road::Road() {};

Road::Road(micropather::MPVector<void *>* path, float c) : cost(c){
  unsigned size = path->size();
  for (int k = 0; k < size; ++k) {
    auto ptr = (*path)[k];
    auto r = *static_cast<std::shared_ptr<Region>*>(ptr);
    regions.push_back(r);
    r->hasRoad = true;
    r->traffic += 1;
  }
};
