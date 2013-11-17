#ifndef LOOP_H
#define LOOP_H

#include <map>
#include <string>
#include <vector>
#include "Controller.h"
#include "settings.h"
#include "Entities/Screen.h"
#if DEBUG_SHOW_FPS == 1
 #include "Entities/Text.h"
#endif
using std::map;
using std::string;
using std::vector;
using namespace Engine::Entities;

namespace Engine {
 enum Loop_Iteraton {
  LOOP_ITERATION_USUAL,
  LOOP_ITERATION_SAVE_STATE
 };

 class Loop
 {
  private:
   Controller* controller;
   bool done;

   #if DEBUG_SHOW_FPS == 1
    Text label;
   #endif

   map<ScreenID, Screen*> static_screens;
   vector<Screen*> drown_static_screens;
   Screen* current_screen;
   Screen* new_screen;

   void clean_drown_memory_up();
   void redraw();
   void update();

  public:
   Loop(Controller*);
   ~Loop();

   void operator()(); //functor-like
   void stop();
   void restart(bool save_state);

   void open_screen(Screen* screen);
   void open_screen(ScreenID sid, bool recreate = false);

   void save(string);
   void load(string);

   ScreenID sid();
 };
}

#endif // LOOP_H
