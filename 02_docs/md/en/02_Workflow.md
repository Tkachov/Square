# Application's workflow

## The infinite loop

The application's entry point in C and C++ is **main()** function that defined in main.cpp file. There are infinite loop, in which the [Game](05_Game.md) object is created. This loop's design gives you ability to relaunch the game without killing application's process. It may be used to instantly switch video mode or language.

Use **[Game::restart()](05_Game.md#void-restart)** method to restart the application. It will free game's resources and start it again from the screen the method was called from.

Throw **0** if you want to restart the application to free game's resources and start from the first screen without saving game's state.

If some exception was not handled or game was stopped using **[Game::stop()](05_Game.md#void-stop)** method, the infinite loop in **main()** function will be broken.

## Update input & redraw the screen

Game's **[loop()](05_Game.md#void-loop)** contains the infinite loop that handles user's input and redraws the screen. It is designed to make the game perform smoothly in any situation. You can configure it using **TICKS_PER_SECOND** and **MAX_FRAMESKIP** constants.

The main idea of the loop is to separate the input handling and screen redrawing. If possible, screen would be redrawn **TICKS_PER_SECOND** times per second, but if the framerate is low, it would skip some frames. It can't skip more than **MAX_FRAMESKIP** frames in row and it will force screen redrawing if it has skipped **MAX_FRAMESKIP** frames. Redrawing is done by [Screen](03_Screen.md)'s **[redraw()](03_Screen.md#void-redraw)** method that calls its' [Object](04_Object.md)s' **[draw()](04_Object.md#void-draw)** functions.

The user's input is handled by special [Input](08_Input.md) class. It can be handled more than **TICKS_PER_SECOND** times, so the game will react to user's actions faster. Current keyboard and mouse states are stored in Input class. Game object contains the only Input object that is updated in the loop. Screens are getting a pointer to this object, and can use it in **[update()](03_Screen.md#void-update)** method. Screen object passes this pointer to it's objects' **[update()](04_Object.md#void-updateinput-int-x_offset--0-int-y_offset--0)** functions and so these objects can update their states (for example, button can react to mouse button press event and do some action).  
   
   
**Previous file:** [Overview](01_Overview.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Screen class](03_Screen.md)