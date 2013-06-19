#include "..\screens\first_screen.h"
#include <iostream>
#include <string>
#include <time.h>
#include <windows.h>
using std::string;
using std::cerr;

namespace Engine {

Game::Game(): __init_sdl(false), __init_img(false), __init_ttf(false), options("config.txt"), done(false) {
 new_screen = current_screen = 0;
 surface = 0;

 //init SDL
 int init = SDL_Init(SDL_INIT_VIDEO);
 if(init<0) {
  string e = "Unable to init SDL: "; e+=SDL_GetError();
  throw e;
 }

#ifdef DBG_SOFTWARE_CURSOR
 SDL_ShowCursor(SDL_DISABLE);
#endif
#ifdef DBG_HARDWARE_CURSOR
 SDL_ShowCursor(SDL_DISABLE);
 SetCursor(LoadCursorFromFile(DBG_HARDWARE_CURSOR));
#endif
 __init_sdl = true;

 //init PNG
 int flags=IMG_INIT_PNG;
 init=IMG_Init(flags);
 if((init&flags) != flags) {
  string e = "IMG_Init: Failed to init required png support ("; e+=IMG_GetError(); e+=")";
  throw e;
 }
 __init_img = true;

 //init fonts
 if(TTF_WasInit()==0) {
  if(TTF_Init()<0) {
   string e = "TTF_Init failed: "; e+=TTF_GetError();
   throw e;
  }
 }
 __init_ttf = true;

 //start with default settings
 start(800, 600, 32, SDL_OPENGL);
}

void Game::clean_drown_memory_up() {
 unique(drown_static_screens.begin(), drown_static_screens.end());
 vector<Screen*> survived;
 for(vector<Screen*>::iterator i=drown_static_screens.begin(); i!=drown_static_screens.end(); ++i)
  if(*i!=current_screen) delete (*i); else survived.push_back(*i);
 drown_static_screens.clear();
 drown_static_screens = survived;
}

Game::~Game() {
 for(map<ScreenID,Screen*>::iterator i=static_screens.begin(); i!=static_screens.end(); ++i)
  if(i->second!=current_screen) delete (i->second);
 clean_drown_memory_up();
 delete current_screen;
 loader.free();
 if(surface!=NULL) SDL_FreeSurface(surface);
 if(__init_sdl) SDL_Quit();
 if(__init_img) IMG_Quit();
 if(__init_ttf) TTF_Quit();
 Logger::end_session();
}

/*METHODS*/

void Game::start(int w, int h, int bits, int surface_params) {
 if(surface!=NULL) SDL_FreeSurface(surface);

 Logger::start_session();

 //now load string tables
 string lang = options["language"];

 //push GENERAL
 string path = "res\\txt\\"; path+=lang; path+="\\general.txt";
 if(!file_exists(path.c_str())) {
  path = "res\\txt\\Russian\\general.txt";
  Logger::err << "Chosen localization files not found. [language=\"" << lang << "\"]\n";
 }
 if(!file_exists(path.c_str())) throw string("No localization files.");
 String_Table::translate.clear();
 String_Table::translate.push_table(path);

 //push UNICODE
 path = "res\\txt\\"; path+=lang; path+="\\unicode.txt";
 if(!file_exists(path.c_str())) {
  path = "res\\txt\\Russian\\unicode.txt";
  Logger::err << "Chosen localizaition unicode-table not found. [language=\"" << lang << "\"]\n";
 }
 if(!file_exists(path.c_str())) Logger::err << "Default (Russian) unicode-table not found.\n";
 else {
  String_Table::unicode.clear();
  String_Table::unicode.push_table(path);
 }

 SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
 SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
 SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
 SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
 SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

 SDL_Surface* ic = SDL_LoadBMP("res\\img\\icon.bmp");
 Uint8 mask[32*4];
 for(int i=0;i<32;++i)
  for(int j=0;j<4;++j) mask[i*4+j]=0b11111111;
 SDL_WM_SetIcon(ic, mask);

 surface = SDL_SetVideoMode(w, h, bits, surface_params);
 if(!surface) {
  string e = "Unable to set videomode ("; e+=SDL_GetError(); e+=")";
  cerr << "[VIDEOMODE REQUESTED = " << w << "x" << h << "]\n";
  throw e;
 }

 glShadeModel(GL_SMOOTH);
 glCullFace(GL_BACK);
 glFrontFace(GL_CCW);
 glEnable(GL_CULL_FACE);

 glClearColor(0, 0, 0, 1.0);
 glViewport(0, 0, w, h);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(0,w,h,0,-1,0);

 SDL_GL_SwapBuffers();

 if(new_screen!=0) delete new_screen;
 new_screen = 0;
 if(current_screen!=0) delete current_screen;
 current_screen = create_screen(SCREENID_DEFAULT);
 done = false;
}

const int TICKS_PER_SECOND = 60;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 5;

void Game::loop() {
 DWORD next_game_tick = GetTickCount();
 DWORD prev = GetTickCount();
 int updates = 0;
 int redraws = 0;
 while(!done) {
  DWORD curr = GetTickCount();
  if(curr-prev >= 1000) {
   string caption = "FPS: ";
   char integer[15];
   itoa(redraws, integer, 10);
   caption += string(integer);
   caption += " / ";
   itoa(updates, integer, 10);
   caption += string(integer);
   SDL_WM_SetCaption(caption.c_str(), NULL );
   prev = curr;
   updates = 0;
   redraws = 0;
  }

  int loops = 0;
  while(GetTickCount()>=next_game_tick && loops<MAX_FRAMESKIP) {
   input.poll_events();
   current_screen->update();

   next_game_tick += SKIP_TICKS;
   ++loops;
   ++updates;
  }

  //float interpolation = float(GetTickCount() + SKIP_TICKS - next_game_tick) / float(SKIP_TICKS);
#ifdef DBG_HARDWARE_CURSOR
  SetCursor(LoadCursorFromFile(DBG_HARDWARE_CURSOR));
#endif
  current_screen->redraw();
  ++redraws;
  if(new_screen) {
   if(!current_screen->is_static()) delete current_screen;
   current_screen = new_screen;
   new_screen = 0;
   input.unpause();
   current_screen->start();
  }
 }
}

void Game::stop() { done=true; }
void Game::open_screen(Screen* s) { if(s!=current_screen && s!=0) new_screen = s; }
void Game::open_screen(ScreenID sid, bool recreate) {
 clean_drown_memory_up();
 if(!recreate && static_screens.count(sid)!=0) new_screen = static_screens[sid];
 else {
  Screen* prev = new_screen;
  Screen* created = create_screen(sid);
  if(created!=0) new_screen = created;
  if(new_screen!=prev) {
   if(static_screens.count(sid)!=0) {
    Screen* s = static_screens[sid];
    if(s==current_screen) drown_static_screens.push_back(s);
    else delete s;
    static_screens.erase(sid);
   }
   if(new_screen->is_static()) static_screens[sid] = new_screen;
  }
 }
}
Screen* Game::create_screen(ScreenID sid) {
 switch(sid) {
  case s_FIRST_SCREEN: return new First_Screen(this, surface, &loader, &input); break;
 }
 return 0;
}

void Game::save(string fn) {
 fn="saves\\"+fn;
 ofstream fout(fn.c_str());
 for(map<ScreenID,Screen*>::iterator i=static_screens.begin(); i!=static_screens.end(); ++i)
  if(i->second) {
   fout << int(i->first) << "\n";
   i->second->save_state(fout);
  }

 fout << "-1\n"; //end of screen infos
 _state.save(fout);
 fout << int(current_screen?current_screen->ID():SCREENID_DEFAULT) << "\n";
 fout.close();
}

void Game::load(string fn) {
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
 _state.load(fin);
 fin >> s;
 sid = ScreenID(s);
 open_screen((static_screens.count(sid)==0?SCREENID_DEFAULT:sid));
 fin.close();
}

/*GETTERS*/

int Game::w() { return surface->w; }
int Game::h() { return surface->h; }
ScreenID Game::sid() { return (current_screen?current_screen->ID():SCREENID_DEFAULT); }

}
