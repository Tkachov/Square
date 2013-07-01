# Button class

## Overview

Button class is used to create buttons. It inherits [Object](04_Object.md) class.  
When the button is pressed, it calls a function that is passed by a pointer to [functor](06_Using_functors.md) class.  
There are four button states:
* “up”, which means the pointer is outside of the button;
* “over”, which means the pointer is on the button;
* “pressed”, which means the pointer is on the button and the mouse button is pressed or being hold;
* “disabled”, which means the button doesn't react to user's actions.

Every state can have its' own [Sprite](13_Sprite.md) object.

The button contains [Text](14_Text.md) label, which can draw text over button's state's sprite.

## Deriving a Button class

Button is an Object object, so its' **[update()](04_Object.md#void-updateinput)** and **[draw()](04_Object.md#void-drawsdl_surface)** functions can (and should) be overriden. But the Button class itself have some protected functions that control its' behaviour:  

##### `void redraw()`
This function is called every time button should be redrawn (when state, font or something else was changed).  
Function updates button's state.  

----
##### `void update_label()`
This function should be called every time label or button has changed so text label will be placed where it should be.  
Usually is called from **[redraw()](15_Button.md#void-redraw)**.

## Functions  

##### `Button(functor* = 0)`
Constructor, can take a pointer to functor which will be used when button is pressed.  

----
##### `void draw()` [inherited from [Object](04_Object.md#void-draw)]
Draws itself on the screen.  

----
##### `void draw(int x, int y)` [inherited from [Object](04_Object.md#void-drawint-x-int-y)]
Draws itself on the screen in given point.  

----
##### `void update(Input*)` [inherited from [Object](04_Object.md#void-updateinput)]
Updates its' state and calls a function if mouse was pressed.  

----
##### `void set_up_state(Sprite)`
Sets a Sprite object for “up” state.  

----
##### `void set_over_state(Sprite)`
Sets a Sprite object for “over” state.  

----
##### `void set_pressed_state(Sprite)`
Sets a Sprite object for “pressed” state.  

----
##### `void set_disabled_state(Sprite)`
Sets a Sprite object for “disabled” state.  

----
##### `void set_states(Sprite up, Sprite over, Sprite pressed, Sprite disabled)`
Sets a Sprite objects for “up”, “over”, “pressed” and “disabled” states.  

----
##### `void set_font(TTF_Font*)`
Sets a font for text label.  

----
##### `void set_color(SDL_Color)`
Sets a color for text label.  

----
##### `void set_text(string)`
Sets a text for text label.  

----
##### `void set_label(TTF_Font* font, SDL_Color color, string text)`
Sets font, color and text for text label.  

----
##### `void set_func(functor*)`
Sets a pointer to functor object.  

----
##### `void set_pixel_perfect(bool)`
Sets “pixel perfect” option.  
If **true**, button will check whether mouse pointer is on non-transparent area of state's sprite or not.  
Otherwise, button will check whether mouse position is inside button's borders rectangle or not (which is simpler).  

----
##### `void set_disabled(bool)`
Sets whether button is disabled or not. (disabled is **true**, enabled is **false**)  
If button is disabled, it will have “disabled” state and won't react to user's actions.  

----
##### `void set_holding_click_delay(int delay)`
Sets the interval between function calls if mouse button is being hold.  
If **delay** is 0, function will be called once button is just pressed.  
Otherwise, function will be called every **delay** frames while mouse button is being hold.  

----
##### `bool is_disabled()`
Returns whether button is disabled or not. (disabled is **true**, enabled is **false**)  
   
   
**Previous file:** [Text class](14_Text.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Window class](16_Window.md) 

