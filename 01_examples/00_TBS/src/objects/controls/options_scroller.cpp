#include "options_scroller.h"

Options_Scroller::Options_Scroller(Loader* l, int d, int x, int y, int pr):
 Object(x,y,pr), distance(d), left(0), right(0), label(0), current(0) {
  //scroll buttons
  Button* bt = new Button(new Functor<Options_Scroller>(this, &Options_Scroller::fnc_scroll_left));
  bt->set_states(
   l->load_sprite("res\\img\\GUI\\buttons\\scroll\\left.sprite"),
   l->load_sprite("res\\img\\GUI\\buttons\\scroll\\left_over.sprite"),
   l->load_sprite("res\\img\\GUI\\buttons\\scroll\\left_press.sprite"),
   l->load_sprite("res\\img\\GUI\\buttons\\scroll\\left_off.sprite")
  );
  bt->set_holding_click_delay(15);
  left = bt;

  bt = new Button(new Functor<Options_Scroller>(this, &Options_Scroller::fnc_scroll_right));
  bt->set_states(
   l->load_sprite("res\\img\\GUI\\buttons\\scroll\\right.sprite"),
   l->load_sprite("res\\img\\GUI\\buttons\\scroll\\right_over.sprite"),
   l->load_sprite("res\\img\\GUI\\buttons\\scroll\\right_press.sprite"),
   l->load_sprite("res\\img\\GUI\\buttons\\scroll\\right_off.sprite")
  );
  bt->set_holding_click_delay(15);
  right = bt;

  SDL_Color c; c.r=c.g=c.b=255;
  label = new Text(l->load_font("Tahoma",12), "", distance, c, 18, 0, 1);
 }

Options_Scroller::~Options_Scroller() {
 if(left) delete left;
 if(right) delete right;
 if(label) delete label;
}

void Options_Scroller::fnc_scroll_left() {
 if(++current>int(olist.size())-1) current=0;
 update_label();
}
void Options_Scroller::fnc_scroll_right() {
 if(--current<0) current=int(olist.size())-1;
 update_label();
}

void Options_Scroller::update_label() {
 if(current<0||current>=int(olist.size())) current=0;
 if(label) {
  if(olist.size()) label->set_text(options[olist[current]]);
  if(label->img()) {
   label->set_x(18+(distance-label->img()->w())/2);
   label->set_y(7 - label->img()->h()/2);
  }
 }
}

void Options_Scroller::update(Input* i) {
 if(i==0||i->paused()) return;
 if(label) label->update(i);
 if(left) left->update(i);
 if(right) right->update(i);
}

void Options_Scroller::draw(SDL_Surface* s) {
 if(left) {
  left->set_x(_x);
  left->set_y(_y);
  left->draw(s);
 }
 if(right) {
  right->set_x(_x+20+distance);
  right->set_y(_y);
  right->draw(s);
 }
 if(label) label->draw(_x+label->x(), _y+label->y(), s);
}
