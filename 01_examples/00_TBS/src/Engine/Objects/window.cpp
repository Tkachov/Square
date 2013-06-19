#include "window.h"

namespace Engine { namespace Objects {

Window::Window(Game* g, Loader* l, int x, int y, int pr):
 Object(x,y,pr), Screen(g,0,l,0) { load(); }
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

void Window::draw(SDL_Surface* surf) {
 surface = surf;
 draw_queue();
}

void Window::add_object(Object* obj) {
 obj->set_x(obj->x()+_x);
 obj->set_y(obj->y()+_y);
 Screen::add_object(obj);
}

} }
