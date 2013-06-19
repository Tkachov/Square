#ifndef OPTIONS_WINDOW_H
#define OPTIONS_WINDOW_H

#include "..\..\Engine\Objects\window.h"
#include "..\controls\options_scroller.h"
#include "..\buttons\blue_button.h"
#include "..\controls\switcher.h"
using namespace Engine;
using namespace Engine::Objects;

class Options_Window: public Window
{
 private:
  bool no_restart;
  Text* tx_language;
  Options_Scroller* sc_language;
  //final buttons
  Switcher* sw_restart;
  Blue_Button* bt_apply;
  Blue_Button* bt_cancel;

  friend class Functor<Options_Window>;
  void fnc_apply();
  void fnc_cancel();

 protected:
  void find_languages();
  virtual void load();

 public:
  Options_Window(Game* g, Loader* l, int pr = 0, bool = false);
  virtual ~Options_Window();

  virtual void update();
  virtual void update(Input*);
};

#endif // OPTIONS_WINDOW_H
