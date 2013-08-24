#ifndef SETTINGS_H
#define SETTINGS_H

namespace Engine {

//application default options
#define DEFAULT_WIDTH "800"
#define DEFAULT_HEIGHT "600"
#define FULLSCREEN "0" /*("1" is for SDL_WINDOW_FULLSCREEN, "2" is for SDL_WINDOW_FULLSCREEN_DESKTOP)*/
#define LANGUAGE "Russian"

//application constants
#define TITLE_ON_LAUNCH "Square Engine Template"
#define WINDOW_ICON_BMP "res\\img\\icon.bmp"
//#define WINDOW_ICON_PNG "res\\img\\icon.png"

const int TICKS_PER_SECOND = 60;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 5;
#define SHOW_FPS_IN_CAPTION 1

//debug mode
#ifdef DEBUG_MODE

 //what to log
 #define DEBUG_LOG_WARNINGS 1
 #define DEBUG_LOG_SPRITE_LOADING 0
 #define DEBUG_LOG_IMAGE_LOADING 0
 #define DEBUG_LOG_STRING_TABLES 0

 //throw exceptions on
 #define DEBUG_EXCEPTION_ON_UNALLOCATED_VARIABLE 1

#endif //DEBUG_MODE

}

#endif //SETTINGS_H
