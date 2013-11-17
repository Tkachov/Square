# Overview

Square is a simple system which is based on SDL+OpenGL libraries and gives you an ability to create applications easier. The engine have some base and primitive classes which are doing their work. All you need to do is just use those classes. There are two general components of the system: [Screens](03_Screen.md) and [Entities](04_Entity.md).

You can switch from one Screen to another, using it to create levels, menus, etc. Each Screen can contain Entities that are drawn on the screen. Different types of Entities are doing different work and are drawn in different way.

So, the simplest Square application should contain at least one Screen to run and no Entities at all. But to make something dynamic you'll need some Entities too.

There are some primitive Entity classes you may need in Square:
* [Sprite](15_Sprite.md), the collection of frames;
* [Text](16_Text.md), the text label with it's font and color;
* [Button](17_Button.md), the combination of Sprite and Text objects that reacts to mouse clicks;
* [Window](14_Window.md), the layer that can contain any Entities;
* [Fade](18_Fade.md), which can be used for fade-in and fade-out effects;
* [Timer](19_Timer.md), the invisible Entity that does some actions with interval.

You can use these Entities on your Screens or derive these and create your own Entities to use.

There are also some service classes you can find useful:
* [Controller](05_Controller.md), which is responsible for the general actions;
* [Main_Window](06_Main_Window.md), that controls window behaviour;
* [Resources](07_Resources.md), that loads different kinds of resources and storages it;
* [Input](08_Input.md), that handles user's input and provides an information about it;
* [State](09_State.md), the container of global (or “persistent”) variables of any type;
* [Logger](10_Logger.md), that writes messages to log files and console.

The [utils.cpp](21_utils_h.md) file contains useful functions and algorithms. Include utils.h file to use it.

There are lots of useful constants in [settings.h](22_settings_h.md) file.
   
    
**[Contents](00_Contents.md)**  
**Next file:** [Workflow](02_Workflow.md)