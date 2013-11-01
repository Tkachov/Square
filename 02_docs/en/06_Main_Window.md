# Main_Window class

## Overview

As Square's developed to make single-windowed applications like games, there is no classes for windows except the class for the main application's window — Main_Window.

Almost all of it's functions are static, so you can call them whereever you want to.

## Functions  

##### `static void create(...)`
    static void create(
     const char* title,
     int x, int y, int w, int h,
     string fullscreen,
     int flags = 0
    )
The function that creates application's window with given parameters. It's automatically called when application is started or restarted. The actual parameters that are passed can differ — there are some default values in [settings.h](22_settings_h.md) that can be overriden by values from config file.  
If you will use it manually, pass window's title as **title**, it's position as **x**, **y** and it's size as **w** and **h**. If you want to run application in [fullscreen mode](06_Main_Window.md#fullscreen-modes-in-square), use "1" for fs_FULLSCREEN_STRETCHED, "2" for fs_FULLSCREEN_WHOLE_SCREEN, "3" for fs_WINDOWED_STRETCHED or "4" for fs_WINDOWED_WHOLE_SCREEN mode. You can also pass some [SDL's window flags](http://wiki.libsdl.org/SDL_CreateWindow#Remarks) if you want.

----
##### `static void destroy()`
Destroyes the window.  
That also deletes OpenGL's context, so all loaded textures will be freed as their indeces will be lost.
This function is called automatically when application is stoped or relaunched.  

----
##### `static void swap()`
Updates the window's surface.  
This function is called automatically after frame redrawing.

----
##### `static void update_window_size()`
Updates window's size.  
Should be called if something has changed window's size (for example, if user has resized it).  
This function is called automatically when you switch back to application's window on Android.  

----
##### `static Fullscreen_Mode get_fullscreen()`
Returns current fullscreen mode.  

----
##### `static int get_viewport_width(bool refresh = false)`
Returns current viewport width.
If **refresh** is **true**, checks whether size has changed and returns an updated value.  
It does not updates projection size.  
 
----
##### `static int get_viewport_height(bool refresh = false)`
Returns current viewport height.
If **refresh** is **true**, checks whether size has changed and returns an updated value.  
It does not updates projection size.  

----
##### `static int get_projection_width()`
Returns current projection width.
It does not updates projection's size.  
 
----
##### `static int get_projection_height()`
Returns current projection height.
It does not updates projection's size. 

----
##### `static void set_fullscreen(Fullscreen_Mode fullscreen)`
Sets new fullscreen mode requesting the same projection size as it was before this function was called.  
It may change both viewport and projection sizes.  

----
##### `static void set_fullscreen(Fullscreen_Mode fullscreen, int pr_width, int pr_height)`
Sets new fullscreen mode requesting projection with size you've passed.  
It may change both viewport and projection sizes.   
 
----
##### `static void set_title(string title)`
Sets new window's title.  

## Fullscreen modes in Square

There are three fullscreen modes in SDL:
* **0**, — windowed mode,
* **SDL_WINDOW_FULLSCREEN**, — “fake” fullscreen,
* **SDL_WINDOW_FULLSCREEN_DESKTOP**, — “real” fullscreen.

In “fake” fullscreen mode SDL changes display's resolution to correspond your application's surface size (so it's stretched to a whole screen).

In “real” fullscreen mode your application gets surface with a size of the display, so you can use more space.

### Fullscreen_Mode

There is special enum for fullscreen modes in Square because of some problems with SDL's fullscreen modes on Ubuntu.

It contains following values:
* **fs_WINDOWED**, — windowed mode,
* **fs_FULLSCREEN_STRETCHED**, — SDL's “fake” fullscreen mode (**SDL_WINDOW_FULLSCREEN**),
* **fs_FULLSCREEN_WHOLE_SCREEN**, — SDL's “real” fullscreen mode (**SDL_WINDOW_FULLSCREEN_DESKTOP**),
* **fs_WINDOWED_STRETCHED**, — “fake” fullscreen emulated,
* **fs_WINDOWED_WHOLE_SCREEN**, — “real” fullscreen emulated.

First three of these are just using corresponding SDL's fullscreen modes and the other two are made for cases like Ubuntu. These modes are using borderless window with the size of the display, which looks exactly like fullscreen mode does. In **fs_WINDOWED_STRETCHED** mode surface is stretched to a whole screen.

This enumeration is in Main_Window.h file.

Note that Android applications are always using whole display, so Square automatically changes **fs_WINDOWED** and **fs_FULLSCREEN_STRETCHED** modes to **fs_WINDOWED_STRETCHED**.
   
   
**Previous file:** [Controller class](05_Controller.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Resources class](07_Resources.md)