# wstream and safe_wstream classes

## Overview

On Android there is “sandbox” where your application's files are storaged. Those files can not be read or modified using std::fstream. That's why Square introduces wstream and safe_wstream classes that can write to application's files. To read application's files you can use **[read_file()](21_utils_h.md)** functions.

These classes are something like simplified std::ofstream. safe_wstream flushes all data instantly (so if application will crash, file will contain everything that has to be written before the crash), though it can be a bit slower than using wstream (which does not guarantees that all the information will be written in case of crash).

Both classes have similar interface so functions will be listed for both of them.

## Functions

##### `wstream()`
##### `safe_wstream()`
Constructor (no file is opened).  

----
##### `wstream(string name, bool append = false)`
##### `safe_wstream(string name, bool append = false)`
Constructor which opens file with name **name** for writing (if **append** is **false**) or appending to file's end (if **append** is **true**).  

----
##### `void open(string name, bool append = false)`
Opens file with name **name** for writing (if **append** is **false**) or appending to file's end (if **append** is **true**).  

----
##### `void close()`
Closes opened file.  

----
##### `bool write(const char* str)`
Writes **str** into opened file. Returns **true** if it was written successfully and **false** otherwise.  

----
##### `bool write(string& str)`
Writes **str** into opened file. Returns **true** if it was written successfully and **false** otherwise.

----
##### `template<class T> wstream& operator<<(const T& p)`
##### `template<class T> safe_wstream& operator<<(const T& p)`
Writes **p** into opened file.  
Returns a reference to the same wstream/safe_wstream object so it can be used like a chain:  
`example_wstream << a << b << c << d << e;`  
   
   
**Previous file:** [Timer class](19_Timer.md)  
**[Contents](00_Contents.md)**  
**Next file:** [utils.h file](21_utils_h.md)