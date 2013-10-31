#include "Button.h"
#include "../Input.h"
#include "../Data/Frame.h"
using Engine::Data::Frame;

namespace Engine { namespace Entities {

Button::Button(Controller* controller, functor* f):
 Entity(controller), func(f), label(controller),
 states({Sprite(controller), Sprite(controller), Sprite(controller), Sprite(controller)})
{
 current_state=0;
 disabled=false;
 delay=holding_clicks_delay=0;
}

Button::~Button() {
 if(func) delete func;
}

void Button::center_label() {
 if(label.label()) {
  label.set_x((states[current_state].width()-label.label()->width())/2);
  label.set_y((states[current_state].height()-label.label()->height())/2);
 }
}

void Button::refresh() {
 center_label();
}

void Button::redraw(int xs, int ys) {
 states[current_state].redraw(xs+_x, ys+_y);
 label.redraw(xs+_x, ys+_y);
}

void Button::update(int x_offset, int y_offset) {
 int mx = Input::mouse_x()-x_offset;
 int my = Input::mouse_y()-y_offset;
 int ns = 0;
 if(delay) --delay;
 if(disabled) ns=3;
 else {
  if(!Input::paused() && !Input::mouse_eaten(0) && states[current_state].is_intersected(mx-_x, my-_y)) {
   Input::mouse_eat(0);
   bool hold = Input::mouse_hold(1, true);
   bool press = (delay==0 && (Input::mouse_release(1, true) || (hold && holding_clicks_delay)));
   if(func!=0 && press) {
    (*func)();
    delay=holding_clicks_delay;
   }
   ns=(hold?2:1);
  }
 }

 bool need_refresh=(current_state!=ns);
 current_state=ns;
 if(need_refresh) refresh();
}

//{ SETTERS

//{ STATES

void Button::set_up_state(Sprite s) {
 states[0]=s;
}

void Button::set_over_state(Sprite s) {
 states[1]=s;
}

void Button::set_pressed_state(Sprite s) {
 states[2]=s;
}

void Button::set_disabled_state(Sprite s) {
 states[3]=s;
}

void Button::set_states(Sprite u, Sprite o, Sprite p, Sprite d) {
 states[0]=u;
 states[1]=o;
 states[2]=p;
 states[3]=d;
}

//}

//{ LABEL

void Button::set_color(SDL_Color c) {
 label.set_color(c);
}

void Button::set_font(TTF_Font* f) {
 label.set_font(f);
 center_label();
}

void Button::set_text(string t) {
 label.set_text(t);
 center_label();
}

void Button::set_label(SDL_Color c, TTF_Font* f, string t) {
 label.set_color(c);
 label.set_font(f);
 set_text(t); //centers label after assignment
}

//}

void Button::set_disabled(bool d) {
 disabled=d;
}

void Button::set_holding_click_delay(int v) {
 holding_clicks_delay=v;
}

void Button::set_func(functor* f) {
 if(func!=f && f!=0) {
  if(func) delete func;
  func = f;
 }
}

//}

} }
