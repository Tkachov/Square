#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>
  #include <GL/gl.h>
  #include <GL/glu.h>
#include "game.h"
#include "state.h"
#include "loader.h"
  #include "input.h"
  #include "utils.h"
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
  SDL_Surface* surface;
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
  Screen(Game* gm, SDL_Surface* surf, Loader* ld, Input* input, bool st = false);
  virtual ~Screen();
  virtual void start(); //called each time screen is opened
  virtual void update();
  virtual void redraw();
  virtual void show_message(Object*);
  virtual void save_state(ofstream&);
  virtual void load_state(ifstream&);

  bool is_static();
  virtual ScreenID ID() { return s_MAIN_MENU; }
};

}

#endif // SCREEN_H
