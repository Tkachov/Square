# State class

## Overview

State class is used to storage global (or “persistent”) variables' values. State objects can be saved into a file or be loaded from it. To determine the type of saved object this class uses a **char** values that corresponds to some type or class. For example, **'i'** corresponds to int type and **'s'** — to string class. If you storage other classes in State, you should add functions in State.h or these variables won't be saved into file. 

Every variable have two keys to access it. So, the value for **{"a","key"}** key pair is not equal to **{"b","key"}** key pair value. Any type can be storaged as value and you can change value's type if you want (i.e. you can replace **{"a","key"}** int value with string value).

Not actual values, but the pointers to those are storaged. So, if you free the memory manually, values can be lost. If you are updating or replacing a value with State class' functions, pointers will be freed if necessary.

State's functions are static, so you can use those from any place you want to.

## Functions  

##### `static void* persistent(string first_key, string second_key)`
Returns the pointer to the variable for given **first_key**, **second_key** pair. If there is no variable for given pair, returns 0 (or throws a string if **[DEBUG_EXCEPTION_ON_UNALLOCATED_VARIABLE](22_settings_h.md#debug_exception_on_unallocated_variable)** is defined).  
(You'll have to cast returned **void*** pointer to type you need. Assumed you know the type of requested variable.)  

----
##### `template<typename T> static void set_persistent(string first_key, string second_key, T* p)`
Adds a variable for given **first_key**, **second_key** pair and storages a pointer to its' value. If there is a value for given pair, it is freed and replaced with given value. If this value's pointer is the same as given pointer, it is not freed.  

----
##### `template<typename T> static void update_persistent(string first_key, string second_key, T& value)`
Searches for a pointer for given **first_key**, **second_key** pair. If there is no variable for given pair, does nothing. Otherwise updates value pointer points to with given **value**. If pointer is 0, allocates new memory and updates it with given **value**.  

## State class' design

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
(Value **'U'** corresponds “Unknown type”, **'i'** — int, **'s'** — string. You have to override function if you need other types.)  

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
   
   
**Previous file:** [Input class](08_Input.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Logger class](10_Logger.md)