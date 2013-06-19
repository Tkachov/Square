#include "the_forest.h"

The_Forest::The_Forest(Game* gm, SDL_Surface* surf, Loader* ld, Input* in):
 Screen(gm,surf,ld,in,true), __first_visit(true), level(0), pause_menu(0) { load(); };

The_Forest::~The_Forest() {};

void The_Forest::fnc_menu() {
 pause_menu->set_enabled(!pause_menu->enabled());
 if(!pause_menu->enabled()) input->unpause();
}

void The_Forest::load() {
 add_object(level = new Level("res\\lvl\\00.txt", game, loader, this));
 add_object(new Blue_Button(String_Table::translate["adv_menu"], new Functor<The_Forest>(this, &The_Forest::fnc_menu), loader, 10, 10, 100, 91));
 add_object(pause_menu = new Pause_Menu(game, loader, 101));
 pause_menu->set_enabled(false);
}

void The_Forest::start() {
 State* st = game->state();

 if(__first_visit) {
  add_object(new Logo_Fade(game,loader,0,0,100));
  st->set_persistent("map", "hero_x", new int(-1));
  st->set_persistent("map", "hero_y", new int(-1));
 } else {
  Fade_Effect* eff = new Fade_Effect(m_FADE_OUT, 30, 0, 0, 0, 100);
  eff->color_mode(0,0,0,game->w(),game->h());
  add_object(eff);
 }

 __first_visit = false;

 int* hx = static_cast<int*>(st->persistent("map", "hero_x"));
 int* hy = static_cast<int*>(st->persistent("map", "hero_y"));
 if(hx!=0&&hy!=0&&*hx>-1&&*hy>-1) {
  level->replace_hero(*hx, *hy, false);
  st->set_persistent("map", "hero_x", new int(-1));
  st->set_persistent("map", "hero_y", new int(-1));
 }
}

void The_Forest::update() {
 if(input->terminate()) game->stop();
 update_queue();
 if(input->key_release(SDLK_ESCAPE)) fnc_menu();
}

void The_Forest::save_state(ofstream& fout) {
 fout << (__first_visit?1:0) << "\n";
 level->save_state(fout);
}

void The_Forest::load_state(ifstream& fin) {
 int v;
 fin >> v;
 __first_visit = (v==0?false:true);
 level->load_state(fin);
}
