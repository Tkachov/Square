#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <string>
#include <vector>
using std::string;
using std::vector;

namespace Engine {

class Input
{
 public:
  struct keychar {
   string unicode;
   int keycode;
  };

  vector<keychar> keyboard_string;

 private:
  short int keys[SDLK_LAST];
  short int mouses[SDLK_LAST];
  bool mouse_ate[SDLK_LAST];
  bool keys_ate[SDLK_LAST];
  int mx, my;
  bool quit;
  bool pausing;

 public:
  Input();
  void poll_events();

  //getters
  short int key(int k);
  short int mouse(int k);
  int mouse_x();
  int mouse_y();
  bool mouse_eaten(int k);
  void mouse_eat(int k);
  bool key_eaten(int k);
  void key_eat(int k);
  bool terminate();
  bool paused();

  bool key_press(int k, bool eat = false);
  bool key_hold(int k, bool eat = false);
  bool key_release(int k, bool eat = false);

  bool mouse_press(int k, bool eat = false);
  bool mouse_hold(int k, bool eat = false);
  bool mouse_release(int k, bool eat = false);

  //setters
  void pause();
  void unpause();
  void repeating(bool);
};

}

#endif // INPUT_H
