#ifndef BUTTON_H
#define BUTTON_H

#include "Entity.h"
#include "Sprite.h"
#include "Text.h"
#include "../Functor.h"

namespace Engine { namespace Entities {

class Button: public Entity
{
 private:
  int current_state;
  int delay;
  bool disabled;
  functor* func;
  int holding_clicks_delay;
  Text label;
  Sprite states[4];

  void center_label();
  void refresh();

 public:
  Button(Controller* controller, functor* func = 0);
  virtual ~Button();

  virtual void redraw(int x, int y);
  virtual void update(int x, int y);

  void set_up_state(Sprite s);
  void set_over_state(Sprite s);
  void set_pressed_state(Sprite s);
  void set_disabled_state(Sprite s);
  void set_states(Sprite u, Sprite o, Sprite p, Sprite d);

  void set_color(SDL_Color c);
  void set_font(TTF_Font* f);
  void set_text(string t);
  void set_label(SDL_Color clr, TTF_Font* fnt, string txt);

  void set_disabled(bool d);
  void set_func(functor* f);
  void set_holding_click_delay(int d);

  bool is_disabled() { return disabled; }
};

} }

#endif // BUTTON_H
