#include <iostream>
#include "GeneratorFacade.h"
#include <vector>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

json region;
char buff[10000];

extern "C" {
	__declspec(dllexport) int createMap (int size) {
		region = json({});
		auto points = json::array();
		/*
		for (float i = 0; i < size; i++)
		{
			points.push_back({ {"x", 1}, {"y", 1}, {"height", 0} });
		}*/
		points.push_back({ {"x", 0}, {"y", 0}, {"height", 1} });
		points.push_back({ {"x", 0}, {"y", 2}, {"height", 0} });
		points.push_back({ {"x", 2}, {"y", 2}, {"height", 0} });
		points.push_back({ {"x", 2}, {"y", 0}, {"height", 1} });
		region["points"] = points;
		auto dump = region.dump();
		std::strcpy(buff, dump.c_str());
		return dump.length() + 1;
  }
	__declspec(dllexport) void getRegion(char *str, int n)
	{
		strcpy_s(str, n, buff);
	}
}
