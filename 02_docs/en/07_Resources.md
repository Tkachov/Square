# Resources class

## Overview

Resources class loads and storages resources. It won't load a file if it was already loaded and will return a loaded resource right away. It's functions are static, so you can request resource loading from any place in your code.

## Functions

##### `Frame* load_texture(string filename)`
Loads an image from the file with given filename and returns [Frame](12_Frame.md) object that contains loaded OpenGL texture's ID.  
If loading fails, throws a string with error description.  
Prints messages if **[DEBUG_LOG_IMAGE_LOADING](22_settings_h.md#debug_log_image_loading)** equals 1.  

----
##### `Sprite load_sprite(string filename)`
Loads a file with given name, creates a [Sprite](15_Sprite.md) object which contains corresponds to a sprite [described in this file](07_Resources.md#sprite-file-structure) and returns this Sprite object. All sprite's frames are loaded using **[load_texture()](07_Resources.md#frame-load_texturestring-filename)**.  
Prints messages if **[DEBUG_LOG_SPRITE_LOADING](22_settings_h.md#debug_log_sprite_loading)** equals 1. 

----
##### `TTF_Font* load_font(string name, int size)`
Loads a font with given name and size and returns it. Function searches in user's C:\Windows\Fonts\ folder for this font. If this font was not found there, it searches for this font in res\fnt\ folder of your project. It this font was not found there too, it throws a string message.  
If loading fails, it throws a string with error description.  

----
##### `Sprite make_sprite(string filename)`
Creates a Sprite object which contains the only frame that was loaded using **[load_texture()](07_Resources.md#frame-load_texturestring-filename)** from the file with given filename.  

----
##### `bool free_font(string name, int size)`
Frees memory of font resource for given font name and size and returns **true**. If there is no font resource for given font name and size, it returns **false**.  

----
##### `bool free_texture(string filename)`
Frees memory of OpenGL texture for given file name and returns **true**. If there is no texture for given file name, it returns **false**.    

----
##### `void free_textures()`
Frees all OpenGL textures that are storaged in Resources object right now.

## .sprite file structure

First line of file contains two integers: **frames** and **animspeed** (**animspeed** is the interval between two sprite's frames (number of screen redrawings)).  
Other **frames** lines contains a string that describes a frame each. The first character of such line defines the format. Square 0.3.0 supports two formats: 's' and 'w'.  

### Strip frame format

In this format frame's line starts with 's'. It also contains filename, area of image that is drawn on this frame and offsets by X and Y axes for this frame.  

It looks like this: `s <filename> <left> <top> <right> <bottom> <x> <y>`.  
For example, `s tileset.png 128 64 32 32 0 0` will correspond 32x32 frame that is placed on (128, 64) in tileset.png file.  

### Whole image frame format

In this format frame's line starts with 'w' and contains only filename and offsets by X and Y axes for this frame.  

It looks like this: `w <filename> <x> <y>`.  
For example, `w background_image.png 10 10` will correspond to a frame that contains a whole image from background_image.png file and this frame will be drawn with offset 10 by X and Y axes.  
   
   
**Previous file:** [Main_Window class](06_Main_Window.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Input class](08_Input.md)