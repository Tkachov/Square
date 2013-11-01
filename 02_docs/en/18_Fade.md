# Fade class

## Overview

Fade class can be used to create some fade-in or fade-out effects. It inherits [Entity](04_Entity.md) class.  
There are **Fade_Mode** enum, which has the following values:
* **m_FADE_IN**, 
* **m_FADE_OUT**.

**m_FADE_IN** is making something visible from complete invisibility, **m_FADE_OUT** is making the opposite — making something invisible from complete visibility.

## Functions  

##### `Fade(...)`
    Fade(
     Controller* controller,
     Fade_Mode mode, int length,
     SDL_Color color, int width, int height,
     functor* f = 0,
     int x = 0, int y = 0, int priority = 0
    )
Constructor, creates new Fade with given **mode** that will last **length** frames and call **f** after fade effect is complete. It also gets position and **priority** and will draw **width** × **height** rectangle of color **color**.  

----
##### `Fade(...)`
    Fade(
     Controller* controller,
     Fade_Mode mode, int length,
     Sprite* image,
     functor* f = 0,
     int x = 0, int y = 0, int priority = 0
    )
Constructor, creates new Fade_Effect with given **mode** that will last **length** frames and call **f** after fade effect is complete. It also gets position and **priority** and will draw **image**.  

----
##### `void redraw(int x, int y)` [inherited from [Entity](04_Entity.md#void-redrawint-x-int-y)]
Draws the effect on the screen in given point.  

----
##### `void update(int x, int y)` [inherited from [Entity](04_Entity.md#void-updateint-x-int-y)]
Updates the state.  
   
   
**Previous file:** [Button class](17_Button.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Timer class](19_Timer.md) 