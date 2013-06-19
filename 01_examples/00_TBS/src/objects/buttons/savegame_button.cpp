#include "savegame_button.h"

SaveGame_Button::SaveGame_Button(string text, functor* f, functor* df, Loader* loader, int x, int y, int pr):
 Button(f), _date(0,""), double_click_check(0), double_func(df), selected(0) {
  _x=x;
  _y=y;
  _priority=pr;

  SDL_Color c; c.r=c.g=c.b=255;
  label = Text(loader->load_font("Tahoma",16), text, 0, c, 3, 2, 1);
  _date = Text(loader->load_font("Tahoma",10), "", 0, c, 3, 26, 1);

  redraw();
 }

SaveGame_Button::~SaveGame_Button() {
 if(double_func) delete double_func;
}

void SaveGame_Button::update_label() {}

void SaveGame_Button::redraw() {
 update_label();
}

void SaveGame_Button::update(Input* input) {
 if(double_click_check) --double_click_check;
 int mx = input->mouse_x();
 int my = input->mouse_y();
 int ns = 0;
 if(disabled) ns=3;
 else {
  if(!input->paused() && !input->mouse_eaten(0)) {
   bool intersects = ((mx > _x && mx < _x + width) && (my > _y && my < _y + height));
   if(intersects) {
    input->mouse_eat(0);
    if(input->mouse_release(1, true)) {
     if(double_click_check==0) double_click_check = 20;
     else {
      if(double_func!=0) (*double_func)();
      double_click_check=0;
     }
     if(func!=0) {
      selected=1;
      (*func)();
     }
    }
    ns = (input->mouse_hold(1, true)?2:1);
   }
  }
 }
 bool rd = (current_state!=ns);
 current_state = ns;
 if(rd) redraw();
}

void SaveGame_Button::draw(SDL_Surface* s) {
 if(selected&&!disabled) {
  glColor4f(0.6,0,0.1, 0.2+0.15*selected);
  draw_rectangle(_x,_y, width, height);
 } else {
  switch(current_state) {
   case 0: glColor4f(0,0,0, 0); break; //off
   case 1: glColor4f(0.4,0,0, 0.4); break; //over
   case 2: glColor4f(0.2,0.01,0.01, 0.4); break; //pressed
   case 3: glColor4f(1,1,1, 0.45); break; //disabled
  }
 }
 draw_rectangle(_x,_y, width, height);
 label.draw(_x+label.x(),_y+label.y(),s);
 _date.draw(_x+_date.x(),_y+_date.y(),s);
 glColor4f(0.45,0.588,1,1);
 draw_rectangle(_x,_y+height,width,1);
}
