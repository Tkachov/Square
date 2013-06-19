#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "..\Engine\screen.h"
#include "..\Engine\Objects\button.h"
#include "..\Engine\Objects\image.h"
#include "..\Engine\Objects\fade_effect.h"
using namespace Engine;

class Main_Menu: public Screen
{
 private:
  bool enabled;
  Button* add_button(int x, int y, string text, functor* = 0, int = 0);

  friend class Functor<Main_Menu>;
  void fnc_goto_start();
  void fnc_start();
  void fnc_load();
  void fnc_options();
  void fnc_exit();

 protected:
  virtual void load();

 public:
  Main_Menu(Game* game, SDL_Surface* surf, Loader* ld, Input* in);
  virtual ~Main_Menu();
};

#endif // MAIN_MENU_H
