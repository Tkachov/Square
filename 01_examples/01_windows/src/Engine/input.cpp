#include "input.h"
#include "utils.h"
namespace Engine {
 Input::Input(): quit(false), pausing(false) {
  for(int i=0; i<SDLK_LAST; ++i) {
   mouses[i]=keys[i]=0;
   mouse_ate[i]=keys_ate[i]=false;
  }
 }

 short int Input::key(int k) { return keys[k]; }
 short int Input::mouse(int k) { return mouses[k]; }
 int Input::mouse_x() { return mx; }
 int Input::mouse_y() { return my; }
 bool Input::mouse_eaten(int k) { return mouse_ate[k]; }
 void Input::mouse_eat(int k) { mouse_ate[k]=true; }
 bool Input::key_eaten(int k) { return keys_ate[k]; }
 void Input::key_eat(int k) { keys_ate[k]=true; }
 bool Input::terminate() { return quit; }
 bool Input::paused() { return pausing; }

 bool Input::key_press(int k, bool eat) {
  if(!keys_ate[k] && keys[k]==1) {
   if(eat) keys_ate[k]=true;
   return true;
  }
  return false;
 }
 bool Input::key_hold(int k, bool eat) {
  if(!keys_ate[k] && keys[k]==2) {
   if(eat) keys_ate[k]=true;
   return true;
  }
  return false;
 }
 bool Input::key_release(int k, bool eat) {
  if(!keys_ate[k] && keys[k]==3) {
   if(eat) keys_ate[k]=true;
   return true;
  }
  return false;
 }

 bool Input::mouse_press(int k, bool eat) {
  if(!mouse_ate[k] && mouses[k]==1) {
   if(eat) mouse_ate[k]=true;
   return true;
  }
  return false;
 }
 bool Input::mouse_hold(int k, bool eat) {
  if(!mouse_ate[k] && mouses[k]==2) {
   if(eat) mouse_ate[k]=true;
   return true;
  }
  return false;
 }
 bool Input::mouse_release(int k, bool eat) {
  if(!mouse_ate[k] && mouses[k]==3) {
   if(eat) mouse_ate[k]=true;
   return true;
  }
  return false;
 }

 void Input::poll_events() {
  keyboard_string.clear();
  for(int i=0; i<SDLK_LAST; ++i) {
   if(keys[i]==3) keys[i]=0;
   if(mouses[i]==3) mouses[i]=0;
   if(keys[i]==1) keys[i]=2;
   if(mouses[i]==1) mouses[i]=2;
   mouse_ate[i]=keys_ate[i]=false;
  }

  SDL_Event event;
  Uint16 v;
  SDL_EnableUNICODE(1);
  while(SDL_PollEvent(&event)) {
   switch(event.type) {
    case SDL_QUIT: quit=true; break;

    case SDL_KEYDOWN:
     keys[event.key.keysym.sym] = 1;
     v = event.key.keysym.unicode;
     if(v) {
      keychar kc;
      kc.unicode = unichar(v);
      kc.keycode = event.key.keysym.sym;
      keyboard_string.push_back(kc);
     }
    break;

    case SDL_KEYUP:
     keys[event.key.keysym.sym] = 3;
    break;

    case SDL_MOUSEMOTION:
     mx = event.motion.x;
     my = event.motion.y;
    break;

    case SDL_MOUSEBUTTONDOWN:
     for(int i=0; i<SDLK_LAST; ++i)
      if(event.button.button == i) mouses[i]=1;
    break;

    case SDL_MOUSEBUTTONUP:
     for(int i=0; i<SDLK_LAST; ++i)
      if(event.button.button == i) mouses[i]=3;
    break;
   }
  }
 }

 void Input::pause() { pausing=true; }
 void Input::unpause() { pausing=false; }
 void Input::repeating(bool enable) {
  if(enable) SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
  else SDL_EnableKeyRepeat(0,0);
 }
}
