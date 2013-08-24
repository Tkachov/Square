#ifndef INDEX_SCREEN_H
#define INDEX_SCREEN_H

#include "../Engine/Entities/Screen.h"
#include "../Engine/Entities/Button.h"
using namespace Engine;
using namespace Engine::Entities;
using namespace Engine::Global;

namespace Engine {

class Controller;

}

class Index_Screen: public Screen
{
 private:
  static const ScreenID _id = s_INDEX;

  Button* add_button(int x, int y, string text, functor* = 0, int = 0);

  friend class Functor<Index_Screen>;
  void fnc_exit();

  virtual void update_after_queue(int x, int y);

 public:
  Index_Screen(Engine::Controller* controller);

  virtual ScreenID id() { return _id; }
};

#endif // INDEX_SCREEN_H
