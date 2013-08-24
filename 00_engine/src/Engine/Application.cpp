#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Application.h"
#include "Logger.h"
#include "Loop.h"
#include "settings.h"

namespace Engine {

Application::Application() {
 //init SDL and it's subsystems
 __sdl_was_init = __img_was_init = __ttf_was_init = false;

 //init SDL main
 if(SDL_Init(SDL_INIT_VIDEO)!=0) {
  string e = "Unable to init SDL: "; e+=SDL_GetError();
  throw e;
 }
 __sdl_was_init = true;

 //init PNG
 int need=IMG_INIT_PNG;
 int init=IMG_Init(need);
 if((init&need) != need) {
  string e = "Unable to init required png support: "; e+=IMG_GetError();
  throw e;
 }
 __img_was_init = true;

 //init fonts
 if(TTF_WasInit()==0) {
  if(TTF_Init()<0) {
   string e = "Unable to init fonts support: "; e+=TTF_GetError();
   throw e;
  }
 }
 __ttf_was_init = true;
}

Application::~Application() {
 if(__ttf_was_init) TTF_Quit();
 if(__img_was_init) IMG_Quit();
 if(__sdl_was_init) SDL_Quit();
}

void Application::load_options(int argc, char** argv) {
 options.clear();

 //Apply default settings
 options.displace("width", DEFAULT_WIDTH);
 options.displace("height", DEFAULT_HEIGHT);
 options.displace("fullscreen", FULLSCREEN);
 options.displace("language", LANGUAGE);

 //TODO: apply arguments settings

 //Apply "config.txt" settings
 options.push_table("config.txt");
}

void Application::work(int argc, char** argv) {
 Controller controller(&options, &state);

 for(int i=LOOP_ITERATION_USUAL;;) {
  load_options(argc, argv);
  Loop loop(&controller);
  switch(i) {
   default:;
    //add cases that influence the game before starting
    //all cases that influence the game after previous iteration are in switch down there
  }
  try {
   loop();
   break;
  } catch (int next_iteration) {
   i=next_iteration;
   switch(next_iteration) {
    case LOOP_ITERATION_USUAL: state.clear(); break; //just relaunch
    case LOOP_ITERATION_SAVE_STATE: break;
    default:
     throw next_iteration; //main() is going to crash
   }
  }
 }
}

}
