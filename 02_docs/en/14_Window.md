# Window class

## Overview

Window class can be used to show windows on the screen. It inherits [Entity](04_Entity.md) class and provides the simplest base for windows.

Windows can be modal — they will pause input and unpause it only to update its' own and its' children state.

## Functions  

##### `Window(Controller* controller, int x, int y, bool modal = false)`
Constuctor, passes **controller** to Entity constructor, moves itself to **x**, **y** and becomes modal if **modal** is **true**.  

----
##### `void update(int x, int y)` [inherited from [Entity](04_Entity.md#void-updateint-x-int-y)]
Updates its' “children” Entities. If Window is modal, it unpauses [Input](08_Input.md) and pauses it again after every “child” Entity is updated.  

----
##### `bool modal()`  
Returns whether Window is modal or not.  
   
   
**Previous file:** [String_Table class](13_String_Table.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Sprite class](15_Sprite.md)