#ifndef SCREENID_H
#define SCREENID_H

namespace Engine {

class Controller;

namespace Entities {

class Screen;

}

using Engine::Entities::Screen;

namespace Global {

enum ScreenID {
 s_UNKNOWN_ID, //no screens with this id will be created
 s_INDEX //screen that is created first automatically


 ///add ScreenIDs BEFORE this line
 , s_TREAT_EVERYTHING_AFTER_AS_INDEX //if any ScreenID is larger or equal to this one, it is treaten as s_INDEX
};

Screen* create_screen(Controller* controller, ScreenID sid);

} }

#endif // SCREENID_H
