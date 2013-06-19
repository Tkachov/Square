#ifndef MAP_ENTITY_H
#define MAP_ENTITY_H

#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "..\input.h"
#include "object.h"
#include "sprite.h"
#include <fstream>
using std::ifstream;
using std::ofstream;

class Level;
//namespace Engine { namespace Objects { class Map_Entity; } };

namespace Engine { namespace Objects {

class Map_Entity: public Object
{
 protected:
  Sprite spr;
  bool _clicked;
  bool _prevents_way;
  bool _visit_from_distance;
  bool _changeable;

 public:
  Map_Entity(Sprite s, bool obstacle = true, bool from_distance = false, bool is_changeable = false): Object(0,0,0), spr(s), _clicked(false), _prevents_way(obstacle), _visit_from_distance(from_distance), _changeable(is_changeable) {};
  virtual ~Map_Entity() {};

  virtual void update(Input* i) { spr.update(i); }
  virtual void update(int sx, int sy, Input* i) {
   spr.update(i);
   Image ci = spr.current_image();
   sx+=ci.x();
   sy+=ci.y();
   int mx = i->mouse_x();
   int my = i->mouse_y();
   if(!i->paused() && !i->mouse_eaten(0) && i->mouse_release(1)) {
    Image img = spr.current_image();
    bool intersects = ((mx >= sx && mx <= sx + img.w()) && (my >= sy && my <= sy + img.h()));
    if(intersects) intersects = spr.is_intersected(mx-sx,my-sy);
    if(intersects) {
     i->mouse_eat(0);
     i->mouse_eat(1);
     _clicked = true;
    }
   }
  }
  virtual void draw(SDL_Surface* s) { spr.draw(_x, _y, s); };
  virtual void draw(int sx, int sy, SDL_Surface* s) {
   int px = _x; _x=sx;
   int py = _y; _y=sy;
   draw(s);
   _x=px; _y=py;
  }

  virtual void hero_visit(Level*) = 0;
  virtual void save(ofstream&) {};
  virtual void load(ifstream&) {};

  bool clicked() { bool wc = _clicked; _clicked = false; return wc; }
  bool prevents_way() { return _prevents_way; }
  bool visit_from_distance() { return _visit_from_distance; }
  bool changeable() { return _changeable; }
};

} }

#endif // MAP_ENTITY_H
