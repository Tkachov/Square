#include "popup_window.h"
#include "..\Engine\Data\string_table.h"
#include "..\Engine\Objects\button.h"
#include "..\Engine\Objects\text.h"

Popup_Window::Popup_Window(Game* g, Loader* l, int x, int y, int pr):
 Window(g, l, x, y, pr), offset_x(0), offset_y(0), follow(false) {
 add_object(new Image(*loader->load_texture("res\\img\\GUI\\first_screen\\window.png")));

 SDL_Color c;
 c.r=c.g=c.b=255;
 add_object(new Text(loader->load_font("Tahoma",12), String_Table::translate["window_caption"], 0, c, 6, 3));

 Button* close_button = new Button(new Functor<Popup_Window>(this, &Popup_Window::fnc_close));
 close_button->set_states(*loader->load_texture("res\\img\\GUI\\first_screen\\close.png"),
                          *loader->load_texture("res\\img\\GUI\\first_screen\\close_over.png"),
                          *loader->load_texture("res\\img\\GUI\\first_screen\\close_pressed.png"),
                          *loader->load_texture("res\\img\\GUI\\first_screen\\close_pressed.png"));
 close_button->set_x(302);
 close_button->set_y(4);
 add_object(close_button);
}

Popup_Window::~Popup_Window() {};

void Popup_Window::update(Input* i, int xo, int yo) {
 input = i;
 update(xo, yo);

 if(i && !i->paused()) {
  if(follow) {
   if(i->mouse(1)) {
    i->mouse_eat(1);
    _x = i->mouse_x()-offset_x;
    _y = i->mouse_y()-offset_y;
   } else follow = false;
  }
  if(i->mouse_x()>=_x && i->mouse_x()<=_x+320) {
   if(i->mouse_y()>=_y && i->mouse_y()<=_y+20) { //caption
    if(!i->mouse_eaten(1) && i->mouse(1) && i->mouse(1)<3) {
     i->mouse_eat(1);
     follow = true;
     offset_x = i->mouse_x() - _x;
     offset_y = i->mouse_y() - _y;
     set_priority(3);
    }
   } else if(i->mouse_y()>=_y+20 && i->mouse_y()<=_y+200)  {
    if(i->mouse_press(1,true)) set_priority(3);
    if(i->mouse(1)) i->mouse_eat(1);
   }
  }
 }
}

void Popup_Window::update(int xo, int yo) {
 if(_destroy||input==0) return;
 update_queue(xo, yo);
}

void Popup_Window::fnc_close() {
 disappear();
}
