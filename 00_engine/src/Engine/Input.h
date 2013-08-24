#ifndef INPUT_H
#define INPUT_H

#include <map>
#include <string>
#include <SDL2/SDL.h>
using std::map;
using std::string;

namespace Engine {

class Input
{
 private:
  static Input* input;

  map<SDL_Keycode, short int> keys;
  map<Uint8, short int> mouses;
  map<SDL_Keycode, bool> keys_ate;
  map<Uint8, bool> mouse_ate;

  int _mx, _my, _wx, _wy;
  bool _quit;
  bool _paused;

 public:
  static string keyboard_string;

  Input();
  void poll_events();

  //getters
  static short int key(SDL_Keycode k);
  static bool key_press(SDL_Keycode k, bool eat = false);
  static bool key_hold(SDL_Keycode k, bool eat = false);
  static bool key_release(SDL_Keycode k, bool eat = false);
  static bool key_eaten(SDL_Keycode k);

  static short int mouse(Uint8 b);
  static bool mouse_press(Uint8 b, bool eat = false);
  static bool mouse_hold(Uint8 b, bool eat = false);
  static bool mouse_release(Uint8 b, bool eat = false);
  static bool mouse_eaten(Uint8 b);

  static int mouse_x();
  static int mouse_y();
  static int wheel_x();
  static int wheel_y();

  static bool paused();
  static bool quit();

  //setters
  static void key_eat(SDL_Keycode k);
  static void mouse_eat(Uint8 b);

  static void pause();
  static void unpause();
};

}

#endif // INPUT_H
