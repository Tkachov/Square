#include "Controller.h"
#include "Loop.h"
#include "Resources.h"

namespace Engine {

Controller::Controller(String_Table* _options, State* _state) {
 loop = 0;
 options = _options;
 resources = new Resources(this);
 state = _state;

 if(!options || !resources || !state) throw "Unable to control.";
}

Controller::~Controller() {
 resources->free();
 delete resources;
}

/* SERVICE FUNCTIONS */

void Controller::bind_loop(Loop* _loop) {
 if(!_loop) throw "Unable to bind loop.";
 loop = _loop;
}

/* GENERAL FUNCTIONS */

void Controller::save(string fn) {
 if(loop) loop->save(fn);
}

void Controller::load(string fn) {
 if(loop) loop->load(fn);
}

/* INPUT FUNCTIONS */

void Controller::poll_events() {
 input.poll_events();
}

/* LOOP FUNCTIONS */

void Controller::stop_loop() {
 if(loop) loop->stop();
}

void Controller::restart_loop(bool keep_state) {
 if(loop) loop->restart(keep_state);
}

void Controller::open_screen(Screen* screen) {
 if(loop) loop->open_screen(screen);
}

void Controller::open_screen(ScreenID sid, bool recreate) {
 if(loop) loop->open_screen(sid, recreate);
}

/* OPTIONS FUNCTIONS */

string Controller::get_option(string key) {
 return (*options)[key];
}

void Controller::set_option(string key, string value) {
 options->displace(key, value);
}

void Controller::save_options() {
 options->save_table("config.txt");
}

/* STATE FUNCTIONS */

void Controller::save_state(ofstream& fout) {
 state->save(fout);
}

void Controller::load_state(ifstream& fin) {
 state->load(fin);
}

}
