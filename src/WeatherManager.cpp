#include "mapgen/WeatherManager.hpp"
#include <fmt/format.h>

WeatherManager::WeatherManager() {}


void WeatherManager::genWind() {
  windForce = rand() / (double)RAND_MAX;
  windAngle = rand() / (double)RAND_MAX * 270;
  fmt::print("{} - {}\n", windForce, windAngle);
}


void WeatherManager::calcTemp(RegionList regions) {
  for (auto r : regions) {
    // TODO: adjust it
    r->temperature = temperature - (temperature / 5 * r->humidity) -
                     (temperature / 1.2 * r->getHeight(r->site));
    for (auto n : r->neighbors) {
      if (n->biom == biom::LAKE) {
        r->temperature += 2;
        r->biom.feritlity += 0.2f;
      }
    }
  }

    for (std::shared_ptr<Region>region : regions) {
      if (!region->cluster->isLand) continue;
      auto r2 = region->getRegionWithDirection(windAngle, windForce);
      if (r2 != nullptr) {
        if (r2->temperature > region->temperature) {
          region->temperature += windForce * r2->temperature;
        } else {
          region->temperature -= 1 * windForce * r2->temperature;
        }
      }
    }
    for (std::shared_ptr<Region>region : regions) {
      auto i = 1;
      auto h = 0.f;
      for (auto n: region->neighbors) {
        h += n->temperature;
        i++;
      }
      region->temperature = h/float(i);
    }
}

void WeatherManager::calcHumidity(RegionList regions) {
  for (auto r : regions) {
    r->humidity = biom::DEFAULT_HUMIDITY;
    if (!r->megaCluster->isLand || r->biom == biom::LAKE) {
      r->humidity = 1;
      continue;
    }
    if (r->hasRiver) {
      r->humidity += 0.2f;
    }
  }

  auto calcRegionsHum = [&]() {
    for (auto r : regions) {
      if (!r->megaCluster->isLand || r->humidity >= 0.9) {
        continue;
      }
      for (auto rn : r->neighbors) {
        if (rn->hasRiver || rn->biom == biom::LAKE) {
          r->humidity += 0.05f;
        }
        float hd = rn->getHeight(rn->site) - r->getHeight(r->site);
        if (rn->humidity > r->humidity && r->humidity != 1 && hd < 0.04) {
          r->humidity += (rn->humidity - r->humidity) / (1.8f - (hd * 2));
        }
      }
      //r->humidity = std::min(0.9f, float(r->humidity));
      r->humidity = float(r->humidity);
    }
  };

  calcRegionsHum();
  std::reverse(regions.begin(), regions.end());
  calcRegionsHum();
  std::reverse(regions.begin(), regions.end());


    for (std::shared_ptr<Region>region : regions) {
      if (!region->cluster->isLand) continue;
      auto r2 = region->getRegionWithDirection(windAngle, windForce);
      if (r2 != nullptr) {
        if (r2->humidity > region->humidity) {
          region->humidity += windForce * r2->humidity;
        } else {
          region->humidity -= 0.2 * windForce * r2->humidity;
        }
      }
    }

    for (std::shared_ptr<Region>region : regions) {
      auto i = 1;
      auto h = 0.f;
      for (auto n: region->neighbors) {
        h += n->humidity;
        i++;
      }
      region->humidity = h/float(i);
    }
}
