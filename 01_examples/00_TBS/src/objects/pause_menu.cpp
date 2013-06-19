#include "pause_menu.h"
#include "..\Engine\Data\string_table.h"
#include "windows\loadgame_window.h"
#include "windows\options_window.h"

Pause_Menu::Pause_Menu(Game* gm, Loader* ld, int pr):
 Object(0,0, pr), Screen(gm, 0, ld, 0), b_save(0) { load(); };

Pause_Menu::~Pause_Menu() {};

void Pause_Menu::fnc_continue() {
 _enabled = false;
 if(input!=0) input->mouse_eat(1);
}
void Pause_Menu::fnc_save() {
 add_object(new LoadGame_Window(false,game,loader,20));
}
void Pause_Menu::fnc_load() {
 add_object(new LoadGame_Window(true,game,loader,20));
}
void Pause_Menu::fnc_options() {
 add_object(new Options_Window(game,loader,20,b_save->is_disabled()));
}
void Pause_Menu::fnc_goto_menu() { game->open_screen(s_MAIN_MENU); }

void Pause_Menu::fnc_exit() { game->stop(); }

void Pause_Menu::load() {
 add_object(new Image(*loader->load_texture("res\\img\\GUI\\pause_menu\\background.png")));
 int shift = -8;
 add_object(new Blue_Button(String_Table::translate["pm_continue"], new Functor<Pause_Menu>(this, &Pause_Menu::fnc_continue), loader, 300, 155+shift, 200, 1));
 add_object(b_save = new Blue_Button(String_Table::translate["pm_save_game"], new Functor<Pause_Menu>(this, &Pause_Menu::fnc_save), loader, 300, 200+shift, 200, 1));
 add_object(new Blue_Button(String_Table::translate["pm_load_game"], new Functor<Pause_Menu>(this, &Pause_Menu::fnc_load), loader, 300, 245+shift, 200, 1));
 add_object(new Blue_Button(String_Table::translate["pm_options"], new Functor<Pause_Menu>(this, &Pause_Menu::fnc_options), loader, 300, 290+shift, 200, 1));
 add_object(new Blue_Button(String_Table::translate["pm_to_main_menu"], new Functor<Pause_Menu>(this, &Pause_Menu::fnc_goto_menu), loader, 300, 335+shift, 200, 1));
 add_object(new Blue_Button(String_Table::translate["pm_exit_game"], new Functor<Pause_Menu>(this, &Pause_Menu::fnc_exit), loader, 300, 380+shift, 200, 1));
}

void Pause_Menu::update(Input* i) {
 input=i;
 i->unpause();
 update_queue();
 if(input->key_release(SDLK_ESCAPE, true)) _enabled=false;
 if(_enabled) i->pause(); else i->unpause(); //in case when the object was disabled inside this function
}

void Pause_Menu::draw(SDL_Surface* s) {
 surface=s;
 draw_queue();
}
