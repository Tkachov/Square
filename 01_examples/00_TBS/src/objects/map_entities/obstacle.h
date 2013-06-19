#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "..\..\Engine\Objects\map_entity.h"
using namespace Engine::Objects;

namespace Map_Entities {

class Obstacle : public Map_Entity
{
 public:
  Obstacle(Sprite s);
  virtual ~Obstacle();

  virtual void hero_visit(Level*) {};
  virtual void save(ofstream&) {};
  virtual void load(ifstream&) {};
};

}

#endif // OBSTACLE_H
