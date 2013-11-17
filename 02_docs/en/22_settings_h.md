# settings.h file

## Overview

settings.h is a file that contains all application's **#define** directives and constants. There are also lots of directives for Debug configuration.

## Application's parameters  

### Default options

Options' values are strings, so these **#defines** are strings.  

##### `DEFAULT_WIDTH`
Default application's window's width.  

----

##### `DEFAULT_HEIGHT`
Default application's window's height.  

----

##### `DEFAULT_FULLSCREEN`
Default application's [fullscreen mode](06_Main_Window.md#static-void-create).  

----

##### `DEFAULT_LANGUAGE`
Default application's language.  

### Application's constants

##### `CONFIG_FILENAME`
Defines name of file that should be loaded as options table on launch.  
No file is loaded if not defined.  

----

##### `TITLE_ON_LAUNCH`
Defines title of application on launch.  

----

##### `WINDOW_ICON_BMP`
Defines name of .bmp file that should be used as window's icon on launch.  

----

##### `WINDOW_ICON_PNG`
Defines name of .png file that should be used as window's icon on launch.  
(It will be used only if **WINDOW_ICON_BMP** is not defined.)

----

##### `const int TICKS_PER_SECOND`
Defines how many frames should be drawn per second.

----

##### `const int MAX_FRAMESKIP`
Defines how many frames could be skipped if framerate is low.

----

##### `CALCULATE_FPS`
If equals 1, Square will calculate framerate.

----

##### `SHOW_FPS_IN_CAPTION`
If equals 1, Square will update application's window's caption with current framerate.

## Debug configuration

##### `DEBUG_SAFE_LOG_COPY`
If equals 1, [safe_wstream](20_wstreams.md) will be used to write copy of logs in "full_log.txt" file.

----
##### `DEBUG_SHOW_FPS`
If equals 1, current framerate will be drawn on application's surface.

----
##### `DEBUG_EXCEPTION_ON_UNALLOCATED_VARIABLE`
If equals 1, accessing unallocated variable will stop the game.  
Otherwise, pointer to unallocated variable will be 0.  
(Look **[State::persistent()](09_State.md#static-void-persistentstring-first_key-string-second_key)** function.)  

----
##### `DEBUG_LOG_WARNINGS`
If equals 1, general warnings will be logged.  

----
##### `DEBUG_LOG_SPRITE_LOADING`
If equals 1, sprite loading will be logged.  
(Look **[Resources::load_sprite()](07_Resources.md#sprite-load_spritestring-filename)** function.)  

----
##### `DEBUG_LOG_IMAGE_LOADING`
If equals 1, texture loading will be logged.  
(Look **[Resources::load_texture()](07_Resources.md#frame-load_texturestring-filename)** function.)  

----
##### `DEBUG_LOG_STRING_TABLES`
If equals 1, string tables will be printed out after loading.  
(Look **[String_Table::push_table()](13_String_Table.md#void-push_tablestring-table)** function.)  

----
##### `DEBUG_LOG_FILTERED_EVENTS`
If equals 1, Square will log about filtered events (on Android).  

----
##### `DEBUG_LOG_WINDOW_MODE`
If equals 1, Square will log window/fullscreen mode on launch.  

----
##### `DEBUG_LOG_FPS`
If equals 1, framerate will be logged.
   
   
**Previous file:** [utils.h file](21_utils_h.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Compiling](23_Compiling.md)