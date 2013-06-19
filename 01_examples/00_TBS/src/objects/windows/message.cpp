#include "message.h"
#include "..\..\Engine\logger.h"
using Engine::Logger;

Message::Message(Design type, Game* g, Loader* l, string msg, functor* yes, functor* no, int pr):
 Window(g,l,0,0,pr), message(msg), yep(yes), nope(no) {
  //add background
  int sw = game->w();
  int sh = game->h();
  string s = "res\\img\\GUI\\message_box.png";
  switch(type) {
   case MSG_SMALL: s = "res\\img\\GUI\\windows\\small_message.png"; break;
   default:;
  }
  Image* img = new Image(*loader->load_texture(s));
  int pw = img->w();
  int ph = img->h();
  int px = (sw - pw)/2;
  int py = (sh - ph)/2;
  img->set_x(px);
  img->set_y(py);
  add_object(img);
  //now place button & text on it
  SDL_Color c; c.r = c.g = c.b = 255;
  add_object(new Text(loader->load_font("Tahoma",16), message, pw-20, c, px+10, py+10, 1)); //text
  add_object(new Blue_Button(String_Table::translate["Yes"], new Functor<Message>(this, &Message::fnc_yes), loader, px+10, py+ph-50, 120, 2));
  add_object(new Blue_Button(String_Table::translate["No"], new Functor<Message>(this, &Message::fnc_no), loader, px+pw-10-120, py+ph-50, 120, 2));
 }

Message::~Message() {
 if(yep) delete yep;
 if(nope) delete nope;
}

void Message::fnc_yes() {
 if(yep) (*yep)();
 disappear();
}

void Message::fnc_no() {
 if(nope) (*nope)();
 disappear();
}

void Message::update() {
 if(_destroy||input==0) return;
 input->unpause();
 update_queue();
 input->pause();
}

void Message::update(Input* _input) {
 input = _input;
 if(input->key_release(SDLK_RETURN)) fnc_yes();
 if(input->key_release(SDLK_ESCAPE, true)) fnc_no();
 update();
 if(_destroy) input->unpause(); //in case when the object was destroyed inside this function
}
