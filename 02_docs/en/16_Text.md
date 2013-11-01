# Text class

## Overview

Text class is used to create text labels and draw those on the display. It inherits [Entity](04_Entity.md) class. The label can change its' text, font, color, width and antialiasing in run-time (i.e. you don't have to create a new label to change these parameters).

If pointer to font is 0, text won't be drawn until font is replaced with valid pointer.

If label's width is 0, text won't have limited width. Otherwise text will be carried over to the next line if necessary (i.e. width limit is exceeded).

## Functions  

##### `Text(...)`
    Text(
     Controller*,
     TTF_Font*,
     string text = "", unsigned int width = 0,
     SDL_Color color = SDL_Color(),
     int x = 0, int y = 0, int priority = 0
    )
Constructor, that passes [Controller](05_Controller.md) to Entity's constructor, requires a font and can also get default text, label's width, color, position and priority.  

----
##### `void redraw(int x, int y)` [inherited from [Entity](04_Entity.md#void-redrawint-x-int-y)]
Draws the Text on the display in given point.  

----
##### `void update(int x, int y)` [inherited from [Entity](04_Entity.md#void-updateint-x-int-y)]
Does nothing.  

----
##### `bool antialiasing()`
Returns whether Text label using antialiasing.  

----
##### `SDL_Color color()`
Returns Text's color.  

----
##### `TTF_Font* const font()`
Returns Text's font.  

----
##### `Frame* const label()`
Returns a pointer to a [Frame](12_Frame.md) object that contains OpenGL's texture ID for current label. Can be used to determine label's real width or height.  

----
##### `string const text()`
Returns current text.  

----
##### `unsigned int const width()`
Returns label's width limit.  

----
##### `void set_antialiasing(bool aa)`
Sets whether label should use antialiasing and redraws it.  
If **aa** equals to current label's antialiasing option, it does nothing.  
If **aa** is **true**, antialiasing is turned on, otherwise it is turned off.  

----
##### `void set_color(SDL_Color& color)`
Sets new color and redraws the label.  
If **color** equals to current label's color, it does nothing.  

----
##### `void set_font(TTF_Font* font)`
Sets new font and redraws the label.  
If **font** is 0 or equals to current label's font pointer, it does nothing.  

----
##### `void set_text(string text)`
Sets new text and redraws the label.  
If **text** equals to current label's text, it does nothing.  

----
##### `void set_width(unsigned int width)`
Sets new width limit and redraws the label.  
If **width** equals to current label's width limit, it does nothing.  
   
   
**Previous file:** [Sprite class](15_Sprite.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Button class](17_Button.md)