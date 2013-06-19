#include "logo_fade.h"
#include "..\Engine\utils.h"
using namespace Engine;

Logo_Fade::Logo_Fade(Game* gm, Loader* ld, int sx, int sy, int pr):
 Object(sx, sy, pr), Screen(gm, 0, ld, 0), fadephase(0) { load(); };

Logo_Fade::~Logo_Fade() {};

void Logo_Fade::load() {
 int w, h;
 w = game->w();
 h = game->h();
 Image* i = new Image(*loader->load_texture("res\\img\\GUI\\logo.png"));
 i->set_x((w-400)/2);
 i->set_y((h-400)/2);
 add_object(i); //400x400 logo
 Fade_Effect* eff = new Fade_Effect(m_FADE_OUT, 60, new Functor<Logo_Fade>(this, &Logo_Fade::fnc_phase1_delay), 0, 0, 1);
 eff->color_mode(0,0,0,w,h);
 add_object(eff);
}

void Logo_Fade::fnc_phase1_delay() {
 fadephase=1;
 add_object(new Timer(120, 1, new Functor<Logo_Fade>(this, &Logo_Fade::fnc_phase2_fade_out)));
}

void Logo_Fade::fnc_phase2_fade_out() {
 fadephase=2;
 clear_queue();

 int w, h;
 w = game->w();
 h = game->h();
 Fade_Effect* eff = new Fade_Effect(m_FADE_OUT, 60, new Functor<Logo_Fade>(this, &Logo_Fade::fnc_phase3_destruct), 0, 0, 1);
 eff->color_mode(0,0,0,w,h);
 add_object(eff);
 eff = new Fade_Effect(m_FADE_OUT, 60, 0, (w-400)/2, (h-400)/2, 2);
 eff->spr()->set_frame(*loader->load_texture("res\\img\\GUI\\logo.png"));
 eff->image_mode();
 add_object(eff);
}

void Logo_Fade::fnc_phase3_destruct() {
 fadephase=3;
 _destroy=true;
}

void Logo_Fade::update(Input* i) {
 if(i->key_release(SDLK_ESCAPE)||i->key_release(SDLK_SPACE)||i->key_release(SDLK_RETURN)||i->mouse_release(1)) fnc_phase3_destruct();
 i->mouse_eat(1);
 i->mouse_eat(2);
 input=i;
 update_queue();
}

void Logo_Fade::draw(SDL_Surface* s) {
 surface=s;
 if(fadephase<2) {
  glColor4f(0,0,0, 1);
  draw_rectangle(0,0,800,600);
  //glRecti(0,600,800,0);
  //glRecti(0,0,800,600);
 }
 draw_queue();
}
