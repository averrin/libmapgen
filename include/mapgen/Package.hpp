#ifndef PACKAGE_H_
#define PACKAGE_H_

#include "City.hpp"

enum PackageType {
  MINERALS,
  AGROCULTURE
};

class Package {
public:
  Package (std::shared_ptr<City> owner, PackageType type, unsigned int count);
  std::shared_ptr<City> owner = nullptr;
  std::vector<std::shared_ptr<City>> ports;
  PackageType type;
  unsigned int count = 0;
  void buy(std::shared_ptr<City> buyer, float price, unsigned int c);
};

#endif
