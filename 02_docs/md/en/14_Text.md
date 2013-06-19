﻿# Text class

## Overview

Text class is used to create text labels and draw those on the screen. It inherits [Object](04_Object.md) class. The label can change its' text, font, color, width and antialiasing in run-time (i.e. you don't have to create a new label to change these parameters).

If pointer to font is 0, text won't be drawn until font is replaced with valid pointer.

If label's width is 0 or is negative, text won't have limited width. Otherwise text will be carried over to the next line if necessary (i.e. width limit is exceeded).

## Functions  

##### `Text(TTF_Font*, string = "", int w = 0, SDL_Color = SDL_Color(), int x = 0, int y = 0, int priority = 0)`
Constructor, that requires a font and can also get default text, label's width, color, position and priority.  

----
##### `virtual void draw(SDL_Surface*)` [inherited from [Object](04_Object.md#void-drawsdl_surface)]
Draws the text on the screen.  

----
##### `virtual void draw(int,int,SDL_Surface*)` [inherited from [Object](04_Object.md#virtual-void-drawint-x-int-y-sdl_surface)]
Draws the text on the screen with given offset by X and Y axes.  

----
##### `virtual void update(Input*)` [inherited from [Object](04_Object.md#void-updateinput)]
Does nothing.  

----
##### `string const text()`
Returns current text.  

----
##### `Image* const img()`
Returns a pointer to [Image](12_Image.md) object that contains SDL's bitmap surface with current text drawn. Can be used to determine text's real width or height.  

----
##### `int const width()`
Returns label's width limit.  

----
##### `void set_font(TTF_Font* font)`
Sets new font and redraws the label.  
If **font** is 0 or equals to current label's font pointer, it does nothing.  

----
##### `void set_text(string text)`
Sets new text and redraws the label.  
If **text** equals to current label's text, it does nothing.  

----
##### `void set_color(SDL_Color& color)`
Sets new color and redraws the label.  
If **color** equals to current label's color, it does nothing.  

----
##### `void set_antialias(bool aa)`
Sets new antialiasing and redraws the label.  
If **aa** equals to current label's antialiasing option, it does nothing.  
If **aa** is **true**, antialiasing is turned on, otherwise it is turned off.  

----
##### `void set_width(int width)`
Sets new width limit and redraws the label.  
If **width** equals to current label's width limit, it does nothing.  
   
   
**Previous file:** [Sprite class](13_Sprite.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Button class](15_Button.md)