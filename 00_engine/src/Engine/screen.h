#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>
  #include <GL/gl.h>
  #include <GL/glu.h>
#include "game.h"
#include "functor.h"
#include "Objects\object.h"
#include <vector>
#include <algorithm>
#include <fstream>
using std::vector;
using std::sort;
using std::ifstream;
using std::ofstream;
using namespace Engine::Objects;

namespace Engine {

class Screen
{
 private:
  friend class Functor<Screen>;

 protected:
  class queued_object {
   public:
    queued_object(Object* o): obj(o) {};
    Object* obj;
    bool operator<(const queued_object& other) const { return (obj->priority() < other.obj->priority()); }
  };

  typedef vector<queued_object> opqueue;

  Game* game;
  Loader* loader;
  Input* input;
  opqueue objects;
  bool _is_static;

  virtual void load(); //called once after construction (though each time if screen is not static)

  void add_object(Object* o, bool reorder = true);
  void reorder_queue();
  void update_queue();
  void clear_queue();
  void draw_queue();
  void draw_queue(int,int);

 public:
  Screen(Game* gm, Loader* ld, Input* input, bool st = false);
  virtual ~Screen();
  virtual void start(); //called each time screen is opened
  virtual void update();
  virtual void redraw();
  virtual void show_message(Object*);
  virtual void save_state(ofstream&);
  virtual void load_state(ifstream&);

  bool is_static();
  virtual ScreenID ID() { return SCREENID_DEFAULT; } //defined in "game.h"
};

}

#endif // SCREEN_H
