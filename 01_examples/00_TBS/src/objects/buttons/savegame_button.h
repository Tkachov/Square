#ifndef SAVEGAME_BUTTON_H
#define SAVEGAME_BUTTON_H

#include "..\..\Engine\Objects\button.h"
#include "..\..\Engine\functor.h"
#include "..\..\Engine\loader.h"
using namespace Engine;
using namespace Engine::Objects;

class SaveGame_Button: public Button
{
 private:
  Text _date;
  int double_click_check;
  functor* double_func;
  static const int width = 363;
  static const int height = 44;

  void redraw();
  void update_label();

 public:
  SaveGame_Button(string text, functor*, functor*, Loader*, int x, int y, int pr = 0);
  virtual ~SaveGame_Button();

  virtual void update(Input*);
  virtual void draw(SDL_Surface*);

  int selected;
  string slotname;
  string savename() { return label.text(); }
  string savedate() { return _date.text(); }

  void set_date(string v) { _date.set_text(v); redraw(); }
};

#endif // SAVEGAME_BUTTON_H
