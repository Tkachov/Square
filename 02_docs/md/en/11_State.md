# State class

## Overview

State class is used to storage global (or "persistent") variables' values. State objects can be saved into a file or be loaded from it. To determine the type of saved object this class uses a **char** values that corresponds to some type or class. For example, **'i'** corresponds to int type and **'s'** — to string class. If you storage other classes in State, you should add functions in state.h or these variables won't be saved into file. 

Every variable have two keys to access it. So, the value for **{"a","key"}** key pair is not equal to **{"b","key"}** key pair value. Any type can be storaged as value and you can change value's type if you want (i.e. you can replace **{"a","key"}** int value with string value).

Not actual values, but the pointers to those are storaged. So, if you free the memory manually, values can be lost. If you are updating or replacing a value with State class' functions, pointers will be freed if necessary.

State object is kept in [Game](05_Game.md) object, but a pointer to it is passed to [Screen](03_Screen.md) objects. That's where State class' functions can be used.

## Functions  

##### `void save(ofstream&)`
Writes all variables into given stream.  
(Contains the **switch** of **char**s that corresponds to different types. If you need other types, you have to edit it.)  

----
##### `void load(ifstream&)`
Reads all variables from given stream.  
(Contains the **switch** of **char**s that corresponds to different types. If you need other types, you have to edit it.)  

----
##### `template<typename T> static char get_type(T*) { return 'U'; }`
##### `static char get_type(int*) { return 'i'; }`
##### `static char get_type(string*) { return 's'; }`
Returns **char** that corresponds to the given type.  
(Value **'U'** corresponds "Unknown type", **'i'** — int, **'s'** — string. You have to override function if you need other types.)  

----
##### `void save_value(int*, ofstream&)`
##### `void save_value(string*, ofstream&)`
Writes variable's value into given stream.  
(If you need other types, you have to override this function.)  

----
##### `int* load_value(ifstream&, identity<int>)`
##### `string* load_value(ifstream&, identity<string>)`
Reads variable's value from given stream.  
(If you need other types, you have to override this function.)  

----
##### `void* persistent(string first_key, string second_key)`
Returns the pointer to the variable for given **first_key**, **second_key** pair. If there is no variable for given pair, returns 0 (or throws a string if **[DBG_STOP_ON_UNALLOCATED_VARIABLE](19_debug_h.md#dbg_stop_on_unallocated_variable)** is defined).  
(You'll have to cast returned **void*** pointer to type you need. Assumed you know the type of requested variable.)  

----
##### `template<typename T> void set_persistent(string first_key, string second_key, T* p)`
Adds a variable for given **first_key**, **second_key** pair and storages a pointer to its' value. If there is a value for given pair, it is freed and replaced with given value. If this value's pointer is the same as given pointer, it is not freed.  

----
##### `template<typename T> void update_persistent(string first_key, string second_key, T& value)`
Searches for a pointer for given **first_key**, **second_key** pair. If there is no variable for given pair, does nothing. Otherwise updates value pointer points to with given **value**. If pointer is 0, allocates new memory and updates it with given **value**.  
   
   
**Previous file:** [Logger class](10_Logger.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Image class](12_Image.md)