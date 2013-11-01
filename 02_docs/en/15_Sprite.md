# Sprite class

## Overview

Sprite class should be used to draw images and animations on the display. It inherits [Entity](04_Entity.md) class. Sprites can be created manually, though it's recommended to load it using **[Resources::load_sprite()](07_Resources.md#sprite-load_spritestring-filename)** function.

## Functions

##### `Sprite(Controller* controller)`
Constructor, creates an empty sprite (with no frames at all).  

----
##### `Sprite(Controller* controller, Frame f)`
Constructor, creates a sprite with one frame which is given [Frame](12_Frame.md).  

----
##### `void redraw(int x, int y)` [inherited from [Entity](04_Entity.md#void-redrawint-x-int-y)]
Draws current Sprite's frame on the display.  

----
##### `void update(int x, int y)` [inherited from [Entity](04_Entity.md#void-updateint-x-int-y)]
Animates Sprite (changes current frame when needed).  

----
##### `void set_frame(Frame f)`
Replaces all Sprite's frames with given Frame.  

----
##### `void add_frame(Frame f)`
Adds given Frame to the Sprite.  

----
##### `GLuint* const texture(unsigned int k = 0)`
Returns a pointer to **k**th frame's texture or 0 if **k**th frame doesn't exists.  

----
##### `unsigned int current_index()`
Returns an index of current frame (i.e. frame which is drawn at this moment).  

----
##### `GLuint* const current_texture()`
Returns a pointer to current frame's texture (or 0, if there are no frames at all).  

----
##### `Frame const frame(unsigned int k = 0)`
Returns a Frame object corresponding to **k**th frame. If **k**th frame doesn't exists, returns an empty Frame (i.e. `Frame(0,0,0,0,0,0,0)`).

----
##### `Frame const current_frame()`
Returns a Frame object corresponding to current frame (or an empty Frame, if there are no frames at all).  

----
##### `int animation_speed()`
Returns interval between two frames.  

----
##### `int left()`
Returns Sprite's left border.  

----
##### `int top()`
Returns Sprite's top border.  

----
##### `int right()`
Returns Sprite's right border.  

----
##### `int bottom()`
Returns Sprite's bottom border.  

----
##### `int width()`
Returns sprite's width.  

----
##### `int height()`
Returns sprite's height.  

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
Returns whether Sprite's current frame is intersected in **mx**, **my** position (i.e. **mx**, **my** pixel is not transparent) or not.  
   
   
**Previous file:** [Window class](14_Window.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Text class](16_Text.md)