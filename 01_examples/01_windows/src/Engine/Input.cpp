#include "Input.h"
#include "Logger.h"
#include "Main_Window.h"

namespace Engine {

Filter* Input::filter = 0;
Input* Input::input = 0;
string Input::keyboard_string = "";

/*helper class: pushed to watch_filter() and communicates Input object*/

class Filter
{
 private:
  Input* input;

 public:
  Filter(Input* i): input(i) {};
  int ask_input(SDL_Event* event) { return input->event_filter(event); }
};

int SDLCALL watch_filter(void* filter, SDL_Event* event) {
 Filter* f = static_cast<Filter*>(filter);
 return f->ask_input(event);
}

Input::Input() {
 if(input) throw "Unable to construct Input: Input is a singletone.";
 input = this;

 _app_paused = false;
 _paused = false;
 _quit = false;
 _mx = _my = 0;
 _wx = _wy = 0;

 filter = new Filter(this);
 SDL_AddEventWatch(watch_filter, filter);
}

/*PRIVATE*/

int Input::event_filter(SDL_Event* event) {
 switch(event->type) {
  case SDL_QUIT:
   _quit=true;

   #if DEBUG_LOG_FILTERED_EVENTS == 1
    Logger::log << "###EVENT: quit\n";
   #endif
  break;

  case SDL_APP_TERMINATING:
   //ok, got it [is not combined with SDL_QUIT as it may require other actions]
   _quit=true;

   #if DEBUG_LOG_FILTERED_EVENTS == 1
    Logger::log << "###EVENT: terminating\n";
   #endif
  break;

  case SDL_APP_WILLENTERBACKGROUND:
   //free up resources [not done by Square]
   //DON'T DRAW ANY MORE until you're in the foreground again! [done by Square]
   _app_paused=true;

   #if DEBUG_LOG_FILTERED_EVENTS == 1
    Logger::log << "###EVENT: goin' to enter background [pause]\n";
   #endif
  break;

  case SDL_APP_DIDENTERBACKGROUND:
   //well, we've gone completely, can't do anything else
   _app_paused=true;

   #if DEBUG_LOG_FILTERED_EVENTS == 1
    Logger::log << "###EVENT: entered background [paused]\n";
   #endif
  break;

  case SDL_APP_WILLENTERFOREGROUND:
   //ok, unfreeze...
   _app_paused=false;

   #if DEBUG_LOG_FILTERED_EVENTS == 1
    Logger::log << "###EVENT: goin' to enter foreground [unpause]\n";
   #endif
  break;

  case SDL_APP_DIDENTERFOREGROUND:
   //should have already be unfrozen
   _app_paused=false;

   Main_Window::update_window_size();

   #if DEBUG_LOG_FILTERED_EVENTS == 1
    Logger::log << "###EVENT: entered foreground [unpaused]\n";
   #endif
  break;

  case SDL_APP_LOWMEMORY:
   //well, ignore =)

   #if DEBUG_LOG_FILTERED_EVENTS == 1
    Logger::log << "###EVENT: low memory (ignored)\n";
   #endif
  break;

  default:
   return 1; //we have not used this event
 }
 return 0; //event filtered
}

/*PUBLIC*/

void Input::poll_events() {
 //prepare new values for the frame
 keyboard_string = "";

 for(map<SDL_Keycode, short int>::iterator i=keys.begin(); i!=keys.end(); ++i)
  if(i->second==1) i->second=2; //was pressed -> became hold
  else if(i->second==3) i->second=0; //was released -> became not pressed

 for(map<Uint8, short int>::iterator i=mouses.begin(); i!=mouses.end(); ++i)
  if(i->second==1) i->second=2;
  else if(i->second==3) i->second=0;

 for(map<SDL_Keycode, bool>::iterator i=keys_ate.begin(); i!=keys_ate.end(); ++i)
  i->second=false;

 for(map<Uint8, bool>::iterator i=mouse_ate.begin(); i!=mouse_ate.end(); ++i)
  i->second=false;

 bool mouse_pos_updated = false;

 //poll events to prepared values
 SDL_Event event;
 while(SDL_PollEvent(&event)) {
  switch(event.type) {
   case SDL_QUIT:
    _quit=true;
   break;

   case SDL_KEYDOWN:
    keys[event.key.keysym.sym] = 1;
   break;

   case SDL_KEYUP:
    keys[event.key.keysym.sym] = 3;
   break;

   case SDL_TEXTINPUT:
    Input::keyboard_string+=event.text.text;
   break;

   case SDL_MOUSEMOTION:
    _mx = event.motion.x;
    _my = event.motion.y;
    mouse_pos_updated = true;
   break;

   case SDL_MOUSEBUTTONDOWN:
    mouses[event.button.button]=1;

    _mx = event.button.x;
    _my = event.button.y;
    mouse_pos_updated = true;
   break;

   case SDL_MOUSEBUTTONUP:
    mouses[event.button.button]=3;

    _mx = event.button.x;
    _my = event.button.y;
    mouse_pos_updated = true;
   break;

   case SDL_MOUSEWHEEL:
    _wx = event.wheel.x;
    _wy = event.wheel.y;
   break;
  }
 }

 if(mouse_pos_updated && Main_Window::get_fullscreen() == fs_WINDOWED_STRETCHED) {
  _mx = ((double)_mx) * (double)Main_Window::get_projection_width() / (double)Main_Window::get_viewport_width();
  _my = ((double)_my) * (double)Main_Window::get_projection_height() / (double)Main_Window::get_viewport_height();
 }
}

//{ statics

//{ getters

//{ keyboard

short int Input::key(SDL_Keycode k) {
 return (input->keys.count(k)?input->keys[k]:0);
}

bool Input::key_press(SDL_Keycode k, bool eat) {
 if(input->keys.count(k)!=0) {
  if((input->keys_ate.count(k)==0 || !input->keys_ate[k]) && input->keys[k]==1) {
   if(eat) input->keys_ate[k]=true;
   return true;
  }
 }
 return false;
}

bool Input::key_hold(SDL_Keycode k, bool eat) {
 if(input->keys.count(k)!=0) {
  if((input->keys_ate.count(k)==0 || !input->keys_ate[k]) && input->keys[k]==2) {
   if(eat) input->keys_ate[k]=true;
   return true;
  }
 }
 return false;
}

bool Input::key_release(SDL_Keycode k, bool eat) {
 if(input->keys.count(k)!=0) {
  if((input->keys_ate.count(k)==0 || !input->keys_ate[k]) && input->keys[k]==3) {
   if(eat) input->keys_ate[k]=true;
   return true;
  }
 }
 return false;
}

bool Input::key_eaten(SDL_Keycode k) {
 return (input->keys_ate.count(k) && input->keys_ate[k]);
}

//}

//{ mouse

short int Input::mouse(Uint8 b) {
 return (input->mouses.count(b)?input->mouses[b]:0);
}

bool Input::mouse_press(Uint8 b, bool eat) {
 if(input->mouses.count(b)!=0) {
  if((input->mouse_ate.count(b)==0 || !input->mouse_ate[b]) && input->mouses[b]==1) {
   if(eat) input->mouse_ate[b]=true;
   return true;
  }
 }
 return false;
}

bool Input::mouse_hold(Uint8 b, bool eat) {
 if(input->mouses.count(b)!=0) {
  if((input->mouse_ate.count(b)==0 || !input->mouse_ate[b]) && input->mouses[b]==2) {
   if(eat) input->mouse_ate[b]=true;
   return true;
  }
 }
 return false;
}

bool Input::mouse_release(Uint8 b, bool eat) {
 if(input->mouses.count(b)!=0) {
  if((input->mouse_ate.count(b)==0 || !input->mouse_ate[b]) && input->mouses[b]==3) {
   if(eat) input->mouse_ate[b]=true;
   return true;
  }
 }
 return false;
}

bool Input::mouse_eaten(Uint8 b) {
 return (input->mouse_ate.count(b) && input->mouse_ate[b]);
}

int Input::mouse_x() {
 return input->_mx;
}

int Input::mouse_y() {
 return input->_my;
}

int Input::wheel_x() {
 return input->_wx;
}

int Input::wheel_y() {
 return input->_wy;
}

//}

bool Input::app_paused() {
 return input->_app_paused;
}

bool Input::paused() {
 return input->_paused;
}

bool Input::quit() {
 return input->_quit;
}

//}

//{ setters

void Input::key_eat(SDL_Keycode k) {
 input->keys_ate[k]=true;
}

void Input::mouse_eat(Uint8 b) {
 input->mouse_ate[b]=true;
}

void Input::pause() {
 input->_paused = true;
}

void Input::unpause() {
 input->_paused = false;
}

//}

//}

}
