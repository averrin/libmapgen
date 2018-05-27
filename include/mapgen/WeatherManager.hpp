#pragma once
#include <vector>
#include "Region.hpp"
#include "Biom.hpp"

class WeatherManager {
public:
    WeatherManager();
    void calcTemp(RegionList r);
    void calcHumidity(RegionList r);
    void genWind();


  float temperature = biom::DEFAULT_TEMPERATURE;
  float windForce;
  float windAngle;
};
