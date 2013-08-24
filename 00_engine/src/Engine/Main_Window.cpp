#include <string>
#include <SDL2\SDL_image.h>
#include <GL/gl.h>
#include "Logger.h"
#include "Main_Window.h"
#include "settings.h"

namespace Engine {

Main_Window* Main_Window::singletone = 0;

Main_Window::Main_Window() {
 if(singletone) throw "Unable to create new Main_Window: Main_Window is a singletone.";
 singletone = this;

 window = 0; //pointer
 fullscreen = 0; //bitmask
 width = height = 0; //usual int
}

Main_Window::~Main_Window() {
 destroy();
}

/* PRIVATE */

void Main_Window::set_GL_viewport(int w, int h) {
 glClearColor(0, 0, 0, 1.0);
 glViewport(0, 0, w, h);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(0, w, h, 0, -1, 0);
}

/* STATIC */

void Main_Window::create(const char* title, int x, int y, int w, int h, int flags) {
 if(!singletone) return;

 destroy(); //clean up if necessary

 //create window
 singletone->window = SDL_CreateWindow(title, x, y, w, h, flags);
 if(!singletone->window) {
  string e = "Unable to create window ("; e+=SDL_GetError(); e+=")";
  Logger::err << "[VIDEOMODE REQUESTED = " << w << "x" << h << "]\n";
  throw e;
 }

 //remember fullscreen and size values
 if((flags&SDL_WINDOW_FULLSCREEN_DESKTOP) == SDL_WINDOW_FULLSCREEN_DESKTOP) singletone->fullscreen = SDL_WINDOW_FULLSCREEN_DESKTOP;
 else if((flags&SDL_WINDOW_FULLSCREEN) == SDL_WINDOW_FULLSCREEN) singletone->fullscreen = SDL_WINDOW_FULLSCREEN;
 else singletone->fullscreen = 0;

 SDL_GetWindowSize(singletone->window, &singletone->width, &singletone->height);

 //add icon
 SDL_Surface* icon = 0;
 #ifdef WINDOW_ICON_BMP
  icon = SDL_LoadBMP(WINDOW_ICON_BMP);
 #else
  #ifdef WINDOW_ICON_PNG
   icon = IMG_Load(WINDOW_ICON_PNG);
  #endif
 #endif
 if(icon) {
  SDL_SetWindowIcon(singletone->window, icon);
  SDL_FreeSurface(icon);
 }

 //create GL context and prepare GL
 singletone->glcontext = SDL_GL_CreateContext(singletone->window);

 SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
 SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
 SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
 SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
 SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

 glShadeModel(GL_SMOOTH);
 glCullFace(GL_BACK);
 glFrontFace(GL_CCW);
 glEnable(GL_CULL_FACE);

 singletone->set_GL_viewport(singletone->width, singletone->height);
 swap();
}

void Main_Window::destroy() {
 if(!singletone || !singletone->window) return;

 SDL_GL_DeleteContext(singletone->glcontext);
 SDL_DestroyWindow(singletone->window);

 singletone->window = 0;
}

void Main_Window::swap() {
 if(!singletone || !singletone->window) return;

 SDL_GL_SwapWindow(singletone->window);
}

Uint32 Main_Window::get_fullscreen() {
 return (singletone?singletone->fullscreen:0);
}

int Main_Window::get_width(bool refresh) {
 if(!singletone) return 0;

 if(refresh && singletone->window)
  SDL_GetWindowSize(singletone->window, &singletone->width, &singletone->height);
 return singletone->width;
}

int Main_Window::get_height(bool refresh) {
 if(!singletone) return 0;

 if(refresh && singletone->window)
  SDL_GetWindowSize(singletone->window, &singletone->width, &singletone->height);
 return singletone->height;
}

void Main_Window::set_fullscreen(Uint32 flag) {
 if(!singletone || !singletone->window) return;

 int w = singletone->width, h = singletone->height;

 //set fullscreen
 if(flag==SDL_WINDOW_FULLSCREEN_DESKTOP || flag==SDL_WINDOW_FULLSCREEN) singletone->fullscreen = flag;
 else singletone->fullscreen = 0;

 SDL_SetWindowFullscreen(singletone->window, singletone->fullscreen);
 SDL_GetWindowSize(singletone->window, &singletone->width, &singletone->height);

 //check if size has changed and change GL viewport if necessary
 if(w!=singletone->width || h!=singletone->height)
  singletone->set_GL_viewport(singletone->width, singletone->height);
}

void Main_Window::set_title(string title) {
 if(!singletone || !singletone->window) return;

 SDL_SetWindowTitle(singletone->window, title.c_str());
}

}
