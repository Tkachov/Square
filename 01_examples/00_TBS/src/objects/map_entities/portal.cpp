#include "portal.h"
#include "..\level.h"

namespace Map_Entities {

 Portal::Portal(Sprite s, int screen, int dstx, int dsty):
  Map_Entity(s), sid(screen), destination_x(dstx), destination_y(dsty) {};
 Portal::~Portal() {};

 void Portal::hero_visit(Level* l) {
  Game* g = l->get_game();
  if(g->portal_available(sid)) {
   State* st = g->state();
   st->set_persistent("map", "hero_x", new int(destination_x));
   st->set_persistent("map", "hero_y", new int(destination_y));
   g->open_screen(ScreenID(sid));
  } else l->show_message(new Text_Message(String_Table::translate["msg_portal_is_unavailable"], g, l->get_loader(), 95));
 }

}
