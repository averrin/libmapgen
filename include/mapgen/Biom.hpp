#ifndef BIOM_H_
#define BIOM_H_
#include <string>
#include <vector>
#include <map>

struct Biom {
  float border;
  std::string name;
  float feritlity;
  bool operator==(const Biom& b) const {
    return b.name == name;
  }
  bool operator!=(const Biom& b) const {
    return b.name != name;
  }
  friend bool operator<(const Biom& l, const Biom& r) {
    return l.name < r.name;
  }
};

namespace biom {
const float DEFAULT_HUMIDITY = 0.f;
  const float DEFAULT_TEMPERATURE = 30.f;

  const Biom ABYSS = {-2.0000f, "Abyss", 0.f};
  const Biom DEEP = {-1.0000f, "Deep", 0.f};
  const Biom SHALLOW = {-0.2500f, "Shallow", 0.f};
  const Biom SHORE = {0.0000f, "Shore", 0.f};
  // const Biom SAND = {0.0625, "Sand", 0};
  const Biom SAND = {0.0625f, "Sand", 0.f};
  const Biom GRASS = {0.1250f, "Grass", 0.8f};
  const Biom FORREST = {0.3750f, "Forrest", 0.6f};
  const Biom ROCK = {0.7500f, "Rock", 0.f};
  const Biom SNOW = {1.0000f, "Snow", 0.f};
  const Biom ICE = {1.2000f, "Ice", 0.f};
  const Biom PRAIRIE = {999.000f, "Prairie", 0.6f};
  const Biom MEADOW = {999.000f, "Meadow", 1.f};
  const Biom DESERT = {999.000f, "Desert", 0.f};
  const Biom CITY = {999.000f, "City", 0.f};

  const Biom RAIN_FORREST = {0.3750f, "Rain forrest", 0.6f};

  const std::vector<Biom> BIOMS = {
    {ABYSS, DEEP, SHALLOW, SHORE, SAND, GRASS, FORREST, ROCK, SNOW, ICE}};

  const Biom LAKE = {999.000f, "Lake", 0.f};
  const Biom MARK = {999.000f, "Mark"};
  const Biom MARK2 = {999.000f, "Mark"};

  const Biom LAND = {0.500f, "Land", 0.f};
  const Biom SEA = {-1.000f, "Sea", 0.f};

  const std::vector<std::vector<Biom>> BIOMS_BY_HEIGHT = {{
    {ABYSS},
    {DEEP},
    {SHALLOW},
    {SHORE},
    {SAND},
    {MEADOW, GRASS, PRAIRIE, SAND},
    {RAIN_FORREST, FORREST, GRASS, PRAIRIE, SAND},
    {ROCK},
    {SNOW, ROCK},
    {ICE},
}};

  const std::map<std::string, Biom> BIOMS_BY_TEMP = {{{SAND.name, DESERT},
                                              {PRAIRIE.name, DESERT},
                                              {GRASS.name, PRAIRIE},
                                              {MEADOW.name, GRASS}}};
}

#endif
