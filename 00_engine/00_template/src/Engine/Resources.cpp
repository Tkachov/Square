#include <fstream>
#include <SDL_image.h>
#include "Logger.h"
#include "Resources.h"
#include "settings.h"
#include "utils.h"
#include "Data/Frame.h"
using std::ifstream;

namespace Engine {

Resources* Resources::resources = 0;

Resources::Resources(Controller* _controller) {
 if(resources) throw "Unable to construct Resources: Resources is a singletone.";
 resources = this;
 if(!_controller) throw "Unable to bind resources to a controller.";
 controller = _controller;
}

Resources::~Resources() { free(); }

//{ /* LOADING FUNCTIONS */

TTF_Font* Resources::load_font(string name, unsigned int sz) {
 string key = name; key+=(char)(sz+32);

 if(resources->fonts.count(key)==0) {
  //look for a font
  string windows_p = "C:\\Windows\\Fonts\\";
  string res_p = "res/fnt/";
  string pth = windows_p + name; pth += ".ttf";
  if(!file_exists(pth.c_str())) {
   pth = res_p + name; pth += ".ttf";
   if(!file_exists(pth.c_str())) {
    string e = "Unable to find font \""; e+=name; e+="\".";
    throw e;
   }
  }

  //load a font
  TTF_Font* fnt = TTF_OpenFont(pth.c_str(), sz);
  if(!fnt) {
   string e = "Unable to load font \""; e+=name; e+="\": "; e+=TTF_GetError();
   throw e;
  }
  resources->fonts[key]=fnt;
 }

 return resources->fonts[key];
}

Sprite Resources::load_sprite(string filename) {
 #if DEBUG_LOG_SPRITE_LOADING == 1
  Logger::log << "\nloading sprite \"" << filename << "\"\n";
 #endif
 ifstream file(filename.c_str());
 int n;
 file >> n;
 #if DEBUG_LOG_SPRITE_LOADING == 1
  Logger::log << "[n = " << n << "]\n";
 #endif
 int spd;
 file >> spd;
 #if DEBUG_LOG_SPRITE_LOADING == 1
  Logger::log << "[frame delay = " << spd << "]\n";
 #endif
 Sprite spr(resources->controller);
 spr.set_speed(spd);
 for(int i=0; i<n; ++i) {
  #if DEBUG_LOG_SPRITE_LOADING == 1
   Logger::log << (i+1) << ". ";
  #endif

  char m;
  file >> m;
  switch(m) {
   case 's': //for Strip
   case 'w': //for Whole
    #if DEBUG_LOG_SPRITE_LOADING == 1
     Logger::log << m << "\n";
    #endif
   break;

   default:
    #if DEBUG_LOG_SPRITE_LOADING == 1
     Logger::log << "Unknown frame mode.\n";
    #endif

    file.ignore(1<<31, '\n');
    continue;
  }

  string s;
  file >> s;
  Frame frame = *load_texture(s);

  //area only in Strip mode
  if(m=='s') {
   int l, t, r, b;
   file >> l >> t >> r >> b;
   frame.set_area(l, t, r, b);
   #if DEBUG_LOG_SPRITE_LOADING == 1
    Logger::log << "Strip area: {" << l << "," << t << "," << r << "," << b << "}.\n";
   #endif
  }

  //shift is in both Strip and Whole modes
  if(m=='s' || m=='w') {
   int x, y;
   file >> x >> y;
   frame.set_shift(x, y);
  }

  if(i) spr.add_frame(frame);
  else spr.set_frame(frame);
 }
 #if DEBUG_LOG_SPRITE_LOADING == 1
  Logger::log << "\n";
 #endif
 file.close();
 return spr;
}

Frame* Resources::load_texture(string filename) {
 if(resources->textures.count(filename)==0) {
  #if DEBUG_LOG_IMAGE_LOADING == 1
   Logger::log << "loading \"" << filename << "\"\n";
  #endif
  SDL_Surface* surf = IMG_Load(filename.c_str());
  if(!surf) {
   string e("Unable to load image into SDL_Surface: "); e+=IMG_GetError();
   throw e;
  }

  resources->textures[filename]=surface_to_texture(surf);
 } else {
  #if DEBUG_LOG_IMAGE_LOADING == 1
   Logger::log << "(\"" << filename << "\" already preloaded)\n";
  #endif
 }

 return resources->textures[filename];
}

Sprite Resources::make_sprite(string filename) {
 return Sprite(resources->controller, *load_texture(filename));
}

//}

//{ /* FREEING FUNCIONS */

void Resources::free() {
 for(map<string, TTF_Font*>::iterator i=fonts.begin(); i!=fonts.end(); ++i)
  TTF_CloseFont(i->second);

 fonts.clear();

 free_textures();
}

bool Resources::free_font(string name, unsigned int sz) {
 string key = name; key+=(char)(sz+32);
 if(resources->fonts.count(key)==0) return false;
 TTF_CloseFont(resources->fonts[key]);
 resources->fonts.erase(key);
 return true;
}

bool Resources::free_texture(string filename) {
 if(resources->textures.count(filename)==0) return false;
 glDeleteTextures(1, resources->textures[filename]->texture());
 delete resources->textures[filename];
 resources->textures.erase(filename);
 return true;
}

void Resources::free_textures() {
 for(map<string, Frame*>::iterator i=resources->textures.begin(); i!=resources->textures.end(); ++i)
  glDeleteTextures(1, (i->second)->texture());

 resources->textures.clear();
}

//}

}
