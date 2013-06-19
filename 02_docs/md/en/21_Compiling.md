# Compiling

As the project is being developed in Code::Blocks IDE, you'll find .cbp file in src/ folders. This file contains some settings that are necessary to build the applications.

It contains Release and Debug configurations with all files you need to compile, compiler flags and linker settings. It also defines DEBUG_H in Release configuration to ignore debug.h and it's **#define** directives.

To run the application you've build, you'll need bunch of DLLs and resource files like images and fonts. DLL files are avaiable to [download on Dropbox](https://dl.dropboxusercontent.com/u/37122166/Square/Square_binaries.zip) (archive contains also object files and compiled executable files) and resource files are placed in repository with source code.

You can learn libraries versions on repository's main page (in README.md file).  
   
   
**Previous file:** [utils.h file](20_utils_h.md)  
**[Contents](00_Contents.md)**