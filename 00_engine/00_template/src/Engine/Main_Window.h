#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <SDL.h>

namespace Engine {

enum Fullscreen_Mode {
 fs_WINDOWED = 1,                //window mode
 fs_FULLSCREEN_STRETCHED = 2,    //SDL's "fake" fullscreen mode (SDL_WINDOW_FULLSCREEN)
 fs_FULLSCREEN_WHOLE_SCREEN = 4, //SDL's "real" fullscreen mode (SDL_WINDOW_FULLSCREEN_DESKTOP)
 fs_WINDOWED_STRETCHED = 8,      //borderless window of display size with stretched contents ("fake" fullscreen emulated)
 fs_WINDOWED_WHOLE_SCREEN = 16   //borderless window of display size ("real" fullscreen emulated)
};

class Main_Window
{
 private:
  static Main_Window* singletone;

  SDL_GLContext glcontext;
  SDL_Window* window;
  Fullscreen_Mode fullscreen;
  int viewport_width, viewport_height;
  int projection_width, projection_height;

  void set_GL_viewport();

 public:
  Main_Window();
  ~Main_Window();

  static void create(const char* title, int x, int y, int w, int h, string fullscreen, int flags = 0);
  static void destroy();
  static void swap();
  static void update_window_size();

  static Fullscreen_Mode get_fullscreen();
  static int get_viewport_width(bool refresh = false);
  static int get_viewport_height(bool refresh = false);
  static int get_projection_width();
  static int get_projection_height();

  static void set_fullscreen(Fullscreen_Mode mode);
  static void set_fullscreen(Fullscreen_Mode mode, int new_projection_width, int new_projection_height);
  static void set_title(string title);

};

}

#endif // MAIN_WINDOW_H
