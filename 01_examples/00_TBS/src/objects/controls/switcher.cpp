#include "switcher.h"

Switcher::Switcher(Text* txt, string v1, string v2, bool first, int x, int y, int pr):
 Object(x,y,pr), label(txt), t_true(v1), t_false(v2), current(first), current_state(0), disabled(false) {
  color[0].r=color[0].g=color[0].b=200;
  color[1].r=color[1].g=color[1].b=255;
  color[2].r=color[2].g=color[2].b=255;
  color[3].r=color[3].g=color[3].b=120;
  if(label) {
   label->set_text((current?t_true:t_false));
   label->set_color(color[0]);
  }
 }

Switcher::~Switcher() {
 if(label) delete label;
}

void Switcher::update(Input* i) {
 if(i==0||i->paused()) return;
 int ns = 0;
 if(disabled) ns=3;
 else {
  int mx = i->mouse_x();
  int my = i->mouse_y();
  if(!i->mouse_eaten(0)) {
   bool intersects = ((mx > _x && mx < _x+state[current_state].w()) && (my > _y && my < _y+state[current_state].h()) && state[current_state].is_intersected(mx-_x,my-_y));
   if(label) {
    int ex = _x + label->x();
    int ey = _y + label->y();
    int ew = 0, eh = 0;
    if(label->img()) {
     ew = label->img()->w();
     eh = label->img()->h();
    }
    intersects = (intersects||((mx > ex && mx < ex+ew) && (my > ey && my < ey+eh)));
   }
   if(intersects) {
    i->mouse_eat(0);
    ns = (i->mouse_hold(1)?2:1);
    if(i->mouse_release(1, true)) {
     current=!current;
     if(label) label->set_text((current?t_true:t_false));
    }
   }
  }
 }
 if(ns<0||ns>3) ns=0;
 if(label) {
  if(ns!=current_state)
   label->set_color(color[ns]);
  label->update(i);
 }
 current_state = ns;
}

void Switcher::draw(SDL_Surface* s) {
 state[current_state].draw(_x,_y,s);
 if(label) label->draw(_x+label->x(), _y+label->y(), s);
}
