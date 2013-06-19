﻿# Input class

## Overview

Input class handles user's input each time [Game](05_Game.md) object is asking it to. [Screen](03_Screen.md) objects are given a pointer to Input object, so they can use it to react to user's actions. Screens should notify [Object](04_Object.md)s and pass them a pointer to Input object too, so they are able to react too.

You can determine whether the keys or mouse are pressed, hold or released in this moment. You can also get mouse pointer position. You can also check if user pressed close button, Alt+F4 or trying to kill process using Task Manager.

Furthermore, you can "eat" keys' and mouse's states. For example, the left mouse button was pressed. If you'll check if left mouse button was pressed, you'll get **true**. After you "eat" this state and check if mouse button was pressed again, you'll get **false**. This can be used to prevent one press like a few (for example, if Escape key closes the windows one by one, it will close all of them if you will not "eat" this event).

You can also check if state was "eaten".

Also, you can "pause" and "unpause" the object. It does not changes it's behaviour, but you can make a system where some objects are not reacting to user's actions because of the reasons you need (for example, the hero should not move while the game is paused, but the pause menu should react to user's actions).

Pause is saved between **update()** calls, but the other states are not. So, if you have eaten a key event in one **update()** call, it will not be eaten in next one (if you won't eat it again).

Keys and mouse buttons can have one of these states:
* 0 — is not pressed;
* 1 — just pressed;
* 2 — is hold (was pressed but was not released yet);
* 3 — just released.

State 1 becomes state 2 and state 3 becomes state 0 on the next **update()** if general (pressed/not pressed) state has not changed.

## Functions

##### `short int key(int k)`
Returns current **k** key's state.  

----
##### `short int mouse(int m)`
Returns current **m** mouse button's state.  

----
##### `int mouse_x()`
Returns mouse pointer's x-position.  

----
##### `int mouse_y()`
Returns mouse pointer's y-position.  

----
##### `bool key_eaten(int k)`
Returns whether **k** key's state was eaten during this **update()** call.  

----
##### `void key_eat(int k)`
Eats **k** key's state.  

----
##### `bool mouse_eaten(int m)`
Returns whether **m** mouse button's state was eaten during this **update()** call.  

----
##### `void mouse_eat(int m)`
Eats **m** mouse button's state.  

----
##### `bool key_press(int k, bool eat = false)`
Returns whether **k** key is just pressed (state 1). If **eat** is **true**, eats the state.  

----
##### `bool key_hold(int k, bool eat = false)`
Returns whether **k** key is being hold (state 2). If **eat** is **true**, eats the state.  

----
##### `bool key_release(int k, bool eat = false)`
Returns whether **k** key is just released (state 3). If **eat** is **true**, eats the state.  

----
##### `bool mouse_press(int m, bool eat = false)`
Returns whether **m** mouse button is just pressed (state 1). If **eat** is **true**, eats the state.  

----
##### `bool mouse_hold(int m, bool eat = false)`
Returns whether **m** mouse button is being hold (state 2). If **eat** is **true**, eats the state.  

----
##### `bool mouse_release(int m, bool eat = false)`
Returns whether **m** mouse button is just released (state 3). If **eat** is **true**, eats the state.  

----
##### `bool terminate()`
Returns **true** if user clicked close button, pressed Alt+F4 or trying to kill process using Task Manager.  

----
##### `bool paused()`
Returns whether the object was paused or not.  

----
##### `void pause()`
Pauses the object.  

----
##### `void unpause()`
Unpauses the object.  

----
##### `void repeating(bool)`
Sets whether to repeat keys and button press event (so state 1 can last more than one **update()** call) or not.  
Can be useful for text fields where holding button writes it again and again.  
(You can also set the delay and interval for these events by editing this function.)

## Variables

##### `vector<keychar> keyboard_string`
Contains all the keys that were pressed at this moment in order they have been pressed.  
There are kept only keys that have unicode value.  
**keychar** definition:

     struct keychar {
      string unicode;
      int keycode;
     };

Note that only keys that are just pressed (i.e. have state 1 at this moment) are kept in the variable.  
(For example, if user presses A, B and C keys simultaneously, the vector will contain corresponding keychar structs. If user presses D then, the vector will contain only keychar for D. If user does not presses anything, the vector will be empty.)  
   
   
**Previous file:** [String_Table class](07_String_Table.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Loader class](09_Loader.md)