# Input class

## Overview

Input class handles user's input while application is running. It's functions are static, so you can react to input from any place you want to.

You can determine whether the keys or mouse are pressed, hold or released in this moment. You can also get mouse pointer position. You can also check if user pressed close button, Alt+F4 or trying to kill process using Task Manager.

Furthermore, you can “eat” keys' and mouse's states. For example, the left mouse button was pressed. If you'll check if left mouse button was pressed, you'll get **true**. After you “eat” this state and check if mouse button was pressed again, you'll get **false**. This can be used to prevent one press like a few (for example, if Escape key closes the windows one by one, it will close all of them if you will not “eat” this event).

You can also check if state was “eaten”.

Also, you can “pause” and “unpause” the object. It does not changes it's behaviour, but you can make a system where some objects are not reacting to user's actions because of the reasons you need (for example, the hero should not move while the game is paused, but the pause menu should react to user's actions).

Pause is saved between **update()** calls, but the other states are not. So, if you have eaten a key event in one **update()** call, it will not be eaten in next one (if you won't eat it again).

Keys and mouse buttons can have one of these states:
* 0 — is not pressed;
* 1 — just pressed;
* 2 — is hold (was pressed but was not released yet);
* 3 — just released.

State 1 becomes state 2 and state 3 becomes state 0 on the next **update()** if general (pressed/not pressed) state has not changed.

## Functions

##### `static short int key(SDL_Keycode k)`
Returns current **k** key's state.  

----
##### `static bool key_press(SDL_Keycode k, bool eat = false)`
Returns whether **k** key is just pressed (state 1). If **eat** is **true**, eats the state.  

----
##### `static bool key_hold(SDL_Keycode k, bool eat = false)`
Returns whether **k** key is being hold (state 2). If **eat** is **true**, eats the state.  

----
##### `static bool key_release(SDL_Keycode k, bool eat = false)`
Returns whether **k** key is just released (state 3). If **eat** is **true**, eats the state. 

----
##### `static bool key_eaten(SDL_Keycode k)`
Returns whether **k** key's state was eaten during this **update()** call.  

----
##### `static short int mouse(Uint8 b)`
Returns current **b** mouse button's state.  

----
##### `static bool mouse_press(Uint8 m, bool eat = false)`
Returns whether **b** mouse button is just pressed (state 1). If **eat** is **true**, eats the state.  

----
##### `static bool mouse_hold(Uint8 m, bool eat = false)`
Returns whether **b** mouse button is being hold (state 2). If **eat** is **true**, eats the state.  

----
##### `static bool mouse_release(Uint8 m, bool eat = false)`
Returns whether **b** mouse button is just released (state 3). If **eat** is **true**, eats the state.  

----
##### `static bool mouse_eaten(Uint8 b)`
Returns whether **b** mouse button's state was eaten during this **update()** call.  

----
##### `static int mouse_x()`
Returns mouse pointer's x-position.  

----
##### `static int mouse_y()`
Returns mouse pointer's y-position.  

----
##### `static int wheel_x()`
Returns the amount scrolled horizontally during this **update()** call.  

----
##### `static int wheel_y()`
Returns the amount scrolled vertically during this **update()** call.  

----
##### `static bool app_paused()`
Returns whether the application is paused or not (application is paused on Android when your application is not in the foreground).

----
##### `static bool paused()`
Returns whether the object was paused or not.  

----
##### `static bool quit()`
Returns **true** if user clicked close button, pressed Alt+F4 or trying to kill process using Task Manager.  

----
##### `static void key_eat(SDL_Keycode k)`
Eats **k** key's state.  

----
##### `static void mouse_eat(Uint8 b)`
Eats **b** mouse button's state.  

----
##### `static void pause()`
Pauses the object.  

----
##### `static void unpause()`
Unpauses the object.  

## Variables

##### `string keyboard_string`
Contains the text that was written by user during this **update()** call.  
   
   
**Previous file:** [Resources class](07_Resources.md)  
**[Contents](00_Contents.md)**  
**Next file:** [State class](09_State.md)