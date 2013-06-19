#ifndef LOADER_H
#define LOADER_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "utils.h"
#include "Objects\sprite.h"
#include <fstream>
#include <string>
#include <map>
using namespace Engine::Objects;
using std::ifstream;
using std::string;
using std::map;

namespace Engine {

class Loader {
 map<string, SDL_Surface*> imgs;
 map<string, TTF_Font*> fnts;
 map<string, Image*> texs;

public:
 Loader() {};
 ~Loader();

 SDL_Surface* load_image(string fn);
 Image* load_texture(string fn, bool keep_surface = true);
 TTF_Font* load_font(string fn, int sz);
 Sprite load_sprite(string fn);
 bool free_image(string fn);
 bool free_texture(string fn);
 bool free_font(string fn, int sz);
 void free();
};

}

#endif // LOADER_H
