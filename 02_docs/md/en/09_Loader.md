# Loader class

## Overview

Loader class loads and storages resources. It won't load a file if it was already loaded and will return a loaded resource right away. The object of the class is kept in [Game](05_Game.md) object. Game object provides every [Screen](03_Screen.md) object with a pointer to this Loader, so these can use it's functions.

## Functions

##### `SDL_Surface* load_image(string filename)`
Loads an image from the file with given filename and returns loaded SDL's bitmap surface.  
If loading fails, throws a string with error description.  
Prints messages if **[DBG_PRINT_IMAGE_LOADING](19_debug_h.md#dbg_print_image_loading)** is defined.  

----
##### `Image* load_texture(string filename, bool keep_surface = true)`
Loads an image from the file with given filename and returns [Image](12_Image.md) object that contains loaded OpenGL texture's ID.  
If loading fails, throws a string with error description.  
If **keep_surface** is **true**, SDL's bitmap surface won't be freed and will be passed to Image object too. In this case **load_image()** for given filename will also return this bitmap surface.  
(Note that taking pixel's transparency from OpenGL texture may be slower than taking it from SDL's surface. At the same time, keeping SDL's surface is waste of memory as OpenGL keeps its' own copy of it.)  
Prints messages if **[DBG_PRINT_IMAGE_LOADING](19_debug_h.md#dbg_print_image_loading)** is defined.  

----
##### `TTF_Font* load_font(string fontname, int size)`
Loads a font with given name and size and returns it. Function searches in user's C:\Windows\Fonts\ folder for this font. If this font was not found there, it searches for this font in res\fnt\ folder of your project. It this font was not found there too, it throws a string message.  
If loading fails, it throws a string with error description.  

----
##### `Sprite load_sprite(string filename)`
Loads a file with given name, creates a [Sprite](13_Sprite.md) object which contains the values from this file and returns this Sprite object. All sprite's frames are loaded using **[load_texture()](09_Loader.md#image-load_texturestring-filename-bool-keep_surface--true)**.  
Prints messages if **[DBG_PRINT_SPRITE_LOADING](19_debug_h.md#dbg_print_sprite_loading)** is defined.  

----
##### `bool free_image(string filename)`
Frees memory of SDL's bitmap surface for given file name and returns **true**. If there is no surface for given file name, it returns **false**.  

----
##### `bool free_texture(string filename)`
Frees memory of OpenGL texture for given file name and returns **true**. If there is no texture for given file name, it returns **false**.  
(Note that if there is an SDL's bitmap surface for given file name, it won't be changed.)  

----
##### `bool free_font(string fontname, int size)`
Frees memory of font resource for given font name and size and returns **true**. If there is no font resource for given font name and size, it returns **false**.  

----
##### `void free()`
Frees every SDL's bitmap surface, OpenGL texture and font resource that is storaged in Loader object right now.

## .sprite file structure

First line of file contains two integers: **frames** and **animspeed**.  
Other **frames** lines contains a string and two integers each: **filename x y**.  
**animspeed** is the interval between two sprite's frames (counted in screen redrawing frames), **filename** is the name of file that contains a frame and **x** and **y** are offsets by X and Y axises for this frame.  
   
   
**Previous file:** [Input class](08_Input.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Logger class](10_Logger.md)