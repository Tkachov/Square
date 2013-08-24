#include <algorithm>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include "Input.h"
#include "Logger.h"
#include "Loop.h"
#include "Main_Window.h"
#include "settings.h"
#include "utils.h"
#include "Global/load_string_tables.h"
using std::unique;

namespace Engine {

Loop::Loop(Controller* control) {
 Logger::start_session();

 //bind itself to controller
 if(!control) throw "Unable to bind to a controller.";
 controller = control;
 controller->bind_loop(this);

 new_screen = current_screen = 0;

 //load settings
 int width = 800;
 int height = 600;
 int flags = SDL_WINDOW_OPENGL;

 string option = controller->get_option("width");
 if(option!="") width = to_int(option);

 option = controller->get_option("height");
 if(option!="") height = to_int(option);

 option = controller->get_option("fullscreen");
 if(option=="1") flags |= SDL_WINDOW_FULLSCREEN;
 else if(option=="2") flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

 //create window with given settings
 Main_Window::create(
  TITLE_ON_LAUNCH,
  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
  width, height, flags
 );

 //now load string tables
 option = controller->get_option("language");
 Global::load_string_tables((option==""?LANGUAGE:option));

 if(new_screen) {
  delete new_screen;
  new_screen=0;
 }
 if(current_screen) {
  delete current_screen;
  current_screen=0;
 }

 open_screen(Global::s_INDEX, true);
 current_screen = new_screen;
 new_screen = 0;
 current_screen->start();

 done = false;
}

Loop::~Loop() {
 for(map<ScreenID, Screen*>::iterator i=static_screens.begin(); i!=static_screens.end(); ++i)
  if(i->second!=current_screen) delete (i->second);
 clean_drown_memory_up();
 delete current_screen;
 Main_Window::destroy();
 Logger::end_session();
}

//{ private methods

void Loop::clean_drown_memory_up() {
 unique(drown_static_screens.begin(), drown_static_screens.end());
 vector<Screen*> survived;
 for(vector<Screen*>::iterator i=drown_static_screens.begin(); i!=drown_static_screens.end(); ++i)
  if(*i!=current_screen) delete (*i); else survived.push_back(*i);
 drown_static_screens.clear();
 drown_static_screens = survived;
}

void Loop::redraw() {
 //erase previous frame
 glClear(GL_COLOR_BUFFER_BIT);
 glEnable(GL_BLEND);
 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

 //draw a new one
 current_screen->redraw(0, 0);

 //bring it to the screen
 Main_Window::swap();
}

void Loop::update() {
 //get user's input
 controller->poll_events();

 //notify everything about it
 current_screen->update(0, 0);
}

//}

/*METHODS*/

void Loop::operator()() {
 Uint32 next_game_tick = SDL_GetTicks();
 Uint32 prev = SDL_GetTicks();
 int updates = 0;
 int redraws = 0;
 while(!done) {
  Uint32 curr = SDL_GetTicks();
  #if SHOW_FPS_IN_CAPTION == 1
   if(curr-prev >= 1000) {
    string caption = "FPS: ";
    char integer[15];
    itoa(redraws, integer, 10);
    caption += string(integer);
    caption += " / ";
    itoa(updates, integer, 10);
    caption += string(integer);
    Main_Window::set_title(caption);
    prev = curr;
    updates = 0;
    redraws = 0;
   }
  #endif

  int loops = 0;
  while(SDL_GetTicks()>=next_game_tick && loops<MAX_FRAMESKIP) {
   update();

   next_game_tick += SKIP_TICKS;
   ++loops;
   ++updates;
  }

  //float interpolation = float(SDL_GetTicks() + SKIP_TICKS - next_game_tick) / float(SKIP_TICKS);
  redraw();
  ++redraws;

  if(new_screen) {
   if(!current_screen->is_static()) delete current_screen;
   current_screen = new_screen;
   new_screen = 0;
   Input::unpause();
   current_screen->start();
  }
 }
}

void Loop::stop() {
 done=true;
}

void Loop::restart(bool save_state) {
 throw (save_state?LOOP_ITERATION_SAVE_STATE:LOOP_ITERATION_USUAL);
}

//screens

void Loop::open_screen(Screen* s) {
 if(s!=current_screen && s!=0) new_screen = s;
}

void Loop::open_screen(ScreenID sid, bool recreate) {
 clean_drown_memory_up();
 if(!recreate && static_screens.count(sid)!=0) new_screen = static_screens[sid];
 else {
  Screen* created = Global::create_screen(controller, sid);
  if(created!=0) {
   new_screen = created;
   if(static_screens.count(sid)!=0) {
    Screen* s = static_screens[sid];
    if(current_screen!=0 && s==current_screen) drown_static_screens.push_back(s);
    else if(s) delete s;
    static_screens.erase(sid);
   }
   if(new_screen->is_static()) static_screens[sid] = new_screen;
  }
 }
}

//saving/loading

void Loop::save(string fn) {
 fn="saves\\"+fn;
 ofstream fout(fn.c_str());
 for(map<ScreenID,Screen*>::iterator i=static_screens.begin(); i!=static_screens.end(); ++i)
  if(i->second) {
   fout << int(i->first) << "\n";
   i->second->save_state(fout);
  }

 fout << "-1\n"; //end of screen infos
 controller->save_state(fout);
 fout << int(current_screen?current_screen->id():Global::s_UNKNOWN_ID) << "\n";
 fout.close();
}

void Loop::load(string fn) {
 fn="saves\\"+fn;
 ifstream fin(fn.c_str());
 int s;
 fin >> s;
 ScreenID sid;
 while(s!=-1) {
  sid = ScreenID(s);
  open_screen(sid, true); //reload the static screen
  static_screens[sid]->load_state(fin);
  fin >> s;
 }
 controller->load_state(fin);
 fin >> s;
 sid = ScreenID(s);
 open_screen((static_screens.count(sid)==0?Global::s_INDEX:sid));
 fin.close();
}

/*GETTERS*/

ScreenID Loop::sid() { return (current_screen?current_screen->id():Global::s_UNKNOWN_ID); }

}
