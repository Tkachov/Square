#include <string>
#include <SDL_image.h>
#include "../importgl.h"
#include "Logger.h"
#include "Main_Window.h"
#include "Resources.h"
#include "settings.h"

namespace Engine {

Main_Window* Main_Window::singletone = 0;

Main_Window::Main_Window() {
 if(singletone) throw "Unable to create new Main_Window: Main_Window is a singletone.";
 singletone = this;

 window = 0;
 fullscreen = fs_WINDOWED;
 projection_width = viewport_width = 800;
 projection_height = viewport_height = 600;
}

Main_Window::~Main_Window() {
 destroy();
}

/* PRIVATE */

void Main_Window::set_GL_viewport() {
 glClearColor(0, 0, 0, 1.0);
 glViewport(0, 0, viewport_width, viewport_height);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();

 #ifdef ANDROID_NDK
  glOrthof(0, projection_width, projection_height, 0, -1, 0);
 #else
  glOrtho(0, projection_width, projection_height, 0, -1, 0);
 #endif
}

/* STATIC */

void Main_Window::create(const char* title, int x, int y, int w, int h, string fullscreen, int flags) {
 if(!singletone) return;

 destroy(); //clean up if necessary

 flags &= ~(SDL_WINDOW_FULLSCREEN | SDL_WINDOW_FULLSCREEN_DESKTOP); //remove fullscreen flags if there are any
 flags |= SDL_WINDOW_OPENGL; //require OpenGL

 //select fullscreen mode
 Fullscreen_Mode mode = fs_WINDOWED;
 if(fullscreen == "1") mode = fs_FULLSCREEN_STRETCHED;
 else if(fullscreen == "2") mode = fs_FULLSCREEN_WHOLE_SCREEN;
 else if(fullscreen == "3") mode = fs_WINDOWED_STRETCHED;
 else if(fullscreen == "4") mode = fs_WINDOWED_WHOLE_SCREEN;

 #ifdef ANDROID_NDK
  if(mode == fs_WINDOWED || mode == fs_FULLSCREEN_STRETCHED) mode = fs_WINDOWED_STRETCHED;
 #endif

 if(mode == fs_FULLSCREEN_STRETCHED) flags |= SDL_WINDOW_FULLSCREEN;
 else if(mode == fs_FULLSCREEN_WHOLE_SCREEN) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

 //create window
 singletone->window = SDL_CreateWindow(title, x, y, w, h, flags);
 if(!singletone->window) {
  string e = "Unable to create window ("; e+=SDL_GetError(); e+=")";
  Logger::err << "[VIDEOMODE REQUESTED = " << w << "x" << h << "]\n";
  throw e;
 }

 //set requested fullscreen mode
 singletone->fullscreen = mode;
 set_fullscreen(singletone->fullscreen);

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

 singletone->set_GL_viewport();
 swap();

 #if DEBUG_LOG_WINDOW_MODE == 1
  Logger::log << "\n###WINDOW CREATION:\n";
  Logger::log << " size: " << singletone->projection_width << "*" << singletone->projection_height << "\n";
  Logger::log << " desired size: " << w << "*" << h << "\n";
  Logger::log << " screen size: " << singletone->viewport_width << "*" << singletone->viewport_height << "\n";
  Logger::log << " fullscreen: ";
  if((flags&SDL_WINDOW_FULLSCREEN_DESKTOP) == SDL_WINDOW_FULLSCREEN_DESKTOP) Logger::log << "FULLSCREEN_DESKTOP";
  else if((flags&SDL_WINDOW_FULLSCREEN) == SDL_WINDOW_FULLSCREEN) Logger::log << "FULLSCREEN";
  else Logger::log << "WINDOWED";
  Logger::log << "\n###\n\n";
 #endif
}

void Main_Window::destroy() {
 if(!singletone || !singletone->window) return;

 //as we're goin' to delete GL context, we have to free all GL-textures
 Resources::free_textures();

 SDL_GL_DeleteContext(singletone->glcontext);
 SDL_DestroyWindow(singletone->window);

 singletone->window = 0;
}

void Main_Window::swap() {
 if(!singletone || !singletone->window) return;

 SDL_GL_SwapWindow(singletone->window);
}

void Main_Window::update_window_size() {
 if(!singletone || !singletone->window) return;

 //remember new size (which should be screen size)
 SDL_GetWindowSize(singletone->window, &singletone->viewport_width, &singletone->viewport_height);

 //now update viewport/projection for that size
 if(singletone->fullscreen != fs_WINDOWED_STRETCHED && singletone->fullscreen != fs_WINDOWED_WHOLE_SCREEN)
  SDL_SetWindowSize(singletone->window, singletone->projection_width, singletone->projection_height);
 singletone->set_GL_viewport();
}

Fullscreen_Mode Main_Window::get_fullscreen() {
 return (singletone?singletone->fullscreen:fs_WINDOWED);
}

int Main_Window::get_viewport_width(bool refresh) {
 if(!singletone) return 0;

 if(refresh && singletone->window)
  SDL_GetWindowSize(singletone->window, &singletone->viewport_width, &singletone->viewport_height);
 return singletone->viewport_width;
}

int Main_Window::get_viewport_height(bool refresh) {
 if(!singletone) return 0;

 if(refresh && singletone->window)
  SDL_GetWindowSize(singletone->window, &singletone->viewport_width, &singletone->viewport_height);
 return singletone->viewport_height;
}

int Main_Window::get_projection_width() {
 return (singletone?singletone->projection_width:0);
}

int Main_Window::get_projection_height() {
 return (singletone?singletone->projection_height:0);
}

void Main_Window::set_fullscreen(Fullscreen_Mode mode) {
 if(!singletone || !singletone->window) return;

 set_fullscreen(mode, singletone->projection_width, singletone->projection_height);
}

void Main_Window::set_fullscreen(Fullscreen_Mode mode, int new_width, int new_height) {
 if(!singletone || !singletone->window) return;

 #ifdef ANDROID_NDK
  if(mode == fs_WINDOWED || mode == fs_FULLSCREEN_STRETCHED) mode = fs_WINDOWED_STRETCHED;
 #endif

 Uint32 old_fullscreen_flag = 0;
 Uint32 new_fullscreen_flag = 0;

 if(singletone->fullscreen == fs_FULLSCREEN_STRETCHED) old_fullscreen_flag = SDL_WINDOW_FULLSCREEN;
 else if(singletone->fullscreen == fs_FULLSCREEN_WHOLE_SCREEN) old_fullscreen_flag = SDL_WINDOW_FULLSCREEN_DESKTOP;

 if(mode == fs_FULLSCREEN_STRETCHED) new_fullscreen_flag = SDL_WINDOW_FULLSCREEN;
 else if(mode == fs_FULLSCREEN_WHOLE_SCREEN) new_fullscreen_flag = SDL_WINDOW_FULLSCREEN_DESKTOP;

 if(mode == fs_WINDOWED_STRETCHED || mode == fs_WINDOWED_WHOLE_SCREEN) { //emulate fullscreen using borderless window with size of display
  int index = SDL_GetWindowDisplayIndex(singletone->window);
  SDL_Rect bounds;
  SDL_GetDisplayBounds(index, &bounds);

  SDL_SetWindowBordered(singletone->window, SDL_FALSE);
  SDL_SetWindowPosition(singletone->window, bounds.x, bounds.y);
  SDL_SetWindowSize(singletone->window, bounds.w, bounds.h);
 }

 //set fullscreen
 if(old_fullscreen_flag != new_fullscreen_flag)
  SDL_SetWindowFullscreen(singletone->window, singletone->fullscreen);
 SDL_GetWindowSize(singletone->window, &singletone->viewport_width, &singletone->viewport_height); //update viewport size
 singletone->fullscreen = mode;

 //update projection size
 if(mode == fs_WINDOWED || mode == fs_FULLSCREEN_WHOLE_SCREEN || mode == fs_WINDOWED_WHOLE_SCREEN) {
  singletone->projection_width = singletone->viewport_width;
  singletone->projection_height = singletone->viewport_height;
 } else {
  singletone->projection_width = new_width;
  singletone->projection_height = new_height;
 }

 //update GL viewport if necessary
 singletone->set_GL_viewport();
}

void Main_Window::set_title(string title) {
 if(!singletone || !singletone->window) return;

 SDL_SetWindowTitle(singletone->window, title.c_str());
}

}
