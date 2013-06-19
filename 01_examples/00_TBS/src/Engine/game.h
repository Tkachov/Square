#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "debug.h" //DEBUG_H is already defined in Release, so file will not work
#include "loader.h"
#include "input.h"
#include "state.h"
#include "logger.h"
#include "Data\string_table.h"
#include "Objects\object.h"
#include "Objects\image.h"
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
using std::map;
using std::vector;
using std::unique;
using std::ifstream;
using std::ofstream;
using namespace Engine::Data;

namespace Engine {
 class Screen;

 enum ScreenID {
  s_MAIN_MENU,
  s_THE_FOREST,
  s_THE_DUNGEON,

  s_screens_count
 };

 class Game
 {
  private:
   bool __init_sdl;
   bool __init_img;
   bool __init_ttf;
   Screen* new_screen; //%current_screen% will be swapped to this if not NULL
   map<ScreenID, Screen*> static_screens;
   vector<Screen*> drown_static_screens;

   //main members
   SDL_Surface* surface;
   Loader loader;
   Input input;
   Screen* current_screen;
   State _state;
   String_Table options;
   bool done;

   void start(int w, int h, int bits = 32, int surface_params = SDL_HWSURFACE|SDL_DOUBLEBUF);
   void clean_drown_memory_up();

  public:
   Game();
   ~Game();

   void loop();
   void stop();
   void open_screen(ScreenID, bool = false);
   void open_screen(Screen*);
   void save(string);
   void load(string);
   void save_options() { options.save_table("config.txt"); }
   void restart() { throw 1; }

   int w();
   int h();
   State* state() { return &_state; }
   ScreenID sid();
   bool portal_available(int);
   bool portal_available(ScreenID);
   string option(string key) { return options[key]; }
   void set_option(string key, string value) { options.displace(key, value); }
 };
}

#endif // GAME_H
