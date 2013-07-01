#include "first_screen.h"
#include "..\Engine\Data\string_table.h"
#include "..\objects\popup_window.h"

//{ creating&destructing screen
First_Screen::First_Screen(Game* gm, Loader* ld, Input* in):
 Screen(gm,ld,in), enabled(true), winx(0), winy(0) { load(); };

void First_Screen::load() {
 ///placing objects
 add_object(new Image(*loader->load_texture("res\\img\\GUI\\first_screen\\background.png")));
 add_button(336,600-32-24-128-40,String_Table::translate["new_window"], new Functor<First_Screen>(this, &First_Screen::fnc_new_window) );
 add_button(336,600-32-24-128,String_Table::translate["exit_game"], new Functor<First_Screen>(this, &First_Screen::fnc_exit) );
}

First_Screen::~First_Screen() {};
//}

//{ methods
Button* First_Screen::add_button(int x, int y, string text, functor* f, int pr) {
 ///creating unique designed button in run-time
 Button* b = new Button();
 //provide images for up, over, pressed & disabled states (respectively)
 b->set_states(*loader->load_texture("res\\img\\GUI\\first_screen\\button.png"),
               *loader->load_texture("res\\img\\GUI\\first_screen\\button_over.png"),
               *loader->load_texture("res\\img\\GUI\\first_screen\\button_pressed.png"),
               *loader->load_texture("res\\img\\GUI\\first_screen\\button_pressed.png"));
 SDL_Color c;
 c.r=c.g=c.b=255;
 b->set_label(loader->load_font("Tahoma",14), c, text); //set white Tahoma 14 as font
 b->set_x(x);
 b->set_y(y);
 if(f) b->set_func(f); //attach function to button's press event
 //now set priority and add object to queue
 b->set_priority(pr);
 add_object(b);
 return b;
}

void First_Screen::update() {
 if(input->terminate()) game->stop();
 bool refresh = false;
 for(opqueue::iterator i=objects.begin(); i!=objects.end(); ++i)
  if(i->obj->priority()==3) refresh=true;
 if(refresh) {
  for(opqueue::iterator i=objects.begin(); i!=objects.end(); ++i)
   i->obj->set_priority(i->obj->priority()<3?1:2);
 }
 reorder_queue();
 update_queue();
 if(input->key_release(SDLK_ESCAPE)) game->stop();
}
//}

//{ functions that are called by buttons
void First_Screen::fnc_new_window() {
 for(opqueue::iterator i=objects.begin(); i!=objects.end(); ++i)
  i->obj->set_priority(1);
 reorder_queue();

 Popup_Window* w = new Popup_Window(game, loader, winx, winy, 2);
 add_object(w);
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
void First_Screen::fnc_exit() { game->stop(); }
//}
