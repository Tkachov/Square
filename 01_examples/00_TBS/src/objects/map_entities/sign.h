#ifndef SIGN_H
#define SIGN_H

#include "..\..\Engine\Objects\map_entity.h"
#include "..\windows\text_message.h"
#include <string>
using namespace Engine::Objects;
using std::string;

namespace Map_Entities {

class Sign: public Map_Entity
{
 private:
  string mess;

 public:
  Sign(Sprite, string);
  virtual ~Sign();

  virtual void hero_visit(Level*);
};

}

#endif // SIGN_H
