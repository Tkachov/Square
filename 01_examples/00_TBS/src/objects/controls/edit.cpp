#include "edit.h"

Edit::Edit(Text* t, functor* f, Loader* loader, int x, int y, int w, int pr):
 Button(f), width(w), height(21), txt(t), selected(false), frame(0), delay(20), checker(0) {
  _x=x;
  _y=y;
  _priority=pr;

  /*set_states(
   loader->load_sprite("res\\img\\GUI\\buttons\\blue_button\\blue_button_up.sprite"),
   loader->load_sprite("res\\img\\GUI\\buttons\\blue_button\\blue_button_over.sprite"),
   loader->load_sprite("res\\img\\GUI\\buttons\\blue_button\\blue_button_up.sprite"),
   loader->load_sprite("res\\img\\GUI\\buttons\\blue_button\\blue_button_off.sprite")
  );*/
 }

Edit::~Edit() {
 if(checker) delete checker;
}

void Edit::check_keys(Input* input) {
 if(input&&!input->paused()) {
  if(input->key_release(SDLK_RETURN)) selected=false;
  if(checker!=0) (*checker)();
  else if(txt) {
   bool updated = false;
   if(input->key_press(SDLK_BACKSPACE)) {
    if(txt->text().length()>0) {
     txt->set_text(txt->text().substr(0,txt->text().length()-1));
     updated=true;
    }
   } else if(input->key_press(SDLK_RETURN)||input->key_press(SDLK_KP_ENTER)||input->key_press(SDLK_TAB)||input->key_press(SDLK_ESCAPE)) {
    /*ignore these, they throw ugly characters*/
   } else {
    for(unsigned int i=0; i<input->keyboard_string.size(); ++i) {
     txt->set_text(txt->text()+input->keyboard_string[i].unicode);
     updated=true;
    }
   }

   if(updated&&func!=0) (*func)();
  }
 }
}

void Edit::update(Input* input) {
 if(txt&&txt->img()) height=txt->img()->h();
 if(selected) check_keys(input);
 if(++frame>delay) frame=0;
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
     selected=!selected;
     input->repeating(selected);
    }
    ns = (input->mouse_hold(1, true)?2:1);
   }
  }
 }
 bool rd = (current_state!=ns);
 current_state = ns;
 if(rd) redraw();
}

void Edit::draw(SDL_Surface* s) {
 if(selected&&!disabled) {
  glColor4f(0.6,0,0.1, 0.6);
 } else {
  switch(current_state) {
   case 0: glColor4f(0,0,0, 0.4); break; //off
   case 1: glColor4f(0.4,0,0, 0.4); break; //over
   case 2: glColor4f(0.2,0.01,0.01, 0.4); break; //pressed
   case 3: glColor4f(1,1,1, 0.45); break; //disabled
  }
 }
 int margin = 4;
 draw_rectangle(_x-margin,_y, width+2*margin, height+1);
 //borders here
 glColor4f(0.1,0.1,0.1,1);
 draw_rectangle(_x-margin,_y,1,height+1);
 draw_rectangle(_x-margin,_y,width+2*margin,1);
 draw_rectangle(_x-margin,_y+height,width+2*margin,1);
 draw_rectangle(_x+width+margin,_y,1,height+1);
 //cursor
 if(selected&&!disabled&&txt&&frame<delay/2) {
  int shift = (txt->img()?txt->img()->w():0);
  glColor4f(1,1,1,0.75);
  draw_rectangle(_x+shift+2,_y+3,1,height-5);
  glColor4f(1,1,1,0.35);
  draw_rectangle(_x+shift+3,_y+3,1,height-5);
 }
}
