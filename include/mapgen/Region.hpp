#ifndef REGION_H_
#define REGION_H_

#include <memory>
#include <vector>
#include "Biom.hpp"
#include "State.hpp"
#include <VoronoiDiagramGenerator.h>

typedef sf::Vector2<double>* Point;
typedef std::vector<Point> PointList;
typedef std::map<Point,float> HeightMap;

struct Cluster;
typedef Cluster MegaCluster;
typedef Cluster StateCluster;
class City;
class Location;
class Region {
public:
  Region();
  Region(Biom b, PointList v, HeightMap h, Point s);
  PointList getPoints();
  float getHeight(Point p);
  Biom biom;
  Point site;
  bool hasRiver = false;
  std::shared_ptr<Cluster>cluster = nullptr;
  std::shared_ptr<Cluster>stateCluster = nullptr;
  std::shared_ptr<MegaCluster>megaCluster = nullptr;
  bool border = false;
  float humidity = 0.f;
  Cell* cell = nullptr;
  float temperature = 0.f;
  float minerals = 0.f;
  float nice = 0.f;
  float windForce = 0.f;
  std::shared_ptr<City> city = nullptr;
  std::vector<std::shared_ptr<Region>> neighbors;
  bool hasRoad = false;
  int traffic = 0;
  std::shared_ptr<Location> location = nullptr;
  State* state = nullptr;
  bool stateBorder = false;
  bool seaBorder = false;
  bool isCoast();
  bool isLakeCoast();

  std::shared_ptr<Region> getRegionWithDirection(float angle, float force);

private:
	PointList _verticies;
  HeightMap _heights;
};

typedef std::vector<std::shared_ptr<Region>> RegionList;

struct Cluster {
  std::string name = "";
  RegionList regions;
  std::vector<std::shared_ptr<Cluster>> neighbors;
  std::shared_ptr<MegaCluster> megaCluster = nullptr;
  Biom biom;
  bool hasRiver = false;;
  bool isLand = false;;
  Point* center = nullptr;
  PointList border;
  RegionList resourcePoints;
  RegionList goodPoints;
  std::vector<std::shared_ptr<City>> cities;
  bool hasPort = false;
  std::vector<State*> states;
};

#endif
