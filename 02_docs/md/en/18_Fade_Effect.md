# Fade_Effect class

## Overview

Fade_Effect class can be used to create some fade-in or fade-out effects. It inherits [Object](04_Object.md) class.  
There are **Fade_Mode** enum, which has the following values:
* **m_FADE_IN**, 
* **m_FADE_OUT**,
* **m_IMAGE_IN**,
* **m_IMAGE_OUT**.

**m_FADE_IN** and **m_IMAGE_IN** are making something visible from complete invisibility, **m_FADE_OUT** and **m_IMAGE_OUT** are making the opposite — making something invisible from complete visibility.

**m_IMAGE_IN** and **m_IMAGE_OUT** can be used to make fade-in or fade-out effect with image.  
**m_FADE_IN** and **m_FADE_OUT** can be used to make fade-in or fade-out effect with color.

## Functions  

##### `Fade_Effect(Fade_Mode mode, int delay, functor* func = 0, int x = 0, int y = 0, int priority = 0)`
Constructor, creates new Fade_Effect with given **mode** that will last **delay** frames and call **func** after fade effect is complete. It also gets position and **priority** for Object constructor.  

----
##### `void draw()` [inherited from [Object](04_Object.md#void-draw)]
Draws the effect on the screen.  

----
##### `void draw(int x, int y)` [inherited from [Object](04_Object.md#void-drawint-x-int-y)]
Draws the effect on the screen in given point.  

----
##### `void update(Input*, int = 0, int = 0)` [inherited from [Object](04_Object.md#void-updateinput-int-x_offset--0-int-y_offset--0)]
Updates the state.  

----
##### `void color_mode(int r, int g, int b, int w, int h)`
This function can be called to set **m_FADE_IN** or **m_FADE_OUT** modes color and width and height parameters.  

----
##### `void image_mode()`
This function can be called to switch to **m_IMAGE_IN** or **m_IMAGE_OUT** modes.  

----
##### `Sprite* spr()`
Returns a pointer to [Sprite](13_Sprite.md) object which can be changed.  
   
   
**Previous file:** [Timer class](17_Timer.md)  
**[Contents](00_Contents.md)**  
**Next file:** [debug.h file](19_debug_h.md) 