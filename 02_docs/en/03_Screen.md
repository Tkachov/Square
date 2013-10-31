# Screen class

## Overview

Screen objects are the main containers of [Entities](04_Entity.md) that are drawn on the display.

Every Screen have it's ScreenID in ScreenID.h file to distinguish different Screens from each other. There are two ways of starting a new Screen — passing a Screen pointer to Controllers's **[open_screen()](05_Controller.md#void-open_screenscreen-screen)** or passing a ScreenID to it's overloaded version, **[open_screen()](05_Controller.md#void-open_screenscreenid-sid-bool-recreate--false)**, which will create the necessary Screen object automatically.

Screens can be “static”. It means the object will be automatically storaged and won't be created again. Static Screen objects are saving their state even if some other Screens were opened. You can also force recreating Screen object (for example, if you want to start a new game) by calling **[Controller::open_screen()](05_Controller.md#void-open_screenscreenid-sid-bool-recreate--false)** with ScreenID and **true** parameters.

Screen actually derives Entity class, so there are some functions of Entity which can be overriden. It also means you can put Screen in Screen if needed.


## Deriving a Screen class

The actual Screen object is ready to be opened, though it doesn't do or contain anything. So if you derive Screen class, you get a working class even if you don't override any of it's virtual functions.

Following functions can be overriden in Screen class:

##### `void start()`
This function is called every time Screen object is opened.  
(For example, you can check if the Screen is opened first time and do something special.)  
Screen class' **start()** does nothing.  

----
##### `void save_state(ofstream& fout)`
This function is called when application saves the state into given output stream. It should be used to save the information that will not be available in next session so it could be restored.  
(For example, menu should not save it's state because it is always the same. But level where player could've replaced something should save its' state.)  
Screen class' **save_state()** does nothing.  

----
##### `void load_state(ifstream& fin)`
This function is called when application loads the state from given input stream. It should be used to load the information that was saved by previous function.  
(For example, you should restore the level you have saved.)  
Screen class' **load_state()** does nothing.  

----
##### `ScreenID id()`
This function should return corresponding ScreenID so this class' objects can be distinguished from others. You *must* override this function. 
Screen class' **id()** returns **s_UNKNOWN_ID**, which is defined in ScreenID.h file.

----
##### `bool is_static()`
This function returns whether Screen is static or not. Every Screen contains a **_static** member which can be set to a **true** or **false** in constructor.
Screen class' returns **false**.


## ScreenID

Every Screen should have an index. Those are defined in ScreenID.h file. When you derive Screen class, you should add a new index in ScreenID enum and edit **create_screen()** in ScreenID.cpp to construct your class by your ID. That's how application will distinguish your class from others. 
   
   
**Previous file:** [Workflow](02_Workflow.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Object class](04_Object.md)