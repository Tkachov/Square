﻿# Logger class

## Overview

Logger class gives you ability to write messages into log files and console from every class you have.  
It creates a file only when it's really necessary (i.e. when first message was sent in Logger object).  
When you compile your project in Debug configuration, the application will also have a console window. 
It can be used to see in which moment messages are logged.

## Functions  

##### `template<class T> Logger& operator<<(const T& p)`
Writes a **T** class' value into file and console streams.  
Returns a reference to Logger object so it can be used like a chain:  
`Logger::log << a << b << c << d << e;`  

----
##### `static void start_session()`
Ends previous session (if it was started) and removes old log files.  

----
##### `static void end_session()`
Ends current session (if it was started) and closes log files (so something else will be able to open these).

## Variables  

##### `static Logger log`
Is attached to log.txt file and **cout** console stream.  
Use: `Logger::log << "message";`.  

----
##### `static Logger err`
Is attached to errors.txt file and **cerr** console stream.  
Use: `Logger::err << "error";`.  
   
   
**Previous file:** [State class](09_State.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Functor class](11_Functor.md)