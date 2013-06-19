#include "main_menu.h"
#include "..\Engine\Data\string_table.h"
#include "..\objects\windows\loadgame_window.h"
#include "..\objects\windows\options_window.h"

//{ creating&destructing screen
Main_Menu::Main_Menu(Game* gm, SDL_Surface* surf, Loader* ld, Input* in):
 Screen(gm,surf,ld,in), enabled(true) { load(); };

void Main_Menu::load() {
 ///placing objects
 add_object(new Image(*loader->load_texture("res\\img\\GUI\\main_menu\\background.png")));
 add_button(75,200,String_Table::translate["mm_new_game"], new Functor<Main_Menu>(this, &Main_Menu::fnc_start) );
 add_button(75,300,String_Table::translate["mm_load_game"], new Functor<Main_Menu>(this, &Main_Menu::fnc_load) );
 add_button(75,400,String_Table::translate["mm_options"], new Functor<Main_Menu>(this, &Main_Menu::fnc_options) );
 add_button(75,500,String_Table::translate["mm_exit_game"], new Functor<Main_Menu>(this, &Main_Menu::fnc_exit) );
}

Main_Menu::~Main_Menu() {};
//}

//{ methods

Button* Main_Menu::add_button(int x, int y, string text, functor* f, int pr) {
 ///creating unique designed button in run-time
 Button* b = new Button();
 //provide images for up, over, pressed & disabled states (respectively)
 b->set_states(*loader->load_texture("res\\img\\GUI\\main_menu\\b_up.png"),
               *loader->load_texture("res\\img\\GUI\\main_menu\\b_over.png"),
               *loader->load_texture("res\\img\\GUI\\main_menu\\b_pressed.png"),
               *loader->load_texture("res\\img\\GUI\\main_menu\\b_pressed.png"));
 SDL_Color c;
 c.r=c.g=c.b=255;
 b->set_label(loader->load_font("Arial",20), c, text); //set white Arial 20 as font
 b->set_x(x);
 b->set_y(y);
 if(f) b->set_func(f); //attach function to button's press event
 //now set priority and add object to queue
 b->set_priority(pr);
 add_object(b);
 return b;
}
//}

//{ functions that are called by buttons
void Main_Menu::fnc_goto_start() { game->open_screen(s_THE_FOREST, true); }
void Main_Menu::fnc_start() {
 if(enabled) {
  enabled=false;
  Fade_Effect* eff = new Fade_Effect(m_FADE_IN, 15, 0, 0, 0, -1);
  eff->color_mode(0,0,0,game->w(),game->h());
  add_object(eff);
  eff = new Fade_Effect(m_FADE_IN, 30, new Functor<Main_Menu>(this, &Main_Menu::fnc_goto_start), 0, 0, 10);
  eff->color_mode(0,0,0,game->w(),game->h());
  add_object(eff);
 }
}
void Main_Menu::fnc_load() {
 if(enabled) {
  add_object(new LoadGame_Window(true,game,loader,20));
 }
}
void Main_Menu::fnc_options() {
 if(enabled) {
  add_object(new Options_Window(game,loader,20));
 }
}
void Main_Menu::fnc_exit() { game->stop(); }
//}
