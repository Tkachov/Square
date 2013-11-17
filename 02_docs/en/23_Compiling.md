# Compiling

As the project is being developed in Code::Blocks IDE, you'll find .cbp file in src/ folders. This file contains some settings that are necessary to build the applications.

It contains Release and Debug configurations with all files you need to compile, compiler flags and linker settings. Note that it contains **sdl2** variable which points SDL2 include and lib directories. If your compiler/linker knows where it is, you may remove it. Otherwise edit it to point to your SDL's include and lib directories.

To run the application you've build, you'll need bunch of DLLs (or .so files on Ubuntu) and resource files like fonts and images. Resource files are placed in repository with source code. DLL and .so files are avaiable to [download on Dropbox](https://dl.dropboxusercontent.com/u/37122166/Square/Square_compiled_shared_libraries.zip).

You can learn libraries versions on repository's main page (in README.md file).  
   
   
**Previous file:** [settings.h file](22_settings_h.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Developing for Android](24_Android.md)