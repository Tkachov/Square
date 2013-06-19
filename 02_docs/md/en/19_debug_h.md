# debug.h file

## Overview

debug.h is a file that contains all **#define** directives that control debug features. In Release configuration this file is not included, so all debug features become disabled.

## #defines  

##### `DBG_SHOW_SOFTWARE_CURSOR`
**[string]** filename of software cursor, that will be drawn on game screen (if framerate is low, it will move slow).  
If not defined, usual SDL black&white cursor is used.  

----
##### `DBG_SHOW_HARDWARE_CURSOR`
**[string]** filename of hardware cursor (*.cur), that replaces system cursor (sometimes can blink or be replaced with default system cursor).  
If not defined, usual SDL black&white cursor is used.  

----
##### `DBG_PRINT_WARNINGS`
If defined, warnings will be written in log files.  

----
##### `DBG_PRINT_SPRITE_LOADING`
If defined, sprite loading will be logged.  
(Look **[Loader::load_sprite()](09_Loader.md#sprite-load_spritestring-filename)** function.)  

----
##### `DBG_PRINT_IMAGE_LOADING`
If defined, image loading will be logged.  
(Look **[Loader::load_image()](09_Loader.md#sdl_surface-load_imagestring-filename)** and **[Loader::load_texture()](09_Loader.md#image-load_texturestring-filename-bool-keep_surface--true)** functions.)  

----
##### `DBG_PRINT_STRING_TABLES`
If defined, string tables will be printed out after loading.  
(Look **[String_Table::push_table()](07_String_Table.md#void-push_tablestring-table)** function.)  

----
##### `DBG_STOP_ON_UNALLOCATED_VARIABLE`
If defined, accessing unallocated variable will stop the game.  
Otherwise, pointer to unallocated variable will be 0.  
(Look **[State::persistent()](11_State.md#void-persistentstring-first_key-string-second_key)** function.)  
   
   
**Previous file:** [Fade_Effect class](18_Fade_Effect.md)  
**[Contents](00_Contents.md)**  
**Next file:** [utils.h file](20_utils_h.md)