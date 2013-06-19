﻿# Object class

## Overview

Objects can be placed in [Screen](03_Screen.md)s. They are doing work, updating the state and drawing itself on the screen.

Every Object have it's own x- and y- position and priority on the screen. Objects with lower priority are drawn first, so Object with the biggest priority will be drawn last.

Objects can be invisible (which means it is not drawn on the screen) and disabled (which means it is neither drawn on the screen nor updates its' state).

## Deriving an Object class

Object have pure virtual functions, so it can't be constructed. If you derive Object class, you'll have to override it's function to get Object you can construct and add to Screen's queue.

Following functions can be overriden in Object class:

##### `void update(Input*)`
This function is called by Screen object. The passed pointer can be used to get current input state and react if necessary.  
Object class' **update()** is pure virtual function.  

----
##### `void draw(SDL_Surface*)`
This function is called by Screen object. The Object should draw itself on given SDL_Surface.  
(If you are using primitive Object classes inside your Object class, you'll need them to draw. Pass the pointer into their **draw()** function and they'll do the work. If you are not using these classes, then you'll have to learn how to draw on SDL_Surfaces.)  
Object class' **draw()** is pure virtual function.  

----
##### `virtual void draw(int x, int y, SDL_Surface*)`
This function should draw the Object itself on given SDL_Surface with given offset by X and Y axes.  
Object class' **draw()** changes coordinates to given and draws itself with previous function. Then it changes coordinates back.

## Object class' functions

There are some setter functions and methods in Object class:

##### `void set_x(int)`
Sets Object's x-position.  

----
##### `void set_y(int)`
Sets Object's y-position.  

----
##### `void set_priority(int)`
Sets Object's priority.  

----
##### `void set_visible(bool)`
Sets Object's visibility. (visible is **true**, invisible is **false**)  

----
##### `void set_enabled(bool)`
Sets either Object is enabled or not. (enabled is **true**, disabled is **false**)    

----
##### `void destruct()`
Makes the Object disappear and free it's memory. It will be removed from Screen's queue automatically.  
   
   
**Previous file:** [Screen class](03_Screen.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Game class](05_Game.md)