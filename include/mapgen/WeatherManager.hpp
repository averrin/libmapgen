#pragma once
#include <vector>
#include "Region.hpp"
#include "Biom.hpp"

class WeatherManager {
public:
    WeatherManager();
    void calcTemp(std::vector<Region *> r);
    void calcHumidity(std::vector<Region *> r);
    void genWind();


  float temperature = biom::DEFAULT_TEMPERATURE;
  float windForce;
  float windAngle;
};
