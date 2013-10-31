# utils.h file

## Overview

utils.h file contains all useful functions that are used by different classes.  
It contains functions:
* to work with surfaces,
* to draw textures and rectangles,
* to determine whether number is power of 2 or not,
* to find nearest power of 2 that bigger than a number,
* to check whether file exists,
* to read a string from an input stream,
* to deal with numbers, strings and unicode,
* to find the shortest route using A* algorithm.

## Functions  

##### `Uint32 getpixel(SDL_Surface* surface, int x, int y)`
Returns a 4-byte integer that contains pixel RGBA information.  
Pixel is taken from **x**, **y** position in **surface**.  

----
##### `Uint8 get_color_r(SDL_Surface* surface, int x, int y)`
Returns pixel's Red component (0-255).  
Pixel is taken from **x**, **y** position in **surface**.  

----
##### `Uint8 get_color_g(SDL_Surface* surface, int x, int y)`
Returns pixel's Green component (0-255).  
Pixel is taken from **x**, **y** position in **surface**.  

----
##### `Uint8 get_color_b(SDL_Surface* surface, int x, int y)`
Returns pixel's Blue component (0-255).  
Pixel is taken from **x**, **y** position in **surface**.  

----
##### `Uint8 get_color_a(SDL_Surface* surface, int x, int y)`
Returns pixel's Alpha (transparency) component (0-255, where 0 is transparent and 255 is not transparent at all).  
Pixel is taken from **x**, **y** position in **surface**.  

----
##### `SDL_Surface* create_surface(int w, int h, int bits = 32)`
Returns a new SDL's bitmap surface created with given parameters.  

----
##### `SDL_Surface* create_surface(SDL_Surface* to_replace, int w, int h, int bits = 32)`
Returns a new SDL's bitmap surface created with given parameters that replaces **to_replace** SDL's bitmap surface.  

----
##### `Frame* surface_to_texture(SDL_Surface* src, bool delete_after_transform = true)`
Converts given **src** SDL's bitmap surface to OpenGL texture and returns [Frame](12_Frame.md) object that contains a pointer to this texture.  
If **delete_after_transform** is **true**, it will free **src** after convertion.  

----

##### `void draw_frame(Frame& frame, float x, float y, float alpha = 1.0f, float angle = 0, bool center = false)`
Draws given Frame on the screen in given position, with given transparency and angle. If **center** is **true**, center of texture will be in given position.

----

##### `void draw_frame(Frame& frame, float x, float y, SDL_Color blend, float alpha = 1.0f, float angle = 0, bool center = false)`
Draws given Frame on the screen in given position, with given transparency and angle. It will be blended with given color. If **center** is **true**, center of texture will be in given position.

----

##### `void draw_frame(Frame& frame, float x, float y, float w, float h, float alpha = 1.0f, float angle = 0, bool center = false)`
Draws given Frame on the screen in given position, with given size, transparency and angle. If **center** is **true**, center of texture will be in given position.

----

##### `void draw_frame(Frame& frame, float x, float y, float w, float h, SDL_Color blend, float alpha = 1.0f, float angle = 0, bool center = false)`
Draws given Frame on the screen in given position, with given size, transparency and angle. It will be blended with given color. If **center** is **true**, center of texture will be in given position.

----

##### `void draw_texture(float x, float y, float w, float h, bool center = false)`
Draws current binded OpenGL texture on the screen. Takes its' position and sizes. If **center** is **true**, texture's center will be in given position.  

----
##### `void draw_texture(float x, float y, float w, float h, float nw, float nh, float a = 0, bool c = false)`
Draws current binded OpenGL texture resized to **nw** width and **nh** height and rotated to **a** degrees on the screen. Takes its' position and original sizes. If **c** is **true**, texture's center will be in given position.  

----
##### `void draw_texture(...)`
    void draw_texture(
     float W, float H,                          //whole texture width and height
     float px, float py, float pw, float ph,    //piece's position and size
     float nx, float ny, float nw, float nh,    //position on screen and new size
     float angle, bool center = false           //rotation angle and centering option
    )
Draws current binded OpenGL texture's piece resized to **nw** width and **nh** height and rotated to **angle** degrees on the screen. Takes its' position and original texture sizes. If **center** is **true**, texture's center will be in given position. The piece is taken from **px**, **py** position and its' width and height would be **pw** and **ph**.  

----
##### `void draw_rectangle(int x, int y, int w, int h)`
Draws a rectangle of given width and height in given position.  

----
##### `unsigned int nearest2(unsigned int a)`
Returns the nearest power of 2 that is bigger than **a** or is equal to it.  

----
##### `bool is_power2(unsigned int a)`
Returns whether **a** is power of 2 or not.  

----
##### `bool file_exists(const char* name)`
##### `bool file_exists(string& name)`
Retruns whether file with given name exists or not.  

----
##### `void read_file(stringstream& destination, const char* name)`
##### `void read_file(stringstream& destination, string& name)`
Reads whole file with given name into **destination** std::stringstream.

----
##### `string read_string(ifstream&)`
Returns a string that was read from given input stream. If string in this stream starts with **"** symbol, then function reads the whole string between two **"** symbols. Otherwise any space character will be treaten as string's end.  

----
##### `bool delete_file(const char* name)`
##### `bool delete_file(string& name)`
Deletes file with given name and returns whether it was successful (**true**) or not.

----
##### `void itoa(int i, char* buf, int base = 10)`
Writes **i** into **buf** in given numerical base **base**.

----
#### `int atoi(const char* buf)`
Parses an integer in **buf** and returns it.

----
##### `int to_int(string)`
Parses an integer in string and returns it. Skips non-digits characters (except **'+'** and **'-'** before the actual number).  

----
##### `string to_string(int v, int base = 10)`
Returns a string that contains **v** written in given numerical base **base**.  

----
##### `string unichar(Uint16 code)`
Returns a string which contains character(s) that correspond to given **code** in Unicode.  
(Uses your [String_Table::unicode](13_String_Table.md#static-string_table-unicode).)  

----
##### `bool letters_equal(string a, string b)`
Returns whether strings **a** and **b** are equal or not. Considers lower-case and upper-case letters as same (for example, **"FATE"**, **"fate"** and **"FaTe"** are equal strings).  

----
##### `string thousands(int n)`
Returns a string that represents **n**. Thousands will be written as “K” (for example, 5000 will become "5K").  

----
##### `stack<int> A_star(int fx, int fy, int tx, int ty, vector< vector<bool> >& obstacles, int u = 10, int d = 14)`
Implements A* algorithm. Returns a **stack** of indeces that forms a path between **(fx, fy)** and **(tx, ty)**. If there is no way, returns an empty **stack**. **obstacles** should contain **true** if the point is impassable, **u** and **d** represent which moves are “cheaper” (horizontal and vertical cost **u** and diagonal cost **d**).  
   
   
**Previous file:** [wstream and safe_wstream classes](20_wstreams.md)  
**[Contents](00_Contents.md)**  
**Next file:** [settings.h](22_settings_h.md)