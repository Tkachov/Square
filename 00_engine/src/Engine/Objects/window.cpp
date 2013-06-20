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

void Window::update(Input* _input) {
 input = _input;
 update();
 if(_destroy) input->unpause(); //in case when the object is destroyed in %update%
}

void Window::update() {
 if(_destroy||input==0) return;
 input->unpause();
 update_queue();
 input->pause();
}

void Window::draw(int x, int y) { draw_queue(x, y); }

} }
