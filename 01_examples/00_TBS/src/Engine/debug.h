#ifndef DEBUG_H
#define DEBUG_H

//global switch
#define DEBUG
//cursor
//#define DBG_SOFTWARE_CURSOR "res\\img\\GUI\\cursor.png"
//#define DBG_HARDWARE_CURSOR "res\\img\\GUI\\cursor.cur"
//map: interactivity
#define DBG_MAP_CONTROL_OBSTACLES
#define DBG_MAP_CONTROL_VIEW
//map: debug info visibility
#define DBG_MAP_SHOW_OBSTACLES
//logs
#define DBG_PRINT_WARNINGS
//#define DBG_PRINT_SPRITE_LOADING
//#define DBG_PRINT_IMAGE_LOADING
//#define DBG_PRINT_STRING_TABLES
#include <iostream>
using std::cout;

//throw exceptions on
#define DBG_STOP_ON_UNALLOCATED_VARIABLE

#endif // DEBUG_H
