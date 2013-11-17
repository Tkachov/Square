# Square 0.3.0

Square is a simple system which is based on SDL2 and OpenGL libraries.
It manages resources loading and input and gives you simple classes that can be used in the application.
There are two general components: Screens and Entities. Screens are containers for Entities. Entities are everything that can be drawn or interacted with. You can switch from one Screen to another. So, menus and levels are Screens and buttons and characters are Entities. All you have to do is to implement necessary Entities and put them in necessary Screens.

[Go to documentation](02_docs/en/00_Contents.md) ([Russian](02_docs/ru/00_Contents.md) available.)  

## Ubuntu and Android support (10/31/13)

Square's now cross-platform. You can use the same C++ source code to build application for Windows, Ubuntu and Android.

Also, Square now uses [zlib license](http://gzip.org/zlib/zlib_license.html) — you can freely use it for any purpose though you must not claim that you wrote the original software.

## API changing (08/24/13)

Square's API is not stable yet and can change dramatically from one version to another.  
The 0.2.0 version is based on SDL 2.0.0 and is not backwards-compatible.  
Version 0.1.0 was based on SDL 1.2.14 and is obsolete now.  

## Repository contents

Repository contains not only source code and documentation, but also some files that are required to run the application. These are graphics and text files which are used in examples. The application will crash if some file will be lost.

Repository does not contains DLLs, LD.SOs of SDL or final binaries of Square applications. You can [get it at Dropbox](https://dl.dropboxusercontent.com/u/37122166/Square/Square2_binaries.zip) though.  

As the project is being developed in Code::Blocks IDE, you'll find .cbp file in src/ folders. This file contains all the information needed to build the applications.
(It contains Code::Blocks **sdl2** global variable. Set it to the path where SDL2 files can be found. You can also remove it from your project if linker and compiler know where SDL2 files are placed.)

These folders can be found in repository:
* 00_engine, — contains source code and template projects.
    + 00_template, — Windows and Ubuntu template project,
    + 01_android_project, — Android project folder.
* 01_examples, — contains example application.
	+ 01_windows, — example of child popup windows.
* 02_docs, — contains Square documentation.
    + en, — English documentation in Markdown format,
    + ru, — Russian documentation in Markdown format.    

## Libraries' versions

* SDL 2.0.0,
* SDL_image 2.0.0,
* SDL_ttf 2.0.12.

## Version history

### 0.3.0

* added Ubuntu and Android support,
* some minor changes were made in API.

### 0.2.0

* rewritten to use SDL 2.0.0 libraries,
* API was changed, some classes were removed or has been rewritten almost completely.

### 0.1.0

* first version. Used SDL 1.2.14.
