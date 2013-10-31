# Controller class

## Overview

Controller class is responsible for some general actions. The pointer to the object of this class is given to every [Entity](04_Entity.md) so those can use Controller when needed.

## Functions  

----
##### `void stop_loop()`
Stops the application loop.  

----
##### `void restart_loop(bool keep_state)`
Relaunches the application.  
Can be used to apply options' changes (if those are critical and require relaunch).
If **keep_state** is **true**, [State](09_State.md) is kept and all “persistent” variables' values will be the same after relaunch.  

----
##### `void open_screen(Screen* screen)`
Opens Screen **screen**.  

----
##### `void open_screen(ScreenID sid, bool recreate = false)`
Opens Screen with ScreenID **sid**.  
Creates a new instance of the Screen if **recreate** is **true**.  
This function works only if you have added your Screen-deriving class in **[create_screen()](03_Screen.md#screenid)** function!   

----
##### `void save(string filename)`
Saves current application state in file with name **filename** in the subfolder "saves".  

----
##### `void load(string filename)`
Loads application state from file with name **filename** from the subfolder "saves".  
 
----
##### `string get_option(string key)`
Returns value for option with name **key**.  

----
##### `void set_option(string key, string value)`
Replaces value of option with name **key** with **value**.

----
##### `void save_options()`
Saves options in **[CONFIG_FILENAME](22_settings_h.md#CONFIG_FILENAME)** file if such constant is defined.  
   
   
**Previous file:** [Entity class](04_Entity.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Main_Window class](06_Main_Window.md)