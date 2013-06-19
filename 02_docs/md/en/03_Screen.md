# Screen class

## Overview

Screen objects are the main containers of [Object](04_Object.md)s that are drawn on the screen.

Every Screen have it's ScreenID in game.h file so [Game](05_Game.md) object is able to distinguish different Screens from each other. There are two ways of starting a new Screen — passing a Screen pointer to Game's **[open_screen()](05_Game.md#void-open_screenscreen-screen)** or passing a ScreenID to Game's **[open_screen()](05_Game.md#void-open_screenscreenid-sid-bool-reload--false)** (it will create the necessary Screen object automatically).

Screens can be “static”. It means the object will be storaged by Game object and won't be created again. Static Screen objects are saving their state even if Game has opened some other Screens. You can also force recreating Screen object (for example, if you want to start a new game) by calling **[Game::open_screen()](05_Game.md#void-open_screenscreenid-sid-bool-reload--false)** with ScreenID and **true** parameters.


## Deriving a Screen class

The actual Screen object is ready to be opened by Game object, though it doesn't do or contain anything. So if you derive Screen class, you'll get a working class even if you don't override any of it's virtual functions.

Following functions can be overriden in Screen class:

##### `void load()`
This function is actually called from class' contructor. You are free to use either this function or constructor to prepare your object to work. You can also use both **load()** and constructor.  
Screen class' **load()** does nothing.  

----
##### `void start()`
This function is called every time Screen object is opened.  
(For example, you can check if the Screen is opened first time and do something special.)  
Screen class' **start()** does nothing.  

----
##### `void update()`
This function is called by Game object in the infinite loop. Function should notify Objects so they can update their state if mouse or keyboard events occured.  
Screen class' **update()** notify all Objects and stops the game if user has pressed close button or Escape key.  

----
##### `void redraw()`
This function is called by Game object in the infinite loop. Function should draw Objects to the screen.  
Screen class' **redraw()** draws all Objects to the screen.  

----
##### `void show_message(Object*)`
This function can be called from some object to ask Screen to show the Object passed.  
Screen class' **show_message()** shows any passed Object.  

----
##### `void save_state(ofstream&)`
This function is called by Game object to save the state into given output stream. It should be used for saving the information that will not be available for next session so it could be restored.  
(For example, menu should not save it's state because it is always the same. And levels where player could've replaced something should save it's state.)  
Screen class' **save_state()** does nothing.  

----
##### `void load_state(ifstream&)`
This function is called by Game object to load the state from given input stream. It should be used for loading the information that was saved by previous function.  
(For example, you should restore the level you have saved.)  
Screen class' **load_state()** does nothing.  

----
##### `ScreenID ID()`
This function should return corresponding ScreenID so this class' objects can be distinguished from others.  
Screen class' **ID()** returns **SCREENID_DEFAULT**, which is defined in game.h file.


## Screen class' design

Every Screen should contain Objects, notify them to update their state and draw it on the screen. As every Object have it's own priority, these Objects should be kept in order. The class have a special queue of Objects for simple accessing. There are bunch of protected functions to deal with Screen's queue. These functions are ready to use and should be used from overriden virtual functions.

This is a list of protected Screen class' functions:

##### `void add_object(Object* o, bool reorder = true)`
This function adds a new object to the queue. As queue's order can be broken by this action, it can be reordered right after Object is added. But as the reordering operation can be time-expensive, you can pass **false** parameter and reorder the queue when it's necessary by your own.  

----
##### `void reorder_queue()`
This function reorders the queue.  

----
##### `void update_queue()`
This function notify Objects in queue to check [Input](08_Input.md) and change their state if necessary.  

----
##### `void clear_queue()`
This function removes every Object from the queue.  

----
##### `void draw_queue()`
This function draws all Objects in the queue to the screen.  

----
##### `void draw_queue(int x, int y)`
This function draws all Objects in the queue to the screen with given offset by X and Y axes.  
   
   
**Previous file:** [Workflow](02_Workflow.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Object class](04_Object.md)