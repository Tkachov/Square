﻿# Image class

## Overview

Image class is used by engine to storage textures (and corresponding bitmaps). It inherits [Object](04_Object.md) class, so you can use Image objects to place a static picture on the screen (pointer to Image is returned by **[Loader::load_texture()](09_Loader.md#image-load_texturestring-filename-bool-keep_surface--true)**). It's recommended to use [Sprite](13_Sprite.md) class though.

## Functions  

##### `void draw(SDL_Surface*)` [inherited from [Object](04_Object.md#void-drawsdl_surface)]
Draws the texture this object contains.  

----
##### `void draw(int x, int y, SDL_Surface*)` [inherited from [Object](04_Object.md#virtual-void-drawint-x-int-y-sdl_surface)]
Draws the texture this object contains with offset by X and Y axes.  

----
##### `void update(Input*)` [inherited from [Object](04_Object.md#void-updateinput)]
If mouse pointer is on the texture and intersects it, then "eats" mouse move event. If **this.eat_click** is **true**, "eats" mouse click event too.  

----
##### `GLuint* const img()`
Returns OpenGL's texture ID.  

----
##### `SDL_Surface* const bmp()`
Returns SDL's bitmap surface.  

----
##### `bool eating_clicks()`
Returns whether **this.eat_click** is **true** or not.  
(Look **[void update(Input*)](12_Image.md#void-updateinput-inherited-from-object)**.)  

----
##### `int w()`
Returns bitmap width.  

----
##### `int h()`
Returns bitmap height.  

----
##### `int pw()`
Returns texture width (can be only power of 2).  

----
##### `int ph()`
Returns texture height (can be only power of 2).  

----
##### `void set_eating_clicks(bool)`
Sets **this.eat_click** value.  
(Look **[void update(Input*)](12_Image.md#void-updateinput-inherited-from-object)**.)  

----
##### `void set_img(GLuint*)`
Sets OpenGL's texture ID. Does not free the memory of previous texture ID.  

----
##### `void set_bmp(SDL_Surface* s)`
Sets SDL's bitmap surface. Does not free the memory of previous bitmap surface.  
   
   
**Previous file:** [State class](11_State.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Sprite class](13_Sprite.md)