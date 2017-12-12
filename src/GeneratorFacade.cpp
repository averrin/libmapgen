#include <iostream>
#include "GeneratorFacade.h"
#include <vector>
#include <string>
#include "json.hpp"
#include "mapgen/MapGenerator.hpp"

using json = nlohmann::json;

json world;
char buff[10000000];

extern "C" {
	__declspec(dllexport) int createMap (int seed, int w, int h) {

		auto mapgen = new MapGenerator(w, h);
		mapgen->setSeed(seed);
		mapgen->update();

		world = json({});
		auto regions = json::array();
		auto mClusters = json::array();
		for (auto c : mapgen->map->megaClusters) {
			mClusters.push_back(c->name);
		}

		int i = 0;
		for (auto r : mapgen->map->regions) {
			auto json_r = json({});
			auto f_points = json::array();
			auto points = r->getPoints();
			
			int n = 0;
			for (PointList::iterator it2 = points.begin(); it2 < points.end();
				it2++, n++) {
				sf::Vector2<double> *p = points[n];
				f_points.push_back({ {"x", p->x}, {"y", p->y}, {"height", r->getHeight(p)} });
			}
			json_r["points"] = f_points;

			json_r["site"] = { {"x", r->site->x}, {"y", r->site->y}, {"height", r->getHeight(r->site)} };
			json_r["biom"] = r->biom.name;
			json_r["isLand"] = r->megaCluster->isLand;
			auto it = std::find(mapgen->map->megaClusters.begin(), mapgen->map->megaClusters.end(), r->megaCluster);
			json_r["megaCluster"] = std::distance(mapgen->map->megaClusters.begin(), it);
			regions.push_back(json_r);
			i++;
		}

		world["regions"] = regions;
		world["megaClusters"] = mClusters;
		auto dump = world.dump();
		std::strcpy(buff, dump.c_str());
		return dump.length() + 1;
  }
	__declspec(dllexport) void getRegion(char *str, int n)
	{
		strcpy_s(str, n, buff);
	}
}
