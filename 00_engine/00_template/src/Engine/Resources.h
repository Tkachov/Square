#ifndef RESOURCES_H
#define RESOURCES_H

#include <map>
#include <string>
#include <SDL_ttf.h>
#include "Entities/Sprite.h"
using std::map;
using std::string;
using Engine::Entities::Sprite;

namespace Engine {

class Controller;

namespace Data { class Frame; }
using Engine::Data::Frame;

class Resources {
 private:
  static Resources* resources;

  Controller* controller;

  map<string, Frame*> textures;
  map<string, TTF_Font*> fonts;

 public:
  Resources(Controller* controller);
  ~Resources();

  //loading
  static Frame* load_texture(string fn);
  static Sprite load_sprite(string fn);
  static TTF_Font* load_font(string n, unsigned int sz);
  static Sprite make_sprite(string fn);

  //freeing
  void free();
  static bool free_texture(string fn);
  static bool free_font(string n, unsigned int sz);
  static void free_textures();

};

}

#endif // RESOURCES_H
