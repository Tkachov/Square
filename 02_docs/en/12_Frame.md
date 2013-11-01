# Frame class

## Overview

Frame class is used by engine to storage textures and information about it. Objects of this class are used by [Sprite](15_Sprite.md) class. You can construct and use it manually if you want. Frames are returned by [Resources::load_texture()](07_Resources.md#frame-load_texturestring-filename) function and can be drawn on the display with [draw_frame()](21_utils_h.md#void-draw_frame) functions.

## Functions  

##### `Frame(...)`
    Frame(
     GLuint* gl_texture, int width, int height,
     int left, int top, int right, int bottom,
     vector< vector<char> >& mask,
     int x_shift = 0, int y_shift = 0
    )
Constructs a Frame with OpenGL's texture ID **gl_texture** (which has size **width*****height**). This Frame will use rectangle area from **left**, **top** to **right**, **bottom** of the texture. It also takes mask array where 0 means transparent pixel and 1 means non-transparent. You can also provide offset values by X and Y axes for this frame. 

----
##### `GLuint* texture()`
Returns OpenGL's texture ID.  

----
##### `int texture_width()`
Returns texture width (can be only power of 2).  

----
##### `int texture_height()`
Returns texture height (can be only power of 2).  

----
##### `int left()`
Returns left border of rectangle area of the texture.  

----
##### `int top()`
Returns top border of rectangle area of the texture.  

----
##### `int right()`
Returns right border of rectangle area of the texture.  

----
##### `int bottom()`
Returns bottom border of rectangle area of the texture.  

----
##### `int width()`
Returns rectangle area width.  

----
##### `int height()`
Returns rectangle area height.  

----
##### `bool is_intersected(int x, int y)`
Returns whether **x**, **y** pixel of rectangle area is non-transparent or not.

----
##### `void set_x_shift(int)`
Sets offset by X axis.  

----
##### `void set_y_shift(int)`
Sets offset by Y axis.

----
##### `void set_shift(int x, int y)`
Sets offset by X and Y axes.  

----
##### `void set_area(int l, int t, int r, int b)`
Sets rectangle area of the texture that will be drawn by this Frame.
   
   
**Previous file:** [Functor class](11_Functor.md)  
**[Contents](00_Contents.md)**  
**Next file:** [String_Table class](13_String_Table.md)