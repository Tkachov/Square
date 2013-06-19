#include "the_dungeon.h"

The_Dungeon::The_Dungeon(Game* gm, SDL_Surface* surf, Loader* ld, Input* in):
 Screen(gm,surf,ld,in,true), level(0), pause_menu(0) { load(); };

The_Dungeon::~The_Dungeon() {};

void The_Dungeon::fnc_menu() {
 pause_menu->set_enabled(!pause_menu->enabled());
 if(!pause_menu->enabled()) input->unpause();
}

void The_Dungeon::load() {
 add_object(level = new Level("res\\lvl\\01.txt", game, loader, this));
 add_object(new Blue_Button(String_Table::translate["adv_menu"], new Functor<The_Dungeon>(this, &The_Dungeon::fnc_menu), loader, 10, 10, 100, 91));
 add_object(pause_menu = new Pause_Menu(game, loader, 101));
 pause_menu->set_enabled(false);
}

void The_Dungeon::start() {
 Fade_Effect* eff = new Fade_Effect(m_FADE_OUT, 30, 0, 0, 0, 100);
 eff->color_mode(0,0,0,game->w(),game->h());
 add_object(eff);

 State* st = game->state();
 int* hx = static_cast<int*>(st->persistent("map", "hero_x"));
 int* hy = static_cast<int*>(st->persistent("map", "hero_y"));
 if(hx!=0&&hy!=0&&*hx>-1&&*hy>-1) {
  level->replace_hero(*hx, *hy, false);
  st->set_persistent("map", "hero_x", new int(-1));
  st->set_persistent("map", "hero_y", new int(-1));
 }
}

void The_Dungeon::update() {
 if(input->terminate()) game->stop();
 update_queue();
 if(input->key_release(SDLK_ESCAPE)) fnc_menu();
}

void The_Dungeon::save_state(ofstream& fout) {
 level->save_state(fout);
}

void The_Dungeon::load_state(ifstream& fin) {
 level->load_state(fin);
}
