#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
#include "State.h"
#include "Data\String_Table.h"
using Engine::Data::String_Table;

namespace Engine {

class Application {
 private:
  bool __sdl_was_init;
  bool __img_was_init;
  bool __ttf_was_init;

  String_Table options;
  State state;

  void load_options(int argc, char** argv);

 public:
  Application();
  ~Application();

  void work(int argc, char** argv);

};

}

#endif // APPLICATION_H
