# Timer class

## Overview

Timer class can be used to call a function with some interval. It inherits [Entity](04_Entity.md) class, but does not draw anything on the screen.

Timer will stop after it called a function **N** times, if **N** is positive (neither negative nor zero).

## Functions

##### `Timer(Controller*, int interval, int N, functor* f)`
Constructor, creates a Timer that calls **f** every **interval** frames **N** times (or doesn't stop calling it if **N** is zero or negative).  

----
##### `void redraw(int x, int y)` [inherited from [Entity](04_Entity.md#void-redrawint-x-int-y)]
Does nothing.  

----
##### `void update(int x, int y)` [inherited from [Entity](04_Entity.md#void-updateint-x-int-y)]
Updates Timer's state and calls its' functor if needed.  
   
   
**Previous file:** [Fade class](18_Fade.md)  
**[Contents](00_Contents.md)**  
**Next file:** [wstream and safe_wstream classes](20_wstreams.md)