#include "mapgen/Region.hpp"
#include <vector>
#include <cmath>
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

Region::Region() {};

Region::Region(Biom b, PointList v, HeightMap h, Point s)
  : biom(b), _verticies(v), _heights(h), site(s) {}

PointList Region::getPoints() {
  return _verticies;
};

float Region::getHeight(Point p) {
  return _heights[p];
}

bool Region::isCoast() {
  return std::count_if(neighbors.begin(), neighbors.end(), [&](std::shared_ptr<Region> n) {
      return !n->megaCluster->isLand;
    }) != 0;
}

bool Region::isLakeCoast() {
  return std::count_if(neighbors.begin(), neighbors.end(), [&](std::shared_ptr<Region> n) {
      return n->biom == biom::LAKE;
    }) != 0;
}

std::shared_ptr<Region> Region::getRegionWithDirection(float angle, float force) {
  std::shared_ptr<Region> nr = nullptr;
  float cabs = 360.0;
  float ar = 0.0;
  float mar = 0.0;
  for (auto n : neighbors) {
    if (n->cluster->isLand && cluster->isLand && n->getHeight(n->site) - getHeight(site) > 0.07 * force) {
      continue;
    }

    //TODO: fix angle > 180
    auto dx = n->site->x - site->x;
    auto dy = n->site->y - site->y;
    ar = atan2(dy, dx);
    ar *= 180.f / M_PI;
    if (angle > 180) ar+=180;
    if (nr == nullptr || abs(ar - angle) < cabs) {
      nr = n;
      mar = ar;
      cabs = abs(ar - angle);
    }
  }
  // std::cout << cabs << std::endl;
  if (cabs > 15 + 45.f * force) return nullptr;
  return nr;
}
