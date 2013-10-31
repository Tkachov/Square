# Entity class

## Overview

Entities are doing work, updating the state and drawing itself on the screen. Entities may have “children” Entities.

Every Entity have it's own x- and y- position and priority on the screen. Entities with lower priority are drawn first, so Entity with the biggest priority will be drawn last.

Entities can be invisible (which means it is not drawn on the screen) and disabled (which means it is neither drawn on the screen nor updates its' state).

Entities are getting a pointer to [Controller](05_Controller.md) in constructor and keep it, so they can request some actions when needed.

## Deriving an Entity class

Following functions may be overriden in Entity class:

##### `void redraw(int x, int y)`
When this function is called, the Entity should draw itself in given position (it can ignore these coordinates though).  
Entity class' **redraw()** calls virtual **[draw_before_queue()](04_Entity.md#void-draw_before_queueint-x-int-y)**, then redraws all its' “children” Entities and calls virtual **[draw_after_queue()](04_Entity.md#void-draw_after_queueint-x-int-y)**. That's why you should override one of those (or both) if you don't need something more complicated.  

----
##### `void update(int x, int y)`
When this function is called, the Entity should update itself like it is in given position (it can ignore these coordinates though).  
Entity class' **redraw()** calls virtual **[update_before_queue()](04_Entity.md#void-update_before_queueint-x-int-y)**, then updates all its' “children” Entities and calls virtual **[update_after_queue()](04_Entity.md#void-update_after_queueint-x-int-y)**. That's why you should override one of those (or both) if you don't need something more complicated.

----
##### `void redraw_before_queue(int x, int y)`
This function is called by the Entity itself before its' “children” Entities are drawn. Given position is the same that was passed to **[redraw()](04_Entity.md#void-redraw)**.

----
##### `void redraw_after_queue(int x, int y)`
This function is called by the Entity itself after its' “children” Entities are drawn. Given position is the same that was passed to **[redraw()](04_Entity.md#void-redraw)**.

----
##### `void update_before_queue(int x, int y)`
This function is called by the Entity itself before its' “children” Entities are updated. Given position is the same that was passed to **[update()](04_Entity.md#void-redraw)**.

----
##### `void update_after_queue(int x, int y)`
This function is called by the Entity itself after its' “children” Entities are updated. Given position is the same that was passed to **[update()](04_Entity.md#void-redraw)**.

## Entity class' functions

There are some getter and setter functions and methods in Entity class:

##### `void set_x(int)`
Sets Entity's x-position.  

----
##### `void set_y(int)`
Sets Entity's y-position.  

----
##### `void set_priority(int)`
Sets Entity's priority.  

----
##### `void set_visible(bool)`
Sets Entity's visibility. (visible is **true**, invisible is **false**)  

----
##### `void set_enabled(bool)`
Sets either Entity is enabled or not. (enabled is **true**, disabled is **false**)    

----
##### `void destruct()`
Makes the Entity disappear and free it's memory. It will be removed from its' “parent” Entity's queue automatically.  

----
##### `int x()`
Returns Entity's x-position.  

----
##### `int y()`
Returns Entity's y-position.  

----
##### `int priority()`
Returns Entity's priority.  

----
##### `bool visible()`
Returns Entity's visibility. (visible is **true**, invisible is **false**)  

----
##### `bool enabled()`
Returns whether Entity is enabled or not. (enabled is **true**, disabled is **false**)  

----
##### `bool destroy()`
Returns whether Entity is destructed or not. (**true** or **false** respectively)  

## Entity class' design

Entities may have “children” Entities and should notify them to update their state and to draw on the display. Every Entity have priority value, so those should be kept in order. There are a special queue and some service functions to deal it. These functions should be used from overriden virtual functions.

These are functions to deal with queue of “children” Entities:

##### `void add_object(Entity* entity, bool reorder = true)`
This function adds a new child to the queue. As queue's order can be broken by this action, it can be reordered right after Entity is added. But as the reordering operation can be time-expensive, you can pass **false** parameter and manually ask to reorder the queue when it's necessary.  

----
##### `void clear_queue()`
This function removes all Entities from the queue.

----
##### `void redraw_queue(int x, int y)`
This function draws all Entities in the queue on the display with given offset by X and Y axes.  

----
##### `void reorder_queue()`
This function reorders the queue.  

----
##### `void update_queue(int x, int y)`
This function notifes Entities in the queue to check [Input](08_Input.md) and change their state if necessary.  
Passes offset by X and Y axes.  
   
   
**Previous file:** [Screen class](03_Screen.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Controller class](05_Controller.md)