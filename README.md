# Square 0.2.0

Square is a simple system which is based on SDL2 and OpenGL libraries.
It manages resources loading and input and gives you simple classes that can be used in the application.
There are two general components: Screens and Entities. Screens are containers for Entities. Entities are everything that can be drawn or interacted with. You can switch from one Screen to another. So, menus and levels are Screens and buttons and characters are Entities. All you have to do is to implement necessary Entities and put them in necessary Screens.

## API changing (08/24/13)

API of Square is not stable yet. It means that API can be changed dramatically from one version to another.
Current version is 0.2.0. It is based on SDL 2.0.0 and is not backwards-compatible.
Previous version 0.1.0 was based on SDL 1.2.14 and is obsolete now.

Please note that documentation and examples were not changed yet.

[Go to documentation](02_docs/md/en/00_Contents.md) **0.1.0**. ([Russian](02_docs/md/ru/00_Contents.md) available.)

## Repository contents

Repository contains not only source code and documentation, but also some files that are required to run the application. These are graphics and text files which are used in examples. The application will crash if some file will be lost.

Repository does not contains DLLs or final binaries. You can [get it at Dropbox](https://dl.dropboxusercontent.com/u/37122166/Square/Square2_binaries.zip) though.
(You can also get 0.1.0 binaries [at Dropbox](https://dl.dropboxusercontent.com/u/37122166/Square/Square_binaries.zip).)

As the project is being developed in Code::Blocks IDE, you'll find .cbp file in src/ folders. This file contains all the information needed to build the applications.
(It contains Code::Blocks **sdl2** global variable. Set it to the path where SDL2 files can be found. You can also remove it from your project if linker and compiler know where SDL2 files are placed.)

These folders can be found in repository:
* 00_engine, — contains a template project which can be used to create a new application (**0.2.0**).
* 01_examples, — contains example applications (**0.1.0**).
    + 00_TBS, — contains turn-based strategy example,
    + 01_windows, — contains windows example (which you can drag, open and close).
* 02_docs, — contains Square documentation (**0.1.0**).
    + md, — Markdown format.
    + plaintext, — txt-files.

## Libraries' versions

* SDL 2.0.0,
* SDL_image 2.0.0,
* SDL_ttf 2.0.12.

## Version history

### 0.2.0

* rewritten to use SDL 2.0.0 libraries,
* API was changed, some classes were removed or has been rewritten almost completely.

### 0.1.0

* first version. Used SDL 1.2.14.