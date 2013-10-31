# Application's workflow

## The infinite loop

The application's entry point in C and C++ is **main()** function that defined in main.cpp file. There are infinite loop, which is designed to give you ability to relaunch the game without killing application's process. It may be used to instantly switch video mode or language.

Use **[Controller::restart_loop()](05_Controller.md#void-restart_loop)** method to restart the application. It will free game's resources and start it again from the screen the method was called from (if you pass **false** in this function, it will be started from the first screen without saving game's state).

If some exception was not handled or game was stopped using **[Controller::stop_loop()](05_Controller.md#void-stop_loop)** method, the infinite loop in **main()** function will be broken and the application will be stopped.

## Update input & redraw the screen

The infinite loop that handles user's input and redraws the screen is designed to make the game perform smoothly in any situation. You can configure it using **TICKS_PER_SECOND** and **MAX_FRAMESKIP** constants in [settings.h](22_settings_h.md) file.

The main idea of the loop is to separate the input handling and screen redrawing. If possible, screen would be redrawn **TICKS_PER_SECOND** times per second, but if the framerate is low, it would skip some frames. It can't skip more than **MAX_FRAMESKIP** frames in row and it will force screen redrawing if it already skipped **MAX_FRAMESKIP** frames. Redrawing is done by [Screen](03_Screen.md)'s **[redraw()](03_Screen.md#void-redraw)** method that calls its' [Entities](04_Entity.md)' **[redraw()](04_Entity.md#void-redraw)** methods.

The user's input is handled by special [Input](08_Input.md) class. It can be handled more than **TICKS_PER_SECOND** times, so the game will react to user's actions faster. Current keyboard and mouse states are stored in Input class. All its' methods are static, so you can use it anywhere you want. State updating is done by Screen's **[update()](03_Screen.md#void-update) method. It calls its' Entities' **[update()](04_Entity.md#void-update)** functions and so these objects can update their states too (for example, button can react to mouse button press event and do some action).
   
   
**Previous file:** [Overview](01_Overview.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Screen class](03_Screen.md)