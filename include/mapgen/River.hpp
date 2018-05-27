#ifndef RIVER_H_
#define RIVER_H_

#include "Region.hpp"

struct River {
  std::string name;
  PointList* points;
  RegionList regions;
};

#endif
