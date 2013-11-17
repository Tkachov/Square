# Button class

## Overview

Button class is used to create buttons. It inherits [Entity](04_Entity.md) class.  
When the button is pressed, it calls a function that is passed by a pointer to [functor](11_Functor.md) class.  
There are four button states:
* “up”, which means the pointer is outside of the button;
* “over”, which means the pointer is on the button;
* “pressed”, which means the pointer is on the button and the mouse button is pressed or being hold;
* “disabled”, which means the button doesn't react to user's actions.

Every state can have its' own [Sprite](15_Sprite.md) object.

The button contains [Text](16_Text.md) label, which can draw text over button's state's sprite.

## Functions  

##### `Button(Controller*, functor* = 0)`
Constructor, passes [Controller](05_Controller.md) to Entity's constructor and takes a pointer to functor which will be used when button is pressed.  

----
##### `void redraw(int x, int y)` [inherited from [Entity](04_Entity.md#void-redrawint-x-int-y)]
Draws itself on the display in given point.  

----
##### `void update(int x, int y)` [inherited from [Entity](04_Entity.md#void-updateint-x-int-y)]
Updates its' state and calls a function if mouse was pressed on it.  

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
##### `void set_color(SDL_Color)`
Sets a color for text label.  

----
##### `void set_font(TTF_Font*)`
Sets a font for text label.  

----
##### `void set_text(string)`
Sets a text for text label.  

----
##### `void set_label(SDL_Color color, TTF_Font* font, string text)`
Sets color, font and text for text label.  

----
##### `void set_disabled(bool)`
Sets whether button is disabled or not. (disabled is **true**, enabled is **false**)  
If button is disabled, it will have “disabled” state and won't react to user's actions.  

----
##### `void set_func(functor*)`
Sets a pointer to functor object.  

----
##### `void set_holding_click_delay(int delay)`
Sets the interval between function calls if mouse button is being hold.  
If **delay** is 0, function will be called once button is just pressed.  
Otherwise, function will be called every **delay** frames while mouse button is being hold.  

----
##### `bool is_disabled()`
Returns whether button is disabled or not. (disabled is **true**, enabled is **false**)  
   
   
**Previous file:** [Text class](16_Text.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Fade class](18_Fade.md) 

