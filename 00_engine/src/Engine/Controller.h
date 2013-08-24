#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <fstream>
#include <string>
#include "Input.h"
#include "Main_Window.h"
#include "State.h"
#include "Data\String_Table.h"
#include "Global\ScreenID.h"
using std::ifstream;
using std::ofstream;
using std::string;
using Engine::Data::String_Table;
//using Engine::Entities::Screen;
using Engine::Global::ScreenID;

namespace Engine {

class Loop;
class Resources;

class Controller {
 private:
  Input input;
  Loop* loop;
  String_Table* options;
  Resources* resources;
  State* state;
  Main_Window window;

 public:
  Controller(String_Table* options, State* state);
  ~Controller();

  //service functions
  void bind_loop(Loop* loop);

  //general functions
  void save(string fn);
  void load(string fn);

  //Input functions
  void poll_events();

  //Loop functions
  void stop_loop();
  void restart_loop(bool keep_state);
  void open_screen(Screen* screen);
  void open_screen(ScreenID sid, bool recreate = false);

  //Options functions
  string get_option(string key);
  void set_option(string key, string value);
  void save_options();

  //State functions
  void save_state(ofstream& fout);
  void load_state(ifstream& fin);

};

}

#endif // CONTROLLER_H
