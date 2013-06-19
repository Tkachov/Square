#include "loader.h"
#include <iostream>
using std::cout;

namespace Engine {

SDL_Surface* Loader::load_image(string fn) {
 if(imgs.count(fn)==0) {
#ifdef DBG_PRINT_IMAGE_LOADING
  cout << "loading \"" << fn << "\"\n";
#endif
  SDL_Surface* bmp = IMG_Load(fn.c_str());
  if(!bmp) {
   string e("Unable to load bitmap: "); e+=IMG_GetError();
   throw e;
  }
  imgs[fn]=bmp;
 } else {
#ifdef DBG_PRINT_IMAGE_LOADING
  cout << "(\"" << fn << "\" already preloaded)\n";
#endif
 }
 return imgs[fn];
}

Image* Loader::load_texture(string fn, bool keep_surface) {
  if(texs.count(fn)==0) {
#ifdef DBG_PRINT_IMAGE_LOADING
  cout << "loading \"" << fn << "\"\n";
#endif
  SDL_Surface* bmp = IMG_Load(fn.c_str());
  if(!bmp) {
   string e("Unable to load bitmap [for GL-texture]: "); e+=IMG_GetError();
   throw e;
  }

  texs[fn]=surface_to_texture(bmp, !keep_surface);
  if(keep_surface) {
   if(imgs.count(fn)!=0&&imgs[fn]!=bmp) free_image(fn);
   imgs[fn]=bmp;
  }
 } else {
#ifdef DBG_PRINT_IMAGE_LOADING
  cout << "(\"" << fn << "\" already preloaded)\n";
#endif
 }
 return texs[fn];
}

TTF_Font* Loader::load_font(string fn, int sz) {
 string windows_p = "C:\\Windows\\Fonts\\";
 string res_p = "res\\fnt\\";
 string key = fn; key+=(char)(sz+32);
 if(fnts.count(key)==0) {
  string pth = windows_p + fn; pth += ".ttf";
  if(!file_exists(pth.c_str())) {
   pth = res_p + fn; pth += ".ttf";
   if(!file_exists(pth.c_str())) {
    string e = "Unable to find font \""; e+=fn; e+="\".";
    throw e;
   }
  }
  TTF_Font* fnt = TTF_OpenFont(pth.c_str(), sz);
  if(!fnt) {
   string e = "Unable to load font \""; e+=fn; e+="\": "; e+=TTF_GetError();
   throw e;
  }
  fnts[key]=fnt;
 }
 return fnts[key];
}

Sprite Loader::load_sprite(string fn) {
#ifdef DBG_PRINT_SPRITE_LOADING
 cout << "\nloading sprite \"" << fn << "\"\n";
#endif
 ifstream file(fn.c_str());
 int n;
 file >> n;
#ifdef DBG_PRINT_SPRITE_LOADING
 cout << "[n = " << n << "]\n";
#endif
 int spd;
 file >> spd;
#ifdef DBG_PRINT_SPRITE_LOADING
 cout << "[frame delay = " << spd << "]\n";
#endif
 Sprite spr;
 spr.set_speed(spd);
 for(int i=0; i<n; ++i) {
  string s;
  int x, y;
  file >> s >> x >> y;
#ifdef DBG_PRINT_SPRITE_LOADING
  cout << (i+1) << ". ";
#endif
  //SDL_Surface* fr = load_image(s);
  Image img = *load_texture(s);
  img.set_x(x); img.set_y(y);//(fr, x, y);
  if(i) spr.add_frame(img);
  else spr.set_frame(img);
 }
#ifdef DBG_PRINT_SPRITE_LOADING
 cout << "\n";
#endif
 file.close();
 return spr;
}

bool Loader::free_image(string fn) {
 if(imgs.count(fn)==0) return false;
 SDL_FreeSurface(imgs[fn]);
 imgs.erase(fn);
 return true;
}

bool Loader::free_texture(string fn) {
 if(texs.count(fn)==0) return false;
 glDeleteTextures(1, texs[fn]->img());
 delete texs[fn];
 texs.erase(fn);
 return true;
}

bool Loader::free_font(string fn, int sz) {
 string key = fn; key+=(char)(sz+32);
 if(fnts.count(key)==0) return false;
 TTF_CloseFont(fnts[key]);
 fnts.erase(key);
 return true;
}

void Loader::free() {
 for(map<string,SDL_Surface*>::iterator i = imgs.begin(); i!=imgs.end(); ++i) SDL_FreeSurface(i->second);
 for(map<string,Image*>::iterator i = texs.begin(); i!=texs.end(); ++i) glDeleteTextures(1, (i->second)->img());
 for(map<string,TTF_Font*>::iterator i = fnts.begin(); i!=fnts.end(); ++i) TTF_CloseFont(i->second);
 imgs.clear();
 texs.clear();
 fnts.clear();
}

Loader::~Loader() {
 free();
}

}
