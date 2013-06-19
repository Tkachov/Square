# Overview

Square is a simple system which is based on SDL+OpenGL libraries and gives you an ability to create applications easier. The engine have some base and primitive classes which are doing their work. All you need to do is just use those classes. There are two general components of the system: [Screen](03_Screen.md)s and [Object](04_Object.md)s.

[Game](05_Game.md), the main game object, can switch from one Screen to another, so you can create levels, menus, etc. Each Screen can contain Objects that are drawn on the screen. Different types of Objects are doing different work and are drawn in different way.

So, the simplest Square application should contain at least one Screen to run and no Objects at all. But to make something dynamic you'll need some Objects too.

There are some primitive Objects classes you may need in Square:
* [Image](12_Image.md), the single bitmap & texture;
* [Sprite](13_Sprite.md), the collection of Image frames;
* [Text](14_Text.md), the text label with it's font and color;
* [Button](15_Button.md), the combination of Sprite and Text objects that reacts to mouse clicks;
* [Window](16_Window.md), the layer that can contain any Objects;
* [Timer](17_Timer.md), the invisible Object that does some actions with interval;
* [Fade_Effect](18_Fade_Effect.md), the Object that can be used for fade-in and fade-out effects.

You can use these Objects on your Screens or derive these and create your own Objects to use.

There are also some engine classes you can find useful:
* [String_Table](07_String_Table.md), the container of strings you can get using the key;
* [Input](08_Input.md), that handles user's input and provides an information about it;
* [Loader](09_Loader.md), that loads different kinds of resources and storages it;
* [Logger](10_Logger.md), that writes messages to log files and console;
* [State](11_State.md), the container of global (or “persistent”) variables of any type.

The [debug.h](19_debug_h.md) file contains constants for debug mode. They have no effect when you build your application in Release configuration, and can be used for easier development & debugging.

The [utils.cpp](20_utils_h.md) file contains useful functions and algorithms. Include utils.h file to use it.

Also, there is a special SDL_win32_main.c file which is used by engine only. There are lots of different SDL parameters  you don't have to change.  
   
    
**[Contents](00_Contents.md)**  
**Next file:** [Workflow](02_Workflow.md)