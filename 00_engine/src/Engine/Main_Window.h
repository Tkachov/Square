#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <SDL2\SDL.h>

namespace Engine {

class Main_Window
{
 private:
  static Main_Window* singletone;

  SDL_GLContext glcontext;
  SDL_Window* window;
  Uint32 fullscreen;
  int width;
  int height;

  void set_GL_viewport(int w, int h);

 public:
  Main_Window();
  ~Main_Window();

  static void create(const char* title, int x, int y, int w, int h, int flags);
  static void destroy();
  static void swap();

  static Uint32 get_fullscreen();
  static int get_width(bool refresh = false);
  static int get_height(bool refresh = false);

  static void set_fullscreen(Uint32 flag);
  static void set_title(string title);

};

}

#endif // MAIN_WINDOW_H
