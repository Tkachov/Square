#include "Window.h"
#include "../Input.h"

namespace Engine { namespace Entities {

Window::Window(Controller* c, int sx, int sy, bool modal): Entity(c) {
 _x = sx;
 _y = sy;
 _modal = modal;
}

Window::~Window() {}

void Window::update(int x, int y) {
 if(_modal) Input::unpause();
 update_before_queue(x, y);
 update_queue(x, y);
 update_after_queue(x, y);
 if(_modal && !_destroy) Input::pause();
}

} }
