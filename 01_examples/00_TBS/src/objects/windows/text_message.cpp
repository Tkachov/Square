#include "text_message.h"

Text_Message::Text_Message(string s, Game* g, Loader* l, int pr):
 Window(g,l,0,0,pr), message(s) { load(); }
Text_Message::~Text_Message() {};

void Text_Message::fnc_OK() {
 if(input!=0) input->mouse_eat(1);
 disappear();
}

Image* Text_Message::newImage(string s, int x, int y, int pr) {
 Image* img = new Image(*loader->load_texture(s));
 img->set_x(x);
 img->set_y(y);
 img->set_priority(pr);
 return img;
}

void Text_Message::load() {
 //add background
 int sw = game->w();
 int sh = game->h();
 Image* img = newImage("res\\img\\GUI\\message_box.png", 0,0, 0);
 int px = (sw - img->w())/2;
 int py = (sh - img->h())/2;
 img->set_x(px);
 img->set_y(py);
 add_object(img);
 //now place button & text on it
 SDL_Color c; c.r = c.g = c.b = 255;
 add_object(new Text(loader->load_font("Tahoma",16), message, 380, c, px+10, py+10, 1)); //text
 add_object(new Blue_Button(String_Table::translate["OK"], new Functor<Text_Message>(this, &Text_Message::fnc_OK), loader, (sw-100)/2, py+img->h()-50, 100, 2)); //OK button
}

void Text_Message::update() {
 if(_destroy||input==0) return;
 input->unpause();
 update_queue();
 input->pause();
}

void Text_Message::update(Input* _input) {
 input = _input;
 if(input->key_release(SDLK_ESCAPE, true)||input->key_release(SDLK_RETURN)) disappear();
 update();
 if(_destroy) input->unpause(); //in case when the object was destroyed inside this function
}
