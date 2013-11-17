#include "ScreenID.h"
#include "../../screens/Index_Screen.h"

namespace Engine { namespace Global {

Screen* create_screen(Controller* controller, ScreenID sid) {
 switch(sid) {
  case s_UNKNOWN_ID:
   throw "Unable to create a screen with undefined id.";
  break;

  case s_INDEX: return new Index_Screen(controller); break;

  default:
   if(sid < s_TREAT_EVERYTHING_AFTER_AS_INDEX)
    throw "Unable to create a screen that is not implemented.";
   else
    return create_screen(controller, s_INDEX);
 }
}

} }
