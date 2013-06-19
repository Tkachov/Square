#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "..\Engine\Objects\object.h"
#include "..\Engine\Objects\button.h"
#include "..\Engine\Objects\image.h"
#include "..\Engine\screen.h"
#include "buttons\blue_button.h"
using namespace Engine;

class Pause_Menu: public Object, public Screen
{
 protected:
  Blue_Button* b_save;
  virtual void load();

  friend class Functor<Pause_Menu>;
  void fnc_continue();
  void fnc_save();
  void fnc_load();
  void fnc_options();
  void fnc_goto_menu();
  void fnc_exit();

 public:
  Pause_Menu(Game* gm, Loader* ld, int pr = 0);
  virtual ~Pause_Menu();

  virtual void update() {};
  virtual void redraw() {};
  virtual void update(Input*);
  virtual void draw(SDL_Surface*);

  void set_saving_enabled(bool v) {
   if(b_save) b_save->set_disabled(!v);
  }
};

#endif // PAUSE_MENU_H
