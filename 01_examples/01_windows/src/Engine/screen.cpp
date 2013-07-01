#include "screen.h"
#include "utils.h"

namespace Engine {

Screen::Screen(Game* gm, Loader* ld, Input* in, bool st):
 game(gm), loader(ld), input(in), _is_static(st) { load(); };

Screen::~Screen() { clear_queue(); }

void Screen::load() {};
void Screen::start() {};

void Screen::show_message(Object* msg) { add_object(msg); }

void Screen::add_object(Object* o, bool reorder) {
 if(o==0) return;
 objects.push_back(queued_object(o));
 if(reorder) reorder_queue();
}

void Screen::reorder_queue() { sort(objects.begin(),objects.end()); }
void Screen::update_queue(int xo, int yo) {
 opqueue clone;
 clone.reserve(objects.size());

 bool removed = false;
 for(opqueue::iterator i=objects.begin(); i!=objects.end(); ++i)
  if(!i->obj->destroy()) clone.push_back(*i);
  else {delete i->obj; removed=true;}
 if(removed) {
  objects.clear();
  objects = clone;
 }

 for(opqueue::reverse_iterator i=clone.rbegin(); i!=clone.rend(); ++i)
  if(i->obj->enabled()) i->obj->update(input, xo, yo);
}
void Screen::clear_queue() {
 for(opqueue::iterator i=objects.begin(); i!=objects.end(); ++i) delete i->obj;
 objects.clear();
}
void Screen::draw_queue() {
 for(opqueue::iterator i=objects.begin(); i!=objects.end(); ++i)
  if(i->obj->enabled() && i->obj->visible()) i->obj->draw();
}
void Screen::draw_queue(int ax, int ay) {
 for(opqueue::iterator i=objects.begin(); i!=objects.end(); ++i)
  if(i->obj->enabled() && i->obj->visible()) i->obj->draw(i->obj->x()+ax, i->obj->y()+ay);
}

void Screen::update(int xo, int yo) {
 if(input->terminate()) game->stop();
 update_queue(xo, yo);
 if(input->key_release(SDLK_ESCAPE)) game->stop(); //keys may be eaten by overlay windows
}

void Screen::redraw() {
 glClear(GL_COLOR_BUFFER_BIT);
 glEnable(GL_BLEND);
 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 draw_queue();
#ifdef DBG_SOFTWARE_CURSOR
 if(loader&&input) {
  Image* cur = loader->load_texture(DBG_SOFTWARE_CURSOR);
  if(cur) cur->draw(input->mouse_x(), input->mouse_y());
 }
#endif
 SDL_GL_SwapBuffers();
}

void Screen::save_state(ofstream& fout) {};

void Screen::load_state(ifstream& fin) {};

bool Screen::is_static() { return _is_static; }

}
