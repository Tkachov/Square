﻿# Sprite class

## Overview

Sprite class can be used to draw images and animations on the screen. It inherits [Object](04_Object.md) class. Sprites can be created manually, though it's recommended to load it using **[Loader::load_sprite()](09_Loader.md#sprite-load_spritestring-filename)** function.

## Functions

##### `Sprite()`
Constructor, creates an empty sprite (with no frames at all).  

----
##### `Sprite(Image i)`
Constructor, creates a sprite with one frame which is given [Image](12_Image.md).  

----
##### `virtual void draw(SDL_Surface*)` [inherited from [Object](04_Object.md#void-drawsdl_surface)]
Draws sprite's frame on the screen.  

----
##### `virtual void draw(int,int,SDL_Surface*)` [inherited from [Object](04_Object.md#virtual-void-drawint-x-int-y-sdl_surface)]
Draws sprite's frame on the screen with given offset by X and Y axes.  

----
##### `virtual void update(Input*)` [inherited from [Object](04_Object.md#void-updateinput)]
Does animating.  

----
##### `void set_frame(GLuint* texture, SDL_Surface* bitmap, int width, int height, int pw, int ph)`
Replaces all sprite's frames with one new frame which is Image, created from given texture, bitmap and their width and height parameters.  

----
##### `void add_frame(GLuint* texture, SDL_Surface* bitmap, int width, int height, int pw, int ph)`
Adds one new frame which is Image, created from given texture, bitmap and their width and height parameters.  

----
##### `void set_frame(Image)`
Replaces all sprite's frames with one new frame which is given Image.  

----
##### `void add_frame(Image)`
Adds one new frame which is given Image.  

----
##### `GLuint* const frame(unsigned int k = 0)`
Returns a pointer to **k**th frame's texture or 0 if **k**th frame doesn't exists.  

----
##### `unsigned int current_index()`
Returns an index of current frame (i.e. frame which is drawn at this moment).  

----
##### `GLuint* const current_frame()`
Returns a pointer to current frame's texture (or 0, if there are no frames at all).  

----
##### `Image const image(unsigned int k = 0)`
Returns an Image object corresponding to **k**th frame. If **k**th frame doesn't exists, returns an empty Image (i.e. `Image(0,0,0,0,0,0)`).

----
##### `Image const current_image()`
Returns an Image object corresponding to current frame (or an empty Image, if there are no frames at all).  

----
##### `SDL_Surface* const bitmap(unsigned int k = 0)`
Returns a pointer to **k**th frame's bitmap surface or 0 if **k**th frame doesn't exists.  

----
##### `SDL_Surface* const current_bitmap()`
Returns a pointer to current frame's bitmap surface (or 0, if there are no frames at all).  

----
##### `int animation_speed()`
Returns interval between two frames.  

----
##### `int w()`
Returns sprite's width. Sprite's width is maximal frames' width.  

----
##### `int h()`
Returns sprite's height. Sprite's height is maximal frames' height.  

----
##### `unsigned int length()`
Returns frames count.  

----
##### `void set_index(unsigned int k)`
Sets current index to **k**.  

----
##### `void set_speed(int s)`
Sets interval between two frames to **s**.  

----
##### `bool is_intersected(int mx, int my)`
Returns whether sprite's current frame is intersected in **mx**, **my** position (i.e. **mx**, **my** pixel is not transparent) or not.  
   
   
**Previous file:** [Image class](12_Image.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Text class](14_Text.md)