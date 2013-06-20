# Game class

## Overview

Game class does the infinite loop that handles user's input and redraws the screen.  
It loads and storages different information like [Screen](03_Screen.md) objects, options and localization [String_Table](07_String_Table.md)s, etc.  
It contains the only instances of [Input](08_Input.md) and [Loader](09_Loader.md) objects you can use from other classes.  
Actually, you don't have to change something in Game's work, but this information can be useful for you anyway.

## Functions  

##### `Game()`
Constructor, creates the window and opens Screen with ScreenID **SCREENID_DEFAULT**.  

----
##### `~Game()`
Destructor, frees the memory.  

----
##### `void loop()`
Contains application loop which actually keeps the game alive.  

----
##### `void stop()`
Stops the application loop.  

----
##### `void open_screen(ScreenID sid, bool reload = false)`
Opens Screen with ScreenID **sid**.  
Reloads the Screen (which means creating a new instance) if **reload** is **true**.  
This function works only if you have added your Screen-deriving class in **[create_screen(ScreenID)](05_Game.md#screenid)** function!  

----
##### `void open_screen(Screen* screen)`
Opens Screen **screen**.  

----
##### `void save(string filename)`
Saves current game state in file with name **filename** in the subfolder "saves".  

----
##### `void load(string filename)`
Loads game state from file with name **filename** from the subfolder "saves".  

----
##### `void save_options()`
Saves options in "config.txt" file.  

----
##### `void restart()`
Relaunches the game.  
Can be used to apply options' changes (if those are critical and require relaunch).  

----
##### `int w()`
Returns the window's width.  

----
##### `int h()`
Returns the window's height.  

----
##### `State* state()`
Returns [State](11_State.md) object of current game (you can save this object or get some shared variables from it).  

----
##### `ScreenID sid()`
Returns current Screen's ScreenID.  

----
##### `string option(string key)`
Returns value for option with name **key**.  

----
##### `void set_option(string key, string value)`
Replaces option's with name **key** value with **value**.

## ScreenID

game.h file contains ScreenID enum and **SCREENID_DEFAULT** contant definitions.  
Game class also contains a private function **create_screen(ScreenID)**, which contains switch of ScreenID values and creates corresponding Screen classes.  
When you derive Screen class, you should also add new ScreenID value into enumeration, include your class' header file into game.cpp and edit the function.  
Otherwise, function **[open_screen(ScreenID, bool)](05_Game.md#void-open_screenscreenid-sid-bool-reload-false)** will not be able to create your class' objects (you still can use **[open_screen(Screen*)](05_Game.md#void-open_screenscreen-screen)** though).  

## Other stuff

Game object contains the only instances of the main window surface, Loader, Input and State (pointers to these are passed to Screen objects). It also contains options in String_Table object and a pointer to current Screen object.  
   
   
**Previous file:** [Object class](04_Object.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Using functors](06_Using_functors.md)