﻿# String_Table class

## Overview

String_Table class is a container for strings which you can get using the key. These strings can be loaded from a file and be saved into a file. Keys can link to another (i.e. take their value from another keys) and contain places for parameters. Value will contain the parameters you pass in those places.

## Functions  

##### `String_Table()`
Constructor, creates empty table.  

----
##### `String_Table(string filename)`
Constructor, loads the key-value pairs from given file.  

----
##### `void push_table(string table)`
Adds key-value pairs from given file to the table.  
If no file found, the table will not change.  
(If **[DBG_PRINT_WARNINGS](19_debug_h.md#dbg_print_warnings)** is defined warnings will be produced if file is not found or there are invalid or recursive keys.)  
(If **[DBG_PRINT_STRING_TABLES](19_debug_h.md#dbg_print_string_tables)** is defined, will print whole table after loading.)  

----
##### `string operator[](string key)`
Returns the value for given key.  
Returns "" if the key is not defined.  

----
##### `string operator()(string key, string* s0 = 0, string* s1 = 0, string* s2 = 0, string* s3 = 0, string* ss = 0)`
Return the value for given key. If value contains %0%, %1%, %2%, etc, those will be replaced with **s0**, **s1**, **s2**, etc. **ss** is an array of strings. So, %4% is replaced with **ss[0]**, %5% — **ss[1]**, etc.  
If the parameter is not defined (i.e. the pointer equals to 0), corresponding place will contain "".  
Returns "" if the key is not defined.  

----
##### `void clear()`
Removes all key-value pairs from table.  

----
##### `void displace(string key, string new_value)`
Replaces the value for given key with **new_value**.  
(Cannot be link to another key.)  

----
##### `void save_table(string filename)`
Saves all key-value pairs into file with name **filename** that can be loaded using **[push_table()](07_String_Table.md#void-push_tablestring-table)** later.  
No links are saved.

## Variables  

##### `public static String_Table unicode`
Contains special Unicode characters.  
Use: `String_Table::unicode["1000"]`.  
(The table is loaded from unicode.txt in localization folder by default. You can change files' names (or remove unicode.txt loading) in **Game::start()**.)  

----
##### `public static String_Table translate`
Contains key-value pairs from general.txt (and any other files you will push into the table in **Game::start()**).  
Use: `String_Table::translate["key"]` or `String_Table::translate("key", string("Value 1"), string("Value 2"))`.  
   
   
**Previous file:** [Using functors](06_Using_functors.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Input class](08_Input.md)