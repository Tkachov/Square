# Timer class

## Overview

Timer class can be used to call a function with some interval. It inherits [Object](04_Object.md) class, but does not draw anything on the screen.

Timer will stop after it called a function **N** times, if **N** is positive (neither negative nor zero).

## Functions

##### `Timer(int interval, int N, functor* f)`
Constructor, creates a Timer that calls **f** every **interval** frames **N** times (or doesn't stop calling it if **N** is zero or negative).  
   
   
**Previous file:** [Window class](16_Window.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Fade_Effect class](18_Fade_Effect.md)