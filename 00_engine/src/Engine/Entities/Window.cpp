#include "Window.h"

namespace Engine { namespace Entities {

Window::Window(Controller* c, int sx, int sy, bool modal): Entity(c) {
 _x = sx;
 _y = sy;
}

Window::~Window() {}

void Window::update(int x, int y) {
 if(_modal) Input::unpause();
 update_queue(x, y);
 if(_modal && !_destroy) Input::pause();
}

} }
