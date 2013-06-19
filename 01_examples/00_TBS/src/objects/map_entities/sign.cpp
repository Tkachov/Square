#include "sign.h"
#include "..\level.h"

namespace Map_Entities {

 Sign::Sign(Sprite s, string m): Map_Entity(s), mess(m) {};
 Sign::~Sign() {};

 void Sign::hero_visit(Level* l) {
  Game* g = l->get_game();
  l->show_message(new Text_Message(mess, g, l->get_loader(), 95));
 }

}
