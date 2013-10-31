#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "../importgl.h"
#include "Application.h"
#include "Loop.h"
#include "settings.h"

namespace Engine {

Application::Application() {
 //init GL
 importGLInit();

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
 importGLDeinit();
}

void Application::load_options(int argc, char** argv) {
 options.clear();

 //apply default settings
 options.displace("width", DEFAULT_WIDTH);
 options.displace("height", DEFAULT_HEIGHT);
 options.displace("fullscreen", DEFAULT_FULLSCREEN);
 options.displace("language", DEFAULT_LANGUAGE);

 //TODO: apply arguments settings

 //apply config settings
 #ifdef CONFIG_FILENAME
  options.push_table(CONFIG_FILENAME);
 #endif
}

void Application::work(int argc, char** argv) {
 Controller controller(&options, &state);

 for(Loop_Iteraton i=LOOP_ITERATION_USUAL;;) {
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
  } catch (Loop_Iteraton next_iteration) {
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
