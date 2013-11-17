#include "Popup_Window.h"
#include "../Engine/Data/String_Table.h"
#include "../Engine/Entities/Button.h"
#include "../Engine/Entities/Text.h"
#include "../Engine/Input.h"
#include "../Engine/Resources.h"
using Engine::Data::String_Table;
using Engine::Entities::Button;
using Engine::Entities::Text;
using Engine::Input;
using Engine::Resources;

Popup_Window::Popup_Window(Controller* cont, int x, int y, int pr):
 Window(cont, x, y, false), offset_x(0), offset_y(0), follow(false) {
 set_priority(pr);
 add_entity(new Sprite(cont, *Resources::load_texture("res\\img\\GUI\\Index_Screen\\window.png")));

 add_entity(new Text(cont, Resources::load_font("Tahoma", 12), String_Table::translate["window_caption"], 0, 0, 6, 3));

 Button* close_button = new Button(cont, new Functor<Popup_Window>(this, &Popup_Window::fnc_close));
 close_button->set_states(Resources::make_sprite("res\\img\\GUI\\Index_Screen\\close.png"),
                          Resources::make_sprite("res\\img\\GUI\\Index_Screen\\close_over.png"),
                          Resources::make_sprite("res\\img\\GUI\\Index_Screen\\close_pressed.png"),
                          Resources::make_sprite("res\\img\\GUI\\Index_Screen\\close_pressed.png"));
 close_button->set_x(302);
 close_button->set_y(4);
 add_entity(close_button);
}

Popup_Window::~Popup_Window() {};

void Popup_Window::update_after_queue(int x_offset, int y_offset) {
 if(!Input::paused()) {
  if(follow) {
   if(Input::mouse(1)) {
    Input::mouse_eat(1);
    _x = Input::mouse_x()-offset_x;
    _y = Input::mouse_y()-offset_y;
   } else follow = false;
  }
  if(Input::mouse_x()>=_x && Input::mouse_x()<=_x+320) {
   if(Input::mouse_y()>=_y && Input::mouse_y()<=_y+20) { //caption
    if(!Input::mouse_eaten(1) && Input::mouse(1) && Input::mouse(1)<3) {
     Input::mouse_eat(1);
     follow = true;
     offset_x = Input::mouse_x() - _x;
     offset_y = Input::mouse_y() - _y;
     set_priority(3);
    }
   } else if(Input::mouse_y()>=_y+20 && Input::mouse_y()<=_y+200)  {
    if(Input::mouse_press(1,true)) set_priority(3);
    if(Input::mouse(1)) Input::mouse_eat(1);
   }
  }
 }
}

void Popup_Window::fnc_close() {
 destruct();
}
