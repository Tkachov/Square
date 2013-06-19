#ifndef BUTTON_H
#define BUTTON_H

#include "object.h"
#include "sprite.h"
#include "image.h"
#include "text.h"
#include "..\functor.h"

namespace Engine { namespace Objects {

class Button: public Object
{
protected:
 Sprite states[4];
 int current_state;
 bool disabled;
 Text label;
 functor* func;
 bool pixel_perfect_intersection;
 int holding_clicks_delay;
 int delay;

 void redraw();
 void update_label();

public:
 Button(functor* = 0);
 virtual ~Button();

 virtual void draw(SDL_Surface*);
 virtual void update(Input*);

 void set_up_state(Sprite);
 void set_over_state(Sprite);
 void set_pressed_state(Sprite);
 void set_disabled_state(Sprite);
 void set_states(Sprite,Sprite,Sprite,Sprite);

 void set_font(TTF_Font*);
 void set_color(SDL_Color);
 void set_text(string);
 void set_label(TTF_Font*, SDL_Color, string);

 void set_func(functor*);
 void set_pixel_perfect(bool);
 void set_disabled(bool);
 void set_holding_click_delay(int);

 bool is_disabled() { return disabled; }
};

} }

#endif // BUTTON_H
