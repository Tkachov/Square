# Square

Square is a simple system which is based on SDL+OpenGL libraries.
It includes the base classes and some primitive classes that are derived from the base ones.
There are two general components: Screens and Objects. Screens are containers for Objects. Objects are everything that can be drawn and interacted with. You can switch from one Screen to another. So, menus and levels are Screens and buttons and characters are Objects. All you have to do is to implement necessary Objects and put them in necessary Screens.

[Go to documentation](02_docs/md/en/00_Contents.md). ([Russian](02_docs/md/ru/00_Contents.md) available.)

## Repository contents

Repository contains not only source code and documentation, but also some files that are required to run the application. These are graphics and text files which are used in examples. The application will crash if some file will be lost.

Repository does not contains DLLs, object files and final binaries. You can [get it at Dropbox](https://dl.dropboxusercontent.com/u/37122166/Square/Square_binaries.zip) though.

As the project is being developed in Code::Blocks IDE, you'll find .cbp file in src/ folders. This file contains some settings that are necessary to build the applications.

These folders can be found in repository:
* 00_engine, — contains (almost empty) template project which can be used to create a new application.
* 01_examples, — contains example applications.
    + 00_TBS, — contains turn-based strategy example.
* 02_docs, — contains Square documentation.
    + md, — Markdown format.
    + plaintext, — txt-files.

## Libraries' versions

* SDL 1.2.14,
* SDL_image 1.2.12,
* SDL_ttf 2.0.11.