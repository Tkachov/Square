#include "button.h"

namespace Engine { namespace Objects {

Button::Button(functor* f): Object(), current_state(0), disabled(false), label(NULL,""), func(f), pixel_perfect_intersection(true), holding_clicks_delay(0), delay(0) {};
Button::~Button() {
 if(func) delete func;
}

void Button::update(Input* input, int x_offset, int y_offset) {
 int mx = input->mouse_x() - x_offset;
 int my = input->mouse_y() - y_offset;
 int ns = 0;
 if(delay) --delay;
 if(disabled) ns=3;
 else {
  if(!input->paused() && !input->mouse_eaten(0)) {
   bool intersects = ((mx > _x && mx < _x + states[current_state].w()) && (my > _y && my < _y + states[current_state].h()));
   if(intersects && pixel_perfect_intersection) intersects = states[current_state].is_intersected(mx-_x,my-_y);
   //check pixel-perfect only if mouse is inside

   if(intersects) {
    input->mouse_eat(0);
    bool hold = input->mouse_hold(1, true);
    bool press = (delay==0 && (input->mouse_release(1, true) || (hold&&holding_clicks_delay)));
    if(func!=0 && press) {(*func)(); delay=holding_clicks_delay;}
    ns = (hold?2:1);
   }
  }
 }
 bool rd = (current_state!=ns);
 current_state = ns;
 if(rd) redraw();
}

void Button::set_up_state(Sprite s) {states[0] = s;}
void Button::set_over_state(Sprite s) {states[1] = s;}
void Button::set_pressed_state(Sprite s) {states[2] = s;}
void Button::set_disabled_state(Sprite s) {states[3] = s;}
void Button::set_states(Sprite u, Sprite o, Sprite p, Sprite d) {
 states[0] = u;
 states[1] = o;
 states[2] = p;
 states[3] = d;
}

void Button::update_label() {
 if(label.img()) {
  label.set_x((states[0].w() - label.img()->w())/2);
  label.set_y((states[0].h() - label.img()->h())/2);
 }
}
void Button::set_font(TTF_Font* f) {
 label.set_font(f);
 update_label();
}
void Button::set_color(SDL_Color c) { label.set_color(c); }
void Button::set_text(string t) {
 label.set_text(t);
 update_label();
}
void Button::set_label(TTF_Font* f, SDL_Color c, string t) {
 label.set_font(f);
 label.set_color(c);
 set_text(t);
}

void Button::set_func(functor* f) {
 if(func!=f && f!=0) {
  if(func) delete func;
  func = f;
 }
}

void Button::set_pixel_perfect(bool p) { pixel_perfect_intersection = p; }
void Button::set_disabled(bool d) { disabled = d; }
void Button::set_holding_click_delay(int v) { holding_clicks_delay = v; }

void Button::redraw() { update_label(); };

void Button::draw(int x, int y) {
 states[current_state].draw(x,y);
 label.draw(x+label.x(),y+label.y());
}

} }
