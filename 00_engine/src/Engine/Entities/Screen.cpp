#include "Screen.h"
#include "Sprite.h"
#include "Text.h"
#include "../Resources.h"

namespace Engine { namespace Entities {

Screen::Screen(Controller* controller): Entity(controller) {}

void Screen::start() {}

void Screen::save_state(ofstream& fout) {}

void Screen::load_state(ifstream& fin) {}

void Screen::update_after_queue(int x, int y) {
 if(Input::quit()) controller->stop_loop();
}

} }
