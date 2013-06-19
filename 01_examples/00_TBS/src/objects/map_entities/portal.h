#ifndef PORTAL_H
#define PORTAL_H

#include "..\..\Engine\Objects\map_entity.h"
#include "..\windows\text_message.h"
using namespace Engine::Objects;

namespace Map_Entities {

class Portal: public Map_Entity
{
 private:
  int sid;
  int destination_x, destination_y;

 public:
  Portal(Sprite, int, int, int);
  virtual ~Portal();

  virtual void hero_visit(Level*);
};

}

#endif // PORTAL_H
