#ifndef LOCATION_H_
#define LOCATION_H_

#include <memory>
#include "Region.hpp"

enum LocationType {
  CAPITAL,
  PORT,
  MINE,
  AGRO,
  TRADE,
  LIGHTHOUSE,
  CAVE,
  FORT
};

class Location {
public:
  Location(std::shared_ptr<Region> r, std::string n, LocationType t);
  std::shared_ptr<Region> region = nullptr;
  std::string name;
  LocationType type;
  std::string typeName;
};

#endif
