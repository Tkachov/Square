#ifndef FIRST_SCREEN_H
#define FIRST_SCREEN_H

#include "..\Engine\screen.h"
#include "..\Engine\Objects\button.h"
#include "..\Engine\Objects\image.h"
using namespace Engine;

class First_Screen: public Screen
{
 private:
  bool enabled;
  Button* add_button(int x, int y, string text, functor* = 0, int = 0);

  friend class Functor<First_Screen>;
  void fnc_exit();

 protected:
  virtual void load();

 public:
  First_Screen(Game* game, Loader* ld, Input* in);
  virtual ~First_Screen();
};

#endif // FIRST_SCREEN_H
