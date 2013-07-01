# Window class

## Overview

Window class can be used to show windows on the screen. It inherits both [Object](04_Object.md) and [Screen](03_Screen.md) classes, so it can be placed to Screen's queue and can contain Objects itself. It provides only simplest base for windows and can't be used to create windows in run-time.

Windows are pausing input and unpausing it to update its' own and its' children state.

## Deriving a Window class

As Screen object, Window can (and should) override **[load()](03_Screen.md#void-load)** function. Window class also provides another virtual function:  

##### `void disappear()`
This function destroys the object and removes it from Screen's queue.

You also can override usual Object class virtual functions to make an unique window. Don't forget that you should both handle the input and notify child Objects to handle it.

## Functions  

##### `Window(Game* game, Loader* loader, int x, int y, int priority = 0)`
Constuctor, passes **game** and **loader** to Screen constructor and position and **priority** parameters to Object constructor.  

----
##### `void update()` [inherited from [Screen](03_Screen.md#void-update)]
Updates Objects queue as if **update(Input*, int x_offset, int y_offset)** was called with offset {0,0}.  

----
##### `void redraw()` [inherited from [Screen](03_Screen.md#void-redraw)]
Does nothing.  

----
##### `void draw()` [inherited from [Object](04_Object.md#void-draw)]
Draws Objects queue on the screen.  

----
##### `void draw(int x, int y)` [inherited from [Object](04_Object.md#void-drawint-x-int-y)]
Draws Objects queue on the screen in given point.  

----
##### `void update(Input*, int x_offset = 0, int y_offset = 0)` [inherited from [Object](04_Object.md#void-updateinput-int-x_offset--0-int-y_offset--0)]
Remembers current input pointer and updates Objects queue with given offset.  
   
   
**Previous file:** [Button class](15_Button.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Timer class](17_Timer.md)