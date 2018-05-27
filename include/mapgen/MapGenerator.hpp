#ifndef MAPGEN_H_
#define MAPGEN_H_

#include "noise/noise.h"
#include "noise/noiseutils.h"
#include <VoronoiDiagramGenerator.h>
#include <functional>
#include <memory>
#include <random>

#include "Region.hpp"
#include "Simulator.hpp"
#include "State.hpp"
#include "WeatherManager.hpp"
#include "micropather.h"

typedef std::function<bool(std::shared_ptr<Region>, std::shared_ptr<Region>)> sameFunc;
typedef std::function<void(std::shared_ptr<Region>, std::shared_ptr<Cluster>)> assignFunc;
typedef std::function<void(std::shared_ptr<Region>, std::shared_ptr<Cluster>,
                           std::map<std::shared_ptr<Region>, std::shared_ptr<Cluster>> *)>
    reassignFunc;
typedef std::function<std::shared_ptr<Cluster>(std::shared_ptr<Region>)> createFunc;

class MapGenerator {
public:
  MapGenerator(int w, int h);

  void build();
  void update();
  void forceUpdate();
  void relax();
  void setSeed(int seed);
  void setOctaveCount(int octaveCount);
  void setSize(int w, int h);
  void setFrequency(float freq);
  void setPointCount(int count);
  int getPointCount();
  int getOctaveCount();
  int getRelax();
  float getFrequency();
  int getSeed();
  std::shared_ptr<Region> getRegion(std::shared_ptr<Region> r, sf::Vector2f pos);
  void seed();
  RegionList getRegions();
  void setMapTemplate(const char *t);
  void startSimulation();

  bool simpleRivers;
  bool ready;
  Map *map;
  Simulator *simulator;
  std::shared_ptr<WeatherManager> weather = nullptr;

  template <typename Iter> Iter select_randomly(Iter start, Iter end);

  std::mt19937 *_gen;

private:
  void makeHeights();
  void makeDiagram();
  void makeRegions();
  void makeFinalRegions();
  void makeRivers();
  void makeClusters();
  void makeMegaClusters();
  void makeRelax();
  void makeRiver(std::shared_ptr<Region>r);
  void calcHumidity();
  void calcTemp();
  void simplifyRivers();
  void makeBorders();
  void makeMinerals();
  void makeCities();
  void makeStates();

  void getSea(RegionList *seas, std::shared_ptr<Region> base, std::shared_ptr<Region> r);
  int _seed;
  VoronoiDiagramGenerator _vdg;
  int _pointsCount;
  int _w;
  int _h;
  int _relax;
  int _octaves;
  float _freq;
  sf::Rect<double> _bbox;
  std::vector<sf::Vector2<double>> *_sites;
  std::map<Cell *, std::shared_ptr<Region>> _cells;
  std::unique_ptr<Diagram> _diagram;
  Cell *_highestCell;
  std::map<std::shared_ptr<Region>, Cell *> cellsMap;
  std::vector<State *> states;

  micropather::MicroPather *_pather;
  module::Perlin _perlin;
  utils::NoiseMap _heightMap;
  utils::NoiseMap _mineralsMap;
  std::string _terrainType;

  void genRandomSites(std::vector<sf::Vector2<double>> &sites,
                      sf::Rect<double> &bbox, unsigned int dx, unsigned int dy,
                      unsigned int numSites);

  std::vector<std::shared_ptr<Cluster>> clusterize(RegionList regions,
                                    sameFunc isSame, assignFunc assignCluster,
                                    reassignFunc reassignCluster,
                                    createFunc createCluster);
};

#endif
