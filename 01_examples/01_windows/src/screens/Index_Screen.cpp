#include "Index_Screen.h"
#include "../Engine/Controller.h"
#include "../Engine/Input.h"
#include "../Engine/Resources.h"
#include "../Engine/Data/Frame.h"
#include "../Engine/Data/String_Table.h"
#include "../Engine/Entities/Button.h"
#include "../Engine/Entities/Sprite.h"
#include "../objects/Popup_Window.h"
using Engine::Input;
using Engine::Resources;
using Engine::Data::Frame;
using Engine::Data::String_Table;
using Engine::Entities::Sprite;

Index_Screen::Index_Screen(Controller* controller): Screen(controller) {
 Frame* f = Resources::load_texture("res/img/GUI/Index_Screen/background.png");
 add_entity(new Sprite(controller, *f));
 add_button(336, 416, String_Table::translate["exit_game"], new Functor<Index_Screen>(this, &Index_Screen::fnc_exit));
 add_button(336, 386, String_Table::translate["new_window"], new Functor<Index_Screen>(this, &Index_Screen::fnc_spawn_window));
}

Button* Index_Screen::add_button(int x, int y, string text, functor* f, int pr) {
 ///creating unique designed button in run-time
 Button* b = new Button(controller);
 //provide images for up, over, pressed & disabled states (respectively)
 b->set_states(Resources::make_sprite("res/img/GUI/Index_Screen/button.png"),
               Resources::make_sprite("res/img/GUI/Index_Screen/button_over.png"),
               Resources::make_sprite("res/img/GUI/Index_Screen/button_pressed.png"),
               Resources::make_sprite("res/img/GUI/Index_Screen/button_pressed.png"));
 SDL_Color c;
 c.r=c.g=c.b=255;
 b->set_label(c, Resources::load_font("Tahoma", 14), text); //use white Tahoma 14
 b->set_x(x);
 b->set_y(y);
 if(f) b->set_func(f); //attach function to button's press event
 //now set priority and add object to queue
 b->set_priority(pr);
 add_entity(b);
 return b;
}

void Index_Screen::fnc_exit() {
 controller->stop_loop();
}

void Index_Screen::fnc_spawn_window() {
 static int winx = 10;
 static int winy = 10;

 for(enqueue::iterator i=children.begin(); i!=children.end(); ++i)
  i->entity->set_priority(1);
 reorder_queue();

 Popup_Window* w = new Popup_Window(controller, winx, winy, 2);
 add_entity(w);
 winx+=10;
 if(winx>480) {
  winx=0;
  winy+=10;
  if(winy>400) {
   winx=0;
   winy=0;
  }
 }
}

void Index_Screen::update_before_queue(int x, int y) {
 bool refresh = false;
 for(enqueue::iterator i=children.begin(); i!=children.end(); ++i)
  if(i->entity->priority()==3) refresh=true;
 if(refresh) {
  for(enqueue::iterator i=children.begin(); i!=children.end(); ++i)
   i->entity->set_priority(i->entity->priority()<3?1:2);
 }
 reorder_queue();
}

void Index_Screen::update_after_queue(int x, int y) {
 if(Input::quit() || Input::key_release(SDLK_ESCAPE)) controller->stop_loop();
}
