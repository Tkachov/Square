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

## Other stuff

game.h — this is where ScreenID enum and **SCREENID_DEFAULT** constant are defined.  
Game object contains the only instances of the main window surface, Loader, Input and State (pointers to these are passed to Screen objects). It also contains options in String_Table object and a pointer to current Screen object.  
   
   
**Previous file:** [Object class](04_Object.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Using functors](06_Using_functors.md)