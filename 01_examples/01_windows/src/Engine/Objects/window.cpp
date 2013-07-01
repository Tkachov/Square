#include "window.h"

namespace Engine { namespace Objects {

Window::Window(Game* g, Loader* l, int x, int y, int pr):
 Object(x,y,pr), Screen(g,l,0) { load(); }
Window::~Window() {};

void Window::load() {};

void Window::disappear() {
 if(input) input->unpause();
 _destroy = true;
}

void Window::update_queue(int xo, int yo) {
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
  if(i->obj->enabled()) i->obj->update(input, _x+xo, _y+yo);
}

void Window::update(Input* _input, int xo, int yo) {
 input = _input;
 update(xo, yo);
 if(_destroy) input->unpause(); //in case when the object is destroyed in %update%
}

void Window::update(int xo, int yo) {
 if(_destroy||input==0) return;
 input->unpause();
 update_queue(xo, yo);
 input->pause();
}

void Window::draw(int x, int y) { draw_queue(x, y); }

} }
