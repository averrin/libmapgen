#ifndef STATE_H_
#define STATE_H_
#include <VoronoiDiagramGenerator.h>

class State {
public:
  State(std::string n, Cell* c);
  std::string name;
  Cell* cell;
};

#endif
